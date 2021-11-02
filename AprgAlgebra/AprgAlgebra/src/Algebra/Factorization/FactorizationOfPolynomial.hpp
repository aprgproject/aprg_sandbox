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
Polynomials factorizeCommonMonomialIfPossible(Polynomial const& polynomial);
void factorizeAPolynomialAndPutToResult(Polynomials & result, Polynomial const& polynomial);
void putFactorizedPolynomialsIfPossible(Polynomials & result, Polynomials const& factorizedPolynomials);
void simplifyAndRemoveEmptyPolynomials(Polynomials & polynomials);
}

}

}
