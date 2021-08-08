#include "SolverUsingSubstitution.hpp"

#include <Algebra/Equation/EquationUtilities.hpp>
#include <Algebra/Isolation/IsolationOfOneVariableOnEqualityEquation.hpp>
#include <Algebra/Solution/Solver/OneEquationOneVariable/OneEquationOneVariableEqualitySolver.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToTerms.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>

#include <algorithm>

using namespace std;

namespace alba
{

namespace algebra
{

SolverUsingSubstitution::SolverUsingSubstitution()
    : BaseSolver()
{}

MultipleVariableSolutionSets SolverUsingSubstitution::calculateSolutionAndReturnSolutionSet(
        Equations const& equations)
{
    clear();
    if(doesAllEquationsHaveEqualityOperator(equations))
    {
        retrieveVariableNames(m_variablesNames, equations);
        calculateSolutions(equations);
    }
    return m_solutionsWithAllVariables;
}

bool SolverUsingSubstitution::isTheValueAlreadyExisting(
        string const& variableName,
        AlbaNumber const& value) const
{
    bool result(false);
    for(MultipleVariableSolutionSet const& solutionSet : m_solutionsWithAllVariables)
    {
        result = result || solutionSet.isValueAcceptedForVariable(variableName, value);
        if(result)
        {
            break;
        }
    }
    if(!result)
    {
        for(MultipleVariableSolutionSet const& solutionSet : m_solutionsWithSomeVariables)
        {
            result = result || solutionSet.isValueAcceptedForVariable(variableName, value);
            if(result)
            {
                break;
            }
        }
    }
    return result;
}

bool SolverUsingSubstitution::isSolutionCorrectAndComplete(
        MultipleVariableSolutionSet const& solutionSet,
        Equations const& equations) const
{
    bool result(true);
    SubstitutionOfVariablesToValues substitution(getSubstitutionFromSolutionSet(solutionSet));
    for(Equation const& equation : equations)
    {
        Equation potentialSolvedEquation(substitution.performSubstitutionTo(equation));
        result = result && isAFiniteConstant(potentialSolvedEquation.getLeftHandTerm())
                && isAFiniteConstant(potentialSolvedEquation.getRightHandTerm())
                && potentialSolvedEquation.isEquationSatisfied();
        if(!result)
        {
            break;
        }
    }
    return result;
}

SubstitutionOfVariablesToValues SolverUsingSubstitution::getSubstitutionFromSolutionSet(
        MultipleVariableSolutionSet const& solutionSet) const
{
    MultipleVariableSolutionSet::VariableNameToSolutionSetMap const& variableNameToSolutionSetMap(
                solutionSet.getVariableNameToSolutionSetMap());
    SubstitutionOfVariablesToValues substitution;
    for(MultipleVariableSolutionSet::VariableNameToSolutionSetPair const& variableNameToSolutionSet : variableNameToSolutionSetMap)
    {
        AlbaNumbers const& acceptedValues(variableNameToSolutionSet.second.getAcceptedValues());
        if(!acceptedValues.empty())
        {
            substitution.putVariableWithValue(variableNameToSolutionSet.first, acceptedValues.front());
        }
    }
    return substitution;
}

void SolverUsingSubstitution::clear()
{
    m_solutionsWithAllVariables.clear();
    m_solutionsWithSomeVariables.clear();
    m_variablesNames.clear();
}

void SolverUsingSubstitution::calculateSolutions(
        Equations const& equations)
{
    do
    {
        MultipleVariableSolutionSet solutionSet;
        if(!m_solutionsWithSomeVariables.empty())
        {
            solutionSet = m_solutionsWithSomeVariables.back();
            m_solutionsWithSomeVariables.pop_back();
        }
        calculateASolutionForAllVariables(solutionSet, equations);
        addIfSolutionIsCompleteAndCorrect(solutionSet, equations);
    }
    while(!m_solutionsWithSomeVariables.empty());
}

void SolverUsingSubstitution::calculateASolutionForAllVariables(
        MultipleVariableSolutionSet & solutionSet,
        Equations const& equations)
{
    VariableNamesSet previousVariablesWithSolution, variablesWithSolution;
    do
    {
        previousVariablesWithSolution=variablesWithSolution;
        calculateASolutionForOneVariable(solutionSet, equations);
        variablesWithSolution = solutionSet.getVariableNames();
    }
    while(previousVariablesWithSolution.size() != variablesWithSolution.size()
          && m_variablesNames.size() != variablesWithSolution.size());
}

void SolverUsingSubstitution::addIfSolutionIsCompleteAndCorrect(
        MultipleVariableSolutionSet const& solutionSet,
        Equations const& equations)
{
    if(m_variablesNames == solutionSet.getVariableNames())
    {
        if(isSolutionCorrectAndComplete(solutionSet, equations))
        {
            m_solutionsWithAllVariables.emplace_back(solutionSet);
            setAsCompleteSolution();
        }
    }
}

void SolverUsingSubstitution::calculateASolutionForOneVariable(
        MultipleVariableSolutionSet & solutionSet,
        Equations const& equations)
{
    Equations substitutedEquations(equations);
    substituteSolutionSetValuesToEquations(substitutedEquations, solutionSet);
    isolateAndSubstituteUntilOneUnknown(substitutedEquations);
    solveForTheFirstOneVariableEquationAndUpdate(solutionSet, substitutedEquations);
}

void SolverUsingSubstitution::substituteSolutionSetValuesToEquations(
        Equations & substitutedEquations,
        MultipleVariableSolutionSet const& solutionSet)
{
    SubstitutionOfVariablesToValues substitution(getSubstitutionFromSolutionSet(solutionSet));
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
        substituteEquationForSelectedEquationIndex(substitutedEquations, areVariableAndEquationSelected, selectedVariableName, selectedEquationIndex);
        removeEquationsWithoutUnknowns(substitutedEquations);
        unknowns.clear();
        retrieveVariableNames(unknowns, substitutedEquations);
    }
}

void SolverUsingSubstitution::solveForTheFirstOneVariableEquationAndUpdate(
        MultipleVariableSolutionSet & solutionSet,
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
            solveAndUpdate(solutionSet, equationToSolve, variableNameToSolve);
        }
    }
}

void SolverUsingSubstitution::solveAndUpdate(
        MultipleVariableSolutionSet& solutionSet,
        Equation const& equationToSolve,
        string const& variableNameToSolve)
{
    OneEquationOneVariableEqualitySolver solver;
    SolutionSet solutionSetForOneVariable(solver.calculateSolutionAndReturnSolutionSet(equationToSolve));
    bool isFirst(true);
    AlbaNumbers const& acceptedValues(solutionSetForOneVariable.getAcceptedValues());
    for(AlbaNumber const& acceptedValue : acceptedValues)
    {
        if(isFirst)
        {
            SolutionSet solutionToAdd;
            solutionToAdd.addAcceptedValue(acceptedValue);
            solutionSet.addSolutionSetForVariable(variableNameToSolve, solutionToAdd);
            isFirst = false;
        }
        else
        {
            SolutionSet potentialSolution;
            potentialSolution.addAcceptedValue(acceptedValue);
            MultipleVariableSolutionSet multipleVariableSolutionSet;
            multipleVariableSolutionSet.addSolutionSetForVariable(variableNameToSolve, potentialSolution);
            m_solutionsWithSomeVariables.emplace_back(multipleVariableSolutionSet);
        }
    }
}

void SolverUsingSubstitution::selectVariableNameAndEquationNumber(
        bool & areVariableAndEquationSelected,
        string & selectedVariableName,
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
            if(isolation.canBeIsolated(variableName)
                    && isolation.getExponentOfIsolatedVariable(variableName) == 1)
            {
                areVariableAndEquationSelected = true;
                selectedVariableName = variableName;
                selectedEquationIndex = equationIndex;
                break;
            }
        }
        equationIndex++;
    }
}

void SolverUsingSubstitution::substituteEquationForSelectedEquationIndex(
        Equations & substitutedEquations,
        bool const areVariableAndEquationSelected,
        string const& selectedVariableName,
        unsigned int const selectedEquationIndex)
{
    if(areVariableAndEquationSelected)
    {
        IsolationOfOneVariableOnEqualityEquation isolation(substitutedEquations.at(selectedEquationIndex));
        Equation isolatedEquation(isolation.isolate(selectedVariableName));
        substitutedEquations.erase(substitutedEquations.begin()+selectedEquationIndex);
        SubstitutionOfVariablesToTerms substitution;
        substitution.putVariableWithTerm(selectedVariableName, isolatedEquation.getLeftHandTerm());
        for(Equation & substitutedEquation : substitutedEquations)
        {
            substitutedEquation = substitution.performSubstitutionTo(substitutedEquation);
        }
    }
}

void SolverUsingSubstitution::removeEquationsWithoutUnknowns(Equations& substitutedEquations)
{
    substitutedEquations.erase(
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
