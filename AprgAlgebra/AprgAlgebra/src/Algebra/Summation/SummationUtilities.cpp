#include "SummationUtilities.hpp"

#include <Algebra/Functions/CommonFunctionLibrary.hpp>
#include <Algebra/Term/Utilities/CreateHelpers.hpp>

using namespace alba::algebra::Functions;
using namespace std;

namespace alba {

namespace algebra {

Term getSummationOfArithmeticSeries(string const& countVariable) {
    // form: Summation of k from 1 to n of k
    return Polynomial{
        Monomial(AlbaNumber::createFraction(1, 2), {{countVariable, 2}}),
        Monomial(AlbaNumber::createFraction(1, 2), {{countVariable, 1}})};
}

Term getSummationOfArithmeticSeriesForSquares(string const& countVariable) {
    // form: Summation of k from 0 to n of k^2
    return Polynomial{
        Monomial(AlbaNumber::createFraction(1, 3), {{countVariable, 3}}),
        Monomial(AlbaNumber::createFraction(1, 2), {{countVariable, 2}}), Monomial(1, {{countVariable, 1}})};
}

Term getSummationOfArithmeticSeriesForCubes(string const& countVariable) {
    // form: Summation of k from 0 to n of k^3
    return Polynomial{
        Monomial(AlbaNumber::createFraction(1, 4), {{countVariable, 4}}),
        Monomial(AlbaNumber::createFraction(1, 2), {{countVariable, 3}}),
        Monomial(AlbaNumber::createFraction(1, 4), {{countVariable, 2}})};
}

Term getSummationOfFiniteGeometricSeries(string const& base, string const& exponent) {
    // form: Summation of k from 0 to n of x^k
    Term numerator(
        createExpressionIfPossible({base, "^", Polynomial{Monomial(1, {{exponent, 1}}), Monomial(1, {})}, "-", 1}));
    Term denominator(Polynomial{Monomial(1, {{"x", 1}}), Monomial(-1, {})});
    Term result(createExpressionIfPossible({numerator, "/", denominator}));
    result.simplify();
    return result;
}

Term getSummationOfInfiniteGeometricSeries(string const& base) {
    // form: Summation of k from 0 to infinity of x^k
    Term numerator(1);
    Term denominator(Polynomial{Monomial(-1, {{base, 1}}), Monomial(1, {})});
    Term result(createExpressionIfPossible({numerator, "/", denominator}));
    result.simplify();
    return result;
}

Term getSummationOfHarmonicSeries(string const& countVariable) {
    // form: Summation of k from 1 to n of 1/k
    return createExpressionIfPossible({ln(countVariable), "+", 1});
}

Term getSummationOfPowersOfTwo(string const& countVariable) {
    // form: Summation of n from 2^0 to 2^n
    Term result(
        createExpressionIfPossible({2, "^", Polynomial{Monomial(1, {{countVariable, 1}}), Monomial(1, {})}, "-", 1}));
    result.simplify();
    return result;
}

}  // namespace algebra

}  // namespace alba