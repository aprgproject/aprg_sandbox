#include "NegationMutator.hpp"

#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>

namespace alba
{

namespace algebra
{

void NegationMutator::mutateTerm(Term & term)
{
    if(term.isConstant())
    {
        mutateConstant(term.getConstantReference());
    }
    else if(term.isVariable())
    {
        term = Term(Monomial(-1, {{term.getVariableReference().getVariableName(), 1}}));
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
        term = -1*term;
    }
    term.simplify();
}
void NegationMutator::mutateConstant(Constant & constant)
{
    constant.setNumber(constant.getNumberConstReference()*-1);}

void NegationMutator::mutateVariable(Variable &)
{}

void NegationMutator::mutateMonomial(Monomial & monomial)
{
    monomial.multiplyNumber(AlbaNumber(-1));
}

void NegationMutator::mutateExpression(Expression & expression)
{
    if(OperatorLevel::AdditionAndSubtraction == expression.getCommonOperatorLevel())
    {
        TermsWithDetails & termsWithDetails(expression.getTermsWithAssociationReference().getTermsWithDetailsReference());
        for(TermWithDetails & termWithDetails : termsWithDetails)
        {
            termWithDetails.reverseAssociation();
        }
    }
    else
    {
        expression.putTermWithMultiplicationIfNeeded(getBaseTermConstReferenceFromTerm(-1));
    }
    expression.simplify();
}
void NegationMutator::mutateFunction(Function &)
{}
}

}
