#pragma once

#include <Algebra/Term/Polynomial.hpp>

namespace alba
{

namespace algebra
{

namespace Factorization
{

bool isPerfectSquare(Monomial const& monomial);
bool isPerfectCube(Monomial const& monomial);
bool isPerfectNthPower(Monomial const& monomial, unsigned int const nthPower);
bool areExponentsDivisible(Monomial const& monomial, unsigned int const divisor);
void simplifyPolynomialThenEmplaceBackIfNotEmpty(Polynomials & polynomials, Polynomial const& polynomial);
void emplaceBackIfNotEmpty(Polynomials & polynomials, Polynomial const& polynomial);
Polynomials returnPolynomialsOrSinglePolynomialIfEmpty(
        Polynomials const& polynomials,
        Polynomial const& polynomial);

}

}

}
