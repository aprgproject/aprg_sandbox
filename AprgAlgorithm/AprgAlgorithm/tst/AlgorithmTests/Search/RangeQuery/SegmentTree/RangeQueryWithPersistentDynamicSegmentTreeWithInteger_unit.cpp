#include <Algorithm/Search/RangeQuery/SegmentTree/RangeQueryWithPersistentDynamicSegmentTree.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using ValuesForTest = vector<int>;
using RangeQueryForTest = RangeQueryWithPersistentDynamicSegmentTree<ValuesForTest>;
using ValueForTest = RangeQueryForTest::Value;

RangeQueryForTest::Function minimumFunction = [](ValueForTest const& value1, ValueForTest const& value2) {
    return min(value1, value2);
};

RangeQueryForTest::Function maximumFunction = [](ValueForTest const& value1, ValueForTest const& value2) {
    return max(value1, value2);
};

RangeQueryForTest::Function plusFunction = plus<>();
}  // namespace

TEST(RangeQueryWithPersistentDynamicSegmentTreeTest, GetValueOnIntervalWithMinimumWorksWithEmptySetOfValues) {
    ValuesForTest values;
    RangeQueryForTest minimumRangeQuery(values, minimumFunction);

    EXPECT_EQ(0, minimumRangeQuery.getValueOnInterval(0, 0));
}

TEST(RangeQueryWithPersistentDynamicSegmentTreeTest, GetValueOnIntervalWithMinimumWorksOnExample1) {
    ValuesForTest values{5, 9, 4, 8, 6, 1, 4, 2, 0};
    RangeQueryForTest minimumRangeQuery(values, minimumFunction);

    EXPECT_EQ(5, minimumRangeQuery.getValueOnInterval(0, 0));
    EXPECT_EQ(5, minimumRangeQuery.getValueOnInterval(0, 1));
    EXPECT_EQ(4, minimumRangeQuery.getValueOnInterval(0, 2));
    EXPECT_EQ(4, minimumRangeQuery.getValueOnInterval(0, 3));
    EXPECT_EQ(4, minimumRangeQuery.getValueOnInterval(0, 4));
    EXPECT_EQ(1, minimumRangeQuery.getValueOnInterval(0, 5));
    EXPECT_EQ(1, minimumRangeQuery.getValueOnInterval(0, 6));
    EXPECT_EQ(1, minimumRangeQuery.getValueOnInterval(0, 7));
    EXPECT_EQ(0, minimumRangeQuery.getValueOnInterval(0, 8));
    EXPECT_EQ(0, minimumRangeQuery.getValueOnInterval(0, 9));
    EXPECT_EQ(1, minimumRangeQuery.getValueOnInterval(3, 6));
    EXPECT_EQ(4, minimumRangeQuery.getValueOnInterval(2, 4));
}

TEST(RangeQueryWithPersistentDynamicSegmentTreeTest, GetValueOnIntervalWithMaximumWorksOnExample1) {
    ValuesForTest values{5, 9, 4, 8, 6, 1, 4, 2, 10};
    RangeQueryForTest maximumRangeQuery(values, maximumFunction);

    EXPECT_EQ(5, maximumRangeQuery.getValueOnInterval(0, 0));
    EXPECT_EQ(9, maximumRangeQuery.getValueOnInterval(0, 1));
    EXPECT_EQ(9, maximumRangeQuery.getValueOnInterval(0, 2));
    EXPECT_EQ(9, maximumRangeQuery.getValueOnInterval(0, 3));
    EXPECT_EQ(9, maximumRangeQuery.getValueOnInterval(0, 4));
    EXPECT_EQ(9, maximumRangeQuery.getValueOnInterval(0, 5));
    EXPECT_EQ(9, maximumRangeQuery.getValueOnInterval(0, 6));
    EXPECT_EQ(9, maximumRangeQuery.getValueOnInterval(0, 7));
    EXPECT_EQ(10, maximumRangeQuery.getValueOnInterval(0, 8));
    EXPECT_EQ(0, maximumRangeQuery.getValueOnInterval(0, 9));
    EXPECT_EQ(8, maximumRangeQuery.getValueOnInterval(3, 6));
    EXPECT_EQ(8, maximumRangeQuery.getValueOnInterval(2, 4));
}

TEST(RangeQueryWithPersistentDynamicSegmentTreeTest, GetValueOnIntervalWithSumWorksOnExample1) {
    ValuesForTest values{1, 3, 4, 8, 6, 1, 4, 2, 9};
    RangeQueryForTest sumRangeQuery(values, plusFunction);

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

TEST(RangeQueryWithPersistentDynamicSegmentTreeTest, ChangeValueAtIndexWithSumWorksWithEmptySetOfValues) {
    ValuesForTest values;
    RangeQueryForTest sumRangeQuery(values, plusFunction);

    sumRangeQuery.changeValueAtIndex(0, 0);

    EXPECT_EQ(0, sumRangeQuery.getValueOnInterval(0, 0));
}

TEST(RangeQueryWithPersistentDynamicSegmentTreeTest, ChangeValueAtIndexWithSumWorksWithOneValue) {
    ValuesForTest values{5};
    RangeQueryForTest sumRangeQuery(values, plusFunction);

    sumRangeQuery.changeValueAtIndex(0, 3);

    EXPECT_EQ(3, sumRangeQuery.getValueOnInterval(0, 0));
}

TEST(RangeQueryWithPersistentDynamicSegmentTreeTest, ChangeValueAtIndexWithSumWorksOnExample1) {
    ValuesForTest values{1, 3, 4, 8, 6, 1, 4, 2, 9};
    RangeQueryForTest sumRangeQuery(values, plusFunction);

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

TEST(
    RangeQueryWithPersistentDynamicSegmentTreeTest,
    GetValueOnIntervalOnPreviousTreeWithSumWorksAfterChangingValuesOnExample1) {
    ValuesForTest values{1, 3, 4, 8, 6, 1, 4, 2, 9};
    RangeQueryForTest sumRangeQuery(values, plusFunction);

    sumRangeQuery.changeValueAtIndex(3, 3);  // New values: 1, 3, 4, 3, 6, 1, 4, 2, 9
    sumRangeQuery.changeValueAtIndex(4, 4);  // New values: 1, 3, 4, 3, 4, 1, 4, 2, 9
    sumRangeQuery.changeValueAtIndex(5, 5);  // New values: 1, 3, 4, 3, 4, 5, 4, 2, 9

    // On zero previous step (current values), the values are: 1, 3, 4, 3, 4, 5, 4, 2, 9
    EXPECT_EQ(1, sumRangeQuery.getValueOnIntervalOnPreviousTree(0, 0, 0));
    EXPECT_EQ(4, sumRangeQuery.getValueOnIntervalOnPreviousTree(0, 1, 0));
    EXPECT_EQ(8, sumRangeQuery.getValueOnIntervalOnPreviousTree(0, 2, 0));
    EXPECT_EQ(11, sumRangeQuery.getValueOnIntervalOnPreviousTree(0, 3, 0));
    EXPECT_EQ(15, sumRangeQuery.getValueOnIntervalOnPreviousTree(0, 4, 0));
    EXPECT_EQ(20, sumRangeQuery.getValueOnIntervalOnPreviousTree(0, 5, 0));
    EXPECT_EQ(24, sumRangeQuery.getValueOnIntervalOnPreviousTree(0, 6, 0));
    EXPECT_EQ(26, sumRangeQuery.getValueOnIntervalOnPreviousTree(0, 7, 0));
    EXPECT_EQ(35, sumRangeQuery.getValueOnIntervalOnPreviousTree(0, 8, 0));
    EXPECT_EQ(0, sumRangeQuery.getValueOnIntervalOnPreviousTree(0, 9, 0));
    EXPECT_EQ(23, sumRangeQuery.getValueOnIntervalOnPreviousTree(1, 6, 0));
    EXPECT_EQ(16, sumRangeQuery.getValueOnIntervalOnPreviousTree(2, 5, 0));
    EXPECT_EQ(7, sumRangeQuery.getValueOnIntervalOnPreviousTree(3, 4, 0));
    EXPECT_EQ(4, sumRangeQuery.getValueOnIntervalOnPreviousTree(4, 4, 0));

    // On first previous step, the values are: 1, 3, 4, 3, 4, 1, 4, 2, 9
    EXPECT_EQ(1, sumRangeQuery.getValueOnIntervalOnPreviousTree(0, 0, 1));
    EXPECT_EQ(4, sumRangeQuery.getValueOnIntervalOnPreviousTree(0, 1, 1));
    EXPECT_EQ(8, sumRangeQuery.getValueOnIntervalOnPreviousTree(0, 2, 1));
    EXPECT_EQ(11, sumRangeQuery.getValueOnIntervalOnPreviousTree(0, 3, 1));
    EXPECT_EQ(15, sumRangeQuery.getValueOnIntervalOnPreviousTree(0, 4, 1));
    EXPECT_EQ(16, sumRangeQuery.getValueOnIntervalOnPreviousTree(0, 5, 1));
    EXPECT_EQ(20, sumRangeQuery.getValueOnIntervalOnPreviousTree(0, 6, 1));
    EXPECT_EQ(22, sumRangeQuery.getValueOnIntervalOnPreviousTree(0, 7, 1));
    EXPECT_EQ(31, sumRangeQuery.getValueOnIntervalOnPreviousTree(0, 8, 1));
    EXPECT_EQ(0, sumRangeQuery.getValueOnIntervalOnPreviousTree(0, 9, 1));
    EXPECT_EQ(19, sumRangeQuery.getValueOnIntervalOnPreviousTree(1, 6, 1));
    EXPECT_EQ(12, sumRangeQuery.getValueOnIntervalOnPreviousTree(2, 5, 1));
    EXPECT_EQ(7, sumRangeQuery.getValueOnIntervalOnPreviousTree(3, 4, 1));
    EXPECT_EQ(4, sumRangeQuery.getValueOnIntervalOnPreviousTree(4, 4, 1));

    // On second previous step, the values are: 1, 3, 4, 3, 6, 1, 4, 2, 9
    EXPECT_EQ(1, sumRangeQuery.getValueOnIntervalOnPreviousTree(0, 0, 2));
    EXPECT_EQ(4, sumRangeQuery.getValueOnIntervalOnPreviousTree(0, 1, 2));
    EXPECT_EQ(8, sumRangeQuery.getValueOnIntervalOnPreviousTree(0, 2, 2));
    EXPECT_EQ(11, sumRangeQuery.getValueOnIntervalOnPreviousTree(0, 3, 2));
    EXPECT_EQ(17, sumRangeQuery.getValueOnIntervalOnPreviousTree(0, 4, 2));
    EXPECT_EQ(18, sumRangeQuery.getValueOnIntervalOnPreviousTree(0, 5, 2));
    EXPECT_EQ(22, sumRangeQuery.getValueOnIntervalOnPreviousTree(0, 6, 2));
    EXPECT_EQ(24, sumRangeQuery.getValueOnIntervalOnPreviousTree(0, 7, 2));
    EXPECT_EQ(33, sumRangeQuery.getValueOnIntervalOnPreviousTree(0, 8, 2));
    EXPECT_EQ(0, sumRangeQuery.getValueOnIntervalOnPreviousTree(0, 9, 2));
    EXPECT_EQ(21, sumRangeQuery.getValueOnIntervalOnPreviousTree(1, 6, 2));
    EXPECT_EQ(14, sumRangeQuery.getValueOnIntervalOnPreviousTree(2, 5, 2));
    EXPECT_EQ(9, sumRangeQuery.getValueOnIntervalOnPreviousTree(3, 4, 2));
    EXPECT_EQ(6, sumRangeQuery.getValueOnIntervalOnPreviousTree(4, 4, 2));

    // On third previous step (original values), the values are: 1, 3, 4, 8, 6, 1, 4, 2, 9
    EXPECT_EQ(1, sumRangeQuery.getValueOnIntervalOnPreviousTree(0, 0, 3));
    EXPECT_EQ(4, sumRangeQuery.getValueOnIntervalOnPreviousTree(0, 1, 3));
    EXPECT_EQ(8, sumRangeQuery.getValueOnIntervalOnPreviousTree(0, 2, 3));
    EXPECT_EQ(16, sumRangeQuery.getValueOnIntervalOnPreviousTree(0, 3, 3));
    EXPECT_EQ(22, sumRangeQuery.getValueOnIntervalOnPreviousTree(0, 4, 3));
    EXPECT_EQ(23, sumRangeQuery.getValueOnIntervalOnPreviousTree(0, 5, 3));
    EXPECT_EQ(27, sumRangeQuery.getValueOnIntervalOnPreviousTree(0, 6, 3));
    EXPECT_EQ(29, sumRangeQuery.getValueOnIntervalOnPreviousTree(0, 7, 3));
    EXPECT_EQ(38, sumRangeQuery.getValueOnIntervalOnPreviousTree(0, 8, 3));
    EXPECT_EQ(0, sumRangeQuery.getValueOnIntervalOnPreviousTree(0, 9, 3));
    EXPECT_EQ(26, sumRangeQuery.getValueOnIntervalOnPreviousTree(1, 6, 3));
    EXPECT_EQ(19, sumRangeQuery.getValueOnIntervalOnPreviousTree(2, 5, 3));
    EXPECT_EQ(14, sumRangeQuery.getValueOnIntervalOnPreviousTree(3, 4, 3));
    EXPECT_EQ(6, sumRangeQuery.getValueOnIntervalOnPreviousTree(4, 4, 3));

    // On fourth previous step, there are no values because there are only 3 changes
    EXPECT_EQ(0, sumRangeQuery.getValueOnIntervalOnPreviousTree(0, 0, 4));
    EXPECT_EQ(0, sumRangeQuery.getValueOnIntervalOnPreviousTree(0, 1, 4));
    EXPECT_EQ(0, sumRangeQuery.getValueOnIntervalOnPreviousTree(0, 2, 4));
    EXPECT_EQ(0, sumRangeQuery.getValueOnIntervalOnPreviousTree(0, 3, 4));
    EXPECT_EQ(0, sumRangeQuery.getValueOnIntervalOnPreviousTree(0, 4, 4));
    EXPECT_EQ(0, sumRangeQuery.getValueOnIntervalOnPreviousTree(0, 5, 4));
    EXPECT_EQ(0, sumRangeQuery.getValueOnIntervalOnPreviousTree(0, 6, 4));
    EXPECT_EQ(0, sumRangeQuery.getValueOnIntervalOnPreviousTree(0, 7, 4));
    EXPECT_EQ(0, sumRangeQuery.getValueOnIntervalOnPreviousTree(0, 8, 4));
    EXPECT_EQ(0, sumRangeQuery.getValueOnIntervalOnPreviousTree(0, 9, 4));
    EXPECT_EQ(0, sumRangeQuery.getValueOnIntervalOnPreviousTree(1, 6, 4));
    EXPECT_EQ(0, sumRangeQuery.getValueOnIntervalOnPreviousTree(2, 5, 4));
    EXPECT_EQ(0, sumRangeQuery.getValueOnIntervalOnPreviousTree(3, 4, 4));
    EXPECT_EQ(0, sumRangeQuery.getValueOnIntervalOnPreviousTree(4, 4, 4));
}

}  // namespace algorithm

}  // namespace alba
