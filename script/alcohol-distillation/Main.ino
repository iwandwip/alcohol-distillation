#include "Main.h"
#include "PID.h"
#include "Servo.h"

#define SERVO_P 9

Servo serv;

MainSys sys;
PID pid;

void MainSys::Init(void (*StartCallback)(void),
                   void (*Shutdown)(void)) {
        serv.attach(SERVO_P);
        StartCallback();
}

void MainSys::Handler() {
        serv.write(pid.GetResult());
}
