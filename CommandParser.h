#pragma once
#include "Command.h"
#include <string>

class CommandParser
{
    public:
    static Command parse(const std::string& input);
};