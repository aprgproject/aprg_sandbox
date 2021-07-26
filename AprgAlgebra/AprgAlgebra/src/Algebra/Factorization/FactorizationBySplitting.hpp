#pragma once

#include <Algebra/Substitution/SubstitutionOfVariablesToExpressions.hpp>
#include <Algebra/Term/TermTypes/Polynomial.hpp>

namespace alba
{

namespace algebra
{

namespace Factorization
{

Polynomials factorizeBySplittingToSmallerPolynomials(Polynomial const& polynomial);
Polynomials factorizeBySplittingToSmallerPolynomialsIfPossible(Polynomial const& polynomial);
Polynomials factorizeIfPossibleBySplittingByPolynomialDegree(Polynomial const& polynomial);
Polynomials factorizeIfPossibleBySplittingByDivisibilityOfExponents(Polynomial const& polynomial);
Polynomials factorizeIfPossibleBySplittingByFirstVariable(Polynomial const& polynomial);
Polynomials splitPolynomialsByPolynomialDegree(Polynomial const& polynomial);
Polynomials splitPolynomialsByDivisibilityOfExponents(Polynomial const& polynomial);
Polynomials splitPolynomialsByFirstVariable(Polynomial const& polynomial);
Polynomials factorizeSmallerPolynomials(Polynomials const& smallerPolynomials);
Polynomials factorizeSmallerPolynomialsByFactoringOutCommonFactors(Polynomials const& smallerPolynomials);
Polynomials factorizeSmallerPolynomialsBySubstitutingCommonFactorsToNewVariables(Polynomials const& smallerPolynomials);
Polynomials factorizePolynomialWithNewVariables(
        Polynomial const& newPolynomialWithVariables,
        SubstitutionOfVariablesToExpressions const& variableSubstitution);
Polynomials getCommonFactorsInThesePolynomials(Polynomials const& smallerPolynomials);
Polynomial getNewPolynomialWithNewVariables(
        SubstitutionOfVariablesToExpressions & variableSubstitution,
        Polynomials const& smallerPolynomials);
Polynomials getPolynomialsWithRemovedCommonFactors(Polynomials const& polynomialsWithCommonFactors, Polynomials const& commonFactors);
void updateToGetSubsetOfFactors(Polynomials & commonFactors, Polynomials const& currentCommonFactors);
void combinePolynomialsByAdditionAndThenEmplaceBack(Polynomials & result, Polynomials const& smallerPolynomials);

}

}

}
