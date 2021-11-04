#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Series/GeneralSeries/SeriesBasedOnFormula.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba
{

namespace algebra
{

TEST(SeriesBasedOnFormulaTest, ConstructionWorks)
{
    SeriesBasedOnFormula series(Term("n"), "n");
}

TEST(SeriesBasedOnFormulaTest, IsConvergentWorksOnConvergentSeries)
{
    Term numerator(Polynomial{Monomial(4, {{"n", 2}})});
    Term denominator(Polynomial{Monomial(2, {{"n", 2}}), Monomial(1, {})});
    Term formula(createExpressionIfPossible({numerator, Term("/"), denominator}));
    SeriesBasedOnFormula series(formula, "n");

    EXPECT_TRUE(series.isConvergent());
}

TEST(SeriesBasedOnFormulaTest, IsConvergentWorksOnDivergentSeries)
{
    Term n("n");
    Term formula(createExpressionIfPossible({Term(-1), Term("^"), n, Term("+"), Term(1)}));
    SeriesBasedOnFormula series(formula, "n");

    EXPECT_FALSE(series.isConvergent());
}

TEST(SeriesBasedOnFormulaTest, IsIncreasingAndIsDecreasingAndIsMonotonicWorksOnIncreasingFunction)
{
    Term numerator(Polynomial{Monomial(1, {{"n", 1}}), Monomial(1, {})});
    Term denominator(Polynomial{Monomial(2, {{"n", 1}}), Monomial(3, {})});
    Term formula(createExpressionIfPossible({numerator, Term("/"), denominator}));
    SeriesBasedOnFormula series(formula, "n");

    EXPECT_TRUE(series.isIncreasing());
    EXPECT_FALSE(series.isDecreasing());
    EXPECT_TRUE(series.isMonotonic());
}

TEST(SeriesBasedOnFormulaTest, IsIncreasingAndIsDecreasingAndIsMonotonicWorksOnNonIncreasingAndDecreasingFunction)
{
    Term n("n");
    Term formula(sin(n));
    SeriesBasedOnFormula series(formula, "n");

    EXPECT_FALSE(series.isIncreasing());
    EXPECT_FALSE(series.isDecreasing());
    EXPECT_FALSE(series.isMonotonic());
}

TEST(SeriesBasedOnFormulaTest, IsIncreasingAndIsDecreasingAndIsMonotonicWorksOnDecreasingFunction)
{
    Term numerator(1);
    Term denominator(Polynomial{Monomial(1, {{"n", 1}}), Monomial(1, {})});
    Term formula(createExpressionIfPossible({numerator, Term("/"), denominator}));
    SeriesBasedOnFormula series(formula, "n");

    EXPECT_FALSE(series.isIncreasing());
    EXPECT_TRUE(series.isDecreasing());
    EXPECT_TRUE(series.isMonotonic());
}

TEST(SeriesBasedOnFormulaTest, GetValueAtIndexWorks)
{
    SeriesBasedOnFormula series(Term("n"), "n");

    EXPECT_EQ(Term(-5), series.getValueAtIndex(-5));
    EXPECT_EQ(Term(Constant(0)), series.getValueAtIndex(0));
    EXPECT_EQ(Term(5), series.getValueAtIndex(5));
}

TEST(SeriesBasedOnFormulaTest, GetFormulaForSeriesWorks)
{
    Term formula(Polynomial{Monomial(1, {{"n", 2}}), Monomial(3, {{"n", 4}}), Monomial(5, {{"n", 6}})});
    SeriesBasedOnFormula series(formula, "n");

    EXPECT_EQ(formula, series.getFormulaForSeries());
}

TEST(SeriesBasedOnFormulaTest, GetSumWorks)
{
    SeriesBasedOnFormula series(Term("n"), "n");

    EXPECT_EQ(Term(55), series.getSum(0, 10));
}

TEST(SeriesBasedOnFormulaTest, GetSumStartingAtIndexAndToInfinityWorks)
{
    Term formula(createExpressionIfPossible({Term(AlbaNumber::createFraction(1, 2)), Term("^"), Term("n")}));
    SeriesBasedOnFormula series(formula, "n");

    EXPECT_EQ(Term(2), series.getSumStartingAtIndexAndToInfinity(0));
}

TEST(SeriesBasedOnFormulaTest, GetValueAtInfinityWorks)
{
    Term n("n");
    Term numerator(n);
    Term denominator(Polynomial{Monomial(2, {{"n", 1}}), Monomial(1, {})});
    Term formula(createExpressionIfPossible({numerator, Term("/"), denominator}));
    SeriesBasedOnFormula series(formula, "n");

    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 2)), series.getValueAtInfinity());
}

TEST(SeriesBasedOnFormulaTest, GetRemainderAtIndexWorks)
{
    Term n("n");
    Term numerator(n);
    Term denominator(Polynomial{Monomial(2, {{"n", 1}}), Monomial(1, {})});
    Term formula(createExpressionIfPossible({numerator, Term("/"), denominator}));
    SeriesBasedOnFormula series(formula, "n");

    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 2)), series.getRemainderAtIndex(0));
    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 6)), series.getRemainderAtIndex(1));
    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 10)), series.getRemainderAtIndex(2));
}

TEST(SeriesBasedOnFormulaTest, GetGreatestLowerBoundWorks)
{
    Term n("n");
    Term numerator(n);
    Term denominator(Polynomial{Monomial(2, {{"n", 1}}), Monomial(1, {})});
    Term formula(createExpressionIfPossible({numerator, Term("/"), denominator}));
    SeriesBasedOnFormula series(formula, "n");

    AlbaNumberOptional greatestLowerBoundOptional(series.getGreatestLowerBound());

    ASSERT_TRUE(greatestLowerBoundOptional.hasContent());
    EXPECT_EQ(AlbaNumber::createFraction(-4, 15), greatestLowerBoundOptional.getConstReference());
}

TEST(SeriesBasedOnFormulaTest, GetLeastUpperBoundWorks)
{
    Term n("n");
    Term numerator(n);
    Term denominator(Polynomial{Monomial(2, {{"n", 1}}), Monomial(1, {})});
    Term formula(createExpressionIfPossible({numerator, Term("/"), denominator}));
    SeriesBasedOnFormula series(formula, "n");

    AlbaNumberOptional leastUpperBoundOptional(series.getLeastUpperBound());

    ASSERT_TRUE(leastUpperBoundOptional.hasContent());
    EXPECT_EQ(AlbaNumber::createFraction(1, 2), leastUpperBoundOptional.getConstReference());
}

}

}
