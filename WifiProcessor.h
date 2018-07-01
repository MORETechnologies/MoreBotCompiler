#ifndef WifiProcessor_h
#define WifiProcessor_h

#include "BotMessage.h"
#include <Arduino.h>
#include <SoftwareSerial.h>

class WifiProcessor
{
public:
    WifiProcessor(int rxPin, int txPin);
    WifiProcessor(int rxPin, int txPin, bool showDebug);
    void begin(String name);
    void read();
    bool isMessageAvailable();
    BotMessage dequeueMessage();

private:
    enum class ReadStep {
        Search,
        CommandType,
        ConnectionId,
        DataLength,
        Input
    };

    String getResponse();
    String readToDelimiter(char delimiter, bool& doesReach);

    SoftwareSerial wifi;
    String messageBuffer;
    int dataLength;
    bool showDebug;
    BotMessage message;
    ReadStep currentStep;
    static const long InitialBaudRate;
    static const int BaudRate;
    static const int ResponseTimeout;
};

#endif
