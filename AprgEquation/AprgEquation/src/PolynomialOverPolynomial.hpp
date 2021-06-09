#pragma once

#include <Polynomial.hpp>

namespace alba
{

namespace equation
{

class PolynomialOverPolynomial
{
public:
    PolynomialOverPolynomial(Polynomial const& numerator, Polynomial const& denominator);

    Polynomial const& getNumerator() const;
    Polynomial const& getDenominator() const;

    void simplify();

private:
    unsigned int getLcmForDenominatorCoefficients(Polynomial const& polynomial);
    unsigned int getGcfForIntegerCoefficients(Polynomial const& polynomial);
    Monomial getAndPositiveExponentsMonomialWithNegativeExponents(Polynomial const& polynomial);
    void convertFractionCoefficientsToInteger();
    void removeGcfOnCoefficients();
    void convertNegativeExponentsToPositive();
    void removeCommonVariableExponents();
    Monomial getMonomialCommonVariablesExponentsInPolynomial(Monomials const& monomials) const;
    Polynomial m_numerator;
    Polynomial m_denominator;
};
}

}