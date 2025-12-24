#include <gtest/gtest.h>
#include "../include/CommandParser.h"

TEST(CommandParser, ParseSet)
{
    auto cmd = CommandParser::parse("SET key value");

    EXPECT_EQ(cmd.type, CommandType::SET);
    EXPECT_EQ(cmd.key, "key");
    EXPECT_EQ(cmd.value, "value");
}

TEST(CommandParser, ParseGet)
{
    auto cmd = CommandParser::parse("GET mykey");

    EXPECT_EQ(cmd.type, CommandType::GET);
    EXPECT_EQ(cmd.key, "mykey");
}

TEST(CommandParser, ParseInvalid)
{
    auto cmd = CommandParser::parse("UNKNOWN cmd");

    EXPECT_EQ(cmd.type, CommandType::INVALID);
}
