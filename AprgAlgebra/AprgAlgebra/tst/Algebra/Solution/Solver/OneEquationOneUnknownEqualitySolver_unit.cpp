#include <Algebra/Solution/Solver/OneEquationOneUnknownEqualitySolver.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(OneEquationOneUnknownEqualitySolverTest, ConstructionWorks)
{
    OneEquationOneUnknownEqualitySolver(Equation(Term("x"), "=", Term("y")));
}

TEST(OneEquationOneUnknownEqualitySolverTest, NonEqualityOperatorsAreNotSolved)
{
    OneEquationOneUnknownEqualitySolver solver(Equation(Term("x"), "<", Term("x")));

    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet());

    EXPECT_FALSE(solver.isSolved());
    EXPECT_FALSE(solver.isACompleteSolution());
    EXPECT_TRUE(solutionSet.isEmpty());
}
TEST(OneEquationOneUnknownEqualitySolverTest, MultipleVariableEquationsAreNotSolved)
{
    OneEquationOneUnknownEqualitySolver solver(Equation(Term("x"), "=", Term("y")));

    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet());

    EXPECT_FALSE(solver.isSolved());
    EXPECT_FALSE(solver.isACompleteSolution());
    EXPECT_TRUE(solutionSet.isEmpty());
}
TEST(OneEquationOneUnknownEqualitySolverTest, EquationsThatAreAlwaysSatisfiedResultsInInfiniteRange)
{
    OneEquationOneUnknownEqualitySolver solver(Equation(Term("x"), "=", Term("x")));

    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet());

    EXPECT_TRUE(solver.isSolved());
    EXPECT_TRUE(solver.isACompleteSolution());
    AlbaNumberIntervals actualIntervals(solutionSet.getAcceptedIntervals());
    ASSERT_EQ(1u, actualIntervals.size());
    EXPECT_EQ(createAllRealValuesInterval(), actualIntervals.at(0));
}

TEST(OneEquationOneUnknownEqualitySolverTest, PolynomialAreSolvedCorrectly){
    OneEquationOneUnknownEqualitySolver solver(Equation(Term(Monomial(1, {{"x", 4}})), "=", Term(16)));

    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet());

    EXPECT_TRUE(solver.isSolved());
    EXPECT_TRUE(solver.isACompleteSolution());
    AlbaNumbers const& acceptedValues(solutionSet.getAcceptedValues());
    ASSERT_EQ(2u, acceptedValues.size());
    EXPECT_EQ(AlbaNumber(-2), acceptedValues.at(0));    EXPECT_EQ(AlbaNumber(2), acceptedValues.at(1));
}

TEST(OneEquationOneUnknownEqualitySolverTest, PolynomialOverPolynomialAreSolvedCorrectly){
    Polynomial numerator{Monomial(1, {{"x", 2}}), Monomial(-25, {})};
    Polynomial denominator{Monomial(1, {{"x", 2}}), Monomial(-36, {})};
    Expression expression(createExpressionIfPossible({Term(numerator), Term("/"), Term(denominator)}));
    OneEquationOneUnknownEqualitySolver solver(Equation(Term(expression), "=", Term(Constant(0))));

    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet());

    EXPECT_TRUE(solver.isSolved());
    EXPECT_TRUE(solver.isACompleteSolution());
    AlbaNumbers const& acceptedValues(solutionSet.getAcceptedValues());
    ASSERT_EQ(2u, acceptedValues.size());
    EXPECT_EQ(AlbaNumber(-5), acceptedValues.at(0));    EXPECT_EQ(AlbaNumber(5), acceptedValues.at(1));
    AlbaNumbers const& rejectedValues(solutionSet.getRejectedValues());
    ASSERT_EQ(2u, rejectedValues.size());
    EXPECT_EQ(AlbaNumber(-6), rejectedValues.at(0));    EXPECT_EQ(AlbaNumber(6), rejectedValues.at(1));
}

TEST(OneEquationOneUnknownEqualitySolverTest, XToTheXAreSolvedCorrectly)
{
    Expression expression(createExpressionIfPossible({Term("x"), Term("^"), Term("x")}));
    OneEquationOneUnknownEqualitySolver solver(Equation(Term(expression), "=", Term(823543)));

    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet());

    EXPECT_TRUE(solver.isSolved());
    EXPECT_FALSE(solver.isACompleteSolution());
    AlbaNumbers const& acceptedValues(solutionSet.getAcceptedValues());
    ASSERT_EQ(1u, acceptedValues.size());
    EXPECT_EQ(AlbaNumber(7), acceptedValues.at(0));
}

TEST(OneEquationOneUnknownEqualitySolverTest, XToTheXWithNegativeSolutionAreNotSolved)
{
    Expression expression(createExpressionIfPossible({Term("x"), Term("^"), Term("x")}));
    OneEquationOneUnknownEqualitySolver solver(Equation(Term(expression), "=", Term(-823543)));
    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet());

    EXPECT_FALSE(solver.isSolved());
    EXPECT_FALSE(solver.isACompleteSolution());
    AlbaNumbers const& acceptedValues(solutionSet.getAcceptedValues());
    EXPECT_EQ(0u, acceptedValues.size());
}
}

}