#include "Factorization.hpp"

#include <Equation/Constructs/PolynomialOverPolynomial.hpp>
#include <Equation/Factorization/FactorizationOfIncreasingAndDecreasingExponentForm.hpp>
#include <Equation/Utilities.hpp>
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

Expression factorize(Expression const& expression)
{
    Expression factorizedExpression(expression);
    factorizedExpression.factorize();
    return factorizedExpression;
}

Polynomials factorize(Polynomial const& polynomial)
{
    Polynomial polynomialToFactorize(polynomial);    polynomialToFactorize.simplify();
    Polynomials result(factorizeCommonMonomial(polynomialToFactorize));
    if(result.size() == 1){result = factorizeDifferenceOfSquares(polynomialToFactorize); }
    if(result.size() == 1){result = factorizeDifferenceOfCubes(polynomialToFactorize); }    if(result.size() == 1){result = factorizeSumOfCubes(polynomialToFactorize); }
    if(result.size() == 1){result = factorizeIncreasingAndDecreasingExponentsForm(polynomialToFactorize); }
    if(result.size() == 1){result = factorizeBySplittingSmallerPolynomials(polynomialToFactorize); }
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
    FactorizationOfIncreasingAndDecreasingExponentForm factorization;
    return returnPolynomialsOrSinglePolynomialIfEmpty(
                factorization.factorizeIfPossible(polynomial),
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
    {
        Monomial gcfMonomial(getGcfMonomialInMonomials(polynomial.getMonomialsConstReference()));
        if(!gcfMonomial.isOne())
        {
            Polynomial reducedPolynomial(polynomial);
            reducedPolynomial.divideMonomial(gcfMonomial);
            reducedPolynomial.simplify();
            simplifyPolynomialThenEmplaceBack(result, createPolynomialFromMonomial(gcfMonomial));
            simplifyPolynomialThenEmplaceBack(result, reducedPolynomial);
        }
    }
    return result;
}

Polynomials factorizeDifferenceOfSquaresIfPossible(Polynomial const& polynomial)
{
    Polynomials result;
    if(isDifferenceOfSquares(polynomial))
    {
        addFactorsOfDifferenceOfSquares(result, polynomial);
    }
    return result;
}

Polynomials factorizeDifferenceOfCubesIfPossible(Polynomial const& polynomial)
{
    Polynomials result;
    if(isDifferenceOfCubes(polynomial))
    {
        addFactorsOfDifferenceOfCubes(result, polynomial);
    }
    return result;
}

Polynomials factorizeSumOfCubesIfPossible(Polynomial const& polynomial)
{
    Polynomials result;
    if(isSumOfCubes(polynomial))
    {
        addFactorsOfSumOfCubes(result, polynomial);
    }
    return result;
}

Polynomials factorizeBySplittingSmallerPolynomialsIfPossible(Polynomial const& polynomial)
{
    Polynomials result;
    Polynomials smallerPolynomials(splitPolynomialIntoSmallerPolynomials(polynomial));
    if(smallerPolynomials.size() > 1)
    {
        Polynomials commonFactors(getCommonFactorsInThesePolynomials(smallerPolynomials));
        if(!commonFactors.empty())
        {
            smallerPolynomials = getPolynomialsWithRemovedCommonFactors(smallerPolynomials, commonFactors);
            combinePolynomialsByAdditionAndThenEmplaceBack(result, smallerPolynomials);
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

Polynomials getCommonFactorsInThesePolynomials(Polynomials const& smallerPolynomials)
{
    Polynomials commonFactors;
    bool isFirst(true);
    for(Polynomial const& smallerPolynomial : smallerPolynomials)
    {
        Polynomials currentCommonFactors(factorize(smallerPolynomial));
        if(isFirst)
        {
            commonFactors = currentCommonFactors;
            isFirst = false;
        }
        else
        {
            Polynomials previousCommonFactors(commonFactors);
            commonFactors.clear();
            for(Polynomials::iterator it1=previousCommonFactors.begin(); it1!=previousCommonFactors.end(); it1++)
            {
                bool isFound(false);
                Polynomial const& previousCommonFactor(*it1);
                for(Polynomials::iterator it2=currentCommonFactors.begin(); it2!=currentCommonFactors.end(); it2++)
                {
                    Polynomial const& currentCommonFactor(*it2);
                    if(previousCommonFactor.isOneMonomial() && currentCommonFactor.isOneMonomial())
                    {
                        Monomial gcfMonomial(getGcfMonomialInMonomials({previousCommonFactor.getFirstMonomial(), currentCommonFactor.getFirstMonomial()}));
                        gcfMonomial.simplify();
                        if(!gcfMonomial.isOne())
                        {
                            commonFactors.emplace_back(Polynomial{gcfMonomial});
                            isFound=true;
                        }
                    }
                    else if(previousCommonFactor == currentCommonFactor)
                    {
                        commonFactors.emplace_back(currentCommonFactor);
                        isFound=true;
                    }
                    if(isFound)
                    {
                        currentCommonFactors.erase(it2);
                        break;
                    }
                }
                if(isFound)
                {
                    previousCommonFactors.erase(it1);
                    it1=previousCommonFactors.begin();
                    it1--;
                }
            }
        }
    }
    return commonFactors;
}

Polynomials getPolynomialsWithRemovedCommonFactors(Polynomials const& polynomialsWithCommonFactors, Polynomials const& commonFactors)
{
    Polynomials result;
    for(Polynomial const& polynomialWithCommonFactors : polynomialsWithCommonFactors)
    {
        Polynomial resultPolynomial(polynomialWithCommonFactors);
        for(Polynomial const& commonFactor : commonFactors)
        {
            PolynomialOverPolynomial divideProcess(resultPolynomial, commonFactor);
            PolynomialOverPolynomial::QuotientAndRemainder quotientAndRemainder(divideProcess.divide());
            if(quotientAndRemainder.remainder.isZero())
            {
                resultPolynomial = quotientAndRemainder.quotient;
            }
        }
        result.emplace_back(resultPolynomial);
    }
    return result;
}

void combinePolynomialsByAdditionAndThenEmplaceBack(Polynomials & result, Polynomials const& smallerPolynomials)
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
                || !isDivisible(getAbsoluteValue(variableExponentPair.second.getInteger()), divisor))
        {
            result=false;
            break;
        }
    }
    return result;
}

void simplifyPolynomialThenEmplaceBack(Polynomials & polynomials, Polynomial const& polynomial)
{
    Polynomial simplifiedPolynomial(polynomial);
    simplifiedPolynomial.simplify();
    polynomials.emplace_back(simplifiedPolynomial);
}

}

}

}
