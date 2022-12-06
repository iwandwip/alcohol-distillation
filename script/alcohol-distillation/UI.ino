#include "UI.h"

#define BAUDRATE 9600

UserInterface ui;

void UserInterface::Init() {
        Serial.begin(BAUDRATE);
}

void UserInterface::Handler() {
}

void UserInterface::parseIn() {
        if (Serial.available() > 1) {
                String read[3];
                read[0] = Serial.readString();
                read[1] = parseStr(read[0], "#", 0);
                if (read[1] == "p1") {
                        read[2] = parseStr(read[0], "#", 1);
                } else if (read[1] == "p2") {
                        read[2] = parseStr(read[0], "#", 1);
                }
        }
}

String UserInterface::parseStr(String data,
                               char separator[],
                               int index) {
        int found = 0;
        int strIndex[] = { 0, -1 };
        int maxIndex = data.length() - 1;
        for (int i = 0; i <= maxIndex && found <= index; i++) {
                if (data.charAt(i) == separator[0] || i == maxIndex) {
                        found++;
                        strIndex[0] = strIndex[1] + 1;
                        strIndex[1] = (i == maxIndex) ? i + 1 : i;
                }
        }
        return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
