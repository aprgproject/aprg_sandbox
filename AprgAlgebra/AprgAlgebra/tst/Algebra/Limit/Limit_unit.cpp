#include <Algebra/Limit/Limit.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;
namespace alba
{

namespace algebra
{

TEST(LimitTest, GetLimitAsVariableApproachesTheValueWorksForPolynomial)
{
    Term polynomial(Polynomial{Monomial(4, {{"x", 1}}), Monomial(-7, {})});

    EXPECT_EQ(Term(5), getLimitAsVariableApproachesTheValue(polynomial, "x", 3));
}

TEST(LimitTest, GetLimitAsVariableApproachesTheValueWorksForPolynomialOverPolynomial)
{
    Term numerator(Polynomial{Monomial(1, {{"x", 2}}), Monomial(-25, {})});
    Term denominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-5, {})});
    Term polynomialOverPolynomial(createExpressionIfPossible({numerator, Term("/"), denominator}));

    EXPECT_EQ(Term(10), getLimitAsVariableApproachesTheValue(polynomialOverPolynomial, "x", 5));
}

TEST(LimitTest, GetLimitAsVariableApproachesTheValueWorksForPolynomialOverPolynomialWithFractionalValues)
{
    Term numerator(Polynomial{Monomial(1, {{"x", AlbaNumber::createFraction(1, 2)}}), Monomial(-2, {})});
    Term denominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-4, {})});
    Term polynomialOverPolynomial(createExpressionIfPossible({numerator, Term("/"), denominator}));

    EXPECT_EQ(Term(10), getLimitAsVariableApproachesTheValue(polynomialOverPolynomial, "x", 4));
}

}

}
