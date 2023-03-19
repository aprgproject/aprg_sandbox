#pragma once

#include <BooleanAlgebra/Term/TermTypes/Term.hpp>

#include <map>
#include <vector>

namespace alba
{

namespace booleanAlgebra
{

using VariablesToTermsMap = std::map<std::string, Term>;
using VariableTermPair = std::pair<std::string, Term>;

class SubstitutionOfVariablesToTerms
{
public:
    SubstitutionOfVariablesToTerms() = default;
    SubstitutionOfVariablesToTerms(std::initializer_list<VariableTermPair> const& variablesWithTerms);
    SubstitutionOfVariablesToTerms(VariablesToTermsMap const& variablesWithTerms);
    bool isEmpty() const;
    bool isVariableFound(std::string const& variable) const;
    unsigned int getSize() const;    Term getTermForVariable(std::string const& variable) const;
    VariablesToTermsMap const& getVariablesToTermsMap() const;

    Term performSubstitutionTo(VariableTerm const& variableTerm) const;
    Term performSubstitutionTo(Expression const& expression) const;
    Term performSubstitutionTo(Term const& term) const;

    Expression performSubstitutionForExpression(Expression const& expression) const;

    void putVariablesWithTerms(std::initializer_list<VariableTermPair> const& variablesWithTerms);
    void putVariablesWithTerms(VariablesToTermsMap const& variablesWithTerms);
    void putVariableWithTerm(std::string const& variable, Term const& term);

private:
    void performSubstitutionForWrappedTerms(WrappedTerms & wrappedTerms) const;
    VariablesToTermsMap m_variableToTermsMap;
};

using SubstitutionsOfVariablesToTerms=std::vector<SubstitutionOfVariablesToTerms>;

}

}
