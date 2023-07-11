#include "SolverUsingSubstitution.hpp"

#include <Algebra/Equation/EquationUtilities.hpp>
#include <Algebra/Retrieval/SingleVariableNameRetriever.hpp>
#include <Algebra/Retrieval/VariableNamesRetriever.hpp>
#include <Algebra/Solution/Solver/OneEquationOneVariable/OneEquationOneVariableEqualitySolver.hpp>
#include <Algebra/Solution/Solver/SolverUsingSubstitution/ReduceEquationsBySubstitution.hpp>#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>

using namespace std;
namespace alba {

namespace algebra {

SolverUsingSubstitution::SolverUsingSubstitution() : BaseSolver() {}

MultipleVariableSolutionSets SolverUsingSubstitution::calculateSolutionAndReturnSolutionSet(
    Equations const& equations) {
    clear();
    if (doesAllEquationsHaveEqualityOperator(equations)) {
        VariableNamesRetriever variableNamesRetriever;
        variableNamesRetriever.retrieveFromEquations(equations);
        m_variablesNames = variableNamesRetriever.getVariableNames();
        calculateSolutions(equations);
    }
    return m_solutionsWithAllVariables;}

bool SolverUsingSubstitution::isTheValueAlreadyExisting(string const& variableName, AlbaNumber const& value) const {
    bool result(false);    for (MultipleVariableSolutionSet const& solutionSet : m_solutionsWithAllVariables) {
        result = result || solutionSet.isValueAcceptedForVariable(variableName, value);
        if (result) {
            break;
        }
    }
    if (!result) {
        for (MultipleVariableSolutionSet const& solutionSet : m_solutionsWithSomeVariables) {
            result = result || solutionSet.isValueAcceptedForVariable(variableName, value);
            if (result) {
                break;
            }
        }
    }
    return result;
}

bool SolverUsingSubstitution::isSolutionCorrect(
    MultipleVariableSolutionSet const& solutionSet, Equations const& equations) const {
    bool result(true);
    SubstitutionOfVariablesToValues substitution(getSubstitutionFromSolutionSet(solutionSet));
    for (Equation const& equation : equations) {
        Equation potentialSolvedEquation(substitution.performSubstitutionTo(equation));
        result = result && isARealFiniteConstant(potentialSolvedEquation.getLeftHandTerm()) &&
                 isARealFiniteConstant(potentialSolvedEquation.getRightHandTerm()) &&
                 potentialSolvedEquation.isEquationSatisfied();
        if (!result) {
            break;
        }
    }
    return result;
}

SubstitutionOfVariablesToValues SolverUsingSubstitution::getSubstitutionFromSolutionSet(
    MultipleVariableSolutionSet const& solutionSet) const {
    MultipleVariableSolutionSet::VariableNameToSolutionSetMap const& variableNameToSolutionSetMap(
        solutionSet.getVariableNameToSolutionSetMap());
    SubstitutionOfVariablesToValues substitution;
    for (auto const& variableNameToSolutionSet : variableNameToSolutionSetMap) {
        AlbaNumbers const& acceptedValues(variableNameToSolutionSet.second.getAcceptedValues());
        if (!acceptedValues.empty()) {
            substitution.putVariableWithValue(variableNameToSolutionSet.first, acceptedValues.front());
        }
    }
    return substitution;
}

void SolverUsingSubstitution::clear() {
    m_solutionsWithAllVariables.clear();
    m_solutionsWithSomeVariables.clear();
    m_variablesNames.clear();
}

void SolverUsingSubstitution::calculateSolutions(Equations const& equations) {
    do {
        MultipleVariableSolutionSet solutionSet;
        if (!m_solutionsWithSomeVariables.empty()) {
            solutionSet = m_solutionsWithSomeVariables.back();
            m_solutionsWithSomeVariables.pop_back();
        }
        calculateASolutionForAllVariables(solutionSet, equations);
        addIfSolutionIsCompleteAndCorrect(solutionSet, equations);
    } while (!m_solutionsWithSomeVariables.empty());
}

void SolverUsingSubstitution::calculateASolutionForAllVariables(
    MultipleVariableSolutionSet& solutionSet, Equations const& equations) {
    int previousNumberOfVariables(0);
    VariableNamesSet variablesWithSolution;
    do {
        previousNumberOfVariables = variablesWithSolution.size();
        calculateASolutionForOneVariable(solutionSet, equations);
        variablesWithSolution = solutionSet.getVariableNames();
    } while (previousNumberOfVariables != static_cast<int>(variablesWithSolution.size()) &&
             m_variablesNames.size() != variablesWithSolution.size());
}

void SolverUsingSubstitution::addIfSolutionIsCompleteAndCorrect(
    MultipleVariableSolutionSet const& solutionSet, Equations const& equations) {
    if (m_variablesNames == solutionSet.getVariableNames()) {
        if (isSolutionCorrect(solutionSet, equations)) {
            m_solutionsWithAllVariables.emplace_back(solutionSet);
            setAsCompleteSolution();
        }
    }
}

void SolverUsingSubstitution::calculateASolutionForOneVariable(
    MultipleVariableSolutionSet& solutionSet, Equations const& equations) {
    Equations substitutedEquations(equations);
    substituteSolutionSetValuesToEquations(substitutedEquations, solutionSet);
    reduceEquationsBySubstitution(substitutedEquations, {});
    solveForTheFirstOneVariableEquationAndUpdate(solutionSet, substitutedEquations);
}

void SolverUsingSubstitution::substituteSolutionSetValuesToEquations(
    Equations& substitutedEquations, MultipleVariableSolutionSet const& solutionSet) {
    SubstitutionOfVariablesToValues substitution(getSubstitutionFromSolutionSet(solutionSet));
    for (Equation& substitutedEquation : substitutedEquations) {
        substitutedEquation = substitution.performSubstitutionTo(substitutedEquation);
    }
    removeEquationsWithoutUnknowns(substitutedEquations);
}

void SolverUsingSubstitution::solveForTheFirstOneVariableEquationAndUpdate(
    MultipleVariableSolutionSet& solutionSet, Equations const& substitutedEquations) {
    if (!substitutedEquations.empty()) {
        Equation const& equationToSolve(substitutedEquations.front());
        string singleVariableName = getSingleVariableNameIfItExistsAsTheOnlyOneOtherwiseItsEmpty(equationToSolve);
        if (!singleVariableName.empty()) {
            solveAndUpdate(solutionSet, equationToSolve, singleVariableName);
        }
    }
}
void SolverUsingSubstitution::solveAndUpdate(
    MultipleVariableSolutionSet& solutionSet, Equation const& equationToSolve, string const& variableNameToSolve) {
    OneEquationOneVariableEqualitySolver solver;    SolutionSet solutionSetForOneVariable(solver.calculateSolutionAndReturnSolutionSet(equationToSolve));
    AlbaNumbers const& acceptedValues(solutionSetForOneVariable.getAcceptedValues());
    if (!acceptedValues.empty()) {
        SolutionSet firstPotentialSolution;
        firstPotentialSolution.addAcceptedValue(acceptedValues.front());
        solutionSet.addSolutionSetForVariable(variableNameToSolve, firstPotentialSolution);
        for (auto it = acceptedValues.cbegin() + 1; it != acceptedValues.cend(); it++) {
            SolutionSet potentialSolution;
            potentialSolution.addAcceptedValue(*it);
            MultipleVariableSolutionSet multipleVariableSolutionSet;
            multipleVariableSolutionSet.addSolutionSetForVariable(variableNameToSolve, potentialSolution);
            m_solutionsWithSomeVariables.emplace_back(multipleVariableSolutionSet);
        }
    }
}

}  // namespace algebra

}  // namespace alba
