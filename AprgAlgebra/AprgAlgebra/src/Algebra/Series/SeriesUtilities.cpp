#include "SeriesUtilities.hpp"

#include <Algebra/Term/Operators/TermOperators.hpp>
#include <Math/AlbaMathHelper.hpp>

using namespace alba::mathHelper;

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

Term getSumOfGeometricSeriesUsingFirstValueAndCommonMultiplier(
        Term const& firstValue,
        Term const& commonMultiplier,
        int const count)
{
    return firstValue * (Term(1)-(commonMultiplier^count)) / (Term(1)-commonMultiplier);
}

Term getInfiniteSumOfGeometricSeriesIfCommonMultiplierIsFractional(
        Term const& firstValue,
        Term const& commonMultiplier)
{
    return firstValue/(Term(1) - commonMultiplier);
}

}
}
