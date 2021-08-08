#pragma once

#include <Algebra/Equation/Equation.hpp>
#include <Algebra/Term/TermTypes/Expression.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>
#include <Algebra/Term/TermTypes/TermsWithAssociation.hpp>

#include <string>

namespace alba
{

namespace algebra
{

using VariablesToTermsMap = std::map<std::string, Term>;
using VariableTermPair = std::pair<std::string, Term>;

class SubstitutionOfVariablesToTerms
{
public:
    SubstitutionOfVariablesToTerms();
    SubstitutionOfVariablesToTerms(std::initializer_list<VariableTermPair> const& variablesWithTerms);
    SubstitutionOfVariablesToTerms(VariablesToTermsMap const& variablesWithTerms);

    bool isEmpty() const;
    bool isVariableFound(std::string const& variable) const;
    unsigned int getSize() const;
    Term getTermForVariable(std::string const& variable) const;
    Term performSubstitutionTo(Variable const& variable) const;
    Term performSubstitutionTo(Monomial const& monomial) const;
    Term performSubstitutionTo(Polynomial const& polynomial) const;
    Term performSubstitutionTo(Expression const& expression) const;
    Term performSubstitutionTo(Function const& functionAsParameter) const;
    Term performSubstitutionTo(Term const& term) const;
    Equation performSubstitutionTo(Equation const& equation) const;

    void putVariablesWithTerms(std::initializer_list<VariableTermPair> const& variablesWithTerms);
    void putVariablesWithTerms(VariablesToTermsMap const& variablesWithTerms);
    void putVariableWithTerm(std::string const& variable, Term const& term);

private:
    Expression performSubstitutionForMonomial(Monomial const& monomial) const;
    Expression performSubstitutionForPolynomial(Polynomial const& polynomial) const;
    Expression performSubstitutionForExpression(Expression const& expression) const;
    Function performSubstitutionForFunction(Function const& functionAsParameter) const;
    void performSubstitutionForTermsWithAssociation(TermsWithAssociation & termsWithAssociation) const;
    VariablesToTermsMap m_variableToExpressionsMap;
};

}

}