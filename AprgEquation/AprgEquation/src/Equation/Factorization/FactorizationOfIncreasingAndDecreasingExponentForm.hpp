#pragma once

#include <Equation/Term/Polynomial.hpp>
#include <Math/AlbaNumberTypes.hpp>

namespace alba
{

namespace equation
{

namespace Factorization
{

class FactorizationOfIncreasingAndDecreasingExponentForm
{
public:

    Polynomials factorizeIfPossible(Polynomial const& polynomial) const;

private:

    void factorizePolynomialForm(
            Polynomials & result,
            Polynomial const& polynomial,
            AlbaNumbers const& coefficients,
            Monomial::VariablesToExponentsMap const& firstVariableExponent,
            Monomial::VariablesToExponentsMap const& secondVariableExponent) const;
    void fixCoefficientsOfFactors(
            AlbaNumber & aCoefficient,
            AlbaNumber & rootFirstCoefficient,
            AlbaNumber & rootSecondCoefficient) const;
    bool areAllMonomialsFoundInMonomialsWithExponentsInOrder(
            Monomials const& monomialsToCheck,
            Monomials const& monomialsWithExponentsInOrder) const;
    unsigned int calculateMaxExponentDivisor(Monomial const& firstMonomial, Monomial const& lastMonomial) const;
    AlbaNumbers getCoefficientsInMonomialsWithExponentsInOrder(Polynomial const& polynomial, Monomials const& monomialsWithExponentsInOrder) const;
    AlbaNumbers calculatePolynomialRoots(AlbaNumbers const& coefficients) const;
    AlbaNumbers calculateQuadraticRoots(AlbaNumber const& a, AlbaNumber const& n, AlbaNumber const& c) const;
    AlbaNumbers calculatePolynomialRootsUsingBrentMethod(AlbaNumbers const& previousDerivativeRoots, AlbaNumbers const& coefficients) const;
    AlbaNumber getMaxAbsoluteValueForRootFinding(AlbaNumbers const& coefficients) const;
    AlbaNumbers getDerivativeCoefficients(AlbaNumbers const& coefficients) const;
    Monomials getMonomialsWithExponentsInOrder(
            unsigned int const exponentDivisor,
            Monomial const& firstInPolynomial,
            Monomial const& lastInPolynomial) const;
};

}

}

}
