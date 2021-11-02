#include <Algebra/Series/SeriesBasedOnTerm.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

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
    Term termToTest(createExpressionIfPossible({numerator, Term("/"), denominator}));
    SeriesBasedOnTerm series(termToTest, "n");

    EXPECT_TRUE(series.isConvergent());
}

TEST(SeriesBasedOnTermTest, IsConvergentWorksOnDivergentSeries)
{
    Term n("n");
    Term termToTest(createExpressionIfPossible({Term(-1), Term("^"), n, Term("+"), Term(1)}));
    SeriesBasedOnTerm series(termToTest, "n");

    EXPECT_FALSE(series.isConvergent());
}

TEST(SeriesBasedOnTermTest, GetValueAtIndexWorks)
{
    SeriesBasedOnTerm series(Term("n"), "n");

    EXPECT_EQ(Term(-5), series.getValueAtIndex(-5));
    EXPECT_EQ(Term(Constant(0)), series.getValueAtIndex(0));
    EXPECT_EQ(Term(5), series.getValueAtIndex(5));
}

TEST(SeriesBasedOnTermTest, GetSumWorks)
{
    SeriesBasedOnTerm series(Term("n"), "n");

    EXPECT_EQ(Term(55), series.getSum(0, 10));
}

TEST(SeriesBasedOnTermTest, GetSumStartingAtIndexAndToInfinityWorks)
{
    Term termToTest(createExpressionIfPossible({Term(AlbaNumber::createFraction(1, 2)), Term("^"), Term("n")}));
    SeriesBasedOnTerm series(termToTest, "n");

    EXPECT_EQ(Term(2), series.getSumStartingAtIndexAndToInfinity(0));
}

TEST(SeriesBasedOnTermTest, GetValueAtInfinityWorks)
{
    Term n("n");
    Term numerator(n);
    Term denominator(Polynomial{Monomial(2, {{"n", 1}}), Monomial(1, {})});
    Term termToTest(createExpressionIfPossible({numerator, Term("/"), denominator}));
    SeriesBasedOnTerm series(termToTest, "n");

    EXPECT_EQ(Term(AlbaNumber::createFraction(1, 2)), series.getValueAtInfinity());
}

}

}
