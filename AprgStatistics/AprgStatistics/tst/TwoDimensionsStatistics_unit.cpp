#include <TwoDimensionsStatistics.hpp>

#include <gtest/gtest.h>
#include <Debug/AlbaDebug.hpp>

#include <iostream>

using namespace alba;
using namespace std;

TEST(TwoDimensionsStatisticsTest, SameValuesOfXAndYForLineModeling)
{
    using LocalSample = TwoDimensionsStatistics::Sample;
    using LocalSamples = TwoDimensionsStatistics::Samples;
    using LocalLineModel = TwoDimensionsStatistics::LineModel;

    LocalSamples samples;
    samples.emplace_back(LocalSample{5,3});
    samples.emplace_back(LocalSample{5,3});
    samples.emplace_back(LocalSample{5,3});
    samples.emplace_back(LocalSample{5,3});
    samples.emplace_back(LocalSample{5,3});
    LocalLineModel lineModel(TwoDimensionsStatistics::calculateLineModelUsingLeastSquares(samples));

    EXPECT_EQ(0, lineModel.aCoefficient);
    EXPECT_EQ(0, lineModel.bCoefficient);
    EXPECT_EQ(0, lineModel.cCoefficient);
}

TEST(TwoDimensionsStatisticsTest, SameValuesOfXForLineModeling)
{
    using LocalSample = TwoDimensionsStatistics::Sample;
    using LocalSamples = TwoDimensionsStatistics::Samples;
    using LocalLineModel = TwoDimensionsStatistics::LineModel;

    LocalSamples samples;
    samples.emplace_back(LocalSample{5,0});
    samples.emplace_back(LocalSample{5,1});
    samples.emplace_back(LocalSample{5,2});
    samples.emplace_back(LocalSample{5,3});
    samples.emplace_back(LocalSample{5,4});
    samples.emplace_back(LocalSample{5,5});
    LocalLineModel lineModel(TwoDimensionsStatistics::calculateLineModelUsingLeastSquares(samples));

    EXPECT_EQ(1, lineModel.aCoefficient);
    EXPECT_EQ(0, lineModel.bCoefficient);
    EXPECT_EQ(-5, lineModel.cCoefficient);
}

TEST(TwoDimensionsStatisticsTest, SameValuesOfYForLineModeling)
{
    using LocalSample = TwoDimensionsStatistics::Sample;
    using LocalSamples = TwoDimensionsStatistics::Samples;
    using LocalLineModel = TwoDimensionsStatistics::LineModel;

    LocalSamples samples;
    samples.emplace_back(LocalSample{0,5});
    samples.emplace_back(LocalSample{1,5});
    samples.emplace_back(LocalSample{2,5});
    samples.emplace_back(LocalSample{3,5});
    samples.emplace_back(LocalSample{4,5});
    samples.emplace_back(LocalSample{5,5});
    LocalLineModel lineModel(TwoDimensionsStatistics::calculateLineModelUsingLeastSquares(samples));

    EXPECT_EQ(0, lineModel.aCoefficient);
    EXPECT_EQ(1, lineModel.bCoefficient);
    EXPECT_EQ(-5, lineModel.cCoefficient);
}

TEST(TwoDimensionsStatisticsTest, LineModelingWithPositiveSlope)
{
    using LocalSample = TwoDimensionsStatistics::Sample;
    using LocalSamples = TwoDimensionsStatistics::Samples;
    using LocalLineModel = TwoDimensionsStatistics::LineModel;

    LocalSamples samples;
    samples.emplace_back(LocalSample{0,0});
    samples.emplace_back(LocalSample{1,1});
    samples.emplace_back(LocalSample{2,2});
    samples.emplace_back(LocalSample{3,3});
    samples.emplace_back(LocalSample{4,4});
    samples.emplace_back(LocalSample{5,5});
    LocalLineModel lineModel(TwoDimensionsStatistics::calculateLineModelUsingLeastSquares(samples));

    EXPECT_EQ(-1, lineModel.aCoefficient);
    EXPECT_EQ(1, lineModel.bCoefficient);
    EXPECT_EQ(0, lineModel.cCoefficient);
}

TEST(TwoDimensionsStatisticsTest, LineModelingWithNegativeSlope)
{
    using LocalSample = TwoDimensionsStatistics::Sample;
    using LocalSamples = TwoDimensionsStatistics::Samples;
    using LocalLineModel = TwoDimensionsStatistics::LineModel;

    LocalSamples samples;
    samples.emplace_back(LocalSample{0,0});
    samples.emplace_back(LocalSample{1,-1});
    samples.emplace_back(LocalSample{2,-2});
    samples.emplace_back(LocalSample{3,-3});
    samples.emplace_back(LocalSample{4,-4});
    samples.emplace_back(LocalSample{5,-5});
    LocalLineModel lineModel(TwoDimensionsStatistics::calculateLineModelUsingLeastSquares(samples));

    EXPECT_EQ(1, lineModel.aCoefficient);
    EXPECT_EQ(1, lineModel.bCoefficient);
    EXPECT_EQ(0, lineModel.cCoefficient);
}

TEST(TwoDimensionsStatisticsTest, LineModelingWithPositiveYIntercept)
{
    using LocalSample = TwoDimensionsStatistics::Sample;
    using LocalSamples = TwoDimensionsStatistics::Samples;
    using LocalLineModel = TwoDimensionsStatistics::LineModel;

    LocalSamples samples;
    samples.emplace_back(LocalSample{0,1});
    samples.emplace_back(LocalSample{1,2});
    samples.emplace_back(LocalSample{2,3});
    samples.emplace_back(LocalSample{3,4});
    samples.emplace_back(LocalSample{4,5});
    samples.emplace_back(LocalSample{5,6});
    LocalLineModel lineModel(TwoDimensionsStatistics::calculateLineModelUsingLeastSquares(samples));

    EXPECT_EQ(-1, lineModel.aCoefficient);
    EXPECT_EQ(1, lineModel.bCoefficient);
    EXPECT_EQ(-1, lineModel.cCoefficient);
}

TEST(TwoDimensionsStatisticsTest, LineModelingWithPositiveXIntercept)
{
    using LocalSample = TwoDimensionsStatistics::Sample;
    using LocalSamples = TwoDimensionsStatistics::Samples;
    using LocalLineModel = TwoDimensionsStatistics::LineModel;

    LocalSamples samples;
    samples.emplace_back(LocalSample{1,0});
    samples.emplace_back(LocalSample{2,1});
    samples.emplace_back(LocalSample{3,2});
    samples.emplace_back(LocalSample{4,3});
    samples.emplace_back(LocalSample{5,4});
    samples.emplace_back(LocalSample{6,5});
    LocalLineModel lineModel(TwoDimensionsStatistics::calculateLineModelUsingLeastSquares(samples));

    EXPECT_EQ(-1, lineModel.aCoefficient);
    EXPECT_EQ(1, lineModel.bCoefficient);
    EXPECT_EQ(1, lineModel.cCoefficient);
}

TEST(TwoDimensionsStatisticsTest, LineModelingWithScatteredValue)
{
    using LocalSample = TwoDimensionsStatistics::Sample;
    using LocalSamples = TwoDimensionsStatistics::Samples;
    using LocalLineModel = TwoDimensionsStatistics::LineModel;

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

    EXPECT_EQ(1, lineModel.aCoefficient);
    EXPECT_EQ(-0.016144305895888833025, lineModel.bCoefficient);
    EXPECT_EQ(-0.64846044526167945232, lineModel.cCoefficient);
}

TEST(TwoDimensionsStatisticsTest, SquareErrorFromLineModelCanBeCalculatedForInvalidLine){
    using LocalSample = TwoDimensionsStatistics::Sample;
    using LocalLineModel = TwoDimensionsStatistics::LineModel;
    LocalLineModel lineModel(0, 0, 0);

    EXPECT_EQ(0, TwoDimensionsStatistics::calculateSquareError(LocalSample{5, 3}, lineModel));
    EXPECT_EQ(0, TwoDimensionsStatistics::calculateSquareError(LocalSample{7, 5}, lineModel));
}

TEST(TwoDimensionsStatisticsTest, SquareErrorFromLineModelCanBeCalculatedForVerticalLine)
{
    using LocalSample = TwoDimensionsStatistics::Sample;
    using LocalLineModel = TwoDimensionsStatistics::LineModel;

    LocalLineModel lineModel(-1, 0, 5);

    EXPECT_EQ(25, TwoDimensionsStatistics::calculateSquareError(LocalSample{10, 10}, lineModel));
}

TEST(TwoDimensionsStatisticsTest, SquareErrorFromLineModelCanBeCalculatedForHorizontalLine)
{
    using LocalSample = TwoDimensionsStatistics::Sample;
    using LocalLineModel = TwoDimensionsStatistics::LineModel;

    LocalLineModel lineModel(0, -1, 5);

    EXPECT_EQ(25, TwoDimensionsStatistics::calculateSquareError(LocalSample{10, 10}, lineModel));
}

TEST(TwoDimensionsStatisticsTest, SquareErrorFromLineModelCanBeCalculatedForScatteredPoints)
{
    using LocalSample = TwoDimensionsStatistics::Sample;
    using LocalLineModel = TwoDimensionsStatistics::LineModel;

    LocalLineModel lineModel(-61.27218654211062443, 1, 39.061955918843921154);

    EXPECT_EQ(1.4444234765251897645, TwoDimensionsStatistics::calculateSquareError(LocalSample{1.47, 52.21}, lineModel));
    EXPECT_EQ(0.55823592527027865451, TwoDimensionsStatistics::calculateSquareError(LocalSample{1.65, 61.29}, lineModel));
    EXPECT_EQ(1.9428304975833747825, TwoDimensionsStatistics::calculateSquareError(LocalSample{1.83, 74.46}, lineModel));
}

TEST(TwoDimensionsStatisticsTest, SamplesCanBeSortedBySquareErrorFromLineModelForInvalidLine)
{
    using LocalSample = TwoDimensionsStatistics::Sample;
    using LocalSamples = TwoDimensionsStatistics::Samples;
    using LocalLineModel = TwoDimensionsStatistics::LineModel;

    LocalSamples samples;
    samples.emplace_back(LocalSample{5,3});
    samples.emplace_back(LocalSample{5,3});
    samples.emplace_back(LocalSample{5,3});
    samples.emplace_back(LocalSample{5,3});
    samples.emplace_back(LocalSample{5,3});
    LocalLineModel lineModel(TwoDimensionsStatistics::calculateLineModelUsingLeastSquares(samples));
    TwoDimensionsStatistics::sortSamplesBySquareError(samples, lineModel);

    ASSERT_EQ(5, samples.size());
    EXPECT_EQ((LocalSample{5,3}), samples[0]);
    EXPECT_EQ((LocalSample{5,3}), samples[1]);
    EXPECT_EQ((LocalSample{5,3}), samples[2]);
    EXPECT_EQ((LocalSample{5,3}), samples[3]);
    EXPECT_EQ((LocalSample{5,3}), samples[4]);
}

TEST(TwoDimensionsStatisticsTest, SamplesCanBeSortedBySquareErrorFromLineModelForVerticalLine)
{
    using LocalSample = TwoDimensionsStatistics::Sample;
    using LocalSamples = TwoDimensionsStatistics::Samples;
    using LocalLineModel = TwoDimensionsStatistics::LineModel;

    LocalSamples samples;
    samples.emplace_back(LocalSample{5,0});
    samples.emplace_back(LocalSample{5,1});
    samples.emplace_back(LocalSample{5,2});
    samples.emplace_back(LocalSample{5,3});
    samples.emplace_back(LocalSample{5,4});
    samples.emplace_back(LocalSample{5,5});
    LocalLineModel lineModel(TwoDimensionsStatistics::calculateLineModelUsingLeastSquares(samples));
    TwoDimensionsStatistics::sortSamplesBySquareError(samples, lineModel);

    ASSERT_EQ(6, samples.size());
    EXPECT_EQ((LocalSample{5,0}), samples[0]);
    EXPECT_EQ((LocalSample{5,1}), samples[1]);
    EXPECT_EQ((LocalSample{5,2}), samples[2]);
    EXPECT_EQ((LocalSample{5,3}), samples[3]);
    EXPECT_EQ((LocalSample{5,4}), samples[4]);
    EXPECT_EQ((LocalSample{5,5}), samples[5]);
}

TEST(TwoDimensionsStatisticsTest, SamplesCanBeSortedBySquareErrorFromLineModelForHorizontalLine)
{
    using LocalSample = TwoDimensionsStatistics::Sample;
    using LocalSamples = TwoDimensionsStatistics::Samples;
    using LocalLineModel = TwoDimensionsStatistics::LineModel;

    LocalSamples samples;
    samples.emplace_back(LocalSample{0,5});
    samples.emplace_back(LocalSample{1,5});
    samples.emplace_back(LocalSample{2,5});
    samples.emplace_back(LocalSample{3,5});
    samples.emplace_back(LocalSample{4,5});
    samples.emplace_back(LocalSample{5,5});
    LocalLineModel lineModel(TwoDimensionsStatistics::calculateLineModelUsingLeastSquares(samples));
    TwoDimensionsStatistics::sortSamplesBySquareError(samples, lineModel);

    ASSERT_EQ(6, samples.size());
    EXPECT_EQ((LocalSample{0,5}), samples[0]);
    EXPECT_EQ((LocalSample{1,5}), samples[1]);
    EXPECT_EQ((LocalSample{2,5}), samples[2]);
    EXPECT_EQ((LocalSample{3,5}), samples[3]);
    EXPECT_EQ((LocalSample{4,5}), samples[4]);
    EXPECT_EQ((LocalSample{5,5}), samples[5]);
}

TEST(TwoDimensionsStatisticsTest, SamplesCanBeSortedBySquareErrorFromLineModelForScatteredPoints)
{
    using LocalSample = TwoDimensionsStatistics::Sample;
    using LocalSamples = TwoDimensionsStatistics::Samples;
    using LocalLineModel = TwoDimensionsStatistics::LineModel;

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
    TwoDimensionsStatistics::sortSamplesBySquareError(samples, lineModel);

    ASSERT_EQ(15, samples.size());
    EXPECT_EQ((LocalSample{1.75, 68.10}), samples[0]);
    EXPECT_EQ((LocalSample{1.57, 57.20}), samples[1]);
    EXPECT_EQ((LocalSample{1.55, 55.84}), samples[2]);
    EXPECT_EQ((LocalSample{1.78, 69.92}), samples[3]);
    EXPECT_EQ((LocalSample{1.50, 53.12}), samples[4]);
    EXPECT_EQ((LocalSample{1.60, 58.57}), samples[5]);
    EXPECT_EQ((LocalSample{1.52, 54.48}), samples[6]);
    EXPECT_EQ((LocalSample{1.70, 64.47}), samples[7]);
    EXPECT_EQ((LocalSample{1.73, 66.28}), samples[8]);
    EXPECT_EQ((LocalSample{1.65, 61.29}), samples[9]);
    EXPECT_EQ((LocalSample{1.68, 63.11}), samples[10]);
    EXPECT_EQ((LocalSample{1.63, 59.93}), samples[11]);
    EXPECT_EQ((LocalSample{1.80, 72.19}), samples[12]);
    EXPECT_EQ((LocalSample{1.47, 52.21}), samples[13]);
    EXPECT_EQ((LocalSample{1.83, 74.46}), samples[14]);
}
