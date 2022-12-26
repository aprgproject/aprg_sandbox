#include <Algorithm/Search/RangeQuery/TwoDimensions/RangeQueryForTwoDSegmentTree.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using ValueForTest = unsigned int;
using RangeQueryForTest = RangeQueryForTwoDSegmentTree<unsigned int>;
using ValueMatrixForTest = RangeQueryForTest::ValueMatrix;
using Function = typename RangeQueryForTest::OneDFunction;
Function plusFunction = plus<>();
}

TEST(RangeQueryForTwoDSegmentTreeTest, GetValueOn2DIntervalWorksOnExample1)
{
    ValueMatrixForTest valueMatrix(4U, 4U,
    {7U, 6U, 1U, 6U,
     8U, 7U, 5U, 2U,
     3U, 9U, 7U, 1U,
     8U, 5U, 3U, 8U});
    RangeQueryForTest sumRangeQuery(valueMatrix, plusFunction);

    // starts with (0,0)
    EXPECT_EQ(7U, sumRangeQuery.getValueOn2DInterval(0U, 0U, 0U, 0U));
    EXPECT_EQ(28U, sumRangeQuery.getValueOn2DInterval(0U, 0U, 1U, 1U));
    EXPECT_EQ(53U, sumRangeQuery.getValueOn2DInterval(0U, 0U, 2U, 2U));
    EXPECT_EQ(86U, sumRangeQuery.getValueOn2DInterval(0U, 0U, 3U, 3U));

    // starts with (0,1)
    EXPECT_EQ(0U, sumRangeQuery.getValueOn2DInterval(0U, 1U, 0U, 0U));
    EXPECT_EQ(15U, sumRangeQuery.getValueOn2DInterval(0U, 1U, 1U, 1U));
    EXPECT_EQ(39U, sumRangeQuery.getValueOn2DInterval(0U, 1U, 2U, 2U));
    EXPECT_EQ(66U, sumRangeQuery.getValueOn2DInterval(0U, 1U, 3U, 3U));

    // starts with (1,0)
    EXPECT_EQ(0U, sumRangeQuery.getValueOn2DInterval(1U, 0U, 0U, 0U));
    EXPECT_EQ(13U, sumRangeQuery.getValueOn2DInterval(1U, 0U, 1U, 1U));
    EXPECT_EQ(35U, sumRangeQuery.getValueOn2DInterval(1U, 0U, 2U, 2U));
    EXPECT_EQ(60U, sumRangeQuery.getValueOn2DInterval(1U, 0U, 3U, 3U));

    // starts with (1,1)
    EXPECT_EQ(0U, sumRangeQuery.getValueOn2DInterval(1U, 1U, 0U, 0U));
    EXPECT_EQ(7U, sumRangeQuery.getValueOn2DInterval(1U, 1U, 1U, 1U));
    EXPECT_EQ(28U, sumRangeQuery.getValueOn2DInterval(1U, 1U, 2U, 2U));
    EXPECT_EQ(47U, sumRangeQuery.getValueOn2DInterval(1U, 1U, 3U, 3U));
}

TEST(RangeQueryForTwoDSegmentTreeTest, ChangeValueAtWorksOnExample1)
{
    ValueMatrixForTest valueMatrix(4U, 4U,
    {7U, 6U, 1U, 6U,
     8U, 7U, 5U, 2U,
     3U, 9U, 7U, 1U,
     8U, 5U, 3U, 8U});
    RangeQueryForTest sumRangeQuery(valueMatrix, plusFunction);

    sumRangeQuery.changeValueAt(0U, 0U, 14U);

    // starts with (0,0)
    EXPECT_EQ(14U, sumRangeQuery.getValueOn2DInterval(0U, 0U, 0U, 0U));
    EXPECT_EQ(35U, sumRangeQuery.getValueOn2DInterval(0U, 0U, 1U, 1U));
    EXPECT_EQ(60U, sumRangeQuery.getValueOn2DInterval(0U, 0U, 2U, 2U));
    EXPECT_EQ(93U, sumRangeQuery.getValueOn2DInterval(0U, 0U, 3U, 3U));

    // starts with (0,1)
    EXPECT_EQ(0U, sumRangeQuery.getValueOn2DInterval(0U, 1U, 0U, 0U));
    EXPECT_EQ(15U, sumRangeQuery.getValueOn2DInterval(0U, 1U, 1U, 1U));
    EXPECT_EQ(39U, sumRangeQuery.getValueOn2DInterval(0U, 1U, 2U, 2U));
    EXPECT_EQ(66U, sumRangeQuery.getValueOn2DInterval(0U, 1U, 3U, 3U));

    // starts with (1,0)
    EXPECT_EQ(0U, sumRangeQuery.getValueOn2DInterval(1U, 0U, 0U, 0U));
    EXPECT_EQ(13U, sumRangeQuery.getValueOn2DInterval(1U, 0U, 1U, 1U));
    EXPECT_EQ(35U, sumRangeQuery.getValueOn2DInterval(1U, 0U, 2U, 2U));
    EXPECT_EQ(60U, sumRangeQuery.getValueOn2DInterval(1U, 0U, 3U, 3U));

    // starts with (1,1)
    EXPECT_EQ(0U, sumRangeQuery.getValueOn2DInterval(1U, 1U, 0U, 0U));
    EXPECT_EQ(7U, sumRangeQuery.getValueOn2DInterval(1U, 1U, 1U, 1U));
    EXPECT_EQ(28U, sumRangeQuery.getValueOn2DInterval(1U, 1U, 2U, 2U));
    EXPECT_EQ(47U, sumRangeQuery.getValueOn2DInterval(1U, 1U, 3U, 3U));
}

}

}
