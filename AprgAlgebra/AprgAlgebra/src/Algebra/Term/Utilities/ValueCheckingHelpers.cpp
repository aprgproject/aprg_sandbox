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
    return term.isEmpty() || isTheValue(term, 0);
}

bool willHaveNoEffectOnMultiplicationOrDivisionOrRaiseToPower(Term const& term)
{
    return term.isEmpty() || isTheValue(term, 1);
}

bool isTheValue(Term const& term, AlbaNumber const& number)
{
    bool result(false);
    if(term.isConstant())
    {
        result = isTheValue(term.getConstantConstReference(), number);
    }
    else if(term.isMonomial())
    {
        result = isTheValue(term.getMonomialConstReference(), number);
    }
    else if(term.isPolynomial())
    {
        result = isTheValue(term.getPolynomialConstReference(), number);
    }
    else if(term.isExpression())
    {
        result = isTheValue(term.getExpressionConstReference(), number);
    }
    return result;
}

bool isTheValue(Constant const& constant, AlbaNumber const& number)
{
    return constant.getNumberConstReference() == number;
}

bool isTheValue(Monomial const& monomial, AlbaNumber const& number)
{
    bool result(false);
    if(number == 0)
    {
        result = monomial.getConstantConstReference() == number;
    }
    else
    {
        result = monomial.isConstantOnly() && monomial.getConstantConstReference() == number;
    }
    return result;
}

bool isTheValue(Polynomial const& polynomial, AlbaNumber const& number)
{
    bool result(false);
    if(number == 0)
    {
        result = polynomial.getMonomialsConstReference().empty();
    }
    else
    {
        result = polynomial.isOneMonomial() && isTheValue(polynomial.getFirstMonomial(), number);
    }
    return result;
}

bool isTheValue(Expression const& expression, AlbaNumber const& number)
{
    bool result(false);
    TermsWithDetails const& termsWithDetails(expression.getTermsWithAssociation().getTermsWithDetails());
    if(termsWithDetails.size() == 1)
    {
        result = isTheValue(
                    getTermConstReferenceFromSharedPointer(termsWithDetails.front().baseTermSharedPointer),
                    number);
    }
    return result;
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
        for(auto const& variableExponentsPair
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
        result = term.getConstantValueConstReference().isAFiniteValue();
    }
    return result;
}

}

}
