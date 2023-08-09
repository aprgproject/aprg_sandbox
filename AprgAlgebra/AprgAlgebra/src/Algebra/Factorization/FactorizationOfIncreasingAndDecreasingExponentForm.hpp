#pragma once

#include <Algebra/Term/TermTypes/Polynomial.hpp>
#include <Math/AlbaNumberTypes.hpp>

namespace alba
{

namespace algebra
{

namespace Factorization
{

Polynomials factorizeIncreasingAndDecreasingExponentsForm(Polynomial const& polynomial);
Polynomials factorizeIncreasingAndDecreasingExponentsFormIfPossible(Polynomial const& polynomial);
Polynomials factorizePolynomialForm(
        Polynomial const& polynomial,
        AlbaNumbers const& coefficients,
        Monomial::VariablesToExponentsMap const& firstVariableExponent,
        Monomial::VariablesToExponentsMap const& secondVariableExponent);
void fixCoefficientsOfFactors(
        AlbaNumber & aCoefficient,
        AlbaNumber & rootFirstCoefficient,
        AlbaNumber & rootSecondCoefficient);
bool areAllMonomialsFoundInMonomialsWithExponentsInOrder(
        Monomials const& monomialsToCheck,
        Monomials const& monomialsWithExponentsInOrder);
unsigned int calculateMaxExponentDivisor(Monomial const& firstMonomial, Monomial const& lastMonomial);
AlbaNumbers getCoefficientsInMonomialsWithExponentsInOrder(Polynomial const& polynomial, Monomials const& monomialsWithExponentsInOrder);
AlbaNumbers calculatePolynomialRoots(AlbaNumbers const& coefficients);
AlbaNumbers calculateQuadraticRoots(AlbaNumber const& a, AlbaNumber const& n, AlbaNumber const& c);
AlbaNumbers calculatePolynomialRootsUsingBrentMethod(AlbaNumbers const& previousDerivativeRoots, AlbaNumbers const& coefficients);
AlbaNumber getMaxAbsoluteValueForRootFinding(AlbaNumbers const& coefficients);
AlbaNumbers getDerivativeCoefficients(AlbaNumbers const& coefficients);
Monomials getMonomialsWithExponentsInOrder(
        unsigned int const exponentDivisor,
        Monomial const& firstInPolynomial,
        Monomial const& lastInPolynomial);

}

}

}
