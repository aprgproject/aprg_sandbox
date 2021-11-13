#pragma once

#include <Algebra/Term/TermTypes/Polynomial.hpp>

namespace alba
{

namespace algebra
{

namespace Factorization
{

Polynomials factorizeAPolynomial(Polynomial const& polynomial);
Polynomials factorizePolynomials(Polynomials const& polynomials);
Polynomials factorizeCommonMonomial(Polynomial const& polynomial);
void factorizeCommonMonomialIfPossible(Polynomials & result, Polynomial const& polynomial);
void factorizePolynomialsAndPutToResult(Polynomials & result, Polynomials const& polynomials);
void putFactorizedPolynomialsIfPossible(Polynomials & result, Polynomials const& factorizedPolynomials);
void simplifyAndRemoveEmptyPolynomials(Polynomials & polynomials);

void tryToFactorizeCommonMonomial(
        Polynomials & polynomialsToFactorize,
        unsigned int & deltaSize,
        Polynomial const& simplifiedPolynomial,
        unsigned int const originalSize);
void tryToFactorizeUsingPatterns(
        Polynomials & polynomialsToFactorize,
        unsigned int & deltaSize,
        Polynomial const& simplifiedPolynomial,
        unsigned int const originalSize);
void tryToFactorizeIncreasingAndDecreasingExponentsForm(
        Polynomials & polynomialsToFactorize,
        unsigned int & deltaSize,
        Polynomial const& simplifiedPolynomial,
        unsigned int const originalSize);
void tryToFactorizeBySplittingToSmallerPolynomials(
        Polynomials & polynomialsToFactorize,
        unsigned int & deltaSize,
        Polynomial const& simplifiedPolynomial,
        unsigned int const originalSize);

unsigned int getDeltaSize(Polynomials const& polynomials, unsigned int const originalSize);

bool isFactorizeUsingPatternsNeeded(Polynomial const& polynomial);
bool isFactorizeIncreasingAndDecreasingExponentsFormNeeded(Polynomial const& polynomial);
bool isFactorizeBySplittingToSmallerPolynomialsNeeded(Polynomial const& polynomial);

}

}

}
