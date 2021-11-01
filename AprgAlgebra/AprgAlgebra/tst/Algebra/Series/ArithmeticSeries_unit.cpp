#include <Algebra/Series/ArithmeticSeries.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(ArithmeticSeriesTest, ConstructionWorksUsingFirstTermAndCommonDifference)
{
    ArithmeticSeries series(2, 3);

    EXPECT_DOUBLE_EQ(74, series.getValueAtIndex(24));
}

TEST(ArithmeticSeriesTest, ConstructionWorksUsing2ValuesAndCount)
{
    ArithmeticSeries series(27, 5, 48, 11);

    EXPECT_DOUBLE_EQ(9.5, series.getValueAtIndex(0));
}

TEST(ArithmeticSeriesTest, GetValueAtIndexWorks)
{
    ArithmeticSeries series(-15, 2);

    EXPECT_DOUBLE_EQ(-15, series.getValueAtIndex(0));
    EXPECT_DOUBLE_EQ(-13, series.getValueAtIndex(1));
    EXPECT_DOUBLE_EQ(-11, series.getValueAtIndex(2));
}

TEST(ArithmeticSeriesTest, GetSumWorks)
{
    ArithmeticSeries series(-15, 2);

    EXPECT_DOUBLE_EQ(420, series.getSum(0, 29));
    EXPECT_DOUBLE_EQ(435, series.getSum(1, 29));
    EXPECT_DOUBLE_EQ(448, series.getSum(2, 29));
}

}

}
