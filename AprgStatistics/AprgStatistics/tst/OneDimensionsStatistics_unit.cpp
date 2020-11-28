#include <OneDimensionsStatistics.hpp>

#include <gtest/gtest.h>

#include <iostream>

using namespace alba;
using namespace std;

using LocalSample = OneDimensionsStatistics::Sample;
using LocalSamples = OneDimensionsStatistics::Samples;

TEST(OneDimensionsStatisticsTest, MinMaxValuesCanFetched)
{
    LocalSamples samples;
    samples.emplace_back(LocalSample{-100});
    samples.emplace_back(LocalSample{-10});
    samples.emplace_back(LocalSample{-1});
    samples.emplace_back(LocalSample{1});
    samples.emplace_back(LocalSample{10});
    samples.emplace_back(LocalSample{100});
    OneDimensionsStatistics::PairOfDoubles minMax(OneDimensionsStatistics::getMinMaxFromSamples(samples));

    EXPECT_EQ(-100, minMax.first);
    EXPECT_EQ(100, minMax.second);
}
