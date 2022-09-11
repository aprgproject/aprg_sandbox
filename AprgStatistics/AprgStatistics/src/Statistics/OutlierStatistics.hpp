#pragma once

#include <Common/Math/Helpers/StatisticsHelpers.hpp>
#include <Statistics/DataStatistics.hpp>

namespace alba
{

template <unsigned int DIMENSIONS>
class OutlierStatistics : public DataStatistics<DIMENSIONS>
{
public:
    using Sample = DataSample<DIMENSIONS>;
    using Samples = std::vector<Sample>;
    using LocalStatistics = DataStatistics<DIMENSIONS>;

    OutlierStatistics(Samples const& samples)
        : DataStatistics<DIMENSIONS>(samples)
    {}

    bool isAnOutlierBasedOnChauvenetCriterion(Sample const& sample)    {
        LocalStatistics::calculateMeanIfNeeded();
        LocalStatistics::calculateSampleStandardDeviationIfNeeded();
        double acceptableDeviation(calculateAcceptableDeviationBasedOnChauvenetCriterion(LocalStatistics::m_samples.size()));        Sample deviation(Sample(sample-LocalStatistics::m_mean.getConstReference()).calculateAbsoluteValue());
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
