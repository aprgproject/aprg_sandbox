#include <Macros/AlbaMacroArgumentCounter.hpp>

#include <gtest/gtest.h>

using namespace std;

TEST(AlbaMacroArgumentCounter, IntegerTest)
{
    EXPECT_EQ(ALBA_COUNT_ARGS(1), 1);
    EXPECT_EQ(ALBA_COUNT_ARGS(8237, 23458, 28749), 3);
    EXPECT_EQ(ALBA_COUNT_ARGS(0x1, 0x2, 0x3, 0x4), 4);
}

TEST(AlbaMacroArgumentCounter, VariableTest)
{
    int i1=1, i2=2, i3=3;
    EXPECT_EQ(ALBA_COUNT_ARGS(i1), 1);
    EXPECT_EQ(ALBA_COUNT_ARGS(i1, i2), 2);
    EXPECT_EQ(ALBA_COUNT_ARGS(i1, i2, i3), 3);
    i1=i2; i2=i3; i3=i1;
}

TEST(AlbaMacroArgumentCounter,StringTest)
{
    EXPECT_EQ(ALBA_COUNT_ARGS("one"), 1);
    EXPECT_EQ(ALBA_COUNT_ARGS("one", "two"), 2);
    EXPECT_EQ(ALBA_COUNT_ARGS("one", "two", "three"), 3);
}



