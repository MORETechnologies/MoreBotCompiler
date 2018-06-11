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

const int MaxProgramLength = 100;

WifiProcessor wifi(WifiRxPin, WifiTxPin);
DriveController driver(LeftSpeedPin, LeftDirectionPin1, LeftDirectionPin2, RightSpeedPin, RightDirectionPin1, RightDirectionPin2);
BotMessage botMessages[MaxProgramLength];
int currentIndex = 0;
int endIndex = 0;

void setup()
{
    Serial.begin(9600);
    wifi.begin("TestCompiler");
}

void loop()
{
    wifi.read();

    if (wifi.isMessageAvailable()) {
        BotMessage message = wifi.dequeueMessage();
        if (showDebug) {
            Serial.println("Wifi message received [command: " + message.getCommand() + "] [data: " + message.getData() + "]");
        }

        processMessage(message);
    }

    // TODO run program

    delay(100);
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
        if (command == "repeat") {
            botMessages[currentIndex] = message;
        }
        endIndex = currentIndex;
        currentIndex++;
    }
}