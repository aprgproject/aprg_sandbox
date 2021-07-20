#include <Algebra/Simplification/SimplificationOfEquation.hpp>
#include <Algebra/Utilities.hpp>

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
    SimplificationOfEquation simplification(Equation(Term(Monomial(1, {{"x", -1}})), "=", Term(Monomial(1, {{"y", -1}}))));

    simplification.simplify();

    Equation simplifiedEquation(simplification.getEquation());
    Term expectedTerm(createExpressionIfPossible(
    {Term(Polynomial({Monomial(-1, {{"x", 1}}), Monomial(1, {{"y", 1}})})),
     Term("/"),
     Term(Monomial(1, {{"x", 1}, {"y", 1}}))}));
    EXPECT_EQ(expectedTerm, simplifiedEquation.getLeftHandTerm());
    EXPECT_EQ("=", simplifiedEquation.getEquationOperator().getOperatorString());
    EXPECT_EQ(Term(Constant(0)), simplifiedEquation.getRightHandTerm());
}

}

}

}