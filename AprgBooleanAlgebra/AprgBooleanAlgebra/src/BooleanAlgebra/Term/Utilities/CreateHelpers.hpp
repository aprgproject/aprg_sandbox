#pragma once

#include <BooleanAlgebra/Term/TermTypes/Term.hpp>

#include <string>

namespace alba {

namespace booleanAlgebra {

Expression createExpressionInAnExpression(Expression const& expression);
Expression createAndWrapExpressionFromATerm(Term const& term);
Expression createOrCopyExpressionFromATerm(Term const& term);
Expression createExpressionIfPossible(Terms const& terms);
Expression createSimplifiedExpressionIfPossible(Terms const& terms);
Term createTermWithAndOperationWrappedTerms(WrappedTerms const& wrappedTerms);
Term createTermWithOrOperationWrappedTerms(WrappedTerms const& wrappedTerms);

}  // namespace booleanAlgebra

}  // namespace alba
