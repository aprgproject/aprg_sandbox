#include "Utilities.hpp"

#include <Algebra/Term/Operators/TermOperators.hpp>

namespace alba
{

namespace algebra
{

Term getSumOfArithmeticSeriesUsingFirstAndLastTerm(
        Term const& firstTerm,
        Term const& lastTerm,
        Term const& count)
{
    return (firstTerm + lastTerm) * count / 2;
}

}

}
