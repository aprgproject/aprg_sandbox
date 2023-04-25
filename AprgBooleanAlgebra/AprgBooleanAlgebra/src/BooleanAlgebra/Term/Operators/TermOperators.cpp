#include "TermOperators.hpp"

#include <BooleanAlgebra/Operations/PerformOperations.hpp>

using namespace std;

namespace alba {

namespace booleanAlgebra {

Term operator&(Term const& term1, Term const& term2) { return performAnd(term1, term2); }

Term& operator&=(Term& term1, Term const& term2) {
    term1 = term1 & term2;
    return term1;
}

Term operator|(Term const& term1, Term const& term2) { return performOr(term1, term2); }

Term& operator|=(Term& term1, Term const& term2) {
    term1 = term1 | term2;
    return term1;
}

}  // namespace booleanAlgebra

}  // namespace alba
