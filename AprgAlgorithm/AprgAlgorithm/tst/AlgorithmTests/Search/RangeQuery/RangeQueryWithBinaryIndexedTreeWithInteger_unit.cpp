#include <Algorithm/Search/RangeQuery/RangeQueryWithBinaryIndexedTree.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using ValuesForTest = vector<int>;
using RangeQueryForTest = RangeQueryWithBinaryIndexedTree<ValuesForTest>;
using ValueForTest = RangeQueryForTest::Value;
RangeQueryForTest::AccumulatorFunction plusAccumulator = plus<>();
RangeQueryForTest::AccumulatorFunction minusAccumulator = minus<>();
}  // namespace

TEST(RangeQueryWithBinaryIndexedTreeTest, GetAccumulatedValueOnIntervalWithSumWorksWithEmptySetOfValues) {
    ValuesForTest values;
    RangeQueryForTest sumRangeQuery(values, plusAccumulator, minusAccumulator);

    EXPECT_EQ(0, sumRangeQuery.getAccumulatedValueOnInterval(0, 0));
}

TEST(RangeQueryWithBinaryIndexedTreeTest, GetAccumulatedValueOnIntervalWithSumWorksOnExample1) {
    ValuesForTest values{1, 3, 4, 8, 6, 1, 4, 2, 9};
    RangeQueryForTest sumRangeQuery(values, plusAccumulator, minusAccumulator);

    EXPECT_EQ(1, sumRangeQuery.getAccumulatedValueOnInterval(0, 0));
    EXPECT_EQ(4, sumRangeQuery.getAccumulatedValueOnInterval(0, 1));
    EXPECT_EQ(8, sumRangeQuery.getAccumulatedValueOnInterval(0, 2));
    EXPECT_EQ(16, sumRangeQuery.getAccumulatedValueOnInterval(0, 3));
    EXPECT_EQ(22, sumRangeQuery.getAccumulatedValueOnInterval(0, 4));
    EXPECT_EQ(23, sumRangeQuery.getAccumulatedValueOnInterval(0, 5));
    EXPECT_EQ(27, sumRangeQuery.getAccumulatedValueOnInterval(0, 6));
    EXPECT_EQ(29, sumRangeQuery.getAccumulatedValueOnInterval(0, 7));
    EXPECT_EQ(38, sumRangeQuery.getAccumulatedValueOnInterval(0, 8));
    EXPECT_EQ(0, sumRangeQuery.getAccumulatedValueOnInterval(0, 9));
    EXPECT_EQ(26, sumRangeQuery.getAccumulatedValueOnInterval(1, 6));
    EXPECT_EQ(19, sumRangeQuery.getAccumulatedValueOnInterval(2, 5));
    EXPECT_EQ(14, sumRangeQuery.getAccumulatedValueOnInterval(3, 4));
    EXPECT_EQ(6, sumRangeQuery.getAccumulatedValueOnInterval(4, 4));
}

TEST(RangeQueryWithBinaryIndexedTreeTest, GetSumFrom0ToIndexWithSumWorksWithEmptySetOfValues) {
    ValuesForTest values;
    RangeQueryForTest sumRangeQuery(values, plusAccumulator, minusAccumulator);

    EXPECT_EQ(0, sumRangeQuery.getAccumulatedValueFrom0ToIndex(0));
}

TEST(RangeQueryWithBinaryIndexedTreeTest, GetSumFrom0ToIndexWithSumWorksOnExample1) {
    ValuesForTest values{1, 3, 4, 8, 6, 1, 4, 2, 9};
    RangeQueryForTest sumRangeQuery(values, plusAccumulator, minusAccumulator);

    EXPECT_EQ(1, sumRangeQuery.getAccumulatedValueFrom0ToIndex(0));
    EXPECT_EQ(4, sumRangeQuery.getAccumulatedValueFrom0ToIndex(1));
    EXPECT_EQ(8, sumRangeQuery.getAccumulatedValueFrom0ToIndex(2));
    EXPECT_EQ(16, sumRangeQuery.getAccumulatedValueFrom0ToIndex(3));
    EXPECT_EQ(22, sumRangeQuery.getAccumulatedValueFrom0ToIndex(4));
    EXPECT_EQ(23, sumRangeQuery.getAccumulatedValueFrom0ToIndex(5));
    EXPECT_EQ(27, sumRangeQuery.getAccumulatedValueFrom0ToIndex(6));
    EXPECT_EQ(29, sumRangeQuery.getAccumulatedValueFrom0ToIndex(7));
    EXPECT_EQ(38, sumRangeQuery.getAccumulatedValueFrom0ToIndex(8));
    EXPECT_EQ(0, sumRangeQuery.getAccumulatedValueFrom0ToIndex(9));
}

TEST(RangeQueryWithBinaryIndexedTreeTest, ChangeValueAtIndexWithSumWorksWithEmptySetOfValues) {
    ValuesForTest values;
    RangeQueryForTest sumRangeQuery(values, plusAccumulator, minusAccumulator);

    sumRangeQuery.changeValueAtIndex(0, 0);

    EXPECT_EQ(0, sumRangeQuery.getAccumulatedValueOnInterval(0, 0));
}

TEST(RangeQueryWithBinaryIndexedTreeTest, ChangeValueAtIndexWithSumWorksOnExample1) {
    ValuesForTest values{1, 3, 4, 8, 6, 1, 4, 2, 9};
    RangeQueryForTest sumRangeQuery(values, plusAccumulator, minusAccumulator);

    sumRangeQuery.changeValueAtIndex(3, 3);

    EXPECT_EQ(1, sumRangeQuery.getAccumulatedValueOnInterval(0, 0));
    EXPECT_EQ(4, sumRangeQuery.getAccumulatedValueOnInterval(0, 1));
    EXPECT_EQ(8, sumRangeQuery.getAccumulatedValueOnInterval(0, 2));
    EXPECT_EQ(11, sumRangeQuery.getAccumulatedValueOnInterval(0, 3));
    EXPECT_EQ(17, sumRangeQuery.getAccumulatedValueOnInterval(0, 4));
    EXPECT_EQ(18, sumRangeQuery.getAccumulatedValueOnInterval(0, 5));
    EXPECT_EQ(22, sumRangeQuery.getAccumulatedValueOnInterval(0, 6));
    EXPECT_EQ(24, sumRangeQuery.getAccumulatedValueOnInterval(0, 7));
    EXPECT_EQ(33, sumRangeQuery.getAccumulatedValueOnInterval(0, 8));
    EXPECT_EQ(0, sumRangeQuery.getAccumulatedValueOnInterval(0, 9));
    EXPECT_EQ(21, sumRangeQuery.getAccumulatedValueOnInterval(1, 6));
    EXPECT_EQ(14, sumRangeQuery.getAccumulatedValueOnInterval(2, 5));
    EXPECT_EQ(9, sumRangeQuery.getAccumulatedValueOnInterval(3, 4));
    EXPECT_EQ(6, sumRangeQuery.getAccumulatedValueOnInterval(4, 4));
}

TEST(RangeQueryWithBinaryIndexedTreeTest, ChangeValueAtIndexWithSumWorksTwiceOnExample1) {
    ValuesForTest values{1, 3, 4, 8, 6, 1, 4, 2, 9};
    RangeQueryForTest sumRangeQuery(values, plusAccumulator, minusAccumulator);

    sumRangeQuery.changeValueAtIndex(3, 3);
    sumRangeQuery.changeValueAtIndex(3, 13);

    EXPECT_EQ(1, sumRangeQuery.getAccumulatedValueOnInterval(0, 0));
    EXPECT_EQ(4, sumRangeQuery.getAccumulatedValueOnInterval(0, 1));
    EXPECT_EQ(8, sumRangeQuery.getAccumulatedValueOnInterval(0, 2));
    EXPECT_EQ(21, sumRangeQuery.getAccumulatedValueOnInterval(0, 3));
    EXPECT_EQ(27, sumRangeQuery.getAccumulatedValueOnInterval(0, 4));
    EXPECT_EQ(28, sumRangeQuery.getAccumulatedValueOnInterval(0, 5));
    EXPECT_EQ(32, sumRangeQuery.getAccumulatedValueOnInterval(0, 6));
    EXPECT_EQ(34, sumRangeQuery.getAccumulatedValueOnInterval(0, 7));
    EXPECT_EQ(43, sumRangeQuery.getAccumulatedValueOnInterval(0, 8));
    EXPECT_EQ(0, sumRangeQuery.getAccumulatedValueOnInterval(0, 9));
    EXPECT_EQ(31, sumRangeQuery.getAccumulatedValueOnInterval(1, 6));
    EXPECT_EQ(24, sumRangeQuery.getAccumulatedValueOnInterval(2, 5));
    EXPECT_EQ(19, sumRangeQuery.getAccumulatedValueOnInterval(3, 4));
    EXPECT_EQ(6, sumRangeQuery.getAccumulatedValueOnInterval(4, 4));
}

}  // namespace algorithm

}  // namespace alba
