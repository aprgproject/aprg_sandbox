#pragma once

#include <Equation/Substitution/SubstitutionOfVariablesToExpressions.hpp>
#include <Equation/Term/Polynomial.hpp>

namespace alba
{

namespace equation
{

namespace Factorization
{

Polynomials factorizeBySplittingToSmallerPolynomials(Polynomial const& polynomial);
Polynomials factorizeIfPossibleBySplittingToSmallerPolynomials(Polynomial const& polynomial);
Polynomials factorizeIfPossibleBySplittingByPolynomialDegree(Polynomial const& polynomial);
Polynomials factorizeIfPossibleBySplittingByDivisibilityOfExponents(Polynomial const& polynomial);
Polynomials factorizeIfPossibleBySplittingByFirstVariable(Polynomial const& polynomial);
Polynomials splitPolynomialsByPolynomialDegree(Polynomial const& polynomial);
Polynomials splitPolynomialsByDivisibilityOfExponents(Polynomial const& polynomial);
Polynomials splitPolynomialsByFirstVariable(Polynomial const& polynomial);
Polynomials factorizeSmallerPolynomials(Polynomials const& smallerPolynomials);
Polynomials factorizeSmallerPolynomialsByFactoringOutCommonFactors(Polynomials const& smallerPolynomials);
Polynomials factorizeSmallerPolynomialsBySubstitutingCommonFactorsToVariables(Polynomials const& smallerPolynomials);
Polynomials factorizePolynomialWithVariables(
        Polynomial const& newPolynomialWithVariables,
        SubstitutionOfVariablesToExpressions const& variableSubstitution);
Polynomials getCommonFactorsInThesePolynomials(Polynomials const& smallerPolynomials);
Polynomial getNewPolynomialWithVariables(SubstitutionOfVariablesToExpressions & variableSubstitution, Polynomials const& smallerPolynomials);
Polynomials getPolynomialsWithRemovedCommonFactors(Polynomials const& polynomialsWithCommonFactors, Polynomials const& commonFactors);
void updateToGetSubsetOfFactors(Polynomials & commonFactors, Polynomials const& currentCommonFactors);
void combinePolynomialsByAdditionAndThenEmplaceBack(Polynomials & result, Polynomials const& smallerPolynomials);

}

}

}
