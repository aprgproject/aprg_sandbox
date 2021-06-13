#include "Factorization.hpp"

#include <Math/AlbaMathHelper.hpp>
#include <Utilities.hpp>

#include <algorithm>


#include <Debug/AlbaDebug.hpp>

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
    ALBA_PRINT1(polynomial.getDisplayableString());
    Polynomials polynomials(factorizeCommonMonomial(polynomial));
    if(polynomials.size() == 1){polynomials = factorizeDifferenceOfSquares(polynomial); }
    if(polynomials.size() != 1)
    {
        polynomials = factorizeForPolynomials(polynomials);
    }
    for(Polynomial const& currentPolynomial : polynomials)
    {
        ALBA_PRINT1(currentPolynomial.getDisplayableString());
    }
    return polynomials;
}

Polynomials factorizeForPolynomials(Polynomials const& polynomials)
{
    Polynomials result;
    for(Polynomial const& currentPolynomial : polynomials)
    {
        ALBA_PRINT1(currentPolynomial.getDisplayableString());
        Polynomials factorizedPolynomials(factorize(currentPolynomial));
        if(factorizedPolynomials.size() == 1)
        {
            simplifyPolynomialThenEmplaceBack(result, currentPolynomial);
        }
        else
        {
            copy(factorizedPolynomials.cbegin(), factorizedPolynomials.cend(), back_inserter(result));
        }
    }
    return result;
}

Polynomials factorizeCommonMonomial(Polynomial const& polynomial)
{
    bool isFactorized(false);
    Polynomials result;
    if(!polynomial.isOneMonomial())
    {
        Monomial commonMonomial(getCommonMonomialInMonomials(polynomial.getMonomialsConstReference()));
        commonMonomial.simplify();
        if(!commonMonomial.isOne())
        {
            Polynomial reducedPolynomial(polynomial);
            reducedPolynomial.divideMonomial(commonMonomial);
            reducedPolynomial.simplify();
            simplifyPolynomialThenEmplaceBack(result, createPolynomialFromMonomial(commonMonomial));
            simplifyPolynomialThenEmplaceBack(result, reducedPolynomial);
            isFactorized = true;
        }
    }
    if(!isFactorized)
    {
        simplifyPolynomialThenEmplaceBack(result, polynomial);
    }
    return result;
}

Polynomials factorizeDifferenceOfSquares(Polynomial const& polynomial)
{
    bool isFactorized(false);
    Polynomials result;
    ALBA_PRINT1(polynomial.getDisplayableString());
    if(isDifferenceOfSquares(polynomial))
    {
        Monomials monomials(polynomial.getMonomialsConstReference());
        Monomial firstMonomial(monomials.at(0));
        Monomial secondMonomial(monomials.at(1));
        ALBA_PRINT2(firstMonomial.getDisplayableString(), secondMonomial.getDisplayableString());
        secondMonomial.multiplyNumber(-1);
        ALBA_PRINT2(firstMonomial.getDisplayableString(), secondMonomial.getDisplayableString());
        ALBA_PRINT2((firstMonomial.getConstantConstReference() >= 0), (secondMonomial.getConstantConstReference() >= 0));
        if(firstMonomial.getConstantConstReference() >= 0
                && secondMonomial.getConstantConstReference() >= 0)
        {
            firstMonomial.raiseToPowerNumber(AlbaNumber(1, 2));
            secondMonomial.raiseToPowerNumber(AlbaNumber(1, 2));
            ALBA_PRINT2(firstMonomial.getDisplayableString(), secondMonomial.getDisplayableString());
            simplifyPolynomialThenEmplaceBack(result, Polynomial{firstMonomial, secondMonomial});
            secondMonomial.multiplyNumber(-1);
            simplifyPolynomialThenEmplaceBack(result, Polynomial{firstMonomial, secondMonomial});
            isFactorized = true;
        }
        else if(firstMonomial.getConstantConstReference() <= 0
                && secondMonomial.getConstantConstReference() <= 0)
        {
            firstMonomial.multiplyNumber(-1);
            secondMonomial.multiplyNumber(-1);
            firstMonomial.raiseToPowerNumber(AlbaNumber(1, 2));
            secondMonomial.raiseToPowerNumber(AlbaNumber(1, 2));
            ALBA_PRINT2(firstMonomial.getDisplayableString(), secondMonomial.getDisplayableString());
            simplifyPolynomialThenEmplaceBack(result, Polynomial{firstMonomial, secondMonomial});
            secondMonomial.multiplyNumber(-1);
            simplifyPolynomialThenEmplaceBack(result, Polynomial{firstMonomial, secondMonomial});
            isFactorized = true;
        }
    }
    if(!isFactorized)
    {
        simplifyPolynomialThenEmplaceBack(result, polynomial);
    }
    return result;
}

bool isDifferenceOfSquares(Polynomial const& polynomial)
{
    bool result(false);
    Monomials monomials(polynomial.getMonomialsConstReference());
    if(monomials.size() == 2)
    {
        Monomial firstMonomial(monomials.at(0));
        Monomial secondMonomial(monomials.at(1));
        secondMonomial.multiplyNumber(-1);
        ALBA_PRINT1(firstMonomial.getDisplayableString());
        ALBA_PRINT1(secondMonomial.getDisplayableString());
        bool isProductPositive = getSign(firstMonomial.getConstantConstReference())
                *getSign(secondMonomial.getConstantConstReference()) == 1;
        ALBA_PRINT1(isProductPositive);
        ALBA_PRINT1(isPerfectSquare(firstMonomial));
        ALBA_PRINT1(isPerfectSquare(secondMonomial));
        result = isProductPositive
                && isPerfectSquare(firstMonomial)
                && isPerfectSquare(secondMonomial);
    }
    return result;
}

bool isPerfectSquare(Monomial const& monomial)
{
    AlbaNumber constant(monomial.getConstantConstReference());
    bool result(false);
    if(constant.isIntegerType() && mathHelper::isPerfectSquare(constant))
    {
        result = true;
        for(Monomial::VariableExponentPair const& variableExponentPair : monomial.getVariablesToExponentsMapConstReference())
        {
            if(!variableExponentPair.second.isIntegerType()
                    || !isDivisible(variableExponentPair.second.getInteger(), 2))
            {
                result=false;
                break;
            }
        }
    }
    return result;
}

bool isPerfectCube(Monomial const& monomial)
{
    AlbaNumber constant(monomial.getConstantConstReference());
    bool result(false);
    if(constant.isIntegerType() && mathHelper::isPerfectCube(constant))
    {
        result = true;
        for(Monomial::VariableExponentPair const& variableExponentPair : monomial.getVariablesToExponentsMapConstReference())
        {
            if(!variableExponentPair.second.isIntegerType()
                    || !isDivisible(variableExponentPair.second.getInteger(), 3))
            {
                result=false;
                break;
            }
        }
    }
    return result;
}

void simplifyPolynomialThenEmplaceBack(Polynomials & polynomials, Polynomial const& polynomial)
{
    Polynomial simplifiedPolynomial(polynomial);
    simplifiedPolynomial.simplify();
    ALBA_PRINT1(simplifiedPolynomial.getDisplayableString());
    polynomials.emplace_back(simplifiedPolynomial);
}

}

}

}
