#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba
{

namespace algebra
{

namespace Functions
{

Function abs(Term const& term);
Function greatestIntegerFunction(Term const& term);
Function sgn(Term const& term);

Function ln(Term const& term);
Function log(Term const& term);
Function harmonicNumber(Term const& term);

Function sin(Term const& term);
Function cos(Term const& term);
Function tan(Term const& term);
Function csc(Term const& term);
Function sec(Term const& term);
Function cot(Term const& term);

Function arcsin(Term const& term);
Function arccos(Term const& term);
Function arctan(Term const& term);
Function arccsc(Term const& term);
Function arcsec(Term const& term);
Function arccot(Term const& term);

Function sinh(Term const& term);
Function cosh(Term const& term);
Function tanh(Term const& term);
Function csch(Term const& term);
Function sech(Term const& term);
Function coth(Term const& term);

Function arcsinh(Term const& term);
Function arccosh(Term const& term);
Function arctanh(Term const& term);
Function arccsch(Term const& term);
Function arcsech(Term const& term);
Function arccoth(Term const& term);

Function sinHarmonic(
        Term const& term,
        AlbaNumber const& amplitude,
        AlbaNumber const& period,
        AlbaNumber const& phaseDifference);

}

}

}
