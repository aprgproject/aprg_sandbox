#include <Algebra/Series/SeriesUtilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(SeriesUtilitiesTest, GetSumOfArithmeticSeriesUsingFirstAndLastTermWorksWithValues)
{
    EXPECT_EQ(Term(60), getSumOfArithmeticSeriesUsingFirstAndLastTerm(Term(12), Term(18), Term(4)));
}

TEST(SeriesUtilitiesTest, GetSumOfArithmeticSeriesUsingFirstAndLastTermWorksWithExample1)
{
    Term firstTerm(1);
    Term lastTerm("n");
    Term count("n");

    Term expectedSum(Polynomial{Monomial(AlbaNumber(1)/2, {{"n", 2}}), Monomial(AlbaNumber(1)/2, {{"n", 1}})});
    EXPECT_EQ(expectedSum, getSumOfArithmeticSeriesUsingFirstAndLastTerm(firstTerm, lastTerm, count));
}

TEST(SeriesUtilitiesTest, GetSumOfArithmeticSeriesUsingFirstAndLastTermWorksWithExample2)
{
    Term firstTerm(4);
    Term lastTerm(Monomial(4, {{"n", 1}}));
    Term count("n");

    Term expectedSum(Polynomial{Monomial(2, {{"n", 2}}), Monomial(2, {{"n", 1}})});
    EXPECT_EQ(expectedSum, getSumOfArithmeticSeriesUsingFirstAndLastTerm(firstTerm, lastTerm, count));
}

TEST(SeriesUtilitiesTest, GetSumOfArithmeticSeriesUsingFirstAndLastTermWorksWithExample3)
{
    Term firstTerm(1);
    Term lastTerm(Polynomial{Monomial(3, {{"n", 1}}), Monomial(-2, {})});
    Term count(Polynomial{Monomial(1, {{"n", 1}}), Monomial(-1, {})});

    Term expectedSum(Polynomial{Monomial(AlbaNumber(3)/2, {{"n", 2}}), Monomial(-2, {{"n", 1}}), Monomial(AlbaNumber(1)/2, {})});
    EXPECT_EQ(expectedSum, getSumOfArithmeticSeriesUsingFirstAndLastTerm(firstTerm, lastTerm, count));
}

TEST(SeriesUtilitiesTest, GetSumOfGeometricSeriesUsingFirstValueAndCommonMultiplierWorksWithValues)
{
    EXPECT_EQ(Term(10230), getSumOfGeometricSeriesUsingFirstValueAndCommonMultiplier(Term(10), Term(2), 10));
}

TEST(SeriesUtilitiesTest, GetInfiniteSumOfGeometricSeriesIfCommonMultiplierIsFractionalWorksWithValues)
{
    EXPECT_EQ(Term(20), getInfiniteSumOfGeometricSeriesIfCommonMultiplierIsFractional(Term(10), Term(AlbaNumber::createFraction(1, 2))));
}

}

}
