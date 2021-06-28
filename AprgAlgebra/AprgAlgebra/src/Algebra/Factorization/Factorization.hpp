#pragma once

#include <Algebra/Term/Function.hpp>
#include <Algebra/Term/Expression.hpp>
#include <Algebra/Term/Polynomial.hpp>

namespace alba
{

namespace algebra
{

namespace Factorization
{

Polynomials factorize(Polynomial const& polynomial);
Expression factorize(Expression const& expression);
Function factorize(Function const& expression);

}

}

}
