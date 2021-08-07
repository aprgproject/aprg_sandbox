#include <Series/GeometricSeries.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace MathSeries
{

TEST(GeometricSeriesTest, ConstructionWorksUsingFirstTermAndCommonDifference)
{
    GeometricSeries series(-8, -0.5);

    EXPECT_DOUBLE_EQ(0.015625, series.getValueAtIndex(9));
}

TEST(GeometricSeriesTest, ConstructionWorksUsing2ValuesAndCount)
{
    GeometricSeries series(4, 1, -2, 2);

    EXPECT_DOUBLE_EQ(-8, series.getValueAtIndex(0));
}

TEST(GeometricSeriesTest, GetValueAtIndexWorks)
{
    GeometricSeries series(-15, 2);

    EXPECT_DOUBLE_EQ(-15, series.getValueAtIndex(0));
    EXPECT_DOUBLE_EQ(-30, series.getValueAtIndex(1));
    EXPECT_DOUBLE_EQ(-60, series.getValueAtIndex(2));
}

TEST(GeometricSeriesTest, GetSumWorks)
{
    GeometricSeries series(1, 4);

    EXPECT_DOUBLE_EQ(21845, series.getSum(0, 7));
    EXPECT_DOUBLE_EQ(21844, series.getSum(1, 7));
    EXPECT_DOUBLE_EQ(21840, series.getSum(2, 7));
}

TEST(GeometricSeriesTest, GetInfiniteSumIfMultiplierIsFractionalWorks)
{
    GeometricSeries series(0.5, 0.5);

    EXPECT_DOUBLE_EQ(1, series.getInfiniteSumIfMultiplierIsFractional(0));
    EXPECT_DOUBLE_EQ(0.5, series.getInfiniteSumIfMultiplierIsFractional(1));
    EXPECT_DOUBLE_EQ(0.25, series.getInfiniteSumIfMultiplierIsFractional(2));
}

}

}

