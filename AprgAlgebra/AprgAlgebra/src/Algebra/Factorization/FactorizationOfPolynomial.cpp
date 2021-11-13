#include "FactorizationOfPolynomial.hpp"

#include <Algebra/Factorization/FactorizationBySplitting.hpp>
#include <Algebra/Factorization/FactorizationOfIncreasingAndDecreasingExponentForm.hpp>
#include <Algebra/Factorization/FactorizationUsingPatterns.hpp>
#include <Algebra/Factorization/FactorizationConfiguration.hpp>
#include <Algebra/Factorization/FactorizationUtilities.hpp>
#include <Algebra/Retrieval/VariableNamesRetriever.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/MonomialHelpers.hpp>
#include <Algebra/Term/Utilities/PolynomialHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>

#include <algorithm>

using namespace std;

namespace alba
{

namespace algebra
{

namespace Factorization
{

Polynomials factorizeAPolynomial(Polynomial const& polynomial)
{
    Polynomials result;
    factorizePolynomialsAndPutToResult(result, {polynomial});
    return result;
}

Polynomials factorizePolynomials(Polynomials const& polynomials)
{
    Polynomials result;
    factorizePolynomialsAndPutToResult(result, polynomials);
    return result;
}

Polynomials factorizeCommonMonomial(Polynomial const& polynomial)
{
    Polynomials result;
    factorizeCommonMonomialIfPossible(result, polynomial);
    simplifyAndEmplaceBackPolynomialIfListIsEmpty(result, polynomial);
    return result;
}

void factorizeCommonMonomialIfPossible(Polynomials & result, Polynomial const& polynomial)
{
    if(!isOneMonomial(polynomial))
    {
        Monomial gcfMonomial(getGcfMonomialInMonomials(polynomial.getMonomialsConstReference()));
        if(!isTheValue(gcfMonomial, 1))
        {
            Polynomial reducedPolynomial(polynomial);
            reducedPolynomial.divideMonomial(gcfMonomial);
            reducedPolynomial.simplify();
            simplifyThenEmplaceBackIfPolynomialIsNotEmpty(result, createPolynomialFromMonomial(gcfMonomial));
            simplifyThenEmplaceBackIfPolynomialIsNotEmpty(result, reducedPolynomial);
        }
    }
}

void factorizePolynomialsAndPutToResult(Polynomials & result, Polynomials const& polynomials)
{
    Polynomials polynomialsToFactorize(polynomials);
    for(unsigned int i=0; i<polynomialsToFactorize.size(); i++)
    {
        Polynomial const& polynomial(polynomialsToFactorize.at(i));
        Polynomial simplifiedPolynomial(polynomial);
        simplifiedPolynomial.simplify();
        if(doesNotNeedToBeFactorized(simplifiedPolynomial))
        {
            result.emplace_back(simplifiedPolynomial);
        }
        else
        {
            unsigned int const originalSize(polynomialsToFactorize.size());
            unsigned int deltaSize = polynomialsToFactorize.size() - originalSize;
            tryToFactorizeCommonMonomial(polynomialsToFactorize, deltaSize, simplifiedPolynomial, originalSize);
            tryToFactorizeUsingPatterns(polynomialsToFactorize, deltaSize, simplifiedPolynomial, originalSize);
            tryToFactorizeIncreasingAndDecreasingExponentsForm(polynomialsToFactorize, deltaSize, simplifiedPolynomial, originalSize);
            tryToFactorizeBySplittingToSmallerPolynomials(polynomialsToFactorize, deltaSize, simplifiedPolynomial, originalSize);

            if(deltaSize == 0)
            {
                result.emplace_back(simplifiedPolynomial);
            }
            else if(deltaSize == 1)
            {
                polynomialsToFactorize.pop_back();
            }
        }
    }
}

void tryToFactorizeCommonMonomial(
        Polynomials & polynomialsToFactorize,
        unsigned int & deltaSize,
        Polynomial const& simplifiedPolynomial,
        unsigned int const originalSize)
{
    if(deltaSize == 0)
    {
        Polynomials factorizedPolynomials;
        factorizeCommonMonomialIfPossible(factorizedPolynomials, simplifiedPolynomial);
        putFactorizedPolynomialsIfPossible(polynomialsToFactorize, factorizedPolynomials);
        deltaSize = getDeltaSize(polynomialsToFactorize, originalSize);
    }
}

void tryToFactorizeUsingPatterns(
        Polynomials & polynomialsToFactorize,
        unsigned int & deltaSize,
        Polynomial const& simplifiedPolynomial,
        unsigned int const originalSize)
{
    if(deltaSize == 0 && isFactorizeUsingPatternsNeeded(simplifiedPolynomial))
    {
        Polynomials factorizedPolynomials;
        factorizeUsingPatternsIfPossible(factorizedPolynomials, simplifiedPolynomial);
        putFactorizedPolynomialsIfPossible(polynomialsToFactorize, factorizedPolynomials);
        deltaSize = polynomialsToFactorize.size() - originalSize;
    }
}

void tryToFactorizeIncreasingAndDecreasingExponentsForm(
        Polynomials & polynomialsToFactorize,
        unsigned int & deltaSize,
        Polynomial const& simplifiedPolynomial,
        unsigned int const originalSize)
{
    if(deltaSize == 0 && isFactorizeIncreasingAndDecreasingExponentsFormNeeded(simplifiedPolynomial))
    {
        Polynomials factorizedPolynomials;
        factorizeIncreasingAndDecreasingExponentsFormIfPossible(factorizedPolynomials, simplifiedPolynomial);
        putFactorizedPolynomialsIfPossible(polynomialsToFactorize, factorizedPolynomials);
        deltaSize = polynomialsToFactorize.size() - originalSize;
    }
}

void tryToFactorizeBySplittingToSmallerPolynomials(
        Polynomials & polynomialsToFactorize,
        unsigned int & deltaSize,
        Polynomial const& simplifiedPolynomial,
        unsigned int const originalSize)
{
    if(deltaSize == 0 && isFactorizeBySplittingToSmallerPolynomialsNeeded(simplifiedPolynomial))
    {
        Polynomials factorizedPolynomials;
        factorizeBySplittingToSmallerPolynomialsIfPossible(factorizedPolynomials, simplifiedPolynomial);
        putFactorizedPolynomialsIfPossible(polynomialsToFactorize, factorizedPolynomials);
        deltaSize = polynomialsToFactorize.size() - originalSize;
    }
}

void putFactorizedPolynomialsIfPossible(
        Polynomials & result,
        Polynomials const& factorizedPolynomials)
{
    bool shouldPutFactorizedPolynomials =
            !(shouldNotFactorizeIfItWouldYieldToPolynomialsWithDoubleValue() && doesOnePolynomialHaveADoubleValue(factorizedPolynomials));
    if(shouldPutFactorizedPolynomials)
    {
        result.reserve(result.size() + factorizedPolynomials.size());
        copy(factorizedPolynomials.cbegin(), factorizedPolynomials.cend(), back_inserter(result));
    }
}

void simplifyAndRemoveEmptyPolynomials(
        Polynomials & polynomials)
{
    for(Polynomial & polynomial : polynomials)
    {
        polynomial.simplify();
    }
    polynomials.erase(remove_if(polynomials.begin(), polynomials.end(), [](Polynomial const& polynomial)
    {
                          return polynomial.isEmpty();
                      }), polynomials.end());
}


unsigned int getDeltaSize(Polynomials const& polynomials, unsigned int const originalSize)
{
    return static_cast<unsigned int>(polynomials.size()) - originalSize;
}

bool isFactorizeUsingPatternsNeeded(Polynomial const& polynomial)
{
    return polynomial.getMonomialsConstReference().size() == 2 && hasAMonomialWithDegreeMoreThanOneOrFractional(polynomial);
}

bool  isFactorizeIncreasingAndDecreasingExponentsFormNeeded(Polynomial const& polynomial)
{
    return hasAMonomialWithDegreeMoreThanOneOrFractional(polynomial);
}

bool isFactorizeBySplittingToSmallerPolynomialsNeeded(Polynomial const& polynomial)
{
    return polynomial.getMonomialsConstReference().size() >= 4 && hasAMonomialWithMultipleVariables(polynomial);
}

}

}

}
