#include <Algorithm/Search/RangeQuery/SegmentTree/RangeQueryWithPersistentDynamicSegmentTree.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using ValuesForTest = vector<double>;
using RangeQueryForTest = RangeQueryWithPersistentDynamicSegmentTree<ValuesForTest>;
using ValueForTest = RangeQueryForTest::Value;
RangeQueryForTest::Function multipliesFunction = multiplies<>();
}

TEST(RangeQueryWithPersistentDynamicSegmentTreeTest, GetValueOnIntervalWithGeometricSumWorksWithEmptySetOfValues)
{
    ValuesForTest values;
    RangeQueryForTest geometricSumRangeQuery(values, multipliesFunction);

    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnInterval(0U, 0U));
}

TEST(RangeQueryWithPersistentDynamicSegmentTreeTest, GetValueOnIntervalWithGeometricSumWorksOnExample1)
{
    ValuesForTest values{1, 3, 4, 8, 6, 1, 4, 2, 9};
    RangeQueryForTest geometricSumRangeQuery(values, multipliesFunction);

    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getValueOnInterval(0U, 0U));
    EXPECT_DOUBLE_EQ(3, geometricSumRangeQuery.getValueOnInterval(0U, 1U));
    EXPECT_DOUBLE_EQ(12, geometricSumRangeQuery.getValueOnInterval(0U, 2U));
    EXPECT_DOUBLE_EQ(96, geometricSumRangeQuery.getValueOnInterval(0U, 3U));
    EXPECT_DOUBLE_EQ(576, geometricSumRangeQuery.getValueOnInterval(0U, 4U));
    EXPECT_DOUBLE_EQ(576, geometricSumRangeQuery.getValueOnInterval(0U, 5U));
    EXPECT_DOUBLE_EQ(2304, geometricSumRangeQuery.getValueOnInterval(0U, 6U));
    EXPECT_DOUBLE_EQ(4608, geometricSumRangeQuery.getValueOnInterval(0U, 7U));
    EXPECT_DOUBLE_EQ(41472, geometricSumRangeQuery.getValueOnInterval(0U, 8U));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnInterval(0U, 9U));
    EXPECT_DOUBLE_EQ(2304, geometricSumRangeQuery.getValueOnInterval(1U, 6U));
    EXPECT_DOUBLE_EQ(192, geometricSumRangeQuery.getValueOnInterval(2U, 5U));
    EXPECT_DOUBLE_EQ(48, geometricSumRangeQuery.getValueOnInterval(3U, 4U));
    EXPECT_DOUBLE_EQ(6, geometricSumRangeQuery.getValueOnInterval(4U, 4U));
}

TEST(RangeQueryWithPersistentDynamicSegmentTreeTest, ChangeValueAtIndexWithGeometricSumWorksWithEmptySetOfValues)
{
    ValuesForTest values;
    RangeQueryForTest geometricSumRangeQuery(values, multipliesFunction);

    geometricSumRangeQuery.changeValueAtIndex(3U, 3);

    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnInterval(0U, 0U));
}

TEST(RangeQueryWithPersistentDynamicSegmentTreeTest, ChangeValueAtIndexWithGeometricSumWorksOnExample1)
{
    ValuesForTest values{1, 3, 4, 8, 6, 1, 4, 2, 9};
    RangeQueryForTest geometricSumRangeQuery(values, multipliesFunction);

    geometricSumRangeQuery.changeValueAtIndex(3U, 3);

    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getValueOnInterval(0U, 0U));
    EXPECT_DOUBLE_EQ(3, geometricSumRangeQuery.getValueOnInterval(0U, 1U));
    EXPECT_DOUBLE_EQ(12, geometricSumRangeQuery.getValueOnInterval(0U, 2U));
    EXPECT_DOUBLE_EQ(36, geometricSumRangeQuery.getValueOnInterval(0U, 3U));
    EXPECT_DOUBLE_EQ(216, geometricSumRangeQuery.getValueOnInterval(0U, 4U));
    EXPECT_DOUBLE_EQ(216, geometricSumRangeQuery.getValueOnInterval(0U, 5U));
    EXPECT_DOUBLE_EQ(864, geometricSumRangeQuery.getValueOnInterval(0U, 6U));
    EXPECT_DOUBLE_EQ(1728, geometricSumRangeQuery.getValueOnInterval(0U, 7U));
    EXPECT_DOUBLE_EQ(15552, geometricSumRangeQuery.getValueOnInterval(0U, 8U));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnInterval(0U, 9U));
    EXPECT_DOUBLE_EQ(864, geometricSumRangeQuery.getValueOnInterval(1U, 6U));
    EXPECT_DOUBLE_EQ(72, geometricSumRangeQuery.getValueOnInterval(2U, 5U));
    EXPECT_DOUBLE_EQ(18, geometricSumRangeQuery.getValueOnInterval(3U, 4U));
    EXPECT_DOUBLE_EQ(6, geometricSumRangeQuery.getValueOnInterval(4U, 4U));
}

TEST(RangeQueryWithPersistentDynamicSegmentTreeTest, GetValueOnIntervalOnPreviousTreeWithGeometricSumWorksAfterChangingValuesOnExample1)
{
    ValuesForTest values{1, 3, 4, 8, 6, 1, 4, 2, 9};
    RangeQueryForTest geometricSumRangeQuery(values, multipliesFunction);

    geometricSumRangeQuery.changeValueAtIndex(3U, 3); // New values: 1, 3, 4, 3, 6, 1, 4, 2, 9
    geometricSumRangeQuery.changeValueAtIndex(4U, 4); // New values: 1, 3, 4, 3, 4, 1, 4, 2, 9
    geometricSumRangeQuery.changeValueAtIndex(5U, 5); // New values: 1, 3, 4, 3, 4, 5, 4, 2, 9

    // On zero previous step (current values), the values are: 1, 3, 4, 3, 4, 5, 4, 2, 9
    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 0U, 0U));
    EXPECT_DOUBLE_EQ(3, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 1U, 0U));
    EXPECT_DOUBLE_EQ(12, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 2U, 0U));
    EXPECT_DOUBLE_EQ(36, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 3U, 0U));
    EXPECT_DOUBLE_EQ(144, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 4U, 0U));
    EXPECT_DOUBLE_EQ(720, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 5U, 0U));
    EXPECT_DOUBLE_EQ(2880, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 6U, 0U));
    EXPECT_DOUBLE_EQ(5760, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 7U, 0U));
    EXPECT_DOUBLE_EQ(51840, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 8U, 0U));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 9U, 0U));
    EXPECT_DOUBLE_EQ(2880, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(1U, 6U, 0U));
    EXPECT_DOUBLE_EQ(240, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(2U, 5U, 0U));
    EXPECT_DOUBLE_EQ(12, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(3U, 4U, 0U));
    EXPECT_DOUBLE_EQ(4, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(4U, 4U, 0U));

    // On first previous step, the values are: 1, 3, 4, 3, 4, 1, 4, 2, 9
    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 0U, 1U));
    EXPECT_DOUBLE_EQ(3, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 1U, 1U));
    EXPECT_DOUBLE_EQ(12, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 2U, 1U));
    EXPECT_DOUBLE_EQ(36, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 3U, 1U));
    EXPECT_DOUBLE_EQ(144, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 4U, 1U));
    EXPECT_DOUBLE_EQ(144, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 5U, 1U));
    EXPECT_DOUBLE_EQ(576, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 6U, 1U));
    EXPECT_DOUBLE_EQ(1152, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 7U, 1U));
    EXPECT_DOUBLE_EQ(10368, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 8U, 1U));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 9U, 1U));
    EXPECT_DOUBLE_EQ(576, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(1U, 6U, 1U));
    EXPECT_DOUBLE_EQ(48, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(2U, 5U, 1U));
    EXPECT_DOUBLE_EQ(12, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(3U, 4U, 1U));
    EXPECT_DOUBLE_EQ(4, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(4U, 4U, 1U));

    // On second previous step, the values are: 1, 3, 4, 3, 6, 1, 4, 2, 9
    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 0U, 2U));
    EXPECT_DOUBLE_EQ(3, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 1U, 2U));
    EXPECT_DOUBLE_EQ(12, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 2U, 2U));
    EXPECT_DOUBLE_EQ(36, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 3U, 2U));
    EXPECT_DOUBLE_EQ(216, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 4U, 2U));
    EXPECT_DOUBLE_EQ(216, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 5U, 2U));
    EXPECT_DOUBLE_EQ(864, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 6U, 2U));
    EXPECT_DOUBLE_EQ(1728, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 7U, 2U));
    EXPECT_DOUBLE_EQ(15552, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 8U, 2U));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 9U, 2U));
    EXPECT_DOUBLE_EQ(864, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(1U, 6U, 2U));
    EXPECT_DOUBLE_EQ(72, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(2U, 5U, 2U));
    EXPECT_DOUBLE_EQ(18, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(3U, 4U, 2U));
    EXPECT_DOUBLE_EQ(6, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(4U, 4U, 2U));

    // On third previous step (original values), the values are: 1, 3, 4, 8, 6, 1, 4, 2, 9
    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 0U, 3U));
    EXPECT_DOUBLE_EQ(3, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 1U, 3U));
    EXPECT_DOUBLE_EQ(12, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 2U, 3U));
    EXPECT_DOUBLE_EQ(96, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 3U, 3U));
    EXPECT_DOUBLE_EQ(576, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 4U, 3U));
    EXPECT_DOUBLE_EQ(576, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 5U, 3U));
    EXPECT_DOUBLE_EQ(2304, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 6U, 3U));
    EXPECT_DOUBLE_EQ(4608, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 7U, 3U));
    EXPECT_DOUBLE_EQ(41472, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 8U, 3U));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 9U, 3U));
    EXPECT_DOUBLE_EQ(2304, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(1U, 6U, 3U));
    EXPECT_DOUBLE_EQ(192, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(2U, 5U, 3U));
    EXPECT_DOUBLE_EQ(48, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(3U, 4U, 3U));
    EXPECT_DOUBLE_EQ(6, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(4U, 4U, 3U));

    // On fourth previous step, there are no values because there are only 3 changes
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 0U, 4U));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 1U, 4U));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 2U, 4U));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 3U, 4U));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 4U, 4U));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 5U, 4U));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 6U, 4U));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 7U, 4U));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 8U, 4U));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(0U, 9U, 4U));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(1U, 6U, 4U));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(2U, 5U, 4U));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(3U, 4U, 4U));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnIntervalOnPreviousTree(4U, 4U, 4U));
}

}

}
