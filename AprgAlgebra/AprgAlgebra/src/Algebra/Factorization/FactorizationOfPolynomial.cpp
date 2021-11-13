#include "FactorizationOfPolynomial.hpp"

#include <Algebra/Factorization/FactorizationBySplitting.hpp>
#include <Algebra/Factorization/FactorizationOfIncreasingAndDecreasingExponentForm.hpp>
#include <Algebra/Factorization/FactorizationUsingPatterns.hpp>
#include <Algebra/Factorization/FactorizationConfiguration.hpp>
#include <Algebra/Factorization/FactorizationUtilities.hpp>
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
    if(!polynomial.isOneMonomial())
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
        if(doesNotNeedToBeFactorized(polynomial))
        {
            result.emplace_back(simplifiedPolynomial);
        }
        else
        {
            auto const originalSize(polynomialsToFactorize.size());
            auto deltaSize = polynomialsToFactorize.size() - originalSize;
            if(deltaSize == 0)
            {
                Polynomials factorizedPolynomials;
                factorizeCommonMonomialIfPossible(factorizedPolynomials, simplifiedPolynomial);
                putFactorizedPolynomialsIfPossible(polynomialsToFactorize, factorizedPolynomials);
                deltaSize = polynomialsToFactorize.size() - originalSize;
            }
            if(deltaSize == 0)
            {
                Polynomials factorizedPolynomials;
                factorizeUsingPatternsIfPossible(factorizedPolynomials, simplifiedPolynomial);
                putFactorizedPolynomialsIfPossible(polynomialsToFactorize, factorizedPolynomials);
                deltaSize = polynomialsToFactorize.size() - originalSize;
            }
            if(deltaSize == 0)
            {
                Polynomials factorizedPolynomials;
                factorizeIncreasingAndDecreasingExponentsFormIfPossible(factorizedPolynomials, simplifiedPolynomial);
                putFactorizedPolynomialsIfPossible(polynomialsToFactorize, factorizedPolynomials);
                deltaSize = polynomialsToFactorize.size() - originalSize;
            }
            if(deltaSize == 0 && simplifiedPolynomial.getMonomialsConstReference().size() > 2)
            {
                Polynomials factorizedPolynomials;
                factorizeBySplittingToSmallerPolynomialsIfPossible(factorizedPolynomials, simplifiedPolynomial);
                putFactorizedPolynomialsIfPossible(polynomialsToFactorize, factorizedPolynomials);
                deltaSize = polynomialsToFactorize.size() - originalSize;
            }

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


}

}

}
