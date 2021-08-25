#include "FactorizationOfPolynomial.hpp"

#include <Algebra/Factorization/FactorizationBySplitting.hpp>
#include <Algebra/Factorization/FactorizationOfIncreasingAndDecreasingExponentForm.hpp>
#include <Algebra/Factorization/FactorizationUsingPatterns.hpp>
#include <Algebra/Factorization/FactorizationUtilities.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>
#include <Algebra/Term/Utilities/MonomialHelpers.hpp>
#include <Algebra/Term/Utilities/ValueCheckingHelpers.hpp>

using namespace std;

namespace alba
{

namespace algebra
{

namespace Factorization
{

Polynomials factorizeAPolynomial(Polynomial const& polynomial)
{
    Polynomial polynomialToFactorize(polynomial);
    polynomialToFactorize.simplify();
    Polynomials result;
    if(doesNotNeedToBeFactorized(polynomial))
    {
        result.emplace_back(polynomialToFactorize);
    }    else
    {
        result = factorizeCommonMonomialIfPossible(polynomialToFactorize);
        if(result.empty())        {
            result = factorizeUsingPatternsIfPossible(polynomialToFactorize);
        }
        if(result.empty())
        {
            result = factorizeIncreasingAndDecreasingExponentsFormIfPossible(polynomialToFactorize);
        }
        if(result.empty() && polynomialToFactorize.getMonomialsConstReference().size() > 2)
        {
            result = factorizeBySplittingToSmallerPolynomialsIfPossible(polynomialToFactorize);
        }
        if(result.empty())
        {
            result.emplace_back(polynomialToFactorize);        }
        else if(result.size() > 1)
        {
            result = factorizePolynomials(result);
        }
    }
    return result;
}

Polynomials factorizePolynomials(Polynomials const& polynomials)
{
    Polynomials result;
    for(Polynomial const& polynomialToFactorize : polynomials)
    {
        Polynomials factorizedPolynomials(factorizeAPolynomial(polynomialToFactorize));
        if(factorizedPolynomials.size() == 1)
        {
            simplifyPolynomialThenEmplaceBackIfNotEmpty(result, polynomialToFactorize);
        }
        else
        {
            result.reserve(result.size()+factorizedPolynomials.size());
            copy(factorizedPolynomials.cbegin(), factorizedPolynomials.cend(), back_inserter(result));
        }
    }
    return result;
}

Polynomials factorizeCommonMonomial(Polynomial const& polynomial)
{
    return returnPolynomialsOrSinglePolynomialIfEmpty(
                factorizeCommonMonomialIfPossible(polynomial),
                polynomial);
}

Polynomials factorizeCommonMonomialIfPossible(Polynomial const& polynomial)
{
    Polynomials result;
    if(!polynomial.isOneMonomial())
    {
        Monomial gcfMonomial(getGcfMonomialInMonomials(polynomial.getMonomialsConstReference()));
        if(!isTheValue(gcfMonomial, 1))
        {
            Polynomial reducedPolynomial(polynomial);
            reducedPolynomial.divideMonomial(gcfMonomial);
            reducedPolynomial.simplify();
            simplifyPolynomialThenEmplaceBackIfNotEmpty(result, createPolynomialFromMonomial(gcfMonomial));
            simplifyPolynomialThenEmplaceBackIfNotEmpty(result, reducedPolynomial);
        }
    }
    return result;
}

}

}

}
