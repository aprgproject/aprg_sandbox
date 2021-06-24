#pragma once

#include <Equation/Term/Polynomial.hpp>

namespace alba
{

namespace equation
{

namespace Factorization
{

Polynomials factorizeBySplittingToSmallerPolynomials(Polynomial const& polynomial);
Polynomials factorizeIfPossibleBySplittingToSmallerPolynomials(Polynomial const& polynomial);
Polynomials factorizeIfPossibleBySplittingByFirstVariable(Polynomial const& polynomial);
Polynomials factorizeIfPossibleBySplittingByPolynomialDegree(Polynomial const& polynomial);
Polynomials factorizeSmallerPolynomials(Polynomials const& smallerPolynomials);
Polynomials factorizeSmallerPolynomialsByFactoringOutCommonFactors(Polynomials const& smallerPolynomials);
Polynomials factorizeSmallerPolynomialsBySubstitutingCommonFactorsToVariables(Polynomials const& smallerPolynomials);
Polynomials splitPolynomialsByFirstVariable(Polynomial const& polynomial);
Polynomials splitPolynomialsByPolynomialDegree(Polynomial const& polynomial);
Polynomials getCommonFactorsInThesePolynomials(Polynomials const& smallerPolynomials);
Polynomials getPolynomialsWithRemovedCommonFactors(Polynomials const& polynomialsWithCommonFactors, Polynomials const& commonFactors);
void combinePolynomialsByAdditionAndThenEmplaceBack(Polynomials & result, Polynomials const& smallerPolynomials);

}

}

}
