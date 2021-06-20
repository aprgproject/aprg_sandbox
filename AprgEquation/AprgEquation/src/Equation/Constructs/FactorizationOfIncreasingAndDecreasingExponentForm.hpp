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

    Polynomials factorizeIfPossible(Polynomial const& polynomial);

private:
    void factorizeUsingQuadraticFormulaOrBrentMethod(
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
    void factorizeUsingBrentMethod(
            Polynomials & result,
            Polynomial const& polynomial,
            AlbaNumbers const& coefficients,
            Monomial::VariablesToExponentsMap const& firstVariableExponent,
            Monomial::VariablesToExponentsMap const& secondVariableExponent);
    void fixCoefficientsOfFactors(
            AlbaNumber & aCoefficient,
            AlbaNumber & rootFirstCoefficient,
            AlbaNumber & rootSecondCoefficient);
    Monomials getMonomialsWithExponentsInOrder(
            unsigned int const exponentDivisor,
            Monomial const& firstInPolynomial,
            Monomial const& lastInPolynomial);
    AlbaNumbers getCoefficientsInMonomialsWithExponentsInOrder(Polynomial const& polynomial, Monomials const& monomialsWithExponentsInOrder);
    AlbaNumbers calculateQuadraticRoots(AlbaNumber const& a, AlbaNumber const& n, AlbaNumber const& c);
    unsigned int calculateMaxExponentDivisor(Monomial const& firstMonomial, Monomial const& lastMonomial);
    bool areAllMonomialsFoundInMonomialsWithExponentsInOrder(
            Monomials const& monomialsToCheck,
            Monomials const& monomialsWithExponentsInOrder);};

}
}

}
