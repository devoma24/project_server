#include <gtest/gtest.h>
#include "../include/Storage.h"

TEST(Storage, SetAndGet)
{
    Storage s;

    s.set("a", "1");
    auto val = s.get("a");

    ASSERT_TRUE(val.has_value());
    EXPECT_EQ(*val, "1");
}

TEST(Storage, Delete)
{
    Storage s;

    s.set("a", "1");
    EXPECT_TRUE(s.del("a"));
    EXPECT_FALSE(s.get("a").has_value());
}

TEST(Storage, DeleteMissing)
{
    Storage s;
    EXPECT_FALSE(s.del("missing"));
}
