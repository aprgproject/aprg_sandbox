#include <Algebra/Series/SpecificSeries/ArithmeticSeries.hpp>
#include <Algebra/Series/Utilities/SeriesUtilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(ArithmeticSeriesTest, ConstructionWorksUsingFirstTermAndCommonDifference)
{
    ArithmeticSeries series(2, 3);

    EXPECT_EQ(Term(74), series.getValueAtIndex(24));
}

TEST(ArithmeticSeriesTest, ConstructionWorksUsing2ValuesAndCount)
{
    ArithmeticSeries series(27, 5, 48, 11);

    EXPECT_EQ(Term(AlbaNumber::createFraction(19, 2)), series.getValueAtIndex(0));
}

TEST(ArithmeticSeriesTest, GetValueAtIndexWorks)
{
    ArithmeticSeries series(-15, 2);

    EXPECT_EQ(Term(-15), series.getValueAtIndex(0));
    EXPECT_EQ(Term(-13), series.getValueAtIndex(1));
    EXPECT_EQ(Term(-11), series.getValueAtIndex(2));
}

TEST(ArithmeticSeriesTest, GetSumWorks)
{
    ArithmeticSeries series(-15, 2);

    EXPECT_EQ(Term(420), series.getSum(0, 29));
    EXPECT_EQ(Term(435), series.getSum(1, 29));
    EXPECT_EQ(Term(448), series.getSum(2, 29));
}

TEST(ArithmeticSeriesTest, GetSumIsEqualToFormulaInUtilities)
{
    ArithmeticSeries series(-15, 2);

    Term sumFromSeries(series.getSum(0, 29));
    Term sumFromFormula(getSumOfArithmeticSeriesUsingFirstAndLastTerm(-15, 43, 30));

    EXPECT_EQ(sumFromSeries, sumFromFormula);
}
}

}