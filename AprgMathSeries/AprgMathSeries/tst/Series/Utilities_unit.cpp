#include <Series/Utilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace MathSeries
{

TEST(UtilitiesTest, GetSumOfArithmeticSeriesUsingFirstAndLastValueWorks)
{
    EXPECT_DOUBLE_EQ(60, getSumOfArithmeticSeriesUsingFirstAndLastValue(12, 18, 4));
}

}

}
