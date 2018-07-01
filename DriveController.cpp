#include "DriveController.h"
#include "MotorController.h"
#include <Arduino.h>

DriveController::DriveController(int leftSpeedPin, int leftDirectionPin1, int leftDirectionPin2, int rightSpeedPin, int rightDirectionPin1, int rightDirectionPin2)
    : leftMotor(leftSpeedPin, leftDirectionPin1, leftDirectionPin2)
    , rightMotor(rightSpeedPin, rightDirectionPin1, rightDirectionPin2)
{
}

void DriveController::setup()
{
    leftMotor.setup();
    rightMotor.setup();
}

void DriveController::goForward(int speed)
{
    leftMotor.rotateClockwise(speed);
    rightMotor.rotateClockwise(speed);
}

void DriveController::goBackward(int speed)
{
    leftMotor.rotateCounterclockwise(speed);
    rightMotor.rotateCounterclockwise(speed);
}

void DriveController::turnLeft(int speed)
{
    leftMotor.rotateCounterclockwise(speed);
    rightMotor.rotateClockwise(speed);
}

void DriveController::turnRight(int speed)
{
    leftMotor.rotateClockwise(speed);
    rightMotor.rotateCounterclockwise(speed);
}

MotorController DriveController::getLeftMotorController()
{
    return leftMotor;
}

MotorController DriveController::getRightMotorController()
{
    return rightMotor;
}