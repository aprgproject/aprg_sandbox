#pragma once

#include <DataSample.hpp>
#include <DataStatistics.hpp>

namespace alba
{

namespace OneDimensionsStatistics
{
    using Sample = DataSample<1>;
    using Statistics = DataStatistics<1>;
    using PairOfDoubles = std::pair<double, double>;
    using Samples = std::vector<Sample>;

    PairOfDoubles getMinMaxFromSamples(Samples const& samples);
}

}
