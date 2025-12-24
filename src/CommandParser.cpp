#include "../include/CommandParser.h"

#include <sstream>

Command CommandParser::parse(const std::string& input)
{
    std::istringstream iss(input);
    std::string cmd;

    iss >> cmd;

    if(cmd == "SET")
    {
        Command c;
        c.type = CommandType::SET;
        iss >> c.key;
        std::getline(iss, c.value);

        if(!c.value.empty() && c.value[0] == ' ')
        {
            c.value.erase(0,1);
        }
        if(c.key.empty() || c.value.empty())
        {
            c.type = CommandType::INVALID;
        }

        return c;
    }
    else if(cmd == "GET")
    {
        Command c;
        c.type = CommandType::GET;
        iss >> c.key;

        if(c.key.empty())
        {
            c.type = CommandType::INVALID;
        }

        return c;
    }
    else if(cmd == "DEL")
    {
        Command c;
        c.type = CommandType::DEL;
        iss >> c.key;

        if(c.key.empty())
        {
            c.type = CommandType::INVALID;
        }

        return c;
    }
    else if(cmd == "EXIT")
    {
        return { CommandType::EXIT };
    }

    return {};
}