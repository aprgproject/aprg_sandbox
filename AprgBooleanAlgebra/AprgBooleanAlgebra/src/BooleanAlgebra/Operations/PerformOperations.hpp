#pragma once

#include <BooleanAlgebra/Term/TermTypes/Term.hpp>

namespace alba
{

namespace booleanAlgebra
{

Term performOperation(
        Operator const& operatorTerm,
        Term const& term);
Term performOperation(
        Operator const& operatorTerm,
        Term const& term1,
        Term const& term2);
Term performNot(Term const& term);
Term performAnd(Term const& term1, Term const& term2);
Term performOr(Term const& term1, Term const& term2);

}

}
