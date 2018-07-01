#ifndef BotMessage_h
#define BotMessage_h

#include <Arduino.h>

class BotMessage
{
public:
    BotMessage();
    BotMessage(String message);
    String getCommand();
    String getData();
    void setCommand(String command);
    void setData(String data);
    String serialize();

private:
    String command;
    String data;
    static const char Delimiter;
};

#endif
