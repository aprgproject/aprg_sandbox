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
}

}

}
