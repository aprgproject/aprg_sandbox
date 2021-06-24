#pragma once

#include <Equation/Term/Term.hpp>
#include <Equation/Term/TermsWithAssociation.hpp>
#include <Math/AlbaNumber.hpp>

#include <string>

using namespace std;

namespace alba
{

namespace equation
{

using VariablesToValuesMap = std::map<std::string, AlbaNumber>;
using VariableValuePair = std::pair<std::string, AlbaNumber>;

class SubstitutionOfVariablesToValues
{
public:
    SubstitutionOfVariablesToValues();
    SubstitutionOfVariablesToValues(std::initializer_list<VariableValuePair> const& variablesWithValues);
    SubstitutionOfVariablesToValues(VariablesToValuesMap const& variablesWithValues);

    bool isEmpty() const;
    bool isVariableFound(string const& variable) const;
    unsigned int getSize() const;
    AlbaNumber getValueForVariable(std::string const& variable) const;
    Term performSubstitutionTo(Variable const& variable) const;
    Term performSubstitutionTo(Monomial const& monomial) const;    Term performSubstitutionTo(Polynomial const& polynomial) const;
    Term performSubstitutionTo(Expression const& expression) const;
    Term performSubstitutionTo(Function const& functionAsParameter) const;
    Term performSubstitutionTo(Term const& term) const;
    void putVariablesWithValues(std::initializer_list<VariableValuePair> const& variablesWithValues);
    void putVariablesWithValues(VariablesToValuesMap const& variablesWithValues);
    void putVariableWithValue(std::string const& variable, AlbaNumber const& value);

private:
    Monomial performSubstitutionForMonomial(Monomial const& monomial) const;
    Polynomial performSubstitutionForPolynomial(Polynomial const& polynomial) const;
    Expression performSubstitutionForExpression(Expression const& expression) const;
    Function performSubstitutionForFunction(Function const& functionAsParameter) const;
    void performSubstitutionForTermsWithAssociation(TermsWithAssociation & termsWithAssociation) const;
    VariablesToValuesMap m_variableToValuesMap;
};

}

}
