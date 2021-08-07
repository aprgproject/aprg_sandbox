#include <Series/Utilities.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba{

namespace MathSeries
{

TEST(UtilitiesTest, GetSumOfArithmeticSeriesUsingFirstAndLastTermWorks)
{
    EXPECT_DOUBLE_EQ(60, getSumOfArithmeticSeriesUsingFirstAndLastTerm(12, 18, 4));
}

}

}

