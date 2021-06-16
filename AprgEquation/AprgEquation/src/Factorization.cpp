#include "Factorization.hpp"

#include <BrentMethod.hpp>
#include <Math/AlbaMathHelper.hpp>
#include <PolynomialOverPolynomial.hpp>
#include <Utilities.hpp>

#include <algorithm>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

namespace equation
{

namespace Factorization
{

Polynomials factorize(Polynomial const& polynomial)
{
    Polynomial polynomialToFactorize(polynomial);
    polynomialToFactorize.simplifyAndSort();
    Polynomials result(factorizeCommonMonomial(polynomialToFactorize));
    if(result.size() == 1){result = factorizeDifferenceOfSquares(polynomialToFactorize); }
    if(result.size() == 1){result = factorizeDifferenceOfCubes(polynomialToFactorize); }
    if(result.size() == 1){result = factorizeSumOfCubes(polynomialToFactorize); }
    if(result.size() == 1){result = factorizeIncreasingAndDecreasingExponentsForm(polynomialToFactorize); }
    if(result.size() == 1){result = factorizeBySplittingSmallerPolynomials(polynomialToFactorize); }
    if(result.size() != 1)
    {
        result = factorizePolynomials(result);    }
    return result;
}
Polynomials factorizePolynomials(Polynomials const& polynomials)
{
    Polynomials result;
    for(Polynomial const& polynomialToFactorize : polynomials)
    {
        Polynomials factorizedPolynomials(factorize(polynomialToFactorize));
        if(factorizedPolynomials.size() == 1)
        {
            simplifyPolynomialThenEmplaceBack(result, polynomialToFactorize);
        }
        else
        {
            copy(factorizedPolynomials.cbegin(), factorizedPolynomials.cend(), back_inserter(result));
        }
    }
    return result;
}

Polynomials returnPolynomialsOrSinglePolynomialIfEmpty(
        Polynomials const& polynomials,
        Polynomial const& polynomial)
{
    Polynomials result(polynomials);
    if(result.empty())
    {
        simplifyPolynomialThenEmplaceBack(result, polynomial);
    }
    return result;
}

Polynomials factorizeCommonMonomial(Polynomial const& polynomial)
{
    return returnPolynomialsOrSinglePolynomialIfEmpty(
                factorizeCommonMonomialIfPossible(polynomial),
                polynomial);
}
Polynomials factorizeDifferenceOfSquares(Polynomial const& polynomial)
{
    return returnPolynomialsOrSinglePolynomialIfEmpty(
                factorizeDifferenceOfSquaresIfPossible(polynomial),
                polynomial);
}
Polynomials factorizeDifferenceOfCubes(Polynomial const& polynomial)
{
    return returnPolynomialsOrSinglePolynomialIfEmpty(
                factorizeDifferenceOfCubesIfPossible(polynomial),
                polynomial);
}
Polynomials factorizeSumOfCubes(Polynomial const& polynomial)
{
    return returnPolynomialsOrSinglePolynomialIfEmpty(
                factorizeSumOfCubesIfPossible(polynomial),
                polynomial);
}
Polynomials factorizeIncreasingAndDecreasingExponentsForm(Polynomial const& polynomial)
{
    return returnPolynomialsOrSinglePolynomialIfEmpty(
                factorizeIncreasingAndDecreasingExponentsFormIfPossible(polynomial),
                polynomial);
}

Polynomials factorizeBySplittingSmallerPolynomials(Polynomial const& polynomial)
{
    return returnPolynomialsOrSinglePolynomialIfEmpty(
                factorizeBySplittingSmallerPolynomialsIfPossible(polynomial),
                polynomial);
}

Polynomials factorizeCommonMonomialIfPossible(Polynomial const& polynomial)
{
    Polynomials result;
    if(!polynomial.isOneMonomial())
    {        Monomial commonMonomial(getCommonMonomialInMonomials(polynomial.getMonomialsConstReference()));
        if(!commonMonomial.isOne())
        {
            Polynomial reducedPolynomial(polynomial);            reducedPolynomial.divideMonomial(commonMonomial);
            reducedPolynomial.simplify();
            simplifyPolynomialThenEmplaceBack(result, createPolynomialFromMonomial(commonMonomial));
            simplifyPolynomialThenEmplaceBack(result, reducedPolynomial);
        }
    }
    return result;
}

Polynomials factorizeDifferenceOfSquaresIfPossible(Polynomial const& polynomial)
{
    Polynomials result;
    if(isDifferenceOfSquares(polynomial))    {
        addFactorsOfDifferenceOfSquares(result, polynomial);
    }
    return result;
}

Polynomials factorizeDifferenceOfCubesIfPossible(Polynomial const& polynomial)
{
    Polynomials result;
    if(isDifferenceOfCubes(polynomial))    {
        addFactorsOfDifferenceOfCubes(result, polynomial);
    }
    return result;
}

Polynomials factorizeSumOfCubesIfPossible(Polynomial const& polynomial)
{
    Polynomials result;
    if(isSumOfCubes(polynomial))    {
        addFactorsOfSumOfCubes(result, polynomial);
    }
    return result;
}

Polynomials factorizeIncreasingAndDecreasingExponentsFormIfPossible(Polynomial const& polynomial)
{
    Polynomials result;
    Monomials monomials(polynomial.getMonomialsConstReference());    if(monomials.size() > 1)
    {
        Monomial firstMonomial(monomials.front());
        Monomial lastMonomial(monomials.back());        unsigned int exponentDivisor(calculateExponentDivisor(firstMonomial, lastMonomial));
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
                factorizeRootsInIncreasingAndDecreasingExponentsForm(
                            result,
                            polynomial,
                            coefficients,
                            unitFirstMonomial.getVariablesToExponentsMapConstReference(),
                            unitSecondMonomial.getVariablesToExponentsMapConstReference());
            }
        }
    }
    return result;
}

void factorizeRootsInIncreasingAndDecreasingExponentsForm(
        Polynomials & result,
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
        factorizeOneRootInIncreasingAndDecreasingExponentsForm(result, polynomial, coefficients, firstVariableExponent, secondVariableExponent);
    }
}
void factorizeQuadraticForm(
        Polynomials & result,
        AlbaNumbers const& coefficients,        Monomial::VariablesToExponentsMap const& firstVariableExponent,
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

void factorizeOneRootInIncreasingAndDecreasingExponentsForm(
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

Polynomials factorizeBySplittingSmallerPolynomialsIfPossible(Polynomial const& polynomial)
{
    Polynomials result;
    Polynomials smallerPolynomials(splitPolynomialIntoSmallerPolynomials(polynomial));
    if(smallerPolynomials.size() > 1)
    {
        Polynomials commonFactors(getCommonFactorsInPolynomials(smallerPolynomials));
        if(!commonFactors.empty())
        {
            removeCommonFactorsInPolynomials(smallerPolynomials, commonFactors);
            combinePolynomialsByAdditionAndEmplaceBack(result, smallerPolynomials);
            for(Polynomial const& commonFactor : commonFactors)
            {
                simplifyPolynomialThenEmplaceBack(result, commonFactor);
            }
        }

    }
    return result;
}

Polynomials splitPolynomialIntoSmallerPolynomials(Polynomial const& polynomial)
{
    Polynomials result;
    Monomials monomials(polynomial.getMonomialsConstReference());
    Polynomial partialPolynomial;
    string firstVariableName;
    bool isFirst(true);
    for(Monomial const& monomial : monomials)
    {
        string monomialFirstVariableName(monomial.getFirstVariableName());
        if(!monomialFirstVariableName.empty())
        {
            if(isFirst)
            {
                firstVariableName = monomialFirstVariableName;
                isFirst = false;
            }
            if(firstVariableName != monomialFirstVariableName)
            {
                firstVariableName = monomialFirstVariableName;
                result.emplace_back(partialPolynomial);
                partialPolynomial.clear();
            }
        }
        partialPolynomial.addMonomial(monomial);
    }
    if(!partialPolynomial.isEmpty())
    {
        result.emplace_back(partialPolynomial);
    }
    return result;
}

Polynomials getCommonFactorsInPolynomials(Polynomials const& smallerPolynomials)
{
    Polynomials commonFactors;
    bool isFirst(true);
    for(Polynomial const& smallerPolynomial : smallerPolynomials)
    {
        Polynomials smallerFactors(factorize(smallerPolynomial));
        if(isFirst)
        {
            commonFactors = smallerFactors;
            isFirst = false;
        }
        else
        {
            Polynomials previousCommonFactors(commonFactors);
            commonFactors.clear();
            for(Polynomial const& previousCommonFactor : previousCommonFactors)
            {
                for(Polynomial const& smallerFactor : smallerFactors)
                {
                    if(previousCommonFactor == smallerFactor)
                    {
                        commonFactors.emplace_back(smallerFactor);
                        break;
                    }
                }
            }
        }
    }
    return commonFactors;
}

void removeCommonFactorsInPolynomials(Polynomials & polynomials, Polynomials const& commonFactors)
{
    for(Polynomial const& commonFactor : commonFactors)
    {
        for(Polynomial & smallerPolynomial : polynomials)
        {
            PolynomialOverPolynomial divideProcess(smallerPolynomial, commonFactor);
            PolynomialOverPolynomial::QuotientAndRemainder quotientAndRemainder(divideProcess.divide());
            smallerPolynomial = quotientAndRemainder.quotient;
        }
    }
}

void combinePolynomialsByAdditionAndEmplaceBack(Polynomials & result, Polynomials const& smallerPolynomials)
{
    Polynomial combinedPolynomial;
    for(Polynomial const& smallerPolynomial : smallerPolynomials)
    {
        combinedPolynomial.addPolynomial(smallerPolynomial);
    }
    simplifyPolynomialThenEmplaceBack(result, combinedPolynomial);
}

void addFactorsOfDifferenceOfSquares(Polynomials & result, Polynomial const& polynomial)
{
    Monomials monomials(polynomial.getMonomialsConstReference());    Monomial firstMonomial(monomials.at(0));
    Monomial secondMonomial(monomials.at(1));
    if(firstMonomial.getConstantConstReference() > 0 && secondMonomial.getConstantConstReference() < 0)
    {        secondMonomial.multiplyNumber(-1);
    }
    else if(firstMonomial.getConstantConstReference() < 0 && secondMonomial.getConstantConstReference() > 0)
    {
        firstMonomial.multiplyNumber(-1);
        simplifyPolynomialThenEmplaceBack(result, createPolynomialFromConstant(Constant(-1)));
    }
    firstMonomial.raiseToPowerNumber(AlbaNumber(1, 2));
    secondMonomial.raiseToPowerNumber(AlbaNumber(1, 2));
    simplifyPolynomialThenEmplaceBack(result, Polynomial{firstMonomial, secondMonomial});
    secondMonomial.multiplyNumber(-1);
    simplifyPolynomialThenEmplaceBack(result, Polynomial{firstMonomial, secondMonomial});
}

void addFactorsOfDifferenceOfCubes(Polynomials & result, Polynomial const& polynomial)
{
    Monomials monomials(polynomial.getMonomialsConstReference());
    Monomial firstMonomial(monomials.at(0));
    Monomial secondMonomial(monomials.at(1));
    if(firstMonomial.getConstantConstReference() > 0 && secondMonomial.getConstantConstReference() < 0)
    {
        secondMonomial.multiplyNumber(-1);
    }
    else if(firstMonomial.getConstantConstReference() < 0 && secondMonomial.getConstantConstReference() > 0)
    {
        firstMonomial.multiplyNumber(-1);
        simplifyPolynomialThenEmplaceBack(result, createPolynomialFromConstant(Constant(-1)));
    }
    firstMonomial.raiseToPowerNumber(AlbaNumber(1, 3));
    secondMonomial.raiseToPowerNumber(AlbaNumber(1, 3));
    Monomial firstMonomialSquared(firstMonomial);
    Monomial secondMonomialSquared(secondMonomial);
    Monomial productOfFirstAndSecond(firstMonomial);
    firstMonomialSquared.raiseToPowerNumber(2);
    secondMonomialSquared.raiseToPowerNumber(2);
    productOfFirstAndSecond.multiplyMonomial(secondMonomial);
    secondMonomial.multiplyNumber(-1);
    simplifyPolynomialThenEmplaceBack(result, Polynomial{firstMonomial, secondMonomial});
    simplifyPolynomialThenEmplaceBack(result, Polynomial{firstMonomialSquared, productOfFirstAndSecond, secondMonomialSquared});
}

void addFactorsOfSumOfCubes(Polynomials & result, Polynomial const& polynomial)
{
    Monomials monomials(polynomial.getMonomialsConstReference());
    Monomial firstMonomial(monomials.at(0));
    Monomial secondMonomial(monomials.at(1));
    if(firstMonomial.getConstantConstReference() < 0 && secondMonomial.getConstantConstReference() < 0)
    {
        firstMonomial.multiplyNumber(-1);
        secondMonomial.multiplyNumber(-1);
        simplifyPolynomialThenEmplaceBack(result, createPolynomialFromConstant(Constant(-1)));
    }
    firstMonomial.raiseToPowerNumber(AlbaNumber(1, 3));
    secondMonomial.raiseToPowerNumber(AlbaNumber(1, 3));
    Monomial firstMonomialSquared(firstMonomial);
    Monomial secondMonomialSquared(secondMonomial);
    Monomial productOfFirstAndSecond(firstMonomial);
    firstMonomialSquared.raiseToPowerNumber(2);
    secondMonomialSquared.raiseToPowerNumber(2);
    productOfFirstAndSecond.multiplyMonomial(secondMonomial);
    productOfFirstAndSecond.multiplyNumber(-1);
    simplifyPolynomialThenEmplaceBack(result, Polynomial{firstMonomial, secondMonomial});
    simplifyPolynomialThenEmplaceBack(result, Polynomial{firstMonomialSquared, productOfFirstAndSecond, secondMonomialSquared});
}

void fixCoefficientsOfFactors(
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

bool isDifferenceOfSquares(Polynomial const& polynomial)
{
    bool result(false);
    Monomials monomials(polynomial.getMonomialsConstReference());
    if(monomials.size() == 2)
    {
        Monomial firstMonomial(monomials.at(0));
        Monomial secondMonomial(monomials.at(1));
        if(firstMonomial.getConstantConstReference() > 0 && secondMonomial.getConstantConstReference() < 0)
        {
            secondMonomial.multiplyNumber(-1);
            result =  isPerfectSquare(firstMonomial) && isPerfectSquare(secondMonomial);
        }
        else if(firstMonomial.getConstantConstReference() < 0 && secondMonomial.getConstantConstReference() > 0)
        {
            firstMonomial.multiplyNumber(-1);
            result =  isPerfectSquare(firstMonomial) && isPerfectSquare(secondMonomial);
        }
    }
    return result;
}

bool isDifferenceOfCubes(Polynomial const& polynomial)
{
    bool result(false);
    Monomials monomials(polynomial.getMonomialsConstReference());
    if(monomials.size() == 2)
    {
        Monomial firstMonomial(monomials.at(0));
        Monomial secondMonomial(monomials.at(1));
        if(firstMonomial.getConstantConstReference() > 0 && secondMonomial.getConstantConstReference() < 0)
        {
            secondMonomial.multiplyNumber(-1);
            result =  isPerfectCube(firstMonomial) && isPerfectCube(secondMonomial);
        }
        else if(firstMonomial.getConstantConstReference() < 0 && secondMonomial.getConstantConstReference() > 0)
        {
            firstMonomial.multiplyNumber(-1);
            result =  isPerfectCube(firstMonomial) && isPerfectCube(secondMonomial);
        }
    }
    return result;
}

bool isSumOfCubes(Polynomial const& polynomial)
{
    bool result(false);
    Monomials monomials(polynomial.getMonomialsConstReference());
    if(monomials.size() == 2)
    {
        Monomial firstMonomial(monomials.at(0));
        Monomial secondMonomial(monomials.at(1));
        if(firstMonomial.getConstantConstReference() > 0 && secondMonomial.getConstantConstReference() > 0)
        {
            result =  isPerfectCube(firstMonomial) && isPerfectCube(secondMonomial);
        }
        else if(firstMonomial.getConstantConstReference() < 0 && secondMonomial.getConstantConstReference() < 0)
        {
            firstMonomial.multiplyNumber(-1);
            secondMonomial.multiplyNumber(-1);
            result =  isPerfectCube(firstMonomial) && isPerfectCube(secondMonomial);
        }
    }
    return result;
}

bool isPerfectSquare(Monomial const& monomial)
{
    return isPerfectNthPower(monomial, 2);
}

bool isPerfectCube(Monomial const& monomial)
{
    return isPerfectNthPower(monomial, 3);
}

bool isPerfectNthPower(Monomial const& monomial, unsigned int const nthPower)
{
    AlbaNumber constant(monomial.getConstantConstReference());
    bool result(false);
    if(constant.isIntegerType() && mathHelper::isPerfectNthPower(constant, nthPower))
    {
        result = areExponentsDivisible(monomial, nthPower);
    }
    return result;
}

bool areExponentsDivisible(Monomial const& monomial, unsigned int const divisor)
{
    bool result(true);
    for(Monomial::VariableExponentPair const& variableExponentPair : monomial.getVariablesToExponentsMapConstReference())
    {
        if(!variableExponentPair.second.isIntegerType()
                || !isDivisible(variableExponentPair.second.getInteger(), divisor))
        {
            result=false;
            break;
        }
    }
    return result;
}

bool areAllMonomialsFoundInMonomialsWithExponentsInOrder(
        Monomials const& monomialsToCheck,
        Monomials const& monomialsWithExponentsInOrder)
{
    Polynomial polynomialWithExponentsInOrder(monomialsWithExponentsInOrder);
    bool areAllMonomialsFoundInPolynomialWithExponentsInOrder(false);
    for(Monomial const& monomialToCheck : monomialsToCheck)
    {
        if(polynomialWithExponentsInOrder.isVariableExponentFound(monomialToCheck))
        {
            areAllMonomialsFoundInPolynomialWithExponentsInOrder = true;
            break;
        }
    }

    return areAllMonomialsFoundInPolynomialWithExponentsInOrder;
}

void simplifyPolynomialThenEmplaceBack(Polynomials & polynomials, Polynomial const& polynomial)
{
    Polynomial simplifiedPolynomial(polynomial);
    simplifiedPolynomial.simplify();
    polynomials.emplace_back(simplifiedPolynomial);
}

Monomials getMonomialsWithExponentsInOrder(
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

AlbaNumbers getCoefficientsInMonomialsWithExponentsInOrder(
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

AlbaNumbers calculateQuadraticRoots(AlbaNumber const& a, AlbaNumber const& b, AlbaNumber const& c)
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

unsigned int calculateExponentDivisor(
        Monomial const& firstMonomial,
        Monomial const& lastMonomial)
{
    AlbaNumber maxExponent = max(firstMonomial.getMaxExponent(), lastMonomial.getMaxExponent());
    unsigned int exponentDivisor = getAbsoluteValue(maxExponent.getInteger());
    for(;exponentDivisor>2; exponentDivisor--)
    {
        if(areExponentsDivisible(firstMonomial, exponentDivisor)
                && areExponentsDivisible(lastMonomial, exponentDivisor))
        {
            break;
        }    }
    return exponentDivisor;
}
}

}

}
