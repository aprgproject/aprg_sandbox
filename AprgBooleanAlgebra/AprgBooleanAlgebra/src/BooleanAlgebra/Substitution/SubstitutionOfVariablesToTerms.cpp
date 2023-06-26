#include "SubstitutionOfVariablesToTerms.hpp"

#include <BooleanAlgebra/Term/Utilities/BaseTermHelpers.hpp>
#include <BooleanAlgebra/Term/Utilities/ConvertHelpers.hpp>
#include <BooleanAlgebra/Term/Utilities/CreateHelpers.hpp>

using namespace std;

namespace alba {

namespace booleanAlgebra {

SubstitutionOfVariablesToTerms::SubstitutionOfVariablesToTerms(
    initializer_list<VariableTermPair> const& variablesWithTerms) {
    putVariablesWithTerms(variablesWithTerms);
}

SubstitutionOfVariablesToTerms::SubstitutionOfVariablesToTerms(VariablesToTermsMap const& variablesWithTerms) {
    putVariablesWithTerms(variablesWithTerms);
}

bool SubstitutionOfVariablesToTerms::isEmpty() const { return m_variableToTermsMap.empty(); }

bool SubstitutionOfVariablesToTerms::isVariableFound(string const& variable) const {
    return m_variableToTermsMap.find(variable) != m_variableToTermsMap.cend();
}

int SubstitutionOfVariablesToTerms::getSize() const { return m_variableToTermsMap.size(); }

Term SubstitutionOfVariablesToTerms::getTermForVariable(string const& variable) const {
    Term result;
    if (isVariableFound(variable)) {
        result = m_variableToTermsMap.at(variable);
    }
    return result;
}

VariablesToTermsMap const& SubstitutionOfVariablesToTerms::getVariablesToTermsMap() const {
    return m_variableToTermsMap;
}

Term SubstitutionOfVariablesToTerms::performSubstitutionTo(VariableTerm const& variableTerm) const {
    Term result;
    string variableName(variableTerm.getVariableTermName());
    if (isVariableFound(variableName)) {
        result = getTermForVariable(variableName);
    } else {
        result = Term(variableTerm);
    }
    if (variableTerm.isNegated()) {
        result.negate();
    }
    result.simplify();
    return result;
}

Term SubstitutionOfVariablesToTerms::performSubstitutionTo(Expression const& expression) const {
    return simplifyAndConvertExpressionToSimplestTerm(performSubstitutionForExpression(expression));
}

Term SubstitutionOfVariablesToTerms::performSubstitutionTo(Term const& term) const {
    Term newTerm(term);
    if (term.isVariableTerm()) {
        newTerm = performSubstitutionTo(term.getVariableTermConstReference());
    } else if (term.isExpression()) {
        newTerm = performSubstitutionTo(term.getExpressionConstReference());
    }
    return newTerm;
}

Expression SubstitutionOfVariablesToTerms::performSubstitutionForExpression(Expression const& expression) const {
    Expression newExpression(expression);
    performSubstitutionForWrappedTerms(newExpression.getWrappedTermsReference());
    return newExpression;
}

void SubstitutionOfVariablesToTerms::putVariablesWithTerms(
    initializer_list<VariableTermPair> const& variablesWithTerms) {
    for (VariableTermPair const& variableValuesPair : variablesWithTerms) {
        putVariableWithTerm(variableValuesPair.first, variableValuesPair.second);
    }
}

void SubstitutionOfVariablesToTerms::putVariablesWithTerms(VariablesToTermsMap const& variablesWithTerms) {
    for (auto const& variableValuesPair : variablesWithTerms) {
        putVariableWithTerm(variableValuesPair.first, variableValuesPair.second);
    }
}

void SubstitutionOfVariablesToTerms::putVariableWithTerm(string const& variable, Term const& term) {
    m_variableToTermsMap[variable] = term;
    m_variableToTermsMap[variable].simplify();
}

void SubstitutionOfVariablesToTerms::performSubstitutionForWrappedTerms(WrappedTerms& wrappedTerms) const {    for (WrappedTerm& wrappedTerm : wrappedTerms) {
        Term& term(getTermReferenceFromUniquePointer(wrappedTerm.baseTermPointer));
        term = performSubstitutionTo(term);
    }}

}  // namespace booleanAlgebra

}  // namespace alba
