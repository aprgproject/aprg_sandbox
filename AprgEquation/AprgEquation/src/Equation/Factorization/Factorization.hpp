#pragma once

#include <Equation/Term/Function.hpp>
#include <Equation/Term/Expression.hpp>
#include <Equation/Term/Polynomial.hpp>

namespace alba
{

namespace equation
{

namespace Factorization
{

Polynomials factorize(Polynomial const& polynomial);
Expression factorize(Expression const& expression);
Function factorize(Function const& expression);

}

}

}
