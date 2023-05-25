#include <Algorithm/Search/RangeQuery/SegmentTree/RangeQueryWithPersistentDynamicSegmentTree.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using ValuesForTest = vector<double>;
using RangeQueryForTest = RangeQueryWithPersistentDynamicSegmentTree<ValuesForTest>;
using ValueForTest = RangeQueryForTest::Value;
RangeQueryForTest::Function multipliesFunction = multiplies<>();
}  // namespace

TEST(RangeQueryWithPersistentDynamicSegmentTreeTest, GetValueOnIntervalWithGeometricSumWorksWithEmptySetOfValues) {
    ValuesForTest values;
    RangeQueryForTest geometricSumRangeQuery(values, multipliesFunction);

    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnInterval(0, 0));
}

TEST(RangeQueryWithPersistentDynamicSegmentTreeTest, GetValueOnIntervalWithGeometricSumWorksOnExample1) {
    ValuesForTest values{1, 3, 4, 8, 6, 1, 4, 2, 9};
    RangeQueryForTest geometricSumRangeQuery(values, multipliesFunction);

    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getValueOnInterval(0, 0));
    EXPECT_DOUBLE_EQ(3, geometricSumRangeQuery.getValueOnInterval(0, 1));
    EXPECT_DOUBLE_EQ(12, geometricSumRangeQuery.getValueOnInterval(0, 2));
    EXPECT_DOUBLE_EQ(96, geometricSumRangeQuery.getValueOnInterval(0, 3));
    EXPECT_DOUBLE_EQ(576, geometricSumRangeQuery.getValueOnInterval(0, 4));
    EXPECT_DOUBLE_EQ(576, geometricSumRangeQuery.getValueOnInterval(0, 5));
    EXPECT_DOUBLE_EQ(2304, geometricSumRangeQuery.getValueOnInterval(0, 6));
    EXPECT_DOUBLE_EQ(4608, geometricSumRangeQuery.getValueOnInterval(0, 7));
    EXPECT_DOUBLE_EQ(41472, geometricSumRangeQuery.getValueOnInterval(0, 8));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnInterval(0, 9));
    EXPECT_DOUBLE_EQ(2304, geometricSumRangeQuery.getValueOnInterval(1, 6));
    EXPECT_DOUBLE_EQ(192, geometricSumRangeQuery.getValueOnInterval(2, 5));
    EXPECT_DOUBLE_EQ(48, geometricSumRangeQuery.getValueOnInterval(3, 4));
    EXPECT_DOUBLE_EQ(6, geometricSumRangeQuery.getValueOnInterval(4, 4));
}

TEST(RangeQueryWithPersistentDynamicSegmentTreeTest, ChangeValueAtIndexWithGeometricSumWorksWithEmptySetOfValues) {
    ValuesForTest values;
    RangeQueryForTest geometricSumRangeQuery(values, multipliesFunction);

    geometricSumRangeQuery.changeValueAtIndex(3, 3);

    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnInterval(0, 0));
}

TEST(RangeQueryWithPersistentDynamicSegmentTreeTest, ChangeValueAtIndexWithGeometricSumWorksOnExample1) {
    ValuesForTest values{1, 3, 4, 8, 6, 1, 4, 2, 9};
    RangeQueryForTest geometricSumRangeQuery(values, multipliesFunction);

    geometricSumRangeQuery.changeValueAtIndex(3, 3);

    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getValueOnInterval(0, 0));
    EXPECT_DOUBLE_EQ(3, geometricSumRangeQuery.getValueOnInterval(0, 1));
    EXPECT_DOUBLE_EQ(12, geometricSumRangeQuery.getValueOnInterval(0, 2));
    EXPECT_DOUBLE_EQ(36, geometricSumRangeQuery.getValueOnInterval(0, 3));
    EXPECT_DOUBLE_EQ(216, geometricSumRangeQuery.getValueOnInterval(0, 4));
    EXPECT_DOUBLE_EQ(216, geometricSumRangeQuery.getValueOnInterval(0, 5));
    EXPECT_DOUBLE_EQ(864, geometricSumRangeQuery.getValueOnInterval(0, 6));
    EXPECT_DOUBLE_EQ(1728, geometricSumRangeQuery.getValueOnInterval(0, 7));
    EXPECT_DOUBLE_EQ(15552, geometricSumRangeQuery.getValueOnInterval(0, 8));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnInterval(0, 9));
    EXPECT_DOUBLE_EQ(864, geometricSumRangeQuery.getValueOnInterval(1, 6));
    EXPECT_DOUBLE_EQ(72, geometricSumRangeQuery.getValueOnInterval(2, 5));
    EXPECT_DOUBLE_EQ(18, geometricSumRangeQuery.getValueOnInterval(3, 4));
    EXPECT_DOUBLE_EQ(6, geometricSumRangeQuery.getValueOnInterval(4, 4));
}

TEST(
    RangeQueryWithPersistentDynamicSegmentTreeTest,
    GetValueOnIntervalOnPreviousTreeWithGeometricSumWorksAfterChangingValuesOnExample1) {
    ValuesForTest values{1, 3, 4, 8, 6, 1, 4, 2, 9};
    RangeQueryForTest geometricSumRangeQuery(values, multipliesFunction);

    geometricSumRangeQuery.changeValueAtIndex(3, 3);  // New values: 1, 3, 4, 3, 6, 1, 4, 2, 9
    geometricSumRangeQuery.changeValueAtIndex(4, 4);  // New values: 1, 3, 4, 3, 4, 1, 4, 2, 9
    geometricSumRangeQuery.changeValueAtIndex(5, 5);  // New values: 1, 3, 4, 3, 4, 5, 4, 2, 9

    // On zero previous step (current values), the values are: 1, 3, 4, 3, 4, 5, 4, 2, 9
    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0, 0, 0));
    EXPECT_DOUBLE_EQ(3, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0, 1, 0));
    EXPECT_DOUBLE_EQ(12, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0, 2, 0));
    EXPECT_DOUBLE_EQ(36, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0, 3, 0));
    EXPECT_DOUBLE_EQ(144, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0, 4, 0));
    EXPECT_DOUBLE_EQ(720, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0, 5, 0));
    EXPECT_DOUBLE_EQ(2880, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0, 6, 0));
    EXPECT_DOUBLE_EQ(5760, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0, 7, 0));
    EXPECT_DOUBLE_EQ(51840, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0, 8, 0));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0, 9, 0));
    EXPECT_DOUBLE_EQ(2880, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(1, 6, 0));
    EXPECT_DOUBLE_EQ(240, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(2, 5, 0));
    EXPECT_DOUBLE_EQ(12, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(3, 4, 0));
    EXPECT_DOUBLE_EQ(4, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(4, 4, 0));

    // On first previous step, the values are: 1, 3, 4, 3, 4, 1, 4, 2, 9
    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0, 0, 1));
    EXPECT_DOUBLE_EQ(3, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0, 1, 1));
    EXPECT_DOUBLE_EQ(12, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0, 2, 1));
    EXPECT_DOUBLE_EQ(36, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0, 3, 1));
    EXPECT_DOUBLE_EQ(144, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0, 4, 1));
    EXPECT_DOUBLE_EQ(144, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0, 5, 1));
    EXPECT_DOUBLE_EQ(576, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0, 6, 1));
    EXPECT_DOUBLE_EQ(1152, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0, 7, 1));
    EXPECT_DOUBLE_EQ(10368, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0, 8, 1));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0, 9, 1));
    EXPECT_DOUBLE_EQ(576, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(1, 6, 1));
    EXPECT_DOUBLE_EQ(48, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(2, 5, 1));
    EXPECT_DOUBLE_EQ(12, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(3, 4, 1));
    EXPECT_DOUBLE_EQ(4, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(4, 4, 1));

    // On second previous step, the values are: 1, 3, 4, 3, 6, 1, 4, 2, 9
    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0, 0, 2));
    EXPECT_DOUBLE_EQ(3, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0, 1, 2));
    EXPECT_DOUBLE_EQ(12, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0, 2, 2));
    EXPECT_DOUBLE_EQ(36, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0, 3, 2));
    EXPECT_DOUBLE_EQ(216, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0, 4, 2));
    EXPECT_DOUBLE_EQ(216, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0, 5, 2));
    EXPECT_DOUBLE_EQ(864, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0, 6, 2));
    EXPECT_DOUBLE_EQ(1728, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0, 7, 2));
    EXPECT_DOUBLE_EQ(15552, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0, 8, 2));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0, 9, 2));
    EXPECT_DOUBLE_EQ(864, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(1, 6, 2));
    EXPECT_DOUBLE_EQ(72, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(2, 5, 2));
    EXPECT_DOUBLE_EQ(18, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(3, 4, 2));
    EXPECT_DOUBLE_EQ(6, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(4, 4, 2));

    // On third previous step (original values), the values are: 1, 3, 4, 8, 6, 1, 4, 2, 9
    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0, 0, 3));
    EXPECT_DOUBLE_EQ(3, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0, 1, 3));
    EXPECT_DOUBLE_EQ(12, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0, 2, 3));
    EXPECT_DOUBLE_EQ(96, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0, 3, 3));
    EXPECT_DOUBLE_EQ(576, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0, 4, 3));
    EXPECT_DOUBLE_EQ(576, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0, 5, 3));
    EXPECT_DOUBLE_EQ(2304, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0, 6, 3));
    EXPECT_DOUBLE_EQ(4608, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0, 7, 3));
    EXPECT_DOUBLE_EQ(41472, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0, 8, 3));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0, 9, 3));
    EXPECT_DOUBLE_EQ(2304, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(1, 6, 3));
    EXPECT_DOUBLE_EQ(192, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(2, 5, 3));
    EXPECT_DOUBLE_EQ(48, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(3, 4, 3));
    EXPECT_DOUBLE_EQ(6, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(4, 4, 3));

    // On fourth previous step, there are no values because there are only 3 changes
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0, 0, 4));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0, 1, 4));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0, 2, 4));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0, 3, 4));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0, 4, 4));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0, 5, 4));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0, 6, 4));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0, 7, 4));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0, 8, 4));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0, 9, 4));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(1, 6, 4));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(2, 5, 4));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(3, 4, 4));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(4, 4, 4));
}

}  // namespace algorithm

}  // namespace alba
