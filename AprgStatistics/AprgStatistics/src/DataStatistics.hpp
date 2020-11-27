#pragma once

#include <DataSample.hpp>

#include <algorithm>
#include <functional>
#include <vector>

namespace alba
{

template <unsigned int dimensions>
class DataStatistics
{
public:
    using Sample = DataSample<dimensions>;
    using Samples = std::vector<Sample>;

    static Sample calculateSum(Samples const& samples)
    {
        return (Sample)std::accumulate(samples.begin(), samples.end(), Sample(), std::plus<Sample>());
    }

    static Sample calculateMean(Samples const& samples)
    {
        Sample mean;
        if(!samples.empty())
        {
            mean = calculateSum(samples)/samples.size();
        }
        return mean;
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

    static double calculateDispersionAroundTheCentroid(Samples const& samples)
    {
        Sample dispersionCalculationTemp(calculateSampleStandardDeviation(samples));
        dispersionCalculationTemp = dispersionCalculationTemp.calculateRaiseToPower(2);
        return pow((double)dispersionCalculationTemp.getSum(), 0.5);
    }

    static double calculateDistance(Sample const& sample1, Sample const& sample2)
    {
        Sample distanceCalculationTemp(sample1-sample2);
        distanceCalculationTemp = distanceCalculationTemp.calculateRaiseToPower(2);
        return pow((double)distanceCalculationTemp.getSum(), 0.5);
    }
private:

    static Sample calculateVariance(Samples const& samples, unsigned int sampleSize)
    {
        Sample variance;
        if(!samples.empty())
        {
            Samples varianceCalculationTemp(samples);
            Sample mean(calculateMean(samples));
            for(Sample & sample: varianceCalculationTemp)
            {
                sample = sample-mean;
                sample = sample.calculateRaiseToPower(2);
            }
            variance = calculateSum(varianceCalculationTemp)/sampleSize;
        }
        return variance;
    }

    static Sample calculateStandardDeviation(Samples const& samples, unsigned int sampleSize)
    {
        Sample standardDeviation(calculateVariance(samples, sampleSize));
        standardDeviation = standardDeviation.calculateRaiseToInversePower(2);
        return standardDeviation;
    }
};

}
