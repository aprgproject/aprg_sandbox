#pragma once

#include <Math/AlbaNumber.hpp>
#include <Term.hpp>
#include <VariablesToValuesTypes.hpp>

#include <map>
#include <string>

using namespace std;

namespace alba
{

namespace equation
{

class SubstitutionOfVariablesToValues
{
public:

    SubstitutionOfVariablesToValues(std::initializer_list<VariableValuePair> const& variablesWithValues);
    SubstitutionOfVariablesToValues(VariablesToValuesMap const& variablesWithValues);

    bool isVariableFound(string const& variable) const;
    AlbaNumber getValueForVariable(std::string const& variable) const;

private:
    void putVariablesWithValues(std::initializer_list<VariableValuePair> const& variablesWithExponents);
    void putVariablesWithValues(VariablesToValuesMap const& variablesWithValues);
    void putVariableWithValue(std::string const& variable, AlbaNumber const& exponent);
    VariablesToValuesMap m_variableToValuesMap;
};

}

}
