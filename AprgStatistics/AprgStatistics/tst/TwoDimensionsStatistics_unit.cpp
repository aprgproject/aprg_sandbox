#include <TwoDimensionsStatistics.hpp>

#include <gtest/gtest.h>

#include <iostream>

using namespace std;

namespace alba
{

using LocalSample = TwoDimensionsStatistics::Sample;
using LocalSamples = TwoDimensionsStatistics::Samples;
using LocalLineModel = TwoDimensionsStatistics::LineModel;
using LocalValueToSampleMultimap = TwoDimensionsStatistics::ValueToSampleMultimap;
using LocalValueToSamplePair = TwoDimensionsStatistics::ValueToSamplePair;

TEST(TwoDimensionsStatisticsTest, SameValuesOfXAndYForLineModeling)
{
    LocalSamples samples;
    samples.emplace_back(LocalSample{5,3});
    samples.emplace_back(LocalSample{5,3});
    samples.emplace_back(LocalSample{5,3});
    samples.emplace_back(LocalSample{5,3});
    samples.emplace_back(LocalSample{5,3});
    LocalLineModel lineModel(TwoDimensionsStatistics::calculateLineModelUsingLeastSquares(samples));

    EXPECT_DOUBLE_EQ(0, lineModel.aCoefficient);
    EXPECT_DOUBLE_EQ(0, lineModel.bCoefficient);
    EXPECT_DOUBLE_EQ(0, lineModel.cCoefficient);
}

TEST(TwoDimensionsStatisticsTest, SameValuesOfXForLineModeling)
{
    LocalSamples samples;
    samples.emplace_back(LocalSample{5,0});
    samples.emplace_back(LocalSample{5,1});
    samples.emplace_back(LocalSample{5,2});
    samples.emplace_back(LocalSample{5,3});
    samples.emplace_back(LocalSample{5,4});
    samples.emplace_back(LocalSample{5,5});
    LocalLineModel lineModel(TwoDimensionsStatistics::calculateLineModelUsingLeastSquares(samples));

    EXPECT_DOUBLE_EQ(1, lineModel.aCoefficient);
    EXPECT_DOUBLE_EQ(0, lineModel.bCoefficient);
    EXPECT_DOUBLE_EQ(-5, lineModel.cCoefficient);
}

TEST(TwoDimensionsStatisticsTest, SameValuesOfYForLineModeling)
{
    LocalSamples samples;
    samples.emplace_back(LocalSample{0,5});
    samples.emplace_back(LocalSample{1,5});
    samples.emplace_back(LocalSample{2,5});
    samples.emplace_back(LocalSample{3,5});
    samples.emplace_back(LocalSample{4,5});
    samples.emplace_back(LocalSample{5,5});
    LocalLineModel lineModel(TwoDimensionsStatistics::calculateLineModelUsingLeastSquares(samples));

    EXPECT_DOUBLE_EQ(0, lineModel.aCoefficient);
    EXPECT_DOUBLE_EQ(1, lineModel.bCoefficient);
    EXPECT_DOUBLE_EQ(-5, lineModel.cCoefficient);
}

TEST(TwoDimensionsStatisticsTest, LineModelingWithPositiveSlope)
{
    LocalSamples samples;
    samples.emplace_back(LocalSample{0,0});
    samples.emplace_back(LocalSample{1,1});
    samples.emplace_back(LocalSample{2,2});
    samples.emplace_back(LocalSample{3,3});
    samples.emplace_back(LocalSample{4,4});
    samples.emplace_back(LocalSample{5,5});
    LocalLineModel lineModel(TwoDimensionsStatistics::calculateLineModelUsingLeastSquares(samples));

    EXPECT_DOUBLE_EQ(-1, lineModel.aCoefficient);
    EXPECT_DOUBLE_EQ(1, lineModel.bCoefficient);
    EXPECT_DOUBLE_EQ(0, lineModel.cCoefficient);
}

TEST(TwoDimensionsStatisticsTest, LineModelingWithNegativeSlope)
{
    LocalSamples samples;
    samples.emplace_back(LocalSample{0,0});
    samples.emplace_back(LocalSample{1,-1});
    samples.emplace_back(LocalSample{2,-2});
    samples.emplace_back(LocalSample{3,-3});
    samples.emplace_back(LocalSample{4,-4});
    samples.emplace_back(LocalSample{5,-5});
    LocalLineModel lineModel(TwoDimensionsStatistics::calculateLineModelUsingLeastSquares(samples));

    EXPECT_DOUBLE_EQ(1, lineModel.aCoefficient);
    EXPECT_DOUBLE_EQ(1, lineModel.bCoefficient);
    EXPECT_DOUBLE_EQ(0, lineModel.cCoefficient);
}

TEST(TwoDimensionsStatisticsTest, LineModelingWithPositiveYIntercept)
{
    LocalSamples samples;
    samples.emplace_back(LocalSample{0,1});
    samples.emplace_back(LocalSample{1,2});
    samples.emplace_back(LocalSample{2,3});
    samples.emplace_back(LocalSample{3,4});
    samples.emplace_back(LocalSample{4,5});
    samples.emplace_back(LocalSample{5,6});
    LocalLineModel lineModel(TwoDimensionsStatistics::calculateLineModelUsingLeastSquares(samples));

    EXPECT_DOUBLE_EQ(-1, lineModel.aCoefficient);
    EXPECT_DOUBLE_EQ(1, lineModel.bCoefficient);
    EXPECT_DOUBLE_EQ(-1, lineModel.cCoefficient);
}

TEST(TwoDimensionsStatisticsTest, LineModelingWithPositiveXIntercept)
{
    LocalSamples samples;
    samples.emplace_back(LocalSample{1,0});
    samples.emplace_back(LocalSample{2,1});
    samples.emplace_back(LocalSample{3,2});
    samples.emplace_back(LocalSample{4,3});
    samples.emplace_back(LocalSample{5,4});
    samples.emplace_back(LocalSample{6,5});
    LocalLineModel lineModel(TwoDimensionsStatistics::calculateLineModelUsingLeastSquares(samples));

    EXPECT_DOUBLE_EQ(-1, lineModel.aCoefficient);
    EXPECT_DOUBLE_EQ(1, lineModel.bCoefficient);
    EXPECT_DOUBLE_EQ(1, lineModel.cCoefficient);
}

TEST(TwoDimensionsStatisticsTest, LineModelingWithScatteredValue)
{
    LocalSamples samples;
    samples.emplace_back(LocalSample{1.47, 52.21});
    samples.emplace_back(LocalSample{1.50, 53.12});
    samples.emplace_back(LocalSample{1.52, 54.48});
    samples.emplace_back(LocalSample{1.55, 55.84});
    samples.emplace_back(LocalSample{1.57, 57.20});
    samples.emplace_back(LocalSample{1.60, 58.57});
    samples.emplace_back(LocalSample{1.63, 59.93});
    samples.emplace_back(LocalSample{1.65, 61.29});
    samples.emplace_back(LocalSample{1.68, 63.11});
    samples.emplace_back(LocalSample{1.70, 64.47});
    samples.emplace_back(LocalSample{1.73, 66.28});
    samples.emplace_back(LocalSample{1.75, 68.10});
    samples.emplace_back(LocalSample{1.78, 69.92});
    samples.emplace_back(LocalSample{1.80, 72.19});
    samples.emplace_back(LocalSample{1.83, 74.46});
    LocalLineModel lineModel(TwoDimensionsStatistics::calculateLineModelUsingLeastSquares(samples));

    EXPECT_DOUBLE_EQ(1, lineModel.aCoefficient);
    EXPECT_DOUBLE_EQ(-0.016144305895888833025, lineModel.bCoefficient);
    EXPECT_DOUBLE_EQ(-0.64846044526168001, lineModel.cCoefficient);
}

TEST(TwoDimensionsStatisticsTest, SquareErrorFromLineModelCanBeCalculatedForInvalidLine)
{
    LocalLineModel lineModel(0, 0, 0);

    EXPECT_EQ(0, TwoDimensionsStatistics::calculateSquareError(LocalSample{5, 3}, lineModel));
    EXPECT_EQ(0, TwoDimensionsStatistics::calculateSquareError(LocalSample{7, 5}, lineModel));
}

TEST(TwoDimensionsStatisticsTest, SquareErrorFromLineModelCanBeCalculatedForVerticalLine)
{
    LocalLineModel lineModel(-1, 0, 5);

    EXPECT_EQ(25, TwoDimensionsStatistics::calculateSquareError(LocalSample{10, 10}, lineModel));
}

TEST(TwoDimensionsStatisticsTest, SquareErrorFromLineModelCanBeCalculatedForHorizontalLine)
{
    LocalLineModel lineModel(0, -1, 5);

    EXPECT_EQ(25, TwoDimensionsStatistics::calculateSquareError(LocalSample{10, 10}, lineModel));
}

TEST(TwoDimensionsStatisticsTest, SquareErrorFromLineModelCanBeCalculatedForScatteredPoints)
{
    LocalLineModel lineModel(-61.27218654211062443, 1, 39.061955918843921154);

    EXPECT_EQ(1.4444234765251897645, TwoDimensionsStatistics::calculateSquareError(LocalSample{1.47, 52.21}, lineModel));
    EXPECT_EQ(0.55823592527027865451, TwoDimensionsStatistics::calculateSquareError(LocalSample{1.65, 61.29}, lineModel));
    EXPECT_EQ(1.9428304975833747825, TwoDimensionsStatistics::calculateSquareError(LocalSample{1.83, 74.46}, lineModel));
}

TEST(TwoDimensionsStatisticsTest, SamplesCanBeSortedBySquareErrorFromLineModelForInvalidLine)
{
    LocalSamples samples;
    samples.emplace_back(LocalSample{5,3});
    samples.emplace_back(LocalSample{5,3});
    samples.emplace_back(LocalSample{5,3});
    samples.emplace_back(LocalSample{5,3});
    samples.emplace_back(LocalSample{5,3});
    LocalLineModel lineModel(TwoDimensionsStatistics::calculateLineModelUsingLeastSquares(samples));
    LocalValueToSampleMultimap squareErrorToSampleMultimap(TwoDimensionsStatistics::getSquareErrorToSampleMultimap(samples, lineModel));

    ASSERT_EQ(5U, squareErrorToSampleMultimap.size());
    LocalValueToSampleMultimap::iterator it=squareErrorToSampleMultimap.begin();
    EXPECT_EQ((LocalSample{5,3}), it++->second);
    EXPECT_EQ((LocalSample{5,3}), it++->second);
    EXPECT_EQ((LocalSample{5,3}), it++->second);
    EXPECT_EQ((LocalSample{5,3}), it++->second);
    EXPECT_EQ((LocalSample{5,3}), it++->second);
}

TEST(TwoDimensionsStatisticsTest, SamplesCanBeSortedBySquareErrorFromLineModelForVerticalLine)
{
    LocalSamples samples;
    samples.emplace_back(LocalSample{5,0});
    samples.emplace_back(LocalSample{5,1});
    samples.emplace_back(LocalSample{5,2});
    samples.emplace_back(LocalSample{5,3});
    samples.emplace_back(LocalSample{5,4});
    samples.emplace_back(LocalSample{5,5});
    LocalLineModel lineModel(TwoDimensionsStatistics::calculateLineModelUsingLeastSquares(samples));
    LocalValueToSampleMultimap squareErrorToSampleMultimap(TwoDimensionsStatistics::getSquareErrorToSampleMultimap(samples, lineModel));

    ASSERT_EQ(6U, squareErrorToSampleMultimap.size());
    LocalValueToSampleMultimap::iterator it=squareErrorToSampleMultimap.begin();
    EXPECT_EQ((LocalSample{5,0}), it++->second);
    EXPECT_EQ((LocalSample{5,1}), it++->second);
    EXPECT_EQ((LocalSample{5,2}), it++->second);
    EXPECT_EQ((LocalSample{5,3}), it++->second);
    EXPECT_EQ((LocalSample{5,4}), it++->second);
    EXPECT_EQ((LocalSample{5,5}), it++->second);
}

TEST(TwoDimensionsStatisticsTest, SamplesCanBeSortedBySquareErrorFromLineModelForHorizontalLine)
{
    LocalSamples samples;
    samples.emplace_back(LocalSample{0,5});
    samples.emplace_back(LocalSample{1,5});
    samples.emplace_back(LocalSample{2,5});
    samples.emplace_back(LocalSample{3,5});
    samples.emplace_back(LocalSample{4,5});
    samples.emplace_back(LocalSample{5,5});
    LocalLineModel lineModel(TwoDimensionsStatistics::calculateLineModelUsingLeastSquares(samples));
    LocalValueToSampleMultimap squareErrorToSampleMultimap(TwoDimensionsStatistics::getSquareErrorToSampleMultimap(samples, lineModel));

    ASSERT_EQ(6U, squareErrorToSampleMultimap.size());
    LocalValueToSampleMultimap::iterator it=squareErrorToSampleMultimap.begin();
    EXPECT_EQ((LocalSample{0,5}), it++->second);
    EXPECT_EQ((LocalSample{1,5}), it++->second);
    EXPECT_EQ((LocalSample{2,5}), it++->second);
    EXPECT_EQ((LocalSample{3,5}), it++->second);
    EXPECT_EQ((LocalSample{4,5}), it++->second);
    EXPECT_EQ((LocalSample{5,5}), it++->second);
}

TEST(TwoDimensionsStatisticsTest, SamplesCanBeSortedBySquareErrorFromLineModelForScatteredPoints)
{
    LocalSamples samples;
    samples.emplace_back(LocalSample{1.47, 52.21});
    samples.emplace_back(LocalSample{1.50, 53.12});
    samples.emplace_back(LocalSample{1.52, 54.48});
    samples.emplace_back(LocalSample{1.55, 55.84});
    samples.emplace_back(LocalSample{1.57, 57.20});
    samples.emplace_back(LocalSample{1.60, 58.57});
    samples.emplace_back(LocalSample{1.63, 59.93});
    samples.emplace_back(LocalSample{1.65, 61.29});
    samples.emplace_back(LocalSample{1.68, 63.11});
    samples.emplace_back(LocalSample{1.70, 64.47});
    samples.emplace_back(LocalSample{1.73, 66.28});
    samples.emplace_back(LocalSample{1.75, 68.10});
    samples.emplace_back(LocalSample{1.78, 69.92});
    samples.emplace_back(LocalSample{1.80, 72.19});
    samples.emplace_back(LocalSample{1.83, 74.46});

    LocalLineModel lineModel(-61.27218654211062443, 1, 39.061955918843921154);
    LocalValueToSampleMultimap squareErrorToSampleMultimap(TwoDimensionsStatistics::getSquareErrorToSampleMultimap(samples, lineModel));

    ASSERT_EQ(15U, squareErrorToSampleMultimap.size());
    LocalValueToSampleMultimap::iterator it=squareErrorToSampleMultimap.begin();
    EXPECT_EQ((LocalSample{1.75, 68.10}), it++->second);
    EXPECT_EQ((LocalSample{1.57, 57.20}), it++->second);
    EXPECT_EQ((LocalSample{1.55, 55.84}), it++->second);
    EXPECT_EQ((LocalSample{1.78, 69.92}), it++->second);
    EXPECT_EQ((LocalSample{1.50, 53.12}), it++->second);
    EXPECT_EQ((LocalSample{1.60, 58.57}), it++->second);
    EXPECT_EQ((LocalSample{1.52, 54.48}), it++->second);
    EXPECT_EQ((LocalSample{1.70, 64.47}), it++->second);
    EXPECT_EQ((LocalSample{1.73, 66.28}), it++->second);
    EXPECT_EQ((LocalSample{1.65, 61.29}), it++->second);
    EXPECT_EQ((LocalSample{1.68, 63.11}), it++->second);
    EXPECT_EQ((LocalSample{1.63, 59.93}), it++->second);
    EXPECT_EQ((LocalSample{1.80, 72.19}), it++->second);
    EXPECT_EQ((LocalSample{1.47, 52.21}), it++->second);
    EXPECT_EQ((LocalSample{1.83, 74.46}), it++->second);
}

}
