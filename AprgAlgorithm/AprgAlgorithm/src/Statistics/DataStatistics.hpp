#pragma once

#include <Statistics/DataSample.hpp>

#include <algorithm>
#include <functional>
#include <vector>

namespace alba
{

template <typename DataType, unsigned int size>
class DataStatistics
{
    using DataSampleSimplifiedType = DataSample<DataType, size>;
    using DataSamples = std::vector<DataSampleSimplifiedType>;

    DataSampleSimplifiedType calculateSum(DataSamples const& samples)
    {
        return std::accumulate(samples.begin(), samples.end(), DataSampleSimplifiedType(), std::plus<DataSamples>());
    }

    DataSampleSimplifiedType calculateMean(DataSamples const& samples)
    {
        return calculateSum(samples)/samples.size();
    }
};

}
