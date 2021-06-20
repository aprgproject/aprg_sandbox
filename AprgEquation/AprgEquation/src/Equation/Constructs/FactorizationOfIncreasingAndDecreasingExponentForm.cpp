#include "FactorizationOfIncreasingAndDecreasingExponentForm.hpp"

#include <Equation/Constructs/BrentMethod.hpp>
#include <Equation/Constructs/Factorization.hpp>
#include <Equation/Constructs/PolynomialOverPolynomial.hpp>
#include <Math/AlbaMathHelper.hpp>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace equation
{

namespace Factorization
{

Polynomials FactorizationOfIncreasingAndDecreasingExponentForm::factorizeIfPossible(Polynomial const& polynomial)
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
                    factorizeUsingQuadraticFormulaOrBrentMethod(
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
    }    return result;
}

void FactorizationOfIncreasingAndDecreasingExponentForm::factorizeUsingQuadraticFormulaOrBrentMethod(        Polynomials & result,
        Polynomial const& polynomial,
        AlbaNumbers const& coefficients,
        Monomial::VariablesToExponentsMap const& firstVariableExponent,
        Monomial::VariablesToExponentsMap const& secondVariableExponent)
{
    if(coefficients.size() == 3)
    {
        factorizeQuadraticForm(result, coefficients, firstVariableExponent, secondVariableExponent);
    }
    else if(coefficients.size() > 3)
    {
        factorizeUsingBrentMethod(result, polynomial, coefficients, firstVariableExponent, secondVariableExponent);
    }
}

void FactorizationOfIncreasingAndDecreasingExponentForm::factorizeQuadraticForm(
        Polynomials & result,
        AlbaNumbers const& coefficients,
        Monomial::VariablesToExponentsMap const& firstVariableExponent,
        Monomial::VariablesToExponentsMap const& secondVariableExponent)
{
    if(coefficients.size() == 3)
    {
        AlbaNumbers roots(calculateQuadraticRoots(coefficients.at(0), coefficients.at(1), coefficients.at(2)));
        if(roots.size() == 2)
        {
            AlbaNumber firstRootFirstCoefficient(1);
            AlbaNumber firstRootSecondCoefficient(roots.at(0)*-1);
            AlbaNumber secondRootFirstCoefficient(1);
            AlbaNumber secondRootSecondCoefficient(roots.at(1)*-1);
            AlbaNumber aCoefficient(coefficients.at(0));
            if(aCoefficient.isIntegerOrFractionType() && firstRootSecondCoefficient.isIntegerOrFractionType())
            {
                fixCoefficientsOfFactors(aCoefficient, firstRootFirstCoefficient, firstRootSecondCoefficient);
            }
            if(aCoefficient.isIntegerOrFractionType() && secondRootSecondCoefficient.isIntegerOrFractionType())
            {
                fixCoefficientsOfFactors(aCoefficient, secondRootFirstCoefficient, secondRootSecondCoefficient);
            }
            if(aCoefficient != 1)
            {
                simplifyPolynomialThenEmplaceBack(result, Polynomial{Monomial(aCoefficient, {})});
                aCoefficient=aCoefficient/aCoefficient;
            }
            Monomial firstRootFirstMonomial(firstRootFirstCoefficient, firstVariableExponent);
            Monomial firstRootSecondMonomial(firstRootSecondCoefficient, secondVariableExponent);
            Monomial secondRootFirstMonomial(secondRootFirstCoefficient, firstVariableExponent);
            Monomial secondRootSecondMonomial(secondRootSecondCoefficient, secondVariableExponent);
            simplifyPolynomialThenEmplaceBack(result, Polynomial{firstRootFirstMonomial, firstRootSecondMonomial});
            simplifyPolynomialThenEmplaceBack(result, Polynomial{secondRootFirstMonomial, secondRootSecondMonomial});
        }
    }
}

void FactorizationOfIncreasingAndDecreasingExponentForm::factorizeUsingBrentMethod(
        Polynomials & result,
        Polynomial const& polynomial,
        AlbaNumbers const& coefficients,
        Monomial::VariablesToExponentsMap const& firstVariableExponent,
        Monomial::VariablesToExponentsMap const& secondVariableExponent)
{
    BrentMethod brentMethod(coefficients);
    AlbaNumberOptional rootOptional(brentMethod.calculateRoot());
    if(rootOptional.hasContent() && !coefficients.empty())
    {
        AlbaNumber rootFirstCoefficient(1);
        AlbaNumber rootSecondCoefficient(rootOptional.getConstReference()*-1);
        AlbaNumber aCoefficient(coefficients.at(0));
        if(aCoefficient.isIntegerOrFractionType() && rootSecondCoefficient.isIntegerOrFractionType())
        {
            fixCoefficientsOfFactors(aCoefficient, rootFirstCoefficient, rootSecondCoefficient);
        }
        Monomial rootFirstMonomial(rootFirstCoefficient, firstVariableExponent);
        Monomial rootSecondMonomial(rootSecondCoefficient, secondVariableExponent);
        Polynomial rootPolynomial{rootFirstMonomial, rootSecondMonomial};
        PolynomialOverPolynomial divideProcess(polynomial, rootPolynomial);
        PolynomialOverPolynomial::QuotientAndRemainder quotientAndRemainder(divideProcess.divide());
        simplifyPolynomialThenEmplaceBack(result, rootPolynomial);
        simplifyPolynomialThenEmplaceBack(result, quotientAndRemainder.quotient);
    }
}

void FactorizationOfIncreasingAndDecreasingExponentForm::fixCoefficientsOfFactors(
        AlbaNumber & aCoefficient,
        AlbaNumber & rootFirstCoefficient,
        AlbaNumber & rootSecondCoefficient)
{
    AlbaNumber::FractionData firstFractionData(aCoefficient.getFractionData());
    AlbaNumber::FractionData secondFractionData(rootSecondCoefficient.getFractionData());
    unsigned multiplier = getGreatestCommonFactor(firstFractionData.numerator, secondFractionData.denominator);
    rootFirstCoefficient = rootFirstCoefficient * multiplier;
    rootSecondCoefficient = rootSecondCoefficient * multiplier;
    aCoefficient = aCoefficient / multiplier;
}

Monomials FactorizationOfIncreasingAndDecreasingExponentForm::getMonomialsWithExponentsInOrder(
        unsigned int const exponentDivisor,
        Monomial const& firstInPolynomial,
        Monomial const& lastInPolynomial)
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

AlbaNumbers FactorizationOfIncreasingAndDecreasingExponentForm::getCoefficientsInMonomialsWithExponentsInOrder(
        Polynomial const& polynomial,
        Monomials const& monomialsWithExponentsInOrder)
{
    AlbaNumbers coefficients;
    for(Monomial const& monomialWithExponentInOrder : monomialsWithExponentsInOrder)
    {
        coefficients.emplace_back(
                    polynomial.getCoefficientOfVariableExponent(monomialWithExponentInOrder));
    }

    return coefficients;
}

AlbaNumbers FactorizationOfIncreasingAndDecreasingExponentForm::calculateQuadraticRoots(AlbaNumber const& a, AlbaNumber const& b, AlbaNumber const& c)
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

unsigned int FactorizationOfIncreasingAndDecreasingExponentForm::calculateMaxExponentDivisor(
        Monomial const& firstMonomial,
        Monomial const& lastMonomial)
{
    AlbaNumber maxExponent = max(firstMonomial.getMaxExponent(), lastMonomial.getMaxExponent());
    unsigned int maxExponentDivisor = getAbsoluteValue(maxExponent.getInteger());
    return maxExponentDivisor;
}

bool FactorizationOfIncreasingAndDecreasingExponentForm::areAllMonomialsFoundInMonomialsWithExponentsInOrder(        Monomials const& monomialsToCheck,
        Monomials const& monomialsWithExponentsInOrder)
{
    Polynomial polynomialWithExponentsInOrder(monomialsWithExponentsInOrder);    bool areAllMonomialsFoundInPolynomialWithExponentsInOrder(false);
    for(Monomial const& monomialToCheck : monomialsToCheck)
    {
        if(polynomialWithExponentsInOrder.isVariableExponentContentFound(monomialToCheck))
        {
            areAllMonomialsFoundInPolynomialWithExponentsInOrder = true;
            break;
        }
    }
    return areAllMonomialsFoundInPolynomialWithExponentsInOrder;
}

}

}

}
