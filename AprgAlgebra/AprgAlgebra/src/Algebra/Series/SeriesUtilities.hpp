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

Term getSumOfGeometricSeriesUsingFirstValueAndCommonMultiplier(
        Term const& firstValue,
        Term const& commonMultiplier,
        int const count);

Term getInfiniteSumOfGeometricSeriesIfCommonMultiplierIsFractional(
        Term const& firstValue,
        Term const& commonMultiplier);

}
}
