#include "ReduceEquationsBySubstitution.hpp"

#include <Algebra/Isolation/IsolationOfOneVariableOnEqualityEquation.hpp>
#include <Algebra/Retrieval/VariableNamesRetriever.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToTerms.hpp>

#include <algorithm>

using namespace std;

namespace alba
{

namespace algebra
{

void reduceEquationsBySubstitution(
        Equations & substitutedEquations,
        VariableNamesSet const& variableNamesToIgnore)
{
    VariableNamesRetriever unknownsRetriever;
    unknownsRetriever.retrieveFromEquations(substitutedEquations);
    bool areVariableAndEquationSelected(true);
    while(areVariableAndEquationSelected && unknownsRetriever.getSavedData().size() > 1)
    {
        areVariableAndEquationSelected = false;
        string selectedVariableName;
        unsigned int selectedEquationIndex(0U);
        selectVariableNameAndEquationNumber(areVariableAndEquationSelected, selectedVariableName, selectedEquationIndex, substitutedEquations, variableNamesToIgnore);
        substituteEquationForSelectedEquationIndex(substitutedEquations, areVariableAndEquationSelected, selectedVariableName, selectedEquationIndex);
        removeEquationsWithoutUnknowns(substitutedEquations);
        unknownsRetriever.getSavedDataReference().clear();
        unknownsRetriever.retrieveFromEquations(substitutedEquations);
    }
}

void selectVariableNameAndEquationNumber(
        bool & areVariableAndEquationSelected,
        string & selectedVariableName,
        unsigned int & selectedEquationIndex,
        Equations const& equations,
        VariableNamesSet const& variableNamesToIgnore)
{
    areVariableAndEquationSelected = false;
    selectedVariableName.clear();
    selectedEquationIndex = 0U;
    VariableNamesSet variableNamesToCheck(getVariablesNamesToCheck(equations, variableNamesToIgnore));
    unsigned int equationIndex=0;
    for(Equation const& equation : equations)
    {
        IsolationOfOneVariableOnEqualityEquation isolation(equation);
        for(string const& variableName : variableNamesToCheck)
        {
            if(isolation.canBeIsolated(variableName)
                    && isolation.getIdenticalExponentForVariableIfPossible(variableName) == 1)
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

void substituteEquationForSelectedEquationIndex(
        Equations & substitutedEquations,
        bool const areVariableAndEquationSelected,
        string const& selectedVariableName,
        unsigned int const selectedEquationIndex)
{
    if(areVariableAndEquationSelected)
    {
        IsolationOfOneVariableOnEqualityEquation isolation(substitutedEquations.at(selectedEquationIndex));
        substitutedEquations.erase(substitutedEquations.begin() + selectedEquationIndex);
        SubstitutionOfVariablesToTerms substitution;
        substitution.putVariableWithTerm(selectedVariableName, isolation.getEquivalentTermByIsolatingAVariable(selectedVariableName));
        for(Equation & substitutedEquation : substitutedEquations)
        {
            substitutedEquation = substitution.performSubstitutionTo(substitutedEquation);
        }
    }
}

void removeEquationsWithoutUnknowns(Equations& substitutedEquations)
{
    substitutedEquations.erase(
                remove_if(substitutedEquations.begin(), substitutedEquations.end(), [](Equation const& equation)
    {

                    VariableNamesRetriever unknownsRetriever;
                    unknownsRetriever.retrieveFromEquation(equation);
                    return unknownsRetriever.getSavedData().empty();
                }),
            substitutedEquations.end());
}

VariableNamesSet getVariablesNamesToCheck(
        Equations const& equations,
        VariableNamesSet const& variableNamesToIgnore)
{
    VariableNamesRetriever variableNamesRetriever;
    variableNamesRetriever.retrieveFromEquations(equations);
    VariableNamesSet variableNamesToCheck(variableNamesRetriever.getSavedData());
    for(string const& variableNameToIgnore : variableNamesToIgnore)
    {
        variableNamesToCheck.erase(variableNameToIgnore);
    }
    return variableNamesToCheck;
}

}

}
