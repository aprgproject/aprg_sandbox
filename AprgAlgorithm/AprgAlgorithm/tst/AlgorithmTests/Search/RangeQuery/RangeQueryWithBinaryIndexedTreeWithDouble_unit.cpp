#include <Algorithm/Search/RangeQuery/RangeQueryWithBinaryIndexedTree.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using ValuesForTest = vector<double>;
using RangeQueryForTest = RangeQueryWithBinaryIndexedTree<ValuesForTest>;
using ValueForTest = RangeQueryForTest::Value;

RangeQueryForTest::AccumulatorFunction multipliesAccumulator = [](ValueForTest const& value1, ValueForTest const& value2)
{
    return multiplies<ValueForTest>()(value1, value2);
};

RangeQueryForTest::AccumulatorFunction dividesAccumulator = [](ValueForTest const& value1, ValueForTest const& value2)
{
    return divides<ValueForTest>()(value1, value2);
};
}

TEST(RangeQueryWithBinaryIndexedTreeTest, GetAccumulatedValueOnIntervalWithGeometricSumWorksWithEmptySetOfValues)
{
    ValuesForTest values;
    RangeQueryForTest geometricSumRangeQuery(values, multipliesAccumulator, dividesAccumulator);

    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getAccumulatedValueOnInterval(0U, 0U));
}

TEST(RangeQueryWithBinaryIndexedTreeTest, GetAccumulatedValueOnIntervalWithGeometricSumWorksOnExample1)
{
    ValuesForTest values{1, 3, 4, 8, 6, 1, 4, 2, 9};
    RangeQueryForTest geometricSumRangeQuery(values, multipliesAccumulator, dividesAccumulator);

    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getAccumulatedValueOnInterval(0U, 0U));
    EXPECT_DOUBLE_EQ(3, geometricSumRangeQuery.getAccumulatedValueOnInterval(0U, 1U));
    EXPECT_DOUBLE_EQ(12, geometricSumRangeQuery.getAccumulatedValueOnInterval(0U, 2U));
    EXPECT_DOUBLE_EQ(96, geometricSumRangeQuery.getAccumulatedValueOnInterval(0U, 3U));
    EXPECT_DOUBLE_EQ(576, geometricSumRangeQuery.getAccumulatedValueOnInterval(0U, 4U));
    EXPECT_DOUBLE_EQ(576, geometricSumRangeQuery.getAccumulatedValueOnInterval(0U, 5U));
    EXPECT_DOUBLE_EQ(2304, geometricSumRangeQuery.getAccumulatedValueOnInterval(0U, 6U));
    EXPECT_DOUBLE_EQ(4608, geometricSumRangeQuery.getAccumulatedValueOnInterval(0U, 7U));
    EXPECT_DOUBLE_EQ(41472, geometricSumRangeQuery.getAccumulatedValueOnInterval(0U, 8U));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getAccumulatedValueOnInterval(0U, 9U));
    EXPECT_DOUBLE_EQ(2304, geometricSumRangeQuery.getAccumulatedValueOnInterval(1U, 6U));
    EXPECT_DOUBLE_EQ(192, geometricSumRangeQuery.getAccumulatedValueOnInterval(2U, 5U));
    EXPECT_DOUBLE_EQ(48, geometricSumRangeQuery.getAccumulatedValueOnInterval(3U, 4U));
    EXPECT_DOUBLE_EQ(6, geometricSumRangeQuery.getAccumulatedValueOnInterval(4U, 4U));
}

TEST(RangeQueryWithBinaryIndexedTreeTest, GetSumFrom0ToIndexWithGeometricSumWorksWithEmptySetOfValues)
{
    ValuesForTest values;
    RangeQueryForTest geometricSumRangeQuery(values, multipliesAccumulator, dividesAccumulator);

    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getAccumulatedValueFrom0ToIndex(0U));
}

TEST(RangeQueryWithBinaryIndexedTreeTest, GetSumFrom0ToIndexWithGeometricSumWorksOnExample1)
{
    ValuesForTest values{1, 3, 4, 8, 6, 1, 4, 2, 9};
    RangeQueryForTest geometricSumRangeQuery(values, multipliesAccumulator, dividesAccumulator);

    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getAccumulatedValueFrom0ToIndex(0U));
    EXPECT_DOUBLE_EQ(3, geometricSumRangeQuery.getAccumulatedValueFrom0ToIndex(1U));
    EXPECT_DOUBLE_EQ(12, geometricSumRangeQuery.getAccumulatedValueFrom0ToIndex(2U));
    EXPECT_DOUBLE_EQ(96, geometricSumRangeQuery.getAccumulatedValueFrom0ToIndex(3U));
    EXPECT_DOUBLE_EQ(576, geometricSumRangeQuery.getAccumulatedValueFrom0ToIndex(4U));
    EXPECT_DOUBLE_EQ(576, geometricSumRangeQuery.getAccumulatedValueFrom0ToIndex(5U));
    EXPECT_DOUBLE_EQ(2304, geometricSumRangeQuery.getAccumulatedValueFrom0ToIndex(6U));
    EXPECT_DOUBLE_EQ(4608, geometricSumRangeQuery.getAccumulatedValueFrom0ToIndex(7U));
    EXPECT_DOUBLE_EQ(41472, geometricSumRangeQuery.getAccumulatedValueFrom0ToIndex(8U));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getAccumulatedValueFrom0ToIndex(9U));
}

TEST(RangeQueryWithBinaryIndexedTreeTest, ChangeValueAtIndexWithGeometricSumWorksWithEmptySetOfValues)
{
    ValuesForTest values;
    RangeQueryForTest geometricSumRangeQuery(values, multipliesAccumulator, dividesAccumulator);

    geometricSumRangeQuery.changeValueAtIndex(0U, 0);

    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getAccumulatedValueOnInterval(0U, 0U));
}

TEST(RangeQueryWithBinaryIndexedTreeTest, ChangeValueAtIndexWithGeometricSumWorksOnExample1)
{
    ValuesForTest values{1, 3, 4, 8, 6, 1, 4, 2, 9};
    RangeQueryForTest geometricSumRangeQuery(values, multipliesAccumulator, dividesAccumulator);

    geometricSumRangeQuery.changeValueAtIndex(3U, 3);

    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getAccumulatedValueOnInterval(0U, 0U));
    EXPECT_DOUBLE_EQ(3, geometricSumRangeQuery.getAccumulatedValueOnInterval(0U, 1U));
    EXPECT_DOUBLE_EQ(12, geometricSumRangeQuery.getAccumulatedValueOnInterval(0U, 2U));
    EXPECT_DOUBLE_EQ(36, geometricSumRangeQuery.getAccumulatedValueOnInterval(0U, 3U));
    EXPECT_DOUBLE_EQ(216, geometricSumRangeQuery.getAccumulatedValueOnInterval(0U, 4U));
    EXPECT_DOUBLE_EQ(216, geometricSumRangeQuery.getAccumulatedValueOnInterval(0U, 5U));
    EXPECT_DOUBLE_EQ(864, geometricSumRangeQuery.getAccumulatedValueOnInterval(0U, 6U));
    EXPECT_DOUBLE_EQ(1728, geometricSumRangeQuery.getAccumulatedValueOnInterval(0U, 7U));
    EXPECT_DOUBLE_EQ(15552, geometricSumRangeQuery.getAccumulatedValueOnInterval(0U, 8U));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getAccumulatedValueOnInterval(0U, 9U));
    EXPECT_DOUBLE_EQ(864, geometricSumRangeQuery.getAccumulatedValueOnInterval(1U, 6U));
    EXPECT_DOUBLE_EQ(72, geometricSumRangeQuery.getAccumulatedValueOnInterval(2U, 5U));
    EXPECT_DOUBLE_EQ(18, geometricSumRangeQuery.getAccumulatedValueOnInterval(3U, 4U));
    EXPECT_DOUBLE_EQ(6, geometricSumRangeQuery.getAccumulatedValueOnInterval(4U, 4U));
}

}

}
