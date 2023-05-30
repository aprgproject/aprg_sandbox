#include "PolynomialRaiseToAnUnsignedInt.hpp"

#include <Algebra/Factorization/FactorizationOfPolynomial.hpp>
#include <Algebra/Term/Utilities/PolynomialHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>
#include <Common/Math/Helpers/FactorAndMulitplesHelpers.hpp>

using namespace alba::algebra::Factorization;
using namespace alba::mathHelper;
using namespace std;

namespace alba {

namespace algebra {

PolynomialRaiseToAnUnsignedInt::PolynomialRaiseToAnUnsignedInt(Polynomial const& polynomial)
    : m_base(polynomial), m_exponent(1) {
    PolynomialToNumberMap factorsToExponent;
    Monomial commonMonomialInBase(1, {});
    factorizeAndUpdateCommonMonomialAndFactorsToExponent(polynomial, factorsToExponent, commonMonomialInBase);
    int gcfOfExponents(getGcfOfExponents(factorsToExponent));
    if (canBeSimplified(gcfOfExponents, commonMonomialInBase)) {
        m_base = getRemainingBase(factorsToExponent, commonMonomialInBase, gcfOfExponents);
        m_exponent = gcfOfExponents;
    }
}

bool PolynomialRaiseToAnUnsignedInt::isExponentOne() const { return m_exponent == 1; }

Polynomial const& PolynomialRaiseToAnUnsignedInt::getBase() const { return m_base; }

int PolynomialRaiseToAnUnsignedInt::getExponent() const { return m_exponent; }

bool PolynomialRaiseToAnUnsignedInt::canBeSimplified(
    int const gcfOfExponents, Monomial const& commonMonomialInBase) {
    return gcfOfExponents != 1 &&
           (!isEven(gcfOfExponents) || (isEven(gcfOfExponents) && !isANegativeMonomial(commonMonomialInBase)));
}

void PolynomialRaiseToAnUnsignedInt::factorizeAndUpdateCommonMonomialAndFactorsToExponent(
    Polynomial const& polynomial, PolynomialToNumberMap& factorsToExponent, Monomial& commonMonomialInBase) {
    Polynomials factors(factorizeAPolynomial(polynomial));
    for (Polynomial const& factor : factors) {
        if (isOneMonomial(factor)) {
            commonMonomialInBase.multiplyMonomial(getFirstMonomial(factor));
        } else {
            PolynomialToNumberMap::iterator it = factorsToExponent.find(factor);
            if (it == factorsToExponent.cend()) {
                factorsToExponent.emplace(factor, 1);
            } else {
                (it->second)++;
            }
        }
    }
}

int PolynomialRaiseToAnUnsignedInt::getGcfOfExponents(PolynomialToNumberMap const& factorsToExponent) {
    int result(1);
    if (!factorsToExponent.empty()) {
        auto it = factorsToExponent.cbegin();
        result = it->second;
        it++;
        for (; it != factorsToExponent.cend(); it++) {
            result = getGreatestCommonFactor(result, it->second);
        }
    }
    return result;
}

Polynomial PolynomialRaiseToAnUnsignedInt::getRemainingBase(
    PolynomialToNumberMap const& factorsToExponent, Monomial const& commonMonomialInBase,
    int const gcfOfExponents) {
    Monomial remainingCommonMonomial(commonMonomialInBase);
    remainingCommonMonomial.raiseToPowerNumber(AlbaNumber::createFraction(1, gcfOfExponents));
    Polynomial result{remainingCommonMonomial};
    for (auto const& factorsAndExponentPair : factorsToExponent) {
        int remainingExponent(factorsAndExponentPair.second / gcfOfExponents);
        Polynomial remainingFactor(factorsAndExponentPair.first);
        remainingFactor.raiseToUnsignedInteger(remainingExponent);
        result.multiplyPolynomial(remainingFactor);
    }
    return result;
}

}  // namespace algebra

}  // namespace alba
