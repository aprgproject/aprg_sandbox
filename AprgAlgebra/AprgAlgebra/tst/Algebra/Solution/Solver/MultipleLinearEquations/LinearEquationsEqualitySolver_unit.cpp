#include <Algebra/Solution/Solver/MultipleLinearEquations/LinearEquationsEqualitySolver.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(LinearEquationsEqualitySolverTest, ConstructionWorks)
{
    LinearEquationsEqualitySolver();
}

TEST(LinearEquationsEqualitySolverTest, CalculateSolutionAndReturnSolutionSetWorksAsDoesNotFindASolutionForNonEqualityEquation)
{
    LinearEquationsEqualitySolver solver;
    Equations equations;
    Polynomial polynomial{Monomial(1, {{"x", 1}})};
    equations.emplace_back(Term(polynomial), ">", Term(4));

    MultipleVariableSolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(equations));

    EXPECT_FALSE(solver.isSolved());
    EXPECT_FALSE(solver.isACompleteSolution());
    EXPECT_EQ(0u, solutionSet.getNumberOfVariablesWithSolutions());
}

TEST(LinearEquationsEqualitySolverTest, CalculateSolutionAndReturnSolutionSetWorksFor1Equation){
    LinearEquationsEqualitySolver solver;
    Equations equations;
    Polynomial polynomial{Monomial(1, {{"x", 1}})};
    equations.emplace_back(Term(polynomial), "=", Term(4));

    MultipleVariableSolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(equations));

    EXPECT_TRUE(solver.isSolved());
    EXPECT_TRUE(solver.isACompleteSolution());
    EXPECT_EQ(1u, solutionSet.getNumberOfVariablesWithSolutions());
    AlbaNumbers acceptedValuesForX(solutionSet.getSolutionSetForVariable("x").getAcceptedValues());
    ASSERT_EQ(1u, acceptedValuesForX.size());
    EXPECT_EQ(AlbaNumber(4), acceptedValuesForX.at(0));
}
TEST(LinearEquationsEqualitySolverTest, CalculateSolutionAndReturnSolutionSetWorksFor2Equations)
{
    LinearEquationsEqualitySolver solver;    Equations equations;
    Polynomial polynomial1{Monomial(1, {{"x", 1}}), Monomial(2, {{"y", 1}})};
    Polynomial polynomial2{Monomial(3, {{"x", 1}}), Monomial(-2, {{"y", 1}})};
    equations.emplace_back(Term(polynomial1), "=", Term(4));
    equations.emplace_back(Term(polynomial2), "=", Term(-12));

    MultipleVariableSolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(equations));

    EXPECT_TRUE(solver.isSolved());
    EXPECT_TRUE(solver.isACompleteSolution());
    EXPECT_EQ(2u, solutionSet.getNumberOfVariablesWithSolutions());
    AlbaNumbers acceptedValuesForX(solutionSet.getSolutionSetForVariable("x").getAcceptedValues());
    ASSERT_EQ(1u, acceptedValuesForX.size());
    EXPECT_EQ(AlbaNumber(-2), acceptedValuesForX.at(0));
    AlbaNumbers acceptedValuesForY(solutionSet.getSolutionSetForVariable("y").getAcceptedValues());
    ASSERT_EQ(1u, acceptedValuesForY.size());
    EXPECT_EQ(AlbaNumber(3), acceptedValuesForY.at(0));
}
TEST(LinearEquationsEqualitySolverTest, CalculateSolutionAndReturnSolutionSetWorksFor3Equations)
{
    LinearEquationsEqualitySolver solver;    Equations equations;
    Polynomial polynomial1{Monomial(2, {{"x", 1}}), Monomial(-1, {{"y", 1}}), Monomial(1, {{"z", 1}})};
    Polynomial polynomial2{Monomial(1, {{"x", 1}}), Monomial(2, {{"y", 1}}), Monomial(3, {{"z", 1}})};
    Polynomial polynomial3{Monomial(4, {{"x", 1}}), Monomial(1, {{"y", 1}}), Monomial(-2, {{"z", 1}})};
    equations.emplace_back(Term(polynomial1), "=", Term(8));
    equations.emplace_back(Term(polynomial2), "=", Term(9));
    equations.emplace_back(Term(polynomial3), "=", Term(1));

    MultipleVariableSolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(equations));

    EXPECT_TRUE(solver.isSolved());
    EXPECT_TRUE(solver.isACompleteSolution());
    EXPECT_EQ(3u, solutionSet.getNumberOfVariablesWithSolutions());
    AlbaNumbers acceptedValuesForX(solutionSet.getSolutionSetForVariable("x").getAcceptedValues());
    ASSERT_EQ(1u, acceptedValuesForX.size());
    EXPECT_EQ(AlbaNumber(2), acceptedValuesForX.at(0));
    AlbaNumbers acceptedValuesForY(solutionSet.getSolutionSetForVariable("y").getAcceptedValues());
    ASSERT_EQ(1u, acceptedValuesForY.size());
    EXPECT_EQ(AlbaNumber(-1), acceptedValuesForY.at(0));
    AlbaNumbers acceptedValuesForZ(solutionSet.getSolutionSetForVariable("z").getAcceptedValues());
    ASSERT_EQ(1u, acceptedValuesForZ.size());
    EXPECT_EQ(AlbaNumber(3), acceptedValuesForZ.at(0));
}
TEST(LinearEquationsEqualitySolverTest, CalculateSolutionAndReturnSolutionSetWorksAsDoesNotFindASolutionForNonLinearEquation)
{
    LinearEquationsEqualitySolver solver;
    Polynomials polynomials;
    polynomials.emplace_back(Polynomial{Monomial(1, {{"x", 3}}), Monomial(-4, {})});

    MultipleVariableSolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(polynomials));

    EXPECT_FALSE(solver.isSolved());
    EXPECT_FALSE(solver.isACompleteSolution());
    EXPECT_EQ(0u, solutionSet.getNumberOfVariablesWithSolutions());
}

TEST(LinearEquationsEqualitySolverTest, CalculateSolutionAndReturnSolutionSetWorksAsDoesNotFindASolutionWhenEquationNumberDoesNotMatchVariableNumber){
    LinearEquationsEqualitySolver solver;
    Polynomials polynomials;
    polynomials.emplace_back(Polynomial{Monomial(1, {{"x", 1}}), Monomial(2, {{"y", 1}}), Monomial(-4, {})});

    MultipleVariableSolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(polynomials));

    EXPECT_FALSE(solver.isSolved());
    EXPECT_FALSE(solver.isACompleteSolution());
    EXPECT_EQ(0u, solutionSet.getNumberOfVariablesWithSolutions());
}

TEST(LinearEquationsEqualitySolverTest, CalculateSolutionAndReturnSolutionSetWorksFor1Polynomial){
    LinearEquationsEqualitySolver solver;
    Polynomials polynomials;
    polynomials.emplace_back(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-4, {})});

    MultipleVariableSolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(polynomials));

    EXPECT_TRUE(solver.isSolved());
    EXPECT_TRUE(solver.isACompleteSolution());
    EXPECT_EQ(1u, solutionSet.getNumberOfVariablesWithSolutions());
    AlbaNumbers acceptedValuesForX(solutionSet.getSolutionSetForVariable("x").getAcceptedValues());
    ASSERT_EQ(1u, acceptedValuesForX.size());
    EXPECT_EQ(AlbaNumber(4), acceptedValuesForX.at(0));
}
TEST(LinearEquationsEqualitySolverTest, CalculateSolutionAndReturnSolutionSetWorksFor2Polynomials)
{
    LinearEquationsEqualitySolver solver;    Polynomials polynomials;
    polynomials.emplace_back(Polynomial{Monomial(1, {{"x", 1}}), Monomial(2, {{"y", 1}}), Monomial(-4, {})});
    polynomials.emplace_back(Polynomial{Monomial(3, {{"x", 1}}), Monomial(-2, {{"y", 1}}), Monomial(12, {})});

    MultipleVariableSolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(polynomials));

    EXPECT_TRUE(solver.isSolved());
    EXPECT_TRUE(solver.isACompleteSolution());
    EXPECT_EQ(2u, solutionSet.getNumberOfVariablesWithSolutions());
    AlbaNumbers acceptedValuesForX(solutionSet.getSolutionSetForVariable("x").getAcceptedValues());
    ASSERT_EQ(1u, acceptedValuesForX.size());
    EXPECT_EQ(AlbaNumber(-2), acceptedValuesForX.at(0));
    AlbaNumbers acceptedValuesForY(solutionSet.getSolutionSetForVariable("y").getAcceptedValues());
    ASSERT_EQ(1u, acceptedValuesForY.size());
    EXPECT_EQ(AlbaNumber(3), acceptedValuesForY.at(0));
}
TEST(LinearEquationsEqualitySolverTest, CalculateSolutionAndReturnSolutionSetWorksFor3Polynomials)
{
    LinearEquationsEqualitySolver solver;    Polynomials polynomials;
    polynomials.emplace_back(Polynomial{Monomial(2, {{"x", 1}}), Monomial(-1, {{"y", 1}}), Monomial(1, {{"z", 1}}), Monomial(-8, {})});
    polynomials.emplace_back(Polynomial{Monomial(1, {{"x", 1}}), Monomial(2, {{"y", 1}}), Monomial(3, {{"z", 1}}), Monomial(-9, {})});
    polynomials.emplace_back(Polynomial{Monomial(4, {{"x", 1}}), Monomial(1, {{"y", 1}}), Monomial(-2, {{"z", 1}}), Monomial(-1, {})});

    MultipleVariableSolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(polynomials));

    EXPECT_TRUE(solver.isSolved());
    EXPECT_TRUE(solver.isACompleteSolution());
    EXPECT_EQ(3u, solutionSet.getNumberOfVariablesWithSolutions());
    AlbaNumbers acceptedValuesForX(solutionSet.getSolutionSetForVariable("x").getAcceptedValues());
    ASSERT_EQ(1u, acceptedValuesForX.size());
    EXPECT_EQ(AlbaNumber(2), acceptedValuesForX.at(0));
    AlbaNumbers acceptedValuesForY(solutionSet.getSolutionSetForVariable("y").getAcceptedValues());
    ASSERT_EQ(1u, acceptedValuesForY.size());
    EXPECT_EQ(AlbaNumber(-1), acceptedValuesForY.at(0));
    AlbaNumbers acceptedValuesForZ(solutionSet.getSolutionSetForVariable("z").getAcceptedValues());
    ASSERT_EQ(1u, acceptedValuesForZ.size());
    EXPECT_EQ(AlbaNumber(3), acceptedValuesForZ.at(0));
}
}

}