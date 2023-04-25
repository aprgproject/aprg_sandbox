#include "CreateHelpers.hpp"

#include <BooleanAlgebra/Constructs/TermsAggregator.hpp>
#include <BooleanAlgebra/Term/Utilities/ConvertHelpers.hpp>

using namespace std;

namespace alba {

namespace booleanAlgebra {

Expression createExpressionInAnExpression(Expression const& expression) { return Expression(Term(expression)); }

Expression createAndWrapExpressionFromATerm(Term const& term) { return Expression(term); }

Expression createOrCopyExpressionFromATerm(Term const& term) {
    Expression result;
    if (!term.isEmpty()) {
        if (term.isExpression()) {
            result = term.getExpressionConstReference();
        } else {
            result = Expression(term);
        }
    }
    return result;
}

Expression createExpressionIfPossible(Terms const& terms) {
    Expression result;
    TermsAggregator aggregator(terms);
    aggregator.buildExpressionFromTerms();
    Terms const& builtTerms(aggregator.getTermsConstReference());
    if (builtTerms.size() == 1) {
        result = createOrCopyExpressionFromATerm(builtTerms.at(0));
    }
    return result;
}

Expression createSimplifiedExpressionIfPossible(Terms const& terms) {
    Expression result;
    TermsAggregator aggregator(terms);
    aggregator.simplifyTerms();
    Terms const& simplifiedTerms(aggregator.getTermsConstReference());
    if (simplifiedTerms.size() == 1) {
        result = createOrCopyExpressionFromATerm(simplifiedTerms.at(0));
    }
    return result;
}

Term createTermWithAndOperationWrappedTerms(WrappedTerms const& wrappedTerms) {
    Term result(true);
    if (!wrappedTerms.empty()) {
        result = convertExpressionToSimplestTerm(Expression(OperatorLevel::And, wrappedTerms));
    }
    return result;
}

Term createTermWithOrOperationWrappedTerms(WrappedTerms const& wrappedTerms) {
    Term result(false);
    if (!wrappedTerms.empty()) {
        result = convertExpressionToSimplestTerm(Expression(OperatorLevel::Or, wrappedTerms));
    }
    return result;
}

}  // namespace booleanAlgebra

}  // namespace alba
