#pragma once

#include <Polynomial.hpp>

namespace alba
{

namespace equation
{

class PolynomialOverPolynomial
{
public:
    struct QuotientAndRemainder
    {
        Polynomial quotient;
        Polynomial remainder;
    };

    PolynomialOverPolynomial(Polynomial const& numerator, Polynomial const& denominator);

    Polynomial const& getNumerator() const;
    Polynomial const& getDenominator() const;

    QuotientAndRemainder simplifyAndDivide();
    void simplify();
    void sortNumeratorAndDenominator();

private:
    QuotientAndRemainder divide() const;
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
