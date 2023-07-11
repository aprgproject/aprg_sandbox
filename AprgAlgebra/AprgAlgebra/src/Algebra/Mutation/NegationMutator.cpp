#include "NegationMutator.hpp"

#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>

namespace alba {

namespace algebra {

void NegationMutator::mutateTerm(Term &term) {
    if (term.isConstant()) {
        mutateConstant(term.getAsConstantReference());
    } else if (term.isVariable()) {
        term = Term(Monomial(-1, {{term.getAsVariableReference().getVariableName(), 1}}));
    } else if (term.isMonomial()) {
        mutateMonomial(term.getAsMonomialReference());
    } else if (term.isPolynomial()) {
        mutatePolynomial(term.getAsPolynomialReference());
    } else if (term.isExpression()) {
        mutateExpression(term.getAsExpressionReference());
    } else if (term.isFunction()) {
        term = -1 * term;
    }
    term.simplify();
}

void NegationMutator::mutateConstant(Constant &constant) {
    constant.setNumber(constant.getNumber() * -1);
}

void NegationMutator::mutateVariable(Variable &) {}

void NegationMutator::mutateMonomial(Monomial &monomial) { monomial.multiplyNumber(AlbaNumber(-1)); }

void NegationMutator::mutateExpression(Expression &expression) {
    if (OperatorLevel::AdditionAndSubtraction == expression.getCommonOperatorLevel()) {
        TermsWithDetails &termsWithDetails(
            expression.getTermsWithAssociationReference().getTermsWithDetailsReference());
        for (TermWithDetails &termWithDetails : termsWithDetails) {
            termWithDetails.reverseAssociation();
        }
    } else {
        expression.putTermWithMultiplicationIfNeeded(Term(-1));
    }
    expression.simplify();
}

void NegationMutator::mutateFunction(Function &) {}

}  // namespace algebra

}  // namespace alba
