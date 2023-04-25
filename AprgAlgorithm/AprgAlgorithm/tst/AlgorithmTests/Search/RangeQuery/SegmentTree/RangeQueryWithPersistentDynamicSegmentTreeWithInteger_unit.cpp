#include <Algorithm/Search/RangeQuery/SegmentTree/RangeQueryWithPersistentDynamicSegmentTree.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using ValuesForTest = vector<unsigned int>;
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

    EXPECT_EQ(0U, minimumRangeQuery.getValueOnInterval(0U, 0U));
}

TEST(RangeQueryWithPersistentDynamicSegmentTreeTest, GetValueOnIntervalWithMinimumWorksOnExample1) {
    ValuesForTest values{5U, 9U, 4U, 8U, 6U, 1U, 4U, 2U, 0U};
    RangeQueryForTest minimumRangeQuery(values, minimumFunction);

    EXPECT_EQ(5U, minimumRangeQuery.getValueOnInterval(0U, 0U));
    EXPECT_EQ(5U, minimumRangeQuery.getValueOnInterval(0U, 1U));
    EXPECT_EQ(4U, minimumRangeQuery.getValueOnInterval(0U, 2U));
    EXPECT_EQ(4U, minimumRangeQuery.getValueOnInterval(0U, 3U));
    EXPECT_EQ(4U, minimumRangeQuery.getValueOnInterval(0U, 4U));
    EXPECT_EQ(1U, minimumRangeQuery.getValueOnInterval(0U, 5U));
    EXPECT_EQ(1U, minimumRangeQuery.getValueOnInterval(0U, 6U));
    EXPECT_EQ(1U, minimumRangeQuery.getValueOnInterval(0U, 7U));
    EXPECT_EQ(0U, minimumRangeQuery.getValueOnInterval(0U, 8U));
    EXPECT_EQ(0U, minimumRangeQuery.getValueOnInterval(0U, 9U));
    EXPECT_EQ(1U, minimumRangeQuery.getValueOnInterval(3U, 6U));
    EXPECT_EQ(4U, minimumRangeQuery.getValueOnInterval(2U, 4U));
}

TEST(RangeQueryWithPersistentDynamicSegmentTreeTest, GetValueOnIntervalWithMaximumWorksOnExample1) {
    ValuesForTest values{5U, 9U, 4U, 8U, 6U, 1U, 4U, 2U, 10U};
    RangeQueryForTest maximumRangeQuery(values, maximumFunction);

    EXPECT_EQ(5U, maximumRangeQuery.getValueOnInterval(0U, 0U));
    EXPECT_EQ(9U, maximumRangeQuery.getValueOnInterval(0U, 1U));
    EXPECT_EQ(9U, maximumRangeQuery.getValueOnInterval(0U, 2U));
    EXPECT_EQ(9U, maximumRangeQuery.getValueOnInterval(0U, 3U));
    EXPECT_EQ(9U, maximumRangeQuery.getValueOnInterval(0U, 4U));
    EXPECT_EQ(9U, maximumRangeQuery.getValueOnInterval(0U, 5U));
    EXPECT_EQ(9U, maximumRangeQuery.getValueOnInterval(0U, 6U));
    EXPECT_EQ(9U, maximumRangeQuery.getValueOnInterval(0U, 7U));
    EXPECT_EQ(10U, maximumRangeQuery.getValueOnInterval(0U, 8U));
    EXPECT_EQ(0U, maximumRangeQuery.getValueOnInterval(0U, 9U));
    EXPECT_EQ(8U, maximumRangeQuery.getValueOnInterval(3U, 6U));
    EXPECT_EQ(8U, maximumRangeQuery.getValueOnInterval(2U, 4U));
}

TEST(RangeQueryWithPersistentDynamicSegmentTreeTest, GetValueOnIntervalWithSumWorksOnExample1) {
    ValuesForTest values{1U, 3U, 4U, 8U, 6U, 1U, 4U, 2U, 9U};
    RangeQueryForTest sumRangeQuery(values, plusFunction);

    EXPECT_EQ(1U, sumRangeQuery.getValueOnInterval(0U, 0U));
    EXPECT_EQ(4U, sumRangeQuery.getValueOnInterval(0U, 1U));
    EXPECT_EQ(8U, sumRangeQuery.getValueOnInterval(0U, 2U));
    EXPECT_EQ(16U, sumRangeQuery.getValueOnInterval(0U, 3U));
    EXPECT_EQ(22U, sumRangeQuery.getValueOnInterval(0U, 4U));
    EXPECT_EQ(23U, sumRangeQuery.getValueOnInterval(0U, 5U));
    EXPECT_EQ(27U, sumRangeQuery.getValueOnInterval(0U, 6U));
    EXPECT_EQ(29U, sumRangeQuery.getValueOnInterval(0U, 7U));
    EXPECT_EQ(38U, sumRangeQuery.getValueOnInterval(0U, 8U));
    EXPECT_EQ(0U, sumRangeQuery.getValueOnInterval(0U, 9U));
    EXPECT_EQ(26U, sumRangeQuery.getValueOnInterval(1U, 6U));
    EXPECT_EQ(19U, sumRangeQuery.getValueOnInterval(2U, 5U));
    EXPECT_EQ(14U, sumRangeQuery.getValueOnInterval(3U, 4U));
    EXPECT_EQ(6U, sumRangeQuery.getValueOnInterval(4U, 4U));
}

TEST(RangeQueryWithPersistentDynamicSegmentTreeTest, ChangeValueAtIndexWithSumWorksWithEmptySetOfValues) {
    ValuesForTest values;
    RangeQueryForTest sumRangeQuery(values, plusFunction);

    sumRangeQuery.changeValueAtIndex(0U, 0U);

    EXPECT_EQ(0U, sumRangeQuery.getValueOnInterval(0U, 0U));
}

TEST(RangeQueryWithPersistentDynamicSegmentTreeTest, ChangeValueAtIndexWithSumWorksWithOneValue) {
    ValuesForTest values{5};
    RangeQueryForTest sumRangeQuery(values, plusFunction);

    sumRangeQuery.changeValueAtIndex(0U, 3U);

    EXPECT_EQ(3U, sumRangeQuery.getValueOnInterval(0U, 0U));
}

TEST(RangeQueryWithPersistentDynamicSegmentTreeTest, ChangeValueAtIndexWithSumWorksOnExample1) {
    ValuesForTest values{1U, 3U, 4U, 8U, 6U, 1U, 4U, 2U, 9U};
    RangeQueryForTest sumRangeQuery(values, plusFunction);

    sumRangeQuery.changeValueAtIndex(3U, 3U);

    EXPECT_EQ(1U, sumRangeQuery.getValueOnInterval(0U, 0U));
    EXPECT_EQ(4U, sumRangeQuery.getValueOnInterval(0U, 1U));
    EXPECT_EQ(8U, sumRangeQuery.getValueOnInterval(0U, 2U));
    EXPECT_EQ(11U, sumRangeQuery.getValueOnInterval(0U, 3U));
    EXPECT_EQ(17U, sumRangeQuery.getValueOnInterval(0U, 4U));
    EXPECT_EQ(18U, sumRangeQuery.getValueOnInterval(0U, 5U));
    EXPECT_EQ(22U, sumRangeQuery.getValueOnInterval(0U, 6U));
    EXPECT_EQ(24U, sumRangeQuery.getValueOnInterval(0U, 7U));
    EXPECT_EQ(33U, sumRangeQuery.getValueOnInterval(0U, 8U));
    EXPECT_EQ(0U, sumRangeQuery.getValueOnInterval(0U, 9U));
    EXPECT_EQ(21U, sumRangeQuery.getValueOnInterval(1U, 6U));
    EXPECT_EQ(14U, sumRangeQuery.getValueOnInterval(2U, 5U));
    EXPECT_EQ(9U, sumRangeQuery.getValueOnInterval(3U, 4U));
    EXPECT_EQ(6U, sumRangeQuery.getValueOnInterval(4U, 4U));
}

TEST(
    RangeQueryWithPersistentDynamicSegmentTreeTest,
    GetValueOnIntervalOnPreviousTreeWithSumWorksAfterChangingValuesOnExample1) {
    ValuesForTest values{1, 3, 4, 8, 6, 1, 4, 2, 9};
    RangeQueryForTest sumRangeQuery(values, plusFunction);

    sumRangeQuery.changeValueAtIndex(3U, 3U);  // New values: 1, 3, 4, 3, 6, 1, 4, 2, 9
    sumRangeQuery.changeValueAtIndex(4U, 4U);  // New values: 1, 3, 4, 3, 4, 1, 4, 2, 9
    sumRangeQuery.changeValueAtIndex(5U, 5U);  // New values: 1, 3, 4, 3, 4, 5, 4, 2, 9

    // On zero previous step (current values), the values are: 1, 3, 4, 3, 4, 5, 4, 2, 9
    EXPECT_EQ(1U, sumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 0U, 0U));
    EXPECT_EQ(4U, sumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 1U, 0U));
    EXPECT_EQ(8U, sumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 2U, 0U));
    EXPECT_EQ(11U, sumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 3U, 0U));
    EXPECT_EQ(15U, sumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 4U, 0U));
    EXPECT_EQ(20U, sumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 5U, 0U));
    EXPECT_EQ(24U, sumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 6U, 0U));
    EXPECT_EQ(26U, sumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 7U, 0U));
    EXPECT_EQ(35U, sumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 8U, 0U));
    EXPECT_EQ(0U, sumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 9U, 0U));
    EXPECT_EQ(23U, sumRangeQuery.getValueOnIntervalOnPreviousTree(1U, 6U, 0U));
    EXPECT_EQ(16U, sumRangeQuery.getValueOnIntervalOnPreviousTree(2U, 5U, 0U));
    EXPECT_EQ(7U, sumRangeQuery.getValueOnIntervalOnPreviousTree(3U, 4U, 0U));
    EXPECT_EQ(4U, sumRangeQuery.getValueOnIntervalOnPreviousTree(4U, 4U, 0U));

    // On first previous step, the values are: 1, 3, 4, 3, 4, 1, 4, 2, 9
    EXPECT_EQ(1U, sumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 0U, 1U));
    EXPECT_EQ(4U, sumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 1U, 1U));
    EXPECT_EQ(8U, sumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 2U, 1U));
    EXPECT_EQ(11U, sumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 3U, 1U));
    EXPECT_EQ(15U, sumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 4U, 1U));
    EXPECT_EQ(16U, sumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 5U, 1U));
    EXPECT_EQ(20U, sumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 6U, 1U));
    EXPECT_EQ(22U, sumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 7U, 1U));
    EXPECT_EQ(31U, sumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 8U, 1U));
    EXPECT_EQ(0U, sumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 9U, 1U));
    EXPECT_EQ(19U, sumRangeQuery.getValueOnIntervalOnPreviousTree(1U, 6U, 1U));
    EXPECT_EQ(12U, sumRangeQuery.getValueOnIntervalOnPreviousTree(2U, 5U, 1U));
    EXPECT_EQ(7U, sumRangeQuery.getValueOnIntervalOnPreviousTree(3U, 4U, 1U));
    EXPECT_EQ(4U, sumRangeQuery.getValueOnIntervalOnPreviousTree(4U, 4U, 1U));

    // On second previous step, the values are: 1, 3, 4, 3, 6, 1, 4, 2, 9
    EXPECT_EQ(1U, sumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 0U, 2U));
    EXPECT_EQ(4U, sumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 1U, 2U));
    EXPECT_EQ(8U, sumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 2U, 2U));
    EXPECT_EQ(11U, sumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 3U, 2U));
    EXPECT_EQ(17U, sumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 4U, 2U));
    EXPECT_EQ(18U, sumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 5U, 2U));
    EXPECT_EQ(22U, sumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 6U, 2U));
    EXPECT_EQ(24U, sumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 7U, 2U));
    EXPECT_EQ(33U, sumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 8U, 2U));
    EXPECT_EQ(0U, sumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 9U, 2U));
    EXPECT_EQ(21U, sumRangeQuery.getValueOnIntervalOnPreviousTree(1U, 6U, 2U));
    EXPECT_EQ(14U, sumRangeQuery.getValueOnIntervalOnPreviousTree(2U, 5U, 2U));
    EXPECT_EQ(9U, sumRangeQuery.getValueOnIntervalOnPreviousTree(3U, 4U, 2U));
    EXPECT_EQ(6U, sumRangeQuery.getValueOnIntervalOnPreviousTree(4U, 4U, 2U));

    // On third previous step (original values), the values are: 1, 3, 4, 8, 6, 1, 4, 2, 9
    EXPECT_EQ(1U, sumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 0U, 3U));
    EXPECT_EQ(4U, sumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 1U, 3U));
    EXPECT_EQ(8U, sumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 2U, 3U));
    EXPECT_EQ(16U, sumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 3U, 3U));
    EXPECT_EQ(22U, sumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 4U, 3U));
    EXPECT_EQ(23U, sumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 5U, 3U));
    EXPECT_EQ(27U, sumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 6U, 3U));
    EXPECT_EQ(29U, sumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 7U, 3U));
    EXPECT_EQ(38U, sumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 8U, 3U));
    EXPECT_EQ(0U, sumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 9U, 3U));
    EXPECT_EQ(26U, sumRangeQuery.getValueOnIntervalOnPreviousTree(1U, 6U, 3U));
    EXPECT_EQ(19U, sumRangeQuery.getValueOnIntervalOnPreviousTree(2U, 5U, 3U));
    EXPECT_EQ(14U, sumRangeQuery.getValueOnIntervalOnPreviousTree(3U, 4U, 3U));
    EXPECT_EQ(6U, sumRangeQuery.getValueOnIntervalOnPreviousTree(4U, 4U, 3U));

    // On fourth previous step, there are no values because there are only 3 changes
    EXPECT_EQ(0U, sumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 0U, 4U));
    EXPECT_EQ(0U, sumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 1U, 4U));
    EXPECT_EQ(0U, sumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 2U, 4U));
    EXPECT_EQ(0U, sumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 3U, 4U));
    EXPECT_EQ(0U, sumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 4U, 4U));
    EXPECT_EQ(0U, sumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 5U, 4U));
    EXPECT_EQ(0U, sumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 6U, 4U));
    EXPECT_EQ(0U, sumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 7U, 4U));
    EXPECT_EQ(0U, sumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 8U, 4U));
    EXPECT_EQ(0U, sumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 9U, 4U));
    EXPECT_EQ(0U, sumRangeQuery.getValueOnIntervalOnPreviousTree(1U, 6U, 4U));
    EXPECT_EQ(0U, sumRangeQuery.getValueOnIntervalOnPreviousTree(2U, 5U, 4U));
    EXPECT_EQ(0U, sumRangeQuery.getValueOnIntervalOnPreviousTree(3U, 4U, 4U));
    EXPECT_EQ(0U, sumRangeQuery.getValueOnIntervalOnPreviousTree(4U, 4U, 4U));
}

}  // namespace algorithm

}  // namespace alba
