#include <Algebra/Series/Utilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(UtilitiesTest, GetSumOfArithmeticSeriesUsingFirstAndLastTermWorksWithExample1)
{
    Term firstTerm(1);
    Term lastTerm("n");
    Term count("n");

    Term expectedSum(Polynomial{Monomial(AlbaNumber(1)/2, {{"n", 2}}), Monomial(AlbaNumber(1)/2, {{"n", 1}})});
    EXPECT_EQ(expectedSum, getSumOfArithmeticSeriesUsingFirstAndLastTerm(firstTerm, lastTerm, count));
}

TEST(UtilitiesTest, GetSumOfArithmeticSeriesUsingFirstAndLastTermWorksWithExample2)
{
    Term firstTerm(4);
    Term lastTerm(Monomial(4, {{"n", 1}}));
    Term count("n");

    Term expectedSum(Polynomial{Monomial(2, {{"n", 2}}), Monomial(2, {{"n", 1}})});
    EXPECT_EQ(expectedSum, getSumOfArithmeticSeriesUsingFirstAndLastTerm(firstTerm, lastTerm, count));
}

TEST(UtilitiesTest, GetSumOfArithmeticSeriesUsingFirstAndLastTermWorksWithExample3)
{
    Term firstTerm(1);
    Term lastTerm(Polynomial{Monomial(3, {{"n", 1}}), Monomial(-2, {})});
    Term count(Polynomial{Monomial(1, {{"n", 1}}), Monomial(-1, {})});

    Term expectedSum(Polynomial{Monomial(AlbaNumber(3)/2, {{"n", 2}}), Monomial(-2, {{"n", 1}}), Monomial(AlbaNumber(1)/2, {})});
    EXPECT_EQ(expectedSum, getSumOfArithmeticSeriesUsingFirstAndLastTerm(firstTerm, lastTerm, count));
}


}

}

