#pragma once

#include <Algebra/Term/TermTypes/Polynomial.hpp>
#include <Common/Container/AlbaOptional.hpp>

#include <vector>

namespace alba
{

namespace algebra
{

class PolynomialOverPolynomial
{
public:
    struct QuotientAndRemainder
    {
        Polynomial quotient;
        Polynomial remainder;
    };

    PolynomialOverPolynomial();
    PolynomialOverPolynomial(Polynomial const& numerator, Polynomial const& denominator);

    bool isEmpty() const;
    Polynomial const& getNumerator() const;
    Polynomial const& getDenominator() const;

    void setAsShouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue(
            bool const shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue);

    void simplify();
    void simplifyWithoutFactorization();
    QuotientAndRemainder simplifyAndDivide();
    QuotientAndRemainder divide() const;

private:
    bool shouldPerformFactorization() const;
    void convertFractionCoefficientsToInteger();
    void convertNegativeExponentsToPositive();
    void removeCommonMonomialOnAllMonomialsInNumeratorAndDenominator();
    void factorizeRemoveCommonFactorsInNumeratorAndDenominatorAndCombineRemainingFactors();
    unsigned int getLcmForDenominatorCoefficients(Polynomial const& polynomial);
    Monomial getMonomialWithMaxNegativeExponentsAndConvertItToPositive(Polynomial const& polynomial);
    bool removeCommonFactorsAndReturnIfSomeFactorsAreRemoved(
            Polynomials & numeratorFactors,
            Polynomials & denominatorFactors) const;
    Polynomial multiplyAndSimplifyFactors(Polynomials const& factors) const;
    Polynomial m_numerator;
    Polynomial m_denominator;
    bool m_shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue;
};

using ListOfPolynomialOverPolynomial = std::vector<PolynomialOverPolynomial>;
using PolynomialOverPolynomialOptional = AlbaOptional<PolynomialOverPolynomial>;

}

}
