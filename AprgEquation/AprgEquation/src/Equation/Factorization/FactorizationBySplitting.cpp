#include "FactorizationBySplitting.hpp"

#include <Equation/Constructs/PolynomialOverPolynomial.hpp>
#include <Equation/Factorization/Factorization.hpp>
#include <Equation/Factorization/FactorizationUtilities.hpp>
#include <Equation/Utilities.hpp>

using namespace std;

namespace alba
{

namespace equation
{

namespace Factorization
{

Polynomials factorizeBySplittingToSmallerPolynomials(Polynomial const& polynomial)
{
    return returnPolynomialsOrSinglePolynomialIfEmpty(
                factorizeIfPossibleBySplittingToSmallerPolynomials(polynomial),
                polynomial);
}

Polynomials factorizeIfPossibleBySplittingToSmallerPolynomials(Polynomial const& polynomial)
{
    Polynomials result;
    result = factorizeIfPossibleBySplittingByPolynomialDegree(polynomial);
    if(result.empty())
    {
        result = factorizeIfPossibleBySplittingByDivisibilityOfExponents(polynomial);
        if(result.empty())
        {
            result = factorizeIfPossibleBySplittingByFirstVariable(polynomial);
        }
    }
    return result;
}

Polynomials factorizeIfPossibleBySplittingByPolynomialDegree(Polynomial const& polynomial)
{
    Polynomials result;
    Polynomials smallerPolynomials(splitPolynomialsByPolynomialDegree(polynomial));
    result = factorizeSmallerPolynomials(smallerPolynomials);
    return result;
}

Polynomials factorizeIfPossibleBySplittingByDivisibilityOfExponents(Polynomial const& polynomial)
{
    Polynomials result;
    Polynomials smallerPolynomials(splitPolynomialsByDivisibilityOfExponents(polynomial));
    result = factorizeSmallerPolynomials(smallerPolynomials);
    return result;
}

Polynomials factorizeIfPossibleBySplittingByFirstVariable(Polynomial const& polynomial)
{
    Polynomials result;
    Polynomials smallerPolynomials(splitPolynomialsByFirstVariable(polynomial));
    result = factorizeSmallerPolynomials(smallerPolynomials);
    return result;
}

Polynomials splitPolynomialsByPolynomialDegree(Polynomial const& polynomial)
{
    Polynomials result;
    Monomials monomials(polynomial.getMonomialsConstReference());
    Polynomial partialPolynomial;
    AlbaNumber currentDegree;
    bool isFirst(true);
    for(Monomial const& monomial : monomials)
    {
        AlbaNumber monomialDegree(monomial.getDegree());
        if(isFirst)
        {
            currentDegree = monomialDegree;
            isFirst = false;
        }
        if(currentDegree != monomialDegree)
        {
            currentDegree = monomialDegree;
            result.emplace_back(partialPolynomial);
            partialPolynomial.clear();
        }
        partialPolynomial.addMonomial(monomial);
    }
    simplifyPolynomialThenEmplaceBackIfNotEmpty(result, partialPolynomial);
    return result;
}

Polynomials splitPolynomialsByDivisibilityOfExponents(Polynomial const& polynomial)
{
    Polynomials result;
    Polynomials collectedPolynomials;
    AlbaNumber polynomialDegree(polynomial.getMaxDegree());
    if(polynomialDegree.isIntegerType() && polynomialDegree > 0)
    {
        Monomials remainingMonomials = polynomial.getMonomialsConstReference();
        unsigned int degree = static_cast<unsigned int>(polynomialDegree.getInteger());
        for(; degree>=2; degree--)
        {
            Polynomial partialPolynomial;
            Monomials collectedMonomials;
            for(Monomial const& remainingMonomial : remainingMonomials)
            {
                if(areExponentsDivisible(remainingMonomial, degree))
                {
                    partialPolynomial.addMonomial(remainingMonomial);
                }
                else
                {
                    collectedMonomials.emplace_back(remainingMonomial);
                }
            }
            simplifyPolynomialThenEmplaceBackIfNotEmpty(collectedPolynomials, partialPolynomial);
            remainingMonomials = collectedMonomials;
        }
        simplifyPolynomialThenEmplaceBackIfNotEmpty(collectedPolynomials, Polynomial(remainingMonomials));
    }
    if(collectedPolynomials.size() > 1)
    {
        result = collectedPolynomials;
    }
    return result;
}

Polynomials splitPolynomialsByFirstVariable(Polynomial const& polynomial)
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
    simplifyPolynomialThenEmplaceBackIfNotEmpty(result, partialPolynomial);
    return result;
}

Polynomials factorizeSmallerPolynomials(Polynomials const& smallerPolynomials)
{
    Polynomials result;
    result = factorizeSmallerPolynomialsByFactoringOutCommonFactors(smallerPolynomials);
    if(result.empty())
    {
        result = factorizeSmallerPolynomialsBySubstitutingCommonFactorsToVariables(smallerPolynomials);
    }
    return result;
}

Polynomials factorizeSmallerPolynomialsByFactoringOutCommonFactors(Polynomials const& smallerPolynomials)
{
    Polynomials result;
    if(smallerPolynomials.size() > 1)
    {
        Polynomials commonFactors(getCommonFactorsInThesePolynomials(smallerPolynomials));
        if(!commonFactors.empty())
        {
            Polynomials remainingSmallerPolynomials(getPolynomialsWithRemovedCommonFactors(smallerPolynomials, commonFactors));
            combinePolynomialsByAdditionAndThenEmplaceBack(result, remainingSmallerPolynomials);
            for(Polynomial const& commonFactor : commonFactors)
            {
                simplifyPolynomialThenEmplaceBackIfNotEmpty(result, commonFactor);
            }
        }
    }
    return result;
}

Polynomials factorizeSmallerPolynomialsBySubstitutingCommonFactorsToVariables(Polynomials const& smallerPolynomials)
{
    Polynomials result;
    SubstitutionOfVariablesToExpressions variableSubstitution;
    if(smallerPolynomials.size() > 1)
    {
        Polynomial newPolynomialWithVariables(getNewPolynomialWithVariables(variableSubstitution, smallerPolynomials));
        if(!variableSubstitution.isEmpty())
        {
            result = factorizePolynomialWithVariables(newPolynomialWithVariables, variableSubstitution);
        }
    }
    return result;
}

Polynomials factorizePolynomialWithVariables(
        Polynomial const& newPolynomialWithVariables,
        SubstitutionOfVariablesToExpressions const& variableSubstitution)
{
    Polynomials result;
    Polynomials factorizedPolynomialsWithVariables(factorize(newPolynomialWithVariables));
    if(factorizedPolynomialsWithVariables.size() > 1)
    {
        for(Polynomial const& factorizedPolynomialWithVariables : factorizedPolynomialsWithVariables)
        {
            Polynomial finalPolynomial(createPolynomialIfPossible(variableSubstitution.performSubstitutionTo(factorizedPolynomialWithVariables)));
            simplifyPolynomialThenEmplaceBackIfNotEmpty(result, finalPolynomial);
        }
    }
    return result;
}

Polynomials getCommonFactorsInThesePolynomials(Polynomials const& smallerPolynomials)
{
    Polynomials commonFactors;
    bool isFirst(true);
    for(Polynomial const& smallerPolynomial : smallerPolynomials)
    {
        Polynomials commonFactorsOfAPolynomial(factorize(smallerPolynomial));
        if(isFirst)
        {
            commonFactors = commonFactorsOfAPolynomial;
            isFirst = false;
        }
        else
        {
            updateToGetSubsetOfFactors(commonFactors, commonFactorsOfAPolynomial);
        }
    }
    return commonFactors;
}

Polynomial getNewPolynomialWithVariables(SubstitutionOfVariablesToExpressions & variableSubstitution, Polynomials const& smallerPolynomials)
{
    Polynomial newPolynomialWithVariables;
    for(Polynomial const& smallerPolynomial : smallerPolynomials)
    {
        Polynomial newSmallerPolynomialWithVariables(createPolynomialFromConstant(1));
        Polynomials factors(factorize(smallerPolynomial));
        for(Polynomial const& factor : factors)
        {
            if(factor.isOneMonomial())
            {
                newSmallerPolynomialWithVariables.multiplyMonomial(factor.getFirstMonomial());
            }
            else
            {
                string variableNameForSubstitution(createVariableNameForSubstitution(factor));
                Expression polynomialExpressionForFactor(createOrCopyExpressionFromATerm(Term(factor)));
                variableSubstitution.putVariableWithExpression(variableNameForSubstitution, polynomialExpressionForFactor);
                newSmallerPolynomialWithVariables.multiplyMonomial(createMonomialFromVariable(Variable(variableNameForSubstitution)));
            }
        }
        newPolynomialWithVariables.addPolynomial(newSmallerPolynomialWithVariables);
    }
    return newPolynomialWithVariables;
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

void updateToGetSubsetOfFactors(Polynomials & commonFactors, Polynomials const& commonFactorsOfAPolynomial)
{
    Polynomials previousCommonFactors(commonFactors);
    Polynomials currentCommonFactors(commonFactorsOfAPolynomial);
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

void combinePolynomialsByAdditionAndThenEmplaceBack(Polynomials & result, Polynomials const& smallerPolynomials)
{
    Polynomial combinedPolynomial;
    for(Polynomial const& smallerPolynomial : smallerPolynomials)
    {
        combinedPolynomial.addPolynomial(smallerPolynomial);
    }
    simplifyPolynomialThenEmplaceBackIfNotEmpty(result, combinedPolynomial);
}

}

}

}