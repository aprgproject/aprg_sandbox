#include <ArithmeticSeries.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace MathSeries
{

TEST(ArithmeticSeriesTest, ConstructionWorksUsingFirstTermAndCommonDifference)
{
    ArithmeticSeries series(2, 3);

    EXPECT_DOUBLE_EQ(74, series.getValueAt(25));
}

TEST(ArithmeticSeriesTest, ConstructionWorksUsing2ValuesAndCount)
{
    ArithmeticSeries series(27, 6, 48, 12);

    EXPECT_DOUBLE_EQ(9.5, series.getValueAt(1));
}

TEST(ArithmeticSeriesTest, GetValueAtWorks)
{
    ArithmeticSeries series(-15, 2);

    EXPECT_DOUBLE_EQ(-11, series.getValueAt(3));
}

TEST(ArithmeticSeriesTest, GetSumWorks)
{
    ArithmeticSeries series(-15, 2);

    EXPECT_DOUBLE_EQ(420, series.getSum(1, 30));
}

}

}

