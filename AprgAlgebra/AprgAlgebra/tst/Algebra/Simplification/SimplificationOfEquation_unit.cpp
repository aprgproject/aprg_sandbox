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
    SimplificationOfEquation simplification(Equation(Term("x"), "=", Term("y")));

    simplification.simplify();

    Equation simplifiedEquation(simplification.getEquation());
    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-1, {{"y", 1}})}), simplifiedEquation.getLeftHandTerm());
    EXPECT_EQ("=", simplifiedEquation.getEquationOperator().getOperatorString());
    EXPECT_EQ(Term(Constant(0)), simplifiedEquation.getRightHandTerm());
}

TEST(SimplificationOfEquationTest, SimplifyWorksOnLessThanOperator)
{
    SimplificationOfEquation simplification(Equation(Term("x"), "<", Term("y")));

    simplification.simplify();

    Equation simplifiedEquation(simplification.getEquation());
    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-1, {{"y", 1}})}), simplifiedEquation.getLeftHandTerm());
    EXPECT_EQ("<", simplifiedEquation.getEquationOperator().getOperatorString());
    EXPECT_EQ(Term(Constant(0)), simplifiedEquation.getRightHandTerm());
}

TEST(SimplificationOfEquationTest, SimplifyWorksOnGreaterThanOperator)
{
    SimplificationOfEquation simplification(Equation(Term("x"), ">", Term("y")));

    simplification.simplify();

    Equation simplifiedEquation(simplification.getEquation());
    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-1, {{"y", 1}})}), simplifiedEquation.getLeftHandTerm());
    EXPECT_EQ(">", simplifiedEquation.getEquationOperator().getOperatorString());
    EXPECT_EQ(Term(Constant(0)), simplifiedEquation.getRightHandTerm());
}

TEST(SimplificationOfEquationTest, SimplifyWorksOnLessThanOrEqualOperator)
{
    SimplificationOfEquation simplification(Equation(Term("x"), "<=", Term("y")));

    simplification.simplify();

    Equation simplifiedEquation(simplification.getEquation());
    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-1, {{"y", 1}})}), simplifiedEquation.getLeftHandTerm());
    EXPECT_EQ("<=", simplifiedEquation.getEquationOperator().getOperatorString());
    EXPECT_EQ(Term(Constant(0)), simplifiedEquation.getRightHandTerm());
}

TEST(SimplificationOfEquationTest, SimplifyWorksToHaveCommonDenominator)
{
    Polynomial denominatorLeft{Monomial(1, {{"x", 1}}), Monomial(1, {})};
    Polynomial denominatorRight{Monomial(2, {{"x", 1}}), Monomial(3, {})};
    Expression expressionLeft(createExpressionIfPossible({Term(1), Term("/"), Term(denominatorLeft)}));
    Expression expressionRight(createExpressionIfPossible({Term(1), Term("/"), Term(denominatorRight)}));
    SimplificationOfEquation simplification(Equation(Term(expressionLeft), "=",  Term(expressionRight)));

    simplification.simplify();

    Polynomial expectedNumerator{Monomial(1, {{"x", 1}}), Monomial(2, {})};
    Polynomial expectedDenominator{Monomial(2, {{"x", 2}}), Monomial(5, {{"x", 1}}), Monomial(3, {})};
    Equation simplifiedEquation(simplification.getEquation());
    Term expectedTerm(createExpressionIfPossible({Term(expectedNumerator), Term("/"), Term(expectedDenominator)}));
    EXPECT_EQ(expectedTerm, simplifiedEquation.getLeftHandTerm());
    EXPECT_EQ("=", simplifiedEquation.getEquationOperator().getOperatorString());
    EXPECT_EQ(Term(Constant(0)), simplifiedEquation.getRightHandTerm());
}

TEST(SimplificationOfEquationTest, SimplifyWorksOnSimplifyingAnExpression)
{
    Expression expression(createExpressionIfPossible({Term(451), Term("/"), Term(523)}));
    SimplificationOfEquation simplification(Equation(Term(expression), "=", Term(Constant(0))));

    simplification.simplify();

    Equation simplifiedEquation(simplification.getEquation());
    Term expectedTerm(AlbaNumber::createFraction(451, 523));
    EXPECT_EQ(expectedTerm, simplifiedEquation.getLeftHandTerm());
    EXPECT_EQ("=", simplifiedEquation.getEquationOperator().getOperatorString());
    EXPECT_EQ(Term(Constant(0)), simplifiedEquation.getRightHandTerm());
}

TEST(SimplificationOfEquationTest, SimplifyWorksOnNegatingTermIfNeeded)
{
    SimplificationOfEquation simplification1(Equation(Term("x"), "=", Term("y")));
    SimplificationOfEquation simplification2(Equation(Term("x"), "=", Term("y")));

    simplification1.simplify();
    simplification2.simplify();

    Equation simplifiedEquation1(simplification1.getEquation());
    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-1, {{"y", 1}})}), simplifiedEquation1.getLeftHandTerm());
    EXPECT_EQ("=", simplifiedEquation1.getEquationOperator().getOperatorString());
    EXPECT_EQ(Term(Constant(0)), simplifiedEquation1.getRightHandTerm());
    Equation simplifiedEquation2(simplification2.getEquation());
    EXPECT_EQ(Term(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-1, {{"y", 1}})}), simplifiedEquation2.getLeftHandTerm());
    EXPECT_EQ("=", simplifiedEquation2.getEquationOperator().getOperatorString());
    EXPECT_EQ(Term(Constant(0)), simplifiedEquation2.getRightHandTerm());
}

TEST(SimplificationOfEquationTest, SimplifyWorksOnRemovingExponentIfNeeded)
{
    Polynomial polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})};
    Expression expression(createExpressionIfPossible({Term(polynomial), Term("^"), Term("x")}));
    SimplificationOfEquation simplification(Equation(Term(expression), "=", Term(Constant(0))));

    simplification.simplify();

    Equation simplifiedEquation(simplification.getEquation());
    EXPECT_EQ(Term(polynomial), simplifiedEquation.getLeftHandTerm());
    EXPECT_EQ("=", simplifiedEquation.getEquationOperator().getOperatorString());
    EXPECT_EQ(Term(Constant(0)), simplifiedEquation.getRightHandTerm());
}

TEST(SimplificationOfEquationTest, SimplifyWorksOnCompletingExpressionWithFractionalExponentsIfNeeded)
{
    Polynomial polynomial1{Monomial(-1, {{"x", 1}}), Monomial(1, {})};
    Polynomial polynomial2{Monomial(1, {{"x", 1}}), Monomial(2, {})};
    Expression expression(createExpressionIfPossible(
    {Term(polynomial1), Term("^"), Term(AlbaNumber::createFraction(1, 2)),
     Term("-"),
     Term(polynomial2), Term("^"), Term(AlbaNumber::createFraction(1, 3))}));
    SimplificationOfEquation simplification(Equation(Term(expression), "=", Term(Constant(0))));

    simplification.simplify();

    Polynomial expectedPolynomial{Monomial(1, {{"x", 3}}), Monomial(-2, {{"x", 2}}), Monomial(7, {{"x", 1}}), Monomial(3, {})};
    Equation simplifiedEquation(simplification.getEquation());
    EXPECT_EQ(Term(expectedPolynomial), simplifiedEquation.getLeftHandTerm());
    EXPECT_EQ("=", simplifiedEquation.getEquationOperator().getOperatorString());
    EXPECT_EQ(Term(Constant(0)), simplifiedEquation.getRightHandTerm());
}

TEST(SimplificationOfEquationTest, SimplifyWorksXPlusOneToTheOneHalf)
{
    Polynomial polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {})};
    Expression expression(createExpressionIfPossible( {Term(polynomial), Term("^"), Term(AlbaNumber::createFraction(1, 2))}));
    SimplificationOfEquation simplification(Equation(Term("y"), "=", Term(expression)));

    simplification.simplify();

    Polynomial expectedPolynomial{Monomial(1, {{"y", 2}}), Monomial(-1, {{"x", 1}}), Monomial(-1, {})};
    Equation simplifiedEquation(simplification.getEquation());
    EXPECT_EQ(Term(expectedPolynomial), simplifiedEquation.getLeftHandTerm());
    EXPECT_EQ("=", simplifiedEquation.getEquationOperator().getOperatorString());
    EXPECT_EQ(Term(Constant(0)), simplifiedEquation.getRightHandTerm());
}

}

}

}
