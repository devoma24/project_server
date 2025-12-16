#pragma once
#include <string>

enum class CommandType
{
    SET,
    GET,
    DEL,
    EXIT,
    INVALID
};

struct Command
{
    CommandType type = CommandType::INVALID;
    std::string key;
    std::string value;
};