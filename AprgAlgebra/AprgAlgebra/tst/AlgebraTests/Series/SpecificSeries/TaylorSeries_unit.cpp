#include <Algebra/Series/SpecificSeries/TaylorSeries.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>

#include <gtest/gtest.h>

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
    EXPECT_EQ(stringToExpect, series.getFormulaForTaylorSeries().getDisplayableString());
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
    EXPECT_EQ(stringToExpect1, series.getValueAtIndex(0, 0).getDisplayableString());
    EXPECT_EQ(stringToExpect2, series.getValueAtIndex(1, 0).getDisplayableString());
    EXPECT_EQ(stringToExpect3, series.getValueAtIndex(2, 0).getDisplayableString());
    EXPECT_EQ(stringToExpect4, series.getValueAtIndex(3, 0).getDisplayableString());
    EXPECT_EQ(stringToExpect5, series.getValueAtIndex(4, 0).getDisplayableString());
}

TEST(TaylorSeriesTest, GetValueForMaclaurinSeriesAtIndexWorks){
    Term formula(createExpressionIfPossible({getEAsATerm(), "^", "x"}));
    TaylorSeries series(formula, "x");
    string stringToExpect1("1");
    string stringToExpect2("(1[x] + 1)");
    string stringToExpect3("((1/2)[x^2] + 1[x] + 1)");
    string stringToExpect4("((1/6)[x^3] + (1/2)[x^2] + 1[x] + 1)");
    string stringToExpect5("((1/24)[x^4] + (1/6)[x^3] + (1/2)[x^2] + 1[x] + 1)");
    EXPECT_EQ(stringToExpect1, series.getValueForMaclaurinSeriesAtIndex(0).getDisplayableString());
    EXPECT_EQ(stringToExpect2, series.getValueForMaclaurinSeriesAtIndex(1).getDisplayableString());
    EXPECT_EQ(stringToExpect3, series.getValueForMaclaurinSeriesAtIndex(2).getDisplayableString());
    EXPECT_EQ(stringToExpect4, series.getValueForMaclaurinSeriesAtIndex(3).getDisplayableString());
    EXPECT_EQ(stringToExpect5, series.getValueForMaclaurinSeriesAtIndex(4).getDisplayableString());
}

}
}