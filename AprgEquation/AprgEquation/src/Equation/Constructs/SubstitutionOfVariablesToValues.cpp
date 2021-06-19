#include "SubstitutionOfVariablesToValues.hpp"

using namespace std;
using TermWithDetails=alba::equation::TermsWithAssociation::TermWithDetails;
using TermsWithDetails=alba::equation::TermsWithAssociation::TermsWithDetails;

namespace alba
{

namespace equation
{

SubstitutionOfVariablesToValues::SubstitutionOfVariablesToValues(std::initializer_list<VariableValuePair> const& variablesWithValues)
{
    putVariablesWithValues(variablesWithValues);
}

SubstitutionOfVariablesToValues::SubstitutionOfVariablesToValues(VariablesToValuesMap const& variablesWithValues)
{
    putVariablesWithValues(variablesWithValues);
}

bool SubstitutionOfVariablesToValues::isVariableFound(string const& variable) const
{
    return m_variableToValuesMap.find(variable) != m_variableToValuesMap.cend();
}

AlbaNumber SubstitutionOfVariablesToValues::getValueForVariable(string const& variable) const
{
    AlbaNumber result;
    if(isVariableFound(variable))
    {
        result = m_variableToValuesMap.at(variable);
    }
    return result;
}

void SubstitutionOfVariablesToValues::putVariablesWithValues(initializer_list<VariableValuePair> const& variablesWithValues)
{
    for(VariableValuePair const& variableValuesPair : variablesWithValues)
    {
        putVariableWithValue(variableValuesPair.first, variableValuesPair.second);
    }
}

void SubstitutionOfVariablesToValues::putVariablesWithValues(VariablesToValuesMap const& variablesWithValues)
{
    for(VariableValuePair const& variableValuesPair : variablesWithValues)
    {
        putVariableWithValue(variableValuesPair.first, variableValuesPair.second);
    }
}

void SubstitutionOfVariablesToValues::putVariableWithValue(string const& variable, AlbaNumber const& exponent)
{
    m_variableToValuesMap[variable]=exponent;
}

}

}
