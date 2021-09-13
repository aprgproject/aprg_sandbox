#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Solution/Solver/OneEquationOneVariable/OneEquationOneVariableNonEqualitySolver.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Math/Number/Interval/AlbaNumberIntervalHelpers.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba{

namespace algebra
{

TEST(OneEquationOneVariableNonEqualitySolverTest, ConstructionWorks)
{
    OneEquationOneVariableNonEqualitySolver();
}

TEST(OneEquationOneVariableNonEqualitySolverTest, EqualityOperatorsAreNotSolved)
{
    OneEquationOneVariableNonEqualitySolver solver;

    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(Equation(Term("x"), "=", Term("x"))));

    EXPECT_FALSE(solver.isSolved());
    EXPECT_FALSE(solver.isACompleteSolution());
    EXPECT_TRUE(solutionSet.isEmpty());
}

TEST(OneEquationOneVariableNonEqualitySolverTest, MultipleVariableEquationsAreNotSolved)
{
    OneEquationOneVariableNonEqualitySolver solver;

    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(Equation(Term("x"), "<", Term("y"))));

    EXPECT_FALSE(solver.isSolved());
    EXPECT_FALSE(solver.isACompleteSolution());
    EXPECT_TRUE(solutionSet.isEmpty());
}

TEST(OneEquationOneVariableNonEqualitySolverTest, EquationsThatAreAlwaysSatisfiedResultsInInfiniteRange)
{
    OneEquationOneVariableNonEqualitySolver solver;

    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(Equation(Term(2), "<", Term(3))));

    EXPECT_TRUE(solver.isSolved());
    EXPECT_TRUE(solver.isACompleteSolution());
    AlbaNumberIntervals actualIntervals(solutionSet.getAcceptedIntervals());
    ASSERT_EQ(1U, actualIntervals.size());
    EXPECT_EQ(createAllRealValuesInterval(), actualIntervals.at(0));
}

TEST(OneEquationOneVariableNonEqualitySolverTest, PolynomialAreSolvedCorrectly)
{
    OneEquationOneVariableNonEqualitySolver solver;

    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(Equation(Term(Monomial(1, {{"x", 4}})), "<", Term(16))));

    EXPECT_TRUE(solver.isSolved());
    EXPECT_TRUE(solver.isACompleteSolution());
    AlbaNumberIntervals const& acceptedIntervals(solutionSet.getAcceptedIntervals());
    ASSERT_EQ(1U, acceptedIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(-2), createOpenEndpoint(2)), acceptedIntervals.at(0));
}

TEST(OneEquationOneVariableNonEqualitySolverTest, PolynomialOverPolynomialAreSolvedCorrectly)
{
    Polynomial numerator{Monomial(1, {{"x", 2}}), Monomial(-25, {})};
    Polynomial denominator{Monomial(1, {{"x", 2}}), Monomial(-36, {})};
    Expression expression(createExpressionIfPossible({Term(numerator), Term("/"), Term(denominator)}));
    OneEquationOneVariableNonEqualitySolver solver;

    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(Equation(Term(expression), ">=", Term(Constant(0)))));

    EXPECT_TRUE(solver.isSolved());
    EXPECT_TRUE(solver.isACompleteSolution());
    AlbaNumberIntervals const& acceptedIntervals(solutionSet.getAcceptedIntervals());
    ASSERT_EQ(3U, acceptedIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createNegativeInfinityOpenEndpoint(), createOpenEndpoint(-6)), acceptedIntervals.at(0));
    EXPECT_EQ(AlbaNumberInterval(createCloseEndpoint(-5), createCloseEndpoint(5)), acceptedIntervals.at(1));
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(6), createPositiveInfinityOpenEndpoint()), acceptedIntervals.at(2));
}

TEST(OneEquationOneVariableNonEqualitySolverTest, XToTheXAreNotSolved){
    Expression expression(createExpressionIfPossible({Term("x"), Term("^"), Term("x")}));
    OneEquationOneVariableNonEqualitySolver solver;
    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(Equation(Term(expression), ">", Term(823543))));

    EXPECT_FALSE(solver.isSolved());
    EXPECT_FALSE(solver.isACompleteSolution());
    AlbaNumberIntervals const& acceptedIntervals(solutionSet.getAcceptedIntervals());
    EXPECT_TRUE(acceptedIntervals.empty());
}

TEST(OneEquationOneVariableNonEqualitySolverTest, XToTheXWithNegativeSolutionAreNotSolved)
{
    Expression expression(createExpressionIfPossible({Term("x"), Term("^"), Term("x")}));
    OneEquationOneVariableNonEqualitySolver solver;

    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(Equation(Term(expression), ">", Term(-823543))));

    EXPECT_FALSE(solver.isSolved());
    EXPECT_FALSE(solver.isACompleteSolution());
    AlbaNumberIntervals const& acceptedIntervals(solutionSet.getAcceptedIntervals());
    EXPECT_TRUE(acceptedIntervals.empty());
}

TEST(OneEquationOneVariableNonEqualitySolverTest, AbsoluteValueFunctionsAreSolved)
{
    Term functionTerm(Functions::abs(createExpressionIfPossible({Term("x")})));
    OneEquationOneVariableNonEqualitySolver solver;

    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(Equation(functionTerm, "<", Term(526))));

    EXPECT_TRUE(solver.isSolved());
    EXPECT_TRUE(solver.isACompleteSolution());
    AlbaNumberIntervals const& acceptedIntervals(solutionSet.getAcceptedIntervals());
    ASSERT_EQ(1U, acceptedIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(-526), createOpenEndpoint(526)), acceptedIntervals.at(0));
}

TEST(OneEquationOneVariableNonEqualitySolverTest, AbsoluteValueFunctionWithInputExpressionAreSolved)
{
    Term functionTerm(Functions::abs(createExpressionIfPossible({Term("x"), Term("+"), Term(100)})));
    OneEquationOneVariableNonEqualitySolver solver;

    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(Equation(functionTerm, ">=", Term(526))));

    EXPECT_TRUE(solver.isSolved());
    EXPECT_TRUE(solver.isACompleteSolution());
    AlbaNumberIntervals const& acceptedIntervals(solutionSet.getAcceptedIntervals());
    ASSERT_EQ(2U, acceptedIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createNegativeInfinityOpenEndpoint(), createCloseEndpoint(-626)), acceptedIntervals.at(0));
    EXPECT_EQ(AlbaNumberInterval(createCloseEndpoint(426), createPositiveInfinityOpenEndpoint()), acceptedIntervals.at(1));
}

TEST(OneEquationOneVariableNonEqualitySolverTest, AbsoluteValueFunctionInDenominatorAreSolved){
    Term functionTerm(Functions::abs(
                          createExpressionIfPossible({Term(Polynomial{Monomial(2, {{"x", 1}}), Monomial(3, {})}) })));
    Term fractionTerm(createExpressionIfPossible({Term(1), Term("/"), functionTerm}));    OneEquationOneVariableNonEqualitySolver solver;

    SolutionSet solutionSet(
                solver.calculateSolutionAndReturnSolutionSet(
                    Equation(fractionTerm, "<", Term(AlbaNumber::createFraction(1, 4)))));

    EXPECT_TRUE(solver.isSolved());
    EXPECT_TRUE(solver.isACompleteSolution());
    AlbaNumberIntervals const& acceptedIntervals(solutionSet.getAcceptedIntervals());
    ASSERT_EQ(2U, acceptedIntervals.size());
    EXPECT_EQ(
                AlbaNumberInterval(
                    createNegativeInfinityOpenEndpoint(),
                    createOpenEndpoint(AlbaNumber::createFraction(-7, 2))),
                acceptedIntervals.at(0));
    EXPECT_EQ(
                AlbaNumberInterval(
                    createOpenEndpoint(AlbaNumber::createFraction(1, 2)),
                    createPositiveInfinityOpenEndpoint()),
                acceptedIntervals.at(1));
}
TEST(OneEquationOneVariableNonEqualitySolverTest, PolynomialsInEquationAreSolved)
{
    Polynomial polynomialLeft{Monomial(AlbaNumber::createFraction(2, 3), {{"x", 1}}), Monomial(-4, {})};    Polynomial polynomialRight{Monomial(5, {{"x", 1}}), Monomial(9, {})};
    OneEquationOneVariableNonEqualitySolver solver;

    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(Equation(Term(polynomialLeft), "<", Term(polynomialRight))));

    EXPECT_TRUE(solver.isSolved());
    EXPECT_TRUE(solver.isACompleteSolution());
    AlbaNumberIntervals const& acceptedIntervals(solutionSet.getAcceptedIntervals());
    ASSERT_EQ(1U, acceptedIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(-3), createPositiveInfinityOpenEndpoint()), acceptedIntervals.at(0));
}

}
}