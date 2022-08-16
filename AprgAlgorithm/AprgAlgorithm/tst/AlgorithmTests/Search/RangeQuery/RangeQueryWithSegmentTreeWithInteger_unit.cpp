#include <Algorithm/Search/RangeQuery/RangeQueryWithSegmentTree.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using ValueForTest = unsigned int;using RangeQueryForTest = RangeQueryWithSegmentTree<ValueForTest>;
using ValuesForTest = RangeQueryForTest::Values;

RangeQueryForTest::Function minimumSelector = [](ValueForTest const& value1, ValueForTest const& value2){
    return min(value1, value2);
};

RangeQueryForTest::Function maximumSelector = [](ValueForTest const& value1, ValueForTest const& value2)
{
    return max(value1, value2);
};

RangeQueryForTest::Function plusAccumulator = [](ValueForTest const& value1, ValueForTest const& value2)
{
    return plus<ValueForTest>()(value1, value2);
};
}

TEST(RangeQueryWithSegmentTreeTest, GetValueOnIntervalWithMinimumWorksInExample1)
{
    ValuesForTest values{5U, 9U, 4U, 8U, 6U, 1U, 4U, 2U};
    RangeQueryForTest minimumRangeQuery(values, minimumSelector);

    EXPECT_EQ(5U, minimumRangeQuery.getValueOnInterval(0U, 0U));
    EXPECT_EQ(5U, minimumRangeQuery.getValueOnInterval(0U, 1U));
    EXPECT_EQ(4U, minimumRangeQuery.getValueOnInterval(0U, 2U));
    EXPECT_EQ(4U, minimumRangeQuery.getValueOnInterval(0U, 3U));
    EXPECT_EQ(4U, minimumRangeQuery.getValueOnInterval(0U, 4U));
    EXPECT_EQ(1U, minimumRangeQuery.getValueOnInterval(0U, 5U));
    EXPECT_EQ(1U, minimumRangeQuery.getValueOnInterval(0U, 6U));
    EXPECT_EQ(1U, minimumRangeQuery.getValueOnInterval(0U, 7U));
    EXPECT_EQ(1U, minimumRangeQuery.getValueOnInterval(3U, 6U));
    EXPECT_EQ(4U, minimumRangeQuery.getValueOnInterval(2U, 4U));
}

TEST(RangeQueryWithSegmentTreeTest, GetValueOnIntervalWithMaximumWorksInExample1)
{
    ValuesForTest values{5U, 9U, 4U, 8U, 6U, 1U, 4U, 2U};
    RangeQueryForTest maximumRangeQuery(values, maximumSelector);

    EXPECT_EQ(5U, maximumRangeQuery.getValueOnInterval(0U, 0U));
    EXPECT_EQ(9U, maximumRangeQuery.getValueOnInterval(0U, 1U));
    EXPECT_EQ(9U, maximumRangeQuery.getValueOnInterval(0U, 2U));
    EXPECT_EQ(9U, maximumRangeQuery.getValueOnInterval(0U, 3U));
    EXPECT_EQ(9U, maximumRangeQuery.getValueOnInterval(0U, 4U));
    EXPECT_EQ(9U, maximumRangeQuery.getValueOnInterval(0U, 5U));
    EXPECT_EQ(9U, maximumRangeQuery.getValueOnInterval(0U, 6U));
    EXPECT_EQ(9U, maximumRangeQuery.getValueOnInterval(0U, 7U));
    EXPECT_EQ(8U, maximumRangeQuery.getValueOnInterval(3U, 6U));
    EXPECT_EQ(8U, maximumRangeQuery.getValueOnInterval(2U, 4U));
}

TEST(RangeQueryWithSegmentTreeTest, GetValueOnIntervalWithSumWorksOnExample1)
{
    ValuesForTest values{1U, 3U, 4U, 8U, 6U, 1U, 4U, 2U};
    RangeQueryForTest sumRangeQuery(values, plusAccumulator);

    EXPECT_EQ(1U, sumRangeQuery.getValueOnInterval(0U, 0U));
    EXPECT_EQ(4U, sumRangeQuery.getValueOnInterval(0U, 1U));
    EXPECT_EQ(8U, sumRangeQuery.getValueOnInterval(0U, 2U));
    EXPECT_EQ(16U, sumRangeQuery.getValueOnInterval(0U, 3U));
    EXPECT_EQ(22U, sumRangeQuery.getValueOnInterval(0U, 4U));
    EXPECT_EQ(23U, sumRangeQuery.getValueOnInterval(0U, 5U));
    EXPECT_EQ(27U, sumRangeQuery.getValueOnInterval(0U, 6U));
    EXPECT_EQ(29U, sumRangeQuery.getValueOnInterval(0U, 7U));
    EXPECT_EQ(0U, sumRangeQuery.getValueOnInterval(0U, 8U));
    EXPECT_EQ(26U, sumRangeQuery.getValueOnInterval(1U, 6U));
    EXPECT_EQ(19U, sumRangeQuery.getValueOnInterval(2U, 5U));
    EXPECT_EQ(14U, sumRangeQuery.getValueOnInterval(3U, 4U));
    EXPECT_EQ(6U, sumRangeQuery.getValueOnInterval(4U, 4U));
}

TEST(RangeQueryWithSegmentTreeTest, ChangeValueAtIndexWithSumWorksOnExample1)
{
    ValuesForTest values{1U, 3U, 4U, 8U, 6U, 1U, 4U, 2U};
    RangeQueryForTest sumRangeQuery(values, plusAccumulator);

    sumRangeQuery.changeValueAtIndex(3U, 3U);

    EXPECT_EQ(1U, sumRangeQuery.getValueOnInterval(0U, 0U));
    EXPECT_EQ(4U, sumRangeQuery.getValueOnInterval(0U, 1U));
    EXPECT_EQ(8U, sumRangeQuery.getValueOnInterval(0U, 2U));
    EXPECT_EQ(11U, sumRangeQuery.getValueOnInterval(0U, 3U));
    EXPECT_EQ(17U, sumRangeQuery.getValueOnInterval(0U, 4U));
    EXPECT_EQ(18U, sumRangeQuery.getValueOnInterval(0U, 5U));
    EXPECT_EQ(22U, sumRangeQuery.getValueOnInterval(0U, 6U));
    EXPECT_EQ(24U, sumRangeQuery.getValueOnInterval(0U, 7U));
    EXPECT_EQ(0U, sumRangeQuery.getValueOnInterval(0U, 8U));
    EXPECT_EQ(21U, sumRangeQuery.getValueOnInterval(1U, 6U));
    EXPECT_EQ(14U, sumRangeQuery.getValueOnInterval(2U, 5U));
    EXPECT_EQ(9U, sumRangeQuery.getValueOnInterval(3U, 4U));
    EXPECT_EQ(6U, sumRangeQuery.getValueOnInterval(4U, 4U));
}

}

}