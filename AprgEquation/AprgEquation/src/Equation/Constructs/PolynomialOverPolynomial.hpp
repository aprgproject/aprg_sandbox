#pragma once

#include <Equation/Term/Polynomial.hpp>

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
    QuotientAndRemainder divide() const;

private:
    unsigned int getLcmForDenominatorCoefficients(Polynomial const& polynomial);
    Monomial getMonomialWithMaxNegativeExponentsAndConvertItToPositive(Polynomial const& polynomial);
    void convertFractionCoefficientsToInteger();
    void convertNegativeExponentsToPositive();
    void removeCommonMonomialOnAllMonomialsInNumeratorAndDenominator();
    void factorizeAndRemoveCommonFactorsInNumeratorAndDenominator();
    bool removeCommonFactorsAndReturnIfSomeFactorsAreRemoved(
            Polynomials & numeratorFactors,
            Polynomials & denominatorFactors) const;
    Polynomial multiplyAndSimplifyFactors(Polynomials const& factors) const;
    Polynomial m_numerator;
    Polynomial m_denominator;
};

}

}
