#pragma once

#include <BooleanAlgebra/Term/TermTypes/Term.hpp>

#include <map>

namespace alba
{

namespace booleanAlgebra
{

using VariablesToValuesMap = std::map<std::string, bool>;
using VariableValuePair = std::pair<std::string, bool>;

class SubstitutionOfVariablesToValues
{
public:
    SubstitutionOfVariablesToValues();
    SubstitutionOfVariablesToValues(std::initializer_list<VariableValuePair> const& variablesWithValues);
    SubstitutionOfVariablesToValues(VariablesToValuesMap const& variablesWithValues);

    bool isEmpty() const;
    bool isVariableFound(std::string const& variable) const;
    unsigned int getSize() const;
    bool getValueForVariable(std::string const& variable) const;
    VariablesToValuesMap const& getVariableToValuesMap() const;

    Term performSubstitutionTo(VariableTerm const& variableTerm) const;
    Term performSubstitutionTo(Expression const& expression) const;
    Term performSubstitutionTo(Term const& term) const;

    Expression performSubstitutionForExpression(Expression const& expression) const;

    void putVariablesWithValues(std::initializer_list<VariableValuePair> const& variablesWithValues);
    void putVariablesWithValues(VariablesToValuesMap const& variablesWithValues);
    void putVariableWithValue(std::string const& variable, bool const value);

private:
    void performSubstitutionForWrappedTerms(WrappedTerms & wrappedTerms) const;
    VariablesToValuesMap m_variableToValuesMap;
};

using SubstitutionsOfVariablesToValues=std::vector<SubstitutionOfVariablesToValues>;

}

}
