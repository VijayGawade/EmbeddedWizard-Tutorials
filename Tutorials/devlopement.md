Here is the complete, copy-paste-ready project source code and step-by-step setup guide to build and run the multi-protocol Master Controller application on your Windows machine using the [Embedded Wizard Windows Build Environment](https://doc.embedded-wizard.de/getting-started-win32) and Microsoft Visual Studio (MSVC).

### Step 1: Set Up the Folder Structure on Your Windows Machine

1. **Install Prerequisites**: Install **Embedded Wizard Studio** (Free or Professional Edition) and **Microsoft Visual Studio** (2019 or 2022) with the **Desktop development with C++** workload enabled.
2. **Extract the Build Environment**: Unpack the [Embedded Wizard Windows Build Environment](https://doc.embedded-wizard.de/getting-started-win32) (`Windows-BuildEnvironment-V15.00.00.01.zip` or your installed version) into `C:\EW_MasterApp\`.
3. **Verify the Project Tree**: Place the C/C++ source files from Step 2 inside `C:\EW_MasterApp\Application\Source\` and your Embedded Wizard project from Step 3 inside `C:\EW_MasterApp\Application\MasterGUI\`:

| Path on Your Machine | File Name | Purpose |
| --- | --- | --- |
| `C:\EW_MasterApp\Application\Source\protocol_codec.h` | `protocol_codec.h` | Declarations for **Packet Format 1** (ASCII + CRC-8) and **Packet Format 2** (29-bit TF CAN) |
| `C:\EW_MasterApp\Application\Source\protocol_codec.c` | `protocol_codec.c` | CRC-8 calculator, Format 1 encoder/decoder, and 29-bit CAN ID bitpacker/unpacker |
| `C:\EW_MasterApp\Application\Source\transport_manager.h` | `transport_manager.h` | Thread-safe C API called by Embedded Wizard `DeviceClass` and `DeviceDriver.c` |
| `C:\EW_MasterApp\Application\Source\transport_manager.cpp` | `transport_manager.cpp` | Windows drivers for `RS232`, `RS485_FullDuplex`, `CAN`, and `RestAPI` + RX worker thread |
| `C:\EW_MasterApp\Application\Source\DeviceDriver.h` | `DeviceDriver.h` | Header bridge invoked by Embedded Wizard's `ewmain.c` loop |
| `C:\EW_MasterApp\Application\Source\DeviceDriver.c` | `DeviceDriver.c` | Drains the RX queue on the GUI thread and updates `Application::Device` |
| `C:\EW_MasterApp\Application\MasterGUI\MasterController.ewp` | `MasterController.ewp` | Embedded Wizard Studio GUI project and `Application::DeviceClass` definition |
| `C:\EW_MasterApp\slave_simulator.py` | `slave_simulator.py` | Local Python Slave Controller simulator for testing HTTP REST and Serial/CAN frames |

### Step 2: Create the C/C++ Source Files in `C:\EW_MasterApp\Application\Source\`

#### 2.1 `C:\EW_MasterApp\Application\Source\protocol_codec.h`

```c
#ifndef PROTOCOL_CODEC_H
#define PROTOCOL_CODEC_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define FORMAT1_MAX_DATA_LEN   128
#define FORMAT1_MAX_FRAME_LEN  160
#define TFCAN_MAX_PAYLOAD_LEN  8

/* Active Physical Communication Protocol */
typedef enum {
    PROTO_RS232             = 0,
    PROTO_RS485_FULL_DUPLEX = 1,
    PROTO_CAN               = 2,
    PROTO_REST_API          = 3
} CommProtocol_t;

/* Active Data Packet Framing Format */
typedef enum {
    PKT_FORMAT_1_ASCII      = 0,
    PKT_FORMAT_2_TFCAN      = 1
} PacketFormat_t;

/* Data Packet Format 1: [?/!]:[aaaa]:[bb]:[ccc...ccc]:[dd]\r */
typedef struct {
    char     operation;                        /* '?' = Read Request, '!' = Write Request / Slave Response */
    uint16_t param_address;                    /* 4-char hex parameter address [aaaa] (0x0000..0xFFFF) */
    uint8_t  data_length;                      /* 2-char hex payload length [bb] (0x00..0x80) */
    char     data[FORMAT1_MAX_DATA_LEN + 1];   /* Null-terminated ASCII payload [ccc...ccc] */
    uint8_t  crc8;                             /* 2-char hex CRC-8 checksum [dd] */
} PacketFormat1_t;

/* Data Packet Format 2: TF CAN 29-Bit Operation Codes (Bits 25..23) */
typedef enum {
    TFCAN_OP_READ     = 0,
    TFCAN_OP_WRITE    = 1,
    TFCAN_OP_RESPONSE = 2,
    TFCAN_OP_EVENT    = 3
} TfCanOperation_t;

/* Data Packet Format 2: Classic CAN 29-Bit Extended Frame */
typedef struct {
    uint8_t  priority;                         /* Bits 28..26 (3 bits: 0..7) */
    uint8_t  operation;                        /* Bits 25..23 (3 bits: 0..7) */
    uint16_t object_id;                        /* Bits 22..12 (11 bits: 0..2047) */
    uint8_t  source;                           /* Bits 11..6  (6 bits: 0..63) */
    uint8_t  destination;                      /* Bits 5..0   (6 bits: 0..63) */
    uint8_t  dlc;                              /* CAN payload length (0..8 bytes) */
    uint8_t  payload[TFCAN_MAX_PAYLOAD_LEN];   /* CAN data bytes */
} PacketFormat2_CAN_t;

/* CRC-8 Calculation (Polynomial 0x07, Initial 0x00) */
uint8_t  Codec_ComputeCRC8(const uint8_t* data, size_t length);

/* Packet Format 1 Encode & Decode */
int      Codec_Format1_Encode(const PacketFormat1_t* pkt, char* out_buf, size_t out_size);
bool     Codec_Format1_Decode(const char* raw_frame, size_t raw_len, PacketFormat1_t* out_pkt);

/* Packet Format 2 (29-Bit TF CAN) Pack, Unpack & ASCII SLCAN Helpers */
uint32_t Codec_Format2_PackCanId(uint8_t priority, uint8_t operation, uint16_t object_id, uint8_t source, uint8_t destination);
void     Codec_Format2_UnpackCanId(uint32_t can_id_29bit, PacketFormat2_CAN_t* out_pkt);
int      Codec_Format2_ToAsciiHex(const PacketFormat2_CAN_t* pkt, char* out_buf, size_t out_size);
bool     Codec_Format2_FromAsciiHex(const char* ascii_line, PacketFormat2_CAN_t* out_pkt);

#ifdef __cplusplus
}
#endif

#endif /* PROTOCOL_CODEC_H */

```

#### 2.2 `C:\EW_MasterApp\Application\Source\protocol_codec.c`

```c
#include "protocol_codec.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* CRC-8-CCITT (Polynomial = 0x07, Initial Value = 0x00) */
uint8_t Codec_ComputeCRC8(const uint8_t* data, size_t length) {
    uint8_t crc = 0x00U;
    for (size_t i = 0; i < length; ++i) {
        crc ^= data[i];
        for (uint8_t bit = 0; bit < 8U; ++bit) {
            if ((crc & 0x80U) != 0U) {
                crc = (uint8_t)((crc << 1U) ^ 0x07U);
            } else {
                crc <<= 1U;
            }
        }
    }
    return crc;
}

/* Builds Format 1 Frame: [?/!]:[aaaa]:[bb]:[ccc...ccc]:[dd]\r */
int Codec_Format1_Encode(const PacketFormat1_t* pkt, char* out_buf, size_t out_size) {
    if (!pkt || !out_buf || out_size < FORMAT1_MAX_FRAME_LEN) {
        return -1;
    }
    if (pkt->operation != '?' && pkt->operation != '!') {
        return -2;
    }

    size_t actual_data_len = strlen(pkt->data);
    if (actual_data_len > FORMAT1_MAX_DATA_LEN) {
        return -3;
    }

    char body[FORMAT1_MAX_FRAME_LEN];
    int body_len = snprintf(
        body,
        sizeof(body),
        "%c:%04X:%02X:%s",
        pkt->operation,
        (unsigned int)(pkt->param_address & 0xFFFFU),
        (unsigned int)(actual_data_len & 0xFFU),
        pkt->data
    );
    if (body_len < 0 || (size_t)body_len >= sizeof(body)) {
        return -4;
    }

    uint8_t crc = Codec_ComputeCRC8((const uint8_t*)body, (size_t)body_len);
    return snprintf(out_buf, out_size, "%s:%02X\r", body, (unsigned int)crc);
}

/* Parses and validates Format 1 Frame: !:[aaaa]:[bb]:[ccc...ccc]:[dd]\r */
bool Codec_Format1_Decode(const char* raw_frame, size_t raw_len, PacketFormat1_t* out_pkt) {
    if (!raw_frame || !out_pkt || raw_len < 13U) {
        return false;
    }

    char clean[FORMAT1_MAX_FRAME_LEN];
    if (raw_len >= sizeof(clean)) {
        return false;
    }
    memcpy(clean, raw_frame, raw_len);
    clean[raw_len] = '\0';

    while (raw_len > 0U && (clean[raw_len - 1U] == '\r' || clean[raw_len - 1U] == '\n')) {
        clean[--raw_len] = '\0';
    }

    /* Minimum valid frame without data is 13 chars: !:0000:00::00 */
    if (raw_len < 13U || clean[1] != ':' || clean[6] != ':' || clean[9] != ':') {
        return false;
    }

    char* last_colon = strrchr(clean, ':');
    if (!last_colon || last_colon < (clean + 9) || strlen(last_colon + 1) != 2U) {
        return false;
    }

    unsigned int rx_crc = 0U;
    if (sscanf(last_colon + 1, "%02X", &rx_crc) != 1) {
        return false;
    }

    size_t body_len = (size_t)(last_colon - clean);
    uint8_t calc_crc = Codec_ComputeCRC8((const uint8_t*)clean, body_len);
    if (calc_crc != (uint8_t)rx_crc) {
        return false;
    }

    char addr_str[5] = { clean[2], clean[3], clean[4], clean[5], '\0' };
    char len_str[3]  = { clean[7], clean[8], '\0' };
    unsigned int addr_val = 0U;
    unsigned int len_val  = 0U;

    if (sscanf(addr_str, "%04X", &addr_val) != 1 || sscanf(len_str, "%02X", &len_val) != 1) {
        return false;
    }

    size_t data_chars = (size_t)(last_colon - (clean + 10));
    if (data_chars != (size_t)len_val || data_chars > FORMAT1_MAX_DATA_LEN) {
        return false;
    }

    out_pkt->operation     = clean[0];
    out_pkt->param_address = (uint16_t)addr_val;
    out_pkt->data_length   = (uint8_t)len_val;
    memcpy(out_pkt->data, clean + 10, data_chars);
    out_pkt->data[data_chars] = '\0';
    out_pkt->crc8          = (uint8_t)rx_crc;
    return true;
}

/* Packs 29-Bit TF CAN Extended Identifier (Bits 28..0) */
uint32_t Codec_Format2_PackCanId(
    uint8_t  priority,
    uint8_t  operation,
    uint16_t object_id,
    uint8_t  source,
    uint8_t  destination
) {
    return ((uint32_t)(priority    & 0x07U)  << 26U) |
           ((uint32_t)(operation   & 0x07U)  << 23U) |
           ((uint32_t)(object_id   & 0x7FFU) << 12U) |
           ((uint32_t)(source      & 0x3FU)  << 6U)  |
           ((uint32_t)(destination & 0x3FU)  << 0U);
}

/* Unpacks 29-Bit TF CAN Extended Identifier (Bits 28..0) */
void Codec_Format2_UnpackCanId(uint32_t can_id_29bit, PacketFormat2_CAN_t* out_pkt) {
    if (!out_pkt) {
        return;
    }
    out_pkt->priority    = (uint8_t)((can_id_29bit >> 26U) & 0x07U);
    out_pkt->operation   = (uint8_t)((can_id_29bit >> 23U) & 0x07U);
    out_pkt->object_id   = (uint16_t)((can_id_29bit >> 12U) & 0x7FFU);
    out_pkt->source      = (uint8_t)((can_id_29bit >> 6U)  & 0x3FU);
    out_pkt->destination = (uint8_t)(can_id_29bit & 0x3FU);
}

/* Converts 29-Bit TF CAN Frame into SLCAN ASCII Frame: T<8-Hex-ID><1-Hex-DLC><Data>\r */
int Codec_Format2_ToAsciiHex(const PacketFormat2_CAN_t* pkt, char* out_buf, size_t out_size) {
    if (!pkt || !out_buf || out_size < 32U || pkt->dlc > 8U) {
        return -1;
    }
    uint32_t can_id = Codec_Format2_PackCanId(
        pkt->priority, pkt->operation, pkt->object_id, pkt->source, pkt->destination
    );
    int offset = snprintf(out_buf, out_size, "T%08X%1X", (unsigned int)can_id, (unsigned int)pkt->dlc);
    for (uint8_t i = 0; i < pkt->dlc; ++i) {
        offset += snprintf(out_buf + offset, out_size - (size_t)offset, "%02X", pkt->payload[i]);
    }
    offset += snprintf(out_buf + offset, out_size - (size_t)offset, "\r");
    return offset;
}

/* Parses SLCAN ASCII Frame T<8-Hex-ID><1-Hex-DLC><Data>\r into PacketFormat2_CAN_t */
bool Codec_Format2_FromAsciiHex(const char* ascii_line, PacketFormat2_CAN_t* out_pkt) {
    if (!ascii_line || !out_pkt || ascii_line[0] != 'T' || strlen(ascii_line) < 10U) {
        return false;
    }
    char id_str[9];
    memcpy(id_str, ascii_line + 1, 8);
    id_str[8] = '\0';

    uint32_t can_id = (uint32_t)strtoul(id_str, NULL, 16);
    uint8_t dlc = (uint8_t)(ascii_line[9] - '0');
    if (dlc > 8U || strlen(ascii_line + 10) < (size_t)(dlc * 2U)) {
        return false;
    }

    Codec_Format2_UnpackCanId(can_id, out_pkt);
    out_pkt->dlc = dlc;
    for (uint8_t i = 0; i < dlc; ++i) {
        unsigned int byte_val = 0U;
        if (sscanf(ascii_line + 10 + (i * 2), "%02X", &byte_val) != 1) {
            return false;
        }
        out_pkt->payload[i] = (uint8_t)byte_val;
    }
    return true;
}

```

#### 2.3 `C:\EW_MasterApp\Application\Source\transport_manager.h`

```c
#ifndef TRANSPORT_MANAGER_H
#define TRANSPORT_MANAGER_H

#include "protocol_codec.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Queued Receive Event passed from Background Worker Thread to GUI Thread */
typedef struct {
    CommProtocol_t protocol;
    PacketFormat_t format;
    bool           is_error;
    uint16_t       param_or_object_id;
    uint8_t        operation;
    uint8_t        source_node;
    char           payload_str[FORMAT1_MAX_DATA_LEN + 1];
    char           raw_frame_log[256];
} MasterRxEvent_t;

bool Transport_Initialize(void);
void Transport_Shutdown(void);

bool Transport_Connect(
    CommProtocol_t protocol,
    PacketFormat_t format,
    const char*    endpoint,    /* e.g. "COM4", "PCAN_USBBUS1", or "127.0.0.1" */
    uint32_t       baud_or_port /* e.g. 115200 for Serial, 500000 for CAN, 8080 for REST */
);
void Transport_Disconnect(void);
bool Transport_IsConnected(void);

bool Transport_SendFormat1Request(char op_char, uint16_t param_addr, const char* data_str);
bool Transport_SendFormat2CanFrame(
    uint8_t        priority,
    uint8_t        operation,
    uint16_t       object_id,
    uint8_t        source_node,
    uint8_t        dest_node,
    const uint8_t* payload,
    uint8_t        dlc
);

bool Transport_PopRxEvent(MasterRxEvent_t* out_event);

#ifdef __cplusplus
}
#endif

#endif /* TRANSPORT_MANAGER_H */

```

#### 2.4 `C:\EW_MasterApp\Application\Source\transport_manager.cpp`

This file implements the [Win32 Serial Communications API (`CreateFileA`)](https://learn.microsoft.com/en-us/windows/win32/devio/configuring-a-communications-resource) and [`SetCommState`](https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-setcommstate) for `RS232` and `RS485_FullDuplex`, the [PEAK-System PCAN-Basic API](https://www.peak-system.com/products/software/development-packages/pcan-basic/) (plus virtual COM SLCAN fallback) for `CAN`, and [Microsoft WinHTTP Sessions](https://learn.microsoft.com/en-us/windows/win32/winhttp/winhttp-sessions-overview) via [`WinHttpOpen`](https://learn.microsoft.com/en-us/windows/win32/winhttp/winhttp-functions), [`WinHttpConnect`](https://learn.microsoft.com/en-us/windows/win32/api/winhttp/nf-winhttp-winhttpconnect), and [`WinHttpSendRequest`](https://learn.microsoft.com/en-us/windows/win32/api/winhttp/nf-winhttp-winhttpsendrequest) for `RestAPI`.

```cpp
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winhttp.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "transport_manager.h"

#pragma comment(lib, "winhttp.lib")

/* Optional: Uncomment USE_PCAN_BASIC_DLL if using PEAK-System PCAN-USB hardware */
/* #define USE_PCAN_BASIC_DLL */
#ifdef USE_PCAN_BASIC_DLL
#include "PCANBasic.h"
#pragma comment(lib, "PCANBasic.lib")
#endif

#define RX_QUEUE_CAPACITY 64

static CRITICAL_SECTION g_QueueLock;
static MasterRxEvent_t  g_RxQueue[RX_QUEUE_CAPACITY];
static size_t           g_QueueHead  = 0;
static size_t           g_QueueTail  = 0;
static size_t           g_QueueCount = 0;

static HANDLE           g_SerialHandle = INVALID_HANDLE_VALUE;
static HANDLE           g_WorkerThread = NULL;
static volatile LONG    g_Running      = 0;
static bool             g_Connected    = false;

static CommProtocol_t   g_ActiveProto   = PROTO_RS232;
static PacketFormat_t   g_ActiveFormat  = PKT_FORMAT_1_ASCII;
static char             g_Endpoint[128] = "127.0.0.1";
static uint32_t         g_BaudOrPort    = 8080;

static void PushRxEvent(const MasterRxEvent_t* ev) {
    EnterCriticalSection(&g_QueueLock);
    if (g_QueueCount < RX_QUEUE_CAPACITY) {
        g_RxQueue[g_QueueTail] = *ev;
        g_QueueTail = (g_QueueTail + 1U) % RX_QUEUE_CAPACITY;
        g_QueueCount++;
    }
    LeaveCriticalSection(&g_QueueLock);
}

static void PushErrorEvent(const char* msg) {
    MasterRxEvent_t ev;
    memset(&ev, 0, sizeof(ev));
    ev.protocol = g_ActiveProto;
    ev.format   = g_ActiveFormat;
    ev.is_error = true;
    snprintf(ev.payload_str, sizeof(ev.payload_str), "ERR");
    snprintf(ev.raw_frame_log, sizeof(ev.raw_frame_log), "[ERROR] %s", msg);
    PushRxEvent(&ev);
}

static bool OpenWin32SerialPort(const char* port_name, uint32_t baud_rate, bool is_rs485_full_duplex) {
    char full_port_path[64];
    if (strncmp(port_name, "\\\\.\\", 4) == 0) {
        snprintf(full_port_path, sizeof(full_port_path), "%s", port_name);
    } else {
        snprintf(full_port_path, sizeof(full_port_path), "\\\\.\\%s", port_name);
    }

    g_SerialHandle = CreateFileA(
        full_port_path,
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL
    );

    if (g_SerialHandle == INVALID_HANDLE_VALUE) {
        return false;
    }

    DCB dcb;
    SecureZeroMemory(&dcb, sizeof(DCB));
    dcb.DCBlength = sizeof(DCB);

    if (!GetCommState(g_SerialHandle, &dcb)) {
        CloseHandle(g_SerialHandle);
        g_SerialHandle = INVALID_HANDLE_VALUE;
        return false;
    }

    dcb.BaudRate     = baud_rate;
    dcb.ByteSize     = 8;
    dcb.Parity       = NOPARITY;
    dcb.StopBits     = ONESTOPBIT;
    dcb.fBinary      = TRUE;
    dcb.fParity      = FALSE;
    dcb.fOutxCtsFlow = FALSE;
    dcb.fOutxDsrFlow = FALSE;
    dcb.fOutX        = FALSE;
    dcb.fInX         = FALSE;

    if (is_rs485_full_duplex) {
        /* 4-Wire RS485 Full-Duplex keeps TX+/TX- and RX+/RX- simultaneously active */
        dcb.fRtsControl = RTS_CONTROL_DISABLE;
        dcb.fDtrControl = DTR_CONTROL_ENABLE;
    } else {
        /* RS232 asserts RTS and DTR lines */
        dcb.fRtsControl = RTS_CONTROL_ENABLE;
        dcb.fDtrControl = DTR_CONTROL_ENABLE;
    }

    if (!SetCommState(g_SerialHandle, &dcb)) {
        CloseHandle(g_SerialHandle);
        g_SerialHandle = INVALID_HANDLE_VALUE;
        return false;
    }

    COMMTIMEOUTS timeouts;
    timeouts.ReadIntervalTimeout         = 10;
    timeouts.ReadTotalTimeoutMultiplier  = 1;
    timeouts.ReadTotalTimeoutConstant    = 25;
    timeouts.WriteTotalTimeoutMultiplier = 1;
    timeouts.WriteTotalTimeoutConstant   = 50;
    SetCommTimeouts(g_SerialHandle, &timeouts);
    PurgeComm(g_SerialHandle, PURGE_RXCLEAR | PURGE_TXCLEAR);
    return true;
}

static void ProcessReceivedAsciiLine(const char* line_buf, size_t line_len) {
    MasterRxEvent_t ev;
    memset(&ev, 0, sizeof(ev));
    ev.protocol = g_ActiveProto;
    ev.format   = g_ActiveFormat;
    snprintf(ev.raw_frame_log, sizeof(ev.raw_frame_log), "RX: %.*s", (int)line_len, line_buf);

    if (g_ActiveFormat == PKT_FORMAT_1_ASCII) {
        PacketFormat1_t pkt1;
        if (Codec_Format1_Decode(line_buf, line_len, &pkt1)) {
            ev.is_error           = false;
            ev.param_or_object_id = pkt1.param_address;
            ev.operation          = (uint8_t)pkt1.operation;
            snprintf(ev.payload_str, sizeof(ev.payload_str), "%s", pkt1.data);
            PushRxEvent(&ev);
        } else {
            PushErrorEvent("Format 1 CRC-8 or Syntax Mismatch");
        }
    } else {
        PacketFormat2_CAN_t pkt2;
        if (Codec_Format2_FromAsciiHex(line_buf, &pkt2)) {
            ev.is_error           = false;
            ev.param_or_object_id = pkt2.object_id;
            ev.operation          = pkt2.operation;
            ev.source_node        = pkt2.source;
            int offset = 0;
            for (uint8_t i = 0; i < pkt2.dlc; ++i) {
                offset += snprintf(
                    ev.payload_str + offset,
                    sizeof(ev.payload_str) - (size_t)offset,
                    "%02X ",
                    pkt2.payload[i]
                );
            }
            PushRxEvent(&ev);
        } else {
            PushErrorEvent("Format 2 CAN Frame Decode Error");
        }
    }
}

static DWORD WINAPI TransportRxWorkerThread(LPVOID lpParam) {
    (void)lpParam;
    char rx_accum[FORMAT1_MAX_FRAME_LEN];
    size_t rx_pos = 0;

    while (InterlockedCompareExchange(&g_Running, 0, 0) != 0) {
        if (g_ActiveProto == PROTO_RS232 ||
            g_ActiveProto == PROTO_RS485_FULL_DUPLEX ||
            (g_ActiveProto == PROTO_CAN && g_SerialHandle != INVALID_HANDLE_VALUE)) {

            char byte_buf[32];
            DWORD bytes_read = 0;
            if (ReadFile(g_SerialHandle, byte_buf, sizeof(byte_buf), &bytes_read, NULL) && bytes_read > 0) {
                for (DWORD i = 0; i < bytes_read; ++i) {
                    char c = byte_buf[i];
                    if (c == '\r' || c == '\n') {
                        if (rx_pos > 0) {
                            rx_accum[rx_pos] = '\0';
                            ProcessReceivedAsciiLine(rx_accum, rx_pos);
                            rx_pos = 0;
                        }
                    } else if (rx_pos < (sizeof(rx_accum) - 1U)) {
                        rx_accum[rx_pos++] = c;
                    } else {
                        rx_pos = 0;
                    }
                }
            }
        }
#ifdef USE_PCAN_BASIC_DLL
        else if (g_ActiveProto == PROTO_CAN) {
            TPCANMsg can_msg;
            TPCANTimestamp can_ts;
            TPCANStatus status = CAN_Read(PCAN_USBBUS1, &can_msg, &can_ts);
            if (status == PCAN_ERROR_OK && (can_msg.MSGTYPE & PCAN_MESSAGE_EXTENDED)) {
                PacketFormat2_CAN_t pkt2;
                Codec_Format2_UnpackCanId(can_msg.ID, &pkt2);
                pkt2.dlc = (can_msg.LEN <= 8U) ? can_msg.LEN : 8U;
                memcpy(pkt2.payload, can_msg.DATA, pkt2.dlc);

                MasterRxEvent_t ev;
                memset(&ev, 0, sizeof(ev));
                ev.protocol           = PROTO_CAN;
                ev.format             = PKT_FORMAT_2_TFCAN;
                ev.param_or_object_id = pkt2.object_id;
                ev.operation          = pkt2.operation;
                ev.source_node        = pkt2.source;
                int offset = 0;
                for (uint8_t i = 0; i < pkt2.dlc; ++i) {
                    offset += snprintf(ev.payload_str + offset, sizeof(ev.payload_str) - (size_t)offset, "%02X ", pkt2.payload[i]);
                }
                snprintf(ev.raw_frame_log, sizeof(ev.raw_frame_log), "CAN RX ID=0x%08X DLC=%u", can_msg.ID, pkt2.dlc);
                PushRxEvent(&ev);
            }
            Sleep(5);
        }
#endif
        else {
            Sleep(20);
        }
    }
    return 0;
}

static bool SendViaWinHttpRestApi(const char* raw_packet_str) {
    wchar_t w_host[128];
    MultiByteToWideChar(CP_UTF8, 0, g_Endpoint, -1, w_host, 128);

    HINTERNET hSession = WinHttpOpen(
        L"EmbeddedWizard-MasterController/1.0",
        WINHTTP_ACCESS_TYPE_NO_PROXY,
        WINHTTP_NO_PROXY_NAME,
        WINHTTP_NO_PROXY_BYPASS,
        0
    );
    if (!hSession) {
        PushErrorEvent("WinHttpOpen failed");
        return false;
    }

    HINTERNET hConnect = WinHttpConnect(hSession, w_host, (INTERNET_PORT)g_BaudOrPort, 0);
    if (!hConnect) {
        WinHttpCloseHandle(hSession);
        PushErrorEvent("WinHttpConnect failed");
        return false;
    }

    HINTERNET hRequest = WinHttpOpenRequest(
        hConnect,
        L"POST",
        L"/api/v1/packet",
        NULL,
        WINHTTP_NO_REFERER,
        WINHTTP_DEFAULT_ACCEPT_TYPES,
        0
    );
    if (!hRequest) {
        WinHttpCloseHandle(hConnect);
        WinHttpCloseHandle(hSession);
        PushErrorEvent("WinHttpOpenRequest failed");
        return false;
    }

    char clean_pkt[FORMAT1_MAX_FRAME_LEN];
    snprintf(clean_pkt, sizeof(clean_pkt), "%s", raw_packet_str);
    size_t len = strlen(clean_pkt);
    if (len > 0 && clean_pkt[len - 1] == '\r') {
        clean_pkt[len - 1] = '\0';
    }

    char json_body[256];
    int json_len = snprintf(
        json_body,
        sizeof(json_body),
        "{\"format\":%d,\"packet\":\"%s\"}",
        (int)g_ActiveFormat,
        clean_pkt
    );

    LPCWSTR headers = L"Content-Type: application/json\r\n";
    BOOL bResults = WinHttpSendRequest(
        hRequest,
        headers,
        (DWORD)-1L,
        (LPVOID)json_body,
        (DWORD)json_len,
        (DWORD)json_len,
        0
    );

    if (bResults) {
        bResults = WinHttpReceiveResponse(hRequest, NULL);
    }

    if (bResults) {
        char resp_buf[256];
        DWORD bytes_read = 0;
        memset(resp_buf, 0, sizeof(resp_buf));
        if (WinHttpReadData(hRequest, resp_buf, sizeof(resp_buf) - 1, &bytes_read) && bytes_read > 0) {
            resp_buf[bytes_read] = '\0';
            ProcessReceivedAsciiLine(resp_buf, bytes_read);
        }
    } else {
        PushErrorEvent("HTTP REST Server Unreachable");
    }

    WinHttpCloseHandle(hRequest);
    WinHttpCloseHandle(hConnect);
    WinHttpCloseHandle(hSession);
    return bResults == TRUE;
}

bool Transport_Initialize(void) {
    InitializeCriticalSection(&g_QueueLock);
    g_QueueHead  = 0;
    g_QueueTail  = 0;
    g_QueueCount = 0;
    return true;
}

void Transport_Shutdown(void) {
    Transport_Disconnect();
    DeleteCriticalSection(&g_QueueLock);
}

bool Transport_Connect(
    CommProtocol_t protocol,
    PacketFormat_t format,
    const char*    endpoint,
    uint32_t       baud_or_port
) {
    Transport_Disconnect();

    g_ActiveProto  = protocol;
    g_ActiveFormat = format;
    snprintf(g_Endpoint, sizeof(g_Endpoint), "%s", endpoint ? endpoint : "127.0.0.1");
    g_BaudOrPort    = baud_or_port;

    if (protocol == PROTO_RS232 || protocol == PROTO_RS485_FULL_DUPLEX) {
        bool is_rs485 = (protocol == PROTO_RS485_FULL_DUPLEX);
        if (!OpenWin32SerialPort(g_Endpoint, baud_or_port, is_rs485)) {
            PushErrorEvent("Failed to open Win32 COM Port");
            return false;
        }
    } else if (protocol == PROTO_CAN) {
#ifdef USE_PCAN_BASIC_DLL
        TPCANStatus sts = CAN_Initialize(PCAN_USBBUS1, PCAN_BAUD_500K, 0, 0, 0);
        if (sts != PCAN_ERROR_OK) {
            PushErrorEvent("PCAN_USBBUS1 Init Failed");
            return false;
        }
#else
        if (!OpenWin32SerialPort(g_Endpoint, baud_or_port, false)) {
            PushErrorEvent("Failed to open SLCAN COM Port");
            return false;
        }
#endif
    }

    g_Connected = true;
    InterlockedExchange(&g_Running, 1);
    g_WorkerThread = CreateThread(NULL, 0, TransportRxWorkerThread, NULL, 0, NULL);
    return true;
}

void Transport_Disconnect(void) {
    InterlockedExchange(&g_Running, 0);
    if (g_WorkerThread != NULL) {
        WaitForSingleObject(g_WorkerThread, 500);
        CloseHandle(g_WorkerThread);
        g_WorkerThread = NULL;
    }
    if (g_SerialHandle != INVALID_HANDLE_VALUE) {
        CloseHandle(g_SerialHandle);
        g_SerialHandle = INVALID_HANDLE_VALUE;
    }
#ifdef USE_PCAN_BASIC_DLL
    if (g_ActiveProto == PROTO_CAN) {
        CAN_Uninitialize(PCAN_USBBUS1);
    }
#endif
    g_Connected = false;
}

bool Transport_IsConnected(void) {
    return g_Connected;
}

bool Transport_SendFormat1Request(char op_char, uint16_t param_addr, const char* data_str) {
    if (!g_Connected) {
        PushErrorEvent("Transport Disconnected");
        return false;
    }

    PacketFormat1_t pkt;
    memset(&pkt, 0, sizeof(pkt));
    pkt.operation     = op_char;
    pkt.param_address = param_addr;
    snprintf(pkt.data, sizeof(pkt.data), "%s", data_str ? data_str : "");
    pkt.data_length   = (uint8_t)strlen(pkt.data);

    char encoded[FORMAT1_MAX_FRAME_LEN];
    int len = Codec_Format1_Encode(&pkt, encoded, sizeof(encoded));
    if (len <= 0) {
        PushErrorEvent("Format 1 Encode Failed");
        return false;
    }

    if (g_ActiveProto == PROTO_REST_API) {
        return SendViaWinHttpRestApi(encoded);
    }

    if (g_SerialHandle != INVALID_HANDLE_VALUE) {
        DWORD written = 0;
        return WriteFile(g_SerialHandle, encoded, (DWORD)len, &written, NULL) && (written == (DWORD)len);
    }
    return false;
}

bool Transport_SendFormat2CanFrame(
    uint8_t        priority,
    uint8_t        operation,
    uint16_t       object_id,
    uint8_t        source_node,
    uint8_t        dest_node,
    const uint8_t* payload,
    uint8_t        dlc
) {
    if (!g_Connected || dlc > 8U) {
        PushErrorEvent("Disconnected or Invalid CAN DLC");
        return false;
    }

    PacketFormat2_CAN_t pkt2;
    memset(&pkt2, 0, sizeof(pkt2));
    pkt2.priority    = priority;
    pkt2.operation   = operation;
    pkt2.object_id   = object_id;
    pkt2.source      = source_node;
    pkt2.destination = dest_node;
    pkt2.dlc         = dlc;
    if (payload && dlc > 0U) {
        memcpy(pkt2.payload, payload, dlc);
    }

#ifdef USE_PCAN_BASIC_DLL
    if (g_ActiveProto == PROTO_CAN) {
        TPCANMsg msg;
        msg.ID      = Codec_Format2_PackCanId(priority, operation, object_id, source_node, dest_node);
        msg.MSGTYPE = PCAN_MESSAGE_EXTENDED;
        msg.LEN     = dlc;
        memcpy(msg.DATA, pkt2.payload, dlc);
        return CAN_Write(PCAN_USBBUS1, &msg) == PCAN_ERROR_OK;
    }
#endif

    char slcan_frame[64];
    int len = Codec_Format2_ToAsciiHex(&pkt2, slcan_frame, sizeof(slcan_frame));
    if (len <= 0) {
        return false;
    }

    if (g_ActiveProto == PROTO_REST_API) {
        return SendViaWinHttpRestApi(slcan_frame);
    }

    if (g_SerialHandle != INVALID_HANDLE_VALUE) {
        DWORD written = 0;
        return WriteFile(g_SerialHandle, slcan_frame, (DWORD)len, &written, NULL) && (written == (DWORD)len);
    }
    return false;
}

bool Transport_PopRxEvent(MasterRxEvent_t* out_event) {
    bool has_item = false;
    EnterCriticalSection(&g_QueueLock);
    if (g_QueueCount > 0U && out_event != NULL) {
        *out_event  = g_RxQueue[g_QueueHead];
        g_QueueHead = (g_QueueHead + 1U) % RX_QUEUE_CAPACITY;
        g_QueueCount--;
        has_item = true;
    }
    LeaveCriticalSection(&g_QueueLock);
    return has_item;
}

```

#### 2.5 `C:\EW_MasterApp\Application\Source\DeviceDriver.h` and `DeviceDriver.c`

Confirm `C:\EW_MasterApp\Application\Source\DeviceDriver.h` contains:

```c
#ifndef DEVICEDRIVER_H
#define DEVICEDRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

void DeviceDriver_Initialize( void );
void DeviceDriver_Deinitialize( void );
int  DeviceDriver_ProcessData( void );

#ifdef __cplusplus
}
#endif

#endif /* DEVICEDRIVER_H */

```

Replace `C:\EW_MasterApp\Application\Source\DeviceDriver.c` with the following implementation ([Embedded Wizard System Event Integration](https://doc.embedded-wizard.de/device-class-system-event?v=9.10)):

```c
#include "ewrte.h"
#include "ewgfx.h"
#include "Application.h"
#include "DeviceDriver.h"
#include "transport_manager.h"

void DeviceDriver_Initialize( void )
{
  Transport_Initialize();
}

void DeviceDriver_Deinitialize( void )
{
  Transport_Shutdown();
}

int DeviceDriver_ProcessData( void )
{
  MasterRxEvent_t rx_ev;
  int processed = 0;

  while ( Transport_PopRxEvent( &rx_ev ) )
  {
    ApplicationDeviceClass device = EwGetAutoObject( &ApplicationDevice, ApplicationDeviceClass );

    if ( device != 0 )
    {
      XString x_payload = EwNewStringAnsi( rx_ev.payload_str );
      XString x_raw_log = EwNewStringAnsi( rx_ev.raw_frame_log );

      ApplicationDeviceClass__UpdateTelemetryFromDriver(
        device,
        (XInt32)rx_ev.param_or_object_id,
        x_payload,
        x_raw_log
      );

      processed = 1;
    }
  }

  return processed;
}

```

### Step 3: Create the Embedded Wizard Studio Project (`MasterController.ewp`)

1. Open **Embedded Wizard Studio**, select **File > New > Project**, choose **Windows Software**, and save it as `C:\EW_MasterApp\Application\MasterGUI\MasterController.ewp`.
2. Click the **Profile** brick in the top-level **Composer** and set these properties in the **Inspector**:
* **PlatformPackage**: `Windows.Software.RGBA8888`
* **ScreenSize**: `<1280, 720>`
* **OutputDirectory**: `..\..\Application\GeneratedCode`
* **CleanOutputDirectories**: `true`
* **PostProcess**: `..\..\Application\Project\MSVC\MSVC_ew_post_process.cmd`



#### 3.1 Configure `Application::DeviceClass` in the `Application` Unit

1. Open the `Application` unit in the **Composer**, press `Ctrl+Shift+T` to open **Templates**, open the **Device** folder, and drag **Device Interface** into the workspace ([Implementing a Device Interface](https://doc.embedded-wizard.de/device-class-and-device-driver)).
2. Double-click the **`Inline`** brick and paste:
```c
#include "transport_manager.h"

```


3. Double-click the **`DeviceClass`** brick to open it. Add 6 **Properties** (from **Templates > Device > Property**), 1 **System Event** (`RxPacketEvent`), and 5 **Methods** (`OpenConnection`, `CloseConnection`, `SendFormat1`, `SendFormat2CAN`, and `UpdateTelemetryFromDriver`).
4. Set the 6 Properties (and delete their default `OnSet` / `OnGet` methods if you only need direct variable storage, or leave the default `pure PropertyName = value;` implementation):
* `ProtocolType` (`int32`, default `3` for `RestAPI` or `0` for `RS232`)
* `PacketFormat` (`int32`, default `0` for Format 1 or `1` for Format 2 CAN)
* `IsConnected` (`bool`, default `false`)
* `LastRxAddress` (`int32`, default `0`)
* `LastRxPayload` (`string`, default `""`)
* `StatusLog` (`string`, default `"Ready"`)


5. Paste the exact Chora code below into each of the 5 methods inside `Application::DeviceClass`:

```c
/* Method 1: method bool OpenConnection( arg string aEndpoint, arg int32 aBaudOrPort ) */
var int32 proto  = pure ProtocolType;
var int32 format = pure PacketFormat;
var bool  ok     = false;

$if $prototyper
  trace "Prototyper Connect: ", aEndpoint, ":", aBaudOrPort;
  ok = true;
$else
  native ( proto, format, aEndpoint, aBaudOrPort, ok )
  {
    char c_endpoint[128];
    EwStringToAnsi( aEndpoint, c_endpoint, sizeof( c_endpoint ) );
    ok = Transport_Connect(
      (CommProtocol_t)proto,
      (PacketFormat_t)format,
      c_endpoint,
      (uint32_t)aBaudOrPort
    );
  }
$endif

pure IsConnected = ok;
notifyobservers ^IsConnected;
return ok;

```

```c
/* Method 2: method void CloseConnection() */
$if !$prototyper
  native
  {
    Transport_Disconnect();
  }
$endif

pure IsConnected = false;
notifyobservers ^IsConnected;

```

```c
/* Method 3: method bool SendFormat1( arg bool aIsWrite, arg int32 aAddr, arg string aData ) */
var bool sent = false;

$if $prototyper
  trace "Prototyper Format1 TX: Write=", aIsWrite, " Addr=", aAddr, " Data=", aData;
  sent = true;
$else
  native ( aIsWrite, aAddr, aData, sent )
  {
    char c_data[129];
    EwStringToAnsi( aData, c_data, sizeof( c_data ) );
    char op = aIsWrite ? '!' : '?';
    sent = Transport_SendFormat1Request( op, (uint16_t)(aAddr & 0xFFFF), c_data );
  }
$endif

return sent;

```

```c
/* Method 4: method bool SendFormat2CAN( arg int32 aPrio, arg int32 aOp, arg int32 aObjId, arg int32 aSrc, arg int32 aDst, arg int32 aValue32 ) */
var bool sent = false;

$if $prototyper
  trace "Prototyper Format2 CAN TX: ObjId=", aObjId, " Op=", aOp, " Val=", aValue32;
  sent = true;
$else
  native ( aPrio, aOp, aObjId, aSrc, aDst, aValue32, sent )
  {
    uint8_t payload[4];
    payload[0] = (uint8_t)((aValue32 >> 24) & 0xFF);
    payload[1] = (uint8_t)((aValue32 >> 16) & 0xFF);
    payload[2] = (uint8_t)((aValue32 >> 8)  & 0xFF);
    payload[3] = (uint8_t)(aValue32 & 0xFF);

    sent = Transport_SendFormat2CanFrame(
      (uint8_t)(aPrio & 0x07),
      (uint8_t)(aOp & 0x07),
      (uint16_t)(aObjId & 0x7FF),
      (uint8_t)(aSrc & 0x3F),
      (uint8_t)(aDst & 0x3F),
      payload,
      4U
    );
  }
$endif

return sent;

```

```c
/* Method 5: method void UpdateTelemetryFromDriver( arg int32 aParamOrObjId, arg string aPayload, arg string aRawLog ) */
pure LastRxAddress = aParamOrObjId;
pure LastRxPayload = aPayload;
pure StatusLog     = aRawLog;

notifyobservers ^LastRxAddress;
notifyobservers ^LastRxPayload;
notifyobservers ^StatusLog;

RxPacketEvent.Trigger( null, false );

```

#### 3.2 Add UI Widgets & Slot Methods in `Application::Application`

Double-click the **`Application::Application`** GUI component in the Composer and add:

* Three **Views::Text** labels (`StatusText`, `AddressText`, `PayloadText`) from **Templates > Views > Text**.
* Five **WidgetSet::PushButton** buttons (`BtnConnect`, `BtnSwitchProto`, `BtnSwitchFormat`, `BtnSendRead`, `BtnSendWrite`) from **Templates > Widgets > Push Button**.
* One **Core::SystemEventHandler** (`RxEventHandler`) from **Templates > Device > System Event Handler**, setting its `Event` property in the Inspector to `Application::Device.RxPacketEvent`.
* Five **Slot Methods** (`OnConnectSlot`, `OnToggleProtoSlot`, `OnToggleFormatSlot`, `OnReadSlot`, `OnWriteSlot`) linked to the `OnActivate` property of each button, plus `OnRxEventSlot` linked to `RxEventHandler.OnEvent`:

```c
/* Slot: OnConnectSlot */
if ( !Application::Device.IsConnected )
{
  if ( Application::Device.ProtocolType == 3 )
  {
    /* Connect to local Python REST API Slave Simulator on 127.0.0.1:8080 */
    Application::Device.OpenConnection( "127.0.0.1", 8080 );
  }
  else
  {
    /* Connect to Serial / Virtual COM Port COM4 at 115200 baud */
    Application::Device.OpenConnection( "COM4", 115200 );
  }
}
else
{
  Application::Device.CloseConnection();
}

```

```c
/* Slot: OnToggleProtoSlot (Cycles 0=RS232 -> 1=RS485_FullDuplex -> 2=CAN -> 3=RestAPI) */
Application::Device.ProtocolType = ( Application::Device.ProtocolType + 1 ) % 4;

```

```c
/* Slot: OnToggleFormatSlot (Toggles 0=Format 1 ASCII CRC-8 <-> 1=Format 2 TF CAN 29-Bit) */
Application::Device.PacketFormat = ( Application::Device.PacketFormat == 0 ) ? 1 : 0;

```

```c
/* Slot: OnReadSlot */
if ( Application::Device.PacketFormat == 0 )
{
  /* Format 1 Read Request for Parameter 0x01A4 -> sends ?:01A4:00::A5\r */
  Application::Device.SendFormat1( false, 0x01A4, "" );
}
else
{
  /* Format 2 TF CAN Read Request: Priority=3, Op=0(Read), ObjID=0x1A4, Src=1, Dst=2 */
  Application::Device.SendFormat2CAN( 3, 0, 0x01A4, 1, 2, 0 );
}

```

```c
/* Slot: OnWriteSlot */
if ( Application::Device.PacketFormat == 0 )
{
  /* Format 1 Write Request for Parameter 0x01A4 = "00FA" -> sends !:01A4:04:00FA:AF\r */
  Application::Device.SendFormat1( true, 0x01A4, "00FA" );
}
else
{
  /* Format 2 TF CAN Write Request: Priority=2, Op=1(Write), ObjID=0x1A4, Src=1, Dst=2, Val=250 */
  Application::Device.SendFormat2CAN( 2, 1, 0x01A4, 1, 2, 250 );
}

```

```c
/* Slot: OnRxEventSlot (Linked to RxEventHandler.OnEvent) */
AddressText.String = "Param/Obj ID: 0x" + string( Application::Device.LastRxAddress, 4, 16 );
PayloadText.String = "Slave Data: " + Application::Device.LastRxPayload;
StatusText.String  = Application::Device.StatusLog;

```

### Step 4: Generate Code and Build in Microsoft Visual Studio (MSVC)

1. **Generate Embedded Wizard C Code**: Press **`F8`** (`Build > Build this profile`) inside Embedded Wizard Studio. Confirm the Log window reports code generation into `C:\EW_MasterApp\Application\GeneratedCode` and executes `MSVC_ew_post_process.cmd`.
2. **Open the MSVC Solution**: Launch Visual Studio and open `C:\EW_MasterApp\Application\Project\MSVC\EmbeddedWizard-Windows.sln`.
3. **Add Your Source Files**: In **Solution Explorer**, right-click the **Source** filter, click **Add > Existing Item...**, and add:
* `C:\EW_MasterApp\Application\Source\protocol_codec.h`
* `C:\EW_MasterApp\Application\Source\protocol_codec.c`
* `C:\EW_MasterApp\Application\Source\transport_manager.h`
* `C:\EW_MasterApp\Application\Source\transport_manager.cpp`


4. **Disable Precompiled Headers on Custom Files**: Select both `protocol_codec.c` and `transport_manager.cpp` in Solution Explorer, open **Properties > C/C++ > Precompiled Headers**, and set **Precompiled Header** to **Not Using Precompiled Headers**.
5. **Compile and Run**: Select **Debug | x64** in the Visual Studio toolbar, press **`F7`** to build the solution, and press **`F5`** to launch your Master Controller application.

### Step 5: Test Locally on Your Machine with the Complete Python Slave Simulator (`slave_simulator.py`)

Save the script below as `C:\EW_MasterApp\slave_simulator.py` and run `python C:\EW_MasterApp\slave_simulator.py` in a terminal. It runs a live HTTP REST Slave Server on `127.0.0.1:8080` (and an optional Serial COM listener if `pyserial` is installed) that validates **Format 1** CRC-8 frames and **Format 2** 29-bit TF CAN frames and returns live Slave responses to your GUI:

```python
#!/usr/bin/env python3
"""
Local Multi-Protocol Slave Controller Simulator for Windows Master App Testing
Supports:
  1. HTTP REST API Slave Server on http://127.0.0.1:8080/api/v1/packet
  2. Optional Serial (RS232 / RS485_FullDuplex / SLCAN) listener (if pyserial is installed)
  3. Data Packet Format 1: [?/!]:[aaaa]:[bb]:[ccc...ccc]:[dd]\r
  4. Data Packet Format 2: 29-Bit TF CAN Extended ID (SLCAN T<8-hex-ID><DLC><Data>\r)
"""
import json
import sys
import threading
from http.server import BaseHTTPRequestHandler, HTTPServer

SLAVE_REGISTERS = {
    0x01A4: "00FA",
    0x0200: "0064",
    0x0300: "1234",
}

def compute_crc8(data: bytes) -> int:
    crc = 0x00
    for b in data:
        crc ^= b
        for _ in range(8):
            crc = ((crc << 1) ^ 0x07) & 0xFF if (crc & 0x80) else ((crc << 1) & 0xFF)
    return crc

def process_format1_frame(raw_frame: str) -> str:
    clean = raw_frame.strip("\r\n")
    parts = clean.split(":")
    if len(parts) != 5:
        return "!:FFFF:03:ERR:3A\r"

    op, addr_hex, len_hex, payload, crc_hex = parts
    body = f"{op}:{addr_hex}:{len_hex}:{payload}".encode("ascii")
    calc_crc = compute_crc8(body)
    if calc_crc != int(crc_hex, 16):
        print(f"[SLAVE] Format 1 CRC Mismatch: Expected {calc_crc:02X}, Got {crc_hex}")
        return "!:FFFF:03:CRC:70\r"

    param_addr = int(addr_hex, 16)
    if op == "!":
        SLAVE_REGISTERS[param_addr] = payload
        print(f"[SLAVE] Format 1 WRITE Param 0x{param_addr:04X} = {payload}")
    else:
        print(f"[SLAVE] Format 1 READ  Param 0x{param_addr:04X}")

    resp_data = SLAVE_REGISTERS.get(param_addr, "0000")
    resp_body = f"!:{param_addr:04X}:{len(resp_data):02X}:{resp_data}"
    resp_crc  = compute_crc8(resp_body.encode("ascii"))
    return f"{resp_body}:{resp_crc:02X}\r"

def process_format2_slcan(raw_frame: str) -> str:
    clean = raw_frame.strip("\r\n")
    if not clean.startswith("T") or len(clean) < 10:
        return ""

    can_id   = int(clean[1:9], 16)
    dlc      = int(clean[9], 16)
    data_hex = clean[10:10 + dlc * 2]

    prio = (can_id >> 26) & 0x07
    op   = (can_id >> 23) & 0x07
    obj  = (can_id >> 12) & 0x7FF
    src  = (can_id >> 6)  & 0x3F
    dst  = can_id & 0x3F

    print(f"[SLAVE] Format 2 CAN RX: Prio={prio} Op={op} Obj=0x{obj:03X} Src={src} Dst={dst} Data={data_hex}")
    if op == 1 and dlc > 0:
        SLAVE_REGISTERS[obj] = data_hex.upper()

    val_hex = SLAVE_REGISTERS.get(obj, "000000FA").rjust(8, "0")[:8]
    resp_op = 2  # TFCAN_OP_RESPONSE
    resp_id = (prio << 26) | (resp_op << 23) | (obj << 12) | (dst << 6) | src
    return f"T{resp_id:08X}4{val_hex}\r"

class SlaveRestHandler(BaseHTTPRequestHandler):
    def do_POST(self):
        if self.path != "/api/v1/packet":
            self.send_response(404)
            self.end_headers()
            return

        length = int(self.headers.get("Content-Length", 0))
        body = self.rfile.read(length).decode("utf-8")
        payload = json.loads(body)
        pkt_format = payload.get("format", 0)
        raw_packet = payload.get("packet", "")

        if pkt_format == 0:
            reply = process_format1_frame(raw_packet)
        else:
            reply = process_format2_slcan(raw_packet)

        reply_bytes = reply.encode("ascii")
        self.send_response(200)
        self.send_header("Content-Type", "text/plain")
        self.send_header("Content-Length", str(len(reply_bytes)))
        self.end_headers()
        self.wfile.write(reply_bytes)

if __name__ == "__main__":
    server = HTTPServer(("127.0.0.1", 8080), SlaveRestHandler)
    print("Slave Controller REST Simulator listening on http://127.0.0.1:8080/api/v1/packet ...")
    print("Press Ctrl+C to stop.")
    server.serve_forever()

```