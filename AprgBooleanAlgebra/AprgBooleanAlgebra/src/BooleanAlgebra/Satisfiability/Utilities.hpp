#pragma once

#include <BooleanAlgebra/Term/TermTypes/Term.hpp>

namespace alba {

namespace booleanAlgebra {

using SatisfiabilityTerm = VariableTerms;
using SatisfiabilityTerms = std::vector<VariableTerms>;

int getSatisfiabilityLevel(SatisfiabilityTerms const& satTerms);
SatisfiabilityTerms getSatisfiabilityTerms(Term const& term);
SatisfiabilityTerms getSatisfiabilityTerms(Expression const& expression);

}  // namespace booleanAlgebra

}  // namespace alba
