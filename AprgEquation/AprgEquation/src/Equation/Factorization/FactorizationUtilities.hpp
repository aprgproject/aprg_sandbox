#pragma once

#include <Equation/Term/Polynomial.hpp>

namespace alba
{

namespace equation
{

namespace Factorization
{

Polynomials factorizePolynomials(Polynomials const& polynomials);
Polynomials returnPolynomialsOrSinglePolynomialIfEmpty(
        Polynomials const& polynomials,
        Polynomial const& polynomial);
Polynomials factorizeCommonMonomial(Polynomial const& polynomial);
Polynomials factorizeCommonMonomialIfPossible(Polynomial const& polynomial);
bool isPerfectSquare(Monomial const& monomial);
bool isPerfectCube(Monomial const& monomial);
bool isPerfectNthPower(Monomial const& monomial, unsigned int const nthPower);
bool areExponentsDivisible(Monomial const& monomial, unsigned int const divisor);
void simplifyPolynomialThenEmplaceBack(Polynomials & polynomials, Polynomial const& polynomial);

}

}

}
