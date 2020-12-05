#include <DataStatisticsUtilities.hpp>

#include <gtest/gtest.h>

#include <iostream>

using namespace alba;
using namespace std;

TEST(DataStatisticsUtilitiesTest, SumAreCorrect)
{
    using LocalStatisticsUtilities = DataStatisticsUtilities<3>;
    using LocalSamples = LocalStatisticsUtilities::Samples;
    using LocalSample = LocalStatisticsUtilities::Sample;

    LocalSamples samples1;
    LocalSamples samples2{LocalSample{1, 10, 100}, LocalSample{2, 20, 200}, LocalSample{3, 30, 300}};
    LocalSample expectedSum1{0, 0, 0};
    LocalSample expectedSum2{6, 60, 600};

    EXPECT_EQ(expectedSum1, LocalStatisticsUtilities::calculateSum(samples1));
    EXPECT_EQ(expectedSum2, LocalStatisticsUtilities::calculateSum(samples2));
}

TEST(DataStatisticsUtilitiesTest, DistancesAreCorrect)
{
    using LocalStatisticsUtilities = DataStatisticsUtilities<3>;
    using LocalSample = LocalStatisticsUtilities::Sample;

    EXPECT_EQ(0, LocalStatisticsUtilities::calculateDistance(LocalSample{}, LocalSample{}));
    EXPECT_EQ(0, LocalStatisticsUtilities::calculateDistance(LocalSample{1, 10, 100}, LocalSample{1, 10, 100}));
    EXPECT_EQ(3, LocalStatisticsUtilities::calculateDistance(LocalSample{1, 10, 100}, LocalSample{2, 12, 102}));
    EXPECT_EQ(7, LocalStatisticsUtilities::calculateDistance(LocalSample{1, 10, 100}, LocalSample{3, 13, 106}));
}
