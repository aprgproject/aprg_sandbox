#include <Algebra/Solution/Solver/DiophantineEquation/LinearDiophantineEquationCoefficientSolver.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

namespace
{
using SolutionStatus = LinearDiophantineEquationCoefficientSolver::SolutionStatus;
}

TEST(LinearDiophantineEquationCoefficientSolverTest, WorksWhenAAndBAreZero)
{
    LinearDiophantineEquationCoefficientSolver solver(0, 0, 12);

    EXPECT_FALSE(solver.isSolved());
    EXPECT_EQ(SolutionStatus::NoSolution, solver.getSolutionStatus());
    EXPECT_EQ(0, solver.getX());
    EXPECT_EQ(0, solver.getY());
}

TEST(LinearDiophantineEquationCoefficientSolverTest, WorksWhenCIsZero)
{
    LinearDiophantineEquationCoefficientSolver solver(39, 15, 0);

    EXPECT_FALSE(solver.isSolved());
    EXPECT_EQ(SolutionStatus::InfiniteSolutions, solver.getSolutionStatus());
    EXPECT_EQ(0, solver.getX());
    EXPECT_EQ(0, solver.getY());
}

TEST(LinearDiophantineEquationCoefficientSolverTest, WorksWhenAAndBAndCAreZero)
{
    LinearDiophantineEquationCoefficientSolver solver(0, 0, 0);

    EXPECT_FALSE(solver.isSolved());
    EXPECT_EQ(SolutionStatus::InfiniteSolutions, solver.getSolutionStatus());
    EXPECT_EQ(0, solver.getX());
    EXPECT_EQ(0, solver.getY());
}

TEST(LinearDiophantineEquationCoefficientSolverTest, WorksWhenAreNonIntegers)
{
    LinearDiophantineEquationCoefficientSolver solver(1.2, 3.4, 5.6);

    EXPECT_FALSE(solver.isSolved());
    EXPECT_EQ(SolutionStatus::CannotBeSolved, solver.getSolutionStatus());
    EXPECT_EQ(0, solver.getX());
    EXPECT_EQ(0, solver.getY());
}

TEST(LinearDiophantineEquationCoefficientSolverTest, WorksWhenCIsNotDivisibleWithGcfOfAAndB)
{
    LinearDiophantineEquationCoefficientSolver solver(39, 15, 13);

    EXPECT_FALSE(solver.isSolved());
    EXPECT_EQ(SolutionStatus::CannotBeSolved, solver.getSolutionStatus());
    EXPECT_EQ(0, solver.getX());
    EXPECT_EQ(0, solver.getY());
}

TEST(LinearDiophantineEquationCoefficientSolverTest, WorksOnExample1)
{
    LinearDiophantineEquationCoefficientSolver solver(39, 15, 12);

    EXPECT_TRUE(solver.isSolved());
    EXPECT_EQ(SolutionStatus::Solved, solver.getSolutionStatus());
    EXPECT_EQ(8, solver.getX());
    EXPECT_EQ(-20, solver.getY());
}

TEST(LinearDiophantineEquationCoefficientSolverTest, WorksOnExample2)
{
    LinearDiophantineEquationCoefficientSolver solver(47, 30, 1);

    EXPECT_TRUE(solver.isSolved());
    EXPECT_EQ(SolutionStatus::Solved, solver.getSolutionStatus());
    EXPECT_EQ(-7, solver.getX());
    EXPECT_EQ(11, solver.getY());
}

TEST(LinearDiophantineEquationCoefficientSolverTest, GetAnotherXValueAndGetAnotherYValueWorksOnExample1)
{
    LinearDiophantineEquationCoefficientSolver solver(39, 15, 12);

    EXPECT_EQ(8, solver.getAnotherXValue(0));
    EXPECT_EQ(-20, solver.getAnotherYValue(0));
    EXPECT_EQ(13, solver.getAnotherXValue(1));
    EXPECT_EQ(-33, solver.getAnotherYValue(1));
    EXPECT_EQ(18, solver.getAnotherXValue(2));
    EXPECT_EQ(-46, solver.getAnotherYValue(2));
}

}

}
