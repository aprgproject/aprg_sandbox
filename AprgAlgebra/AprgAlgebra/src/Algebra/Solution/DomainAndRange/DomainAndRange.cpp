#include "DomainAndRange.hpp"

#include <Algebra/Equation/EquationUtilities.hpp>
#include <Algebra/Solution/SolutionUtilities.hpp>
#include <Algebra/Solution/Solver/OneEquationOneVariable/OneEquationOneVariableEqualitySolver.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Math/AlbaMathHelper.hpp>

#include <algorithm>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace algebra
{

namespace DomainAndRange
{

SolutionSet calculateDomainUsingTransitionValues(
        AlbaNumbers const& domainValuesToCheck,
        FunctionToCheck const& functionToCheck)
{
    //This would be better if we have differentiation.
    SolutionSet domain;
    AlbaNumbers numbersWithTransitionValues(
                getNumbersWithTransitionValues(domainValuesToCheck, functionToCheck));
    domain.determineAndAddAcceptedIntervals(numbersWithTransitionValues, [&](AlbaNumber const& value)
    {
        AlbaNumber computedValue(functionToCheck(value));
        return computedValue.isAFiniteValue();
    });
    return domain;
}

SolutionSet calculateDomainForTermWithOneVariable(
        AlbaNumbers const& valuesToCheck,
        Term const& term)
{
    SolutionSet domain;
    VariableNamesSet variableNames(getVariableNames(term));
    if(variableNames.size() == 1)
    {
        string variableName = *variableNames.cbegin();
        SubstitutionOfVariablesToValues substitution;
        domain = calculateDomainUsingTransitionValues(valuesToCheck, [&](AlbaNumber const& value)
        {
                substitution.putVariableWithValue(variableName, value);
                Term computedTerm(substitution.performSubstitutionTo(term));
                AlbaNumber computedValue;
                if(computedTerm.isConstant()){computedValue = computedTerm.getConstantConstReference().getNumberConstReference();}
                return computedValue;
    });
    }
    return domain;
}

SolutionSet calculateDomainForTermWithOneVariable(
        Term const& term)
{
    return calculateDomainForTermWithOneVariable(getValuesForDomainSearching(term), term);
}

SolutionSet calculateDomainForEquation(
        string const& variableNameToCheck,
        AlbaNumbers const& valuesToCheck,
        Equation const& equation)
{
    SolutionSet domain;
    VariableNamesSet variableNames(getVariableNames(equation));
    string inputName, outputName;
    retrieveTwoVariableNames(inputName, outputName, variableNames, variableNameToCheck);
    if(!inputName.empty() && !outputName.empty())
    {
        domain = calculateDomainForEquationWithVariableToSubstitute(inputName, valuesToCheck, equation);
    }
    return domain;
}

SolutionSet calculateDomainForEquation(
        string const& variableNameToCheck,
        Equation const& equation)
{
    return calculateDomainForEquation(variableNameToCheck, getValuesForDomainSearching(equation), equation);
}

SolutionSet calculateRangeForEquation(
        string const& variableNameToCheck,
        AlbaNumbers const& valuesToCheck,
        Equation const& equation)
{
    SolutionSet domain;
    VariableNamesSet variableNames(getVariableNames(equation));
    string inputName, outputName;
    retrieveTwoVariableNames(inputName, outputName, variableNames, variableNameToCheck);
    if(!inputName.empty() && !outputName.empty())
    {
        domain = calculateDomainForEquationWithVariableToSubstitute(outputName, valuesToCheck, equation);
    }
    return domain;
}

SolutionSet calculateRangeForEquation(
        string const& variableNameToCheck,
        Equation const& equation)
{
    return calculateRangeForEquation(variableNameToCheck, getValuesForDomainSearching(equation), equation);
}

SolutionSet calculateDomainForEquationWithVariableToSubstitute(
        string const& variableNameToSubstitute,
        AlbaNumbers const& valuesToCheck,
        Equation const& equation)
{
    SolutionSet domain;
    SubstitutionOfVariablesToValues substitution;
    OneEquationOneVariableEqualitySolver solver;
    domain = calculateDomainUsingTransitionValues(valuesToCheck, [&](AlbaNumber const& value)
    {
            substitution.putVariableWithValue(variableNameToSubstitute, value);
            Equation simplifiedEquation(substitution.performSubstitutionTo(equation));
            Equation equationToSolve(simplifiedEquation.getLeftHandTerm(), "=", Term(Constant(0)));
            SolutionSet solutionSet(solver.calculateSolutionAndReturnSolutionSet(equationToSolve));
            AlbaNumber computedValue(AlbaNumber::Value::NotANumber);
            AlbaNumbers acceptedValues(solutionSet.getAcceptedValues());
            if(!acceptedValues.empty()){computedValue = acceptedValues.back();}
            return computedValue;
});
    return domain;
}

AlbaNumbers getNumbersWithTransitionValues(
        AlbaNumbers const& valuesToCheck,
        FunctionToCheck const& functionToCheck)
{
    AlbaNumbers sortedValues(valuesToCheck);
    sort(sortedValues.begin(), sortedValues.end());

    bool isFirst(true);
    AlbaNumber previousInputValue;
    AlbaNumber previousOutputValue;
    AlbaNumbersSet numbersSet;
    for(AlbaNumber const& inputValue : sortedValues)
    {
        AlbaNumber outputValue(functionToCheck(inputValue));
        if(isFirst)
        {
            isFirst = false;
        }
        else if(previousOutputValue.isAFiniteValue() && !outputValue.isAFiniteValue())
        {
            numbersSet.emplace(getTransitionValue(previousInputValue, inputValue, functionToCheck));
        }
        else if(!previousOutputValue.isAFiniteValue() && outputValue.isAFiniteValue())
        {
            numbersSet.emplace(getTransitionValue(inputValue, previousInputValue, functionToCheck));
        }
        previousInputValue = inputValue;
        previousOutputValue = outputValue;
    }

    if(sortedValues.size() == 1)
    {
        numbersSet.emplace(sortedValues.front());
    }
    else if(sortedValues.size() >= 2)
    {
        numbersSet.emplace(sortedValues.front());
        numbersSet.emplace(sortedValues.back());
    }

    return AlbaNumbers(numbersSet.cbegin(), numbersSet.cend());
}

AlbaNumber getTransitionValue(
        AlbaNumber const& inputValueYieldsToFiniteValue,
        AlbaNumber const& inputValueYieldsToNonFiniteValue,
        FunctionToCheck const& functionToCheck)
{
    AlbaNumber currentValueToFiniteValue = inputValueYieldsToFiniteValue;
    AlbaNumber currentValueToNonFiniteValue = inputValueYieldsToNonFiniteValue;
    AlbaNumber newInputValue(inputValueYieldsToFiniteValue);
    AlbaNumber previousInputValue;
    while(previousInputValue != newInputValue)
    {
        previousInputValue = newInputValue;
        newInputValue = getAverage(currentValueToFiniteValue, currentValueToNonFiniteValue);
        AlbaNumber newOutputValue(functionToCheck(newInputValue));
        if(newOutputValue.isAFiniteValue())
        {
            currentValueToFiniteValue = newInputValue;
        }
        else
        {
            currentValueToNonFiniteValue = newInputValue;
        }
    }
    return newInputValue;
}

void retrieveTwoVariableNames(
        string & nameThatMatch,
        string & nameThatDoesNotMatch,
        VariableNamesSet const& variableNames,
        string const& variableNameToCheck)
{
    if(variableNames.size() == 2)
    {
        VariableNamesSet::const_iterator it = variableNames.cbegin();
        string variableName1=*(it++);
        string variableName2=*(it++);
        if(variableName1 == variableNameToCheck)
        {
            nameThatMatch = variableName1;
            nameThatDoesNotMatch = variableName2;
        }
        else if(variableName2 == variableNameToCheck)
        {
            nameThatMatch = variableName2;
            nameThatDoesNotMatch = variableName1;
        }
    }
}

}

}

}
