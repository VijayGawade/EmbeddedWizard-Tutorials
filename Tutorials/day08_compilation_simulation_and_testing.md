# Day 08: Compilation, Simulation, and Testing

## 1. Stage Objective
Bring the entire project together:
1. Generate ANSI C code from Embedded Wizard Studio 15.
2. Configure and compile the Visual Studio 2022 solution (`x64`).
3. Build a Python loopback **Virtual Chamber Simulator** to test the service tool without needing physical hardware.
4. Verify end-to-end functionality (RS485 polling, dynamic lighting detection, CSV logging intervals).

---

## 2. Why We Are Doing This Step
Hardware is rarely available during early desktop service tool development:
- Waiting for physical environmental chambers creates development bottlenecks.
- Developing against a software simulator allows testing boundary cases: CRC errors (`?0`), unknown parameters (`?1`), disconnects, and rapid lighting module swapping (`AH` $\leftrightarrow$ `ICH`).
- Verifying the build pipeline in Visual Studio 2022 ensures that all C++17 dependencies, include paths, and Windows SDK libraries link cleanly into a standalone `.exe`.

---

## 3. How It Fits Into The Project
```
+------------------------------------------+
|  Embedded Wizard Studio 15               |
|  - Press F8 -> Generates C source files  |
+------------------------------------------+
                     |
                     v
+-------------------------------------------------------------+
|  Visual Studio 2022 (MSVC v143, x64)                        |
|  - Compiles:                                                |
|     * GeneratedCode/ (Application.c, Core.c, Views.c...)    |
|     * Source/ (DeviceDriver.cpp, ChamberEngine.cpp...)      |
|  - Output: EnvironmentalChamberServiceTool.exe              |
+-------------------------------------------------------------+
                     ^
                     | (Virtual Serial Pair via com0com, e.g. COM11 <-> COM12)
                     v
+-------------------------------------------------------------+
|  Python Virtual Chamber Simulator (virtual_chamber.py)      |
|  - Listens on COM11                                         |
|  - Emulates PID loops, temperatures, light modules, CRC8    |
+-------------------------------------------------------------+
```

---

## 4. Visual Studio 2022 Project Configuration

1. Open `WindowsSimulator/Application/Project/MSVC/EmbeddedWizard-Windows.sln` in **Visual Studio 2022**.
2. Set configuration to **Release** and platform to **x64**.
3. In Solution Explorer, right-click the project $\to$ **Properties**:
   * **C/C++ $\to$ Language $\to$ C++ Language Standard:** Set to **ISO C++17 Standard (`/std:c++17`)**.
   * **C/C++ $\to$ General $\to$ Additional Include Directories:** Ensure the following paths are present:
     ```
     ..\..\Source
     ..\..\GeneratedCode
     ..\..\..\PlatformPackage\RTE
     ..\..\..\PlatformPackage\RGBA8888
     ..\..\..\TargetSpecific
     ```
4. Right-click the **Source Files** filter in Solution Explorer $\to$ **Add $\to$ Existing Item**, and add:
   * `DeviceDriver.cpp`
   * `ChamberEngine.cpp`
5. Right-click the **Header Files** filter $\to$ **Add $\to$ Existing Item**, and add:
   * `DeviceDriver.h`
   * `ChamberEngine.h`
   * `ChamberProtocol.h`
   * `Crc8.h`
   * `ICommChannel.h`
   * `Win32SerialChannel.h`

---

## 5. Implementation: Virtual Chamber Simulator (`virtual_chamber.py`)

Save this test script in the project root as `virtual_chamber.py`. It uses `pyserial` to emulate the chamber firmware:

```python
"""
Virtual Environmental Chamber Simulator
Emulates RS485 communication, CRC-8 (poly 0x07), and dynamic light modules.
"""

import serial
import time
import sys

def calc_crc8(data_bytes: bytes) -> int:
    crc = 0x00
    for byte in data_bytes:
        crc ^= byte
        for _ in range(8):
            if crc & 0x80:
                crc = ((crc << 1) ^ 0x07) & 0xFF
            else:
                crc = (crc << 1) & 0xFF
    return crc

def build_response(address: str, payload: str) -> bytes:
    bb = f"{len(payload):02X}"
    covered = f"!:{address}:{bb}:{payload}:"
    crc = calc_crc8(covered.encode('ascii'))
    crc_hex = f"{crc:02X}"
    # Form: !:aaaa:bb:XXXX:CC:\r
    return f"{covered}{crc_hex}:\r".encode('ascii')

def main():
    port = sys.argv[1] if len(sys.argv) > 1 else "COM11"
    print(f"[*] Starting Virtual Chamber Simulator on {port} (115200 8N1)...")

    try:
        ser = serial.Serial(port, 115200, timeout=0.1)
    except Exception as e:
        print(f"[!] Error opening serial port: {e}")
        print("Tip: Install com0com to create a virtual COM pair (e.g. COM11 <-> COM12).")
        return

    # Simulated Chamber State
    light_module = "ICH" # Toggle between "AH", "ICH", or "NONE"
    temp_actual = 24.5
    temp_setpoint = 25.0
    co2_actual = 4.9
    rh_actual = 60.2
    weight = 15.350

    rx_buffer = ""

    while True:
        data = ser.read(64)
        if data:
            rx_buffer += data.decode('ascii', errors='ignore')

            while '\r' in rx_buffer:
                line, rx_buffer = rx_buffer.split('\r', 1)
                line = line.strip()
                if not line:
                    continue

                print(f"[RX] {line}")
                tokens = line.split(':')
                if len(tokens) >= 3 and tokens[0] == '?':
                    addr = tokens[1]
                    resp = b""

                    if addr == "1000":
                        resp = build_response("1000", "v3.2.14;2026-10-08;2026-10-08 18:42:00")
                    elif addr == "2000":
                        # Status: generalStatus;tempStatus;co2Status;rhStatus;lightType
                        resp = build_response("2000", f"0;1;1;1;{light_module}")
                    elif addr == "2010":
                        # Temp: setpoint;actual;reference;kp;ki;kd;status
                        temp_actual += 0.05 if temp_actual < temp_setpoint else -0.05
                        resp = build_response("2010", f"{temp_setpoint:.1f};{temp_actual:.1f};25.0;10;5;2;HEATING")
                    elif addr == "2020":
                        resp = build_response("2020", f"5.0;{co2_actual:.1f};5.0;15;5;0;STABLE")
                    elif addr == "2030":
                        resp = build_response("2030", f"60.0;{rh_actual:.1f};60.0;20;10;0;HUMIDIFYING")
                    elif addr == "2040":
                        resp = build_response("2040", f"{weight:.3f};0.000;1000;OK")
                    elif addr == "2050":
                        resp = build_response("2050", "1;1;0;1") # Door locked, Socket1 ON
                    elif addr == "2060" and light_module == "AH":
                        resp = build_response("2060", "80;60;100") # Red, Green, Blue
                    elif addr == "2070" and light_module == "ICH":
                        resp = build_response("2070", "85;90;70;60;100") # UV345, UV365, ICH, UVA, VIS
                    elif addr == "2080":
                        resp = build_response("2080", "0;None;0000")

                    if resp:
                        time.sleep(0.01) # 10ms hardware turn-around
                        ser.write(resp)
                        print(f"[TX] {resp.decode('ascii').strip()}")

        time.sleep(0.01)

if __name__ == "__main__":
    main()
```

---

## 6. End-to-End Verification Procedure

1. **Setup Virtual Ports:**
   * Using **com0com** (or a dual-port USB-to-RS485 adapter with crossed TX/RX lines), create a paired connection: `COM11` $\leftrightarrow$ `COM12`.
2. **Start the Chamber Simulator:**
   ```bash
   python virtual_chamber.py COM11
   ```
3. **Launch the Service Tool:**
   * In Visual Studio 2022, press **F5** (or run `EmbeddedWizard-Windows-x64.exe`).
4. **Connect:**
   * Go to the **Comm Setup** tab.
   * Select `COM12`, Baud `115200`. Click **Connect**.
5. **Verify Live Monitoring:**
   * Observe the **Main Tab**: Software version `v3.2.14` and Date/Time should appear.
   * Observe the **Monitoring Tab**: Dials for Temperature, CO2, RH, and Load Cell update in real-time.
   * Observe the **Lighting Panel**: It should automatically render the 5 sliders for the **ICH module** (UV345, UV365, ICH, UVA, VIS).
6. **Verify CSV Logging:**
   * Click **Start CSV Logging...**.
   * Set destination to `C:\TestLog.csv`, select interval **5s**, and check desired parameters.
   * Click **Start Recording**. Let it run for 30 seconds, then click **Stop Logging**.
   * Open `C:\TestLog.csv` in Excel or Notepad and verify timestamped rows recorded at exactly 5-second intervals.

---

## 7. Troubleshooting & Debugging

| Symptom | Probable Cause | Solution |
|:---|:---|:---|
| **Build error: Unresolved external symbol `ChamberBridge_*`** | `DeviceDriver.cpp` missing from project | Ensure `DeviceDriver.cpp` is added under Source Files in Visual Studio. |
| **All received packets report CRC error (`?0`)** | CRC polynomial or covered slice mismatch | Check `Crc8.h`. Ensure CRC is computed up to the colon before the CRC string. |
| **COM port cannot be opened** | Another program has exclusive handle | Close serial terminals (Putty, RealTerm, or older simulator instances). |
| **UI freezes for ~1 second periodically** | Blocking serial call executed inside Chora | Ensure all `ReadFile` and serial queries execute strictly in `ChamberEngine`'s worker thread. |
| **Light sliders do not appear** | Address `2000` returned unknown light type string | Verify simulator returns exact token `AH` or `ICH` as the 5th field in packet `2000`. |
