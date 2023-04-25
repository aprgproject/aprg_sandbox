#pragma once

#include <BooleanAlgebra/Term/TermTypes/Term.hpp>

#include <functional>

namespace alba {

namespace booleanAlgebra {

using UnaryBooleanFunction = std::function<bool(Term const&)>;

Term getNegation(Term const& term);
Term getConjunction(Term const& term1, Term const& term2);
Term getInclusiveDisjunction(Term const& term1, Term const& term2);
Term getExclusiveDisjunction(Term const& term1, Term const& term2);
Term getImplication(Term const& term1, Term const& term2);
Term getEquivalence(Term const& term1, Term const& term2);
Term getUniversalQuantification(Terms const& terms, UnaryBooleanFunction const& unaryBooleanFunction);
Term getExistentialQuantification(Terms const& terms, UnaryBooleanFunction const& unaryBooleanFunction);
Term getUniquenessQuantification(Terms const& terms, UnaryBooleanFunction const& unaryBooleanFunction);
UnaryBooleanFunction getTautology();
UnaryBooleanFunction getContradiction();

}  // namespace booleanAlgebra

}  // namespace alba
