#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Solution/Solver/OneEquationOneVariable/OneEquationOneVariableNonEqualitySolver.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Common/Math/Number/Interval/AlbaNumberIntervalHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(OneEquationOneVariableNonEqualitySolverTest, ConstructionWorks)
{
    OneEquationOneVariableNonEqualitySolver();
}

TEST(OneEquationOneVariableNonEqualitySolverTest, EqualityOperatorsAreNotSolved)
{
    OneEquationOneVariableNonEqualitySolver solver;

    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(Equation("x", "=", "x")));

    EXPECT_FALSE(solver.isSolved());
    EXPECT_FALSE(solver.isACompleteSolution());
    EXPECT_TRUE(solutionSet.isEmpty());
}

TEST(OneEquationOneVariableNonEqualitySolverTest, MultipleVariableEquationsAreNotSolved)
{
    OneEquationOneVariableNonEqualitySolver solver;

    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(Equation("x", "<", "y")));

    EXPECT_FALSE(solver.isSolved());
    EXPECT_FALSE(solver.isACompleteSolution());
    EXPECT_TRUE(solutionSet.isEmpty());
}

TEST(OneEquationOneVariableNonEqualitySolverTest, EquationsThatAreAlwaysSatisfiedResultsInInfiniteRange)
{
    OneEquationOneVariableNonEqualitySolver solver;

    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(Equation(2, "<", 3)));

    EXPECT_TRUE(solver.isSolved());
    EXPECT_TRUE(solver.isACompleteSolution());
    AlbaNumberIntervals actualIntervals(solutionSet.getAcceptedIntervals());
    ASSERT_EQ(1U, actualIntervals.size());
    EXPECT_EQ(createAllRealValuesInterval(), actualIntervals.at(0));
}

TEST(OneEquationOneVariableNonEqualitySolverTest, PolynomialAreSolvedCorrectly)
{
    OneEquationOneVariableNonEqualitySolver solver;

    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(Equation(Monomial(1, {{"x", 4}}), "<", 16)));

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
    Expression expression(createExpressionIfPossible({numerator, "/", denominator}));
    OneEquationOneVariableNonEqualitySolver solver;

    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(Equation(expression, ">=", 0)));

    EXPECT_TRUE(solver.isSolved());
    EXPECT_TRUE(solver.isACompleteSolution());
    AlbaNumberIntervals const& acceptedIntervals(solutionSet.getAcceptedIntervals());
    ASSERT_EQ(3U, acceptedIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createNegativeInfinityOpenEndpoint(), createOpenEndpoint(-6)), acceptedIntervals.at(0));
    EXPECT_EQ(AlbaNumberInterval(createCloseEndpoint(-5), createCloseEndpoint(5)), acceptedIntervals.at(1));
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(6), createPositiveInfinityOpenEndpoint()), acceptedIntervals.at(2));
}

TEST(OneEquationOneVariableNonEqualitySolverTest, XToTheXAreNotSolved)
{
    Expression expression(createExpressionIfPossible({"x", "^", "x"}));
    OneEquationOneVariableNonEqualitySolver solver;

    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(Equation(expression, ">", 823543)));

    EXPECT_FALSE(solver.isSolved());
    EXPECT_FALSE(solver.isACompleteSolution());
    AlbaNumberIntervals const& acceptedIntervals(solutionSet.getAcceptedIntervals());
    EXPECT_TRUE(acceptedIntervals.empty());
}

TEST(OneEquationOneVariableNonEqualitySolverTest, XToTheXWithNegativeSolutionAreNotSolved)
{
    Expression expression(createExpressionIfPossible({"x", "^", "x"}));
    OneEquationOneVariableNonEqualitySolver solver;

    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(Equation(expression, ">", -823543)));

    EXPECT_FALSE(solver.isSolved());
    EXPECT_FALSE(solver.isACompleteSolution());
    AlbaNumberIntervals const& acceptedIntervals(solutionSet.getAcceptedIntervals());
    EXPECT_TRUE(acceptedIntervals.empty());
}

TEST(OneEquationOneVariableNonEqualitySolverTest, AbsoluteValueFunctionsAreSolved)
{
    Term functionTerm(Functions::abs(createExpressionIfPossible({"x"})));
    OneEquationOneVariableNonEqualitySolver solver;

    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(Equation(functionTerm, "<", 526)));

    EXPECT_TRUE(solver.isSolved());
    EXPECT_TRUE(solver.isACompleteSolution());
    AlbaNumberIntervals const& acceptedIntervals(solutionSet.getAcceptedIntervals());
    ASSERT_EQ(1U, acceptedIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(-526), createOpenEndpoint(526)), acceptedIntervals.at(0));
}

TEST(OneEquationOneVariableNonEqualitySolverTest, AbsoluteValueFunctionWithInputExpressionAreSolved)
{
    Term functionTerm(Functions::abs(createExpressionIfPossible({"x", "+", 100})));
    OneEquationOneVariableNonEqualitySolver solver;

    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(Equation(functionTerm, ">=", 526)));

    EXPECT_TRUE(solver.isSolved());
    EXPECT_TRUE(solver.isACompleteSolution());
    AlbaNumberIntervals const& acceptedIntervals(solutionSet.getAcceptedIntervals());
    ASSERT_EQ(2U, acceptedIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createNegativeInfinityOpenEndpoint(), createCloseEndpoint(-626)), acceptedIntervals.at(0));
    EXPECT_EQ(AlbaNumberInterval(createCloseEndpoint(426), createPositiveInfinityOpenEndpoint()), acceptedIntervals.at(1));
}

TEST(OneEquationOneVariableNonEqualitySolverTest, AbsoluteValueFunctionInDenominatorAreSolved)
{
    Term functionTerm(Functions::abs(
                          createExpressionIfPossible({Polynomial{Monomial(2, {{"x", 1}}), Monomial(3, {})}})));
    Term fractionTerm(createExpressionIfPossible({1, "/", functionTerm}));
    OneEquationOneVariableNonEqualitySolver solver;

    SolutionSet solutionSet(
                solver.calculateSolutionAndReturnSolutionSet(
                    Equation(fractionTerm, "<", AlbaNumber::createFraction(1, 4))));

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
    Polynomial polynomialLeft{Monomial(AlbaNumber::createFraction(2, 3), {{"x", 1}}), Monomial(-4, {})};
    Polynomial polynomialRight{Monomial(5, {{"x", 1}}), Monomial(9, {})};
    OneEquationOneVariableNonEqualitySolver solver;

    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(Equation(polynomialLeft, "<", polynomialRight)));

    EXPECT_TRUE(solver.isSolved());
    EXPECT_TRUE(solver.isACompleteSolution());
    AlbaNumberIntervals const& acceptedIntervals(solutionSet.getAcceptedIntervals());
    ASSERT_EQ(1U, acceptedIntervals.size());
    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(-3), createPositiveInfinityOpenEndpoint()), acceptedIntervals.at(0));
}

// There is no capability for TermsOverTerms solution yet in non equality solver. This is hard.
//TEST(OneEquationOneVariableNonEqualitySolverTest, RadicalOverRadicalInEquationAreSolved)
//{
//    Polynomial polynomial1{Monomial(1, {{"x", 1}}), Monomial(-2, {})};
//    Polynomial polynomial2{Monomial(1, {{"x", 1}}), Monomial(-3, {})};
//    Expression numerator(createExpressionIfPossible({polynomial1, "^", AlbaNumber::createFraction(1, 3)}));
//    Expression denominator(createExpressionIfPossible({polynomial2, "^", AlbaNumber::createFraction(1, 5)}));
//    Expression radicalOverRadical(createExpressionIfPossible({numerator, "/", denominator}));
//    OneEquationOneVariableNonEqualitySolver solver;

//    SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(Equation(radicalOverRadical, "<=", 0)));

//    EXPECT_TRUE(solver.isSolved());
//    EXPECT_TRUE(solver.isACompleteSolution());
//    AlbaNumberIntervals const& acceptedIntervals(solutionSet.getAcceptedIntervals());
//    ASSERT_EQ(1U, acceptedIntervals.size());
//    EXPECT_EQ(AlbaNumberInterval(createOpenEndpoint(-3), createPositiveInfinityOpenEndpoint()), acceptedIntervals.at(0));
//}

}

}
