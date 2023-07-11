#include "CreateHelpers.hpp"

#include <Algebra/Constructs/TermsAggregator.hpp>
#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/PolynomialHelpers.hpp>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba {

namespace algebra {

Monomial createMonomialFromNumber(AlbaNumber const& number) { return Monomial(number, {}); }

Monomial createMonomialFromVariable(Variable const& variable) { return Monomial(1, {{variable.getVariableName(), 1}}); }

Monomial createMonomialIfPossible(Term const& term) {
    Monomial result;
    if (term.isConstant()) {
        result = createMonomialFromNumber(term.getAsNumber());
    } else if (term.isVariable()) {
        result = createMonomialFromVariable(term.getAsVariable());
    } else if (term.isMonomial()) {
        result = term.getAsMonomial();
    } else if (term.isPolynomial()) {
        Polynomial const& polynomial(term.getAsPolynomial());
        if (isOneMonomial(polynomial)) {
            result = getFirstMonomial(polynomial);
        }    }
    return result;
}
Polynomial createPolynomialFromNumber(AlbaNumber const& number) { return Polynomial{createMonomialFromNumber(number)}; }

Polynomial createPolynomialFromVariable(Variable const& variable) {
    return Polynomial{createMonomialFromVariable(variable)};
}

Polynomial createPolynomialFromMonomial(Monomial const& monomial) { return Polynomial{monomial}; }

Polynomial createPolynomialIfPossible(Term const& term) {
    Polynomial result;
    if (term.isConstant()) {
        result = createPolynomialFromNumber(term.getAsNumber());
    } else if (term.isVariable()) {
        result = createPolynomialFromVariable(term.getAsVariable());
    } else if (term.isMonomial()) {
        result = createPolynomialFromMonomial(term.getAsMonomial());
    } else if (term.isPolynomial()) {
        result = term.getAsPolynomial();
    }
    return result;
}
Expression createExpressionInAnExpression(Expression const& expression) { return Expression(Term(expression)); }

Expression createAndWrapExpressionFromATerm(Term const& term) { return Expression(term); }
Expression createOrCopyExpressionFromATerm(Term const& term) {
    Expression result;
    if (!term.isEmpty()) {
        if (term.isExpression()) {
            result = term.getAsExpression();
        } else {
            result = Expression(term);
        }    }
    return result;
}
Expression createExpressionIfPossible(Terms const& terms) {
    Expression result;
    TermsAggregator aggregator(terms);
    aggregator.buildExpressionFromTerms();
    Terms const& builtTerms(aggregator.getTermsConstReference());
    if (builtTerms.size() == 1) {
        result = createOrCopyExpressionFromATerm(builtTerms[0]);
    }
    return result;
}

Expression createSimplifiedExpressionIfPossible(Terms const& terms) {
    Expression result;
    TermsAggregator aggregator(terms);
    aggregator.simplifyTerms();
    Terms const& simplifiedTerms(aggregator.getTermsConstReference());
    if (simplifiedTerms.size() == 1) {
        result = createOrCopyExpressionFromATerm(simplifiedTerms[0]);
    }
    return result;
}

Function createFunctionWithEmptyInputExpression(string const& functionName) {
    Function result;
    if ("abs" == functionName) {
        result = abs(Term());
    }
    return result;
}

Function createFunctionInAnFunction(Function const& functionObject) {
    return Function(functionObject.getFunctionName(), Term(functionObject), functionObject.getEvaluationFunction());
}

Term createTermWithAdditionAndSubtractionTermsWithDetails(TermsWithDetails const& termsWithDetails) {
    Term result(0);
    if (!termsWithDetails.empty()) {
        result = convertExpressionToSimplestTerm(Expression(OperatorLevel::AdditionAndSubtraction, termsWithDetails));
    }
    return result;
}

Term createTermWithMultiplicationAndDivisionTermsWithDetails(TermsWithDetails const& termsWithDetails) {
    Term result(1);
    if (!termsWithDetails.empty()) {
        result =
            convertExpressionToSimplestTerm(Expression(OperatorLevel::MultiplicationAndDivision, termsWithDetails));
    }
    return result;
}

Term createTermWithRaiseToPowerTermsWithDetails(TermsWithDetails const& termsWithDetails) {
    return convertExpressionToSimplestTerm(Expression(OperatorLevel::RaiseToPower, termsWithDetails));
}

}  // namespace algebra

}  // namespace alba
