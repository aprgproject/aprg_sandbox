#pragma once

#include <Equation/Term/Polynomial.hpp>

namespace alba
{

namespace equation
{

namespace Factorization
{

Polynomials factorizeAPolynomial(Polynomial const& polynomial);
Polynomials factorizePolynomials(Polynomials const& polynomials);
Polynomials factorizeCommonMonomial(Polynomial const& polynomial);
Polynomials factorizeCommonMonomialIfPossible(Polynomial const& polynomial);
}

}

}
