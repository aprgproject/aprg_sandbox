#pragma once

#include <Algebra/Term/TermTypes/Polynomial.hpp>

#include <map>

namespace alba
{

namespace algebra
{

class PolynomialRaiseToANumber
{
public:
    using PolynomialToNumberMap = std::map<Polynomial, unsigned int>;

    PolynomialRaiseToANumber(Polynomial const& polynomial);

    bool isExponentOne() const;

    Polynomial const& getBase() const;
    unsigned int getExponent() const;

private:
    void factorizeAndUpdateCommonMonomialAndFactorsToExponent(
            Polynomial const& polynomial,
            PolynomialToNumberMap & factorsToExponent,
            Monomial & commonMonomialInBase);
    unsigned int getGcfOfExponents(
            PolynomialToNumberMap const& factorsToExponent);
    Polynomial getRemainingBase(
            PolynomialToNumberMap const& factorsToExponent,
            Monomial const& commonMonomialInBase,
            unsigned int const gcfOfExponents);
    Polynomial m_base;
    unsigned int m_exponent;
};


}

}
