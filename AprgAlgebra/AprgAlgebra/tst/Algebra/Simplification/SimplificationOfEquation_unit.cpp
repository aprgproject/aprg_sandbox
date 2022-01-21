#include <Algebra/Simplification/SimplificationOfEquation.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

namespace Simplification
{

TEST(SimplificationOfEquationTest, SimplifyWorksOnEqualityOperator)
{
    SimplificationOfEquation simplification(Equation("x", "=", "y"));

    simplification.simplify();

    Equation simplifiedEquation(simplification.getEquation());
    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-1, {{"y", 1}})}), simplifiedEquation.getLeftHandTerm());
    EXPECT_EQ("=", simplifiedEquation.getEquationOperator().getOperatorString());
    EXPECT_EQ(Term(0), simplifiedEquation.getRightHandTerm());
}

TEST(SimplificationOfEquationTest, SimplifyWorksOnLessThanOperator)
{
    SimplificationOfEquation simplification(Equation("x", "<", "y"));

    simplification.simplify();

    Equation simplifiedEquation(simplification.getEquation());
    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-1, {{"y", 1}})}), simplifiedEquation.getLeftHandTerm());
    EXPECT_EQ("<", simplifiedEquation.getEquationOperator().getOperatorString());
    EXPECT_EQ(Term(0), simplifiedEquation.getRightHandTerm());
}

TEST(SimplificationOfEquationTest, SimplifyWorksOnGreaterThanOperator)
{
    SimplificationOfEquation simplification(Equation("x", ">", "y"));

    simplification.simplify();

    Equation simplifiedEquation(simplification.getEquation());
    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-1, {{"y", 1}})}), simplifiedEquation.getLeftHandTerm());
    EXPECT_EQ(">", simplifiedEquation.getEquationOperator().getOperatorString());
    EXPECT_EQ(Term(0), simplifiedEquation.getRightHandTerm());
}

TEST(SimplificationOfEquationTest, SimplifyWorksOnLessThanOrEqualOperator)
{
    SimplificationOfEquation simplification(Equation("x", "<=", "y"));

    simplification.simplify();

    Equation simplifiedEquation(simplification.getEquation());
    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-1, {{"y", 1}})}), simplifiedEquation.getLeftHandTerm());
    EXPECT_EQ("<=", simplifiedEquation.getEquationOperator().getOperatorString());
    EXPECT_EQ(Term(0), simplifiedEquation.getRightHandTerm());
}

TEST(SimplificationOfEquationTest, SimplifyWorksToHaveCommonDenominator)
{
    Polynomial denominatorLeft{Monomial(1, {{"x", 1}}), Monomial(1, {})};
    Polynomial denominatorRight{Monomial(2, {{"x", 1}}), Monomial(3, {})};
    Expression expressionLeft(createExpressionIfPossible({1, "/", denominatorLeft}));
    Expression expressionRight(createExpressionIfPossible({1, "/", denominatorRight}));
    SimplificationOfEquation simplification(Equation(expressionLeft, "=",  expressionRight));

    simplification.simplify();

    Polynomial expectedNumerator{Monomial(1, {{"x", 1}}), Monomial(2, {})};
    Polynomial expectedDenominator{Monomial(2, {{"x", 2}}), Monomial(5, {{"x", 1}}), Monomial(3, {})};
    Equation simplifiedEquation(simplification.getEquation());
    Term expectedTerm(createExpressionIfPossible({expectedNumerator, "/", expectedDenominator}));
    EXPECT_EQ(expectedTerm, simplifiedEquation.getLeftHandTerm());
    EXPECT_EQ("=", simplifiedEquation.getEquationOperator().getOperatorString());
    EXPECT_EQ(Term(0), simplifiedEquation.getRightHandTerm());
}

TEST(SimplificationOfEquationTest, SimplifyWorksOnSimplifyingAnExpression)
{
    Expression expression(createExpressionIfPossible({"x", "/", 523}));
    SimplificationOfEquation simplification(Equation(expression, "=", 0));

    simplification.simplify();

    Equation simplifiedEquation(simplification.getEquation());
    Term expectedTerm("x");
    EXPECT_EQ(expectedTerm, simplifiedEquation.getLeftHandTerm());
    EXPECT_EQ("=", simplifiedEquation.getEquationOperator().getOperatorString());
    EXPECT_EQ(Term(0), simplifiedEquation.getRightHandTerm());
}

TEST(SimplificationOfEquationTest, SimplifyWorksOnNegatingTermIfNeeded)
{
    SimplificationOfEquation simplification1(Equation("x", "=", "y"));
    SimplificationOfEquation simplification2(Equation("x", "=", "y"));

    simplification1.simplify();
    simplification2.simplify();

    Equation simplifiedEquation1(simplification1.getEquation());
    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-1, {{"y", 1}})}), simplifiedEquation1.getLeftHandTerm());
    EXPECT_EQ("=", simplifiedEquation1.getEquationOperator().getOperatorString());
    EXPECT_EQ(Term(0), simplifiedEquation1.getRightHandTerm());
    Equation simplifiedEquation2(simplification2.getEquation());
    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-1, {{"y", 1}})}), simplifiedEquation2.getLeftHandTerm());
    EXPECT_EQ("=", simplifiedEquation2.getEquationOperator().getOperatorString());
    EXPECT_EQ(Term(0), simplifiedEquation2.getRightHandTerm());
}

TEST(SimplificationOfEquationTest, SimplifyWorksOnRemovingExponentIfNeeded)
{
    Polynomial polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})};
    Expression expression(createExpressionIfPossible({polynomial, "^", "x"}));
    SimplificationOfEquation simplification(Equation(expression, "=", 0));

    simplification.simplify();

    Equation simplifiedEquation(simplification.getEquation());
    EXPECT_EQ(Term(polynomial), simplifiedEquation.getLeftHandTerm());
    EXPECT_EQ("=", simplifiedEquation.getEquationOperator().getOperatorString());
    EXPECT_EQ(Term(0), simplifiedEquation.getRightHandTerm());
}

TEST(SimplificationOfEquationTest, SimplifyWorksOnCompletingExpressionWithFractionalExponentsIfNeeded)
{
    Polynomial polynomial1{Monomial(-1, {{"x", 1}}), Monomial(1, {})};
    Polynomial polynomial2{Monomial(1, {{"x", 1}}), Monomial(2, {})};
    Expression expression(createExpressionIfPossible(
    {polynomial1, "^", AlbaNumber::createFraction(1, 2), "-", polynomial2, "^", AlbaNumber::createFraction(1, 3)}));
    SimplificationOfEquation simplification(Equation(expression, "=", 0));

    simplification.simplify();

    Polynomial expectedPolynomial{Monomial(1, {{"x", 3}}), Monomial(-2, {{"x", 2}}), Monomial(7, {{"x", 1}}), Monomial(3, {})};
    Equation simplifiedEquation(simplification.getEquation());
    EXPECT_EQ(Term(expectedPolynomial), simplifiedEquation.getLeftHandTerm());
    EXPECT_EQ("=", simplifiedEquation.getEquationOperator().getOperatorString());
    EXPECT_EQ(Term(0), simplifiedEquation.getRightHandTerm());
}

TEST(SimplificationOfEquationTest, SimplifyWorksXPlusOneToTheOneHalf)
{
    Polynomial polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})};
    Expression expression(createExpressionIfPossible({polynomial, "^", AlbaNumber::createFraction(1, 2)}));
    SimplificationOfEquation simplification(Equation("y", "=", expression));

    simplification.simplify();

    Polynomial expectedPolynomial{Monomial(1, {{"y", 2}}), Monomial(-1, {{"x", 1}}), Monomial(-1, {})};
    Equation simplifiedEquation(simplification.getEquation());
    EXPECT_EQ(Term(expectedPolynomial), simplifiedEquation.getLeftHandTerm());
    EXPECT_EQ("=", simplifiedEquation.getEquationOperator().getOperatorString());
    EXPECT_EQ(Term(0), simplifiedEquation.getRightHandTerm());
}

TEST(SimplificationOfEquationTest, SimplifyWorksOnRemovingCommonConstantsInMonomial)
{
    Monomial monomial(24, {{"x", 2}, {"y", 2}});
    SimplificationOfEquation simplification(Equation(monomial, "=", 0));

    simplification.simplify();

    Monomial expectedMonomial(1, {{"x", 2}, {"y", 2}});
    Equation simplifiedEquation(simplification.getEquation());
    EXPECT_EQ(Term(expectedMonomial), simplifiedEquation.getLeftHandTerm());
    EXPECT_EQ("=", simplifiedEquation.getEquationOperator().getOperatorString());
    EXPECT_EQ(Term(0), simplifiedEquation.getRightHandTerm());
}

TEST(SimplificationOfEquationTest, SimplifyWorksOnRemovingCommonConstantsInPolynomial)
{
    Polynomial polynomial{Monomial(24, {{"x", 2}, {"y", 2}}), Monomial(18, {{"x", 2}})};
    SimplificationOfEquation simplification(Equation(polynomial, "=", 0));

    simplification.simplify();

    Polynomial expectedPolynomial{Monomial(4, {{"x", 2}, {"y", 2}}), Monomial(3, {{"x", 2}})};
    Equation simplifiedEquation(simplification.getEquation());
    EXPECT_EQ(Term(expectedPolynomial), simplifiedEquation.getLeftHandTerm());
    EXPECT_EQ("=", simplifiedEquation.getEquationOperator().getOperatorString());
    EXPECT_EQ(Term(0), simplifiedEquation.getRightHandTerm());
}

TEST(SimplificationOfEquationTest, SimplifyWorksOnRemovingCommonConstantsInExpression)
{
    Term xToTheX(createExpressionIfPossible({"x", "^", "x"}));
    Term yToTheY(createExpressionIfPossible({"y", "^", "y"}));
    Term expression(createExpressionIfPossible({18, "*", xToTheX, "+", 24, "*", yToTheY}));
    SimplificationOfEquation simplification(Equation(expression, "=", 0));

    simplification.simplify();

    Term expectedExpression(createExpressionIfPossible({3, "*", xToTheX, "+", 4, "*", yToTheY}));
    Equation simplifiedEquation(simplification.getEquation());
    EXPECT_EQ(Term(expectedExpression), simplifiedEquation.getLeftHandTerm());
    EXPECT_EQ("=", simplifiedEquation.getEquationOperator().getOperatorString());
    EXPECT_EQ(Term(0), simplifiedEquation.getRightHandTerm());
}

}

}

}
