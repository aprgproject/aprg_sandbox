#include "ValueCheckingHelpers.hpp"

#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>

#include <algorithm>

using namespace std;

namespace alba
{

namespace algebra
{

namespace
{

NumberCheckingCondition IsNotANumberCondition = [](
        AlbaNumber const& numberToCheck) -> bool
{
    return numberToCheck.isNotANumber();
};

NumberCheckingCondition IsNotAFiniteNumberCondition = [](
        AlbaNumber const& numberToCheck) -> bool
{
    return !numberToCheck.isAFiniteValue();
};

NumberCheckingCondition IsPositiveOrNegativeInfinityCondition = [](
        AlbaNumber const& numberToCheck) -> bool
{
    return numberToCheck.isPositiveOrNegativeInfinity();
};

}

bool isValueSatisfyTheCondition(
        Term const& term,
        NumberCheckingCondition const& condition)
{
    bool result(false);
    if(term.isConstant())
    {
        result = isValueSatisfyTheCondition(term.getConstantConstReference(), condition);
    }
    else if(term.isMonomial())
    {
        result = isValueSatisfyTheCondition(term.getMonomialConstReference(), condition);
    }
    else if(term.isPolynomial())
    {
        result = isValueSatisfyTheCondition(term.getPolynomialConstReference(), condition);
    }
    else if(term.isExpression())
    {
        result = isValueSatisfyTheCondition(term.getExpressionConstReference(), condition);
    }
    return result;
}

bool isValueSatisfyTheCondition(
        Constant const& constant,
        NumberCheckingCondition const& condition)
{
    return condition(constant.getNumberConstReference());
}

bool isValueSatisfyTheCondition(
        Monomial const& monomial,
        NumberCheckingCondition const& condition)
{
    return monomial.isConstantOnly()
            && isValueSatisfyTheCondition(monomial.getConstantConstReference(), condition);
}

bool isValueSatisfyTheCondition(
        Polynomial const& polynomial,
        NumberCheckingCondition const& condition)
{
    return polynomial.isOneMonomial()
            && isValueSatisfyTheCondition(polynomial.getFirstMonomial(), condition);
}

bool isValueSatisfyTheCondition(
        Expression const& expression,
        NumberCheckingCondition const& condition)
{
    bool result(false);
    TermsWithDetails const& termsWithDetails(expression.getTermsWithAssociation().getTermsWithDetails());
    if(termsWithDetails.size() == 1)
    {
        result = isValueSatisfyTheCondition(
                    getTermConstReferenceFromSharedPointer(termsWithDetails.front().baseTermSharedPointer),
                    condition);
    }
    return result;
}

bool doAnyNumbersSatisfyTheCondition(
        Term const& term,
        NumberCheckingCondition const& condition)
{
    bool result(false);
    if(term.isConstant())
    {
        result = condition(term.getConstantValueConstReference());
    }
    else if(term.isMonomial())
    {
        result = doAnyNumbersSatisfyTheCondition(term.getMonomialConstReference(), condition);
    }
    else if(term.isPolynomial())
    {
        result = doAnyNumbersSatisfyTheCondition(term.getPolynomialConstReference(), condition);
    }
    else if(term.isExpression())
    {
        result = doAnyNumbersSatisfyTheCondition(term.getExpressionConstReference(), condition);
    }
    else if(term.isFunction())
    {
        result = doAnyNumbersSatisfyTheCondition(term.getFunctionConstReference(), condition);
    }
    return result;
}

bool doAnyNumbersSatisfyTheCondition(
        Monomial const& monomial,
        NumberCheckingCondition const& condition)
{
    bool result(condition(monomial.getConstantConstReference()));
    if(!result)
    {
        for(auto const& variableExponentsPair
            : monomial.getVariablesToExponentsMapConstReference())
        {
            result |= condition(variableExponentsPair.second);
            if(result)
            {
                break;
            }
        }
    }
    return result;
}

bool doAnyNumbersSatisfyTheCondition(
        Polynomial const& polynomial,
        NumberCheckingCondition const& condition)
{
    bool result(false);
    for(Monomial const& monomial : polynomial.getMonomialsConstReference())
    {
        result |= doAnyNumbersSatisfyTheCondition(monomial, condition);
        if(result)
        {
            break;
        }
    }
    return result;
}

bool doAnyNumbersSatisfyTheCondition(
        Expression const& expression,
        NumberCheckingCondition const& condition)
{
    bool result(false);
    TermsWithDetails const& termsWithDetails(expression.getTermsWithAssociation().getTermsWithDetails());
    for(TermWithDetails const& termWithDetails : termsWithDetails)
    {
        result |= doAnyNumbersSatisfyTheCondition(
                    getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer),
                    condition);
        if(result)
        {
            break;
        }
    }
    return result;
}

bool doAnyNumbersSatisfyTheCondition(
        Function const& function,
        NumberCheckingCondition const& condition)
{
    return doAnyNumbersSatisfyTheCondition(function.getInputTermConstReference(), condition);
}

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
    return isValueSatisfyTheCondition(term, IsNotANumberCondition);
}

bool isNotANumber(Constant const& constant)
{
    return isValueSatisfyTheCondition(constant, IsNotANumberCondition);
}

bool isNotANumber(Monomial const& monomial)
{
    return isValueSatisfyTheCondition(monomial, IsNotANumberCondition);
}

bool isNotANumber(Polynomial const& polynomial)
{
    return isValueSatisfyTheCondition(polynomial, IsNotANumberCondition);
}

bool isNotANumber(Expression const& expression)
{
    return isValueSatisfyTheCondition(expression, IsNotANumberCondition);
}

bool isPositiveOrNegativeInfinity(Term const& term)
{
    return isValueSatisfyTheCondition(term, IsPositiveOrNegativeInfinityCondition);
}

bool isPositiveOrNegativeInfinity(Constant const& constant)
{
    return isValueSatisfyTheCondition(constant, IsPositiveOrNegativeInfinityCondition);
}

bool isPositiveOrNegativeInfinity(Monomial const& monomial)
{
    return isValueSatisfyTheCondition(monomial, IsPositiveOrNegativeInfinityCondition);
}

bool isPositiveOrNegativeInfinity(Polynomial const& polynomial)
{
    return isValueSatisfyTheCondition(polynomial, IsPositiveOrNegativeInfinityCondition);
}

bool isPositiveOrNegativeInfinity(Expression const& expression)
{
    return isValueSatisfyTheCondition(expression, IsPositiveOrNegativeInfinityCondition);
}

bool isANegativeTerm(Term const& term)
{
    bool result(false);
    if(term.isConstant())
    {
        result = isANegativeConstant(term.getConstantConstReference());
    }
    else if(term.isMonomial())
    {
        result = isANegativeMonomial(term.getMonomialConstReference());
    }
    else if(term.isPolynomial())
    {
        result = isANegativePolynomial(term.getPolynomialConstReference());
    }
    else if(term.isExpression())
    {
        result = isANegativeExpression(term.getExpressionConstReference());
    }
    return result;
}

bool isANegativeConstant(Constant const& constant)
{
    return constant.getNumberConstReference() < 0;
}

bool isANegativeMonomial(Monomial const& monomial)
{
    return monomial.getConstantConstReference() < 0;
}

bool isANegativePolynomial(Polynomial const& polynomial)
{
    bool result(false);
    Monomials const& monomials(polynomial.getMonomialsConstReference());
    if(!monomials.empty())
    {
        result = monomials.front().getConstantConstReference() < 0;
    }
    return result;
}

bool isANegativeExpression(Expression const& expression)
{
    bool result(false);
    TermsWithDetails termsWithDetails(expression.getTermsWithAssociation().getTermsWithDetails());
    if(OperatorLevel::AdditionAndSubtraction == expression.getCommonOperatorLevel())
    {
        if(!termsWithDetails.empty())
        {
            Term const& firstTerm(getTermConstReferenceFromSharedPointer(termsWithDetails.front().baseTermSharedPointer));
            result = isANegativeTerm(firstTerm);
        }
    }
    else if(OperatorLevel::MultiplicationAndDivision == expression.getCommonOperatorLevel())
    {
        bool isNegative(false);
        for(TermWithDetails const& termWithDetails : termsWithDetails)
        {
            Term const& term(getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer));
            isNegative = isNegative ^ isANegativeTerm(term);
        }
        result = isNegative;
    }
    else if(OperatorLevel::RaiseToPower == expression.getCommonOperatorLevel())
    {
        result = false;
    }
    return result;
}

bool isIntegerConstant(Term const& term)
{
    return term.isConstant()
            && term.getConstantValueConstReference().isIntegerType();
}

bool isPositiveIntegerConstant(Term const& term)
{
    return term.isConstant()
            && term.getConstantValueConstReference().isIntegerType()
            && term.getConstantValueConstReference() >= 0;
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

bool hasNotANumber(Term const& term)
{
    return doAnyNumbersSatisfyTheCondition(term, IsNotANumberCondition);
}

bool hasNotANumber(Monomial const& monomial)
{
    return doAnyNumbersSatisfyTheCondition(monomial, IsNotANumberCondition);
}

bool hasNotANumber(Polynomial const& polynomial)
{
    return doAnyNumbersSatisfyTheCondition(polynomial, IsNotANumberCondition);
}

bool hasNotANumber(Expression const& expression)
{
    return doAnyNumbersSatisfyTheCondition(expression, IsNotANumberCondition);
}

bool hasNotANumber(Function const& function)
{
    return doAnyNumbersSatisfyTheCondition(function, IsNotANumberCondition);
}

bool hasNonFiniteNumbers(Term const& term)
{
    return doAnyNumbersSatisfyTheCondition(term, IsNotAFiniteNumberCondition);
}

bool hasNonFiniteNumbers(Monomial const& monomial)
{
    return doAnyNumbersSatisfyTheCondition(monomial, IsNotAFiniteNumberCondition);
}

bool hasNonFiniteNumbers(Polynomial const& polynomial)
{
    return doAnyNumbersSatisfyTheCondition(polynomial, IsNotAFiniteNumberCondition);
}

bool hasNonFiniteNumbers(Expression const& expression)
{
    return doAnyNumbersSatisfyTheCondition(expression, IsNotAFiniteNumberCondition);
}

bool hasNonFiniteNumbers(Function const& function)
{
    return doAnyNumbersSatisfyTheCondition(function, IsNotAFiniteNumberCondition);
}

bool hasZero(Terms const& terms)
{
    Terms::const_iterator it=find_if(terms.cbegin(), terms.cend(), [](Term const& term)
    {
        return isTheValue(term, 0);
    });
    return it != terms.cend();
}

bool hasNegativeExponentsWithVariable(
        Polynomial const& polynomial,
        string const& variableName)
{
    bool result(false);
    for(Monomial const& monomial : polynomial.getMonomialsConstReference())
    {
        result = result
                || (monomial.getExponentForVariable(variableName) < 0);
        if(result)
        {
            break;
        }
    }
    return result;
}

}

}
