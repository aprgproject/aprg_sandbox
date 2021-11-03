#include <Algebra/Series/SeriesBasedOnSummation.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(SeriesBasedOnSummationTest, ConstructionWorks)
{
    SeriesBasedOnSummation(Term("n"), "n");
}

TEST(SeriesBasedOnSummationTest, IsConvergentWorksWhenItHasAValidSummationModel)
{
    Term exponent(Polynomial{Monomial(1, {}), Monomial(-1, {{"n", 1}})});
    Term formula(createExpressionIfPossible({Term(2), Term("^"), exponent}));
    SeriesBasedOnSummation series(formula, "n");

    EXPECT_TRUE(series.hasAValidSummationModel());
    EXPECT_TRUE(series.isConvergent());
}

TEST(SeriesBasedOnSummationTest, IsConvergentWorksWhenItDoesNotHaveAValidSummationModel)
{
    Term numerator(Polynomial{Monomial(1, {{"n", 2}}), Monomial(1, {})});
    Term denominator(Monomial(1, {{"n", 2}}));
    Term formula(createExpressionIfPossible({numerator, Term("/"), denominator}));
    SeriesBasedOnSummation series(formula, "n");

    EXPECT_TRUE(series.hasAValidSummationModel());
    EXPECT_FALSE(series.isConvergent());
}

}

}
