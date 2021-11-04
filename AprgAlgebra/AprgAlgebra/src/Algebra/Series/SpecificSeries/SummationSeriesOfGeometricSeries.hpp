#pragma once

#include <Algebra/Series/GeneralSeries/SeriesBasedOnSummation.hpp>

namespace alba
{

namespace algebra
{

class SummationSeriesOfGeometricSeries : public SeriesBasedOnSummation
{
public:
    SummationSeriesOfGeometricSeries(
            AlbaNumber const& firstValue,
            AlbaNumber const& commonMultiplier);

    SummationSeriesOfGeometricSeries(
            AlbaNumber const& valueAtNthIndex1,
            int const nthIndex1,
            AlbaNumber const& valueAtNthIndex2,
            int const nthIndex2);

private:

};

}

}
