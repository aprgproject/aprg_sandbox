#include <FrequencyStatistics.hpp>

#include <gtest/gtest.h>

#include <iostream>

using namespace std;

namespace alba
{

TEST(FrequencyStatisticsTest, SamplesAreEmpty)
{
    FrequencyStatistics::FrequencySamples samples;
    FrequencyStatistics::MultipleValues modes(FrequencyStatistics::calculateMode(samples));
    EXPECT_EQ(0u, FrequencyStatistics::calculateNumberOfSamples(samples));
    EXPECT_EQ(0u, FrequencyStatistics::calculateSum(samples));    EXPECT_EQ(0u, FrequencyStatistics::calculateMean(samples));
    EXPECT_EQ(0u, FrequencyStatistics::calculateMedian(samples));
    ASSERT_EQ(0u, modes.size());
}

TEST(FrequencyStatisticsTest, SingleSamplePerValueWithOddNumberOfValues)
{
    FrequencyStatistics::FrequencySamples samples;
    samples[1] = 1;
    samples[2] = 1;
    samples[3] = 1;
    samples[4] = 1;
    samples[5] = 1;
    samples[6] = 1;
    samples[7] = 1;
    samples[8] = 1;
    samples[9] = 1;

    FrequencyStatistics::MultipleValues modes(FrequencyStatistics::calculateMode(samples));
    EXPECT_EQ(9u, FrequencyStatistics::calculateNumberOfSamples(samples));
    EXPECT_EQ(45u, FrequencyStatistics::calculateSum(samples));
    EXPECT_EQ(5u, FrequencyStatistics::calculateMean(samples));
    EXPECT_EQ(5u, FrequencyStatistics::calculateMedian(samples));
    ASSERT_EQ(9u, modes.size());
    EXPECT_EQ(1, modes[0]);
    EXPECT_EQ(2, modes[1]);
    EXPECT_EQ(3, modes[2]);
    EXPECT_EQ(4, modes[3]);
    EXPECT_EQ(5, modes[4]);
    EXPECT_EQ(6, modes[5]);
    EXPECT_EQ(7, modes[6]);
    EXPECT_EQ(8, modes[7]);
    EXPECT_EQ(9, modes[8]);
}

TEST(FrequencyStatisticsTest, SingleSamplePerValueWithEvenNumberOfValues){
    FrequencyStatistics::FrequencySamples samples;
    samples[1] = 1;
    samples[2] = 1;    samples[3] = 1;
    samples[4] = 1;
    samples[5] = 1;
    samples[6] = 1;
    samples[7] = 1;
    samples[8] = 1;
    samples[9] = 1;
    samples[10] = 1;

    FrequencyStatistics::MultipleValues modes(FrequencyStatistics::calculateMode(samples));
    EXPECT_EQ(10u, FrequencyStatistics::calculateNumberOfSamples(samples));
    EXPECT_EQ(55u, FrequencyStatistics::calculateSum(samples));
    EXPECT_EQ(5.5, FrequencyStatistics::calculateMean(samples));
    EXPECT_EQ(5.5, FrequencyStatistics::calculateMedian(samples));
    ASSERT_EQ(10u, modes.size());
    EXPECT_EQ(1, modes[0]);
    EXPECT_EQ(2, modes[1]);
    EXPECT_EQ(3, modes[2]);
    EXPECT_EQ(4, modes[3]);
    EXPECT_EQ(5, modes[4]);
    EXPECT_EQ(6, modes[5]);
    EXPECT_EQ(7, modes[6]);
    EXPECT_EQ(8, modes[7]);
    EXPECT_EQ(9, modes[8]);
    EXPECT_EQ(10, modes[9]);
}

TEST(FrequencyStatisticsTest, MulipleSamplesPerValue){
    FrequencyStatistics::FrequencySamples samples;
    samples[1] = 7;
    samples[2] = 1;    samples[3] = 6;
    samples[4] = 11;
    samples[5] = 5;

    FrequencyStatistics::MultipleValues modes(FrequencyStatistics::calculateMode(samples));
    EXPECT_EQ(30u, FrequencyStatistics::calculateNumberOfSamples(samples));
    EXPECT_EQ(96u, FrequencyStatistics::calculateSum(samples));
    EXPECT_EQ(3.2, FrequencyStatistics::calculateMean(samples));
    EXPECT_EQ(4u, FrequencyStatistics::calculateMedian(samples));
    ASSERT_EQ(1u, modes.size());
    EXPECT_EQ(4, modes[0]);
}

TEST(FrequencyStatisticsTest, MulipleSamplesWithEmptyValues){
    FrequencyStatistics::FrequencySamples samples;
    samples[9] = 0;
    samples[10] = 7;    samples[15] = 0;
    samples[20] = 8;
    samples[23] = 0;
    samples[27] = 0;
    samples[30] = 4;
    samples[32] = 0;
    samples[40] = 6;
    samples[48] = 0;
    samples[50] = 5;
    samples[54] = 0;

    FrequencyStatistics::MultipleValues modes(FrequencyStatistics::calculateMode(samples));
    EXPECT_EQ(30u, FrequencyStatistics::calculateNumberOfSamples(samples));
    EXPECT_EQ(840u, FrequencyStatistics::calculateSum(samples));
    EXPECT_EQ(28u, FrequencyStatistics::calculateMean(samples));
    EXPECT_EQ(25u, FrequencyStatistics::calculateMedian(samples));
    ASSERT_EQ(1u, modes.size());
    EXPECT_EQ(20, modes[0]);
}

}