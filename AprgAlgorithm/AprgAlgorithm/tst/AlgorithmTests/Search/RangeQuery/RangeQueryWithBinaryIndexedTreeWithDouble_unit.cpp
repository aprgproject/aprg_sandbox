#include <Algorithm/Search/RangeQuery/RangeQueryWithBinaryIndexedTree.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using ValuesForTest = vector<double>;
using RangeQueryForTest = RangeQueryWithBinaryIndexedTree<ValuesForTest>;
using ValueForTest = RangeQueryForTest::Value;
RangeQueryForTest::AccumulatorFunction multipliesAccumulator = multiplies<>();
RangeQueryForTest::AccumulatorFunction dividesAccumulator = divides<>();
}  // namespace

TEST(RangeQueryWithBinaryIndexedTreeTest, GetAccumulatedValueOnIntervalWithGeometricSumWorksWithEmptySetOfValues) {
    ValuesForTest values;
    RangeQueryForTest geometricSumRangeQuery(values, multipliesAccumulator, dividesAccumulator);

    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getAccumulatedValueOnInterval(0, 0));
}

TEST(RangeQueryWithBinaryIndexedTreeTest, GetAccumulatedValueOnIntervalWithGeometricSumWorksOnExample1) {
    ValuesForTest values{1, 3, 4, 8, 6, 1, 4, 2, 9};
    RangeQueryForTest geometricSumRangeQuery(values, multipliesAccumulator, dividesAccumulator);

    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getAccumulatedValueOnInterval(0, 0));
    EXPECT_DOUBLE_EQ(3, geometricSumRangeQuery.getAccumulatedValueOnInterval(0, 1));
    EXPECT_DOUBLE_EQ(12, geometricSumRangeQuery.getAccumulatedValueOnInterval(0, 2));
    EXPECT_DOUBLE_EQ(96, geometricSumRangeQuery.getAccumulatedValueOnInterval(0, 3));
    EXPECT_DOUBLE_EQ(576, geometricSumRangeQuery.getAccumulatedValueOnInterval(0, 4));
    EXPECT_DOUBLE_EQ(576, geometricSumRangeQuery.getAccumulatedValueOnInterval(0, 5));
    EXPECT_DOUBLE_EQ(2304, geometricSumRangeQuery.getAccumulatedValueOnInterval(0, 6));
    EXPECT_DOUBLE_EQ(4608, geometricSumRangeQuery.getAccumulatedValueOnInterval(0, 7));
    EXPECT_DOUBLE_EQ(41472, geometricSumRangeQuery.getAccumulatedValueOnInterval(0, 8));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getAccumulatedValueOnInterval(0, 9));
    EXPECT_DOUBLE_EQ(2304, geometricSumRangeQuery.getAccumulatedValueOnInterval(1, 6));
    EXPECT_DOUBLE_EQ(192, geometricSumRangeQuery.getAccumulatedValueOnInterval(2, 5));
    EXPECT_DOUBLE_EQ(48, geometricSumRangeQuery.getAccumulatedValueOnInterval(3, 4));
    EXPECT_DOUBLE_EQ(6, geometricSumRangeQuery.getAccumulatedValueOnInterval(4, 4));
}

TEST(RangeQueryWithBinaryIndexedTreeTest, GetSumFrom0ToIndexWithGeometricSumWorksWithEmptySetOfValues) {
    ValuesForTest values;
    RangeQueryForTest geometricSumRangeQuery(values, multipliesAccumulator, dividesAccumulator);

    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getAccumulatedValueFrom0ToIndex(0));
}

TEST(RangeQueryWithBinaryIndexedTreeTest, GetSumFrom0ToIndexWithGeometricSumWorksOnExample1) {
    ValuesForTest values{1, 3, 4, 8, 6, 1, 4, 2, 9};
    RangeQueryForTest geometricSumRangeQuery(values, multipliesAccumulator, dividesAccumulator);

    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getAccumulatedValueFrom0ToIndex(0));
    EXPECT_DOUBLE_EQ(3, geometricSumRangeQuery.getAccumulatedValueFrom0ToIndex(1));
    EXPECT_DOUBLE_EQ(12, geometricSumRangeQuery.getAccumulatedValueFrom0ToIndex(2));
    EXPECT_DOUBLE_EQ(96, geometricSumRangeQuery.getAccumulatedValueFrom0ToIndex(3));
    EXPECT_DOUBLE_EQ(576, geometricSumRangeQuery.getAccumulatedValueFrom0ToIndex(4));
    EXPECT_DOUBLE_EQ(576, geometricSumRangeQuery.getAccumulatedValueFrom0ToIndex(5));
    EXPECT_DOUBLE_EQ(2304, geometricSumRangeQuery.getAccumulatedValueFrom0ToIndex(6));
    EXPECT_DOUBLE_EQ(4608, geometricSumRangeQuery.getAccumulatedValueFrom0ToIndex(7));
    EXPECT_DOUBLE_EQ(41472, geometricSumRangeQuery.getAccumulatedValueFrom0ToIndex(8));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getAccumulatedValueFrom0ToIndex(9));
}

TEST(RangeQueryWithBinaryIndexedTreeTest, ChangeValueAtIndexWithGeometricSumWorksWithEmptySetOfValues) {
    ValuesForTest values;
    RangeQueryForTest geometricSumRangeQuery(values, multipliesAccumulator, dividesAccumulator);

    geometricSumRangeQuery.changeValueAtIndex(0, 0);

    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getAccumulatedValueOnInterval(0, 0));
}

TEST(RangeQueryWithBinaryIndexedTreeTest, ChangeValueAtIndexWithGeometricSumWorksOnExample1) {
    ValuesForTest values{1, 3, 4, 8, 6, 1, 4, 2, 9};
    RangeQueryForTest geometricSumRangeQuery(values, multipliesAccumulator, dividesAccumulator);

    geometricSumRangeQuery.changeValueAtIndex(3, 3);

    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getAccumulatedValueOnInterval(0, 0));
    EXPECT_DOUBLE_EQ(3, geometricSumRangeQuery.getAccumulatedValueOnInterval(0, 1));
    EXPECT_DOUBLE_EQ(12, geometricSumRangeQuery.getAccumulatedValueOnInterval(0, 2));
    EXPECT_DOUBLE_EQ(36, geometricSumRangeQuery.getAccumulatedValueOnInterval(0, 3));
    EXPECT_DOUBLE_EQ(216, geometricSumRangeQuery.getAccumulatedValueOnInterval(0, 4));
    EXPECT_DOUBLE_EQ(216, geometricSumRangeQuery.getAccumulatedValueOnInterval(0, 5));
    EXPECT_DOUBLE_EQ(864, geometricSumRangeQuery.getAccumulatedValueOnInterval(0, 6));
    EXPECT_DOUBLE_EQ(1728, geometricSumRangeQuery.getAccumulatedValueOnInterval(0, 7));
    EXPECT_DOUBLE_EQ(15552, geometricSumRangeQuery.getAccumulatedValueOnInterval(0, 8));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getAccumulatedValueOnInterval(0, 9));
    EXPECT_DOUBLE_EQ(864, geometricSumRangeQuery.getAccumulatedValueOnInterval(1, 6));
    EXPECT_DOUBLE_EQ(72, geometricSumRangeQuery.getAccumulatedValueOnInterval(2, 5));
    EXPECT_DOUBLE_EQ(18, geometricSumRangeQuery.getAccumulatedValueOnInterval(3, 4));
    EXPECT_DOUBLE_EQ(6, geometricSumRangeQuery.getAccumulatedValueOnInterval(4, 4));
}

}  // namespace algorithm

}  // namespace alba
