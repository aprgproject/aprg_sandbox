#include <TwoDimensionsStatistics.hpp>

#include <gtest/gtest.h>

#include <iostream>

using namespace alba;
using namespace std;

TEST(TwoDimensionsStatisticsTest, SameValuesXForLineModeling)
{
    using LocalStatistics = TwoDimensionsStatistics<double>;
    using LocalSample = LocalStatistics::Sample;
    using LocalSamples = LocalStatistics::Samples;
    using LocalLineModel = LocalStatistics::LineModel;

    LocalSamples samples;
    samples.emplace_back(LocalSample{5,1});
    samples.emplace_back(LocalSample{5,2});
    samples.emplace_back(LocalSample{5,3});
    samples.emplace_back(LocalSample{5,4});
    samples.emplace_back(LocalSample{5,5});

    LocalLineModel lineModel(LocalStatistics::calculateLineModelUsingLeastSquares(samples));
    EXPECT_EQ(1, lineModel.aCoefficient);
    EXPECT_EQ(0, lineModel.bCoefficient);
    EXPECT_EQ(-5, lineModel.cCoefficient);
}
