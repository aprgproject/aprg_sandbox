#pragma once

#include <BooleanAlgebra/Term/TermTypes/Term.hpp>

namespace alba
{

namespace booleanAlgebra
{

// Not: ~a
// Not operators are declared in the class

// And: a & b
Term operator&(Constant const& constant1, Constant const& constant2);
Term operator&(Constant const& constant, VariableTerm const& variableTerm);
Term operator&(Constant const& constant, Expression const& expression);Term operator&(Constant const& constant, Term const& term);
Term operator&(VariableTerm const& variableTerm, Constant const& constant);
Term operator&(VariableTerm const& variableTerm1, VariableTerm const& variableTerm2);
Term operator&(VariableTerm const& variableTerm, Expression const& expression);Term operator&(VariableTerm const& variableTerm, Term const& term);
Term operator&(Expression const& expression, Constant const& constant);
Term operator&(Expression const& expression, VariableTerm const& variableTerm);
Term operator&(Expression const& expression1, Expression const& expression2);
Term operator&(Expression const& expression, Term const& term);
Term operator&(Term const& term, Constant const& constant);
Term operator&(Term const& term, VariableTerm const& variableTerm);
Term operator&(Term const& term, Expression const& expression);

// Or: a | b
Term operator|(Constant const& constant1, Constant const& constant2);
Term operator|(Constant const& constant, VariableTerm const& variableTerm);
Term operator|(Constant const& constant, Expression const& expression);Term operator|(Constant const& constant, Term const& term);
Term operator|(VariableTerm const& variableTerm, Constant const& constant);
Term operator|(VariableTerm const& variableTerm1, VariableTerm const& variableTerm2);
Term operator|(VariableTerm const& variableTerm, Expression const& expression);Term operator|(VariableTerm const& variableTerm, Term const& term);
Term operator|(Expression const& expression, Constant const& constant);
Term operator|(Expression const& expression, VariableTerm const& variableTerm);
Term operator|(Expression const& expression1, Expression const& expression2);
Term operator|(Expression const& expression, Term const& term);
Term operator|(Term const& term, Constant const& constant);
Term operator|(Term const& term, VariableTerm const& variableTerm);
Term operator|(Term const& term, Expression const& expression);


}

}
