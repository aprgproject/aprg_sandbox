#include <Statistics/DataStatistics.hpp>

#include <gtest/gtest.h>

#include <iostream>

using namespace alba;
using namespace std;

TEST(DataStatisticsTest, StatisticsAreCorrect)
{
    using LocalStatistics = DataStatistics<double, 3>;
    using LocalSamples = LocalStatistics::Samples;
    using LocalSample = LocalStatistics::Sample;

    LocalSamples samples{LocalSample{1, 10, 100}, LocalSample{2, 20, 200}, LocalSample{3, 30, 300}};
    LocalStatistics statistics;
    LocalSample sum(LocalStatistics::calculateSum(samples));
    LocalSample mean(LocalStatistics::calculateMean(samples));
    LocalSample variance(LocalStatistics::calculateSampleVariance(samples));
    LocalSample standardDeviation(LocalStatistics::calculateSampleStandardDeviation(samples));
    double dispersion(LocalStatistics::calculateDispersionAroundTheCentroid(samples));
    LocalSample expectedSum{6, 60, 600};
    LocalSample expectedMean{2, 20, 200};
    LocalSample expectedVariance{1, 100, 10000};
    LocalSample expectedStandardDeviation{1, 10, 100};
    double expectedDispersion(100.50373127401788);

    EXPECT_EQ(expectedSum, sum);
    EXPECT_EQ(expectedMean, mean);
    EXPECT_EQ(expectedVariance, variance);
    EXPECT_EQ(expectedStandardDeviation, standardDeviation);
    EXPECT_DOUBLE_EQ(expectedDispersion, dispersion);
}
