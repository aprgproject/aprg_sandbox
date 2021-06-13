#pragma once

#include <Polynomial.hpp>

namespace alba
{

namespace equation
{

namespace Factorization
{

Polynomials factorize(Polynomial const& polynomial);
Polynomials factorizeForPolynomials(Polynomials const& polynomials);
Polynomials factorizeCommonMonomial(Polynomial const& polynomial);
Polynomials factorizeDifferenceOfSquares(Polynomial const& polynomial);
bool isDifferenceOfSquares(Polynomial const& polynomial);
bool isPerfectSquare(Monomial const& monomial);
bool isPerfectCube(Monomial const& monomial);
void simplifyPolynomialThenEmplaceBack(Polynomials & polynomials, Polynomial const& polynomial);

}

}

}
