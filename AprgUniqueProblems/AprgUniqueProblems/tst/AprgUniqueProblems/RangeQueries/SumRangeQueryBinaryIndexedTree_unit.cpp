#include <AprgUniqueProblems/RangeQueries/SumRangeQueryBinaryIndexedTree.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(SumRangeQueryBinaryIndexedTreeTest, GetSumFromStartAndEndWorksOnExample1)
{
    SumRangeQueryBinaryIndexedTree search({1U, 3U, 4U, 8U, 6U, 1U, 4U, 2U});

    EXPECT_EQ(1U, search.getSumFromStartToEnd(0U, 0U));
    EXPECT_EQ(4U, search.getSumFromStartToEnd(0U, 1U));
    EXPECT_EQ(8U, search.getSumFromStartToEnd(0U, 2U));
    EXPECT_EQ(16U, search.getSumFromStartToEnd(0U, 3U));
    EXPECT_EQ(22U, search.getSumFromStartToEnd(0U, 4U));
    EXPECT_EQ(23U, search.getSumFromStartToEnd(0U, 5U));
    EXPECT_EQ(27U, search.getSumFromStartToEnd(0U, 6U));
    EXPECT_EQ(29U, search.getSumFromStartToEnd(0U, 7U));
    EXPECT_EQ(0U, search.getSumFromStartToEnd(0U, 8U));
    EXPECT_EQ(26U, search.getSumFromStartToEnd(1U, 6U));
    EXPECT_EQ(19U, search.getSumFromStartToEnd(2U, 5U));
    EXPECT_EQ(14U, search.getSumFromStartToEnd(3U, 4U));
    EXPECT_EQ(6U, search.getSumFromStartToEnd(4U, 4U));
}

TEST(SumRangeQueryBinaryIndexedTreeTest, GetSumFrom0ToIndexOnExample1)
{
    SumRangeQueryBinaryIndexedTree search({1U, 3U, 4U, 8U, 6U, 1U, 4U, 2U});

    EXPECT_EQ(1U, search.getSumFrom0ToIndex(0U));
    EXPECT_EQ(4U, search.getSumFrom0ToIndex(1U));
    EXPECT_EQ(8U, search.getSumFrom0ToIndex(2U));
    EXPECT_EQ(16U, search.getSumFrom0ToIndex(3U));
    EXPECT_EQ(22U, search.getSumFrom0ToIndex(4U));
    EXPECT_EQ(23U, search.getSumFrom0ToIndex(5U));
    EXPECT_EQ(27U, search.getSumFrom0ToIndex(6U));
    EXPECT_EQ(29U, search.getSumFrom0ToIndex(7U));
    EXPECT_EQ(0U, search.getSumFrom0ToIndex(8U));
}

TEST(SumRangeQueryBinaryIndexedTreeTest, ChangeValueAtIndexWorks)
{
    SumRangeQueryBinaryIndexedTree search({1U, 3U, 4U, 8U, 6U, 1U, 4U, 2U});

    search.changeValueAtIndex(3U, 3U);

    EXPECT_EQ(1U, search.getSumFromStartToEnd(0U, 0U));
    EXPECT_EQ(4U, search.getSumFromStartToEnd(0U, 1U));
    EXPECT_EQ(8U, search.getSumFromStartToEnd(0U, 2U));
    EXPECT_EQ(11U, search.getSumFromStartToEnd(0U, 3U));
    EXPECT_EQ(17U, search.getSumFromStartToEnd(0U, 4U));
    EXPECT_EQ(18U, search.getSumFromStartToEnd(0U, 5U));
    EXPECT_EQ(22U, search.getSumFromStartToEnd(0U, 6U));
    EXPECT_EQ(24U, search.getSumFromStartToEnd(0U, 7U));
    EXPECT_EQ(0U, search.getSumFromStartToEnd(0U, 8U));
    EXPECT_EQ(21U, search.getSumFromStartToEnd(1U, 6U));
    EXPECT_EQ(14U, search.getSumFromStartToEnd(2U, 5U));
    EXPECT_EQ(9U, search.getSumFromStartToEnd(3U, 4U));
    EXPECT_EQ(6U, search.getSumFromStartToEnd(4U, 4U));
}

}
