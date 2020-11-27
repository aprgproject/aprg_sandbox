#include <DataStatistics.hpp>

#include <gtest/gtest.h>

#include <iostream>

using namespace alba;
using namespace std;

TEST(DataStatisticsTest, StatisticsAreCorrectWhenSamplesAreEmpty)
{
    using LocalStatistics = DataStatistics<3>;
    using LocalSamples = LocalStatistics::Samples;
    using LocalSample = LocalStatistics::Sample;

    LocalSamples samples;
    LocalSample expectedSum{0, 0, 0};
    LocalSample expectedMean{0, 0, 0};
    LocalSample expectedSampleVariance{0, 0, 0};
    LocalSample expectedSampleStandardDeviation{0, 0, 0};
    LocalSample expectedPopulationVariance{0, 0, 0};
    LocalSample expectedPopulationStandardDeviation{0, 0, 0};
    double expectedDispersion(0);

    LocalSample sum(LocalStatistics::calculateSum(samples));
    LocalSample mean(LocalStatistics::calculateMean(samples));
    LocalSample sampleVariance(LocalStatistics::calculateSampleVariance(samples));
    LocalSample sampleStandardDeviation(LocalStatistics::calculateSampleStandardDeviation(samples));
    LocalSample populationVariance(LocalStatistics::calculatePopulationVariance(samples));
    LocalSample populationStandardDeviation(LocalStatistics::calculatePopulationStandardDeviation(samples));
    double dispersion(LocalStatistics::calculateDispersionAroundTheCentroid(samples));

    EXPECT_EQ(expectedSum, sum);
    EXPECT_EQ(expectedMean, mean);
    EXPECT_EQ(expectedSampleVariance, sampleVariance);
    EXPECT_EQ(expectedSampleStandardDeviation, sampleStandardDeviation);
    EXPECT_EQ(expectedPopulationVariance, populationVariance);
    EXPECT_EQ(expectedPopulationStandardDeviation, populationStandardDeviation);
    EXPECT_DOUBLE_EQ(expectedDispersion, dispersion);
}

TEST(DataStatisticsTest, StatisticsAreCorrect)
{
    using LocalStatistics = DataStatistics<3>;
    using LocalSamples = LocalStatistics::Samples;
    using LocalSample = LocalStatistics::Sample;

    LocalSamples samples{LocalSample{1, 10, 100}, LocalSample{2, 20, 200}, LocalSample{3, 30, 300}};
    LocalSample expectedSum{6, 60, 600};
    LocalSample expectedMean{2, 20, 200};
    LocalSample expectedSampleVariance{1, 100, 10000};
    LocalSample expectedSampleStandardDeviation{1, 10, 100};
    LocalSample expectedPopulationVariance{0.66666666666666662966, 66.666666666666671404, 6666.6666666666669698};
    LocalSample expectedPopulationStandardDeviation{0.81649658092772603446, 8.1649658092772607887, 81.64965809277261144};
    double expectedDispersion(100.50373127401788);

    LocalSample sum(LocalStatistics::calculateSum(samples));
    LocalSample mean(LocalStatistics::calculateMean(samples));
    LocalSample sampleVariance(LocalStatistics::calculateSampleVariance(samples));
    LocalSample sampleStandardDeviation(LocalStatistics::calculateSampleStandardDeviation(samples));
    LocalSample populationVariance(LocalStatistics::calculatePopulationVariance(samples));
    LocalSample populationStandardDeviation(LocalStatistics::calculatePopulationStandardDeviation(samples));
    double dispersion(LocalStatistics::calculateDispersionAroundTheCentroid(samples));

    EXPECT_EQ(expectedSum, sum);
    EXPECT_EQ(expectedMean, mean);
    EXPECT_EQ(expectedSampleVariance, sampleVariance);
    EXPECT_EQ(expectedSampleStandardDeviation, sampleStandardDeviation);
    EXPECT_EQ(expectedPopulationVariance, populationVariance);
    EXPECT_EQ(expectedPopulationStandardDeviation, populationStandardDeviation);
    EXPECT_DOUBLE_EQ(expectedDispersion, dispersion);
}

TEST(DataStatisticsTest, DistancesAreCorrect)
{
    using LocalStatistics = DataStatistics<3>;
    using LocalSample = LocalStatistics::Sample;

    EXPECT_EQ(0, LocalStatistics::calculateDistance(LocalSample{}, LocalSample{}));
    EXPECT_EQ(0, LocalStatistics::calculateDistance(LocalSample{1, 10, 100}, LocalSample{1, 10, 100}));
    EXPECT_EQ(3, LocalStatistics::calculateDistance(LocalSample{1, 10, 100}, LocalSample{2, 12, 102}));
    EXPECT_EQ(7, LocalStatistics::calculateDistance(LocalSample{1, 10, 100}, LocalSample{3, 13, 106}));
}