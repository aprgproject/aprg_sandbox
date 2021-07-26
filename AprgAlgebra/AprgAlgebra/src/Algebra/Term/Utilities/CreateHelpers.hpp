#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

#include <string>

namespace alba
{

namespace algebra
{

Monomial createMonomialFromConstant(Constant const& constant);
Monomial createMonomialFromVariable(Variable const& variable);
Monomial createMonomialIfPossible(Term const& term);
Polynomial createPolynomialFromConstant(Constant const& constant);
Polynomial createPolynomialFromVariable(Variable const& variable);
Polynomial createPolynomialFromMonomial(Monomial const& monomial);
Polynomial createPolynomialIfPossible(Term const& term);
Expression createExpressionInAnExpression(Expression const& expression);
Expression createAndWrapExpressionFromATerm(Term const& term);
Expression createOrCopyExpressionFromATerm(Term const& term);
Expression createExpressionIfPossible(Terms const& terms);
Expression createSimplifiedExpressionIfPossible(Terms const& terms);
Function createFunctionWithEmptyInputExpression(std::string const& functionName);

}

}
