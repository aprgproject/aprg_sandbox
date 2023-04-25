#include <Algebra/Solution/Solver/DiophantineEquation/LinearDiophantineEquationSolver.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algebra {

TEST(LinearDiophantineEquationSolverTest, ConstructionWorks) { LinearDiophantineEquationSolver(); }

TEST(
    LinearDiophantineEquationSolverTest,
    CalculateSolutionAndReturnSolutionSetWorksAsDoesNotFindASolutionForNonEqualityEquation) {
    LinearDiophantineEquationSolver solver;
    Polynomial polynomial{Monomial(1, {{"x", 1}}), Monomial(1, {{"y", 1}})};
    Equation equation(polynomial, ">", 4);

    MultipleVariableSolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(equation));

    EXPECT_FALSE(solver.isSolved());
    EXPECT_FALSE(solver.isACompleteSolution());
    EXPECT_EQ(0U, solutionSet.getNumberOfVariablesWithSolutions());
}

TEST(LinearDiophantineEquationSolverTest, CalculateSolutionAndReturnSolutionSetWorksForThreeMonomials) {
    LinearDiophantineEquationSolver solver;
    Polynomial polynomial{Monomial(39, {{"x", 1}}), Monomial(15, {{"y", 1}})};
    Equation equation(polynomial, "=", 12);

    MultipleVariableSolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(equation));

    EXPECT_TRUE(solver.isSolved());
    EXPECT_FALSE(solver.isACompleteSolution());
    EXPECT_EQ(2U, solutionSet.getNumberOfVariablesWithSolutions());
    EXPECT_EQ(AlbaNumbers{8}, solutionSet.getSolutionSetForVariable("x").getAcceptedValues());
    EXPECT_EQ(AlbaNumbers{-20}, solutionSet.getSolutionSetForVariable("y").getAcceptedValues());
}

}  // namespace algebra

}  // namespace alba
