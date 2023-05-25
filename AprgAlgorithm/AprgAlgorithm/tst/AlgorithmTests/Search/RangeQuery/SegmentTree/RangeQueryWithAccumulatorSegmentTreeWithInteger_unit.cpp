#include <Algorithm/Search/RangeQuery/SegmentTree/RangeQueryWithAccumulatorLazySegmentTree.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using ValuesForTest = vector<int>;
using RangeQueryForTest = RangeQueryWithAccumulatorLazySegmentTree<ValuesForTest>;
using ValueForTest = RangeQueryForTest::Value;
RangeQueryForTest::Function plusFunction = plus<>();
RangeQueryForTest::Function minusFunction = minus<>();
}  // namespace

TEST(RangeQueryWithAccumulatorLazySegmentTreeTest, GetValueOnIntervalWithMinimumWorksWithEmptySetOfValues) {
    ValuesForTest values;
    RangeQueryForTest sumRangeQuery(values, plusFunction, minusFunction, 0);

    EXPECT_EQ(0, sumRangeQuery.getValueOnInterval(0, 0));
}

TEST(RangeQueryWithAccumulatorLazySegmentTreeTest, GetValueOnIntervalWithSumWorksOnExample1) {
    ValuesForTest values{1, 3, 4, 8, 6, 1, 4, 2, 9};
    RangeQueryForTest sumRangeQuery(values, plusFunction, minusFunction, 0);

    EXPECT_EQ(1, sumRangeQuery.getValueOnInterval(0, 0));
    EXPECT_EQ(4, sumRangeQuery.getValueOnInterval(0, 1));
    EXPECT_EQ(8, sumRangeQuery.getValueOnInterval(0, 2));
    EXPECT_EQ(16, sumRangeQuery.getValueOnInterval(0, 3));
    EXPECT_EQ(22, sumRangeQuery.getValueOnInterval(0, 4));
    EXPECT_EQ(23, sumRangeQuery.getValueOnInterval(0, 5));
    EXPECT_EQ(27, sumRangeQuery.getValueOnInterval(0, 6));
    EXPECT_EQ(29, sumRangeQuery.getValueOnInterval(0, 7));
    EXPECT_EQ(38, sumRangeQuery.getValueOnInterval(0, 8));
    EXPECT_EQ(0, sumRangeQuery.getValueOnInterval(0, 9));
    EXPECT_EQ(26, sumRangeQuery.getValueOnInterval(1, 6));
    EXPECT_EQ(19, sumRangeQuery.getValueOnInterval(2, 5));
    EXPECT_EQ(14, sumRangeQuery.getValueOnInterval(3, 4));
    EXPECT_EQ(6, sumRangeQuery.getValueOnInterval(4, 4));
}

TEST(RangeQueryWithAccumulatorLazySegmentTreeTest, IncreaseAtRangeWithSumWorksWithEmptySetOfValues) {
    ValuesForTest values;
    RangeQueryForTest sumRangeQuery(values, plusFunction, minusFunction, 0);

    sumRangeQuery.increaseAtRange(0, 5, 4);

    EXPECT_EQ(0, sumRangeQuery.getValueOnInterval(0, 0));
}

TEST(RangeQueryWithAccumulatorLazySegmentTreeTest, IncreaseAtRangeWithSumWorksOnExample1) {
    ValuesForTest values{1, 3, 4, 8, 6, 1, 4, 2, 9};
    RangeQueryForTest sumRangeQuery(values, plusFunction, minusFunction, 0);

    sumRangeQuery.increaseAtRange(0, 5, 4);

    EXPECT_EQ(5, sumRangeQuery.getValueOnInterval(0, 0));
    EXPECT_EQ(12, sumRangeQuery.getValueOnInterval(0, 1));
    EXPECT_EQ(20, sumRangeQuery.getValueOnInterval(0, 2));
    EXPECT_EQ(32, sumRangeQuery.getValueOnInterval(0, 3));
    EXPECT_EQ(42, sumRangeQuery.getValueOnInterval(0, 4));
    EXPECT_EQ(47, sumRangeQuery.getValueOnInterval(0, 5));
    EXPECT_EQ(51, sumRangeQuery.getValueOnInterval(0, 6));
    EXPECT_EQ(53, sumRangeQuery.getValueOnInterval(0, 7));
    EXPECT_EQ(62, sumRangeQuery.getValueOnInterval(0, 8));
    EXPECT_EQ(0, sumRangeQuery.getValueOnInterval(0, 9));
    EXPECT_EQ(46, sumRangeQuery.getValueOnInterval(1, 6));
    EXPECT_EQ(35, sumRangeQuery.getValueOnInterval(2, 5));
    EXPECT_EQ(22, sumRangeQuery.getValueOnInterval(3, 4));
    EXPECT_EQ(10, sumRangeQuery.getValueOnInterval(4, 4));
}

TEST(RangeQueryWithAccumulatorLazySegmentTreeTest, ChangeValueAtIndexWithSumWorksWithEmptySetOfValues) {
    ValuesForTest values;
    RangeQueryForTest sumRangeQuery(values, plusFunction, minusFunction, 0);

    sumRangeQuery.changeValueAtIndex(0, 0);

    EXPECT_EQ(0, sumRangeQuery.getValueOnInterval(0, 0));
}

TEST(RangeQueryWithAccumulatorLazySegmentTreeTest, ChangeValueAtIndexWithSumWorksWithOneValue) {
    ValuesForTest values{5};
    RangeQueryForTest sumRangeQuery(values, plusFunction, minusFunction, 0);

    sumRangeQuery.changeValueAtIndex(0, 3);

    EXPECT_EQ(3, sumRangeQuery.getValueOnInterval(0, 0));
}

TEST(RangeQueryWithAccumulatorLazySegmentTreeTest, ChangeValueAtIndexWithSumWorksOnExample1) {
    ValuesForTest values{1, 3, 4, 8, 6, 1, 4, 2, 9};
    RangeQueryForTest sumRangeQuery(values, plusFunction, minusFunction, 0);

    sumRangeQuery.changeValueAtIndex(3, 3);

    EXPECT_EQ(1, sumRangeQuery.getValueOnInterval(0, 0));
    EXPECT_EQ(4, sumRangeQuery.getValueOnInterval(0, 1));
    EXPECT_EQ(8, sumRangeQuery.getValueOnInterval(0, 2));
    EXPECT_EQ(11, sumRangeQuery.getValueOnInterval(0, 3));
    EXPECT_EQ(17, sumRangeQuery.getValueOnInterval(0, 4));
    EXPECT_EQ(18, sumRangeQuery.getValueOnInterval(0, 5));
    EXPECT_EQ(22, sumRangeQuery.getValueOnInterval(0, 6));
    EXPECT_EQ(24, sumRangeQuery.getValueOnInterval(0, 7));
    EXPECT_EQ(33, sumRangeQuery.getValueOnInterval(0, 8));
    EXPECT_EQ(0, sumRangeQuery.getValueOnInterval(0, 9));
    EXPECT_EQ(21, sumRangeQuery.getValueOnInterval(1, 6));
    EXPECT_EQ(14, sumRangeQuery.getValueOnInterval(2, 5));
    EXPECT_EQ(9, sumRangeQuery.getValueOnInterval(3, 4));
    EXPECT_EQ(6, sumRangeQuery.getValueOnInterval(4, 4));
}

}  // namespace algorithm

}  // namespace alba
