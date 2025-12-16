#pragma once
#include "Command.h"
#include <string>

class CommandParser
{
    static Command parse(const std::string& input);
};