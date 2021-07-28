#include "Domain.hpp"

#include <Algebra/Solution/SolutionUtilities.hpp>
#include <Algebra/Substitution/SubstitutionOfVariablesToValues.hpp>
#include <Algebra/Term/Utilities/TermUtilities.hpp>
#include <Math/AlbaMathHelper.hpp>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace algebra
{

namespace Domain
{

SolutionSet calculateDomainForTermWithOneVariable(
        Term const& term)
{
    return calculateDomainForTermWithOneVariable(getValuesForDomainSearching(term), term);
}

SolutionSet calculateDomainForTermWithOneVariable(
        AlbaNumbers const& valuesToCheck,
        Term const& term)
{
    SolutionSet domain;
    VariableNamesSet variableNames(getVariableNames(term));
    SubstitutionOfVariablesToValues substitution;
    if(variableNames.size() == 1)
    {
        string variableName = *variableNames.cbegin();
        domain = calculateDomain(valuesToCheck,  [&](AlbaNumber const& value)
        {
                substitution.putVariableWithValue(variableName, value);
                Term computedTerm(substitution.performSubstitutionTo(term));
                AlbaNumber computedValue;
                if(computedTerm.isConstant())
        {
                computedValue = computedTerm.getConstantConstReference().getNumberConstReference();
    }
                return computedValue;
    });
    }
    return domain;
}

SolutionSet calculateDomain(
        AlbaNumbers const& valuesToCheck,
        FunctionToCheck const& functionToCheck)
{
    SolutionSet domain;
    AlbaNumbers transitionValues(getTransitionValues(valuesToCheck, functionToCheck));
    domain.determineAndAddAcceptedIntervals(transitionValues, [&](AlbaNumber const& value)
    {
        AlbaNumber computedValue(functionToCheck(value));
        return computedValue.isAFiniteValue();
    });
    return domain;
}

AlbaNumbers getTransitionValues(
        AlbaNumbers const& valuesToCheck,
        FunctionToCheck const& functionToCheck)
{
    AlbaNumbers transitionValues;
    bool isFirst(true);
    AlbaNumber previousInputValue;
    AlbaNumber previousOutputValue;

    for(AlbaNumber const& inputValue : valuesToCheck)
    {
        AlbaNumber outputValue(functionToCheck(inputValue));
        if(isFirst)
        {
            isFirst = false;
        }
        else if(previousOutputValue.isAFiniteValue() && !outputValue.isAFiniteValue())
        {
            transitionValues.emplace_back(getTransitionValue(previousInputValue, inputValue, functionToCheck));
        }
        else if(!previousOutputValue.isAFiniteValue() && outputValue.isAFiniteValue())
        {
            transitionValues.emplace_back(getTransitionValue(inputValue, previousInputValue, functionToCheck));
        }
        previousInputValue = inputValue;
        previousOutputValue = outputValue;
    }
    return transitionValues;
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

}

}

}
