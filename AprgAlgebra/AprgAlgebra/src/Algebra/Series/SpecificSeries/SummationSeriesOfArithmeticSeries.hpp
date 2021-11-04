#pragma once

#include <Algebra/Series/SeriesBasedOnSummation.hpp>

namespace alba
{

namespace algebra
{

class SummationSeriesOfArithmeticSeries : public SeriesBasedOnSummation
{
public:
    SummationSeriesOfArithmeticSeries(
            AlbaNumber const& firstValue,
            AlbaNumber const& commonDifference);

    SummationSeriesOfArithmeticSeries(
            AlbaNumber const& valueAtNthIndex1,
            int const nthIndex1,
            AlbaNumber const& valueAtNthIndex2,
            int const nthIndex2);
private:

};

}

}
