#include "PolynomialOverPolynomial.hpp"

#include <Factorization.hpp>
#include <Math/AlbaMathHelper.hpp>
#include <Utilities.hpp>

using namespace alba::mathHelper;
using namespace alba::equation::Factorization;
using namespace std;

namespace alba
{

namespace equation
{

PolynomialOverPolynomial::PolynomialOverPolynomial(
        Polynomial const& numerator,
        Polynomial const& denominator)
    : m_numerator(numerator)
    , m_denominator(denominator)
{}

Polynomial const& PolynomialOverPolynomial::getNumerator() const
{
    return m_numerator;
}

Polynomial const& PolynomialOverPolynomial::getDenominator() const
{
    return m_denominator;
}

PolynomialOverPolynomial::QuotientAndRemainder PolynomialOverPolynomial::simplifyAndDivide()
{
    simplify();
    sortNumeratorAndDenominator();
    return divide();
}

void PolynomialOverPolynomial::simplify()
{
    convertFractionCoefficientsToInteger();
    convertNegativeExponentsToPositive();
    removeCommonMonomialOnAllMonomialsInNumeratorAndDenominator();
    m_numerator.simplify();
    m_denominator.simplify();
    factorizeAndRemoveCommonFactorsInNumeratorAndDenominator();
}

void PolynomialOverPolynomial::sortNumeratorAndDenominator()
{
    m_numerator.sortMonomialsWithInversePriority();
    m_denominator.sortMonomialsWithInversePriority();
}

PolynomialOverPolynomial::QuotientAndRemainder PolynomialOverPolynomial::divide() const
{
    Polynomial currentQuotient;
    Polynomial currentRemainder(m_numerator);
    while(!currentRemainder.isZero())
    {
        Monomial const& dividendMonomial(currentRemainder.getFirstMonomial());
        Monomial const& divisorMonomial(m_denominator.getFirstMonomial());
        Monomial currentQuotientMonomial(dividendMonomial);
        currentQuotientMonomial.divideMonomial(divisorMonomial);
        if(currentQuotientMonomial.hasNegativeExponents())
        {
            break;
        }
        else
        {
            currentQuotient.addMonomial(currentQuotientMonomial);
            Polynomial polynomialToSubtract(m_denominator);
            polynomialToSubtract.multiplyMonomial(currentQuotientMonomial);
            polynomialToSubtract.multiplyNumber(-1);
            currentRemainder.addPolynomial(polynomialToSubtract);
            currentQuotient.simplify();
            currentRemainder.simplify();
        }
    }
    return QuotientAndRemainder{currentQuotient, currentRemainder};}

unsigned int PolynomialOverPolynomial::getLcmForDenominatorCoefficients(Polynomial const& polynomial)
{    unsigned int lcm(1);
    for(Monomial const& monomial : polynomial.getMonomialsConstReference())
    {
        AlbaNumber const& coefficient(monomial.getConstantConstReference());
        if(coefficient.isFractionType())
        {
            AlbaNumber::FractionData fractionData(coefficient.getFractionData());
            lcm = getLeastCommonMultiple(lcm, fractionData.denominator);
        }
    }
    return lcm;
}

Monomial PolynomialOverPolynomial::getMonomialWithMaxNegativeExponentsAndConvertItToPositive(Polynomial const& polynomial)
{
    Monomial resultMonomial(1, {});
    Monomial::VariablesToExponentsMap const& resultVariableMap(resultMonomial.getVariablesToExponentsMapConstReference());
    for(Monomial const& monomial : polynomial.getMonomialsConstReference())
    {
        for(Monomial::VariableExponentPair const& variablePair : monomial.getVariablesToExponentsMapConstReference())
        {
            if(variablePair.second < 0)
            {
                AlbaNumber existingExponent;
                if(resultVariableMap.find(variablePair.first) != resultVariableMap.end())
                {
                    existingExponent = resultVariableMap.at(variablePair.first);
                }
                AlbaNumber newPositiveExponent(variablePair.second*-1);
                if(newPositiveExponent > existingExponent)
                {
                    resultMonomial.putVariableWithExponent(variablePair.first, newPositiveExponent);
                }
            }
        }
    }
    return resultMonomial;
}

void PolynomialOverPolynomial::convertFractionCoefficientsToInteger()
{
    unsigned int numeratorMultiplier(getLcmForDenominatorCoefficients(m_numerator));
    m_numerator.multiplyNumber(numeratorMultiplier);
    m_denominator.multiplyNumber(numeratorMultiplier);
    unsigned int denominatorMultiplier(getLcmForDenominatorCoefficients(m_denominator));
    m_numerator.multiplyNumber(denominatorMultiplier);
    m_denominator.multiplyNumber(denominatorMultiplier);
}

void PolynomialOverPolynomial::convertNegativeExponentsToPositive()
{
    Monomial monomialExponentNumerator(getMonomialWithMaxNegativeExponentsAndConvertItToPositive(m_numerator));
    Monomial monomialExponentDenominator(getMonomialWithMaxNegativeExponentsAndConvertItToPositive(m_denominator));
    m_numerator.multiplyMonomial(monomialExponentNumerator);
    m_numerator.multiplyMonomial(monomialExponentDenominator);
    m_denominator.multiplyMonomial(monomialExponentNumerator);
    m_denominator.multiplyMonomial(monomialExponentDenominator);
}

void PolynomialOverPolynomial::removeCommonMonomialOnAllMonomialsInNumeratorAndDenominator()
{
    Monomials numeratorAndDenominatorMonomials;
    Monomials const& numeratorMonomials(m_numerator.getMonomialsConstReference());
    Monomials const& denominatorMonomials(m_denominator.getMonomialsConstReference());
    copy(numeratorMonomials.cbegin(), numeratorMonomials.cend(), back_inserter(numeratorAndDenominatorMonomials));
    copy(denominatorMonomials.cbegin(), denominatorMonomials.cend(), back_inserter(numeratorAndDenominatorMonomials));
    Monomial gcfMonomial(getGcfMonomialInMonomials(numeratorAndDenominatorMonomials));
    m_numerator.divideMonomial(gcfMonomial);
    m_denominator.divideMonomial(gcfMonomial);
    //bool isNumeratorHasNegativeSign = getCommonSignInMonomials(m_numerator.getMonomialsConstReference()) == -1;
    bool isDenominatorHasNegativeSign = getCommonSignInMonomials(m_denominator.getMonomialsConstReference()) == -1;
    if(isDenominatorHasNegativeSign)
    {
        m_numerator.divideMonomial(createMonomialFromConstant(-1));
        m_denominator.divideMonomial(createMonomialFromConstant(-1));
    }

}

void PolynomialOverPolynomial::factorizeAndRemoveCommonFactorsInNumeratorAndDenominator()
{
    Polynomials numeratorFactors(factorize(m_numerator));
    Polynomials denominatorFactors(factorize(m_denominator));

    bool areSomeFactorsRemoved(removeCommonFactorsAndReturnIfSomeFactorsAreRemoved(numeratorFactors, denominatorFactors));
    if(areSomeFactorsRemoved)
    {
        m_numerator = multiplyAndSimplifyFactors(numeratorFactors);
        m_denominator = multiplyAndSimplifyFactors(denominatorFactors);
    }
}

bool PolynomialOverPolynomial::removeCommonFactorsAndReturnIfSomeFactorsAreRemoved(
        Polynomials & numeratorFactors,
        Polynomials & denominatorFactors) const
{
    bool areSomeFactorsRemoved(false);
    for(Polynomials::iterator numeratorIterator = numeratorFactors.begin();
        numeratorIterator != numeratorFactors.end();
        numeratorIterator++)
    {
        for(Polynomials::iterator denominatorIterator = denominatorFactors.begin();
            denominatorIterator != denominatorFactors.end();
            denominatorIterator++)
        {
            Polynomial const& numerator(*numeratorIterator);
            Polynomial const& denominator(*denominatorIterator);
            if(!(numerator.isOneMonomial() && denominator.isOneMonomial()))
            {
                if(numerator == denominator)
                {
                    numeratorFactors.erase(numeratorIterator);
                    denominatorFactors.erase(denominatorIterator);
                    numeratorIterator--;
                    denominatorIterator--;
                    areSomeFactorsRemoved = true;
                }
            }
        }
    }
    return areSomeFactorsRemoved;
}

Polynomial PolynomialOverPolynomial::multiplyAndSimplifyFactors(Polynomials const& factors) const
{
    Polynomial product{Monomial(1, {})};
    for(Polynomial const& factor : factors)
    {
        product.multiplyPolynomial(factor);
    }
    product.simplify();
    return product;
}

}

}
