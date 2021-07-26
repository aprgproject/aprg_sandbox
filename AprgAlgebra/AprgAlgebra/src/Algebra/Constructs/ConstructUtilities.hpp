#pragma once

#include <Algebra/Constructs/PolynomialOverPolynomial.hpp>
#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba
{

namespace algebra
{

PolynomialOverPolynomial createPolynomialOverPolynomialFromTermIfPossible(Term const& term);

}

}
