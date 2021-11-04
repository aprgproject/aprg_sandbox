#include <Algebra/Series/SpecificSeries/BinomialSeries.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(BinomialSeriesTest, ConstructionWorks)
{
    Term x("x");
    BinomialSeries(x, Term(AlbaNumber::createFraction(1, 3)));
}

TEST(BinomialSeriesTest, GetMonomialPartWorks)
{
    Term x("x");
    BinomialSeries series(x, Term(AlbaNumber::createFraction(1, 3)));

    EXPECT_EQ(x, series.getMonomialPart());
}

TEST(BinomialSeriesTest, GetExponentWorks)
{
    Term x("x");
    BinomialSeries series(x, Term(AlbaNumber::createFraction(1, 3)));

    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 3)), series.getExponent());
}

TEST(BinomialSeriesTest, GetValueAtIndexWorks)
{
    Term x("x");
    BinomialSeries series(x, Term(AlbaNumber::createFraction(1, 3)));

    string stringToExpect1("1");
    string stringToExpect2("((1/3)[x] + 1)");
    string stringToExpect3("((-1/9)[x^2] + (1/3)[x] + 1)");
    string stringToExpect4("((5/81)[x^3] + (-1/9)[x^2] + (1/3)[x] + 1)");
    EXPECT_EQ(stringToExpect1, series.getValueAtIndex(0).getDisplayableString());
    EXPECT_EQ(stringToExpect2, series.getValueAtIndex(1).getDisplayableString());
    EXPECT_EQ(stringToExpect3, series.getValueAtIndex(2).getDisplayableString());
    EXPECT_EQ(stringToExpect4, series.getValueAtIndex(3).getDisplayableString());
}

}

}
