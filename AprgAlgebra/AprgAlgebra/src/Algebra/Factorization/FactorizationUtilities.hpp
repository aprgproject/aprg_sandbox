#pragma once

#include <Algebra/Term/TermTypes/Polynomial.hpp>

namespace alba
{

namespace algebra
{

namespace Factorization
{

bool areExponentsDivisible(Monomial const& monomial, unsigned int const divisor);
bool isPerfectSquare(Monomial const& monomial);
bool isPerfectCube(Monomial const& monomial);
bool isPerfectNthPower(Monomial const& monomial, unsigned int const nthPower);
bool doesNotNeedToBeFactorized(Polynomial const& polynomial);
bool doesContainOnlyConstants(Polynomials const& polynomials);
bool doesContainConstantsOrOnlyOneNonConstant(Polynomials const& polynomials);

void simplifyPolynomialThenEmplaceBackIfNotEmpty(Polynomials & polynomials, Polynomial const& polynomial);
void emplaceBackIfNotEmpty(Polynomials & polynomials, Polynomial const& polynomial);
Polynomials returnPolynomialsOrSinglePolynomialIfEmpty(
        Polynomials const& polynomials,
        Polynomial const& polynomial);
}

}

}
