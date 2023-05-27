#pragma once

#include <Algebra/Term/TermTypes/Polynomial.hpp>

namespace alba {

namespace algebra {

namespace Factorization {

bool areExponentsDivisible(Monomial const& monomial, int const divisor);
bool isPerfectSquare(Monomial const& monomial);
bool isPerfectCube(Monomial const& monomial);
bool isPerfectNthPower(Monomial const& monomial, int const nthPower);
bool doesNotNeedToBeFactorized(Polynomial const& polynomial);
bool doesContainOnlyConstants(Polynomials const& polynomials);
bool IsEmptyOrContainConstantsOrOneNonConstant(Polynomials const& polynomials);
void simplifyThenEmplaceBackIfPolynomialIsNotEmpty(Polynomials& polynomials, Polynomial const& polynomial);
void emplaceBackIfPolynomialIsNotEmpty(Polynomials& polynomials, Polynomial const& polynomial);
void simplifyAndEmplaceBackPolynomialIfListIsEmpty(Polynomials& existingPolynomials, Polynomial const& polynomial);

}  // namespace Factorization

}  // namespace algebra

}  // namespace alba
