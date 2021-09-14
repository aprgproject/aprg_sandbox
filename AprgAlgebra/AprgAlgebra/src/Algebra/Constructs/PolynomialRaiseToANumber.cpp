#include "PolynomialRaiseToANumber.hpp"

#include <Algebra/Factorization/FactorizationOfPolynomial.hpp>
#include <Math/AlbaMathHelper.hpp>

using namespace alba::algebra::Factorization;
using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace algebra
{

PolynomialRaiseToANumber::PolynomialRaiseToANumber(
        Polynomial const& polynomial)
    : m_base(polynomial)
    , m_exponent(1U)
{
    PolynomialToNumberMap factorsToExponent;
    Monomial commonMonomialInBase(1, {});
    factorizeAndUpdateCommonMonomialAndFactorsToExponent(polynomial, factorsToExponent, commonMonomialInBase);
    unsigned int gcfOfExponents(getGcfOfExponents(factorsToExponent));
    if(gcfOfExponents!=1)
    {
        m_base = getRemainingBase(factorsToExponent, commonMonomialInBase, gcfOfExponents);
        m_exponent = gcfOfExponents;
    }
}

bool PolynomialRaiseToANumber::isExponentOne() const
{
    return m_exponent == 1U;
}

Polynomial const& PolynomialRaiseToANumber::getBase() const
{
    return m_base;
}

unsigned int PolynomialRaiseToANumber::getExponent() const
{
    return m_exponent;
}

void PolynomialRaiseToANumber::factorizeAndUpdateCommonMonomialAndFactorsToExponent(
        Polynomial const& polynomial,
        PolynomialToNumberMap & factorsToExponent,
        Monomial & commonMonomialInBase)
{
    Polynomials factors(factorizeAPolynomial(polynomial));
    for(Polynomial const& factor : factors)
    {
        if(factor.isOneMonomial())
        {
            commonMonomialInBase.multiplyMonomial(factor.getFirstMonomial());
        }
        else
        {
            PolynomialToNumberMap::iterator it = factorsToExponent.find(factor);
            if(it == factorsToExponent.cend())
            {
                factorsToExponent.emplace(factor, 1);
            }
            else
            {
                (it->second)++;
            }
        }
    }
}

unsigned int PolynomialRaiseToANumber::getGcfOfExponents(
        PolynomialToNumberMap const& factorsToExponent)
{
    unsigned int result(1U);
    bool isFirst(true);
    for(auto const& factorsAndExponentPair : factorsToExponent)
    {
        if(isFirst)
        {
            result = factorsAndExponentPair.second;
            isFirst = false;
        }
        else
        {
            result = getGreatestCommonFactor(result, factorsAndExponentPair.second);
        }
    }
    return result;
}

Polynomial PolynomialRaiseToANumber::getRemainingBase(
        PolynomialToNumberMap const& factorsToExponent,
        Monomial const& commonMonomialInBase,
        unsigned int const gcfOfExponents)
{
    Monomial remainingCommonMonomial(commonMonomialInBase);
    remainingCommonMonomial.raiseToPowerNumber(AlbaNumber::createFraction(1, gcfOfExponents));
    Polynomial result{remainingCommonMonomial};
    for(auto const& factorsAndExponentPair : factorsToExponent)
    {
        unsigned int remainingExponent(factorsAndExponentPair.second/gcfOfExponents);
        Polynomial remainingFactor(factorsAndExponentPair.first);
        remainingFactor.raiseToUnsignedInteger(remainingExponent);
        result.multiplyPolynomial(remainingFactor);
    }
    return result;
}

}

}
