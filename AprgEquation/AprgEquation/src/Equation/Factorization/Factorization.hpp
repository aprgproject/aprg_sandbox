#pragma once

#include <Equation/Term/Polynomial.hpp>
#include <Equation/Term/Expression.hpp>

namespace alba
{

namespace equation
{

namespace Factorization
{
Expression factorize(Expression const& expression);
Polynomials factorize(Polynomial const& polynomial);
Polynomials factorizePolynomials(Polynomials const& polynomials);
Polynomials returnPolynomialsOrSinglePolynomialIfEmpty(
        Polynomials const& polynomials,
        Polynomial const& polynomial);
Polynomials factorizeCommonMonomial(Polynomial const& polynomial);
Polynomials factorizeDifferenceOfSquares(Polynomial const& polynomial);
Polynomials factorizeDifferenceOfCubes(Polynomial const& polynomial);
Polynomials factorizeSumOfCubes(Polynomial const& polynomial);
Polynomials factorizeIncreasingAndDecreasingExponentsForm(Polynomial const& polynomial);
Polynomials factorizeBySplittingSmallerPolynomials(Polynomial const& polynomial);
Polynomials factorizeCommonMonomialIfPossible(Polynomial const& polynomial);
Polynomials factorizeDifferenceOfSquaresIfPossible(Polynomial const& polynomial);
Polynomials factorizeDifferenceOfCubesIfPossible(Polynomial const& polynomial);
Polynomials factorizeSumOfCubesIfPossible(Polynomial const& polynomial);
Polynomials factorizeBySplittingSmallerPolynomialsIfPossible(Polynomial const& polynomial);
Polynomials splitPolynomialIntoSmallerPolynomials(Polynomial const& polynomial);
Polynomials getCommonFactorsInThesePolynomials(Polynomials const& smallerPolynomials);
Polynomials getPolynomialsWithRemovedCommonFactors(Polynomials const& polynomialsWithCommonFactors, Polynomials const& commonFactors);
void combinePolynomialsByAdditionAndThenEmplaceBack(Polynomials & result, Polynomials const& smallerPolynomials);
void addFactorsOfDifferenceOfSquares(Polynomials & result, Polynomial const& polynomial);
void addFactorsOfDifferenceOfCubes(Polynomials & result, Polynomial const& polynomial);
void addFactorsOfSumOfCubes(Polynomials & result, Polynomial const& polynomial);
bool isDifferenceOfSquares(Polynomial const& polynomial);
bool isDifferenceOfCubes(Polynomial const& polynomial);
bool isSumOfCubes(Polynomial const& polynomial);
bool isPerfectSquare(Monomial const& monomial);
bool isPerfectCube(Monomial const& monomial);
bool isPerfectNthPower(Monomial const& monomial, unsigned int const nthPower);
bool areExponentsDivisible(Monomial const& monomial, unsigned int const divisor);
void simplifyPolynomialThenEmplaceBack(Polynomials & polynomials, Polynomial const& polynomial);

}

}

}
