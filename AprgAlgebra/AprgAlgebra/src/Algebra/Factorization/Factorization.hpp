#pragma once

#include <Algebra/Term/TermTypes/Function.hpp>
#include <Algebra/Term/TermTypes/Expression.hpp>
#include <Algebra/Term/TermTypes/Polynomial.hpp>

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
