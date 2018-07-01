#include "BotMessage.h"
#include <Arduino.h>

const char BotMessage::Delimiter = '|';

BotMessage::BotMessage()
    : command("")
    , data("")
{
}

BotMessage::BotMessage(String message)
{
    int commandSeparatorIndex = message.indexOf(Delimiter);

    if (commandSeparatorIndex >= 0) {
        command = message.substring(0, commandSeparatorIndex);
        data = message.substring(commandSeparatorIndex + 1);
    } else {
        command = "";
        data = "";
    }
}

String BotMessage::getCommand()
{
    return command;
}

String BotMessage::getData()
{
    return data;
}

void BotMessage::setCommand(String command)
{
    this->command = command;
}

void BotMessage::setData(String data)
{
    this->data = data;
}

String BotMessage::serialize()
{
    return command + "|" + data;
}