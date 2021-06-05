#pragma once

#include <BaseTermPointers.hpp>
#include <Expression.hpp>
#include <Term.hpp>
#include <WrappedTerms.hpp>

#include <string>

namespace alba
{

namespace equation
{

bool isOperator(std::string const& variableOrOperator);
bool isOperatorForMultipleTerms(std::string const& variableOrOperator);

bool canBeAddedOrSubtracted(Monomial const& monomial1, Monomial const& monomial2);
bool canBeAddedOrSubtracted(Monomial const& monomial, Variable const& variable);

Term createTerm(BaseTermUniquePointer const& baseTerm);
BaseTermUniquePointer createBaseTermUniquePointer(Term const& term);

void performChangeForVariables(
        Monomial::VariablesToExponentsMap & variablesMap,
        Monomial::ChangeExponentsForVariableFunction const& changeVariablesFunction);
Monomial::VariablesToExponentsMap combineVariableExponentMapByMultiplication(
        Monomial::VariablesToExponentsMap const& variablesMap1,
        Monomial::VariablesToExponentsMap const& variablesMap2);
Monomial::VariablesToExponentsMap combineVariableExponentMapByDivision(
        Monomial::VariablesToExponentsMap const& variablesMap1,
        Monomial::VariablesToExponentsMap const& variablesMap2);

void wrapTerms(WrappedTerms & wrappedTerms, Terms const& terms);
Terms unwrapTermsAndReturnTerms(WrappedTerms const& wrappedTerms);

Expression createExpression(Terms const& terms);
Terms getTermsInAnExpression(Expression const& expression);

}

}
