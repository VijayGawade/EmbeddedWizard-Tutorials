# Environmental Chamber Service Tool - Tutorial Series

Comprehensive, day-by-day developer guide to building a production-grade Windows Desktop Service Tool using **Embedded Wizard Studio 15**, **Visual Studio 2022 (MSVC C++17)**, and **Win32 RS485 Communication**.

---

## Curriculum Overview

Every tutorial module explains:
1. **The Objective:** What will be built in this stage.
2. **Why We Are Doing This Step:** Engineering rationale, performance, and maintainability considerations.
3. **How It Fits Into The Project:** Architectural context and integration with preceding/following layers.
4. **Concrete Implementation:** Full source code, Chora scripts, JSON schemas, or configuration files.
5. **Verification & Testing Checklist:** Steps to validate before moving to the next day.

---

## Daily Modules

| Day | Document | Focus Area | Key Deliverables |
|:---:|:---|:---|:---|
| **Day 01** | [`day01_system_architecture_and_setup.md`](./day01_system_architecture_and_setup.md) | Architecture & Environment | Win32 Platform Package, Studio 15 setup, Project layout, Threading rules |
| **Day 02** | [`day02_parameter_catalog_and_json_schema.md`](./day02_parameter_catalog_and_json_schema.md) | Parameter Data Model | `parameters.json` schema, Addresses (2000–2080, 1000), Scaling & Types |
| **Day 03** | [`day03_communication_layer_and_win32_rs485.md`](./day03_communication_layer_and_win32_rs485.md) | Hardware Abstraction | `ICommChannel` interface, `Win32SerialChannel` (RS485 Full Duplex) |
| **Day 04** | [`day04_custom_protocol_and_crc8.md`](./day04_custom_protocol_and_crc8.md) | Custom Protocol & CRC8 | CRC-8 (`0x07`), Request/Response framing, NACK parser (`?0`..`?3`) |
| **Day 05** | [`day05_polling_engine_and_csv_logger.md`](./day05_polling_engine_and_csv_logger.md) | Polling & CSV Logging | 1 Hz background polling loop, Configurable intervals (1s–300s), CSV engine |
| **Day 06** | [`day06_device_driver_bridge_and_ewinvoke.md`](./day06_device_driver_bridge_and_ewinvoke.md) | EW Native Bridge | `DeviceDriver.cpp`, `EwInvokeCopy` thread synchronization, Snapshot struct |
| **Day 07** | [`day07_embedded_wizard_ui_implementation.md`](./day07_embedded_wizard_ui_implementation.md) | Chora GUI Development | Main Tab, Setup Dialog, Monitoring Tab (AH/ICH dynamic light), CSV Modal |
| **Day 08** | [`day08_compilation_simulation_and_testing.md`](./day08_compilation_simulation_and_testing.md) | Build, Test & Deploy | Code generation (F8), VS 2022 build, Virtual loopback chamber simulator |

---

## Project Prerequisites

- **Embedded Wizard Studio 15** (Professional or Evaluation with Windows Platform Package)
- **Microsoft Visual Studio 2022** (Desktop development with C++, MSVC v143, Windows 10/11 SDK)
- **USB-to-RS485 Adapter** (or virtual serial pair like `com0com` for testing)
