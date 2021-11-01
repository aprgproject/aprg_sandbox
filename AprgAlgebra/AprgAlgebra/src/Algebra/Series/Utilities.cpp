#include "Utilities.hpp"

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

double getSumOfArithmeticSeriesUsingFirstAndLastValue(
        double const firstValue,
        double const lastValue,
        int const count)
{
    return (firstValue + lastValue) * count / 2;
}

double getSumOfGeometricSeriesUsingFirstValueAndCommonMultiplier(
        double const firstValue,
        double const commonMultiplier,
        int const count)
{
    return firstValue*(1-pow(commonMultiplier, count))/(1-commonMultiplier);
}

double getInfiniteSumOfGeometricSeriesIfCommonMultiplierIsFractional(
        double const firstValue,
        double const commonMultiplier)
{
    double result(0);
    if(getAbsoluteValue(commonMultiplier) < 1)
    {
        result = firstValue/(1-commonMultiplier);
    }
    return result;
}

}

}