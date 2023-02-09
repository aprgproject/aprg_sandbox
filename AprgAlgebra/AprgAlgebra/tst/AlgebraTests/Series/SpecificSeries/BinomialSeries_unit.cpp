#include <Algebra/Series/SpecificSeries/BinomialSeries.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::stringHelper;
using namespace std;

namespace alba
{

namespace algebra
{

TEST(BinomialSeriesTest, ConstructionWorks)
{
    BinomialSeries("x", AlbaNumber::createFraction(1, 3));
}

TEST(BinomialSeriesTest, GetMonomialPartWorks)
{
    BinomialSeries series("x", AlbaNumber::createFraction(1, 3));

    EXPECT_EQ(Term("x"), series.getMonomialPart());
}

TEST(BinomialSeriesTest, GetExponentWorks)
{
    BinomialSeries series("x", AlbaNumber::createFraction(1, 3));

    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 3)), series.getExponent());
}

TEST(BinomialSeriesTest, GetValueAtIndexWorks)
{
    BinomialSeries series("x", AlbaNumber::createFraction(1, 3));

    string stringToExpect1("1");
    string stringToExpect2("((1/3)[x] + 1)");
    string stringToExpect3("((-1/9)[x^2] + (1/3)[x] + 1)");
    string stringToExpect4("((5/81)[x^3] + (-1/9)[x^2] + (1/3)[x] + 1)");
    EXPECT_EQ(stringToExpect1, convertToString(series.getValueAtIndex(0)));
    EXPECT_EQ(stringToExpect2, convertToString(series.getValueAtIndex(1)));
    EXPECT_EQ(stringToExpect3, convertToString(series.getValueAtIndex(2)));
    EXPECT_EQ(stringToExpect4, convertToString(series.getValueAtIndex(3)));
}

}

}
