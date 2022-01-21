#include <Algebra/Series/Utilities/SeriesUtilities.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(SeriesUtilitiesTest, IsAxiomOfCompletenessTrueWorks)
{
    Term n("n");
    Term numerator("n");
    Term denominator(Polynomial{Monomial(2, {{"n", 1}}), Monomial(1, {})});
    Term formula(createExpressionIfPossible({numerator, "/", denominator}));
    SeriesBasedOnFormula series(formula, "n");

    EXPECT_TRUE(isAxiomOfCompletenessTrue(series));
}

TEST(SeriesUtilitiesTest, IsBoundedMonotonicSeriesConvergentWorks)
{
    Term n("n");
    Term numerator("n");
    Term denominator(Polynomial{Monomial(2, {{"n", 1}}), Monomial(1, {})});
    Term formula(createExpressionIfPossible({numerator, "/", denominator}));
    SeriesBasedOnFormula series(formula, "n");

    EXPECT_TRUE(isBoundedMonotonicSeriesConvergent(series));
}

TEST(SeriesUtilitiesTest, IsConvergentMonotonicSeriesBoundedWorks)
{
    Term n("n");
    Term numerator("n");
    Term denominator(Polynomial{Monomial(2, {{"n", 1}}), Monomial(1, {})});
    Term formula(createExpressionIfPossible({numerator, "/", denominator}));
    SeriesBasedOnFormula series(formula, "n");

    EXPECT_TRUE(isConvergentMonotonicSeriesBounded(series));
}

TEST(SeriesUtilitiesTest, IsConvergentUsingComparisonTestWorks)
{
    Term n("n");
    Term numeratorToTest(4);
    Term denominatorToTest(createExpressionIfPossible({3, "^", n, "^", 1}));
    Term formulaToTest(createExpressionIfPossible({numeratorToTest, "/", denominatorToTest}));
    SeriesBasedOnSummation seriesToTest(formulaToTest, "n");
    Term convergentNumerator(4);
    Term convergentDenominator(createExpressionIfPossible({3, "^", n}));
    Term convergentFormula(createExpressionIfPossible({convergentNumerator, "/", convergentDenominator}));
    SeriesBasedOnSummation convergentSeries(convergentFormula, "n");

    EXPECT_TRUE(isConvergentUsingComparisonTest(seriesToTest, convergentSeries, 10));
}

TEST(SeriesUtilitiesTest, IsDivergentUsingComparisonTestWorks)
{
    Term n("n");
    Term numeratorToTest(1);
    Term denominatorToTest(Monomial(1, {{"n", AlbaNumber::createFraction(1, 2)}}));
    Term formulaToTest(createExpressionIfPossible({numeratorToTest, "/", denominatorToTest}));
    SeriesBasedOnSummation seriesToTest(formulaToTest, "n");
    Term divergentNumerator(1);
    Term divergentDenominator("n");
    Term divergentFormula(createExpressionIfPossible({divergentNumerator, "/", divergentDenominator}));
    SeriesBasedOnSummation divergentSeries(divergentFormula, "n");

    EXPECT_TRUE(isDivergentUsingComparisonTest(seriesToTest, divergentSeries, 10));
}

TEST(SeriesUtilitiesTest, PerformLimitComparisonTestWorks)
{
    Term n("n");
    Term numerator1(1);
    Term denominator1(Monomial(1, {{"n", AlbaNumber::createFraction(1, 2)}}));
    Term formula1(createExpressionIfPossible({numerator1, "/", denominator1}));
    SeriesBasedOnSummation series1(formula1, "n");
    Term numerator2(1);
    Term denominator2("n");
    Term formula2(createExpressionIfPossible({numerator2, "/", denominator2}));
    SeriesBasedOnSummation series2(formula2, "n");

    bool isConvergent(false);
    bool isDivergent(false);
    performLimitComparisonTest(isConvergent, isDivergent, series1, series2, "n");

    EXPECT_FALSE(isConvergent);
    EXPECT_TRUE(isDivergent);
}

TEST(SeriesUtilitiesTest, PerformIntegralTestWorksOnPSeriesWithPowerIsOneHalf)
{
    Term numerator(1);
    Term denominator(Monomial(1, {{"n", AlbaNumber::createFraction(1, 2)}}));
    Term formula(createExpressionIfPossible({numerator, "/", denominator}));
    SeriesBasedOnSummation series(formula, "n");

    bool isConvergent(false);
    bool isDivergent(false);
    performIntegralTest(isConvergent, isDivergent, series, "n");

    EXPECT_FALSE(isConvergent);
    EXPECT_TRUE(isDivergent);
}

TEST(SeriesUtilitiesTest, PerformIntegralTestWorksOnPSeriesWithPowerIsTwo)
{
    Term numerator(1);
    Term denominator(Monomial(1, {{"n", 2}}));
    Term formula(createExpressionIfPossible({numerator, "/", denominator}));
    SeriesBasedOnSummation series(formula, "n");

    bool isConvergent(false);
    bool isDivergent(false);
    performIntegralTest(isConvergent, isDivergent, series, "n");

    EXPECT_TRUE(isConvergent);
    EXPECT_FALSE(isDivergent);
}

TEST(SeriesUtilitiesTest, PerformRatioTestWorksWhenConvergent)
{
    Term n("n");
    Term numerator("n");
    Term denominator(createExpressionIfPossible({2, "^", n}));
    Term formula(createExpressionIfPossible({numerator, "/", denominator}));
    SeriesBasedOnSummation series(formula, "n");

    bool isConvergent(false);
    bool isDivergent(false);
    performRatioTest(isConvergent, isDivergent, series, "n");

    EXPECT_TRUE(isConvergent);
    EXPECT_FALSE(isDivergent);
}

TEST(SeriesUtilitiesTest, PerformRatioTestWorksWhenConvergentOrDivergent)
{
    Term numerator(Polynomial{Monomial(1, {{"n", 1}}), Monomial(2, {})});
    Term denominator(Polynomial{Monomial(1, {{"n", 2}}), Monomial(1, {{"n", 1}})});
    Term formula(createExpressionIfPossible({numerator, "/", denominator}));
    SeriesBasedOnSummation series(formula, "n");

    bool isConvergent(false);
    bool isDivergent(false);
    performRatioTest(isConvergent, isDivergent, series, "n");

    EXPECT_FALSE(isConvergent);
    EXPECT_FALSE(isDivergent);
}

TEST(SeriesUtilitiesTest, PerformRootTestWorks)
{
    Term n("n");
    Term exponentNumerator(Polynomial{Monomial(2, {{"n", 1}}), Monomial(1, {})});
    Term exponentDenominator(Polynomial{Monomial(2, {{"n", 1}})});
    Term numerator(createExpressionIfPossible({3, "^", exponentNumerator}));
    Term denominator(createExpressionIfPossible({n, "^", exponentDenominator}));
    Term formula(createExpressionIfPossible({numerator, "/", denominator}));
    SeriesBasedOnSummation series(formula, "n");

    bool isConvergent(false);
    bool isDivergent(false);
    performRootTest(isConvergent, isDivergent, series, "n");

    EXPECT_TRUE(isConvergent);
    EXPECT_FALSE(isDivergent);
}

TEST(SeriesUtilitiesTest, GetSumOfArithmeticSeriesUsingFirstAndLastTermWorksWithValues)
{
    EXPECT_EQ(Term(60), getSumOfArithmeticSeriesUsingFirstAndLastTerm(12, 18, 4));
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
    EXPECT_EQ(Term(10230), getSumOfGeometricSeriesUsingFirstValueAndCommonMultiplier(10, 2, 10));
}

TEST(SeriesUtilitiesTest, GetInfiniteSumOfGeometricSeriesIfCommonMultiplierIsFractionalWorksWithValues)
{
    EXPECT_EQ(Term(20), getInfiniteSumOfGeometricSeriesIfCommonMultiplierIsFractional(10, AlbaNumber::createFraction(1, 2)));
}

TEST(SeriesUtilitiesTest, GetEToTheXPowerSeriesWorks)
{
    PowerSeries series(getEToTheXPowerSeries());

    string stringToExpect1("1");
    string stringToExpect2("(1[x] + 1)");
    string stringToExpect3("((1/2)[x^2] + 1[x] + 1)");
    string stringToExpect4("((1/6)[x^3] + (1/2)[x^2] + 1[x] + 1)");
    string stringToExpect5("(1/factorial(n)*(x^n))");
    EXPECT_FALSE(series.isSummationModelValid());
    EXPECT_EQ(stringToExpect1, series.getValueAtIndex(0).getDisplayableString());
    EXPECT_EQ(stringToExpect2, series.getValueAtIndex(1).getDisplayableString());
    EXPECT_EQ(stringToExpect3, series.getValueAtIndex(2).getDisplayableString());
    EXPECT_EQ(stringToExpect4, series.getValueAtIndex(3).getDisplayableString());
    EXPECT_EQ(stringToExpect5, series.getFormulaForEachTermInSummation().getDisplayableString());
}

}

}
