#pragma once

#include <Algebra/Equation/Equation.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>
#include <Algebra/Term/TermTypes/TermsWithAssociation.hpp>
#include <Math/Number/AlbaNumber.hpp>

#include <string>
namespace alba
{
namespace algebra
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
    bool isVariableFound(std::string const& variable) const;
    unsigned int getSize() const;
    AlbaNumber getValueForVariable(std::string const& variable) const;
    Term performSubstitutionTo(Variable const& variable) const;
    Term performSubstitutionTo(Monomial const& monomial) const;
    Term performSubstitutionTo(Polynomial const& polynomial) const;
    Term performSubstitutionTo(Expression const& expression) const;
    Term performSubstitutionTo(Function const& functionAsParameter) const;
    Term performSubstitutionTo(Term const& term) const;
    Equation performSubstitutionTo(Equation const& equation) const;

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
