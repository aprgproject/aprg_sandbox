#include "PolynomialRaiseToAnUnsignedInt.hpp"

#include <Algebra/Factorization/FactorizationOfPolynomial.hpp>
#include <Algebra/Term/Utilities/PolynomialHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Common/Math/AlbaMathHelper.hpp>

using namespace alba::algebra::Factorization;
using namespace alba::mathHelper;using namespace std;

namespace alba
{
namespace algebra
{

PolynomialRaiseToAnUnsignedInt::PolynomialRaiseToAnUnsignedInt(
        Polynomial const& polynomial)
    : m_base(polynomial)
    , m_exponent(1U)
{
    PolynomialToNumberMap factorsToExponent;
    Monomial commonMonomialInBase(1, {});
    factorizeAndUpdateCommonMonomialAndFactorsToExponent(polynomial, factorsToExponent, commonMonomialInBase);
    unsigned int gcfOfExponents(getGcfOfExponents(factorsToExponent));
    if(canBeSimplified(gcfOfExponents, commonMonomialInBase))
    {
        m_base = getRemainingBase(factorsToExponent, commonMonomialInBase, gcfOfExponents);
        m_exponent = gcfOfExponents;
    }
}

bool PolynomialRaiseToAnUnsignedInt::isExponentOne() const
{
    return m_exponent == 1U;
}

Polynomial const& PolynomialRaiseToAnUnsignedInt::getBase() const
{
    return m_base;
}

unsigned int PolynomialRaiseToAnUnsignedInt::getExponent() const
{
    return m_exponent;
}

bool PolynomialRaiseToAnUnsignedInt::canBeSimplified(
        unsigned int const gcfOfExponents,
        Monomial const& commonMonomialInBase)
{
    return gcfOfExponents != 1
            && (!isEven(gcfOfExponents)
                || (isEven(gcfOfExponents) && !isANegativeMonomial(commonMonomialInBase)));
}

void PolynomialRaiseToAnUnsignedInt::factorizeAndUpdateCommonMonomialAndFactorsToExponent(
        Polynomial const& polynomial,
        PolynomialToNumberMap & factorsToExponent,
        Monomial & commonMonomialInBase)
{
    Polynomials factors(factorizeAPolynomial(polynomial));
    for(Polynomial const& factor : factors)
    {
        if(isOneMonomial(factor))
        {
            commonMonomialInBase.multiplyMonomial(getFirstMonomial(factor));
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

unsigned int PolynomialRaiseToAnUnsignedInt::getGcfOfExponents(
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

Polynomial PolynomialRaiseToAnUnsignedInt::getRemainingBase(
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
