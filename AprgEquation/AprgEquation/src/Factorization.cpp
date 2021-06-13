#include "Factorization.hpp"

#include <Math/AlbaMathHelper.hpp>
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
    if(result.size() != 1)
    {
        result = factorizePolynomials(result);
    }
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
        {            copy(factorizedPolynomials.cbegin(), factorizedPolynomials.cend(), back_inserter(result));
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
                factorizeCommonMonomialAndReturnEmptyIfNotFactorized(polynomial),
                polynomial);
}

Polynomials factorizeDifferenceOfSquares(Polynomial const& polynomial)
{
    return returnPolynomialsOrSinglePolynomialIfEmpty(
                factorizeDifferenceOfSquaresAndReturnEmptyIfNotFactorized(polynomial),
                polynomial);
}

Polynomials factorizeDifferenceOfCubes(Polynomial const& polynomial)
{
    return returnPolynomialsOrSinglePolynomialIfEmpty(
                factorizeDifferenceOfCubesAndReturnEmptyIfNotFactorized(polynomial),
                polynomial);
}

Polynomials factorizeSumOfCubes(Polynomial const& polynomial)
{
    return returnPolynomialsOrSinglePolynomialIfEmpty(
                factorizeSumOfCubesAndReturnEmptyIfNotFactorized(polynomial),
                polynomial);
}

Polynomials factorizeIncreasingAndDecreasingExponentsForm(Polynomial const& polynomial)
{
    return returnPolynomialsOrSinglePolynomialIfEmpty(
                factorizeIncreasingAndDecreasingExponentsFormIfNotFactorized(polynomial),
                polynomial);
}

Polynomials factorizeCommonMonomialAndReturnEmptyIfNotFactorized(Polynomial const& polynomial)
{
    Polynomials result;
    if(!polynomial.isOneMonomial())
    {
        Monomial commonMonomial(getCommonMonomialInMonomials(polynomial.getMonomialsConstReference()));
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

Polynomials factorizeDifferenceOfSquaresAndReturnEmptyIfNotFactorized(Polynomial const& polynomial)
{
    Polynomials result;
    if(isDifferenceOfSquares(polynomial))
    {
        addFactorsOfDifferenceOfSquares(result, polynomial);
    }
    return result;
}

Polynomials factorizeDifferenceOfCubesAndReturnEmptyIfNotFactorized(Polynomial const& polynomial)
{
    Polynomials result;
    if(isDifferenceOfCubes(polynomial))
    {
        addFactorsOfDifferenceOfCubes(result, polynomial);
    }
    return result;
}

Polynomials factorizeSumOfCubesAndReturnEmptyIfNotFactorized(Polynomial const& polynomial)
{
    Polynomials result;
    if(isSumOfCubes(polynomial))
    {
        addFactorsOfSumOfCubes(result, polynomial);
    }
    return result;
}

Polynomials factorizeIncreasingAndDecreasingExponentsFormIfNotFactorized(Polynomial const& polynomial)
{
    Polynomials result;
    Monomials monomials(polynomial.getMonomialsConstReference());
    if(monomials.size() > 1)
    {
        Monomial firstMonomial(monomials.front());
        Monomial lastMonomial(monomials.back());
        unsigned int divisor=2;
        while(areExponentsDivisible(firstMonomial, divisor)
              && areExponentsDivisible(lastMonomial, divisor))
        {
            divisor++;
        }
        divisor--;
        if(areExponentsDivisible(firstMonomial, divisor)
                && areExponentsDivisible(lastMonomial, divisor))
        {
            firstMonomial.setConstant(1);
            lastMonomial.setConstant(1);
            firstMonomial.raiseToPowerNumber(AlbaNumber(1, divisor));
            lastMonomial.raiseToPowerNumber(AlbaNumber(1, divisor));
            Monomials monomialsWithExponentsInOrder;
            for(unsigned int i=0; i<=divisor; i++)
            {
                Monomial firstPart(firstMonomial);
                firstPart.raiseToPowerNumber(divisor-i);
                Monomial secondPart(lastMonomial);
                secondPart.raiseToPowerNumber(i);
                Monomial product(firstPart);
                product.multiplyMonomial(secondPart);
                product.simplify();
                monomialsWithExponentsInOrder.emplace_back(product);
            }
            Polynomial polynomialWithExponentsInOrder(monomialsWithExponentsInOrder);
            bool areAllMonomialsFoundInPolynomialWithExponentsInOrder(false);
            for(Monomial const& monomialToCheck : monomials)
            {
                if(polynomialWithExponentsInOrder.isVariableExponentFound(monomialToCheck))
                {
                    areAllMonomialsFoundInPolynomialWithExponentsInOrder = true;
                    break;
                }
            }
            if(areAllMonomialsFoundInPolynomialWithExponentsInOrder)
            {
                AlbaNumbers coefficients;
                for(Monomial const& monomialWithExponentInOrder : monomialsWithExponentsInOrder)
                {
                    coefficients.emplace_back(
                                polynomial.getCoefficientOfVariableExponent(monomialWithExponentInOrder));
                }
                if(divisor==2 && coefficients.size() == 3)
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
                            AlbaNumber::FractionData firstFractionData(aCoefficient.getFractionData());
                            AlbaNumber::FractionData secondFractionData(firstRootSecondCoefficient.getFractionData());
                            unsigned multiplier = getGreatestCommonFactor(firstFractionData.numerator, secondFractionData.denominator);
                            firstRootFirstCoefficient = firstRootFirstCoefficient * multiplier;
                            firstRootSecondCoefficient = firstRootSecondCoefficient * multiplier;
                            aCoefficient = aCoefficient / multiplier;
                        }
                        if(aCoefficient.isIntegerOrFractionType() && secondRootSecondCoefficient.isIntegerOrFractionType())
                        {
                            AlbaNumber::FractionData firstFractionData(aCoefficient.getFractionData());
                            AlbaNumber::FractionData secondFractionData(secondRootSecondCoefficient.getFractionData());
                            unsigned multiplier = getGreatestCommonFactor(firstFractionData.numerator, secondFractionData.denominator);
                            secondRootFirstCoefficient = secondRootFirstCoefficient * multiplier;
                            secondRootSecondCoefficient = secondRootSecondCoefficient * multiplier;
                            aCoefficient = aCoefficient / multiplier;
                        }
                        if(aCoefficient != 1)
                        {
                            simplifyPolynomialThenEmplaceBack(result, Polynomial{Monomial(aCoefficient, {})});
                            aCoefficient=aCoefficient/aCoefficient;
                        }

                        Monomial firstRootFirstMonomial(firstMonomial);
                        Monomial firstRootSecondMonomial(lastMonomial);
                        Monomial secondRootFirstMonomial(firstMonomial);
                        Monomial secondRootSecondMonomial(lastMonomial);
                        firstRootFirstMonomial.setConstant(firstRootFirstCoefficient);
                        firstRootSecondMonomial.setConstant(firstRootSecondCoefficient);
                        secondRootFirstMonomial.setConstant(secondRootFirstCoefficient);
                        secondRootSecondMonomial.setConstant(secondRootSecondCoefficient);
                        simplifyPolynomialThenEmplaceBack(result, Polynomial{firstRootFirstMonomial, firstRootSecondMonomial});
                        simplifyPolynomialThenEmplaceBack(result, Polynomial{secondRootFirstMonomial, secondRootSecondMonomial});
                    }
                }
            }
        }
    }
    return result;
}

void addFactorsOfDifferenceOfSquares(Polynomials & result, Polynomial const& polynomial)
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
    Monomials monomials(polynomial.getMonomialsConstReference());    if(monomials.size() == 2)
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
    return result;}

void simplifyPolynomialThenEmplaceBack(Polynomials & polynomials, Polynomial const& polynomial)
{
    Polynomial simplifiedPolynomial(polynomial);
    simplifiedPolynomial.simplify();
    polynomials.emplace_back(simplifiedPolynomial);
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

}

}

}