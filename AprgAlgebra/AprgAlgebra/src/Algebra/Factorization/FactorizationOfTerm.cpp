#include "FactorizationOfTerm.hpp"

#include <Algebra/Factorization/FactorizationConfiguration.hpp>
#include <Algebra/Factorization/FactorizationOfExpression.hpp>
#include <Algebra/Factorization/FactorizationOfPolynomial.hpp>
#include <Algebra/Term/Utilities/ConvertHelpers.hpp>

using namespace std;

namespace alba {

namespace algebra {

namespace Factorization {

Terms factorizeTerm(Term const& term) { return factorizeTerms({term}); }

Terms factorizeTerms(Terms const& terms) {
    Terms result;
    for (Term const& term : terms) {
        if (term.isPolynomial()) {
            Polynomial simplifiedPolynomial(term.getAsPolynomial());
            simplifiedPolynomial.simplify();
            Polynomials polynomialFactors(factorizeAPolynomial(simplifiedPolynomial));
            for (Polynomial const& polynomialFactor : polynomialFactors) {                result.emplace_back(simplifyAndConvertPolynomialToSimplestTerm(polynomialFactor));
            }
        } else if (term.isExpression()) {
            if (shouldSimplifyExpressionsToFactors()) {
                Terms factors(factorizeAnExpression(term.getAsExpression()));
                result.reserve(result.size() + factors.size());
                copy(factors.cbegin(), factors.cend(), back_inserter(result));
            } else {                result.emplace_back(term);
            }
        } else {
            result.emplace_back(term);        }
    }
    return result;
}

}  // namespace Factorization

}  // namespace algebra

}  // namespace alba
