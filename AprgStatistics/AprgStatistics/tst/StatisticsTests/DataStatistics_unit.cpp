#include <Statistics/DataStatistics.hpp>

#include <gtest/gtest.h>

#include <iostream>

using namespace std;

namespace alba
{

TEST(DataStatisticsTest, StatisticsAreCorrectWhenSamplesAreEmpty)
{
    using LocalStatistics = DataStatistics<3>;
    using LocalSamples = LocalStatistics::Samples;
    using LocalSample = LocalStatistics::Sample;
    LocalSample expectedSum{0, 0, 0};
    LocalSample expectedMean{0, 0, 0};
    LocalSample expectedSampleVariance{0, 0, 0};
    LocalSample expectedSampleStandardDeviation{0, 0, 0};
    LocalSample expectedPopulationVariance{0, 0, 0};
    LocalSample expectedPopulationStandardDeviation{0, 0, 0};
    double expectedDispersion(0);

    LocalSamples samples;
    LocalStatistics localStatistics(samples);
    LocalSample sum(localStatistics.getSum());
    LocalSample mean(localStatistics.getMean());
    LocalSample sampleVariance(localStatistics.getSampleVariance());
    LocalSample sampleStandardDeviation(localStatistics.getSampleStandardDeviation());
    LocalSample populationVariance(localStatistics.getPopulationVariance());
    LocalSample populationStandardDeviation(localStatistics.getPopulationStandardDeviation());
    double dispersion(localStatistics.getDispersionAroundTheCentroid());

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
    LocalSample expectedSum{6, 60, 600};
    LocalSample expectedMean{2, 20, 200};
    LocalSample expectedSampleVariance{1, 100, 10000};
    LocalSample expectedSampleStandardDeviation{1, 10, 100};
    LocalSample expectedPopulationVariance{0.66666666666666662966, 66.666666666666671404, 6666.6666666666669698};
    LocalSample expectedPopulationStandardDeviation{0.81649658092772603446, 8.1649658092772607887, 81.64965809277261144};
    double expectedDispersion(100.50373127401788);

    LocalSamples samples{LocalSample{1, 10, 100}, LocalSample{2, 20, 200}, LocalSample{3, 30, 300}};
    LocalStatistics localStatistics(samples);
    LocalSample sum(localStatistics.getSum());
    LocalSample mean(localStatistics.getMean());
    LocalSample sampleVariance(localStatistics.getSampleVariance());
    LocalSample sampleStandardDeviation(localStatistics.getSampleStandardDeviation());
    LocalSample populationVariance(localStatistics.getPopulationVariance());
    LocalSample populationStandardDeviation(localStatistics.getPopulationStandardDeviation());
    double dispersion(localStatistics.getDispersionAroundTheCentroid());

    EXPECT_EQ(expectedSum, sum);
    EXPECT_EQ(expectedMean, mean);
    EXPECT_EQ(expectedSampleVariance, sampleVariance);
    EXPECT_EQ(expectedSampleStandardDeviation, sampleStandardDeviation);
    EXPECT_EQ(expectedPopulationVariance, populationVariance);
    EXPECT_EQ(expectedPopulationStandardDeviation, populationStandardDeviation);
    EXPECT_DOUBLE_EQ(expectedDispersion, dispersion);
}

TEST(DataStatisticsTest, StatisticsCanBeClearedAfterCalculation)
{
    using LocalStatistics = DataStatistics<3>;
    using LocalSamples = LocalStatistics::Samples;
    using LocalSample = LocalStatistics::Sample;
    LocalSample expectedSum{0, 0, 0};
    LocalSample expectedMean{0, 0, 0};
    LocalSample expectedSampleVariance{0, 0, 0};
    LocalSample expectedSampleStandardDeviation{0, 0, 0};
    LocalSample expectedPopulationVariance{0, 0, 0};
    LocalSample expectedPopulationStandardDeviation{0, 0, 0};
    double expectedDispersion(0);

    LocalSamples samples{LocalSample{1, 10, 100}, LocalSample{2, 20, 200}, LocalSample{3, 30, 300}};
    LocalStatistics localStatistics(samples);
    LocalSample sum(localStatistics.getSum());
    LocalSample mean(localStatistics.getMean());
    LocalSample sampleVariance(localStatistics.getSampleVariance());
    LocalSample sampleStandardDeviation(localStatistics.getSampleStandardDeviation());
    LocalSample populationVariance(localStatistics.getPopulationVariance());
    LocalSample populationStandardDeviation(localStatistics.getPopulationStandardDeviation());
    double dispersion(localStatistics.getDispersionAroundTheCentroid());
    samples.clear();
    localStatistics.clearPreviousCalculations();
    sum = localStatistics.getSum();
    mean = localStatistics.getMean();
    sampleVariance = localStatistics.getSampleVariance();
    sampleStandardDeviation = localStatistics.getSampleStandardDeviation();
    populationVariance = localStatistics.getPopulationVariance();
    populationStandardDeviation = localStatistics.getPopulationStandardDeviation();
    dispersion = localStatistics.getDispersionAroundTheCentroid();

    EXPECT_EQ(expectedSum, sum);
    EXPECT_EQ(expectedMean, mean);
    EXPECT_EQ(expectedSampleVariance, sampleVariance);
    EXPECT_EQ(expectedSampleStandardDeviation, sampleStandardDeviation);
    EXPECT_EQ(expectedPopulationVariance, populationVariance);
    EXPECT_EQ(expectedPopulationStandardDeviation, populationStandardDeviation);
    EXPECT_DOUBLE_EQ(expectedDispersion, dispersion);
}

}
