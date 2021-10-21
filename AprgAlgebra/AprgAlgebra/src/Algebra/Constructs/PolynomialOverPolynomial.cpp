#include "PolynomialOverPolynomial.hpp"

#include <Algebra/Factorization/Factorization.hpp>
#include <Algebra/Factorization/FactorizationUtilities.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/MonomialHelpers.hpp>
#include <Algebra/Term/Utilities/PolynomialHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Math/AlbaMathHelper.hpp>

#include <algorithm>

using namespace alba::mathHelper;
using namespace alba::algebra::Factorization;
using namespace std;

namespace alba
{

namespace algebra
{

PolynomialOverPolynomial::PolynomialOverPolynomial()
    : m_numerator()
    , m_denominator()
{}

PolynomialOverPolynomial::PolynomialOverPolynomial(
        Polynomial const& numerator,
        Polynomial const& denominator)
    : m_numerator(numerator)
    , m_denominator(denominator)
{}

bool PolynomialOverPolynomial::isEmpty() const
{
    return m_numerator.isEmpty() && m_denominator.isEmpty();
}

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
    return divide();
}

void PolynomialOverPolynomial::simplify()
{
    convertFractionCoefficientsToInteger();
    convertNegativeExponentsToPositive();
    removeCommonMonomialOnAllMonomialsInNumeratorAndDenominator();
    m_numerator.simplify();
    m_denominator.simplify();
    factorizeRemoveCommonFactorsInNumeratorAndDenominatorAndCombineRemainingFactors();
}

PolynomialOverPolynomial::QuotientAndRemainder PolynomialOverPolynomial::divide() const
{
    Polynomial currentQuotient;
    Polynomial currentRemainder(m_numerator);
    while(!isTheValue(currentRemainder, 0) && !isNotANumber(currentRemainder))
    {
        Monomial const& dividendMonomial(currentRemainder.getFirstMonomial());
        Monomial const& divisorMonomial(m_denominator.getFirstMonomial());
        Monomial currentQuotientMonomial(dividendMonomial);
        currentQuotientMonomial.divideMonomial(divisorMonomial);
        if(!hasNegativeExponents(currentQuotientMonomial))
        {
            currentQuotient.addMonomial(currentQuotientMonomial);
            Polynomial polynomialToSubtract(m_denominator);
            polynomialToSubtract.multiplyMonomial(currentQuotientMonomial);
            polynomialToSubtract.multiplyNumber(-1);
            currentRemainder.addPolynomial(polynomialToSubtract);
            currentQuotient.simplify();
            currentRemainder.simplify();
        }
        else
        {
            break;
        }
    }
    return QuotientAndRemainder{currentQuotient, currentRemainder};
}

bool PolynomialOverPolynomial::shouldPerformFactorization() const
{
    return !canBeConvertedToConstant(m_numerator) && !canBeConvertedToConstant(m_denominator);
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
    numeratorAndDenominatorMonomials.reserve(numeratorMonomials.size()+denominatorMonomials.size());
    copy(numeratorMonomials.cbegin(), numeratorMonomials.cend(), back_inserter(numeratorAndDenominatorMonomials));
    copy(denominatorMonomials.cbegin(), denominatorMonomials.cend(), back_inserter(numeratorAndDenominatorMonomials));
    Monomial gcfMonomial(getGcfMonomialInMonomials(numeratorAndDenominatorMonomials));
    if(!isTheValue(gcfMonomial, 0))
    {
        m_numerator.divideMonomial(gcfMonomial);
        m_denominator.divideMonomial(gcfMonomial);
        bool isDenominatorHasNegativeSign = getCommonSignInMonomials(m_denominator.getMonomialsConstReference()) == -1;
        if(isDenominatorHasNegativeSign)
        {            m_numerator.divideMonomial(createMonomialFromConstant(-1));
            m_denominator.divideMonomial(createMonomialFromConstant(-1));
        }
    }
}

void PolynomialOverPolynomial::factorizeRemoveCommonFactorsInNumeratorAndDenominatorAndCombineRemainingFactors(){
    if(shouldPerformFactorization())
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

Monomial PolynomialOverPolynomial::getMonomialWithMaxNegativeExponentsAndConvertItToPositive(Polynomial const& polynomial)
{
    Monomial resultMonomial(1, {});
    Monomial::VariablesToExponentsMap const& resultVariableMap(resultMonomial.getVariablesToExponentsMapConstReference());
    for(Monomial const& monomial : polynomial.getMonomialsConstReference())
    {
        for(auto const& variablePair : monomial.getVariablesToExponentsMapConstReference())
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

bool PolynomialOverPolynomial::removeCommonFactorsAndReturnIfSomeFactorsAreRemoved(
        Polynomials & numeratorFactors,
        Polynomials & denominatorFactors) const
{
    bool areSomeFactorsRemoved(false);
    for(Polynomials::iterator numeratorIterator = numeratorFactors.begin();
        !numeratorFactors.empty() && numeratorIterator != numeratorFactors.end();
        numeratorIterator++)
    {
        for(Polynomials::iterator denominatorIterator = denominatorFactors.begin();
            !numeratorFactors.empty() && !denominatorFactors.empty() && denominatorIterator != denominatorFactors.end();
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
                    if(numeratorFactors.begin() != numeratorIterator){numeratorIterator--;}
                    if(denominatorFactors.begin() != denominatorIterator){denominatorIterator--;}
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
