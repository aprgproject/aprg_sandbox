#pragma once

#include <DataStatistics.hpp>
#include <Math/AlbaMathHelper.hpp>

namespace alba
{

template <unsigned int dimensions>
class OutlierStatistics : public DataStatistics<dimensions>
{
public:
    using Sample = DataSample<dimensions>;
    using Samples = std::vector<Sample>;
    using LocalStatistics = DataStatistics<dimensions>;

    OutlierStatistics(Samples const& samples)
        : DataStatistics<dimensions>(samples)
    {}

    bool isAnOutlierBasedOnChauvenetCriterion(Sample const& sample)
    {
        LocalStatistics::calculateMeanIfNeeded();
        LocalStatistics::calculateSampleStandardDeviationIfNeeded();
        double acceptableDeviation(calculateAcceptableDeviationBasedOnChauvenetCriterion(LocalStatistics::m_samples.size()));
        Sample deviation(Sample(sample-LocalStatistics::m_mean.getConstReference()).calculateAbsoluteValue());
        Sample deviationOverStandardDeviation(deviation/LocalStatistics::m_sampleStandardDeviation.getConstReference());
        bool isAnOutlier(false);
        for(unsigned int i=0; i<deviationOverStandardDeviation.getSize(); i++)
        {
            if(deviationOverStandardDeviation.getValueAt(i)>acceptableDeviation)
            {
                isAnOutlier = true;
                break;
            }
        }
        return isAnOutlier;
    }

    double calculateAcceptableDeviationBasedOnChauvenetCriterion(unsigned int const sampleSize)
    {
        return mathHelper::getAbsoluteValue(mathHelper::getInverseCumulativeStandardDistributionApproximation(1/((double)4*sampleSize), 20));
    }
};

}
