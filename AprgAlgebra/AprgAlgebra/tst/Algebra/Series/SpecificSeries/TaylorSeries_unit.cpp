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
    Term x("x");
    Term formula(createExpressionIfPossible({getEAsTerm(), Term("^"), x}));
    TaylorSeries(formula, "x");
}

TEST(TaylorSeriesTest, GetFormulaForTaylorSeriesWorks)
{
    Term x("x");
    Term formula(createExpressionIfPossible({getEAsTerm(), Term("^"), x}));
    TaylorSeries series(formula, "x");

    string stringToExpect("((e)^x)");
    EXPECT_EQ(stringToExpect, series.getFormulaForTaylorSeries().getDisplayableString());
}

TEST(TaylorSeriesTest, GetValueAtIndexWorks)
{
    Term x("x");
    Term formula(createExpressionIfPossible({getEAsTerm(), Term("^"), x}));
    TaylorSeries series(formula, "x");

    string stringToExpect1("1");
    string stringToExpect2("(e)[x]");
    string stringToExpect3("(3.694528049465325[x^2] + -7.38905609893065[x] + 7.38905609893065)");
    EXPECT_EQ(stringToExpect1, series.getValueAtIndex(0, Term(0)).getDisplayableString());
    EXPECT_EQ(stringToExpect2, series.getValueAtIndex(1, Term(1)).getDisplayableString());
    EXPECT_EQ(stringToExpect3, series.getValueAtIndex(2, Term(2)).getDisplayableString());
}

TEST(TaylorSeriesTest, GetValueForMaclaurinSeriesAtIndexWorks)
{
    Term x("x");
    Term formula(createExpressionIfPossible({getEAsTerm(), Term("^"), x}));
    TaylorSeries series(formula, "x");

    string stringToExpect1("1");
    string stringToExpect2("(1[x] + 1)");
    string stringToExpect3("((1/2)[x^2] + 1[x] + 1)");
    string stringToExpect4("((1/6)[x^3] + (1/2)[x^2] + 1[x] + 1)");
    EXPECT_EQ(stringToExpect1, series.getValueForMaclaurinSeriesAtIndex(0).getDisplayableString());
    EXPECT_EQ(stringToExpect2, series.getValueForMaclaurinSeriesAtIndex(1).getDisplayableString());
    EXPECT_EQ(stringToExpect3, series.getValueForMaclaurinSeriesAtIndex(2).getDisplayableString());
    EXPECT_EQ(stringToExpect4, series.getValueForMaclaurinSeriesAtIndex(3).getDisplayableString());
}

}

}
