#pragma once

#include <Algebra/Equation/Equation.hpp>
#include <Algebra/Solution/SolutionSet/MultipleVariableSolutionSet.hpp>
#include <Algebra/Solution/Solver/BaseSolver.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>

namespace alba
{

namespace algebra
{

class SolverUsingSubstitution : public BaseSolver
{
public:
    SolverUsingSubstitution();

    MultipleVariableSolutionSets calculateSolutionAndReturnSolutionSet(Equations const& equations);

private:
    bool isTheValueAlreadyExisting(
            std::string const& variableName,
            AlbaNumber const& value) const;
    bool isSolutionCorrectAndComplete(
            MultipleVariableSolutionSet const& solutionSet,
            Equations const& equations) const;
    SubstitutionOfVariablesToValues getSubstitutionFromSolutionSet(
            MultipleVariableSolutionSet const& solutionSet) const;

    void clear();
    void calculateSolutions(
            Equations const& equations);
    void calculateASolutionForAllVariables(
            MultipleVariableSolutionSet & multipleVariableSolutionSet,
            Equations const& equations);
    void addIfSolutionIsCompleteAndCorrect(
            MultipleVariableSolutionSet const& solutionSet,
            Equations const& equations);
    void calculateASolutionForOneVariable(
            MultipleVariableSolutionSet & multipleVariableSolutionSet,
            Equations const& equations);
    void substituteSolutionSetValuesToEquations(
            Equations & substitutedEquations,
            MultipleVariableSolutionSet const& multipleVariableSolutionSet);
    void isolateAndSubstituteUntilOneUnknown(Equations & substitutedEquations);
    void solveForTheFirstOneVariableEquationAndUpdate(
            MultipleVariableSolutionSet & multipleVariableSolutionSet,
            Equations const& substitutedEquations);
    void solveAndUpdate(
            MultipleVariableSolutionSet & solutionSet,
            Equation const& equationToSolve,
            std::string const& variableNameToSolve);
    void selectVariableNameAndEquationNumber(
            bool & isFound,
            std::string & selectedVariableName,
            unsigned int & selectedEquationIndex,
            Equations const& equations);
    void substituteEquationForSelectedEquationIndex(
            Equations & substitutedEquations,
            bool const areVariableAndEquationSelected,
            std::string const& selectedVariableName,
            unsigned int const selectedEquationIndex);
    void removeEquationsWithoutUnknowns(Equations& substitutedEquations);

    MultipleVariableSolutionSets m_solutionsWithAllVariables;
    MultipleVariableSolutionSets m_solutionsWithSomeVariables;
    VariableNamesSet m_variablesNames;
};


}

}
