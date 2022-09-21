#include <Algorithm/Search/RangeQuery/RangeQueryWithAccumulator.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using ValuesForTest = vector<unsigned int>;
using RangeQueryForTest = RangeQueryWithAccumulator<ValuesForTest>;
using ValueForTest = RangeQueryForTest::Value;

RangeQueryForTest::AccumulatorFunction plusAccumulator = [](ValueForTest const& value1, ValueForTest const& value2)
{
    return plus<ValueForTest>()(value1, value2);
};

RangeQueryForTest::AccumulatorFunction minusAccumulator = [](ValueForTest const& value1, ValueForTest const& value2)
{
    return minus<ValueForTest>()(value1, value2);
};

RangeQueryForTest::AccumulatorFunction multipliesAccumulator = [](ValueForTest const& value1, ValueForTest const& value2)
{
    return multiplies<ValueForTest>()(value1, value2);
};

RangeQueryForTest::AccumulatorFunction dividesAccumulator = [](ValueForTest const& value1, ValueForTest const& value2)
{
    return divides<ValueForTest>()(value1, value2);
};
}

TEST(RangeQueryWithAccumulatorTest, GetAccumulatedValueOnIntervalWithSumWorksInExample1)
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
    EXPECT_EQ(0U, sumRangeQuery.getAccumulatedValueOnInterval(0U, 9U));;
    EXPECT_EQ(26U, sumRangeQuery.getAccumulatedValueOnInterval(1U, 6U));
    EXPECT_EQ(19U, sumRangeQuery.getAccumulatedValueOnInterval(2U, 5U));
    EXPECT_EQ(14U, sumRangeQuery.getAccumulatedValueOnInterval(3U, 4U));
    EXPECT_EQ(6U, sumRangeQuery.getAccumulatedValueOnInterval(4U, 4U));
}

TEST(RangeQueryWithAccumulatorTest, GetAccumulatedValueOnIntervalWithSumWorksInExample2)
{
    ValuesForTest values{1U, 3U, 4U, 3U, 6U, 1U, 4U, 2U, 9U};
    RangeQueryForTest sumRangeQuery(values, plusAccumulator, minusAccumulator);

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

TEST(RangeQueryWithAccumulatorTest, GetAccumulatedValueOnIntervalWithGeometricSumWorksInExample1)
{
    ValuesForTest values{1U, 3U, 4U, 8U, 6U, 1U, 4U, 2U, 9U};
    RangeQueryForTest geometricSumRangeQuery(values, multipliesAccumulator, dividesAccumulator);

    EXPECT_EQ(1U, geometricSumRangeQuery.getAccumulatedValueOnInterval(0U, 0U));
    EXPECT_EQ(3U, geometricSumRangeQuery.getAccumulatedValueOnInterval(0U, 1U));
    EXPECT_EQ(12U, geometricSumRangeQuery.getAccumulatedValueOnInterval(0U, 2U));
    EXPECT_EQ(96U, geometricSumRangeQuery.getAccumulatedValueOnInterval(0U, 3U));
    EXPECT_EQ(576U, geometricSumRangeQuery.getAccumulatedValueOnInterval(0U, 4U));
    EXPECT_EQ(576U, geometricSumRangeQuery.getAccumulatedValueOnInterval(0U, 5U));
    EXPECT_EQ(2304U, geometricSumRangeQuery.getAccumulatedValueOnInterval(0U, 6U));
    EXPECT_EQ(4608U, geometricSumRangeQuery.getAccumulatedValueOnInterval(0U, 7U));
    EXPECT_EQ(41472U, geometricSumRangeQuery.getAccumulatedValueOnInterval(0U, 8U));
    EXPECT_EQ(0U, geometricSumRangeQuery.getAccumulatedValueOnInterval(0U, 9U));
    EXPECT_EQ(2304U, geometricSumRangeQuery.getAccumulatedValueOnInterval(1U, 6U));
    EXPECT_EQ(192U, geometricSumRangeQuery.getAccumulatedValueOnInterval(2U, 5U));
    EXPECT_EQ(48U, geometricSumRangeQuery.getAccumulatedValueOnInterval(3U, 4U));
    EXPECT_EQ(6U, geometricSumRangeQuery.getAccumulatedValueOnInterval(4U, 4U));
}

TEST(RangeQueryWithAccumulatorTest, GetAccumulatedValueOnIntervalWithGeometricSumWorksInExample2)
{
    ValuesForTest values{1U, 3U, 4U, 3U, 6U, 1U, 4U, 2U, 9U};
    RangeQueryForTest geometricSumRangeQuery(values, multipliesAccumulator, dividesAccumulator);

    EXPECT_EQ(1U, geometricSumRangeQuery.getAccumulatedValueOnInterval(0U, 0U));
    EXPECT_EQ(3U, geometricSumRangeQuery.getAccumulatedValueOnInterval(0U, 1U));
    EXPECT_EQ(12U, geometricSumRangeQuery.getAccumulatedValueOnInterval(0U, 2U));
    EXPECT_EQ(36U, geometricSumRangeQuery.getAccumulatedValueOnInterval(0U, 3U));
    EXPECT_EQ(216U, geometricSumRangeQuery.getAccumulatedValueOnInterval(0U, 4U));
    EXPECT_EQ(216U, geometricSumRangeQuery.getAccumulatedValueOnInterval(0U, 5U));
    EXPECT_EQ(864U, geometricSumRangeQuery.getAccumulatedValueOnInterval(0U, 6U));
    EXPECT_EQ(1728U, geometricSumRangeQuery.getAccumulatedValueOnInterval(0U, 7U));
    EXPECT_EQ(15552U, geometricSumRangeQuery.getAccumulatedValueOnInterval(0U, 8U));
    EXPECT_EQ(0U, geometricSumRangeQuery.getAccumulatedValueOnInterval(0U, 9U));
    EXPECT_EQ(864U, geometricSumRangeQuery.getAccumulatedValueOnInterval(1U, 6U));
    EXPECT_EQ(72U, geometricSumRangeQuery.getAccumulatedValueOnInterval(2U, 5U));
    EXPECT_EQ(18U, geometricSumRangeQuery.getAccumulatedValueOnInterval(3U, 4U));
    EXPECT_EQ(6U, geometricSumRangeQuery.getAccumulatedValueOnInterval(4U, 4U));
}

}

}
