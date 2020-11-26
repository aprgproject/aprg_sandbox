#pragma once

#include <DataSample.hpp>

#include <algorithm>
#include <functional>
#include <vector>

namespace alba
{

template <typename DataType, unsigned int dimensions>
class DataStatistics
{
public:
    using Sample = DataSample<DataType, dimensions>;
    using Samples = std::vector<Sample>;

    static Sample calculateSum(Samples const& samples)
    {
        return (Sample)std::accumulate(samples.begin(), samples.end(), Sample(), std::plus<Sample>());
    }

    static Sample calculateMean(Samples const& samples)
    {
        return calculateSum(samples)/samples.size();
    }

    static Sample calculateSampleVariance(Samples const& samples)
    {
        return calculateVariance(samples, samples.size()-1);
    }

    static Sample calculateSampleStandardDeviation(Samples const& samples)
    {
        return calculateStandardDeviation(samples, samples.size()-1);
    }

    static Sample calculatePopulationVariance(Samples const& samples)
    {
        return calculateVariance(samples, samples.size());
    }

    static Sample calculatePopulationStandardDeviation(Samples const& samples)
    {
        return calculateStandardDeviation(samples, samples.size());
    }

    static DataType calculateDispersionAroundTheCentroid(Samples const& samples)
    {
        Sample dispersionCalculationTemp(calculateSampleStandardDeviation(samples));
        dispersionCalculationTemp = dispersionCalculationTemp.calculateRaiseToPower(2);
        return pow((double)dispersionCalculationTemp.getSum(), 0.5);
    }
private:

    static Sample calculateVariance(Samples const& samples, unsigned int sampleSize)
    {
        Samples varianceCalculationTemp(samples);
        Sample mean(calculateMean(samples));
        for(Sample & sample: varianceCalculationTemp)
        {
            sample = sample-mean;
            sample = sample.calculateRaiseToPower(2);
        }
        return(calculateSum(varianceCalculationTemp)/sampleSize);
    }

    static Sample calculateStandardDeviation(Samples const& samples, unsigned int sampleSize)
    {
        Sample standardDeviation(calculateVariance(samples, sampleSize));
        standardDeviation = standardDeviation.calculateRaiseToInversePower(2);
        return standardDeviation;
    }
};

}
