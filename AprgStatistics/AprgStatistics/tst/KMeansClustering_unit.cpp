#include <KMeansClustering.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

using LocalKMeans = KMeansClustering<2>;
using LocalSamples = LocalKMeans::Samples;
using LocalSample = LocalKMeans::Sample;
using LocalGroupOfSamples = LocalKMeans::GroupOfSamples;

TEST(KMeansClusteringTestTwoDimensions, KMeansObjectCanbeCreated)
{
    LocalKMeans kMeans;
}

TEST(KMeansClusteringTestTwoDimensions, DataSampleCanBeAdded)
{
    LocalKMeans kMeans;
    kMeans.addSample(LocalSample{1,1});

    LocalSamples result(kMeans.getSamples());

    ASSERT_EQ(1u, result.size());
    EXPECT_EQ((LocalSample{1,1}), result[0]);
}

TEST(KMeansClusteringTestTwoDimensions, DataSamplesCanBeAdded)
{
    LocalKMeans kMeans;
    LocalSamples samples;
    samples.emplace_back(LocalSample{1,1});
    samples.emplace_back(LocalSample{2,2});
    kMeans.addSamples(samples);

    LocalSamples result(kMeans.getSamples());

    ASSERT_EQ(2u, result.size());
    EXPECT_EQ((LocalSample{1,1}), result[0]);
    EXPECT_EQ((LocalSample{2,2}), result[1]);
}

TEST(KMeansClusteringTestTwoDimensions, PerformKMeansWithNoSamples)
{
    LocalKMeans kMeans;

    LocalGroupOfSamples result(kMeans.getGroupOfSamplesUsingKMeans(1));

    ASSERT_EQ(1u, result.size());
}

TEST(KMeansClusteringTestTwoDimensions, PerformKMeansForOneSample)
{
    LocalKMeans kMeans;
    kMeans.addSample(LocalSample{1,1});

    LocalGroupOfSamples result(kMeans.getGroupOfSamplesUsingKMeans(1));

    ASSERT_EQ(1u, result.size());
    ASSERT_EQ(1u, result[0].size());
    EXPECT_EQ((LocalSample{1,1}), result[0][0]);
}

TEST(KMeansClusteringTestTwoDimensions, PerformKMeansForTwoGroupsWithSameValue)
{
    LocalKMeans kMeans;
    kMeans.addSample(LocalSample{1,1});
    kMeans.addSample(LocalSample{1,1});
    kMeans.addSample(LocalSample{1,1});
    kMeans.addSample(LocalSample{1,1});

    LocalGroupOfSamples result(kMeans.getGroupOfSamplesUsingKMeans(2));

    ASSERT_EQ(2u, result.size());
    ASSERT_EQ(4u, result[0].size());
    ASSERT_EQ(0u, result[1].size());
    EXPECT_EQ((LocalSample{1,1}), result[0][0]);
    EXPECT_EQ((LocalSample{1,1}), result[0][1]);
    EXPECT_EQ((LocalSample{1,1}), result[0][2]);
    EXPECT_EQ((LocalSample{1,1}), result[0][3]);
}

TEST(KMeansClusteringTestTwoDimensions, PerformKMeansForTwoGroupsWithTwoDifferentValues)
{
    LocalKMeans kMeans;
    kMeans.addSample(LocalSample{1,1});
    kMeans.addSample(LocalSample{2,2});
    kMeans.addSample(LocalSample{2,2});
    kMeans.addSample(LocalSample{2,2});

    LocalGroupOfSamples result(kMeans.getGroupOfSamplesUsingKMeans(2));

    ASSERT_EQ(2u, result.size());
    ASSERT_EQ(1u, result[0].size());
    ASSERT_EQ(3u, result[1].size());
    EXPECT_EQ((LocalSample{1,1}), result[0][0]);
    EXPECT_EQ((LocalSample{2,2}), result[1][0]);
    EXPECT_EQ((LocalSample{2,2}), result[1][1]);
    EXPECT_EQ((LocalSample{2,2}), result[1][2]);
}

TEST(KMeansClusteringTestTwoDimensions, PerformKMeansForTwoGroupsWithManyDifferentValues)
{
    LocalKMeans kMeans;
    kMeans.addSample(LocalSample{1,1});
    kMeans.addSample(LocalSample{1.5,2});
    kMeans.addSample(LocalSample{3,4});
    kMeans.addSample(LocalSample{5,7});
    kMeans.addSample(LocalSample{3.5,5});
    kMeans.addSample(LocalSample{4.5,5});
    kMeans.addSample(LocalSample{3.5,4.5});

    LocalGroupOfSamples result(kMeans.getGroupOfSamplesUsingKMeans(2));

    ASSERT_EQ(2u, result.size());
    ASSERT_EQ(2u, result[0].size());
    ASSERT_EQ(5u, result[1].size());
    EXPECT_EQ((LocalSample{1,1}), result[0][0]);
    EXPECT_EQ((LocalSample{1.5,2}), result[0][1]);
    EXPECT_EQ((LocalSample{3,4}), result[1][0]);
    EXPECT_EQ((LocalSample{5,7}), result[1][1]);
    EXPECT_EQ((LocalSample{3.5,5}), result[1][2]);
    EXPECT_EQ((LocalSample{4.5,5}), result[1][3]);
    EXPECT_EQ((LocalSample{3.5,4.5}), result[1][4]);
}

