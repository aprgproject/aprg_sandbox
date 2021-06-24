#pragma once

#include <Equation/Term/Polynomial.hpp>
#include <Equation/Term/Expression.hpp>

namespace alba
{

namespace equation
{

namespace Factorization
{

Expression factorize(Expression const& expression);
Polynomials factorize(Polynomial const& polynomial);

}

}

}
