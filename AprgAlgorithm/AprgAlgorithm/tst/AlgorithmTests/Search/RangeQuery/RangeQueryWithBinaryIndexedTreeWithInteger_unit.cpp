#include <Algorithm/Search/RangeQuery/RangeQueryWithBinaryIndexedTree.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using ValueForTest = unsigned int;using RangeQueryForTest = RangeQueryWithBinaryIndexedTree<ValueForTest>;
using ValuesForTest = RangeQueryForTest::Values;

RangeQueryForTest::AccumulatorFunction plusAccumulator = [](ValueForTest const& value1, ValueForTest const& value2){
    return plus<ValueForTest>()(value1, value2);
};

RangeQueryForTest::AccumulatorFunction minusAccumulator = [](ValueForTest const& value1, ValueForTest const& value2)
{
    return minus<ValueForTest>()(value1, value2);
};
}

TEST(RangeQueryWithBinaryIndexedTreeTest, GetAccumulatedValueOnIntervalWithSumWorksOnExample1)
{
    ValuesForTest values{1U, 3U, 4U, 8U, 6U, 1U, 4U, 2U};
    RangeQueryForTest sumRangeQuery(values, plusAccumulator, minusAccumulator);

    EXPECT_EQ(1U, sumRangeQuery.getAccumulatedValueOnInterval(0U, 0U));
    EXPECT_EQ(4U, sumRangeQuery.getAccumulatedValueOnInterval(0U, 1U));
    EXPECT_EQ(8U, sumRangeQuery.getAccumulatedValueOnInterval(0U, 2U));
    EXPECT_EQ(16U, sumRangeQuery.getAccumulatedValueOnInterval(0U, 3U));
    EXPECT_EQ(22U, sumRangeQuery.getAccumulatedValueOnInterval(0U, 4U));
    EXPECT_EQ(23U, sumRangeQuery.getAccumulatedValueOnInterval(0U, 5U));
    EXPECT_EQ(27U, sumRangeQuery.getAccumulatedValueOnInterval(0U, 6U));
    EXPECT_EQ(29U, sumRangeQuery.getAccumulatedValueOnInterval(0U, 7U));
    EXPECT_EQ(0U, sumRangeQuery.getAccumulatedValueOnInterval(0U, 8U));
    EXPECT_EQ(26U, sumRangeQuery.getAccumulatedValueOnInterval(1U, 6U));
    EXPECT_EQ(19U, sumRangeQuery.getAccumulatedValueOnInterval(2U, 5U));
    EXPECT_EQ(14U, sumRangeQuery.getAccumulatedValueOnInterval(3U, 4U));
    EXPECT_EQ(6U, sumRangeQuery.getAccumulatedValueOnInterval(4U, 4U));
}

TEST(RangeQueryWithBinaryIndexedTreeTest, GetSumFrom0ToIndexWithSumWorksOnExample1)
{
    ValuesForTest values{1U, 3U, 4U, 8U, 6U, 1U, 4U, 2U};
    RangeQueryForTest sumRangeQuery(values, plusAccumulator, minusAccumulator);

    EXPECT_EQ(1U, sumRangeQuery.getAccumulatedValueFrom0ToIndex(0U));
    EXPECT_EQ(4U, sumRangeQuery.getAccumulatedValueFrom0ToIndex(1U));
    EXPECT_EQ(8U, sumRangeQuery.getAccumulatedValueFrom0ToIndex(2U));
    EXPECT_EQ(16U, sumRangeQuery.getAccumulatedValueFrom0ToIndex(3U));
    EXPECT_EQ(22U, sumRangeQuery.getAccumulatedValueFrom0ToIndex(4U));
    EXPECT_EQ(23U, sumRangeQuery.getAccumulatedValueFrom0ToIndex(5U));
    EXPECT_EQ(27U, sumRangeQuery.getAccumulatedValueFrom0ToIndex(6U));
    EXPECT_EQ(29U, sumRangeQuery.getAccumulatedValueFrom0ToIndex(7U));
    EXPECT_EQ(0U, sumRangeQuery.getAccumulatedValueFrom0ToIndex(8U));
}

TEST(RangeQueryWithBinaryIndexedTreeTest, ChangeValueAtIndexWithSumWorksOnExample1)
{
    ValuesForTest values{1U, 3U, 4U, 8U, 6U, 1U, 4U, 2U};
    RangeQueryForTest sumRangeQuery(values, plusAccumulator, minusAccumulator);

    sumRangeQuery.changeValueAtIndex(3U, 3U);

    EXPECT_EQ(1U, sumRangeQuery.getAccumulatedValueOnInterval(0U, 0U));
    EXPECT_EQ(4U, sumRangeQuery.getAccumulatedValueOnInterval(0U, 1U));
    EXPECT_EQ(8U, sumRangeQuery.getAccumulatedValueOnInterval(0U, 2U));
    EXPECT_EQ(11U, sumRangeQuery.getAccumulatedValueOnInterval(0U, 3U));
    EXPECT_EQ(17U, sumRangeQuery.getAccumulatedValueOnInterval(0U, 4U));
    EXPECT_EQ(18U, sumRangeQuery.getAccumulatedValueOnInterval(0U, 5U));
    EXPECT_EQ(22U, sumRangeQuery.getAccumulatedValueOnInterval(0U, 6U));
    EXPECT_EQ(24U, sumRangeQuery.getAccumulatedValueOnInterval(0U, 7U));
    EXPECT_EQ(0U, sumRangeQuery.getAccumulatedValueOnInterval(0U, 8U));
    EXPECT_EQ(21U, sumRangeQuery.getAccumulatedValueOnInterval(1U, 6U));
    EXPECT_EQ(14U, sumRangeQuery.getAccumulatedValueOnInterval(2U, 5U));
    EXPECT_EQ(9U, sumRangeQuery.getAccumulatedValueOnInterval(3U, 4U));
    EXPECT_EQ(6U, sumRangeQuery.getAccumulatedValueOnInterval(4U, 4U));
}

}

}