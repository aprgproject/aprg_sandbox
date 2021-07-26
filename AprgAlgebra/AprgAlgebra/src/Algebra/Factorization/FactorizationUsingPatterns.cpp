#include "FactorizationUsingPatterns.hpp"

#include <Algebra/Factorization/FactorizationUtilities.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

using namespace std;

namespace alba
{

namespace algebra
{

namespace Factorization
{

Polynomials factorizeUsingPatterns(Polynomial const& polynomial)
{
    return returnPolynomialsOrSinglePolynomialIfEmpty(
                factorizeUsingPatternsIfPossible(polynomial),
                polynomial);
}

Polynomials factorizeUsingPatternsIfPossible(Polynomial const& polynomial)
{
    Polynomials result;
    result = factorizeDifferenceOfSquaresIfPossible(polynomial);
    if(result.empty())
    {
        result = factorizeDifferenceOfCubesIfPossible(polynomial);
        if(result.empty())
        {
            result = factorizeSumOfCubesIfPossible(polynomial);
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
        simplifyPolynomialThenEmplaceBackIfNotEmpty(result, createPolynomialFromConstant(Constant(-1)));
    }
    firstMonomial.raiseToPowerNumber(AlbaNumber(1, 2));
    secondMonomial.raiseToPowerNumber(AlbaNumber(1, 2));
    simplifyPolynomialThenEmplaceBackIfNotEmpty(result, Polynomial{firstMonomial, secondMonomial});
    secondMonomial.multiplyNumber(-1);
    simplifyPolynomialThenEmplaceBackIfNotEmpty(result, Polynomial{firstMonomial, secondMonomial});
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
        simplifyPolynomialThenEmplaceBackIfNotEmpty(result, createPolynomialFromConstant(Constant(-1)));
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
    simplifyPolynomialThenEmplaceBackIfNotEmpty(result, Polynomial{firstMonomial, secondMonomial});
    simplifyPolynomialThenEmplaceBackIfNotEmpty(result, Polynomial{firstMonomialSquared, productOfFirstAndSecond, secondMonomialSquared});
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
        simplifyPolynomialThenEmplaceBackIfNotEmpty(result, createPolynomialFromConstant(Constant(-1)));
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
    simplifyPolynomialThenEmplaceBackIfNotEmpty(result, Polynomial{firstMonomial, secondMonomial});
    simplifyPolynomialThenEmplaceBackIfNotEmpty(result, Polynomial{firstMonomialSquared, productOfFirstAndSecond, secondMonomialSquared});
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

}

}

}
