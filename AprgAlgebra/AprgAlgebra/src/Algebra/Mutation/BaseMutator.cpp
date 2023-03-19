#include "BaseMutator.hpp"

#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>

namespace alba
{

namespace algebra
{

void BaseMutator::mutateEquation(Equation & equation)
{
    mutateTerm(equation.getLeftHandTermReference());
    mutateTerm(equation.getRightHandTermReference());
}

void BaseMutator::mutateTerm(Term & term)
{
    if(term.isConstant())
    {
        mutateConstant(term.getConstantReference());
    }
    else if(term.isVariable())
    {
        mutateVariable(term.getVariableReference());
    }
    else if(term.isMonomial())
    {
        mutateMonomial(term.getMonomialReference());
    }
    else if(term.isPolynomial())
    {
        mutatePolynomial(term.getPolynomialReference());
    }
    else if(term.isExpression())
    {
        mutateExpression(term.getExpressionReference());
    }
    else if(term.isFunction())
    {
        mutateFunction(term.getFunctionReference());
    }
}

void BaseMutator::mutateConstant(Constant &)
{}

void BaseMutator::mutateVariable(Variable &)
{}

void BaseMutator::mutateMonomial(Monomial &)
{}

void BaseMutator::mutatePolynomial(Polynomial & polynomial)
{
    for(Monomial & monomial : polynomial.getMonomialsReference())
    {
        mutateMonomial(monomial);
    }
}

void BaseMutator::mutateExpression(Expression & expression)
{
    for(TermWithDetails & termWithDetails
        : expression.getTermsWithAssociationReference().getTermsWithDetailsReference())
    {
        mutateTerm(getTermReferenceFromUniquePointer(termWithDetails.baseTermPointer));
    }
}

void BaseMutator::mutateFunction(Function & functionObject)
{
    mutateTerm(getTermReferenceFromBaseTerm(functionObject.getInputTermReference()));
}

}

}
