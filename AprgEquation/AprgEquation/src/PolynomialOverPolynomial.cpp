#include "PolynomialOverPolynomial.hpp"

#include <Math/AlbaMathHelper.hpp>

using namespace alba::mathHelper;
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

void PolynomialOverPolynomial::simplify()
{
    convertFractionCoefficientsToInteger();
    removeGcfOnCoefficients();
    convertNegativeExponentsToPositive();
    removeCommonVariableExponents();
    m_numerator.simplify();
    m_denominator.simplify();
}

unsigned int PolynomialOverPolynomial::getLcmForDenominatorCoefficients(Polynomial const& polynomial)
{
    unsigned int lcm(1);
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

unsigned int PolynomialOverPolynomial::getGcfForIntegerCoefficients(Polynomial const& polynomial)
{
    unsigned int gcf(1);
    bool isFirst(true);
    for(Monomial const& monomial : polynomial.getMonomialsConstReference())
    {
        AlbaNumber const& coefficient(monomial.getConstantConstReference());
        if(coefficient.isIntegerType())
        {
            unsigned int integerCoefficient(static_cast<unsigned int>(getAbsoluteValue(coefficient.getInteger())));
            if(isFirst)
            {
                gcf = integerCoefficient;
                isFirst = false;
            }
            else
            {
                gcf = getGreatestCommonFactor(gcf, integerCoefficient);
            }
        }
    }
    return gcf;
}

Monomial PolynomialOverPolynomial::getAndPositiveExponentsMonomialWithNegativeExponents(Polynomial const& polynomial)
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

void PolynomialOverPolynomial::removeGcfOnCoefficients()
{
    unsigned int numeratorGcf(getGcfForIntegerCoefficients(m_numerator));
    unsigned int denominatorGcf(getGcfForIntegerCoefficients(m_denominator));
    unsigned int commonGcfOnNumeratorAndDenominator(getGreatestCommonFactor(numeratorGcf, denominatorGcf));
    m_numerator.divideNumber(commonGcfOnNumeratorAndDenominator);
    m_denominator.divideNumber(commonGcfOnNumeratorAndDenominator);
}

void PolynomialOverPolynomial::convertNegativeExponentsToPositive()
{
    Monomial monomialExponentNumerator(getAndPositiveExponentsMonomialWithNegativeExponents(m_numerator));
    Monomial monomialExponentDenominator(getAndPositiveExponentsMonomialWithNegativeExponents(m_denominator));
    m_numerator.multiplyMonomial(monomialExponentNumerator);
    m_numerator.multiplyMonomial(monomialExponentDenominator);
    m_denominator.multiplyMonomial(monomialExponentNumerator);
    m_denominator.multiplyMonomial(monomialExponentDenominator);
}

void PolynomialOverPolynomial::removeCommonVariableExponents()
{
    Monomial commonMonomialInNumerator(getMonomialCommonVariablesExponentsInPolynomial(m_numerator.getMonomialsConstReference()));
    Monomial commonMonomialInDenominator(getMonomialCommonVariablesExponentsInPolynomial(m_denominator.getMonomialsConstReference()));
    Monomial commonMonomial(getMonomialCommonVariablesExponentsInPolynomial(Monomials{commonMonomialInNumerator, commonMonomialInDenominator}));

    m_numerator.divideMonomial(commonMonomial);
    m_denominator.divideMonomial(commonMonomial);
}

Monomial PolynomialOverPolynomial::getMonomialCommonVariablesExponentsInPolynomial(Monomials const& monomials) const
{
    Monomial intersectionMonomial(1, {});
    bool isFirst(true);
    for(Monomial const& monomial : monomials)
    {
        if(isFirst)
        {
            intersectionMonomial = monomial;
            isFirst=false;
        }
        else
        {
            intersectionMonomial.saveIntersectionOfVariableExponentsMap(monomial);
        }
    }
    return intersectionMonomial;
}



}

}
