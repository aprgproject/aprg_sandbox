#include "FactorizationOfTerm.hpp"

#include <Algebra/Factorization/FactorizationOfPolynomial.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>

using namespace std;

namespace alba
{

namespace algebra
{

namespace Factorization
{

Terms factorizeTerm(Term const& term)
{
    Terms result;
    if(term.isPolynomial())
    {
        Polynomial simplifiedPolynomial(term.getPolynomialConstReference());
        simplifiedPolynomial.simplify();
        Polynomials polynomialFactors(factorizeAPolynomial(simplifiedPolynomial));
        for(Polynomial const& polynomialFactor : polynomialFactors)
        {
            result.emplace_back(simplifyAndConvertPolynomialToSimplestTerm(polynomialFactor));
        }
    }
    else
    {
        result.emplace_back(term);
    }
    return result;
}

Terms factorizeTerms(Terms const& terms)
{
    Terms result;
    for(Term const& termToFactorize : terms)
    {
        Terms factorizedTerms(factorizeTerm(termToFactorize));
        result.reserve(result.size() + factorizedTerms.size());
        copy(factorizedTerms.cbegin(), factorizedTerms.cend(), back_inserter(result));
    }
    return result;
}

}

}

}
