#include <Arduino.h>
#include <MoreBotLibrary.h>

WifiProcessor wifi(12, 13);
BotMessage botMessages[100];
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
        botMessages[currentIndex] = message;
        endIndex = currentIndex;
        currentIndex++;
    }
}