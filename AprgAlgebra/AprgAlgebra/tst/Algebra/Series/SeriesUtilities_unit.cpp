#include <Algebra/Series/SeriesUtilities.hpp>
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
    Term numerator(n);
    Term denominator(Polynomial{Monomial(2, {{"n", 1}}), Monomial(1, {})});
    Term formula(createExpressionIfPossible({numerator, Term("/"), denominator}));
    SeriesBasedOnTerm series(formula, "n");

    EXPECT_TRUE(isAxiomOfCompletenessTrue(series));
}

TEST(SeriesUtilitiesTest, IsBoundedMonotonicSeriesConvergentWorks)
{
    Term n("n");
    Term numerator(n);
    Term denominator(Polynomial{Monomial(2, {{"n", 1}}), Monomial(1, {})});
    Term formula(createExpressionIfPossible({numerator, Term("/"), denominator}));
    SeriesBasedOnTerm series(formula, "n");

    EXPECT_TRUE(isBoundedMonotonicSeriesConvergent(series));
}

TEST(SeriesUtilitiesTest, IsConvergentMonotonicSeriesBoundedWorks)
{
    Term n("n");
    Term numerator(n);
    Term denominator(Polynomial{Monomial(2, {{"n", 1}}), Monomial(1, {})});
    Term formula(createExpressionIfPossible({numerator, Term("/"), denominator}));
    SeriesBasedOnTerm series(formula, "n");

    EXPECT_TRUE(isConvergentMonotonicSeriesBounded(series));
}

TEST(SeriesUtilitiesTest, IsConvergentUsingComparisonTestWorks)
{
    Term n("n");
    Term numeratorToTest(4);
    Term denominatorToTest(createExpressionIfPossible({Term(3), Term("^"), n, Term("^"), Term(1)}));
    Term formulaToTest(createExpressionIfPossible({numeratorToTest, Term("/"), denominatorToTest}));
    SeriesBasedOnSummation seriesToTest(formulaToTest, "n");
    Term convergentNumerator(4);
    Term convergentDenominator(createExpressionIfPossible({Term(3), Term("^"), n}));
    Term convergentFormula(createExpressionIfPossible({convergentNumerator, Term("/"), convergentDenominator}));
    SeriesBasedOnSummation convergentSeries(convergentFormula, "n");

    EXPECT_TRUE(isConvergentUsingComparisonTest(seriesToTest, convergentSeries, 10));
}

TEST(SeriesUtilitiesTest, IsDivergentUsingComparisonTestWorks)
{
    Term n("n");
    Term numeratorToTest(1);
    Term denominatorToTest(Monomial(1, {{"n", AlbaNumber::createFraction(1, 2)}}));
    Term formulaToTest(createExpressionIfPossible({numeratorToTest, Term("/"), denominatorToTest}));
    SeriesBasedOnSummation seriesToTest(formulaToTest, "n");
    Term divergentNumerator(1);
    Term divergentDenominator(n);
    Term divergentFormula(createExpressionIfPossible({divergentNumerator, Term("/"), divergentDenominator}));
    SeriesBasedOnSummation divergentSeries(divergentFormula, "n");

    EXPECT_TRUE(isDivergentUsingComparisonTest(seriesToTest, divergentSeries, 10));
}

TEST(SeriesUtilitiesTest, PerformLimitComparisonTestWorks)
{
    Term n("n");
    Term numerator1(1);
    Term denominator1(Monomial(1, {{"n", AlbaNumber::createFraction(1, 2)}}));
    Term formula1(createExpressionIfPossible({numerator1, Term("/"), denominator1}));
    SeriesBasedOnSummation series1(formula1, "n");
    Term numerator2(1);
    Term denominator2(n);
    Term formula2(createExpressionIfPossible({numerator2, Term("/"), denominator2}));
    SeriesBasedOnSummation series2(formula2, "n");

    bool isConvergent(false);
    bool isDivergent(false);
    performLimitComparisonTest(isConvergent, isDivergent, series1, series2, "n");

    EXPECT_FALSE(isConvergent);
    EXPECT_TRUE(isDivergent);
}

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
