#include <Algorithm/Search/RangeQuery/SegmentTree/RangeQueryWithAccumulatorLazySegmentTree.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using ValuesForTest = vector<unsigned int>;
using RangeQueryForTest = RangeQueryWithAccumulatorLazySegmentTree<ValuesForTest>;
using ValueForTest = RangeQueryForTest::Value;
RangeQueryForTest::Function plusFunction = plus<>();
RangeQueryForTest::Function minusFunction = minus<>();
}

TEST(RangeQueryWithAccumulatorLazySegmentTreeTest, GetValueOnIntervalWithMinimumWorksWithEmptySetOfValues)
{
    ValuesForTest values;
    RangeQueryForTest sumRangeQuery(values, plusFunction, minusFunction, 0U);

    EXPECT_EQ(0U, sumRangeQuery.getValueOnInterval(0U, 0U));
}

TEST(RangeQueryWithAccumulatorLazySegmentTreeTest, GetValueOnIntervalWithSumWorksOnExample1)
{
    ValuesForTest values{1U, 3U, 4U, 8U, 6U, 1U, 4U, 2U, 9U};
    RangeQueryForTest sumRangeQuery(values, plusFunction, minusFunction, 0U);

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

TEST(RangeQueryWithAccumulatorLazySegmentTreeTest, IncreaseAtRangeWithSumWorksWithEmptySetOfValues)
{
    ValuesForTest values;
    RangeQueryForTest sumRangeQuery(values, plusFunction, minusFunction, 0U);

    sumRangeQuery.increaseAtRange(0U, 5U, 4U);

    EXPECT_EQ(0U, sumRangeQuery.getValueOnInterval(0U, 0U));
}

TEST(RangeQueryWithAccumulatorLazySegmentTreeTest, IncreaseAtRangeWithSumWorksOnExample1)
{
    ValuesForTest values{1U, 3U, 4U, 8U, 6U, 1U, 4U, 2U, 9U};
    RangeQueryForTest sumRangeQuery(values, plusFunction, minusFunction, 0U);

    sumRangeQuery.increaseAtRange(0U, 5U, 4U);

    EXPECT_EQ(5U, sumRangeQuery.getValueOnInterval(0U, 0U));
    EXPECT_EQ(12U, sumRangeQuery.getValueOnInterval(0U, 1U));
    EXPECT_EQ(20U, sumRangeQuery.getValueOnInterval(0U, 2U));
    EXPECT_EQ(32U, sumRangeQuery.getValueOnInterval(0U, 3U));
    EXPECT_EQ(42U, sumRangeQuery.getValueOnInterval(0U, 4U));
    EXPECT_EQ(47U, sumRangeQuery.getValueOnInterval(0U, 5U));
    EXPECT_EQ(51U, sumRangeQuery.getValueOnInterval(0U, 6U));
    EXPECT_EQ(53U, sumRangeQuery.getValueOnInterval(0U, 7U));
    EXPECT_EQ(62U, sumRangeQuery.getValueOnInterval(0U, 8U));
    EXPECT_EQ(0U, sumRangeQuery.getValueOnInterval(0U, 9U));
    EXPECT_EQ(46U, sumRangeQuery.getValueOnInterval(1U, 6U));
    EXPECT_EQ(35U, sumRangeQuery.getValueOnInterval(2U, 5U));
    EXPECT_EQ(22U, sumRangeQuery.getValueOnInterval(3U, 4U));
    EXPECT_EQ(10U, sumRangeQuery.getValueOnInterval(4U, 4U));
}

TEST(RangeQueryWithAccumulatorLazySegmentTreeTest, ChangeValueAtIndexWithSumWorksWithEmptySetOfValues)
{
    ValuesForTest values;
    RangeQueryForTest sumRangeQuery(values, plusFunction, minusFunction, 0U);

    sumRangeQuery.changeValueAtIndex(0U, 0U);

    EXPECT_EQ(0U, sumRangeQuery.getValueOnInterval(0U, 0U));
}

TEST(RangeQueryWithAccumulatorLazySegmentTreeTest, ChangeValueAtIndexWithSumWorksWithOneValue)
{
    ValuesForTest values{5};
    RangeQueryForTest sumRangeQuery(values, plusFunction, minusFunction, 0U);

    sumRangeQuery.changeValueAtIndex(0U, 3U);

    EXPECT_EQ(3U, sumRangeQuery.getValueOnInterval(0U, 0U));
}

TEST(RangeQueryWithAccumulatorLazySegmentTreeTest, ChangeValueAtIndexWithSumWorksOnExample1)
{
    ValuesForTest values{1U, 3U, 4U, 8U, 6U, 1U, 4U, 2U, 9U};
    RangeQueryForTest sumRangeQuery(values, plusFunction, minusFunction, 0U);

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

}

}
