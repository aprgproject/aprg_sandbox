#include <Algebra/Series/SpecificSeries/TaylorSeries.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::stringHelper;
using namespace std;

namespace alba
{

namespace algebra
{

TEST(TaylorSeriesTest, ConstructionWorks)
{
    Term formula(createExpressionIfPossible({getEAsATerm(), "^", "x"}));
    TaylorSeries(formula, "x");
}

TEST(TaylorSeriesTest, GetFormulaForTaylorSeriesWorks)
{
    Term formula(createExpressionIfPossible({getEAsATerm(), "^", "x"}));
    TaylorSeries series(formula, "x");

    string stringToExpect("((e)^x)");
    EXPECT_EQ(stringToExpect, convertToString(series.getFormulaForTaylorSeries()));
}

TEST(TaylorSeriesTest, GetValueAtIndexWorks)
{
    // taylors formula: f(b) = f(a) + f'(a)*(b-a)/1! + f''(a)*(b-a)^2/2! ...
    // Given that "starting value" is 0 and "value to approach" is x, the formula for e^x becomes:
    // e^x = 1 + x + x^2/2! + x^3/3! + x^4/4! + x^5/5! ...

    Term formula(createExpressionIfPossible({getEAsATerm(), "^", "x"}));
    TaylorSeries series(formula, "x");

    string stringToExpect1("1");
    string stringToExpect2("(1[x] + 1)");
    string stringToExpect3("((1/2)[x^2] + 1[x] + 1)");
    string stringToExpect4("((1/6)[x^3] + (1/2)[x^2] + 1[x] + 1)");
    string stringToExpect5("((1/24)[x^4] + (1/6)[x^3] + (1/2)[x^2] + 1[x] + 1)");
    EXPECT_EQ(stringToExpect1, convertToString(series.getValueAtIndex(0, 0)));
    EXPECT_EQ(stringToExpect2, convertToString(series.getValueAtIndex(1, 0)));
    EXPECT_EQ(stringToExpect3, convertToString(series.getValueAtIndex(2, 0)));
    EXPECT_EQ(stringToExpect4, convertToString(series.getValueAtIndex(3, 0)));
    EXPECT_EQ(stringToExpect5, convertToString(series.getValueAtIndex(4, 0)));
}

TEST(TaylorSeriesTest, GetValueForMaclaurinSeriesAtIndexWorks)
{
    Term formula(createExpressionIfPossible({getEAsATerm(), "^", "x"}));
    TaylorSeries series(formula, "x");

    string stringToExpect1("1");
    string stringToExpect2("(1[x] + 1)");
    string stringToExpect3("((1/2)[x^2] + 1[x] + 1)");
    string stringToExpect4("((1/6)[x^3] + (1/2)[x^2] + 1[x] + 1)");
    string stringToExpect5("((1/24)[x^4] + (1/6)[x^3] + (1/2)[x^2] + 1[x] + 1)");
    EXPECT_EQ(stringToExpect1, convertToString(series.getValueForMaclaurinSeriesAtIndex(0)));
    EXPECT_EQ(stringToExpect2, convertToString(series.getValueForMaclaurinSeriesAtIndex(1)));
    EXPECT_EQ(stringToExpect3, convertToString(series.getValueForMaclaurinSeriesAtIndex(2)));
    EXPECT_EQ(stringToExpect4, convertToString(series.getValueForMaclaurinSeriesAtIndex(3)));
    EXPECT_EQ(stringToExpect5, convertToString(series.getValueForMaclaurinSeriesAtIndex(4)));
}

}

}
