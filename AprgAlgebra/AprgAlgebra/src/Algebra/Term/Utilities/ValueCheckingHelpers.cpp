#include "ValueCheckingHelpers.hpp"

#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>

using TermsWithDetails=alba::algebra::TermsWithAssociation::TermsWithDetails;
using TermWithDetails=alba::algebra::TermsWithAssociation::TermWithDetails;

namespace alba
{

namespace algebra
{

bool willHaveNoEffectOnAdditionOrSubtraction(Term const& term)
{
    return term.isEmpty() || term.isTheValueZero();
}

bool willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term const& term)
{
    return term.isEmpty() || term.isTheValueOne();
}

bool isNotANumber(Term const& term)
{
    bool result(false);
    if(term.isConstant())
    {
        result = isNotANumber(term.getConstantConstReference());
    }
    else if(term.isMonomial())
    {
        result = isNotANumber(term.getMonomialConstReference());
    }
    else if(term.isPolynomial())
    {
        result = isNotANumber(term.getPolynomialConstReference());
    }
    else if(term.isExpression())
    {
        result = isNotANumber(term.getExpressionConstReference());
    }
    return result;
}

bool isNotANumber(Constant const& constant)
{
    return constant.getNumberConstReference().isNotANumber();
}

bool isNotANumber(Monomial const& monomial)
{
    return monomial.isConstantOnly() && monomial.getConstantConstReference().isNotANumber();
}

bool isNotANumber(Polynomial const& polynomial)
{
    return polynomial.isOneMonomial() && isNotANumber(polynomial.getFirstMonomial());
}

bool isNotANumber(Expression const& expression)
{
    bool result(false);
    TermsWithDetails const& termsWithDetails(expression.getTermsWithAssociation().getTermsWithDetails());
    if(termsWithDetails.size() == 1)
    {
        result = isNotANumber(getTermConstReferenceFromSharedPointer(termsWithDetails.front().baseTermSharedPointer));
    }
    return result;
}

bool hasNotANumber(Term const& term)
{
    bool result(false);
    if(term.isConstant())
    {
        result = isNotANumber(term.getConstantConstReference());
    }
    else if(term.isMonomial())
    {
        result = hasNotANumber(term.getMonomialConstReference());
    }
    else if(term.isPolynomial())
    {
        result = hasNotANumber(term.getPolynomialConstReference());
    }
    else if(term.isExpression())
    {
        result = hasNotANumber(term.getExpressionConstReference());
    }
    else if(term.isFunction())
    {
        result = hasNotANumber(term.getFunctionConstReference());
    }
    return result;
}

bool hasNotANumber(Monomial const& monomial)
{
    bool result(isNotANumber(monomial.getConstantConstReference()));
    if(!result)
    {
        for(Monomial::VariableExponentPair const& variableExponentsPair
            : monomial.getVariablesToExponentsMapConstReference())
        {
            result |= variableExponentsPair.second.isNotANumber();
            if(result)
            {
                break;
            }
        }
    }
    return result;
}

bool hasNotANumber(Polynomial const& polynomial)
{
    bool result(false);
    for(Monomial const& monomial : polynomial.getMonomialsConstReference())
    {
        result |= hasNotANumber(monomial);
        if(result)
        {
            break;
        }
    }
    return result;
}

bool hasNotANumber(Expression const& expression)
{
    bool result(false);
    TermsWithDetails const& termsWithDetails(expression.getTermsWithAssociation().getTermsWithDetails());
    for(TermWithDetails const& termWithDetails : termsWithDetails)
    {
        result |= hasNotANumber(getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
        if(result)
        {
            break;
        }
    }
    return result;
}

bool hasNotANumber(Function const& function)
{
    return hasNotANumber(function.getInputTermConstReference());
}

bool isAFiniteConstant(Term const& term)
{
    bool result(false);
    if(term.isConstant())
    {
        result = term.getConstantConstReference().getNumberConstReference().isAFiniteValue();
    }
    return result;
}

}

}
