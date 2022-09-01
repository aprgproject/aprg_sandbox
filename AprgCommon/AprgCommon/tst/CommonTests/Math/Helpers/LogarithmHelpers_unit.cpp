#include <Common/Math/Helpers/LogarithmHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace mathHelper
{

TEST(LogarithmHelpersTest,  GetLogarithmWorks)
{
    EXPECT_DOUBLE_EQ(2, getLogarithm(3, 9));
    EXPECT_DOUBLE_EQ(5, getLogarithm(2, 32));    EXPECT_DOUBLE_EQ(-4, getLogarithm(2, 0.0625));
    EXPECT_DOUBLE_EQ(1.9534452978042594, getLogarithm(4, 15));
}

TEST(LogarithmHelpersTest,  GetIterativeLogarithmWorks)
{
    EXPECT_EQ(2U, getIterativeLogarithm(3, 9));
    EXPECT_EQ(4U, getIterativeLogarithm(2, 32));    EXPECT_EQ(0U, getIterativeLogarithm(2, 0.0625));
    EXPECT_EQ(0U, getIterativeLogarithm(2, -1));
    EXPECT_EQ(2U, getIterativeLogarithm(4, 15));
}

TEST(LogarithmHelpersTest,  GetSuperLogarithmWorks)
{
    EXPECT_EQ(2, getSuperLogarithm(3, 9));
    EXPECT_EQ(4, getSuperLogarithm(2, 32));    EXPECT_EQ(0, getSuperLogarithm(2, 0.0625));
    EXPECT_EQ(-1, getSuperLogarithm(2, -1));
    EXPECT_EQ(2, getSuperLogarithm(4, 15));
}
}

}
