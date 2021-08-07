#include "SolverUsingSubstitution.hpp"

#include <Algebra/Equation/EquationUtilities.hpp>
#include <Algebra/Isolation/IsolationOfOneVariableOnEqualityEquation.hpp>
#include <Algebra/Solution/Solver/OneEquationOneVariable/OneEquationOneVariableEqualitySolver.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToTerms.hpp>

#include <algorithm>


#include <Debug/AlbaDebug.hpp>

using namespace std;

namespace alba{

namespace algebra
{
SolverUsingSubstitution::SolverUsingSubstitution()
    : BaseSolver()
{}

MultipleVariableSolutionSet SolverUsingSubstitution::calculateSolutionAndReturnSolutionSet(
        Equations const& equations)
{
    MultipleVariableSolutionSet solutionSet;
    if(doesAllEquationsHaveEqualityOperator(equations))
    {
        calculateSolutionForAllVariables(solutionSet, equations);
    }
    return solutionSet;
}

void SolverUsingSubstitution::calculateSolutionForAllVariables(
        MultipleVariableSolutionSet & multipleVariableSolutionSet,
        Equations const& equations)
{
    VariableNamesSet variablesWithUnknownValues;
    retrieveVariableNames(variablesWithUnknownValues, equations);
    VariableNamesSet previousVariableWithSolution, variableWithSolution;
    do
    {        previousVariableWithSolution=variableWithSolution;
        calculateSolutionForOneVariable(multipleVariableSolutionSet, equations);
        variableWithSolution = multipleVariableSolutionSet.getVariableNames();
    }
    while(previousVariableWithSolution.size() != variableWithSolution.size() && variablesWithUnknownValues.size() != variableWithSolution.size());
    if(variablesWithUnknownValues == variableWithSolution)
    {
        setAsCompleteSolution();
    }}

void SolverUsingSubstitution::calculateSolutionForOneVariable(
        MultipleVariableSolutionSet & multipleVariableSolutionSet,        Equations const& equations)
{
    Equations substitutedEquations(equations);
    substituteSolutionSetValuesToEquations(substitutedEquations, multipleVariableSolutionSet);
    isolateAndSubstituteUntilOneUnknown(substitutedEquations);
    solveUsingOneUnknownAndAddToSolutionSet(multipleVariableSolutionSet, substitutedEquations);
}

void SolverUsingSubstitution::substituteSolutionSetValuesToEquations(
        Equations & substitutedEquations,
        MultipleVariableSolutionSet const& multipleVariableSolutionSet)
{
    MultipleVariableSolutionSet::VariableNameToSolutionSetMap const& variableNameToSolutionSetMap(
                multipleVariableSolutionSet.getVariableNameToSolutionSetMap());
    SubstitutionOfVariablesToValues substitution;
    for(MultipleVariableSolutionSet::VariableNameToSolutionSetPair const& variableNameToSolutionSet : variableNameToSolutionSetMap)
    {
        AlbaNumbers const& acceptedValues(variableNameToSolutionSet.second.getAcceptedValues());
        if(!acceptedValues.empty())
        {
            substitution.putVariableWithValue(variableNameToSolutionSet.first, acceptedValues.front());
        }
    }
    for(Equation & substitutedEquation : substitutedEquations)
    {
        substitutedEquation = substitution.performSubstitutionTo(substitutedEquation);
    }
    removeEquationsWithoutUnknowns(substitutedEquations);
}

void SolverUsingSubstitution::isolateAndSubstituteUntilOneUnknown(
        Equations & substitutedEquations)
{
    VariableNamesSet unknowns;
    retrieveVariableNames(unknowns, substitutedEquations);
    while(unknowns.size() > 1)
    {
        bool areVariableAndEquationSelected(false);
        string selectedVariableName;
        unsigned int selectedEquationIndex(0u);
        selectVariableNameAndEquationNumber(areVariableAndEquationSelected, selectedVariableName, selectedEquationIndex, substitutedEquations);
        ALBA_PRINT4(areVariableAndEquationSelected, selectedVariableName, selectedEquationIndex, substitutedEquations.at(selectedEquationIndex));
        substituteEquationForSelectedEquationIndex(substitutedEquations, areVariableAndEquationSelected, selectedVariableName, selectedEquationIndex);
        removeEquationsWithoutUnknowns(substitutedEquations);
        unknowns.clear();        retrieveVariableNames(unknowns, substitutedEquations);
    }
}
void SolverUsingSubstitution::solveUsingOneUnknownAndAddToSolutionSet(
        MultipleVariableSolutionSet & multipleVariableSolutionSet,
        Equations const& substitutedEquations)
{
    if(substitutedEquations.size() >= 1)
    {
        Equation const& equationToSolve(substitutedEquations.front());
        VariableNamesSet variableNamesToSolve;
        retrieveVariableNames(variableNamesToSolve, equationToSolve);
        if(variableNamesToSolve.size() == 1)
        {
            string variableNameToSolve(*(variableNamesToSolve.cbegin()));
            OneEquationOneVariableEqualitySolver solver;
            SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(equationToSolve));
            ALBA_PRINT2(solutionSet, equationToSolve);
            multipleVariableSolutionSet.addSolutionSetForVariable(variableNameToSolve, solutionSet);
        }
    }}

void SolverUsingSubstitution::selectVariableNameAndEquationNumber(
        bool & areVariableAndEquationSelected,        string & selectedVariableName,
        unsigned int & selectedEquationIndex,
        Equations const& equations)
{
    areVariableAndEquationSelected = false;
    selectedVariableName.clear();
    selectedEquationIndex = 0u;
    VariableNamesSet variableNames;
    retrieveVariableNames(variableNames, equations);
    unsigned int equationIndex=0;
    for(Equation const& equation : equations)
    {
        IsolationOfOneVariableOnEqualityEquation isolation(equation);
        for(string const& variableName : variableNames)
        {
            ALBA_PRINT3(isolation.canBeIsolated(variableName), variableName, equation);
            if(isolation.canBeIsolated(variableName)
                    && isolation.getExponentOfIsolatedVariable(variableName) == 1)
            {
                areVariableAndEquationSelected = true;
                selectedVariableName = variableName;
                selectedEquationIndex = equationIndex;
                ALBA_PRINT3(areVariableAndEquationSelected, selectedVariableName, selectedEquationIndex);
                break;
            }
        }
        equationIndex++;
    }
}
void SolverUsingSubstitution::substituteEquationForSelectedEquationIndex(
        Equations & substitutedEquations,
        bool const areVariableAndEquationSelected,        string const& selectedVariableName,
        unsigned int const selectedEquationIndex)
{
    if(areVariableAndEquationSelected)
    {
        IsolationOfOneVariableOnEqualityEquation isolation(substitutedEquations.at(selectedEquationIndex));
        Equation isolatedEquation(isolation.isolate(selectedVariableName));
        ALBA_PRINT2(substitutedEquations.at(selectedEquationIndex), isolatedEquation);
        substitutedEquations.erase(substitutedEquations.begin()+selectedEquationIndex);
        SubstitutionOfVariablesToTerms substitution;
        substitution.putVariableWithTerm(selectedVariableName, isolatedEquation.getLeftHandTerm());
        for(Equation & substitutedEquation : substitutedEquations)
        {
            ALBA_PRINT2(substitutedEquation, substitution.performSubstitutionTo(substitutedEquation));
            substitutedEquation = substitution.performSubstitutionTo(substitutedEquation);
        }
    }}

void SolverUsingSubstitution::removeEquationsWithoutUnknowns(Equations& substitutedEquations)
{    substitutedEquations.erase(
                remove_if(substitutedEquations.begin(), substitutedEquations.end(), [](Equation const& equation)
    {
                    VariableNamesSet unknowns;
                    retrieveVariableNames(unknowns, equation);
                    return unknowns.empty();
                }),
            substitutedEquations.end());
}

}

}
