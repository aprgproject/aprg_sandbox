#pragma once

#include <Polynomial.hpp>

namespace alba
{

namespace equation
{

namespace Factorization
{

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
Polynomials factorizeCommonMonomialAndReturnEmptyIfNotFactorized(Polynomial const& polynomial);
Polynomials factorizeDifferenceOfSquaresAndReturnEmptyIfNotFactorized(Polynomial const& polynomial);
Polynomials factorizeDifferenceOfCubesAndReturnEmptyIfNotFactorized(Polynomial const& polynomial);
Polynomials factorizeSumOfCubesAndReturnEmptyIfNotFactorized(Polynomial const& polynomial);
Polynomials factorizeIncreasingAndDecreasingExponentsFormIfNotFactorized(Polynomial const& polynomial);
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
AlbaNumbers calculateQuadraticRoots(AlbaNumber const& a, AlbaNumber const& n, AlbaNumber const& c);

}
}

}
