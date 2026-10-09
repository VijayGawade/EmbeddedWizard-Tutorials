# Day 07: Embedded Wizard UI Implementation in Chora

## 1. Stage Objective
Build the graphical user interface in Embedded Wizard Studio 15 using Chora and the Mosaic framework. Implement the `MainTab`, `CommSetupDialog`, `MonitoringTab` (with dynamic AH vs. ICH lighting panel), `CsvConfigModal`, and the `ParametersTab`.

---

## 2. Why We Are Doing This Step
The user interface represents the final product seen by field service engineers:
- **Responsive Telemetry:** Live sensor dials, status pills, and charts must reflect actual chamber states at 1-second intervals without flicker or delay.
- **Dynamic Adaptability:** Environmental chambers can be fitted with either agricultural/horticultural light bars (**AH**: Red, Green, Blue) or photostability testing modules (**ICH**: UV345, UV365, ICH, UVA, VIS). Hardcoding static controls would confuse users. The UI must inspect parameter `2000` and automatically reconfigure the controls on screen.
- **Operator Safety:** Clear confirmation dialogs for CSV recording and parameter write operations prevent accidental setpoint modifications.

---

## 3. How It Fits Into The Project
```
+-------------------------------------------------------------------------------+
|                        Application::Application (Root)                        |
|                                                                               |
|   +-----------------------------------------------------------------------+   |
|   | Header: Title | Connection Status Pill | Controller Time | Close      |   |
|   +-----------------------------------------------------------------------+   |
|   | Navigation Bar: [Main]  [Comm Setup]  [Monitoring]  [Parameters]      |   |
|   +-----------------------------------------------------------------------+   |
|   | Content Area (Switched dynamically):                                  |   |
|   |  - Application::MainTab                                               |   |
|   |  - Application::CommSetupDialog                                       |   |
|   |  - Application::MonitoringTab                                         |   |
|   |     +-- AH Light Component (Red, Green, Blue)                         |   |
|   |     +-- ICH Light Component (UV345, UV365, ICH, UVA, VIS)             |   |
|   |     +-- Application::CsvConfigModal                                   |   |
|   |  - Application::ParametersTab                                         |   |
|   +-----------------------------------------------------------------------+   |
+-------------------------------------------------------------------------------+
                                        | Observes
                                        v
                    Application::ChamberDevice (AutoObject)
```

---

## 4. Chora Implementation: `Application::ChamberDeviceClass`

Open `Application.ewu` in Embedded Wizard Studio and define the `ChamberDeviceClass`:

```chora
// ==============================================================================
// Class: Application::ChamberDeviceClass
// Description: Singleton bridge object mediating between GUI and C++ Engine
// ==============================================================================
class ChamberDeviceClass : Core::Resource
{
  // ----------------------------------------------------------------------------
  // Properties
  // ----------------------------------------------------------------------------
  property bool IsConnected = false;
  property bool IsLogging = false;

  // 0: None, 1: AH (RGB), 2: ICH (UV/VIS)
  property int32 LightModuleType = 0;

  property float TempSetpoint = 0.0;
  property float TempActual = 0.0;
  property float TempRef = 0.0;
  property int32 TempStatus = 0; // 0=Disabled, 1=Heating, 2=Cooling

  property float CO2Setpoint = 0.0;
  property float CO2Actual = 0.0;

  property float RHSetpoint = 0.0;
  property float RHActual = 0.0;

  property float LoadCellWeight = 0.0;

  property bool DoorLocked = false;
  property bool Socket1Active = false;
  property bool Socket2Active = false;

  property int32 LightCh0 = 0;
  property int32 LightCh1 = 0;
  property int32 LightCh2 = 0;
  property int32 LightCh3 = 0;
  property int32 LightCh4 = 0;

  property string ActiveErrors = "None";
  property string FwVersion = "N/A";
  property string ControllerDateTime = "--:--:--";

  // ----------------------------------------------------------------------------
  // Upstream Methods (called by DeviceDriver.cpp via EwInvokeCopy)
  // ----------------------------------------------------------------------------
  method void UpdateTemperatures( arg float aSp, arg float aAct, arg float aRef, arg int32 aStat )
  {
    TempSetpoint = aSp;
    TempActual   = aAct;
    TempRef      = aRef;
    TempStatus   = aStat;
  }

  method void UpdateEnvironment( arg float aCo2Sp, arg float aCo2Act, arg float aRhSp, arg float aRhAct, arg float aWeight )
  {
    CO2Setpoint    = aCo2Sp;
    CO2Actual      = aCo2Act;
    RHSetpoint     = aRhSp;
    RHActual       = aRhAct;
    LoadCellWeight = aWeight;
  }

  method void UpdateHardwareIO( arg int32 aDoor, arg int32 aSock1, arg int32 aSock2 )
  {
    DoorLocked    = ( aDoor != 0 );
    Socket1Active = ( aSock1 != 0 );
    Socket2Active = ( aSock2 != 0 );
  }

  method void UpdateLighting( arg int32 aType, arg int32 aC0, arg int32 aC1, arg int32 aC2, arg int32 aC3, arg int32 aC4 )
  {
    LightModuleType = aType;
    LightCh0 = aC0;
    LightCh1 = aC1;
    LightCh2 = aC2;
    LightCh3 = aC3;
    LightCh4 = aC4;
  }

  method void UpdateSystemState( arg int32 aConn, arg int32 aLog, arg string aErr, arg string aFw, arg string aDt )
  {
    IsConnected        = ( aConn != 0 );
    IsLogging          = ( aLog != 0 );
    ActiveErrors       = aErr;
    FwVersion          = aFw;
    ControllerDateTime = aDt;
  }

  // ----------------------------------------------------------------------------
  // Downstream Commands (called by UI buttons -> C++ engine)
  // ----------------------------------------------------------------------------
  method void Connect( arg string aPort, arg int32 aBaud )
  {
    native ( aPort, aBaud )
    {
      ChamberBridge_Connect( EwStringToAnsi( aPort ), aBaud );
    }
  }

  method void Disconnect()
  {
    native
    {
      ChamberBridge_Disconnect();
    }
  }

  method void StartLogging( arg string aPath, arg int32 aIntervalSec, arg int32 aDurationSec )
  {
    native ( aPath, aIntervalSec, aDurationSec )
    {
      ChamberBridge_StartLogging( EwStringToAnsi( aPath ), aIntervalSec, aDurationSec );
    }
  }

  method void StopLogging()
  {
    native
    {
      ChamberBridge_StopLogging();
    }
  }

  method void WriteParameter( arg string aAddr, arg string aPayload )
  {
    native ( aAddr, aPayload )
    {
      ChamberBridge_WriteParameter( EwStringToAnsi( aAddr ), EwStringToAnsi( aPayload ) );
    }
  }
}
```

Create an **AutoObject** in `Application` named `ChamberDevice` of type `Application::ChamberDeviceClass`.

---

## 5. UI Views Implementation

### A. Main Tab (`Application::MainTab`)
Displays software versions and system status:
```chora
// In MainTab::OnUpdate / PropertyObserver on ChamberDevice
TextAppVersion.String  = "App Version: v1.0.0 (Release: 2026-10-08)";
TextFwVersion.String   = "Main Controller FW: " + Application::ChamberDevice.FwVersion;
TextControllerDT.String = "Controller Time: " + Application::ChamberDevice.ControllerDateTime;

if ( Application::ChamberDevice.IsConnected )
{
  PillStatus.Color = #00CC66FF; // Green
  PillStatusText.String = "CONNECTED (RS485)";
}
else
{
  PillStatus.Color = #CC0000FF; // Red
  PillStatusText.String = "DISCONNECTED";
}
```

### B. Comm Setup Dialog (`Application::CommSetupDialog`)
Provides controls for port selection, baud rate, and bus type:
```chora
// Slot method: OnConnectButtonClicked
if ( !Application::ChamberDevice.IsConnected )
{
  var string selectedPort = DropdownPort.SelectedItemText; // e.g. "COM3"
  var int32  selectedBaud = (int32)DropdownBaud.SelectedItemText; // e.g. 115200
  Application::ChamberDevice.Connect( selectedPort, selectedBaud );
}
else
{
  Application::ChamberDevice.Disconnect();
}
```

### C. Monitoring Tab with Dynamic Light Panel (`Application::MonitoringTab`)
Reactively binds sensor values and adapts the lighting controls:

```chora
// Slot method observing Application::ChamberDevice.LightModuleType
slot OnLightModuleChanged
{
  switch ( Application::ChamberDevice.LightModuleType )
  {
    case 1: // AH Module (Agricultural / Horticultural)
    {
      PanelAhLights.Visible  = true;
      PanelIchLights.Visible = false;
      TextNoLights.Visible   = false;
      
      SliderRed.Value   = Application::ChamberDevice.LightCh0;
      SliderGreen.Value = Application::ChamberDevice.LightCh1;
      SliderBlue.Value  = Application::ChamberDevice.LightCh2;
    }
    case 2: // ICH Module (Photostability testing)
    {
      PanelAhLights.Visible  = false;
      PanelIchLights.Visible = true;
      TextNoLights.Visible   = false;
      
      SliderUV345.Value = Application::ChamberDevice.LightCh0;
      SliderUV365.Value = Application::ChamberDevice.LightCh1;
      SliderICH.Value   = Application::ChamberDevice.LightCh2;
      SliderUVA.Value   = Application::ChamberDevice.LightCh3;
      SliderVIS.Value   = Application::ChamberDevice.LightCh4;
    }
    default: // No Light module detected
    {
      PanelAhLights.Visible  = false;
      PanelIchLights.Visible = false;
      TextNoLights.Visible   = true;
      TextNoLights.String    = "No Lighting Module Connected";
    }
  }
}
```

### D. CSV Setup Modal Dialog (`Application::CsvConfigModal`)
Modal window opened when the user clicks **Start CSV Logging...**:

```chora
// Slot method: OnConfirmStartLogging
slot OnConfirmStartLogging
{
  var string filePath = EditFilePath.String;
  if ( filePath == "" )
    filePath = "C:\\ChamberLogs\\chamber_log.csv";

  // Map dropdown selection to interval in seconds (1, 5, 30, 60, 120, 300)
  var int32 intervalSec = 1;
  switch ( DropdownInterval.SelectedIndex )
  {
    case 0: intervalSec = 1;
    case 1: intervalSec = 5;
    case 2: intervalSec = 30;
    case 3: intervalSec = 60;
    case 4: intervalSec = 120;
    case 5: intervalSec = 300;
  }

  var int32 durationSec = 0; // 0 = continuous
  if ( CheckboxLimitDuration.Checked )
    durationSec = (int32)EditDurationMinutes.String * 60;

  // Dispatch command to C++
  Application::ChamberDevice.StartLogging( filePath, intervalSec, durationSec );

  // Close modal dialog
  this.Dismiss();
}
```

---

## 6. Verification Checklist
- [ ] `ChamberDeviceClass` contains all properties matching `ChamberGuiSnapshot`.
- [ ] Dials and numeric displays update smoothly when simulator data is injected.
- [ ] Toggling `LightModuleType` between `0`, `1`, and `2` correctly hides and shows the AH vs ICH panels.
- [ ] CSV Modal provides all interval options (1s, 5s, 30s, 60s, 120s, 300s).
