#include "FactorizationOfIncreasingAndDecreasingExponentForm.hpp"

#include <Equation/Constructs/PolynomialOverPolynomial.hpp>
#include <Equation/Factorization/BrentMethod.hpp>
#include <Equation/Factorization/Factorization.hpp>
#include <Math/AlbaMathHelper.hpp>

#include <algorithm>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace equation
{

namespace Factorization
{

Polynomials FactorizationOfIncreasingAndDecreasingExponentForm::factorizeIfPossible(Polynomial const& polynomial) const
{
    Polynomials result;
    Monomials monomials(polynomial.getMonomialsConstReference());
    if(monomials.size() > 1)
    {
        Monomial firstMonomial(monomials.front());
        Monomial lastMonomial(monomials.back());
        unsigned int maxExponentDivisor(calculateMaxExponentDivisor(firstMonomial, lastMonomial));
        for(unsigned int exponentDivisor=2; exponentDivisor<=maxExponentDivisor; exponentDivisor++)
        {
            if(areExponentsDivisible(firstMonomial, exponentDivisor) && areExponentsDivisible(lastMonomial, exponentDivisor))
            {
                Monomial unitFirstMonomial(1, firstMonomial.getVariablesToExponentsMapConstReference());
                Monomial unitSecondMonomial(1, lastMonomial.getVariablesToExponentsMapConstReference());
                unitFirstMonomial.raiseToPowerNumber(AlbaNumber(1, exponentDivisor));
                unitSecondMonomial.raiseToPowerNumber(AlbaNumber(1, exponentDivisor));
                Monomials monomialsWithExponentsInOrder(getMonomialsWithExponentsInOrder(exponentDivisor, unitFirstMonomial, unitSecondMonomial));
                if(areAllMonomialsFoundInMonomialsWithExponentsInOrder(monomials, monomialsWithExponentsInOrder))
                {
                    AlbaNumbers coefficients(getCoefficientsInMonomialsWithExponentsInOrder(polynomial, monomialsWithExponentsInOrder));
                    factorizePolynomialForm(
                                result,
                                polynomial,
                                coefficients,
                                unitFirstMonomial.getVariablesToExponentsMapConstReference(),
                                unitSecondMonomial.getVariablesToExponentsMapConstReference());
                }
                if(!result.empty())
                {
                    break;
                }
            }
        }
    }
    return result;
}

void FactorizationOfIncreasingAndDecreasingExponentForm::factorizePolynomialForm(
        Polynomials & result,
        Polynomial const& polynomial,
        AlbaNumbers const& coefficients,
        Monomial::VariablesToExponentsMap const& firstVariableExponent,
        Monomial::VariablesToExponentsMap const& secondVariableExponent) const
{
    AlbaNumbers rootValues(calculatePolynomialRoots(coefficients));
    Polynomial remainingPolynomial(polynomial);
    for(AlbaNumber const& rootValue : rootValues)
    {
        AlbaNumber rootFirstCoefficient(1);
        AlbaNumber rootSecondCoefficient(rootValue*-1);
        AlbaNumber aCoefficient(remainingPolynomial.getFirstMonomial().getConstantConstReference());
        if(aCoefficient.isIntegerOrFractionType() && rootSecondCoefficient.isIntegerOrFractionType())
        {
            fixCoefficientsOfFactors(aCoefficient, rootFirstCoefficient, rootSecondCoefficient);
        }
        Monomial rootFirstMonomial(rootFirstCoefficient, firstVariableExponent);
        Monomial rootSecondMonomial(rootSecondCoefficient, secondVariableExponent);
        Polynomial rootPolynomial{rootFirstMonomial, rootSecondMonomial};
        PolynomialOverPolynomial divideProcess(remainingPolynomial, rootPolynomial);
        PolynomialOverPolynomial::QuotientAndRemainder quotientAndRemainder(divideProcess.divide());
        simplifyPolynomialThenEmplaceBack(result, rootPolynomial);
        remainingPolynomial = quotientAndRemainder.quotient;
    }
    if(!remainingPolynomial.isOne())
    {
        simplifyPolynomialThenEmplaceBack(result, remainingPolynomial);
    }
}

void FactorizationOfIncreasingAndDecreasingExponentForm::fixCoefficientsOfFactors(
        AlbaNumber & aCoefficient,
        AlbaNumber & rootFirstCoefficient,
        AlbaNumber & rootSecondCoefficient) const
{
    AlbaNumber::FractionData firstFractionData(aCoefficient.getFractionData());
    AlbaNumber::FractionData secondFractionData(rootSecondCoefficient.getFractionData());
    unsigned multiplier = getGreatestCommonFactor(firstFractionData.numerator, secondFractionData.denominator);
    rootFirstCoefficient = rootFirstCoefficient * multiplier;
    rootSecondCoefficient = rootSecondCoefficient * multiplier;
    aCoefficient = aCoefficient / multiplier;
}

bool FactorizationOfIncreasingAndDecreasingExponentForm::areAllMonomialsFoundInMonomialsWithExponentsInOrder(
        Monomials const& monomialsToCheck,
        Monomials const& monomialsWithExponentsInOrder) const
{
    Polynomial polynomialWithExponentsInOrder(monomialsWithExponentsInOrder);
    bool areAllMonomialsFoundInPolynomialWithExponentsInOrder(true);
    for(Monomial const& monomialToCheck : monomialsToCheck)
    {
        if(!polynomialWithExponentsInOrder.isVariableExponentContentFound(monomialToCheck))
        {
            areAllMonomialsFoundInPolynomialWithExponentsInOrder = false;
            break;
        }
    }
    return areAllMonomialsFoundInPolynomialWithExponentsInOrder;
}

unsigned int FactorizationOfIncreasingAndDecreasingExponentForm::calculateMaxExponentDivisor(
        Monomial const& firstMonomial,
        Monomial const& lastMonomial) const
{
    AlbaNumber maxExponent = max(firstMonomial.getMaxExponent(), lastMonomial.getMaxExponent());
    unsigned int maxExponentDivisor = getAbsoluteValue(maxExponent.getInteger());
    return maxExponentDivisor;
}

AlbaNumbers FactorizationOfIncreasingAndDecreasingExponentForm::getCoefficientsInMonomialsWithExponentsInOrder(
        Polynomial const& polynomial,
        Monomials const& monomialsWithExponentsInOrder) const
{
    AlbaNumbers coefficients;
    for(Monomial const& monomialWithExponentInOrder : monomialsWithExponentsInOrder)
    {
        coefficients.emplace_back(
                    polynomial.getCoefficientOfVariableExponent(monomialWithExponentInOrder));
    }

    return coefficients;
}

AlbaNumbers FactorizationOfIncreasingAndDecreasingExponentForm::calculatePolynomialRoots(AlbaNumbers const& coefficients) const
{
    AlbaNumbers result;
    if(coefficients.size() == 3)
    {
        result = calculateQuadraticRoots(coefficients.at(0), coefficients.at(1), coefficients.at(2));
    }
    else
    {
        AlbaNumbers derivativeRoots(calculatePolynomialRoots(getDerivativeCoefficients(coefficients)));
        result = calculatePolynomialRootsUsingBrentMethod(derivativeRoots, coefficients);
    }
    return result;
}

AlbaNumbers FactorizationOfIncreasingAndDecreasingExponentForm::calculateQuadraticRoots(
        AlbaNumber const& a,
        AlbaNumber const& b,
        AlbaNumber const& c) const
{
    AlbaNumbers result;
    AlbaNumber discriminant((b^2)-(a*c*4));
    if(discriminant >= 0)
    {
        AlbaNumber discriminantSquaredRoot = discriminant^(AlbaNumber(1, 2));
        AlbaNumber firstPart((-b)/(a*2));
        AlbaNumber secondPart(discriminantSquaredRoot/(a*2));
        result.emplace_back(firstPart + secondPart);
        result.emplace_back(firstPart - secondPart);
    }
    return result;
}

AlbaNumbers FactorizationOfIncreasingAndDecreasingExponentForm::calculatePolynomialRootsUsingBrentMethod(
        AlbaNumbers const& previousDerivativeRoots,
        AlbaNumbers const& coefficients) const
{
    AlbaNumbers result;
    AlbaNumbers valuesForRootFinding(previousDerivativeRoots);
    AlbaNumber maxAbsoluteValue(getMaxAbsoluteValueForRootFinding(coefficients));
    valuesForRootFinding.emplace_back(maxAbsoluteValue*-1);
    valuesForRootFinding.emplace_back(maxAbsoluteValue);
    sort(valuesForRootFinding.begin(), valuesForRootFinding.end());
    BrentMethod brentMethod(coefficients);
    unsigned int size = valuesForRootFinding.size();
    for(unsigned int i = 0; i<size-1; i++)
    {
        unsigned int j=i+1;
        AlbaNumberOptional rootOptional(brentMethod.calculateRoot(valuesForRootFinding.at(i), valuesForRootFinding.at(j)));
        if(rootOptional.hasContent())
        {
            result.emplace_back(rootOptional.getConstReference());
        }
    }
    return result;
}

AlbaNumber FactorizationOfIncreasingAndDecreasingExponentForm::getMaxAbsoluteValueForRootFinding(AlbaNumbers const& coefficients) const
{
    AlbaNumber result(0);
    if(!coefficients.empty())
    {
        result = max(getAbsoluteValue(coefficients.front()), getAbsoluteValue(coefficients.back()));
    }
    return result;
}

AlbaNumbers FactorizationOfIncreasingAndDecreasingExponentForm::getDerivativeCoefficients(AlbaNumbers const& coefficients) const
{
    AlbaNumbers derivativeCoefficients(coefficients);
    if(!derivativeCoefficients.empty())
    {
        derivativeCoefficients.pop_back();
        AlbaNumber derivativeMultiplier = derivativeCoefficients.size();
        for(AlbaNumber & derivativeCoefficient : derivativeCoefficients)
        {
            derivativeCoefficient = derivativeCoefficient*derivativeMultiplier;
            derivativeMultiplier=derivativeMultiplier-1;
        }
    }
    return derivativeCoefficients;
}

Monomials FactorizationOfIncreasingAndDecreasingExponentForm::getMonomialsWithExponentsInOrder(
        unsigned int const exponentDivisor,
        Monomial const& firstInPolynomial,
        Monomial const& lastInPolynomial) const
{
    Monomials monomialsWithExponentsInOrder;
    for(unsigned int i=0; i<=exponentDivisor; i++)
    {
        Monomial firstPart(firstInPolynomial);
        firstPart.raiseToPowerNumber(exponentDivisor-i);
        Monomial secondPart(lastInPolynomial);
        secondPart.raiseToPowerNumber(i);
        Monomial product(firstPart);
        product.multiplyMonomial(secondPart);
        product.simplify();
        monomialsWithExponentsInOrder.emplace_back(product);
    }
    return monomialsWithExponentsInOrder;
}

}

}

}
