#include <Algebra/Factorization/FactorizationOfExpression.hpp>
#include <Algebra/Utilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

namespace Factorization
{

TEST(FactorizationOfExpressions, FactorizeWorksOnPolynomialOverPolynomial)
{
    Polynomial polynomial1({Monomial(2, {{"x", 2}}), Monomial(5, {{"x", 1}}), Monomial(-12, {})});
    Polynomial polynomial2({Monomial(4, {{"x", 2}}), Monomial(-4, {{"x", 1}}), Monomial(-3, {})});
    Expression expressionToTest(createExpressionIfPossible({Term(polynomial1), Term("/"), Term(polynomial2)}));

    factorizeAnExpression(expressionToTest);

    Polynomial polynomialToExpect1({Monomial(2, {{"x", 1}}), Monomial(-3, {})});
    Polynomial polynomialToExpect2({Monomial(1, {{"x", 1}}), Monomial(4, {})});
    Polynomial polynomialToExpect3({Monomial(2, {{"x", 1}}), Monomial(1, {})});
    Expression expressionToExpect(createExpressionIfPossible(
                                      {
                                          Term(polynomialToExpect1),
                                          Term("*"), Term(polynomialToExpect2),
                                          Term("/"), Term(polynomialToExpect1),
                                          Term("/"), Term(polynomialToExpect3)
                                      }));
    EXPECT_EQ(expressionToExpect, expressionToTest);
}

TEST(FactorizationOfExpressions, FactorizeWorksOnPolynomialPlusPolynomial)
{
    Polynomial polynomial1({Monomial(2, {{"x", 2}}), Monomial(5, {{"x", 1}}), Monomial(-12, {})});
    Polynomial polynomial2({Monomial(4, {{"x", 2}}), Monomial(-4, {{"x", 1}}), Monomial(-3, {})});
    Expression expressionToTest(createExpressionIfPossible({Term(polynomial1), Term("+"), Term(polynomial2)}));

    factorizeAnExpression(expressionToTest);

    Polynomial polynomialToExpect1({Monomial(2, {{"x", 1}}), Monomial(-3, {})});
    Polynomial polynomialToExpect2({Monomial(1, {{"x", 1}}), Monomial(4, {})});
    Polynomial polynomialToExpect3({Monomial(2, {{"x", 1}}), Monomial(1, {})});
    Expression expression1(createExpressionIfPossible({Term(polynomialToExpect1), Term("*"), Term(polynomialToExpect2)}));
    Expression expression2(createExpressionIfPossible({Term(polynomialToExpect1), Term("*"), Term(polynomialToExpect3)}));
    Expression expressionToExpect(createExpressionIfPossible({Term(expression1), Term("+"), Term(expression2)}));
    EXPECT_EQ(expressionToExpect, expressionToTest);
}

}

}

}
