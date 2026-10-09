# Day 04: Custom Protocol Engine and CRC-8

## 1. Stage Objective
Implement the custom ASCII communication protocol used by the environmental chamber's main controller. Write the exact CRC-8 calculation engine (polynomial `0x07`), serialize read/write requests, and parse both successful responses and error NACK packets (`?0`, `?1`, `?2`, `?3`).

---

## 2. Why We Are Doing This Step
Requirement 2 specifies:
> - Read: `?:aaaa:bb:CC<CR>` $\to$ `!:aaaa:bb:XXXX...XXX:CC:<CR>`
> - Write: `!:aaaa:bb:XXXX...XXXX:CC<CR>` $\to$ `!:aaaa:bb::CC<CR>`
> - Polynomial: `0x07`, CRC includes all characters except `CC<CR>`, `CC` is ASCII hex.
> - Error/NACK: `!:aaaa:bb:[?0/?1/?2/?3]:CC<CR>` (0: checksum, 1: unknown param, 2: internal error, 3: data error).

In serial industrial communications (RS485), line noise, reflections, and transient glitches can corrupt individual bytes. 
- **CRC-8** guarantees that corrupted packets are rejected before invalid numbers reach the PID controller or UI.
- Abstracting this behind an **`IProtocolHandler`** interface allows future protocols (such as Modbus RTU or CANopen) to be integrated without modifying the service tool's business logic.

---

## 3. How It Fits Into The Project
```
       +---------------------------------------------+
       |   ChamberEngine (1 Hz Polling & Logging)    |
       +---------------------------------------------+
                              |
                              v
       +---------------------------------------------+
       |            << IProtocolHandler >>           |
       |  + FormatRead(address)                      |
       |  + FormatWrite(address, payload)            |
       |  + ParseResponse(rawFrame, outPacket)       |
       +---------------------------------------------+
                              |
                              v
       +---------------------------------------------+
       |         ChamberAsciiProtocol (C++)          |
       |  - Calculates CRC8 (Poly 0x07)              |
       |  - Validates trailing colons & delimiters   |
       |  - Splits semicolon tokens in XXXX payload  |
       |  - Decodes NACK codes ?0, ?1, ?2, ?3        |
       +---------------------------------------------+
```

---

## 4. Implementation: `Crc8.h`

Save this file at: `WindowsSimulator/Application/Source/Crc8.h`:

```cpp
#pragma once
#include <cstdint>
#include <string>
#include <sstream>
#include <iomanip>

/**
 * CRC-8 implementation for Environmental Chamber Protocol
 * Polynomial: 0x07 (x^8 + x^2 + x + 1)
 * Initial Value: 0x00
 */
class Crc8 {
public:
    static uint8_t Calculate(const uint8_t* buffer, size_t length) {
        uint8_t crc = 0x00;
        for (size_t i = 0; i < length; ++i) {
            crc ^= buffer[i];
            for (int bit = 0; bit < 8; ++bit) {
                if (crc & 0x80) {
                    crc = (crc << 1) ^ 0x07;
                } else {
                    crc <<= 1;
                }
            }
        }
        return crc;
    }

    static uint8_t Calculate(const std::string& str) {
        return Calculate(reinterpret_cast<const uint8_t*>(str.data()), str.size());
    }

    // Formats byte as 2-character uppercase hexadecimal string
    static std::string ToHex(uint8_t crc) {
        std::stringstream ss;
        ss << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(crc);
        return ss.str();
    }
};
```

---

## 5. Implementation: `ChamberProtocol.h`

Save this file at: `WindowsSimulator/Application/Source/ChamberProtocol.h`:

```cpp
#pragma once
#include "Crc8.h"
#include <string>
#include <vector>
#include <optional>
#include <sstream>

enum class ProtocolNackCode {
    None = -1,
    ChecksumError = 0,    // ?0
    UnknownParameter = 1, // ?1
    InternalError = 2,    // ?2
    DataError = 3         // ?3
};

struct ChamberPacket {
    bool isSuccess = false;
    ProtocolNackCode nackCode = ProtocolNackCode::None;
    std::string address;                // 4-digit hex, e.g. "2010"
    uint8_t byteCount = 0;              // Decoded from "bb"
    std::string rawPayload;             // "XXXX...XXXX"
    std::vector<std::string> fields;    // Payload split by ';'
};

class IProtocolHandler {
public:
    virtual ~IProtocolHandler() = default;
    virtual std::string BuildReadRequest(const std::string& addressHex4) = 0;
    virtual std::string BuildWriteRequest(const std::string& addressHex4, const std::string& payload) = 0;
    virtual std::optional<ChamberPacket> ParseIncomingFrame(const std::string& rawFrame) = 0;
};

class ChamberAsciiProtocol : public IProtocolHandler {
public:
    // Build: ?:aaaa:bb:CC<CR>
    // For Read Request, byte count is 00
    std::string BuildReadRequest(const std::string& addressHex4) override {
        std::string frameWithoutCrc = "?:" + addressHex4 + ":00:";
        uint8_t crc = Crc8::Calculate(frameWithoutCrc);
        return frameWithoutCrc + Crc8::ToHex(crc) + "\r";
    }

    // Build: !:aaaa:bb:XXXX...XXXX:CC<CR>
    std::string BuildWriteRequest(const std::string& addressHex4, const std::string& payload) override {
        std::stringstream bbStream;
        bbStream << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << payload.size();

        std::string frameWithoutCrc = "!:" + addressHex4 + ":" + bbStream.str() + ":" + payload + ":";
        uint8_t crc = Crc8::Calculate(frameWithoutCrc);
        return frameWithoutCrc + Crc8::ToHex(crc) + "\r";
    }

    // Parse Response: !:aaaa:bb:XXXX...XXX:CC:<CR> or !:aaaa:bb::CC<CR> or !:aaaa:bb:?N:CC<CR>
    std::optional<ChamberPacket> ParseIncomingFrame(const std::string& rawFrame) override {
        if (rawFrame.empty() || rawFrame.front() != '!' || rawFrame.back() != '\r') {
            return std::nullopt;
        }

        // Remove <CR>
        std::string frame = rawFrame.substr(0, rawFrame.size() - 1);

        // Find the CRC field
        // Some responses end with ":CC:" before CR, others end with ":CC"
        size_t lastColon = frame.rfind(':');
        if (lastColon == std::string::npos) return std::nullopt;

        std::string receivedCrcStr;
        std::string coveredPart;

        if (lastColon == frame.size() - 1) {
            // Case: ends with trailing colon ":CC:"
            size_t secondLastColon = frame.rfind(':', lastColon - 1);
            if (secondLastColon == std::string::npos) return std::nullopt;
            receivedCrcStr = frame.substr(secondLastColon + 1, lastColon - secondLastColon - 1);
            coveredPart = frame.substr(0, secondLastColon + 1);
        } else {
            // Case: ends with ":CC"
            receivedCrcStr = frame.substr(lastColon + 1);
            coveredPart = frame.substr(0, lastColon + 1);
        }

        // Verify CRC8 over covered portion
        uint8_t expectedCrc = Crc8::Calculate(coveredPart);
        if (Crc8::ToHex(expectedCrc) != receivedCrcStr) {
            ChamberPacket badCrc;
            badCrc.isSuccess = false;
            badCrc.nackCode = ProtocolNackCode::ChecksumError;
            return badCrc;
        }

        // Split covered part: "!", "aaaa", "bb", "XXXX...XXXX"
        std::stringstream ss(coveredPart);
        std::string segment;
        std::vector<std::string> tokens;
        while (std::getline(ss, segment, ':')) {
            tokens.push_back(segment);
        }

        if (tokens.size() < 3) return std::nullopt;

        ChamberPacket packet;
        packet.address = tokens[1];
        packet.byteCount = static_cast<uint8_t>(std::stoul(tokens[2], nullptr, 16));

        // If there is payload content
        if (tokens.size() >= 4) {
            packet.rawPayload = tokens[3];
        }

        // Check for error NACK: ?0, ?1, ?2, ?3
        if (packet.rawPayload.rfind("?", 0) == 0 && packet.rawPayload.size() >= 2) {
            packet.isSuccess = false;
            int code = packet.rawPayload[1] - '0';
            packet.nackCode = static_cast<ProtocolNackCode>(code);
            return packet;
        }

        // Successful response
        packet.isSuccess = true;
        std::stringstream pss(packet.rawPayload);
        std::string val;
        while (std::getline(pss, val, ';')) {
            packet.fields.push_back(val);
        }

        return packet;
    }
};
```

---

## 6. Verification Checklist & Unit Test

Create a quick unit test in `WindowsSimulator/Application/Source/test_protocol.cpp` to verify:

```cpp
#include "ChamberProtocol.h"
#include <cassert>
#include <iostream>

void TestProtocol() {
    ChamberAsciiProtocol proto;

    // 1. Test Read Request Generation
    std::string req = proto.BuildReadRequest("2010");
    std::cout << "Generated Read Req: " << req << std::endl;
    assert(req.rfind("?:2010:00:", 0) == 0);
    assert(req.back() == '\r');

    // 2. Test Success Response Parsing
    // Frame: !:2010:14:25.0;24.8;25.0;10;5;2;HEATING:<CRC>:\r
    std::string covered = "!:2010:14:25.0;24.8;25.0;10;5;2;HEATING:";
    std::string crc = Crc8::ToHex(Crc8::Calculate(covered));
    std::string sampleResp = covered + crc + ":\r";

    auto parsed = proto.ParseIncomingFrame(sampleResp);
    assert(parsed.has_value());
    assert(parsed->isSuccess == true);
    assert(parsed->address == "2010");
    assert(parsed->fields.size() == 7);
    assert(parsed->fields[0] == "25.0"); // Setpoint
    assert(parsed->fields[1] == "24.8"); // Actual
    assert(parsed->fields[6] == "HEATING"); // Status

    // 3. Test NACK Response Parsing
    // Frame: !:2010:02:?1:<CRC>\r (Unknown parameter)
    std::string nackCovered = "!:2010:02:?1:";
    std::string nackCrc = Crc8::ToHex(Crc8::Calculate(nackCovered));
    std::string nackResp = nackCovered + nackCrc + "\r";

    auto nackParsed = proto.ParseIncomingFrame(nackResp);
    assert(nackParsed.has_value());
    assert(nackParsed->isSuccess == false);
    assert(nackParsed->nackCode == ProtocolNackCode::UnknownParameter);

    std::cout << "All Protocol & CRC8 tests passed successfully!" << std::endl;
}
```
- [ ] Read requests end with `\r` and include valid CRC-8.
- [ ] Payload semicolon splitting parses all sensor values cleanly.
- [ ] NACK error codes (`?0`, `?1`, `?2`, `?3`) are identified and handled.
