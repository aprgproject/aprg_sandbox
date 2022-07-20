#pragma once

#include <BooleanAlgebra/Term/TermTypes/Term.hpp>

namespace alba
{

namespace booleanAlgebra
{

bool willHaveNoEffectOnAndOperation(Term const& term);
bool willHaveNoEffectOnAndOperation(Expression const& expression);
bool willHaveNoEffectOnOrOperation(Term const& term);
bool willHaveNoEffectOnOrOperation(Expression const& expression);

bool isTheValue(Term const& term, bool const value);
bool isTheValue(Constant const& constant, bool const value);
bool isTheValue(Expression const& expression, bool const value);

}

}
