#pragma once

#include <Equation/Substitution/VariablesToValuesTypes.hpp>
#include <Equation/Term/Term.hpp>
#include <Equation/Term/TermsWithAssociation.hpp>
#include <Math/AlbaNumber.hpp>

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

    Term performSubstitutionTo(Variable const& variable) const;
    Term performSubstitutionTo(Monomial const& monomial) const;
    Term performSubstitutionTo(Polynomial const& polynomial) const;
    Term performSubstitutionTo(Expression const& expression) const;
    Term performSubstitutionTo(Term const& term) const;

private:
    Monomial performSubstitutionForMonomial(Monomial const& monomial) const;
    Polynomial performSubstitutionForPolynomial(Polynomial const& polynomial) const;
    Expression performSubstitutionForExpression(Expression const& expression) const;
    void performSubstitutionForTermsWithAssociation(TermsWithAssociation & termsWithAssociation) const;
    void putVariablesWithValues(std::initializer_list<VariableValuePair> const& variablesWithExponents);
    void putVariablesWithValues(VariablesToValuesMap const& variablesWithValues);
    void putVariableWithValue(std::string const& variable, AlbaNumber const& exponent);
    VariablesToValuesMap m_variableToValuesMap;
};

}

}
