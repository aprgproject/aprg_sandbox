#pragma once

#include <Algebra/Substitution/SubstitutionOfVariablesToTerms.hpp>
#include <Algebra/Term/TermTypes/Polynomial.hpp>

namespace alba
{

namespace algebra
{

namespace Factorization
{

Polynomials factorizeBySplittingToSmallerPolynomials(Polynomial const& polynomial);

void factorizeBySplittingToSmallerPolynomialsIfPossible(Polynomials & result, Polynomial const& polynomial);
void factorizeIfPossibleBySplittingByPolynomialDegree(Polynomials & result, Polynomial const& polynomial);
void factorizeIfPossibleBySplittingByDivisibilityOfExponents(Polynomials & result, Polynomial const& polynomial);
void factorizeIfPossibleBySplittingByFirstVariable(Polynomials & result, Polynomial const& polynomial);

void splitPolynomialsByPolynomialDegree(Polynomials & result, Polynomial const& polynomial);
void splitPolynomialsByDivisibilityOfExponents(Polynomials & result, Polynomial const& polynomial);
void splitPolynomialsByFirstVariable(Polynomials & result, Polynomial const& polynomial);

void factorizeSmallerPolynomials(Polynomials & result, Polynomials const& smallerPolynomials);
void factorizeSmallerPolynomialsByFactoringOutCommonFactors(Polynomials & result, Polynomials const& smallerPolynomials);
void factorizeSmallerPolynomialsBySubstitutingCommonFactorsToNewVariables(Polynomials & result, Polynomials const& smallerPolynomials);
void factorizePolynomialWithNewVariables(
        Polynomials & result,
        Polynomial const& newPolynomialWithVariables,
        SubstitutionOfVariablesToTerms const& variableSubstitution);
void getCommonFactorsInThesePolynomials(Polynomials & commonFactors, Polynomials const& smallerPolynomials);
Polynomial getNewPolynomialWithNewVariables(
        SubstitutionOfVariablesToTerms & variableSubstitution,
        Polynomials const& smallerPolynomials);void getPolynomialsWithRemovedCommonFactors(Polynomials & result, Polynomials const& polynomialsWithCommonFactors, Polynomials const& commonFactors);
void updateToGetSubsetOfFactors(Polynomials & commonFactors, Polynomials const& commonFactorsOfAPolynomial);
void combinePolynomialsByAdditionThenEmplaceFactoredPolynomialIfNeeded(Polynomials & result, Polynomials const& smallerPolynomials);
}

}

}
