# Day 03: Communication Layer and Win32 RS485

## 1. Stage Objective
Build a flexible, polymorphic hardware communication layer in C++. Implement the `ICommChannel` abstract interface and create the concrete `Win32SerialChannel` driver configured for full-duplex RS485 serial communication under Windows.

---

## 2. Why We Are Doing This Step
Requirement 1 explicitly states:
> *"Allow user to setup rs485 full duplex serial communication - com port, baud rate, databit, flow control etc. (Make it flexible to support multiple communication like CAN, rs232, REST API, Modbus)"*

If serial port handling is tied directly to the protocol parser or GUI callbacks:
- Supporting a future CAN bus adapter (e.g. PCAN-USB) or Modbus TCP gateway would require re-writing the entire application.
- Direct Windows API calls (`CreateFile`, `ReadFile`) scattered across the project would create high coupling and fragile code.

By creating an **`ICommChannel` interface**, the upper polling and protocol layers only talk to a generic stream abstraction. Swapping RS485 for CAN, RS232, or a REST API endpoint is as simple as injecting a different channel implementation.

---

## 3. How It Fits Into The Project
```
       +---------------------------------------------+
       |   ChamberEngine (1 Hz Polling & Logging)    |
       +---------------------------------------------+
                              |
                              v
       +---------------------------------------------+
       |             << ICommChannel >>              |
       |  + Open(config)                             |
       |  + Close()                                  |
       |  + Write(data)                              |
       |  + ReadUntil(delimiter, timeoutMs)          |
       |  + IsOpen()                                 |
       +---------------------------------------------+
                              |
            +-----------------+-----------------+
            |                                   |
            v                                   v
+-----------------------+           +-----------------------+
|  Win32SerialChannel   |           |  Future Channels      |
|  - Windows COM Port   |           |  - CanCommChannel     |
|  - RS485 Full Duplex  |           |  - ModbusTcpChannel   |
|  - Baud, Parity, Bits |           |  - RestApiChannel     |
+-----------------------+           +-----------------------+
            |
            v
   Win32 COM API (COM1..COM256)
```

---

## 4. Understanding RS485 Full Duplex on Windows

1. **4-Wire Full Duplex:**
   * Full-duplex RS485 utilizes independent TX pair and RX pair lines.
   * Unlike 2-wire half-duplex (which requires strict RTS pin toggle timing to switch the transceiver between transmit and receive mode), 4-wire full duplex can transmit and receive simultaneously, just like standard RS232.
2. **Win32 Serial Subsystem:**
   * Ports beyond COM9 (e.g. `COM10`, `COM24`) must be addressed using the device namespace `\\\\.\\COMx`.
   * Non-blocking operation is achieved by configuring `COMMTIMEOUTS`. If the main controller takes longer than the timeout to respond, `ReadFile` returns without hanging the worker thread indefinitely.

---

## 5. Implementation: `ICommChannel.h`

Save this file at: `WindowsSimulator/Application/Source/ICommChannel.h`:

```cpp
#pragma once
#include <string>
#include <cstdint>
#include <vector>

enum class ChannelType {
    RS485_FullDuplex,
    RS232,
    CAN,
    ModbusRTU,
    ModbusTCP,
    RestAPI
};

struct SerialConfig {
    std::string portName = "COM1";
    uint32_t baudRate = 115200;
    uint8_t dataBits = 8;
    uint8_t stopBits = 1;       // 1 = ONESTOPBIT, 2 = TWOSTOPBITS
    uint8_t parity = 0;         // 0 = NOPARITY, 1 = ODDPARITY, 2 = EVENPARITY
    bool hardwareFlowControl = false;
};

class ICommChannel {
public:
    virtual ~ICommChannel() = default;

    // Lifecycle
    virtual bool Open(const SerialConfig& config) = 0;
    virtual void Close() = 0;
    virtual bool IsOpen() const = 0;

    // Data Transfer
    virtual bool Write(const std::string& data) = 0;
    virtual bool ReadUntil(std::string& outData, char delimiter, uint32_t timeoutMs) = 0;
    virtual void Purge() = 0;

    // Diagnostics
    virtual std::string GetLastErrorMessage() const = 0;
};
```

---

## 6. Implementation: `Win32SerialChannel.h`

Save this file at: `WindowsSimulator/Application/Source/Win32SerialChannel.h`:

```cpp
#pragma once
#include "ICommChannel.h"
#include <windows.h>
#include <sstream>

class Win32SerialChannel : public ICommChannel {
private:
    HANDLE hComm = INVALID_HANDLE_VALUE;
    std::string lastError;

public:
    Win32SerialChannel() = default;
    ~Win32SerialChannel() override { Close(); }

    bool Open(const SerialConfig& cfg) override {
        Close();
        lastError.clear();

        // Support ports COM1 through COM256
        std::string fullDevicePath = "\\\\.\\" + cfg.portName;

        hComm = CreateFileA(
            fullDevicePath.c_str(),
            GENERIC_READ | GENERIC_WRITE,
            0,                          // Exclusive access
            NULL,                       // No security attributes
            OPEN_EXISTING,              // Must open existing device
            FILE_ATTRIBUTE_NORMAL,
            NULL
        );

        if (hComm == INVALID_HANDLE_VALUE) {
            lastError = "Failed to open port: " + cfg.portName + " (Error code " + std::to_string(GetLastError()) + ")";
            return false;
        }

        // Configure DCB (Device Control Block)
        DCB dcb = { 0 };
        dcb.DCBlength = sizeof(DCB);
        if (!GetCommState(hComm, &dcb)) {
            lastError = "GetCommState failed";
            Close();
            return false;
        }

        dcb.BaudRate = cfg.baudRate;
        dcb.ByteSize = cfg.dataBits;
        dcb.StopBits = (cfg.stopBits == 2) ? TWOSTOPBITS : ONESTOPBIT;
        dcb.Parity   = (cfg.parity == 1) ? ODDPARITY : (cfg.parity == 2 ? EVENPARITY : NOPARITY);
        dcb.fBinary  = TRUE;
        dcb.fParity  = (cfg.parity != 0);

        // Flow control / RS485 full-duplex configuration
        dcb.fOutxCtsFlow = cfg.hardwareFlowControl;
        dcb.fRtsControl  = cfg.hardwareFlowControl ? RTS_CONTROL_HANDSHAKE : RTS_CONTROL_ENABLE;
        dcb.fOutxDsrFlow = FALSE;
        dcb.fDtrControl  = DTR_CONTROL_ENABLE;

        if (!SetCommState(hComm, &dcb)) {
            lastError = "SetCommState failed (Invalid baud or port settings)";
            Close();
            return false;
        }

        // Configure Non-blocking Timeouts
        COMMTIMEOUTS timeouts = { 0 };
        timeouts.ReadIntervalTimeout         = 10;
        timeouts.ReadTotalTimeoutConstant    = 150; // Max 150 ms wait per frame
        timeouts.ReadTotalTimeoutMultiplier  = 2;
        timeouts.WriteTotalTimeoutConstant   = 100;
        timeouts.WriteTotalTimeoutMultiplier = 2;

        if (!SetCommTimeouts(hComm, &timeouts)) {
            lastError = "SetCommTimeouts failed";
            Close();
            return false;
        }

        Purge();
        return true;
    }

    void Close() override {
        if (hComm != INVALID_HANDLE_VALUE) {
            CloseHandle(hComm);
            hComm = INVALID_HANDLE_VALUE;
        }
    }

    bool IsOpen() const override {
        return (hComm != INVALID_HANDLE_VALUE);
    }

    bool Write(const std::string& data) override {
        if (!IsOpen()) return false;
        DWORD bytesWritten = 0;
        BOOL result = WriteFile(hComm, data.data(), static_cast<DWORD>(data.size()), &bytesWritten, NULL);
        return (result && bytesWritten == data.size());
    }

    bool ReadUntil(std::string& outData, char delimiter, uint32_t timeoutMs) override {
        outData.clear();
        if (!IsOpen()) return false;

        DWORD startTick = GetTickCount();
        char byteIn = 0;
        DWORD bytesRead = 0;

        while ((GetTickCount() - startTick) < timeoutMs) {
            if (ReadFile(hComm, &byteIn, 1, &bytesRead, NULL) && bytesRead > 0) {
                outData += byteIn;
                if (byteIn == delimiter) {
                    return true;
                }
            }
        }
        return false; // Timed out before delimiter was encountered
    }

    void Purge() override {
        if (IsOpen()) {
            PurgeComm(hComm, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);
        }
    }

    std::string GetLastErrorMessage() const override {
        return lastError;
    }
};
```

---

## 7. Verification Checklist
- [ ] `ICommChannel.h` defines a pure virtual interface free from Win32 dependencies.
- [ ] `Win32SerialChannel.h` correctly uses `\\\\.\\` to handle COM ports above COM9.
- [ ] Non-blocking read loop terminates cleanly upon receiving the delimiter (`\r`) or expiring after `timeoutMs`.
