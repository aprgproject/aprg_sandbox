#include "FactorizationOfPolynomial.hpp"

#include <Algebra/Factorization/FactorizationBySplitting.hpp>
#include <Algebra/Factorization/FactorizationOfIncreasingAndDecreasingExponentForm.hpp>
#include <Algebra/Factorization/FactorizationUsingPatterns.hpp>
#include <Algebra/Factorization/FactorizationUtilities.hpp>
#include <Algebra/Utilities.hpp>

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
    Polynomials result{polynomialToFactorize};
    if(!polynomialToFactorize.isOneMonomial())
    {
        result = factorizeCommonMonomial(polynomialToFactorize);
        if(result.size() == 1){result = factorizeUsingPatterns(polynomialToFactorize); }
        if(result.size() == 1){result = factorizeIncreasingAndDecreasingExponentsForm(polynomialToFactorize); }
        if(result.size() == 1){result = factorizeBySplittingToSmallerPolynomials(polynomialToFactorize); }
        if(result.size() != 1)
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
        if(!gcfMonomial.isOne())
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
