#include <Algorithm/Search/RangeQuery/SegmentTree/RangeQueryWithSparseSegmentTree.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using ValueForTest = int;
using RangeQueryForTest = RangeQueryWithSparseSegmentTree<ValueForTest>;

RangeQueryForTest::Function minimumFunction = [](ValueForTest const& value1, ValueForTest const& value2) {
    return min(value1, value2);
};

RangeQueryForTest::Function maximumFunction = [](ValueForTest const& value1, ValueForTest const& value2) {
    return max(value1, value2);
};

RangeQueryForTest::Function plusFunction = plus<>();
}  // namespace

TEST(RangeQueryWithSparseSegmentTreeTest, GetValueOnIntervalWithMinimumWorksWithZeroNumberOfValues) {
    RangeQueryForTest minimumRangeQuery(0, 0, minimumFunction);

    EXPECT_EQ(0, minimumRangeQuery.getValueOnInterval(0, 0));
}

TEST(RangeQueryWithSparseSegmentTreeTest, GetValueOnIntervalWithMinimumWorksOnExample1) {
    RangeQueryForTest minimumRangeQuery(9, 0, minimumFunction);

    EXPECT_EQ(0, minimumRangeQuery.getValueOnInterval(0, 0));
    EXPECT_EQ(0, minimumRangeQuery.getValueOnInterval(0, 1));
    EXPECT_EQ(0, minimumRangeQuery.getValueOnInterval(0, 2));
    EXPECT_EQ(0, minimumRangeQuery.getValueOnInterval(0, 3));
    EXPECT_EQ(0, minimumRangeQuery.getValueOnInterval(0, 4));
    EXPECT_EQ(0, minimumRangeQuery.getValueOnInterval(0, 5));
    EXPECT_EQ(0, minimumRangeQuery.getValueOnInterval(0, 6));
    EXPECT_EQ(0, minimumRangeQuery.getValueOnInterval(0, 7));
    EXPECT_EQ(0, minimumRangeQuery.getValueOnInterval(0, 8));
    EXPECT_EQ(0, minimumRangeQuery.getValueOnInterval(0, 9));
    EXPECT_EQ(0, minimumRangeQuery.getValueOnInterval(3, 6));
    EXPECT_EQ(0, minimumRangeQuery.getValueOnInterval(2, 4));
}

TEST(RangeQueryWithSparseSegmentTreeTest, GetValueOnIntervalWithMaximumWorksOnExample1) {
    RangeQueryForTest maximumRangeQuery(9, 0, maximumFunction);

    EXPECT_EQ(0, maximumRangeQuery.getValueOnInterval(0, 0));
    EXPECT_EQ(0, maximumRangeQuery.getValueOnInterval(0, 1));
    EXPECT_EQ(0, maximumRangeQuery.getValueOnInterval(0, 2));
    EXPECT_EQ(0, maximumRangeQuery.getValueOnInterval(0, 3));
    EXPECT_EQ(0, maximumRangeQuery.getValueOnInterval(0, 4));
    EXPECT_EQ(0, maximumRangeQuery.getValueOnInterval(0, 5));
    EXPECT_EQ(0, maximumRangeQuery.getValueOnInterval(0, 6));
    EXPECT_EQ(0, maximumRangeQuery.getValueOnInterval(0, 7));
    EXPECT_EQ(0, maximumRangeQuery.getValueOnInterval(0, 8));
    EXPECT_EQ(0, maximumRangeQuery.getValueOnInterval(0, 9));
    EXPECT_EQ(0, maximumRangeQuery.getValueOnInterval(3, 6));
    EXPECT_EQ(0, maximumRangeQuery.getValueOnInterval(2, 4));
}

TEST(RangeQueryWithSparseSegmentTreeTest, GetValueOnIntervalWithSumWorksOnExample1) {
    RangeQueryForTest sumRangeQuery(9, 0, plusFunction);

    EXPECT_EQ(0, sumRangeQuery.getValueOnInterval(0, 0));
    EXPECT_EQ(0, sumRangeQuery.getValueOnInterval(0, 1));
    EXPECT_EQ(0, sumRangeQuery.getValueOnInterval(0, 2));
    EXPECT_EQ(0, sumRangeQuery.getValueOnInterval(0, 3));
    EXPECT_EQ(0, sumRangeQuery.getValueOnInterval(0, 4));
    EXPECT_EQ(0, sumRangeQuery.getValueOnInterval(0, 5));
    EXPECT_EQ(0, sumRangeQuery.getValueOnInterval(0, 6));
    EXPECT_EQ(0, sumRangeQuery.getValueOnInterval(0, 7));
    EXPECT_EQ(0, sumRangeQuery.getValueOnInterval(0, 8));
    EXPECT_EQ(0, sumRangeQuery.getValueOnInterval(0, 9));
    EXPECT_EQ(0, sumRangeQuery.getValueOnInterval(1, 6));
    EXPECT_EQ(0, sumRangeQuery.getValueOnInterval(2, 5));
    EXPECT_EQ(0, sumRangeQuery.getValueOnInterval(3, 4));
    EXPECT_EQ(0, sumRangeQuery.getValueOnInterval(4, 4));
}

TEST(RangeQueryWithSparseSegmentTreeTest, SetValueOnIndexWithMinimumWorksWithZeroNumberOfValues) {
    RangeQueryForTest minimumRangeQuery(0, 0, minimumFunction);

    minimumRangeQuery.setValueOnIndex(0, 10);

    EXPECT_EQ(0, minimumRangeQuery.getValueOnInterval(0, 0));
}

TEST(RangeQueryWithSparseSegmentTreeTest, SetValueOnIndexWithMinimumWorksWithOneValue) {
    RangeQueryForTest minimumRangeQuery(1, 0, minimumFunction);

    minimumRangeQuery.setValueOnIndex(0, 10);

    EXPECT_EQ(10, minimumRangeQuery.getValueOnInterval(0, 0));
}

TEST(RangeQueryWithSparseSegmentTreeTest, SetValueOnIndexWithMinimumWorksOnExample1) {
    RangeQueryForTest minimumRangeQuery(9, 0, minimumFunction);

    minimumRangeQuery.setValueOnIndex(3, 10);
    minimumRangeQuery.setValueOnIndex(4, 11);
    minimumRangeQuery.setValueOnIndex(5, 12);

    EXPECT_EQ(0, minimumRangeQuery.getValueOnInterval(0, 0));
    EXPECT_EQ(0, minimumRangeQuery.getValueOnInterval(0, 1));
    EXPECT_EQ(0, minimumRangeQuery.getValueOnInterval(0, 2));
    EXPECT_EQ(0, minimumRangeQuery.getValueOnInterval(0, 3));
    EXPECT_EQ(0, minimumRangeQuery.getValueOnInterval(0, 4));
    EXPECT_EQ(0, minimumRangeQuery.getValueOnInterval(0, 5));
    EXPECT_EQ(0, minimumRangeQuery.getValueOnInterval(0, 6));
    EXPECT_EQ(0, minimumRangeQuery.getValueOnInterval(0, 7));
    EXPECT_EQ(0, minimumRangeQuery.getValueOnInterval(0, 8));
    EXPECT_EQ(0, minimumRangeQuery.getValueOnInterval(0, 9));
    EXPECT_EQ(0, minimumRangeQuery.getValueOnInterval(1, 6));
    EXPECT_EQ(0, minimumRangeQuery.getValueOnInterval(2, 5));
    EXPECT_EQ(10, minimumRangeQuery.getValueOnInterval(3, 4));
    EXPECT_EQ(11, minimumRangeQuery.getValueOnInterval(4, 4));
}

TEST(RangeQueryWithSparseSegmentTreeTest, SetValueOnIndexWithMaximumWorksOnExample1) {
    RangeQueryForTest maximumRangeQuery(9, 0, maximumFunction);

    maximumRangeQuery.setValueOnIndex(3, 10);
    maximumRangeQuery.setValueOnIndex(4, 11);
    maximumRangeQuery.setValueOnIndex(5, 12);

    EXPECT_EQ(0, maximumRangeQuery.getValueOnInterval(0, 0));
    EXPECT_EQ(0, maximumRangeQuery.getValueOnInterval(0, 1));
    EXPECT_EQ(0, maximumRangeQuery.getValueOnInterval(0, 2));
    EXPECT_EQ(10, maximumRangeQuery.getValueOnInterval(0, 3));
    EXPECT_EQ(11, maximumRangeQuery.getValueOnInterval(0, 4));
    EXPECT_EQ(12, maximumRangeQuery.getValueOnInterval(0, 5));
    EXPECT_EQ(12, maximumRangeQuery.getValueOnInterval(0, 6));
    EXPECT_EQ(12, maximumRangeQuery.getValueOnInterval(0, 7));
    EXPECT_EQ(12, maximumRangeQuery.getValueOnInterval(0, 8));
    EXPECT_EQ(0, maximumRangeQuery.getValueOnInterval(0, 9));
    EXPECT_EQ(12, maximumRangeQuery.getValueOnInterval(1, 6));
    EXPECT_EQ(12, maximumRangeQuery.getValueOnInterval(2, 5));
    EXPECT_EQ(11, maximumRangeQuery.getValueOnInterval(3, 4));
    EXPECT_EQ(11, maximumRangeQuery.getValueOnInterval(4, 4));
}

TEST(RangeQueryWithSparseSegmentTreeTest, SetValueOnIndexWithSumWorksOnExample1) {
    RangeQueryForTest sumRangeQuery(9, 0, plusFunction);

    sumRangeQuery.setValueOnIndex(3, 10);
    sumRangeQuery.setValueOnIndex(4, 11);
    sumRangeQuery.setValueOnIndex(5, 12);

    EXPECT_EQ(0, sumRangeQuery.getValueOnInterval(0, 0));
    EXPECT_EQ(0, sumRangeQuery.getValueOnInterval(0, 1));
    EXPECT_EQ(0, sumRangeQuery.getValueOnInterval(0, 2));
    EXPECT_EQ(10, sumRangeQuery.getValueOnInterval(0, 3));
    EXPECT_EQ(21, sumRangeQuery.getValueOnInterval(0, 4));
    EXPECT_EQ(33, sumRangeQuery.getValueOnInterval(0, 5));
    EXPECT_EQ(33, sumRangeQuery.getValueOnInterval(0, 6));
    EXPECT_EQ(33, sumRangeQuery.getValueOnInterval(0, 7));
    EXPECT_EQ(33, sumRangeQuery.getValueOnInterval(0, 8));
    EXPECT_EQ(0, sumRangeQuery.getValueOnInterval(0, 9));
    EXPECT_EQ(33, sumRangeQuery.getValueOnInterval(1, 6));
    EXPECT_EQ(33, sumRangeQuery.getValueOnInterval(2, 5));
    EXPECT_EQ(21, sumRangeQuery.getValueOnInterval(3, 4));
    EXPECT_EQ(11, sumRangeQuery.getValueOnInterval(4, 4));
}

}  // namespace algorithm

}  // namespace alba
