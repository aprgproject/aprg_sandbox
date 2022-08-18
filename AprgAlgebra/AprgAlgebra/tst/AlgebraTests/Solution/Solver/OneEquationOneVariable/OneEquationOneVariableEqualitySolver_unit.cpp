#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Solution/Solver/OneEquationOneVariable/OneEquationOneVariableEqualitySolver.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Common/Math/Number/Interval/AlbaNumberIntervalHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba
{

namespace algebra
{

TEST(OneEquationOneVariableEqualitySolverTest, ConstructionWorks)
{
    OneEquationOneVariableEqualitySolver();
}

TEST(OneEquationOneVariableEqualitySolverTest, NonEqualityOperatorsAreNotSolved)
{
    OneEquationOneVariableEqualitySolver solver;

    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(Equation("x", "<", "x")));

    EXPECT_FALSE(solver.isSolved());
    EXPECT_FALSE(solver.isACompleteSolution());
    EXPECT_TRUE(solutionSet.isEmpty());
}

TEST(OneEquationOneVariableEqualitySolverTest, MultipleVariableEquationsAreNotSolved)
{
    OneEquationOneVariableEqualitySolver solver;

    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(Equation("x", "=", "y")));

    EXPECT_FALSE(solver.isSolved());
    EXPECT_FALSE(solver.isACompleteSolution());
    EXPECT_TRUE(solutionSet.isEmpty());
}

TEST(OneEquationOneVariableEqualitySolverTest, EquationsThatAreAlwaysSatisfiedResultsInInfiniteRange)
{
    OneEquationOneVariableEqualitySolver solver;

    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(Equation("x", "=", "x")));

    EXPECT_TRUE(solver.isSolved());
    EXPECT_TRUE(solver.isACompleteSolution());
    AlbaNumberIntervals actualIntervals(solutionSet.getAcceptedIntervals());
    ASSERT_EQ(1U, actualIntervals.size());
    EXPECT_EQ(createAllRealValuesInterval(), actualIntervals.at(0));
}

TEST(OneEquationOneVariableEqualitySolverTest, PolynomialAreSolvedCorrectly)
{
    OneEquationOneVariableEqualitySolver solver;

    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(Equation(Monomial(1, {{"x", 4}}), "=", 16)));

    EXPECT_TRUE(solver.isSolved());
    EXPECT_TRUE(solver.isACompleteSolution());
    EXPECT_EQ((AlbaNumbers{-2, AlbaNumber::createComplexNumber(0, 2), 2}), solutionSet.getAcceptedValues());
}

TEST(OneEquationOneVariableEqualitySolverTest, PolynomialOverPolynomialAreSolvedCorrectly){
    Polynomial numerator{Monomial(1, {{"x", 2}}), Monomial(-25, {})};
    Polynomial denominator{Monomial(1, {{"x", 2}}), Monomial(-36, {})};
    Expression expression(createExpressionIfPossible({numerator, "/", denominator}));    OneEquationOneVariableEqualitySolver solver;

    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(Equation(expression, "=", 0)));

    EXPECT_TRUE(solver.isSolved());
    EXPECT_TRUE(solver.isACompleteSolution());
    EXPECT_EQ((AlbaNumbers{-5, 5}), solutionSet.getAcceptedValues());
    EXPECT_EQ((AlbaNumbers{-6, 6}), solutionSet.getRejectedValues());
}

TEST(OneEquationOneVariableEqualitySolverTest, XToTheXAreSolvedCorrectly){
    Expression expression(createExpressionIfPossible({"x", "^", "x"}));
    OneEquationOneVariableEqualitySolver solver;
    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(Equation(expression, "=", 823543)));

    EXPECT_TRUE(solver.isSolved());
    EXPECT_FALSE(solver.isACompleteSolution());
    EXPECT_EQ(AlbaNumbers{7}, solutionSet.getAcceptedValues());
}

TEST(OneEquationOneVariableEqualitySolverTest, XToTheXWithNegativeSolutionAreNotSolved){
    Expression expression(createExpressionIfPossible({"x", "^", "x"}));
    OneEquationOneVariableEqualitySolver solver;
    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(Equation(expression, "=", -823543)));

    EXPECT_FALSE(solver.isSolved());
    EXPECT_FALSE(solver.isACompleteSolution());
    EXPECT_TRUE(solutionSet.getAcceptedValues().empty());
}

TEST(OneEquationOneVariableEqualitySolverTest, AbsoluteValueFunctionsAreSolved){
    Term functionTerm(abs(createExpressionIfPossible({"x"})));
    OneEquationOneVariableEqualitySolver solver;
    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(Equation(functionTerm, "=", 526)));

    EXPECT_TRUE(solver.isSolved());
    EXPECT_TRUE(solver.isACompleteSolution());
    EXPECT_EQ((AlbaNumbers{-526, 526}), solutionSet.getAcceptedValues());
}

TEST(OneEquationOneVariableEqualitySolverTest, AbsoluteValueFunctionWithInputExpressionAreSolved){
    Term functionTerm(abs(createExpressionIfPossible({"x", "+", 100})));
    OneEquationOneVariableEqualitySolver solver;
    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(Equation(functionTerm, "=", 526)));

    EXPECT_TRUE(solver.isSolved());
    EXPECT_TRUE(solver.isACompleteSolution());
    EXPECT_EQ((AlbaNumbers{-626, 426}), solutionSet.getAcceptedValues());
}

TEST(OneEquationOneVariableEqualitySolverTest, TwoAbsoluteValueFunctionsAreSolved){
    Term functionTerm1(abs(Polynomial{Monomial(2,{{"x", 1}}), Monomial(-1, {})}));
    Term functionTerm2(abs(Polynomial{Monomial(4,{{"x", 1}}), Monomial(3, {})}));
    OneEquationOneVariableEqualitySolver solver;
    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(Equation(functionTerm1, "=", functionTerm2)));

    AlbaNumbers acceptedValues(solutionSet.getAcceptedValues());
    ASSERT_EQ(2U, acceptedValues.size());
    EXPECT_EQ(AlbaNumber(-2), acceptedValues.at(0));
    EXPECT_EQ(AlbaNumber::createFraction(-1, 3), acceptedValues.at(1));
}

TEST(OneEquationOneVariableEqualitySolverTest, AdditionFractionsInEquationIsSolved)
{
    Polynomial polynomial1{Monomial(2, {{"x", 1}}), Monomial(5, {})};
    Polynomial polynomial2{Monomial(5, {{"x", 1}})};
    Polynomial polynomial3{Monomial(1, {{"x", 1}}), Monomial(-1, {})};
    Expression expression1(createExpressionIfPossible({polynomial1, "/", 2}));
    Expression expression2(createExpressionIfPossible({polynomial2, "/", polynomial3}));
    Expression leftHandExpression(createExpressionIfPossible({expression1, "-", expression2}));
    OneEquationOneVariableEqualitySolver solver;

    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(Equation(leftHandExpression, "=", "x")));

    EXPECT_TRUE(solver.isSolved());
    EXPECT_TRUE(solver.isACompleteSolution());
    EXPECT_EQ(AlbaNumbers{-1}, solutionSet.getAcceptedValues());
}

TEST(OneEquationOneVariableEqualitySolverTest, SquareRootInEquationAreSolved){
    Polynomial polynomial1{Monomial(-5, {{"x", 1}}), Monomial(1, {})};
    Polynomial polynomial2{Monomial(-1, {{"x", 1}}), Monomial(1, {})};
    Expression expression1(createExpressionIfPossible({polynomial1, "^", AlbaNumber::createFraction(1, 2)}));    Expression expression2(createExpressionIfPossible({polynomial2, "^", AlbaNumber::createFraction(1, 2)}));
    Expression expressionLeft(createExpressionIfPossible({expression1, "+", expression2}));
    OneEquationOneVariableEqualitySolver solver;

    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(Equation(expressionLeft, "=", 2)));

    EXPECT_TRUE(solver.isSolved());
    EXPECT_FALSE(solver.isACompleteSolution());
    EXPECT_EQ(AlbaNumbers{0}, solutionSet.getAcceptedValues());
}

TEST(OneEquationOneVariableEqualitySolverTest, RadicalOverRadicalInEquationAreSolved){
    Polynomial polynomial1{Monomial(1, {{"x", 1}}), Monomial(-2, {})};
    Polynomial polynomial2{Monomial(1, {{"x", 1}}), Monomial(-3, {})};
    Expression numerator(createExpressionIfPossible({polynomial1, "^", AlbaNumber::createFraction(1, 3)}));    Expression denominator(createExpressionIfPossible({polynomial2, "^", AlbaNumber::createFraction(1, 5)}));
    Expression radicalOverRadical(createExpressionIfPossible({numerator, "/", denominator}));
    OneEquationOneVariableEqualitySolver solver;

    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(Equation(radicalOverRadical, "=", 0)));

    EXPECT_TRUE(solver.isSolved());
    EXPECT_FALSE(solver.isACompleteSolution());
    EXPECT_EQ(AlbaNumbers{2}, solutionSet.getAcceptedValues());
    EXPECT_EQ(AlbaNumbers{3}, solutionSet.getRejectedValues());
}

}
}