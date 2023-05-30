#pragma once
#include <Statistics/DataSample.hpp>
#include <Statistics/DataStatisticsUtilities.hpp>

#include <algorithm>
#include <functional>
#include <optional>

namespace alba {

template <int DIMENSIONS>
class DataStatistics {
public:
    using Sample = DataSample<DIMENSIONS>;
    using Samples = std::vector<Sample>;
    using StatisticsUtilities = DataStatisticsUtilities<DIMENSIONS>;
    using SampleOptional = std::optional<Sample>;
    using DoubleOptional = std::optional<double>;

    DataStatistics() {}

    DataStatistics(Samples const& samples) : m_samples(samples) {}

    void clearPreviousCalculations() {
        m_sum.reset();
        m_mean.reset();
        m_sampleVariance.reset();
        m_sampleStandardDeviation.reset();
        m_populationVariance.reset();
        m_populationStandardDeviation.reset();
        m_dispersionAroundTheCentroid.reset();
    }

    Samples const& getSamples() const { return m_samples; }

    Sample getSum() {
        calculateSumIfNeeded();
        return m_sum.value();
    }

    Sample getMean() {
        calculateMeanIfNeeded();
        return m_mean.value();
    }

    Sample getSampleVariance() {
        calculateSampleVarianceIfNeeded();
        return m_sampleVariance.value();
    }

    Sample getSampleStandardDeviation() {
        calculateSampleStandardDeviationIfNeeded();
        return m_sampleStandardDeviation.value();
    }

    Sample getPopulationVariance() {
        calculatePopulationVarianceIfNeeded();
        return m_populationVariance.value();
    }

    Sample getPopulationStandardDeviation() {
        calculatePopulationStandardDeviationIfNeeded();
        return m_populationStandardDeviation.value();
    }

    double getDispersionAroundTheCentroid() {
        calculateDispersionAroundTheCentroidIfNeeded();
        return m_dispersionAroundTheCentroid.value();
    }

protected:
    void calculateSumIfNeeded() {
        if (!m_sum) {
            m_sum = StatisticsUtilities::calculateSum(m_samples);
        }
    }

    void calculateMeanIfNeeded() {
        if (!m_mean) {
            calculateSumIfNeeded();
            int sampleSize(m_samples.empty() ? 1 : m_samples.size());
            m_mean = m_sum.value() / sampleSize;
        }
    }

    void calculateSampleVarianceIfNeeded() { calculateVarianceIfNeeded(m_sampleVariance, m_samples.size() - 1); }

    void calculateSampleStandardDeviationIfNeeded() {
        calculateStandardDeviationIfNeeded(m_sampleStandardDeviation, m_sampleVariance, m_samples.size() - 1);
    }

    void calculatePopulationVarianceIfNeeded() { calculateVarianceIfNeeded(m_populationVariance, m_samples.size()); }

    void calculatePopulationStandardDeviationIfNeeded() {
        calculateStandardDeviationIfNeeded(m_populationStandardDeviation, m_populationVariance, m_samples.size());
    }

    void calculateVarianceIfNeeded(SampleOptional& variance, int sampleSize) {
        if (!variance) {
            if (!m_samples.empty()) {
                Samples varianceCalculationTemp(m_samples);
                calculateMeanIfNeeded();
                for (Sample& sample : varianceCalculationTemp) {
                    sample = sample - m_mean.value();
                    sample = sample.calculateRaiseToPower(2);
                }
                variance = StatisticsUtilities::calculateSum(varianceCalculationTemp) / sampleSize;
            } else {
                variance = Sample{};
            }
        }
    }

    void calculateStandardDeviationIfNeeded(
        SampleOptional& standardDeviation, SampleOptional& variance, int sampleSize) {
        if (!standardDeviation) {
            calculateVarianceIfNeeded(variance, sampleSize);
            Sample standardDeviationTemp(variance.value());
            standardDeviationTemp = standardDeviationTemp.calculateRaiseToInversePower(2);
            standardDeviation = standardDeviationTemp;
        }
    }

    void calculateDispersionAroundTheCentroidIfNeeded() {
        if (!m_dispersionAroundTheCentroid) {
            calculateSampleStandardDeviationIfNeeded();
            Sample dispersionCalculationTemp(m_sampleStandardDeviation.value());
            dispersionCalculationTemp = dispersionCalculationTemp.calculateRaiseToPower(2);
            m_dispersionAroundTheCentroid = pow((double)dispersionCalculationTemp.getSum(), 0.5);
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

}  // namespace alba
