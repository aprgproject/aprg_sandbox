#pragma once

#include <Expression.hpp>
#include <Term.hpp>
#include <WrappedTerms.hpp>

#include <string>

namespace alba{

namespace equation
{

bool isOperator(std::string const& variableOrOperator);
void wrapTerms(WrappedTerms & wrappedTerms, Terms const& terms);
Terms unwrapTermsAndReturnTerms(WrappedTerms const& wrappedTerms);
Expression createExpression(Terms const& terms);
Terms getTermsInAnExpression(Expression const& expression);

}
}