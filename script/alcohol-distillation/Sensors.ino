#include "Sensors.h"
#include "UI.h"
#include "MQUnifiedsensor.h"
#include "max6675.h"
#include "Wire.h"

#define Board ("Arduino UNO")
#define Type ("MQ-3")

#define VoltRes (5)
#define ADCRes (10)
#define RatioCleanAir (60)
#define Mq3SamplingT 500

#define Exponential 1
#define Linear 0
#define Inf 1
#define Zero 0

#define T_SAMPLING 1000

#define getF(C) (C * 1.8) + 32
#define self (*this)

Sensor sens;

MQUnifiedsensor MQ3(Board, VoltRes, ADCRes, A3, Type);
MAX6675 th(4, 5, 6);

void Sensor::Init() {
        MQ3.setRegressionMethod(Exponential);
        MQ3.setA(0.3934);
        MQ3.setB(-1.504);
        MQ3.init();
}

void Sensor::Handler() {
        sens.Debug();
}

void Sensor::Debug() {
        if (millis() - dbgTmr >= 1000) {

                if (sens.mq3.getDebug()) {
                        Serial.print("Alcohol = ");
                        Serial.println(sens.mq3.getValue());
                        MQ3.serialDebug();
                }

                if (sens.thermo.getDebug()) {
                        Serial.print("Suhu = ");
                        Serial.println(sens.thermo.getValue());
                }

                dbgTmr = millis();
        }
}

void Sensor::mq3Sens::Calibrate(uint16_t ratioCleanAir) {
        Serial.print("Calibrating.");
        float calcR0 = 0;
        for (int i = 1; i <= 10; i++) {
                MQ3.update();
                calcR0 += MQ3.calibrate(ratioCleanAir);
                Serial.print(".");
        }
        MQ3.setR0(calcR0 / 10);

        if (isinf(calcR0)) errMsg(Inf);
        if (calcR0 == 0) errMsg(Zero);

        Serial.print("Done.");
        MQ3.serialDebug(false);
}

void Sensor::mq3Sens::readSens() {
        if (millis() - mqTmr >= Mq3SamplingT) {

                MQ3.update();
                self.value = float(MQ3.readSensor());

                mqTmr = millis();
        }
}

float Sensor::mq3Sens::getValue() {
        return float(self.value);
}

void Sensor::mq3Sens::Debug(bool _st) {
        self._debug = _st;
}

bool Sensor::mq3Sens::getDebug() {
        return self._debug;
}

void Sensor::mq3Sens::errMsg(bool err) {
        switch (err) {
                case Inf:
                        Serial.println("Open circuit detected");
                        while (1)
                                ;
                        break;
                case Zero:
                        Serial.println("Analog pin shorts");
                        while (1)
                                ;
                        break;
        }
}

void Sensor::thermoCouple::readSens() {
        if (millis() - thrTmr >= T_SAMPLING) {

                self.value = th.readCelsius();

                thrTmr = millis();
        }
}

void Sensor::thermoCouple::Debug(bool _st) {
        self._debug = _st;
}

bool Sensor::thermoCouple::getDebug() {
        return self._debug;
}

float Sensor::thermoCouple::getValue() {
        return self.value;
}

float Sensor::thermoCouple::getValueF() {
        return getF(self.value);
}

void Sensor::thermoCouple::errMsg() {
        Serial.print("Fault 0x");
        Serial.println();
}
