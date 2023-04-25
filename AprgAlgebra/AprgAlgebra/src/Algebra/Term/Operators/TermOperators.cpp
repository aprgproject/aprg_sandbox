#include "TermOperators.hpp"

#include <Algebra/Operations/PerformOperations.hpp>

using namespace std;

namespace alba {

namespace algebra {

Term operator+(Term const& term) { return performUnaryPlus(term); }

Term operator-(Term const& term) { return performUnaryMinus(term); }

Term operator+(Term const& term1, Term const& term2) { return performAddition(term1, term2); }

Term& operator+=(Term& term1, Term const& term2) {
    term1 = term1 + term2;
    return term1;
}

Term operator-(Term const& term1, Term const& term2) { return performSubtraction(term1, term2); }

Term& operator-=(Term& term1, Term const& term2) {
    term1 = term1 - term2;
    return term1;
}

Term operator*(Term const& term1, Term const& term2) { return performMultiplication(term1, term2); }

Term& operator*=(Term& term1, Term const& term2) {
    term1 = term1 * term2;
    return term1;
}

Term operator/(Term const& term1, Term const& term2) { return performDivision(term1, term2); }

Term& operator/=(Term& term1, Term const& term2) {
    term1 = term1 / term2;
    return term1;
}

Term operator^(Term const& term1, Term const& term2) { return performRaiseToPower(term1, term2); }

Term& operator^=(Term& term1, Term const& term2) {
    term1 = term1 ^ term2;
    return term1;
}

}  // namespace algebra

}  // namespace alba
