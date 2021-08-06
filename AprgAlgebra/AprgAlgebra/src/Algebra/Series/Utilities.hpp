#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba
{

namespace algebra
{

Term getSumOfArithmeticSeriesUsingFirstAndLastTerm(
        Term const& firstTerm,
        Term const& lastTerm,
        Term const& count);

}

}
