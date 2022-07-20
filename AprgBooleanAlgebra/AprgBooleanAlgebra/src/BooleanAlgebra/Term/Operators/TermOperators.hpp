#pragma once

#include <BooleanAlgebra/Term/TermTypes/Term.hpp>

namespace alba
{

namespace booleanAlgebra
{

//Negation (NOT)
Term operator~(Term const& term);

//And: a & b
Term operator&(Term const& term1, Term const& term2);
Term & operator&=(Term & term1, Term const& term2);

//Or: a | b
Term operator|(Term const& term1, Term const& term2);
Term & operator|=(Term & term1, Term const& term2);

}

}
