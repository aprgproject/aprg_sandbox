#include "BaseMutator.hpp"

#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>

namespace alba {

namespace algebra {

void BaseMutator::mutateEquation(Equation &equation) {
    mutateTerm(equation.getLeftHandTermReference());
    mutateTerm(equation.getRightHandTermReference());
}

void BaseMutator::mutateTerm(Term &term) {
    if (term.isConstant()) {
        mutateConstant(term.getAsConstantReference());
    } else if (term.isVariable()) {
        mutateVariable(term.getAsVariableReference());
    } else if (term.isMonomial()) {
        mutateMonomial(term.getAsMonomialReference());
    } else if (term.isPolynomial()) {
        mutatePolynomial(term.getAsPolynomialReference());
    } else if (term.isExpression()) {
        mutateExpression(term.getAsExpressionReference());
    } else if (term.isFunction()) {
        mutateFunction(term.getAsFunctionReference());
    }
}

void BaseMutator::mutateConstant(Constant &) {}

void BaseMutator::mutateVariable(Variable &) {}

void BaseMutator::mutateMonomial(Monomial &) {}

void BaseMutator::mutatePolynomial(Polynomial &polynomial) {
    for (Monomial &monomial : polynomial.getMonomialsReference()) {
        mutateMonomial(monomial);
    }
}

void BaseMutator::mutateExpression(Expression &expression) {
    for (TermWithDetails &termWithDetails :
         expression.getTermsWithAssociationReference().getTermsWithDetailsReference()) {
        mutateTerm(getTermReferenceFromUniquePointer(termWithDetails.baseTermPointer));
    }
}

void BaseMutator::mutateFunction(Function &functionObject) {
    mutateTerm(getTermReferenceFromBaseTerm(functionObject.getInputTermReference()));
}

}  // namespace algebra

}  // namespace alba
