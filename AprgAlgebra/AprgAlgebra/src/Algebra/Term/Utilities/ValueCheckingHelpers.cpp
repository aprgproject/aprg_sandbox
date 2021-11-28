#include "ValueCheckingHelpers.hpp"

#include <Algebra/Term/Utilities/BaseTermHelpers.hpp>
#include <Algebra/Term/Utilities/MonomialHelpers.hpp>
#include <Algebra/Term/Utilities/PolynomialHelpers.hpp>

#include <algorithm>

using namespace std;

namespace alba
{

namespace algebra
{

namespace
{

NumberCheckingCondition IsDoubleCondition = [](
        AlbaNumber const& numberToCheck) -> bool
{
    return numberToCheck.isDoubleType();
};

NumberCheckingCondition IsNotANumberCondition = [](
        AlbaNumber const& numberToCheck) -> bool
{
    return numberToCheck.isNotANumber();
};

NumberCheckingCondition IsNotARealFiniteNumberCondition = [](
        AlbaNumber const& numberToCheck) -> bool
{
    return !numberToCheck.isARealFiniteValue();
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
    return isConstantOnly(monomial)
            && isValueSatisfyTheCondition(monomial.getConstantConstReference(), condition);
}

bool isValueSatisfyTheCondition(
        Polynomial const& polynomial,
        NumberCheckingCondition const& condition)
{
    return isOneMonomial(polynomial)
            && isValueSatisfyTheCondition(getFirstMonomial(polynomial), condition);
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
        Monomial::VariablesToExponentsMap const& variableExponentMap(
                    monomial.getVariablesToExponentsMapConstReference());
        result = any_of(variableExponentMap.cbegin(), variableExponentMap.cend(), [&](auto const& variableExponentsPair)
        {
            return condition(variableExponentsPair.second);
        });
    }
    return result;
}

bool doAnyNumbersSatisfyTheCondition(
        Polynomial const& polynomial,
        NumberCheckingCondition const& condition)
{
    Monomials const& monomials(polynomial.getMonomialsConstReference());
    return any_of(monomials.cbegin(), monomials.cend(), [&](Monomial const& monomial)
    {
        return doAnyNumbersSatisfyTheCondition(monomial, condition);
    });
}

bool doAnyNumbersSatisfyTheCondition(
        Expression const& expression,
        NumberCheckingCondition const& condition)
{
    TermsWithDetails const& termsWithDetails(expression.getTermsWithAssociation().getTermsWithDetails());
    return any_of(termsWithDetails.cbegin(), termsWithDetails.cend(), [&](TermWithDetails const& termWithDetails)
    {
        return doAnyNumbersSatisfyTheCondition(
                    getTermConstReferenceFromSharedPointer(termWithDetails.baseTermSharedPointer),
                    condition);
    });
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
        result = isConstantOnly(monomial) && monomial.getConstantConstReference() == number;
    }
    return result;
}

bool isTheValue(Polynomial const& polynomial, AlbaNumber const& number)
{
    bool result(false);
    if(number == 0)
    {
        result = polynomial.isEmpty();
    }
    else
    {
        result = isOneMonomial(polynomial) && isTheValue(getFirstMonomial(polynomial), number);
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

bool isARealFiniteConstant(Term const& term)
{
    bool result(false);
    if(term.isConstant())
    {
        result = term.getConstantValueConstReference().isARealFiniteValue();
    }
    return result;
}

bool hasDoubleValues(Term const& term)
{
    return doAnyNumbersSatisfyTheCondition(term, IsDoubleCondition);
}

bool hasDoubleValues(Monomial const& monomial)
{
    return doAnyNumbersSatisfyTheCondition(monomial, IsDoubleCondition);
}

bool hasDoubleValues(Polynomial const& polynomial)
{
    return doAnyNumbersSatisfyTheCondition(polynomial, IsDoubleCondition);
}

bool hasDoubleValues(Expression const& expression)
{
    return doAnyNumbersSatisfyTheCondition(expression, IsDoubleCondition);
}

bool hasDoubleValues(Function const& function)
{
    return doAnyNumbersSatisfyTheCondition(function, IsDoubleCondition);
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

bool hasNonRealFiniteNumbers(Term const& term)
{
    return doAnyNumbersSatisfyTheCondition(term, IsNotARealFiniteNumberCondition);
}

bool hasNonRealFiniteNumbers(Monomial const& monomial)
{
    return doAnyNumbersSatisfyTheCondition(monomial, IsNotARealFiniteNumberCondition);
}

bool hasNonRealFiniteNumbers(Polynomial const& polynomial)
{
    return doAnyNumbersSatisfyTheCondition(polynomial, IsNotARealFiniteNumberCondition);
}

bool hasNonRealFiniteNumbers(Expression const& expression)
{
    return doAnyNumbersSatisfyTheCondition(expression, IsNotARealFiniteNumberCondition);
}

bool hasNonRealFiniteNumbers(Function const& function)
{
    return doAnyNumbersSatisfyTheCondition(function, IsNotARealFiniteNumberCondition);
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
