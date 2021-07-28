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
    EXPECT_EQ(Term(Polynomial({Monomial(1, {{"x", 1}}), Monomial(-1, {{"y", 1}})})), simplifiedEquation.getLeftHandTerm());
    EXPECT_EQ("=", simplifiedEquation.getEquationOperator().getOperatorString());
    EXPECT_EQ(Term(Constant(0)), simplifiedEquation.getRightHandTerm());
}

TEST(SimplificationOfEquationTest, SimplifyWorksOnLessThanOperator)
{
    SimplificationOfEquation simplification(Equation(Term("x"), "<", Term("y")));

    simplification.simplify();

    Equation simplifiedEquation(simplification.getEquation());
    EXPECT_EQ(Term(Polynomial({Monomial(-1, {{"x", 1}}), Monomial(1, {{"y", 1}})})), simplifiedEquation.getLeftHandTerm());
    EXPECT_EQ(">", simplifiedEquation.getEquationOperator().getOperatorString());
    EXPECT_EQ(Term(Constant(0)), simplifiedEquation.getRightHandTerm());
}

TEST(SimplificationOfEquationTest, SimplifyWorksOnGreaterThanOperator)
{
    SimplificationOfEquation simplification(Equation(Term("x"), ">", Term("y")));

    simplification.simplify();

    Equation simplifiedEquation(simplification.getEquation());
    EXPECT_EQ(Term(Polynomial({Monomial(1, {{"x", 1}}), Monomial(-1, {{"y", 1}})})), simplifiedEquation.getLeftHandTerm());
    EXPECT_EQ(">", simplifiedEquation.getEquationOperator().getOperatorString());
    EXPECT_EQ(Term(Constant(0)), simplifiedEquation.getRightHandTerm());
}

TEST(SimplificationOfEquationTest, SimplifyWorksOnLessThanOrEqualOperator)
{
    SimplificationOfEquation simplification(Equation(Term("x"), "<=", Term("y")));

    simplification.simplify();

    Equation simplifiedEquation(simplification.getEquation());
    EXPECT_EQ(Term(Polynomial({Monomial(-1, {{"x", 1}}), Monomial(1, {{"y", 1}})})), simplifiedEquation.getLeftHandTerm());
    EXPECT_EQ(">=", simplifiedEquation.getEquationOperator().getOperatorString());
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
    Term expectedTerm(AlbaNumber(451, 523));
    EXPECT_EQ(expectedTerm, simplifiedEquation.getLeftHandTerm());
    EXPECT_EQ("=", simplifiedEquation.getEquationOperator().getOperatorString());
    EXPECT_EQ(Term(Constant(0)), simplifiedEquation.getRightHandTerm());
}
}

}

}
