#include <Algebra/Solution/Solver/Simplex/SimplexSolver.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(SimplexSolverTest, SimplexWorksOnBrewersProblem)
{
    Equations constraints;
    constraints.emplace_back(Polynomial{Monomial(5, {{"A", 1}}), Monomial(15, {{"B", 1}})}, "<=", 480);
    constraints.emplace_back(Polynomial{Monomial(4, {{"A", 1}}), Monomial(4, {{"B", 1}})}, "<=", 160);
    constraints.emplace_back(Polynomial{Monomial(35, {{"A", 1}}), Monomial(20, {{"B", 1}})}, "<=", 1190);
    Polynomial objectiveFunction{Monomial(13, {{"A", 1}}), Monomial(23, {{"B", 1}})};

    SimplexSolver solver(constraints, objectiveFunction);

    Equations solutionEquations;
    solutionEquations.emplace_back(Polynomial{Monomial(1, {{"B", 1}}), Monomial(-28, {})}, "=", 0);
    solutionEquations.emplace_back(Polynomial{Monomial(1, {{"A", 1}}), Monomial(-12, {})}, "=", 0);
    EXPECT_TRUE(solver.isOptimized());
    EXPECT_EQ(AlbaNumber(800), solver.getOptimizedObjectiveValue());
    EXPECT_EQ(solutionEquations, solver.getSolutionEquations());
}

TEST(SimplexSolverTest, SimplexWorksOnBrewersProblemWithZeroEquation)
{
    //Equal equations ruins current simplex algorithm (zero equation here)

    Equations constraints;
    constraints.emplace_back(Polynomial{Monomial(5, {{"A", 1}}), Monomial(15, {{"B", 1}})}, "<=", 480);
    constraints.emplace_back(Monomial(25, {{"C", 1}}), "=", 0); // Zero Equation
    constraints.emplace_back(Polynomial{Monomial(4, {{"A", 1}}), Monomial(4, {{"B", 1}})}, "<=", 160);
    constraints.emplace_back(Polynomial{Monomial(35, {{"A", 1}}), Monomial(20, {{"B", 1}})}, "<=", 1190);
    Polynomial objectiveFunction{Monomial(13, {{"A", 1}}), Monomial(23, {{"B", 1}}), Monomial(100, {{"C", 1}})};

    SimplexSolver solver(constraints, objectiveFunction);

    Equations solutionEquations;
    solutionEquations.emplace_back("C", "=", 0);
    solutionEquations.emplace_back(Polynomial{Monomial(1, {{"B", 1}}), Monomial(-14, {})}, "=", 0);
    solutionEquations.emplace_back(Polynomial{Monomial(1, {{"A", 1}}), Monomial(-26, {})}, "=", 0);
    EXPECT_FALSE(solver.isOptimized());
    EXPECT_EQ(AlbaNumber(660), solver.getOptimizedObjectiveValue());
    EXPECT_EQ(solutionEquations, solver.getSolutionEquations());
}

TEST(SimplexSolverTest, SimplexWorksOnExample1)
{
    Equations constraints;
    constraints.emplace_back(Polynomial{Monomial(1, {{"A", 1}}), Monomial(3, {{"B", 1}}), Monomial(2, {{"C", 1}})}, "<=", 10);
    constraints.emplace_back(Polynomial{Monomial(-1, {{"A", 1}}), Monomial(-5, {{"B", 1}}), Monomial(-1, {{"C", 1}})}, ">=", -8);
    Polynomial objectiveFunction{Monomial(8, {{"A", 1}}), Monomial(10, {{"B", 1}}), Monomial(7, {{"C", 1}})};

    SimplexSolver solver(constraints, objectiveFunction);

    Equations solutionEquations;
    solutionEquations.emplace_back(Polynomial{Monomial(2, {{"B", 1}}), Monomial(-1, {{"C", 1}}), Monomial(2, {})}, "=", 0);
    solutionEquations.emplace_back(Polynomial{Monomial(1, {{"A", 1}}), Monomial(5, {{"B", 1}}), Monomial(1, {{"C", 1}}), Monomial(-8, {})}, "=", 0);
    EXPECT_TRUE(solver.isOptimized());
    EXPECT_EQ(AlbaNumber(64), solver.getOptimizedObjectiveValue());
    EXPECT_EQ(solutionEquations, solver.getSolutionEquations());
}

}

}
