#include <SPI.h>
#include <mcp_canbus.h>

#define SPI_CS_PIN 17
#define CAN_ID_PID 0x7DF

MCP_CAN CAN(SPI_CS_PIN);

void set_mask_filt() {
    CAN.init_Mask(0, 0, 0x700);
    CAN.init_Mask(1, 0, 0x700);
    CAN.init_Filt(0, 0, 0x700);
    for (int i = 1; i < 6; i++) {
        CAN.init_Filt(i, 0, 0x7E8 + (i % 8));
    }
}

void sendRequestDTCs() {
    unsigned char buf[8] = {0x02, 0x03, 0x00, 0, 0, 0, 0, 0};  // Mode 03
    CAN.sendMsgBuf(CAN_ID_PID, 0, 8, buf);
}

void sendClearDTCs() {
    unsigned char buf[8] = {0x02, 0x04, 0x00, 0, 0, 0, 0, 0};  // Mode 04
    CAN.sendMsgBuf(CAN_ID_PID, 0, 8, buf);
}

void parseAndPrintDTCs(unsigned char* data, int len) {
    int dtcCount = len / 2;
    for (int i = 0; i < dtcCount; i++) {
        unsigned char A = data[i * 2];
        unsigned char B = data[i * 2 + 1];
        if (A == 0x00 && B == 0x00) continue;

        char dtc[6];
        char system = "PCBU"[(A >> 6) & 0x03];
        int code = ((A & 0x3F) << 8) | B;
        sprintf(dtc, "%c%04X", system, code);

        Serial.print("DTC: ");
        Serial.println(dtc);
    }
}

void flushCANBuffer() {
    unsigned char len;
    unsigned char buf[8];
    while (CAN_MSGAVAIL == CAN.checkReceive()) {
        CAN.readMsgBuf(&len, buf);
    }
}

void scanDTCs() {
    flushCANBuffer();
    sendRequestDTCs();

    unsigned long startTime = millis();
    unsigned char buffer[64];
    int totalLen = 0;
    int expectedLen = -1;

    while (millis() - startTime < 3000) {
        if (CAN_MSGAVAIL == CAN.checkReceive()) {
            unsigned char len = 0;
            unsigned char buf[8];
            CAN.readMsgBuf(&len, buf);

            unsigned char frameType = buf[0] & 0xF0;

            if (frameType == 0x00 && buf[1] == 0x43) {
                totalLen = len - 2;
                memcpy(buffer, buf + 2, totalLen);
                break;

            } else if (frameType == 0x10) {
                expectedLen = ((buf[0] & 0x0F) << 8) | buf[1];
                totalLen = len - 2;
                memcpy(buffer, buf + 2, totalLen);

                int nextFrame = 1;
                unsigned long frameStart = millis();

                while (totalLen < expectedLen && millis() - frameStart < 1000) {
                    if (CAN_MSGAVAIL == CAN.checkReceive()) {
                        CAN.readMsgBuf(&len, buf);
                        if ((buf[0] & 0xF0) == 0x20 && (buf[0] & 0x0F) == nextFrame) {
                            int copyLen = min(len - 1, expectedLen - totalLen);
                            memcpy(buffer + totalLen, buf + 1, copyLen);
                            totalLen += copyLen;
                            nextFrame++;
                        }
                    }
                }
                break;
            }
        }
    }

    if (totalLen == 0) {
        Serial.println("No valid DTC response received.");
        return;
    }

    bool allZero = true;
    for (int i = 0; i < totalLen; i++) {
        if (buffer[i] != 0x00) {
            allZero = false;
            break;
        }
    }

    if (allZero) {
        Serial.println("No error codes (DTCs are all 0).");
    } else {
        Serial.println("DTCs found:");
        parseAndPrintDTCs(buffer, totalLen);
    }
}

void clearDTCs() {
    flushCANBuffer();
    sendClearDTCs();

    unsigned long timeout = millis();
    bool responseSeen = false;

    while (millis() - timeout < 3000) {
        if (CAN_MSGAVAIL == CAN.checkReceive()) {
            unsigned char len = 0;
            unsigned char buf[8];
            CAN.readMsgBuf(&len, buf);

            if (buf[1] == 0x44) {
                Serial.println("DTCs cleared successfully.");
                responseSeen = true;
                break;
            }
        }
    }

    if (!responseSeen) {
        Serial.println("No confirmation of DTC clear received.");
    }
}

void setup() {
    Serial.begin(115200);
    while (!Serial);

    pinMode(A3, OUTPUT);
    digitalWrite(A3, HIGH);

    while (CAN_OK != CAN.begin(CAN_500KBPS)) {
        Serial.println("CAN init fail, retry...");
        delay(100);
    }
    Serial.println("CAN init ok!");
    set_mask_filt();
}

void loop() {
    Serial.println("Click 'scan' to scan for DTCs or 'clear' to clear them.");

    String input;
    do {
        input = Serial.readStringUntil('\n');
        input.trim();
        input.toLowerCase();
    } while (!(input.startsWith("scan") || input.startsWith("clear")));

    if (input.startsWith("scan")) {
        scanDTCs();
    } else if (input.startsWith("clear")) {
        clearDTCs();
    }
}
