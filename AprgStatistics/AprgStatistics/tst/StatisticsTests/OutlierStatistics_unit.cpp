#include <Statistics/OutlierStatistics.hpp>

#include <gtest/gtest.h>
#include <iostream>

using namespace std;

namespace alba
{

TEST(OutlierStatisticsTest, OneDimensionOutlierStatisticsAreCorrect)
{
    using LocalStatistics = OutlierStatistics<1>;
    using LocalSamples = LocalStatistics::Samples;
    using LocalSample = LocalStatistics::Sample;
    LocalSamples samples{LocalSample{47}, LocalSample{50}, LocalSample{53}, LocalSample{55}, LocalSample{55},
    LocalSample{56}, LocalSample{57}, LocalSample{57}, LocalSample{58}, LocalSample{58},
    LocalSample{58}, LocalSample{58}, LocalSample{60}, LocalSample{60}, LocalSample{60},
    LocalSample{61}, LocalSample{61}, LocalSample{61}, LocalSample{61}, LocalSample{61},
    LocalSample{61}, LocalSample{62}, LocalSample{62}, LocalSample{62}, LocalSample{63},
    LocalSample{63}, LocalSample{64}, LocalSample{67}, LocalSample{68},
    LocalSample{72}};
    LocalStatistics outlierStatistics(samples);
    EXPECT_TRUE(outlierStatistics.isAnOutlierBasedOnChauvenetCriterion(LocalSample{47}));
    EXPECT_FALSE(outlierStatistics.isAnOutlierBasedOnChauvenetCriterion(LocalSample{67}));
}

TEST(OutlierStatisticsTest, ThreeDimensionOutlierStatisticsAreCorrect)
{
    using LocalStatistics = OutlierStatistics<3>;
    using LocalSamples = LocalStatistics::Samples;
    using LocalSample = LocalStatistics::Sample;
    LocalSamples samples{LocalSample{1, 10, 100}, LocalSample{2, 20, 200}, LocalSample{3, 30, 300}};

    LocalStatistics outlierStatistics(samples);
    EXPECT_TRUE(outlierStatistics.isAnOutlierBasedOnChauvenetCriterion(LocalSample{3.39, 33.9, 339}));
    EXPECT_TRUE(outlierStatistics.isAnOutlierBasedOnChauvenetCriterion(LocalSample{3.37, 33.9, 339}));
    EXPECT_TRUE(outlierStatistics.isAnOutlierBasedOnChauvenetCriterion(LocalSample{3.37, 33.7, 339}));
    EXPECT_FALSE(outlierStatistics.isAnOutlierBasedOnChauvenetCriterion(LocalSample{3.37, 33.7, 337}));
}

}
