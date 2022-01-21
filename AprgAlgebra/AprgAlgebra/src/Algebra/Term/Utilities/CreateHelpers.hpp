#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

#include <string>

namespace alba
{

namespace algebra
{

Monomial createMonomialFromNumber(AlbaNumber const& number);
Monomial createMonomialFromVariable(Variable const& variable);
Monomial createMonomialIfPossible(Term const& term);
Polynomial createPolynomialFromNumber(AlbaNumber const& number);
Polynomial createPolynomialFromVariable(Variable const& variable);
Polynomial createPolynomialFromMonomial(Monomial const& monomial);
Polynomial createPolynomialIfPossible(Term const& term);
Expression createExpressionInAnExpression(Expression const& expression);
Expression createAndWrapExpressionFromATerm(Term const& term);
Expression createOrCopyExpressionFromATerm(Term const& term);
Expression createExpressionIfPossible(Terms const& terms);
Expression createSimplifiedExpressionIfPossible(Terms const& terms);
Function createFunctionWithEmptyInputExpression(std::string const& functionName);
Function createFunctionInAnFunction(Function const& functionObject);
Term createTermWithAdditionAndSubtractionTermsWithDetails(TermsWithDetails const& termsWithDetails);
Term createTermWithMultiplicationAndDivisionTermsWithDetails(TermsWithDetails const& termsWithDetails);
Term createTermWithRaiseToPowerTermsWithDetails(TermsWithDetails const& termsWithDetails);

}

}
