#include <Algebra/Factorization/Factorization.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Term.hpp>
#include <Algebra/Utilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

namespace Factorization
{

TEST(FactorizationTest, FactorizeWorksForAPolynomial)
{
    Polynomial polynomialToTest{Monomial(4, {{"x", 3}}), Monomial(-12, {{"x", 2}}), Monomial(-1, {{"x", 1}}), Monomial(3, {})};

    Polynomials polynomialsToVerify(factorize(polynomialToTest));

    ASSERT_EQ(3u, polynomialsToVerify.size());
    Polynomial polynomialToExpect1{Monomial(2, {{"x", 1}}), Monomial(1, {})};
    Polynomial polynomialToExpect2{Monomial(2, {{"x", 1}}), Monomial(-1, {})};
    Polynomial polynomialToExpect3{Monomial(1, {{"x", 1}}), Monomial(-3, {})};
    EXPECT_EQ(polynomialToExpect1, polynomialsToVerify.at(0));
    EXPECT_EQ(polynomialToExpect2, polynomialsToVerify.at(1));
    EXPECT_EQ(polynomialToExpect3, polynomialsToVerify.at(2));
}

TEST(FactorizationTest, FactorizeWorksForAnExpression)
{
    Polynomial polynomial1({Monomial(2, {{"x", 2}}), Monomial(5, {{"x", 1}}), Monomial(-12, {})});
    Polynomial polynomial2({Monomial(4, {{"x", 2}}), Monomial(-4, {{"x", 1}}), Monomial(-3, {})});
    Expression expressionToTest(createExpressionIfPossible({Term(polynomial1), Term("/"), Term(polynomial2)}));

    Expression expressionToVerify(factorize(expressionToTest));

    Polynomial polynomialToExpect1({Monomial(2, {{"x", 1}}), Monomial(-3, {})});
    Polynomial polynomialToExpect2({Monomial(1, {{"x", 1}}), Monomial(4, {})});
    Polynomial polynomialToExpect3({Monomial(2, {{"x", 1}}), Monomial(1, {})});
    Expression expressionToExpect(
                createExpressionIfPossible({
                                               Term(polynomialToExpect1),
                                               Term("*"), Term(polynomialToExpect2),
                                               Term("/"), Term(polynomialToExpect1),
                                               Term("/"), Term(polynomialToExpect3)
                                           }));
    EXPECT_EQ(expressionToExpect, expressionToVerify);
}

TEST(FactorizationTest, FactorizeWorksForAFunction)
{
    Polynomial polynomial({Monomial(2, {{"x", 2}}), Monomial(5, {{"x", 1}}), Monomial(-12, {})});
    Function functionToTest(Functions::abs(createOrCopyExpressionFromATerm(Term(polynomial))));

    Function functionToVerify(factorize(functionToTest));

    Polynomial polynomialToExpect1({Monomial(2, {{"x", 1}}), Monomial(-3, {})});
    Polynomial polynomialToExpect2({Monomial(1, {{"x", 1}}), Monomial(4, {})});
    Function functionToExpect(
                Functions::abs(
                    createExpressionIfPossible({Term(polynomialToExpect1), Term("*"), Term(polynomialToExpect2)})));
    EXPECT_EQ(functionToExpect, functionToVerify);
}

}

}

}
