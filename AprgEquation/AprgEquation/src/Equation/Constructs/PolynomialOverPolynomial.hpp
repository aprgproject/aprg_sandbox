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
    QuotientAndRemainder divide() const;

private:
    void convertFractionCoefficientsToInteger();
    void convertNegativeExponentsToPositive();
    void removeCommonMonomialOnAllMonomialsInNumeratorAndDenominator();
    void factorizeRemoveCommonFactorsInNumeratorAndDenominatorAndCombineRemainingFactors();
    unsigned int getLcmForDenominatorCoefficients(Polynomial const& polynomial);
    Monomial getMonomialWithMaxNegativeExponentsAndConvertItToPositive(Polynomial const& polynomial);
    bool removeCommonFactorsAndReturnIfSomeFactorsAreRemoved(            Polynomials & numeratorFactors,
            Polynomials & denominatorFactors) const;    Polynomial multiplyAndSimplifyFactors(Polynomials const& factors) const;
    Polynomial m_numerator;
    Polynomial m_denominator;};
}

}
