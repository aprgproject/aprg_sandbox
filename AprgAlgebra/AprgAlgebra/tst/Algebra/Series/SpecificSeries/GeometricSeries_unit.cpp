#include <Algebra/Series/GeometricSeries.hpp>
#include <Algebra/Series/SeriesUtilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(GeometricSeriesTest, ConstructionWorksUsingFirstTermAndCommonDifference)
{
    GeometricSeries series(-8, AlbaNumber::createFraction(-1, 2));

    EXPECT_EQ(Term(-8), series.getValueAtIndex(0));
    EXPECT_EQ(Term(0.015625), series.getValueAtIndex(9));
}

TEST(GeometricSeriesTest, ConstructionWorksUsing2ValuesAndCount)
{
    GeometricSeries series(4, 1, -2, 2);

    EXPECT_EQ(Term(-8), series.getValueAtIndex(0));
    EXPECT_EQ(Term(0.015625), series.getValueAtIndex(9));
}

TEST(GeometricSeriesTest, GetValueAtIndexWorks)
{
    GeometricSeries series(-15, 2);

    EXPECT_EQ(Term(-15), series.getValueAtIndex(0));
    EXPECT_EQ(Term(-30), series.getValueAtIndex(1));
    EXPECT_EQ(Term(-60), series.getValueAtIndex(2));
}

TEST(GeometricSeriesTest, GetSumWorks)
{
    GeometricSeries series(1, 4);

    EXPECT_EQ(Term(21845), series.getSum(0, 7));
    EXPECT_EQ(Term(21844), series.getSum(1, 7));
    EXPECT_EQ(Term(21840), series.getSum(2, 7));
}

TEST(GeometricSeriesTest, GetInfiniteSumWorks)
{
    GeometricSeries series(AlbaNumber::createFraction(1, 2), AlbaNumber::createFraction(1,2));

    EXPECT_EQ(Term(1), series.getInfiniteSumStartingFrom(0));
    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 2)), series.getInfiniteSumStartingFrom(1));
    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 4)), series.getInfiniteSumStartingFrom(2));
}

TEST(GeometricSeriesTest, GetSumIsEqualToFormulaInUtilities)
{
    GeometricSeries series(1, 4);

    Term sumFromSeries(series.getSum(0, 7));
    Term sumFromFormula(getSumOfGeometricSeriesUsingFirstValueAndCommonMultiplier(Term(1), Term(4), 8));

    EXPECT_EQ(sumFromSeries, sumFromFormula);
}

TEST(GeometricSeriesTest, GetInfiniteSumIsEqualToFormulaInUtilities)
{
    GeometricSeries series(AlbaNumber::createFraction(1, 2), AlbaNumber::createFraction(1,2));

    Term sumFromSeries(series.getInfiniteSumStartingFrom(2));
    Term sumFromFormula(
                getInfiniteSumOfGeometricSeriesIfCommonMultiplierIsFractional(
                    Term(AlbaNumber::createFraction(1, 8)),
                    Term(AlbaNumber::createFraction(1, 2))));

    EXPECT_EQ(sumFromSeries, sumFromFormula);
}

TEST(GeometricSeriesTest, IsConvergentWorks)
{
    // Geometric diverges when less than one
    GeometricSeries seriesWithMultiplierLessThanOne(1, AlbaNumber::createFraction(1, 2));
    GeometricSeries seriesWithMultiplierEqualsToOne(1, 1);
    GeometricSeries seriesWithMultiplierMoreThanOne(1, 2);

    EXPECT_TRUE(seriesWithMultiplierLessThanOne.isConvergent());
    EXPECT_TRUE(seriesWithMultiplierEqualsToOne.isConvergent());
    EXPECT_FALSE(seriesWithMultiplierMoreThanOne.isConvergent());
}

}

}
