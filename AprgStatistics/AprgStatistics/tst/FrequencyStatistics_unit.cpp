#include <FrequencyStatistics.hpp>

#include <gtest/gtest.h>
#include <iostream>

using namespace alba;
using namespace std;

TEST(FrequencyStatisticsTest, SamplesAreEmpty)
{
    using LocalFrequencyStatistics = FrequencyStatistics<double>;
    LocalFrequencyStatistics::FrequencySamples samples;

    LocalFrequencyStatistics::MultipleValues modes(LocalFrequencyStatistics::calculateMode(samples));
    EXPECT_EQ(0, LocalFrequencyStatistics::calculateNumberOfSamples(samples));
    EXPECT_EQ(0, LocalFrequencyStatistics::calculateSum(samples));
    EXPECT_EQ(0, LocalFrequencyStatistics::calculateMean(samples));
    EXPECT_EQ(0, LocalFrequencyStatistics::calculateMedian(samples));
    ASSERT_EQ(0, modes.size());
}

TEST(FrequencyStatisticsTest, SingleSamplePerValueWithOddNumberOfValues){
    using LocalFrequencyStatistics = FrequencyStatistics<double>;
    LocalFrequencyStatistics::FrequencySamples samples;
    samples[1] = 1;    samples[2] = 1;
    samples[3] = 1;
    samples[4] = 1;
    samples[5] = 1;
    samples[6] = 1;
    samples[7] = 1;
    samples[8] = 1;
    samples[9] = 1;

    LocalFrequencyStatistics::MultipleValues modes(LocalFrequencyStatistics::calculateMode(samples));
    EXPECT_EQ(9, LocalFrequencyStatistics::calculateNumberOfSamples(samples));
    EXPECT_EQ(45, LocalFrequencyStatistics::calculateSum(samples));
    EXPECT_EQ(5, LocalFrequencyStatistics::calculateMean(samples));
    EXPECT_EQ(5, LocalFrequencyStatistics::calculateMedian(samples));
    ASSERT_EQ(9, modes.size());
    EXPECT_EQ(1, modes[0]);
    EXPECT_EQ(2, modes[1]);    EXPECT_EQ(3, modes[2]);
    EXPECT_EQ(4, modes[3]);
    EXPECT_EQ(5, modes[4]);
    EXPECT_EQ(6, modes[5]);
    EXPECT_EQ(7, modes[6]);
    EXPECT_EQ(8, modes[7]);
    EXPECT_EQ(9, modes[8]);
}

TEST(FrequencyStatisticsTest, SingleSamplePerValueWithEvenNumberOfValues){
    using LocalFrequencyStatistics = FrequencyStatistics<double>;
    LocalFrequencyStatistics::FrequencySamples samples;
    samples[1] = 1;    samples[2] = 1;
    samples[3] = 1;
    samples[4] = 1;
    samples[5] = 1;
    samples[6] = 1;
    samples[7] = 1;
    samples[8] = 1;
    samples[9] = 1;
    samples[10] = 1;

    LocalFrequencyStatistics::MultipleValues modes(LocalFrequencyStatistics::calculateMode(samples));
    EXPECT_EQ(10, LocalFrequencyStatistics::calculateNumberOfSamples(samples));
    EXPECT_EQ(55, LocalFrequencyStatistics::calculateSum(samples));
    EXPECT_EQ(5.5, LocalFrequencyStatistics::calculateMean(samples));
    EXPECT_EQ(5.5, LocalFrequencyStatistics::calculateMedian(samples));
    ASSERT_EQ(10, modes.size());
    EXPECT_EQ(1, modes[0]);
    EXPECT_EQ(2, modes[1]);    EXPECT_EQ(3, modes[2]);
    EXPECT_EQ(4, modes[3]);
    EXPECT_EQ(5, modes[4]);
    EXPECT_EQ(6, modes[5]);    EXPECT_EQ(7, modes[6]);
    EXPECT_EQ(8, modes[7]);
    EXPECT_EQ(9, modes[8]);
    EXPECT_EQ(10, modes[9]);
}

TEST(FrequencyStatisticsTest, MulipleSamplesPerValue){
    using LocalFrequencyStatistics = FrequencyStatistics<double>;
    LocalFrequencyStatistics::FrequencySamples samples;
    samples[1] = 7;    samples[2] = 1;
    samples[3] = 6;
    samples[4] = 11;
    samples[5] = 5;

    LocalFrequencyStatistics::MultipleValues modes(LocalFrequencyStatistics::calculateMode(samples));
    EXPECT_EQ(30, LocalFrequencyStatistics::calculateNumberOfSamples(samples));
    EXPECT_EQ(96, LocalFrequencyStatistics::calculateSum(samples));
    EXPECT_EQ(3.2, LocalFrequencyStatistics::calculateMean(samples));
    EXPECT_EQ(4, LocalFrequencyStatistics::calculateMedian(samples));
    ASSERT_EQ(1, modes.size());
    EXPECT_EQ(4, modes[0]);
}

TEST(FrequencyStatisticsTest, MulipleSamplesWithEmptyValues)
{
    using LocalFrequencyStatistics = FrequencyStatistics<double>;
    LocalFrequencyStatistics::FrequencySamples samples;
    samples[9] = 0;
    samples[10] = 7;
    samples[15] = 0;
    samples[20] = 8;
    samples[23] = 0;
    samples[27] = 0;
    samples[30] = 4;
    samples[32] = 0;
    samples[40] = 6;
    samples[48] = 0;
    samples[50] = 5;
    samples[54] = 0;

    LocalFrequencyStatistics::MultipleValues modes(LocalFrequencyStatistics::calculateMode(samples));
    EXPECT_EQ(30, LocalFrequencyStatistics::calculateNumberOfSamples(samples));
    EXPECT_EQ(840, LocalFrequencyStatistics::calculateSum(samples));
    EXPECT_EQ(28, LocalFrequencyStatistics::calculateMean(samples));
    EXPECT_EQ(25, LocalFrequencyStatistics::calculateMedian(samples));
    ASSERT_EQ(1, modes.size());
    EXPECT_EQ(20, modes[0]);
}