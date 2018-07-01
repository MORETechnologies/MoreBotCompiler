#ifndef DriveController_h
#define DriveController_h

#include "MotorController.h"
#include <Arduino.h>

class DriveController
{
public:
    DriveController(int leftSpeedPin, int leftDirectionPin1, int leftDirectionPin2, int rightSpeedPin, int rightDirectionPin1, int rightDirectionPin2);
    void setup();
    void goForward(int speed);
    void goBackward(int speed);
    void turnLeft(int speed);
    void turnRight(int speed);
    MotorController getLeftMotorController();
    MotorController getRightMotorController();

private:
    MotorController leftMotor;
    MotorController rightMotor;
};

#endif
