#include <Algebra/Solution/Solver/SolverUsingSubstitution/SolverUsingSubstitution.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algebra
{

TEST(SolverUsingSubstitutionTest, ConstructionWorks)
{
    SolverUsingSubstitution();
}

TEST(SolverUsingSubstitutionTest, CalculateSolutionAndReturnSolutionSetWorksAsDoesNotFindASolutionForNonEqualityEquation)
{
    SolverUsingSubstitution solver;
    Equations equations;
    Polynomial polynomial{Monomial(1, {{"x", 1}})};
    equations.emplace_back(Term(polynomial), ">", Term(4));

    MultipleVariableSolutionSets solutionSets(solver.calculateSolutionAndReturnSolutionSet(equations));

    EXPECT_FALSE(solver.isSolved());
    EXPECT_FALSE(solver.isACompleteSolution());
    EXPECT_TRUE(solutionSets.empty());
}

TEST(SolverUsingSubstitutionTest, CalculateSolutionAndReturnSolutionSetWorksFor1Equation)
{
    SolverUsingSubstitution solver;
    Equations equations;
    Polynomial polynomial{Monomial(1, {{"x", 1}})};
    equations.emplace_back(Term(polynomial), "=", Term(4));

    MultipleVariableSolutionSets solutionSets(solver.calculateSolutionAndReturnSolutionSet(equations));

    EXPECT_TRUE(solver.isSolved());
    EXPECT_TRUE(solver.isACompleteSolution());
    ASSERT_EQ(1u, solutionSets.size());
    MultipleVariableSolutionSet const& solutionSet(solutionSets.back());
    EXPECT_EQ(1u, solutionSet.getNumberOfVariablesWithSolutions());
    AlbaNumbers acceptedValuesForX(solutionSet.getSolutionSetForVariable("x").getAcceptedValues());
    ASSERT_EQ(1u, acceptedValuesForX.size());
    EXPECT_EQ(AlbaNumber(4), acceptedValuesForX.at(0));
}

TEST(SolverUsingSubstitutionTest, CalculateSolutionAndReturnSolutionSetWorksFor2Equations)
{
    SolverUsingSubstitution solver;
    Equations equations;
    Polynomial polynomial1{Monomial(1, {{"x", 1}}), Monomial(2, {{"y", 1}})};
    Polynomial polynomial2{Monomial(3, {{"x", 1}}), Monomial(-2, {{"y", 1}})};
    equations.emplace_back(Term(polynomial1), "=", Term(4));
    equations.emplace_back(Term(polynomial2), "=", Term(-12));

    MultipleVariableSolutionSets solutionSets(solver.calculateSolutionAndReturnSolutionSet(equations));

    EXPECT_TRUE(solver.isSolved());
    EXPECT_TRUE(solver.isACompleteSolution());
    ASSERT_EQ(1u, solutionSets.size());
    MultipleVariableSolutionSet const& solutionSet(solutionSets.back());
    EXPECT_EQ(2u, solutionSet.getNumberOfVariablesWithSolutions());
    AlbaNumbers acceptedValuesForX(solutionSet.getSolutionSetForVariable("x").getAcceptedValues());
    ASSERT_EQ(1u, acceptedValuesForX.size());
    EXPECT_EQ(AlbaNumber(-2), acceptedValuesForX.at(0));
    AlbaNumbers acceptedValuesForY(solutionSet.getSolutionSetForVariable("y").getAcceptedValues());
    ASSERT_EQ(1u, acceptedValuesForY.size());
    EXPECT_EQ(AlbaNumber(3), acceptedValuesForY.at(0));
}

TEST(SolverUsingSubstitutionTest, CalculateSolutionAndReturnSolutionSetWorksFor3Equations)
{
    SolverUsingSubstitution solver;
    Equations equations;
    Polynomial polynomial1{Monomial(2, {{"x", 1}}), Monomial(-1, {{"y", 1}}), Monomial(1, {{"z", 1}})};
    Polynomial polynomial2{Monomial(1, {{"x", 1}}), Monomial(2, {{"y", 1}}), Monomial(3, {{"z", 1}})};
    Polynomial polynomial3{Monomial(4, {{"x", 1}}), Monomial(1, {{"y", 1}}), Monomial(-2, {{"z", 1}})};
    equations.emplace_back(Term(polynomial1), "=", Term(8));
    equations.emplace_back(Term(polynomial2), "=", Term(9));
    equations.emplace_back(Term(polynomial3), "=", Term(1));

    MultipleVariableSolutionSets solutionSets(solver.calculateSolutionAndReturnSolutionSet(equations));

    EXPECT_TRUE(solver.isSolved());
    EXPECT_TRUE(solver.isACompleteSolution());
    ASSERT_EQ(1u, solutionSets.size());
    MultipleVariableSolutionSet const& solutionSet(solutionSets.back());
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

TEST(SolverUsingSubstitutionTest, CalculateSolutionAndReturnSolutionSetWorksForLinearAndQuadratic)
{
    SolverUsingSubstitution solver;
    Equations equations;
    Polynomial polynomial1{Monomial(1, {{"x", 2}}), Monomial(-5, {{"x", 1}}), Monomial(-1, {{"y", 1}}), Monomial(4, {})};
    Polynomial polynomial2{Monomial(1, {{"x", 1}}), Monomial(-4, {{"y", 1}})};
    equations.emplace_back(Term(polynomial1), "=", Term(Constant(0)));
    equations.emplace_back(Term(polynomial2), "=", Term(1));

    MultipleVariableSolutionSets solutionSets(solver.calculateSolutionAndReturnSolutionSet(equations));

    EXPECT_TRUE(solver.isSolved());
    EXPECT_TRUE(solver.isACompleteSolution());
    ASSERT_EQ(2u, solutionSets.size());
    MultipleVariableSolutionSet const& solutionSet1(solutionSets.at(0));
    EXPECT_EQ(2u, solutionSet1.getNumberOfVariablesWithSolutions());
    AlbaNumbers acceptedValuesForX1(solutionSet1.getSolutionSetForVariable("x").getAcceptedValues());
    ASSERT_EQ(1u, acceptedValuesForX1.size());
    EXPECT_EQ(AlbaNumber(1), acceptedValuesForX1.at(0));
    AlbaNumbers acceptedValuesForY1(solutionSet1.getSolutionSetForVariable("y").getAcceptedValues());
    ASSERT_EQ(1u, acceptedValuesForY1.size());
    EXPECT_EQ(AlbaNumber(0), acceptedValuesForY1.at(0));
    MultipleVariableSolutionSet const& solutionSet2(solutionSets.at(1));
    EXPECT_EQ(2u, solutionSet2.getNumberOfVariablesWithSolutions());
    AlbaNumbers acceptedValuesForX2(solutionSet2.getSolutionSetForVariable("x").getAcceptedValues());
    ASSERT_EQ(1u, acceptedValuesForX2.size());
    EXPECT_EQ(AlbaNumber(17)/4, acceptedValuesForX2.at(0));
    AlbaNumbers acceptedValuesForY2(solutionSet2.getSolutionSetForVariable("y").getAcceptedValues());
    ASSERT_EQ(1u, acceptedValuesForY2.size());
    EXPECT_EQ(AlbaNumber(13)/16, acceptedValuesForY2.at(0));
}

}

}
