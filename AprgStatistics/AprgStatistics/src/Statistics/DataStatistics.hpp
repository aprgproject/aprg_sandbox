#pragma once

#include <Common/Container/AlbaOptional.hpp>
#include <Statistics/DataSample.hpp>
#include <Statistics/DataStatisticsUtilities.hpp>

#include <algorithm>
#include <functional>

namespace alba
{

template <unsigned int DIMENSIONS>
class DataStatistics
{
public:
    using Sample = DataSample<DIMENSIONS>;
    using Samples = std::vector<Sample>;
    using StatisticsUtilities = DataStatisticsUtilities<DIMENSIONS>;
    using SampleOptional = alba::AlbaOptional<Sample>;
    using DoubleOptional = alba::AlbaOptional<double>;

    DataStatistics()
    {}

    DataStatistics(Samples const& samples)
        : m_samples(samples)
    {}

    void clearPreviousCalculations()
    {
        m_sum.clear();
        m_mean.clear();
        m_sampleVariance.clear();
        m_sampleStandardDeviation.clear();
        m_populationVariance.clear();
        m_populationStandardDeviation.clear();
        m_dispersionAroundTheCentroid.clear();
    }

    Samples const& getSamples() const
    {
        return m_samples;
    }

    Sample getSum()
    {
        calculateSumIfNeeded();
        return m_sum.getConstReference();
    }

    Sample getMean()
    {
        calculateMeanIfNeeded();
        return m_mean.getConstReference();
    }

    Sample getSampleVariance()
    {
        calculateSampleVarianceIfNeeded();
        return m_sampleVariance.getConstReference();
    }

    Sample getSampleStandardDeviation()
    {
        calculateSampleStandardDeviationIfNeeded();
        return m_sampleStandardDeviation.getConstReference();
    }

    Sample getPopulationVariance()
    {
        calculatePopulationVarianceIfNeeded();
        return m_populationVariance.getConstReference();
    }

    Sample getPopulationStandardDeviation()
    {
        calculatePopulationStandardDeviationIfNeeded();
        return m_populationStandardDeviation.getConstReference();
    }

    double getDispersionAroundTheCentroid()
    {
        calculateDispersionAroundTheCentroidIfNeeded();
        return m_dispersionAroundTheCentroid.getConstReference();
    }

protected:
    void calculateSumIfNeeded()
    {
        if(!m_sum)
        {
            m_sum.setValue(StatisticsUtilities::calculateSum(m_samples));
        }
    }

    void calculateMeanIfNeeded()
    {
        if(!m_mean)
        {
            calculateSumIfNeeded();
            unsigned int sampleSize(m_samples.empty() ? 1 : m_samples.size());
            m_mean.setValue(m_sum.getConstReference()/sampleSize);
        }
    }

    void calculateSampleVarianceIfNeeded()
    {
        calculateVarianceIfNeeded(m_sampleVariance, m_samples.size()-1);
    }

    void calculateSampleStandardDeviationIfNeeded()
    {
        calculateStandardDeviationIfNeeded(m_sampleStandardDeviation, m_sampleVariance, m_samples.size()-1);
    }

    void calculatePopulationVarianceIfNeeded()
    {
        calculateVarianceIfNeeded(m_populationVariance, m_samples.size());
    }

    void calculatePopulationStandardDeviationIfNeeded()
    {
        calculateStandardDeviationIfNeeded(m_populationStandardDeviation, m_populationVariance, m_samples.size());
    }

    void calculateVarianceIfNeeded(SampleOptional & variance, unsigned int sampleSize)
    {
        if(!variance)
        {
            if(!m_samples.empty())
            {
                Samples varianceCalculationTemp(m_samples);
                calculateMeanIfNeeded();
                for(Sample & sample: varianceCalculationTemp)
                {
                    sample = sample-m_mean.getConstReference();
                    sample = sample.calculateRaiseToPower(2);
                }
                variance.setValue(StatisticsUtilities::calculateSum(varianceCalculationTemp)/sampleSize);
            }
            else
            {
                variance.setValue(Sample{});
            }
        }
    }

    void calculateStandardDeviationIfNeeded(SampleOptional & standardDeviation, SampleOptional & variance, unsigned int sampleSize)
    {
        if(!standardDeviation)
        {
            calculateVarianceIfNeeded(variance, sampleSize);
            Sample standardDeviationTemp(variance.getConstReference());
            standardDeviationTemp = standardDeviationTemp.calculateRaiseToInversePower(2);
            standardDeviation.setValue(standardDeviationTemp);
        }
    }

    void calculateDispersionAroundTheCentroidIfNeeded()
    {
        if(!m_dispersionAroundTheCentroid)
        {
            calculateSampleStandardDeviationIfNeeded();
            Sample dispersionCalculationTemp(m_sampleStandardDeviation.getConstReference());
            dispersionCalculationTemp = dispersionCalculationTemp.calculateRaiseToPower(2);
            m_dispersionAroundTheCentroid.setValue(pow((double)dispersionCalculationTemp.getSum(), 0.5));
        }
    }

    SampleOptional m_sum;
    SampleOptional m_mean;
    SampleOptional m_sampleVariance;
    SampleOptional m_sampleStandardDeviation;
    SampleOptional m_populationVariance;
    SampleOptional m_populationStandardDeviation;
    DoubleOptional m_dispersionAroundTheCentroid;
    Samples const& m_samples;
};

}
