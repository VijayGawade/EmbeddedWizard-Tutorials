# Day 05: Polling Engine and Asynchronous CSV Logger

## 1. Stage Objective
Build the multi-threaded background engine responsible for:
1. Sequentially querying 5–10 chamber parameter addresses every second over RS485.
2. Detecting the connected lighting module (`NONE`, `AH`, or `ICH`) from address `2000`.
3. Logging data to a user-specified CSV file at configurable intervals (**1s, 5s, 30s, 60s, 120s, or 300s**) without degrading GUI responsiveness.

---

## 2. Why We Are Doing This Step
Requirement 3 demands:
- Continuous 1-second live sensor monitoring.
- High-integrity recording into CSV files.
- Dynamic light module interrogation based on hardware status.

### The Pitfalls of Doing This Synchronously:
If we send 7 serial queries sequentially and wait 150 ms for each timeout on the GUI thread:
$$7 \times 150\text{ ms} = 1050\text{ ms}$$
The UI thread would be permanently blocked! Sliders, tabs, and buttons would freeze.

### The Solution:
We spawn a dedicated **C++ Worker Thread** (`ChamberEngine`). The worker thread handles all RS485 turnaround times, parses packets into a thread-safe data cache, streams to the CSV file at the user's chosen interval, and dispatches UI snapshots to the main thread via `EwInvokeCopy`.

---

## 3. How It Fits Into The Project
```
+-------------------------------------------------------------------------------+
|                       ChamberEngine Background Worker                         |
+-------------------------------------------------------------------------------+
       |                                                    |
       v (Every 1 Second)                                   v (Configured Interval:
  Sequential RS485 Queries                                     1s/5s/30s/60s/120s/300s)
  1. 2000: Status & Light Detection                         +---------------------+
  2. 2010: Temperature Data                                 |  CSV File Writer    |
  3. 2020: CO2 Gas Data                                     |  - User file path   |
  4. 2030: Relative Humidity Data                           |  - Formatted time   |
  5. 2040: Load Cell                                        |  - Selected columns |
  6. 2050: Door & Socket IO                                 +---------------------+
  7. 2060/2070: AH or ICH Light Data                                  |
  8. 2080: Active Errors                                              v
       |                                                    Chamber_Log_XXXX.csv
       v
+-------------------------------------------------------------------------------+
|                       EwInvokeCopy Snapshot Dispatch                          |
|  - Pushes live values to Embedded Wizard Chora UI                             |
+-------------------------------------------------------------------------------+
```

---

## 4. Implementation: `ChamberEngine.h`

Save this file at: `WindowsSimulator/Application/Source/ChamberEngine.h`:

```cpp
#pragma once
#include "ICommChannel.h"
#include "ChamberProtocol.h"
#include <thread>
#include <mutex>
#include <atomic>
#include <vector>
#include <string>
#include <fstream>
#include <chrono>

enum class LoggingIntervalSec : uint32_t {
    Sec_1   = 1,
    Sec_5   = 5,
    Sec_30  = 30,
    Sec_60  = 60,
    Sec_120 = 120,
    Sec_300 = 300
};

struct ChamberLiveCache {
    // 2000: Status
    int generalStatus = 0;
    std::string lightModuleType = "NONE"; // "NONE", "AH", "ICH"

    // 2010: Temperature
    float tempSetpoint = 0.0f;
    float tempActual = 0.0f;
    float tempRef = 0.0f;
    std::string tempStatus = "DISABLED";

    // 2020: CO2
    float co2Setpoint = 0.0f;
    float co2Actual = 0.0f;

    // 2030: RH
    float rhSetpoint = 0.0f;
    float rhActual = 0.0f;

    // 2040: Load Cell
    float loadCellWeight = 0.0f;

    // 2050: Hardware IO
    bool doorLocked = false;
    bool socket1Active = false;
    bool socket2Active = false;

    // 2060: AH Light (RGB)
    int lightRed = 0, lightGreen = 0, lightBlue = 0;

    // 2070: ICH Light (UV/VIS)
    int lightUV345 = 0, lightUV365 = 0, lightICH = 0, lightUVA = 0, lightVIS = 0;

    // 2080: Active Errors
    std::string activeErrors = "None";

    // 1000: Info
    std::string fwVersion = "Unknown";
    std::string controllerDateTime = "";
};

struct CsvLoggingConfig {
    std::string filePath;
    LoggingIntervalSec interval = LoggingIntervalSec::Sec_1;
    uint32_t durationSeconds = 0; // 0 = continuous
    bool logTemp = true;
    bool logCO2 = true;
    bool logRH = true;
    bool logLoadCell = true;
    bool logLights = true;
    bool logErrors = true;
};

class ChamberEngine {
private:
    std::unique_ptr<ICommChannel> channel;
    std::unique_ptr<IProtocolHandler> protocol;
    
    std::thread workerThread;
    std::atomic<bool> isRunning{false};
    std::atomic<bool> isLogging{false};

    mutable std::mutex dataMutex;
    ChamberLiveCache cache;

    CsvLoggingConfig logConfig;
    std::ofstream csvFile;
    std::chrono::steady_clock::time_point lastLogTime;
    std::chrono::steady_clock::time_point loggingStartTime;

public:
    ChamberEngine(std::unique_ptr<ICommChannel> ch, std::unique_ptr<IProtocolHandler> proto);
    ~ChamberEngine();

    bool StartConnection(const SerialConfig& cfg);
    void StopConnection();
    bool IsConnected() const;

    bool StartLogging(const CsvLoggingConfig& cfg);
    void StopLogging();
    bool IsLoggingActive() const { return isLogging.load(); }

    ChamberLiveCache GetSnapshot() const;
    bool SendWriteCommand(const std::string& address, const std::string& payload);

private:
    void WorkerLoop();
    void QueryAddress(const std::string& address);
    void ProcessParsedPacket(const ChamberPacket& packet);
    void MaybeWriteCsvRow();
    void BuildAndWriteCsvHeader();
};
```

---

## 5. Implementation: `ChamberEngine.cpp`

Save this file at: `WindowsSimulator/Application/Source/ChamberEngine.cpp`:

```cpp
#include "ChamberEngine.h"
#include <iostream>
#include <iomanip>
#include <ctime>

ChamberEngine::ChamberEngine(std::unique_ptr<ICommChannel> ch, std::unique_ptr<IProtocolHandler> proto)
    : channel(std::move(ch)), protocol(std::move(proto)) {}

ChamberEngine::~ChamberEngine() {
    StopConnection();
}

bool ChamberEngine::StartConnection(const SerialConfig& cfg) {
    if (!channel->Open(cfg)) {
        return false;
    }
    isRunning = true;
    workerThread = std::thread(&ChamberEngine::WorkerLoop, this);
    return true;
}

void ChamberEngine::StopConnection() {
    isRunning = false;
    if (workerThread.joinable()) {
        workerThread.join();
    }
    StopLogging();
    channel->Close();
}

bool ChamberEngine::IsConnected() const {
    return channel && channel->IsOpen();
}

bool ChamberEngine::StartLogging(const CsvLoggingConfig& cfg) {
    std::lock_guard<std::mutex> lock(dataMutex);
    logConfig = cfg;

    csvFile.open(cfg.filePath, std::ios::out | std::ios::trunc);
    if (!csvFile.is_open()) return false;

    BuildAndWriteCsvHeader();
    loggingStartTime = std::chrono::steady_clock::now();
    lastLogTime = loggingStartTime - std::chrono::seconds(1000); // Force immediate first record
    isLogging = true;
    return true;
}

void ChamberEngine::StopLogging() {
    std::lock_guard<std::mutex> lock(dataMutex);
    if (csvFile.is_open()) {
        csvFile.flush();
        csvFile.close();
    }
    isLogging = false;
}

ChamberLiveCache ChamberEngine::GetSnapshot() const {
    std::lock_guard<std::mutex> lock(dataMutex);
    return cache;
}

void ChamberEngine::WorkerLoop() {
    while (isRunning) {
        auto cycleStart = std::chrono::steady_clock::now();

        if (channel->IsOpen()) {
            // 1. Device Status (also detects Light Module)
            QueryAddress("2000");

            // 2. Core Environmental Parameters
            QueryAddress("2010"); // Temp
            QueryAddress("2020"); // CO2
            QueryAddress("2030"); // RH
            QueryAddress("2040"); // Load Cell
            QueryAddress("2050"); // Hardware IO

            // 3. Dynamic Light Module Query
            std::string lightType;
            {
                std::lock_guard<std::mutex> lock(dataMutex);
                lightType = cache.lightModuleType;
            }

            if (lightType == "AH") {
                QueryAddress("2060");
            } else if (lightType == "ICH") {
                QueryAddress("2070");
            }

            // 4. Diagnostics
            QueryAddress("2080");

            // 5. Evaluate CSV Logging
            MaybeWriteCsvRow();
        }

        // Maintain 1 Hz Polling rate
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - cycleStart).count();
        if (elapsed < 1000) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000 - elapsed));
        }
    }
}

void ChamberEngine::QueryAddress(const std::string& address) {
    if (!isRunning || !channel->IsOpen()) return;

    std::string req = protocol->BuildReadRequest(address);
    if (!channel->Write(req)) return;

    std::string response;
    if (channel->ReadUntil(response, '\r', 150)) {
        auto parsed = protocol->ParseIncomingFrame(response);
        if (parsed && parsed->isSuccess) {
            ProcessParsedPacket(*parsed);
        }
    }
    // Polite 20 ms inter-message pause for RS485 line turnaround
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
}

void ChamberEngine::ProcessParsedPacket(const ChamberPacket& packet) {
    std::lock_guard<std::mutex> lock(dataMutex);

    if (packet.address == "2000" && packet.fields.size() >= 5) {
        // generalStatus;TempStatus;CO2Status;RHStatus;LightStatus
        cache.generalStatus = std::stoi(packet.fields[0]);
        cache.lightModuleType = packet.fields[4]; // "NONE", "AH", "ICH"
    }
    else if (packet.address == "2010" && packet.fields.size() >= 7) {
        // setpoint;actual;reference;kp;ki;kd;status
        cache.tempSetpoint = std::stof(packet.fields[0]);
        cache.tempActual   = std::stof(packet.fields[1]);
        cache.tempRef      = std::stof(packet.fields[2]);
        cache.tempStatus   = packet.fields[6];
    }
    else if (packet.address == "2020" && packet.fields.size() >= 2) {
        cache.co2Setpoint  = std::stof(packet.fields[0]);
        cache.co2Actual    = std::stof(packet.fields[1]);
    }
    else if (packet.address == "2030" && packet.fields.size() >= 2) {
        cache.rhSetpoint   = std::stof(packet.fields[0]);
        cache.rhActual     = std::stof(packet.fields[1]);
    }
    else if (packet.address == "2040" && packet.fields.size() >= 1) {
        cache.loadCellWeight = std::stof(packet.fields[0]);
    }
    else if (packet.address == "2050" && packet.fields.size() >= 3) {
        cache.doorLocked     = (packet.fields[0] == "1" || packet.fields[0] == "true");
        cache.socket1Active  = (packet.fields[1] == "1" || packet.fields[1] == "true");
        cache.socket2Active  = (packet.fields[2] == "1" || packet.fields[2] == "true");
    }
    else if (packet.address == "2060" && packet.fields.size() >= 3) { // AH (RGB)
        cache.lightRed   = std::stoi(packet.fields[0]);
        cache.lightGreen = std::stoi(packet.fields[1]);
        cache.lightBlue  = std::stoi(packet.fields[2]);
    }
    else if (packet.address == "2070" && packet.fields.size() >= 5) { // ICH
        cache.lightUV345 = std::stoi(packet.fields[0]);
        cache.lightUV365 = std::stoi(packet.fields[1]);
        cache.lightICH   = std::stoi(packet.fields[2]);
        cache.lightUVA   = std::stoi(packet.fields[3]);
        cache.lightVIS   = std::stoi(packet.fields[4]);
    }
    else if (packet.address == "2080" && packet.fields.size() >= 2) {
        cache.activeErrors = packet.fields[1];
    }
}

void ChamberEngine::BuildAndWriteCsvHeader() {
    csvFile << "Timestamp";
    if (logConfig.logTemp)     csvFile << ",Temp_Actual,Temp_Setpoint,Temp_Status";
    if (logConfig.logCO2)      csvFile << ",CO2_Actual,CO2_Setpoint";
    if (logConfig.logRH)       csvFile << ",RH_Actual,RH_Setpoint";
    if (logConfig.logLoadCell) csvFile << ",Weight_kg";
    if (logConfig.logLights)   csvFile << ",Light_Type,L1,L2,L3,L4,L5";
    if (logConfig.logErrors)   csvFile << ",Active_Errors";
    csvFile << "\n";
}

void ChamberEngine::MaybeWriteCsvRow() {
    if (!isLogging) return;

    auto now = std::chrono::steady_clock::now();
    auto elapsedSec = std::chrono::duration_cast<std::chrono::seconds>(now - lastLogTime).count();

    if (elapsedSec >= static_cast<uint32_t>(logConfig.interval)) {
        lastLogTime = now;

        std::lock_guard<std::mutex> lock(dataMutex);
        auto sysTime = std::chrono::system_clock::now();
        std::time_t tt = std::chrono::system_clock::to_time_t(sysTime);
        char timeStr[32];
        std::strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", std::localtime(&tt));

        csvFile << timeStr;
        if (logConfig.logTemp)     csvFile << "," << cache.tempActual << "," << cache.tempSetpoint << "," << cache.tempStatus;
        if (logConfig.logCO2)      csvFile << "," << cache.co2Actual << "," << cache.co2Setpoint;
        if (logConfig.logRH)       csvFile << "," << cache.rhActual << "," << cache.rhSetpoint;
        if (logConfig.logLoadCell) csvFile << "," << cache.loadCellWeight;
        if (logConfig.logLights) {
            csvFile << "," << cache.lightModuleType;
            if (cache.lightModuleType == "AH") {
                csvFile << "," << cache.lightRed << "," << cache.lightGreen << "," << cache.lightBlue << ",0,0";
            } else if (cache.lightModuleType == "ICH") {
                csvFile << "," << cache.lightUV345 << "," << cache.lightUV365 << "," << cache.lightICH << "," << cache.lightUVA << "," << cache.lightVIS;
            } else {
                csvFile << ",0,0,0,0,0";
            }
        }
        if (logConfig.logErrors)   csvFile << ",\"" << cache.activeErrors << "\"";
        csvFile << "\n";
        csvFile.flush();

        // Check total logging duration
        if (logConfig.durationSeconds > 0) {
            auto totalElapsed = std::chrono::duration_cast<std::chrono::seconds>(now - loggingStartTime).count();
            if (totalElapsed >= logConfig.durationSeconds) {
                StopLogging();
            }
        }
    }
}
```

---

## 6. Verification Checklist
- [ ] Polling loop queries `2000`, `2010`, `2020`, `2030`, `2040`, `2050`, `2080` sequentially once every second.
- [ ] Hardware light detection dynamically chooses between address `2060` (AH) and `2070` (ICH).
- [ ] CSV logging intervals correctly decimate recording between 1s and 300s.
- [ ] Duration timer automatically closes the file handle when the test completes.
