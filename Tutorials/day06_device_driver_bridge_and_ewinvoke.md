# Day 06: Device Driver Bridge and EwInvoke Thread Synchronization

## 1. Stage Objective
Construct the two-way bridge between the background C++ communication engine and the Embedded Wizard Chora UI runtime. Implement `DeviceDriver.h` and `DeviceDriver.cpp` to marshal commands from the GUI to C++, and safely push sensor telemetry back into Chora properties using `EwInvokeCopy()`.

---

## 2. Why We Are Doing This Step
In Embedded Wizard, the GUI runtime is not thread-safe:
- If a background C++ thread attempts to directly set a Chora property like `ApplicationChamberDevice->TempActual = 24.5`, the internal garbage collector, display dirty-region queues, and memory pools will experience data corruption and crash.
- Embedded Wizard provides the **`EwInvoke()` / `EwInvokeCopy()`** mechanism specifically for this purpose. It places an invocation descriptor into the GUI loop's event queue. The main thread executes it during `EwProcessInvocations()`, guaranteeing 100% thread safety without requiring complex mutex locking inside UI views.

---

## 3. How It Fits Into The Project
```
     Embedded Wizard Chora UI (Main Thread)
        |                              ^
        | (Button Click: Connect)      | (EwInvokeCopy updates properties)
        v                              |
+-------------------------------------------------------------------------------+
|                    DeviceDriver.cpp (The Synchronization Hub)                 |
|                                                                               |
|  [GUI -> Native Commands]                 [Native -> GUI Updates]             |
|  - ChamberBridge_Connect()                - ChamberGuiSnapshot struct         |
|  - ChamberBridge_StartLogging()           - EwInvokeCopy(Callback, &snapshot) |
|  - ChamberBridge_WriteParameter()         - Calls generated Chora setters     |
+-------------------------------------------------------------------------------+
        |                              ^
        v                              | (Worker thread loop)
     C++ ChamberEngine (Worker Thread)
```

---

## 4. Implementation: `DeviceDriver.h`

Save this file at: `WindowsSimulator/Application/Source/DeviceDriver.h`:

```c
#ifndef DEVICEDRIVER_H
#define DEVICEDRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

// Snapshot structure representing all UI-bound variables
typedef struct {
    // Environmental readings
    float tempSetpoint;
    float tempActual;
    float tempRef;
    int   tempStatus; // 0=Disabled, 1=Heating, 2=Cooling

    float co2Setpoint;
    float co2Actual;

    float rhSetpoint;
    float rhActual;

    float loadCellWeight;

    // Hardware State
    int   doorLocked;
    int   socket1Active;
    int   socket2Active;

    // Lighting (0=NONE, 1=AH, 2=ICH)
    int   lightModuleType;
    int   lightChannels[5]; // AH: R,G,B | ICH: UV345, UV365, ICH, UVA, VIS

    // Diagnostics & Meta
    char  activeErrors[64];
    int   isConnected;
    int   isLogging;

    char  fwVersion[32];
    char  controllerDateTime[32];
} ChamberGuiSnapshot;

// Engine Lifecycle
void DeviceDriver_Initialize( void );
void DeviceDriver_Deinitialize( void );
int  DeviceDriver_ProcessData( void );

// GUI to Native Commands
void ChamberBridge_Connect( const char* aPortName, int aBaudRate );
void ChamberBridge_Disconnect( void );
void ChamberBridge_StartLogging( const char* aFilePath, int aIntervalSec, int aDurationSec );
void ChamberBridge_StopLogging( void );
void ChamberBridge_WriteParameter( const char* aAddressHex4, const char* aPayload );

#ifdef __cplusplus
}
#endif

#endif // DEVICEDRIVER_H
```

---

## 5. Implementation: `DeviceDriver.cpp`

Save this file at: `WindowsSimulator/Application/Source/DeviceDriver.cpp`:

```cpp
#include "DeviceDriver.h"
#include "ChamberEngine.h"
#include "Win32SerialChannel.h"
#include "ChamberProtocol.h"

// Embedded Wizard generated headers
#include "ewrte.h"
#include "Application.h"

#include <memory>
#include <string>
#include <cstring>

static std::unique_ptr<ChamberEngine> gEngine;
static std::thread gDispatcherThread;
static std::atomic<bool> gDispatcherRunning{false};

// ----------------------------------------------------------------------
// GUI Invocation Callback (Executes strictly inside the UI Main Thread)
// ----------------------------------------------------------------------
static void GuiUpdateSnapshotCallback( const void* aData )
{
    const ChamberGuiSnapshot* snap = static_cast<const ChamberGuiSnapshot*>(aData);
    if (!snap) return;

    // Fetch the Chora AutoObject instance
    ApplicationChamberDeviceClass device = EwGetAutoObject( &ApplicationChamberDevice, ApplicationChamberDeviceClass );
    if ( !device ) return;

    // Update Chora properties using EW generated accessors
    ApplicationChamberDeviceClass__UpdateTemperatures(
        device, snap->tempSetpoint, snap->tempActual, snap->tempRef, snap->tempStatus );

    ApplicationChamberDeviceClass__UpdateEnvironment(
        device, snap->co2Setpoint, snap->co2Actual, snap->rhSetpoint, snap->rhActual, snap->loadCellWeight );

    ApplicationChamberDeviceClass__UpdateHardwareIO(
        device, snap->doorLocked, snap->socket1Active, snap->socket2Active );

    ApplicationChamberDeviceClass__UpdateLighting(
        device, snap->lightModuleType,
        snap->lightChannels[0], snap->lightChannels[1], snap->lightChannels[2],
        snap->lightChannels[3], snap->lightChannels[4] );

    ApplicationChamberDeviceClass__UpdateSystemState(
        device, snap->isConnected, snap->isLogging,
        EwNewStringAnsi(snap->activeErrors),
        EwNewStringAnsi(snap->fwVersion),
        EwNewStringAnsi(snap->controllerDateTime) );
}

// ----------------------------------------------------------------------
// Periodic Dispatcher Thread: Polls engine cache & pushes to EW UI
// ----------------------------------------------------------------------
static void DispatcherLoop()
{
    while (gDispatcherRunning)
    {
        if (gEngine && gEngine->IsConnected())
        {
            ChamberLiveCache c = gEngine->GetSnapshot();
            ChamberGuiSnapshot snap = { 0 };

            snap.tempSetpoint = c.tempSetpoint;
            snap.tempActual = c.tempActual;
            snap.tempRef = c.tempRef;
            snap.tempStatus = (c.tempStatus == "HEATING") ? 1 : ((c.tempStatus == "COOLING") ? 2 : 0);

            snap.co2Setpoint = c.co2Setpoint;
            snap.co2Actual = c.co2Actual;
            snap.rhSetpoint = c.rhSetpoint;
            snap.rhActual = c.rhActual;
            snap.loadCellWeight = c.loadCellWeight;

            snap.doorLocked = c.doorLocked ? 1 : 0;
            snap.socket1Active = c.socket1Active ? 1 : 0;
            snap.socket2Active = c.socket2Active ? 1 : 0;

            if (c.lightModuleType == "AH") {
                snap.lightModuleType = 1;
                snap.lightChannels[0] = c.lightRed;
                snap.lightChannels[1] = c.lightGreen;
                snap.lightChannels[2] = c.lightBlue;
            } else if (c.lightModuleType == "ICH") {
                snap.lightModuleType = 2;
                snap.lightChannels[0] = c.lightUV345;
                snap.lightChannels[1] = c.lightUV365;
                snap.lightChannels[2] = c.lightICH;
                snap.lightChannels[3] = c.lightUVA;
                snap.lightChannels[4] = c.lightVIS;
            } else {
                snap.lightModuleType = 0;
            }

            strncpy_s(snap.activeErrors, c.activeErrors.c_str(), sizeof(snap.activeErrors) - 1);
            strncpy_s(snap.fwVersion, c.fwVersion.c_str(), sizeof(snap.fwVersion) - 1);
            strncpy_s(snap.controllerDateTime, c.controllerDateTime.c_str(), sizeof(snap.controllerDateTime) - 1);

            snap.isConnected = gEngine->IsConnected() ? 1 : 0;
            snap.isLogging = gEngine->IsLoggingActive() ? 1 : 0;

            // Schedule safe invocation in the context of the main UI thread
            EwInvokeCopy( GuiUpdateSnapshotCallback, &snap, sizeof(snap) );
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(250)); // 4 Hz UI refresh
    }
}

// ----------------------------------------------------------------------
// C Native Functions called by ewmain.c & Chora native methods
// ----------------------------------------------------------------------
extern "C" {

void DeviceDriver_Initialize( void )
{
    auto channel = std::make_unique<Win32SerialChannel>();
    auto protocol = std::make_unique<ChamberAsciiProtocol>();
    gEngine = std::make_unique<ChamberEngine>(std::move(channel), std::move(protocol));

    gDispatcherRunning = true;
    gDispatcherThread = std::thread(DispatcherLoop);
}

void DeviceDriver_Deinitialize( void )
{
    gDispatcherRunning = false;
    if (gDispatcherThread.joinable()) {
        gDispatcherThread.join();
    }
    if (gEngine) {
        gEngine->StopConnection();
        gEngine.reset();
    }
}

int DeviceDriver_ProcessData( void )
{
    return 0; // Invocations handled via EwInvokeCopy
}

void ChamberBridge_Connect( const char* aPortName, int aBaudRate )
{
    if (!gEngine) return;
    SerialConfig cfg;
    cfg.portName = (aPortName && strlen(aPortName) > 0) ? aPortName : "COM1";
    cfg.baudRate = (aBaudRate > 0) ? aBaudRate : 115200;
    cfg.dataBits = 8;
    cfg.stopBits = 1;
    cfg.parity = 0;
    cfg.hardwareFlowControl = false;

    gEngine->StartConnection(cfg);
}

void ChamberBridge_Disconnect( void )
{
    if (gEngine) {
        gEngine->StopConnection();
    }
}

void ChamberBridge_StartLogging( const char* aFilePath, int aIntervalSec, int aDurationSec )
{
    if (!gEngine) return;
    CsvLoggingConfig cfg;
    cfg.filePath = aFilePath;
    cfg.interval = static_cast<LoggingIntervalSec>(aIntervalSec);
    cfg.durationSeconds = aDurationSec;
    gEngine->StartLogging(cfg);
}

void ChamberBridge_StopLogging( void )
{
    if (gEngine) {
        gEngine->StopLogging();
    }
}

void ChamberBridge_WriteParameter( const char* aAddressHex4, const char* aPayload )
{
    if (gEngine) {
        gEngine->SendWriteCommand(aAddressHex4, aPayload);
    }
}

} // extern "C"
```

---

## 6. Verification Checklist
- [ ] `EwInvokeCopy()` is used instead of direct global struct access.
- [ ] `GuiUpdateSnapshotCallback` runs on the UI main thread and sets Chora properties via generated methods.
- [ ] Native methods in Chora (`ChamberDeviceClass`) map directly to `ChamberBridge_*` entry points.
