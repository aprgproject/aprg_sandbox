#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Solution/Solver/OneEquationOneUnknownNonEqualitySolver.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(OneEquationOneUnknownNonEqualitySolverTest, ConstructionWorks)
{
    OneEquationOneUnknownNonEqualitySolver();
}

TEST(OneEquationOneUnknownNonEqualitySolverTest, EqualityOperatorsAreNotSolved)
{
    OneEquationOneUnknownNonEqualitySolver solver;

    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(Equation(Term("x"), "=", Term("x"))));

    EXPECT_FALSE(solver.isSolved());
    EXPECT_FALSE(solver.isACompleteSolution());
    EXPECT_TRUE(solutionSet.isEmpty());
}

TEST(OneEquationOneUnknownNonEqualitySolverTest, MultipleVariableEquationsAreNotSolved)
{
    OneEquationOneUnknownNonEqualitySolver solver;

    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(Equation(Term("x"), "<", Term("y"))));

    EXPECT_FALSE(solver.isSolved());
    EXPECT_FALSE(solver.isACompleteSolution());
    EXPECT_TRUE(solutionSet.isEmpty());
}

TEST(OneEquationOneUnknownNonEqualitySolverTest, EquationsThatAreAlwaysSatisfiedResultsInInfiniteRange)
{
    OneEquationOneUnknownNonEqualitySolver solver;

    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(Equation(Term(2), "<", Term(3))));

    EXPECT_TRUE(solver.isSolved());
    EXPECT_TRUE(solver.isACompleteSolution());
    AlbaNumberIntervals actualIntervals(solutionSet.getAcceptedIntervals());
    ASSERT_EQ(1u, actualIntervals.size());
    EXPECT_EQ(createAllRealValuesInterval(), actualIntervals.at(0));
}

TEST(OneEquationOneUnknownNonEqualitySolverTest, PolynomialAreSolvedCorrectly)
{
    OneEquationOneUnknownNonEqualitySolver solver;

    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(Equation(Term(Monomial(1, {{"x", 4}})), "<", Term(16))));

    EXPECT_TRUE(solver.isSolved());
    EXPECT_TRUE(solver.isACompleteSolution());
    AlbaNumberIntervals const& acceptedIntervals(solutionSet.getAcceptedIntervals());
    ASSERT_EQ(1u, acceptedIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(-2), createOpenEndpoint(2)), acceptedIntervals.at(0));
}

TEST(OneEquationOneUnknownNonEqualitySolverTest, PolynomialOverPolynomialAreSolvedCorrectly)
{
    Polynomial numerator{Monomial(1, {{"x", 2}}), Monomial(-25, {})};
    Polynomial denominator{Monomial(1, {{"x", 2}}), Monomial(-36, {})};
    Expression expression(createExpressionIfPossible({Term(numerator), Term("/"), Term(denominator)}));
    OneEquationOneUnknownNonEqualitySolver solver;

    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(Equation(Term(expression), ">=", Term(Constant(0)))));

    EXPECT_TRUE(solver.isSolved());
    EXPECT_TRUE(solver.isACompleteSolution());
    AlbaNumberIntervals const& acceptedIntervals(solutionSet.getAcceptedIntervals());
    ASSERT_EQ(3u, acceptedIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(AlbaNumber::Value::NegativeInfinity), createOpenEndpoint(-6)), acceptedIntervals.at(0));
    EXPECT_EQ(AlbaNumberInterval(createCloseEndpoint(-5), createCloseEndpoint(5)), acceptedIntervals.at(1));
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(6), createOpenEndpoint(AlbaNumber::Value::PositiveInfinity)), acceptedIntervals.at(2));
}

TEST(OneEquationOneUnknownNonEqualitySolverTest, XToTheXAreNotSolved)
{
    Expression expression(createExpressionIfPossible({Term("x"), Term("^"), Term("x")}));
    OneEquationOneUnknownNonEqualitySolver solver;

    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(Equation(Term(expression), ">", Term(823543))));

    EXPECT_FALSE(solver.isSolved());
    EXPECT_FALSE(solver.isACompleteSolution());
    AlbaNumberIntervals const& acceptedIntervals(solutionSet.getAcceptedIntervals());
    EXPECT_TRUE(acceptedIntervals.empty());
}

TEST(OneEquationOneUnknownNonEqualitySolverTest, XToTheXWithNegativeSolutionAreNotSolved)
{
    Expression expression(createExpressionIfPossible({Term("x"), Term("^"), Term("x")}));
    OneEquationOneUnknownNonEqualitySolver solver;

    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(Equation(Term(expression), ">", Term(-823543))));

    EXPECT_FALSE(solver.isSolved());
    EXPECT_FALSE(solver.isACompleteSolution());
    AlbaNumberIntervals const& acceptedIntervals(solutionSet.getAcceptedIntervals());
    EXPECT_TRUE(acceptedIntervals.empty());
}

TEST(OneEquationOneUnknownNonEqualitySolverTest, AbsoluteValueFunctionsAreSolved)
{
    Term functionTerm(Functions::abs(createExpressionIfPossible({Term("x")})));
    OneEquationOneUnknownNonEqualitySolver solver;

    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(Equation(functionTerm, "<", Term(526))));

    EXPECT_TRUE(solver.isSolved());
    EXPECT_TRUE(solver.isACompleteSolution());
    AlbaNumberIntervals const& acceptedIntervals(solutionSet.getAcceptedIntervals());
    ASSERT_EQ(1u, acceptedIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(-526), createOpenEndpoint(526)), acceptedIntervals.at(0));
}

TEST(OneEquationOneUnknownNonEqualitySolverTest, AbsoluteValueFunctionWithInputExpressionAreSolved)
{
    Term functionTerm(Functions::abs(createExpressionIfPossible({Term("x"), Term("+"), Term(100)})));
    OneEquationOneUnknownNonEqualitySolver solver;

    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(Equation(functionTerm, ">=", Term(526))));

    EXPECT_TRUE(solver.isSolved());
    EXPECT_TRUE(solver.isACompleteSolution());
    AlbaNumberIntervals const& acceptedIntervals(solutionSet.getAcceptedIntervals());
    ASSERT_EQ(2u, acceptedIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(AlbaNumber::Value::NegativeInfinity), createCloseEndpoint(-626)), acceptedIntervals.at(0));
    EXPECT_EQ(AlbaNumberInterval(createCloseEndpoint(426), createOpenEndpoint(AlbaNumber::Value::PositiveInfinity)), acceptedIntervals.at(1));
}

TEST(OneEquationOneUnknownNonEqualitySolverTest, AbsoluteValueFunctionInDenominatorAreSolved)
{
    Term functionTerm(Functions::abs(
                          createExpressionIfPossible({Term(Polynomial{Monomial(2, {{"x", 1}}), Monomial(3, {})}) })));
    Term fractionTerm(createExpressionIfPossible({Term(1), Term("/"), functionTerm}));
    OneEquationOneUnknownNonEqualitySolver solver;

    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(Equation(fractionTerm, "<", Term(AlbaNumber(1, 4)))));

    EXPECT_TRUE(solver.isSolved());
    EXPECT_TRUE(solver.isACompleteSolution());
    AlbaNumberIntervals const& acceptedIntervals(solutionSet.getAcceptedIntervals());
    ASSERT_EQ(2u, acceptedIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(AlbaNumber::Value::NegativeInfinity), createOpenEndpoint(AlbaNumber(-7, 2))), acceptedIntervals.at(0));
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(AlbaNumber(1, 2)), createOpenEndpoint(AlbaNumber::Value::PositiveInfinity)), acceptedIntervals.at(1));
}

}

}