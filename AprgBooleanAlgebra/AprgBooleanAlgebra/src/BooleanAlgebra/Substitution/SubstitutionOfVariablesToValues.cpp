#include "SubstitutionOfVariablesToValues.hpp"

#include <BooleanAlgebra/Term/Utilities/BaseTermHelpers.hpp>
#include <BooleanAlgebra/Term/Utilities/ConvertHelpers.hpp>
#include <BooleanAlgebra/Term/Utilities/CreateHelpers.hpp>

using namespace std;

namespace alba {

namespace booleanAlgebra {

SubstitutionOfVariablesToValues::SubstitutionOfVariablesToValues(
    initializer_list<VariableValuePair> const& variablesWithValues) {
    putVariablesWithValues(variablesWithValues);
}

SubstitutionOfVariablesToValues::SubstitutionOfVariablesToValues(VariablesToValuesMap const& variablesWithValues) {
    putVariablesWithValues(variablesWithValues);
}

bool SubstitutionOfVariablesToValues::isEmpty() const { return m_variableToValuesMap.empty(); }

bool SubstitutionOfVariablesToValues::isVariableFound(string const& variable) const {
    return m_variableToValuesMap.find(variable) != m_variableToValuesMap.cend();
}

int SubstitutionOfVariablesToValues::getSize() const { return m_variableToValuesMap.size(); }

bool SubstitutionOfVariablesToValues::getValueForVariable(string const& variable) const {
    bool result(false);
    if (isVariableFound(variable)) {
        result = m_variableToValuesMap.at(variable);
    }
    return result;
}

VariablesToValuesMap const& SubstitutionOfVariablesToValues::getVariableToValuesMap() const {
    return m_variableToValuesMap;
}

Term SubstitutionOfVariablesToValues::performSubstitutionTo(VariableTerm const& variableTerm) const {
    Term result;
    string variableName(variableTerm.getVariableTermName());
    if (isVariableFound(variableName)) {
        result = Term(getValueForVariable(variableName));
    } else {
        result = Term(variableTerm);
    }
    if (variableTerm.isNegated()) {
        result.negate();
    }
    result.simplify();
    return result;
}

Term SubstitutionOfVariablesToValues::performSubstitutionTo(Expression const& expression) const {
    return simplifyAndConvertExpressionToSimplestTerm(performSubstitutionForExpression(expression));
}

Term SubstitutionOfVariablesToValues::performSubstitutionTo(Term const& term) const {
    Term newTerm(term);
    if (term.isVariableTerm()) {
        newTerm = performSubstitutionTo(term.getVariableTermConstReference());
    } else if (term.isExpression()) {
        newTerm = performSubstitutionTo(term.getExpressionConstReference());
    }
    return newTerm;
}

Expression SubstitutionOfVariablesToValues::performSubstitutionForExpression(Expression const& expression) const {
    Expression newExpression(expression);
    performSubstitutionForWrappedTerms(newExpression.getWrappedTermsReference());
    return newExpression;
}

void SubstitutionOfVariablesToValues::putVariablesWithValues(
    initializer_list<VariableValuePair> const& variablesWithValues) {
    for (auto const& [variableName, value] : variablesWithValues) {
        putVariableWithValue(variableName, value);
    }
}

void SubstitutionOfVariablesToValues::putVariablesWithValues(VariablesToValuesMap const& variablesWithValues) {
    for (auto const& [variableName, value] : variablesWithValues) {
        putVariableWithValue(variableName, value);
    }
}

void SubstitutionOfVariablesToValues::putVariableWithValue(string const& variable, bool const value) {
    m_variableToValuesMap[variable] = value;
}

void SubstitutionOfVariablesToValues::performSubstitutionForWrappedTerms(WrappedTerms& wrappedTerms) const {
    for (WrappedTerm& wrappedTerm : wrappedTerms) {
        Term& term(getTermReferenceFromUniquePointer(wrappedTerm.baseTermPointer));
        term = performSubstitutionTo(term);
    }
}

}  // namespace booleanAlgebra

}  // namespace alba
