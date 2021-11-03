#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Series/SeriesBasedOnTerm.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba{

namespace algebra
{
TEST(SeriesBasedOnTermTest, ConstructionWorks)
{
    SeriesBasedOnTerm series(Term("n"), "n");
}

TEST(SeriesBasedOnTermTest, IsConvergentWorksOnConvergentSeries)
{
    Term numerator(Polynomial{Monomial(4, {{"n", 2}})});
    Term denominator(Polynomial{Monomial(2, {{"n", 2}}), Monomial(1, {})});
    Term formula(createExpressionIfPossible({numerator, Term("/"), denominator}));
    SeriesBasedOnTerm series(formula, "n");

    EXPECT_TRUE(series.isConvergent());
}
TEST(SeriesBasedOnTermTest, IsConvergentWorksOnDivergentSeries)
{
    Term n("n");
    Term formula(createExpressionIfPossible({Term(-1), Term("^"), n, Term("+"), Term(1)}));
    SeriesBasedOnTerm series(formula, "n");

    EXPECT_FALSE(series.isConvergent());
}

TEST(SeriesBasedOnTermTest, IsIncreasingAndIsDecreasingAndIsMonotonicWorksOnIncreasingFunction)
{
    Term numerator(Polynomial{Monomial(1, {{"n", 1}}), Monomial(1, {})});
    Term denominator(Polynomial{Monomial(2, {{"n", 1}}), Monomial(3, {})});
    Term formula(createExpressionIfPossible({numerator, Term("/"), denominator}));
    SeriesBasedOnTerm series(formula, "n");

    EXPECT_TRUE(series.isIncreasing());
    EXPECT_FALSE(series.isDecreasing());
    EXPECT_TRUE(series.isMonotonic());
}

TEST(SeriesBasedOnTermTest, IsIncreasingAndIsDecreasingAndIsMonotonicWorksOnNonIncreasingAndDecreasingFunction)
{
    Term n("n");
    Term formula(sin(n));
    SeriesBasedOnTerm series(formula, "n");

    EXPECT_FALSE(series.isIncreasing());
    EXPECT_FALSE(series.isDecreasing());
    EXPECT_FALSE(series.isMonotonic());
}

TEST(SeriesBasedOnTermTest, IsIncreasingAndIsDecreasingAndIsMonotonicWorksOnDecreasingFunction)
{
    Term numerator(1);
    Term denominator(Polynomial{Monomial(1, {{"n", 1}}), Monomial(1, {})});
    Term formula(createExpressionIfPossible({numerator, Term("/"), denominator}));
    SeriesBasedOnTerm series(formula, "n");

    EXPECT_FALSE(series.isIncreasing());
    EXPECT_TRUE(series.isDecreasing());
    EXPECT_TRUE(series.isMonotonic());
}

TEST(SeriesBasedOnTermTest, GetValueAtIndexWorks)
{
    SeriesBasedOnTerm series(Term("n"), "n");
    EXPECT_EQ(Term(-5), series.getValueAtIndex(-5));
    EXPECT_EQ(Term(Constant(0)), series.getValueAtIndex(0));
    EXPECT_EQ(Term(5), series.getValueAtIndex(5));
}

TEST(SeriesBasedOnTermTest, GetFormulaForSeriesWorks)
{
    Term formula(Polynomial{Monomial(1, {{"n", 2}}), Monomial(3, {{"n", 4}}), Monomial(5, {{"n", 6}})});
    SeriesBasedOnTerm series(formula, "n");

    EXPECT_EQ(formula, series.getFormulaForSeries());
}

TEST(SeriesBasedOnTermTest, GetSumWorks)
{
    SeriesBasedOnTerm series(Term("n"), "n");
    EXPECT_EQ(Term(55), series.getSum(0, 10));
}

TEST(SeriesBasedOnTermTest, GetSumStartingAtIndexAndToInfinityWorks)
{
    Term formula(createExpressionIfPossible({Term(AlbaNumber::createFraction(1, 2)), Term("^"), Term("n")}));
    SeriesBasedOnTerm series(formula, "n");

    EXPECT_EQ(Term(2), series.getSumStartingAtIndexAndToInfinity(0));
}
TEST(SeriesBasedOnTermTest, GetValueAtInfinityWorks)
{
    Term n("n");
    Term numerator(n);
    Term denominator(Polynomial{Monomial(2, {{"n", 1}}), Monomial(1, {})});
    Term formula(createExpressionIfPossible({numerator, Term("/"), denominator}));
    SeriesBasedOnTerm series(formula, "n");

    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 2)), series.getValueAtInfinity());
}

TEST(SeriesBasedOnTermTest, GetGreatestLowerBoundWorks)
{
    Term n("n");
    Term numerator(n);
    Term denominator(Polynomial{Monomial(2, {{"n", 1}}), Monomial(1, {})});
    Term formula(createExpressionIfPossible({numerator, Term("/"), denominator}));
    SeriesBasedOnTerm series(formula, "n");

    AlbaNumberOptional greatestLowerBoundOptional(series.getGreatestLowerBound());

    ASSERT_TRUE(greatestLowerBoundOptional.hasContent());
    EXPECT_EQ(AlbaNumber::createFraction(-4, 15), greatestLowerBoundOptional.getConstReference());
}

TEST(SeriesBasedOnTermTest, GetLeastUpperBoundWorks)
{
    Term n("n");
    Term numerator(n);
    Term denominator(Polynomial{Monomial(2, {{"n", 1}}), Monomial(1, {})});
    Term formula(createExpressionIfPossible({numerator, Term("/"), denominator}));
    SeriesBasedOnTerm series(formula, "n");

    AlbaNumberOptional leastUpperBoundOptional(series.getLeastUpperBound());

    ASSERT_TRUE(leastUpperBoundOptional.hasContent());
    EXPECT_EQ(AlbaNumber::createFraction(1, 2), leastUpperBoundOptional.getConstReference());
}

}

}