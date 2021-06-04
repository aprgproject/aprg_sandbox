#pragma once

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
void performChangeForVariables(
        Monomial::VariablesToExponentsMap & variableToExponentMap,
        Monomial::ChangeExponentsForVariableFunction const& changeVariablesFunction);

void wrapTerms(WrappedTerms & wrappedTerms, Terms const& terms);
Terms unwrapTermsAndReturnTerms(WrappedTerms const& wrappedTerms);
Expression createExpression(Terms const& terms);Terms getTermsInAnExpression(Expression const& expression);

}
}
