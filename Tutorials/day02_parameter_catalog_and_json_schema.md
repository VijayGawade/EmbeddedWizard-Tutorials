# Day 02: Parameter Catalog and JSON Schema

## 1. Stage Objective
Design and implement the complete parameter dictionary for the Environmental Chamber in a structured JSON file (`parameters.json`). Define addresses, field definitions, unit scales, numeric conversions (`divideBy: 10/100/1000`), hex indicators, and the hardware auto-detection flags for lighting modules (`NONE`, `AH`, `ICH`).

---

## 2. Why We Are Doing This Step
In typical embedded service tools, developers frequently hardcode parameter addresses (e.g. `0x2010`) and scaling factors directly into the UI buttons or parsing code. This leads to three severe issues:
1. **Firmware Drift:** If firmware changes an address, data type, or scaling factor (e.g., from tenths of a degree `x10` to hundredths `x100`), the entire GUI code must be refactored and recompiled.
2. **Maintenance Nightmare:** Adding new parameters requires adding repetitive Chora code for every sensor.
3. **No Dynamic Capabilities:** A data-driven dictionary allows the service tool to dynamically populate parameter tabs, validate user input bounds, auto-format engineering units (`°C`, `%RH`, `kg`), and dynamically detect peripheral hardware modules (such as AH vs. ICH lights).

---

## 3. How It Fits Into The Project
`parameters.json` serves as the **Single Source of Truth** for the entire project:
- The **C++ Protocol Parser** uses it to determine how many fields are expected in payload `XXXX...XXXX` and what conversions to apply.
- The **Polling Engine** uses it to determine the sequence of addresses to query every second (`2000`, `2010`, `2020`...).
- The **CSV Logger** uses it to generate column headers (`Timestamp`, `Temperature_Actual`, `CO2_Setpoint`...).
- The **Embedded Wizard UI** uses it to configure which cards and controls to display (e.g., switching the lighting dashboard between RGB vs UV/ICH based on address `2000`).

```
                    +--------------------+
                    |  parameters.json   |
                    +--------------------+
                              |
            +-----------------+-----------------+
            v                                   v
+-----------------------+           +-----------------------+
|  C++ Engine & Parser  |           |  Embedded Wizard GUI  |
|  - Address sequence   |           |  - Field names        |
|  - Data scaling       |           |  - Unit symbols       |
|  - CSV header columns |           |  - Lighting AH vs ICH |
+-----------------------+           +-----------------------+
```

---

## 4. Parameter Address Catalog

The main controller uses 4-digit hexadecimal ASCII strings for parameter addresses:

| Address (`aaaa`) | Parameter Category | Description | Access | Semicolon Fields in Payload (`XXXX`) |
|:---:|:---|:---|:---:|:---|
| `1000` | System Information | Firmware Version, Release Date, Clock | Read | `fwVersion;releaseDate;dateTime` |
| `2000` | Device Status | System State & Hardware Detection | Read | `generalStatus;tempStatus;co2Status;rhStatus;lightType` |
| `2010` | Temperature | Thermal chamber control & PID | Read/Write | `setpoint;actual;reference;kp;ki;kd;status` |
| `2020` | CO2 Gas | Carbon Dioxide control & PID | Read/Write | `setpoint;actual;reference;kp;ki;kd;status` |
| `2030` | Relative Humidity | Humidity control & PID | Read/Write | `setpoint;actual;reference;kp;ki;kd;status` |
| `2040` | Load Cell | Specimen Weight measurement | Read | `weight;tare;calibFactor;status` |
| `2050` | Hardware I/O | Door lock, AC Sockets | Read/Write | `doorLock;socket1State;socket2State;interlock` |
| `2060` | Light Module AH | Agricultural / Horticultural Lighting | Read/Write | `red;green;blue` (0–100%) |
| `2070` | Light Module ICH | Photostability Testing Lighting | Read/Write | `uv345;uv365;ich;uva;vis` (0–100%) |
| `2080` | Diagnostics | Active Error Codes & Mask | Read | `errorCount;errorCodes;errorMask` |

---

## 5. Implementation: `parameters.json`

Save this file in the root project folder: `EnvironmentalChamberServiceTool/parameters.json`:

```json
{
  "version": "1.0",
  "deviceStatusAddress": "2000",
  "parameters": [
    {
      "address": "1000",
      "name": "MainControllerInfo",
      "category": "System",
      "readOnly": true,
      "fields": [
        { "id": "fwVersion", "name": "Firmware Version", "type": "string" },
        { "id": "releaseDate", "name": "Release Date", "type": "string" },
        { "id": "dateTime", "name": "Controller Date/Time", "type": "string" }
      ]
    },
    {
      "address": "2000",
      "name": "DeviceStatus",
      "category": "Status",
      "readOnly": true,
      "fields": [
        { "id": "generalStatus", "name": "General Status", "type": "int", "isHex": true },
        { "id": "tempStatus", "name": "Temperature Status", "type": "int", "isHex": true },
        { "id": "co2Status", "name": "CO2 Status", "type": "int", "isHex": true },
        { "id": "rhStatus", "name": "RH Status", "type": "int", "isHex": true },
        { "id": "lightType", "name": "Light Module", "type": "string", "enum": ["NONE", "AH", "ICH"] }
      ]
    },
    {
      "address": "2010",
      "name": "TemperatureData",
      "category": "Temperature",
      "readOnly": false,
      "fields": [
        { "id": "setpoint", "name": "Setpoint", "type": "float", "unit": "°C", "divideBy": 10, "min": -40.0, "max": 180.0 },
        { "id": "actual", "name": "Actual", "type": "float", "unit": "°C", "divideBy": 10 },
        { "id": "reference", "name": "Reference", "type": "float", "unit": "°C", "divideBy": 10 },
        { "id": "kp", "name": "Kp", "type": "float", "divideBy": 100 },
        { "id": "ki", "name": "Ki", "type": "float", "divideBy": 100 },
        { "id": "kd", "name": "Kd", "type": "float", "divideBy": 100 },
        { "id": "status", "name": "Status", "type": "string", "enum": ["DISABLED", "HEATING", "COOLING"] }
      ]
    },
    {
      "address": "2020",
      "name": "CO2Data",
      "category": "CO2",
      "readOnly": false,
      "fields": [
        { "id": "setpoint", "name": "Setpoint", "type": "float", "unit": "%", "divideBy": 10, "min": 0.0, "max": 20.0 },
        { "id": "actual", "name": "Actual", "type": "float", "unit": "%", "divideBy": 10 },
        { "id": "reference", "name": "Reference", "type": "float", "unit": "%", "divideBy": 10 },
        { "id": "kp", "name": "Kp", "type": "float", "divideBy": 100 },
        { "id": "ki", "name": "Ki", "type": "float", "divideBy": 100 },
        { "id": "kd", "name": "Kd", "type": "float", "divideBy": 100 },
        { "id": "status", "name": "Status", "type": "string" }
      ]
    },
    {
      "address": "2030",
      "name": "RHData",
      "category": "RH",
      "readOnly": false,
      "fields": [
        { "id": "setpoint", "name": "Setpoint", "type": "float", "unit": "%RH", "divideBy": 10, "min": 10.0, "max": 98.0 },
        { "id": "actual", "name": "Actual", "type": "float", "unit": "%RH", "divideBy": 10 },
        { "id": "reference", "name": "Reference", "type": "float", "unit": "%RH", "divideBy": 10 },
        { "id": "kp", "name": "Kp", "type": "float", "divideBy": 100 },
        { "id": "ki", "name": "Ki", "type": "float", "divideBy": 100 },
        { "id": "kd", "name": "Kd", "type": "float", "divideBy": 100 },
        { "id": "status", "name": "Status", "type": "string" }
      ]
    },
    {
      "address": "2040",
      "name": "LoadCellData",
      "category": "Load Cell",
      "readOnly": true,
      "fields": [
        { "id": "weight", "name": "Weight", "type": "float", "unit": "kg", "divideBy": 1000 },
        { "id": "tare", "name": "Tare", "type": "float", "unit": "kg", "divideBy": 1000 },
        { "id": "calibFactor", "name": "Calibration Factor", "type": "float", "divideBy": 1000 },
        { "id": "status", "name": "Status", "type": "string" }
      ]
    },
    {
      "address": "2050",
      "name": "HardwareIO",
      "category": "Hardware",
      "readOnly": false,
      "fields": [
        { "id": "doorLock", "name": "Door Locked", "type": "bool" },
        { "id": "socket1State", "name": "Socket 1 Active", "type": "bool" },
        { "id": "socket2State", "name": "Socket 2 Active", "type": "bool" },
        { "id": "interlock", "name": "Safety Interlock", "type": "bool" }
      ]
    },
    {
      "address": "2060",
      "name": "LightModuleAH",
      "category": "Lights",
      "readOnly": false,
      "fields": [
        { "id": "red", "name": "Red Intensity", "type": "int", "unit": "%", "min": 0, "max": 100 },
        { "id": "green", "name": "Green Intensity", "type": "int", "unit": "%", "min": 0, "max": 100 },
        { "id": "blue", "name": "Blue Intensity", "type": "int", "unit": "%", "min": 0, "max": 100 }
      ]
    },
    {
      "address": "2070",
      "name": "LightModuleICH",
      "category": "Lights",
      "readOnly": false,
      "fields": [
        { "id": "uv345", "name": "UV345 Intensity", "type": "int", "unit": "%", "min": 0, "max": 100 },
        { "id": "uv365", "name": "UV365 Intensity", "type": "int", "unit": "%", "min": 0, "max": 100 },
        { "id": "ich", "name": "ICH Intensity", "type": "int", "unit": "%", "min": 0, "max": 100 },
        { "id": "uva", "name": "UVA Intensity", "type": "int", "unit": "%", "min": 0, "max": 100 },
        { "id": "vis", "name": "VIS Intensity", "type": "int", "unit": "%", "min": 0, "max": 100 }
      ]
    },
    {
      "address": "2080",
      "name": "ActiveErrors",
      "category": "Diagnostics",
      "readOnly": true,
      "fields": [
        { "id": "errorCount", "name": "Total Active Errors", "type": "int" },
        { "id": "errorCodes", "name": "Error Code List", "type": "string" },
        { "id": "errorMask", "name": "Error Bitmask", "type": "int", "isHex": true }
      ]
    }
  ]
}
```

---

## 6. How the C++ Backend Uses the Catalog

In C++, we can parse this file on startup using header-only `nlohmann/json.hpp`:
```cpp
void ParameterCatalog::LoadFromFile(const std::string& jsonPath) {
    std::ifstream file(jsonPath);
    nlohmann::json j;
    file >> j;

    for (const auto& item : j["parameters"]) {
        ParameterDef def;
        def.address = item["address"].get<std::string>();
        def.name = item["name"].get<std::string>();
        def.readOnly = item["readOnly"].get<bool>();
        for (const auto& f : item["fields"]) {
            FieldDef field;
            field.id = f["id"].get<std::string>();
            field.name = f["name"].get<std::string>();
            field.type = f["type"].get<std::string>();
            if (f.contains("divideBy")) field.divideBy = f["divideBy"].get<double>();
            def.fields.push_back(field);
        }
        parametersByAddress[def.address] = def;
    }
}
```

---

## 7. Verification Checklist
- [ ] `parameters.json` is saved in the project root.
- [ ] Addresses match the firmware specification (`2000`, `2010`, `2020`, etc.).
- [ ] Conversion multipliers (`divideBy: 10`, `100`, `1000`) reflect real sensor scaling.
- [ ] Light Module hardware enum options (`NONE`, `AH`, `ICH`) are clearly established.
