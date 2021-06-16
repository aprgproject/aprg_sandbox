#pragma once

#include <Math/AlbaNumberTypes.hpp>
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
void factorizeRootsInIncreasingAndDecreasingExponentsForm(
        Polynomials & result,
        Polynomial const& polynomial,
        AlbaNumbers const& coefficients,
        Monomial::VariablesToExponentsMap const& firstVariableExponent,
        Monomial::VariablesToExponentsMap const& secondVariableExponent);
void factorizeQuadraticForm(
        Polynomials & result,
        AlbaNumbers const& coefficients,
        Monomial::VariablesToExponentsMap const& firstVariableExponent,
        Monomial::VariablesToExponentsMap const& secondVariableExponent);
void factorizeOneRootInIncreasingAndDecreasingExponentsForm(
        Polynomials & result,
        Polynomial const& polynomial,
        AlbaNumbers const& coefficients,
        Monomial::VariablesToExponentsMap const& firstVariableExponent,
        Monomial::VariablesToExponentsMap const& secondVariableExponent);
void addFactorsOfDifferenceOfSquares(Polynomials & result, Polynomial const& polynomial);
void addFactorsOfDifferenceOfCubes(Polynomials & result, Polynomial const& polynomial);
void addFactorsOfSumOfCubes(Polynomials & result, Polynomial const& polynomial);
void fixCoefficientsOfFactors(
        AlbaNumber & aCoefficient,
        AlbaNumber & secondRootFirstCoefficient,
        AlbaNumber & secondRootSecondCoefficient);
bool isDifferenceOfSquares(Polynomial const& polynomial);
bool isDifferenceOfCubes(Polynomial const& polynomial);
bool isSumOfCubes(Polynomial const& polynomial);
bool isPerfectSquare(Monomial const& monomial);
bool isPerfectCube(Monomial const& monomial);
bool isPerfectNthPower(Monomial const& monomial, unsigned int const nthPower);
bool areExponentsDivisible(Monomial const& monomial, unsigned int const divisor);
bool areAllMonomialsFoundInMonomialsWithExponentsInOrder(
        Monomials const& monomialsToCheck,
        Monomials const& monomialsWithExponentsInOrder);
void simplifyPolynomialThenEmplaceBack(Polynomials & polynomials, Polynomial const& polynomial);
Monomials getMonomialsWithExponentsInOrder(
        unsigned int const exponentDivisor,
        Monomial const& firstInPolynomial,
        Monomial const& lastInPolynomial);
AlbaNumbers getCoefficientsInMonomialsWithExponentsInOrder(Polynomial const& polynomial, Monomials const& monomialsWithExponentsInOrder);
AlbaNumbers calculateQuadraticRoots(AlbaNumber const& a, AlbaNumber const& n, AlbaNumber const& c);
unsigned int calculateExponentDivisor(Monomial const& firstMonomial, Monomial const& lastMonomial);

}

}

}
