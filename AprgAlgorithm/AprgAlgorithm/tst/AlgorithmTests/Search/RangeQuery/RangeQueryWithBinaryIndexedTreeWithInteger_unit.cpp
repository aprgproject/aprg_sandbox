#include <Algorithm/Search/RangeQuery/RangeQueryWithBinaryIndexedTree.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using ValuesForTest = vector<unsigned int>;
using RangeQueryForTest = RangeQueryWithBinaryIndexedTree<ValuesForTest>;
using ValueForTest = RangeQueryForTest::Value;

RangeQueryForTest::AccumulatorFunction plusAccumulator = [](ValueForTest const& value1, ValueForTest const& value2)
{
    return plus<ValueForTest>()(value1, value2);
};

RangeQueryForTest::AccumulatorFunction minusAccumulator = [](ValueForTest const& value1, ValueForTest const& value2)
{
    return minus<ValueForTest>()(value1, value2);
};
}

TEST(RangeQueryWithBinaryIndexedTreeTest, GetAccumulatedValueOnIntervalWithSumWorksWithEmptySetOfValues)
{
    ValuesForTest values;
    RangeQueryForTest sumRangeQuery(values, plusAccumulator, minusAccumulator);

    EXPECT_EQ(0U, sumRangeQuery.getAccumulatedValueOnInterval(0U, 0U));
}

TEST(RangeQueryWithBinaryIndexedTreeTest, GetAccumulatedValueOnIntervalWithSumWorksOnExample1)
{
    ValuesForTest values{1U, 3U, 4U, 8U, 6U, 1U, 4U, 2U, 9U};
    RangeQueryForTest sumRangeQuery(values, plusAccumulator, minusAccumulator);

    EXPECT_EQ(1U, sumRangeQuery.getAccumulatedValueOnInterval(0U, 0U));
    EXPECT_EQ(4U, sumRangeQuery.getAccumulatedValueOnInterval(0U, 1U));
    EXPECT_EQ(8U, sumRangeQuery.getAccumulatedValueOnInterval(0U, 2U));
    EXPECT_EQ(16U, sumRangeQuery.getAccumulatedValueOnInterval(0U, 3U));
    EXPECT_EQ(22U, sumRangeQuery.getAccumulatedValueOnInterval(0U, 4U));
    EXPECT_EQ(23U, sumRangeQuery.getAccumulatedValueOnInterval(0U, 5U));
    EXPECT_EQ(27U, sumRangeQuery.getAccumulatedValueOnInterval(0U, 6U));
    EXPECT_EQ(29U, sumRangeQuery.getAccumulatedValueOnInterval(0U, 7U));
    EXPECT_EQ(38U, sumRangeQuery.getAccumulatedValueOnInterval(0U, 8U));
    EXPECT_EQ(0U, sumRangeQuery.getAccumulatedValueOnInterval(0U, 9U));
    EXPECT_EQ(26U, sumRangeQuery.getAccumulatedValueOnInterval(1U, 6U));
    EXPECT_EQ(19U, sumRangeQuery.getAccumulatedValueOnInterval(2U, 5U));
    EXPECT_EQ(14U, sumRangeQuery.getAccumulatedValueOnInterval(3U, 4U));
    EXPECT_EQ(6U, sumRangeQuery.getAccumulatedValueOnInterval(4U, 4U));
}

TEST(RangeQueryWithBinaryIndexedTreeTest, GetSumFrom0ToIndexWithSumWorksWithEmptySetOfValues)
{
    ValuesForTest values;
    RangeQueryForTest sumRangeQuery(values, plusAccumulator, minusAccumulator);

    EXPECT_EQ(0U, sumRangeQuery.getAccumulatedValueFrom0ToIndex(0U));
}

TEST(RangeQueryWithBinaryIndexedTreeTest, GetSumFrom0ToIndexWithSumWorksOnExample1)
{
    ValuesForTest values{1U, 3U, 4U, 8U, 6U, 1U, 4U, 2U, 9U};
    RangeQueryForTest sumRangeQuery(values, plusAccumulator, minusAccumulator);

    EXPECT_EQ(1U, sumRangeQuery.getAccumulatedValueFrom0ToIndex(0U));
    EXPECT_EQ(4U, sumRangeQuery.getAccumulatedValueFrom0ToIndex(1U));
    EXPECT_EQ(8U, sumRangeQuery.getAccumulatedValueFrom0ToIndex(2U));
    EXPECT_EQ(16U, sumRangeQuery.getAccumulatedValueFrom0ToIndex(3U));
    EXPECT_EQ(22U, sumRangeQuery.getAccumulatedValueFrom0ToIndex(4U));
    EXPECT_EQ(23U, sumRangeQuery.getAccumulatedValueFrom0ToIndex(5U));
    EXPECT_EQ(27U, sumRangeQuery.getAccumulatedValueFrom0ToIndex(6U));
    EXPECT_EQ(29U, sumRangeQuery.getAccumulatedValueFrom0ToIndex(7U));
    EXPECT_EQ(38U, sumRangeQuery.getAccumulatedValueFrom0ToIndex(8U));
    EXPECT_EQ(0U, sumRangeQuery.getAccumulatedValueFrom0ToIndex(9U));
}

TEST(RangeQueryWithBinaryIndexedTreeTest, ChangeValueAtIndexWithSumWorksWithEmptySetOfValues)
{
    ValuesForTest values;
    RangeQueryForTest sumRangeQuery(values, plusAccumulator, minusAccumulator);

    sumRangeQuery.changeValueAtIndex(0U, 0U);

    EXPECT_EQ(0U, sumRangeQuery.getAccumulatedValueOnInterval(0U, 0U));
}

TEST(RangeQueryWithBinaryIndexedTreeTest, ChangeValueAtIndexWithSumWorksOnExample1)
{
    ValuesForTest values{1U, 3U, 4U, 8U, 6U, 1U, 4U, 2U, 9U};
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
    EXPECT_EQ(33U, sumRangeQuery.getAccumulatedValueOnInterval(0U, 8U));
    EXPECT_EQ(0U, sumRangeQuery.getAccumulatedValueOnInterval(0U, 9U));
    EXPECT_EQ(21U, sumRangeQuery.getAccumulatedValueOnInterval(1U, 6U));
    EXPECT_EQ(14U, sumRangeQuery.getAccumulatedValueOnInterval(2U, 5U));
    EXPECT_EQ(9U, sumRangeQuery.getAccumulatedValueOnInterval(3U, 4U));
    EXPECT_EQ(6U, sumRangeQuery.getAccumulatedValueOnInterval(4U, 4U));
}

TEST(RangeQueryWithBinaryIndexedTreeTest, ChangeValueAtIndexWithSumWorksTwiceOnExample1)
{
    ValuesForTest values{1U, 3U, 4U, 8U, 6U, 1U, 4U, 2U, 9U};
    RangeQueryForTest sumRangeQuery(values, plusAccumulator, minusAccumulator);

    sumRangeQuery.changeValueAtIndex(3U, 3U);
    sumRangeQuery.changeValueAtIndex(3U, 13U);

    EXPECT_EQ(1U, sumRangeQuery.getAccumulatedValueOnInterval(0U, 0U));
    EXPECT_EQ(4U, sumRangeQuery.getAccumulatedValueOnInterval(0U, 1U));
    EXPECT_EQ(8U, sumRangeQuery.getAccumulatedValueOnInterval(0U, 2U));
    EXPECT_EQ(21U, sumRangeQuery.getAccumulatedValueOnInterval(0U, 3U));
    EXPECT_EQ(27U, sumRangeQuery.getAccumulatedValueOnInterval(0U, 4U));
    EXPECT_EQ(28U, sumRangeQuery.getAccumulatedValueOnInterval(0U, 5U));
    EXPECT_EQ(32U, sumRangeQuery.getAccumulatedValueOnInterval(0U, 6U));
    EXPECT_EQ(34U, sumRangeQuery.getAccumulatedValueOnInterval(0U, 7U));
    EXPECT_EQ(43U, sumRangeQuery.getAccumulatedValueOnInterval(0U, 8U));
    EXPECT_EQ(0U, sumRangeQuery.getAccumulatedValueOnInterval(0U, 9U));
    EXPECT_EQ(31U, sumRangeQuery.getAccumulatedValueOnInterval(1U, 6U));
    EXPECT_EQ(24U, sumRangeQuery.getAccumulatedValueOnInterval(2U, 5U));
    EXPECT_EQ(19U, sumRangeQuery.getAccumulatedValueOnInterval(3U, 4U));
    EXPECT_EQ(6U, sumRangeQuery.getAccumulatedValueOnInterval(4U, 4U));
}

}

}
