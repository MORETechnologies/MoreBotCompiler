#include <Arduino.h>
#include <MoreBotLibrary.h>

// Wifi pins
const int WifiRxPin = 12;
const int WifiTxPin = 13;

// Motor pins
const int LeftSpeedPin = 5;
const int LeftDirectionPin1 = 4;
const int LeftDirectionPin2 = 3;
const int RightSpeedPin = 6;
const int RightDirectionPin1 = 7;
const int RightDirectionPin2 = 8;

const int MaxProgramLength = 25;

WifiProcessor wifi(WifiRxPin, WifiTxPin);
DriveController driver(LeftSpeedPin, LeftDirectionPin1, LeftDirectionPin2, RightSpeedPin, RightDirectionPin1, RightDirectionPin2);
BotMessage botMessages[MaxProgramLength];
int currentIndex = 0;
int endIndex = 0;

void setup()
{
    Serial.begin(9600);
    wifi.begin("BotWifi");
}

void loop()
{
    wifi.read();

    if (wifi.isMessageAvailable()) {
        BotMessage message = wifi.dequeueMessage();
        Serial.println("Wifi message received [command: " + message.getCommand() + "] [data: " + message.getData() + "]");

        processMessage(message);
    }

    for (int i = 0; i < endIndex; i++) {
        runMessage(botMessages[i]);
    }
}

void processMessage(BotMessage& message)
{
    String command = message.getCommand();

    if (command == "begin") {
        currentIndex = 0;
        endIndex = 0;
    } else if (command == "move" || command == "sleep") {
        botMessages[currentIndex] = message;
        currentIndex++;
    } else if (command == "repeat" || command == "end") {
        botMessages[currentIndex] = message;
        endIndex = currentIndex;
        currentIndex++;
    }
}

void runMessage(BotMessage& message)
{
    String command = message.getCommand();

    if (command == "move") {
        int direction = message.getData().substring(0, 1).toInt();
        int speed = message.getData().substring(1).toInt();

        if (direction == 0) {
            driver.goForward(speed);
        } else if (direction == 1) {
            driver.turnLeft(speed);
        } else if (direction == 2) {
            driver.goBackward(speed);
        } else if (direction == 3) {
            driver.turnRight(speed);
        } else if (direction == 4) {
            driver.goForward(0);
        }
    } else if (command == "sleep") {
        delay(message.getData().toInt());
    } else if (command == "end") {
        endIndex = 0;
        driver.goForward(0);
    }
}