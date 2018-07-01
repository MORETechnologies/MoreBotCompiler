#ifndef MotorController_h
#define MotorController_h

#include "BotMessage.h"
#include <Arduino.h>

class MotorController
{
public:
    MotorController();
    MotorController(int speedPin, int directionPin1, int directionPin2);
    void setup();
    void setup(int speedPin, int directionPin1, int directionPin2);
    void rotateClockwise(int speed);
    void rotateCounterclockwise(int speed);
    int getId();
    void setId(int id);

private:
    int id;
    int speedPin;
    int directionPin1;
    int directionPin2;
};

#endif
