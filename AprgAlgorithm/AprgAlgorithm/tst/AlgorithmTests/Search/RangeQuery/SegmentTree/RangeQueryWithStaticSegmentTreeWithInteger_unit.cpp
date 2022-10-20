#include <Algorithm/Search/RangeQuery/SegmentTree/RangeQueryWithStaticSegmentTree.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using ValuesForTest = vector<unsigned int>;
using RangeQueryForTest = RangeQueryWithStaticSegmentTree<ValuesForTest>;
using ValueForTest = RangeQueryForTest::Value;

RangeQueryForTest::Function minimumFunction = [](ValueForTest const& value1, ValueForTest const& value2)
{
    return min(value1, value2);
};

RangeQueryForTest::Function maximumFunction = [](ValueForTest const& value1, ValueForTest const& value2)
{
    return max(value1, value2);
};

RangeQueryForTest::Function plusFunction = plus<ValueForTest>();
}

TEST(RangeQueryWithStaticSegmentTreeTest, GetStartOfChildrenWithMinimumWorksOnExample1)
{
    ValuesForTest values{5U, 9U, 4U, 8U, 6U, 1U, 4U, 2U, 0U};
    RangeQueryForTest minimumRangeQuery(values, minimumFunction);

    EXPECT_EQ(15U, minimumRangeQuery.getStartOfChildren());
}

TEST(RangeQueryWithStaticSegmentTreeTest, GetTreeValuesWithMinimumWorksOnExample1)
{
    ValuesForTest values{5U, 9U, 4U, 8U, 6U, 1U, 4U, 2U, 0U};
    RangeQueryForTest minimumRangeQuery(values, minimumFunction);

    ValuesForTest expectedTreeValues{0U, 1U, 0U, 4U, 1U, 0U, 0U, 5U, 4U, 1U, 2U, 0U, 0U, 0U, 0U, 5U, 9U, 4U, 8U, 6U, 1U, 4U, 2U, 0U};
    EXPECT_EQ(expectedTreeValues, minimumRangeQuery.getTreeValues());
}

TEST(RangeQueryWithStaticSegmentTreeTest, GetValueOnIntervalWithMinimumWorksWithEmptySetOfValues)
{
    ValuesForTest values;
    RangeQueryForTest minimumRangeQuery(values, minimumFunction);

    EXPECT_EQ(0U, minimumRangeQuery.getValueOnInterval(0U, 0U));
}

TEST(RangeQueryWithStaticSegmentTreeTest, GetValueOnIntervalWithMinimumWorksOnExample1)
{
    ValuesForTest values{5U, 9U, 4U, 8U, 6U, 1U, 4U, 2U, 0U};
    RangeQueryForTest minimumRangeQuery(values, minimumFunction);

    EXPECT_EQ(5U, minimumRangeQuery.getValueOnInterval(0U, 0U));
    EXPECT_EQ(5U, minimumRangeQuery.getValueOnInterval(0U, 1U));
    EXPECT_EQ(4U, minimumRangeQuery.getValueOnInterval(0U, 2U));
    EXPECT_EQ(4U, minimumRangeQuery.getValueOnInterval(0U, 3U));
    EXPECT_EQ(4U, minimumRangeQuery.getValueOnInterval(0U, 4U));
    EXPECT_EQ(1U, minimumRangeQuery.getValueOnInterval(0U, 5U));
    EXPECT_EQ(1U, minimumRangeQuery.getValueOnInterval(0U, 6U));
    EXPECT_EQ(1U, minimumRangeQuery.getValueOnInterval(0U, 7U));
    EXPECT_EQ(0U, minimumRangeQuery.getValueOnInterval(0U, 8U));
    EXPECT_EQ(0U, minimumRangeQuery.getValueOnInterval(0U, 9U));
    EXPECT_EQ(1U, minimumRangeQuery.getValueOnInterval(3U, 6U));
    EXPECT_EQ(4U, minimumRangeQuery.getValueOnInterval(2U, 4U));
}

TEST(RangeQueryWithStaticSegmentTreeTest, GetValueOnIntervalWithMaximumWorksOnExample1)
{
    ValuesForTest values{5U, 9U, 4U, 8U, 6U, 1U, 4U, 2U, 10U};
    RangeQueryForTest maximumRangeQuery(values, maximumFunction);

    EXPECT_EQ(5U, maximumRangeQuery.getValueOnInterval(0U, 0U));
    EXPECT_EQ(9U, maximumRangeQuery.getValueOnInterval(0U, 1U));
    EXPECT_EQ(9U, maximumRangeQuery.getValueOnInterval(0U, 2U));
    EXPECT_EQ(9U, maximumRangeQuery.getValueOnInterval(0U, 3U));
    EXPECT_EQ(9U, maximumRangeQuery.getValueOnInterval(0U, 4U));
    EXPECT_EQ(9U, maximumRangeQuery.getValueOnInterval(0U, 5U));
    EXPECT_EQ(9U, maximumRangeQuery.getValueOnInterval(0U, 6U));
    EXPECT_EQ(9U, maximumRangeQuery.getValueOnInterval(0U, 7U));
    EXPECT_EQ(10U, maximumRangeQuery.getValueOnInterval(0U, 8U));
    EXPECT_EQ(0U, maximumRangeQuery.getValueOnInterval(0U, 9U));
    EXPECT_EQ(8U, maximumRangeQuery.getValueOnInterval(3U, 6U));
    EXPECT_EQ(8U, maximumRangeQuery.getValueOnInterval(2U, 4U));
}

TEST(RangeQueryWithStaticSegmentTreeTest, GetValueOnIntervalWithSumWorksOnExample1)
{
    ValuesForTest values{1U, 3U, 4U, 8U, 6U, 1U, 4U, 2U, 9U};
    RangeQueryForTest sumRangeQuery(values, plusFunction);

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

TEST(RangeQueryWithStaticSegmentTreeTest, GetValueOnIntervalFromTopToBottomWithMinimumWorksOnExample1)
{
    ValuesForTest values{5U, 9U, 4U, 8U, 6U, 1U, 4U, 2U, 0U};
    RangeQueryForTest minimumRangeQuery(values, minimumFunction);

    EXPECT_EQ(5U, minimumRangeQuery.getValueOnIntervalFromTopToBottom(0U, 0U));
    EXPECT_EQ(5U, minimumRangeQuery.getValueOnIntervalFromTopToBottom(0U, 1U));
    EXPECT_EQ(4U, minimumRangeQuery.getValueOnIntervalFromTopToBottom(0U, 2U));
    EXPECT_EQ(4U, minimumRangeQuery.getValueOnIntervalFromTopToBottom(0U, 3U));
    EXPECT_EQ(4U, minimumRangeQuery.getValueOnIntervalFromTopToBottom(0U, 4U));
    EXPECT_EQ(1U, minimumRangeQuery.getValueOnIntervalFromTopToBottom(0U, 5U));
    EXPECT_EQ(1U, minimumRangeQuery.getValueOnIntervalFromTopToBottom(0U, 6U));
    EXPECT_EQ(1U, minimumRangeQuery.getValueOnIntervalFromTopToBottom(0U, 7U));
    EXPECT_EQ(0U, minimumRangeQuery.getValueOnIntervalFromTopToBottom(0U, 8U));
    EXPECT_EQ(0U, minimumRangeQuery.getValueOnIntervalFromTopToBottom(0U, 9U));
    EXPECT_EQ(1U, minimumRangeQuery.getValueOnIntervalFromTopToBottom(3U, 6U));
    EXPECT_EQ(4U, minimumRangeQuery.getValueOnIntervalFromTopToBottom(2U, 4U));
}

TEST(RangeQueryWithStaticSegmentTreeTest, GetValueOnIntervalFromTopToBottomWithMaximumWorksOnExample1)
{
    ValuesForTest values{5U, 9U, 4U, 8U, 6U, 1U, 4U, 2U, 10U};
    RangeQueryForTest maximumRangeQuery(values, maximumFunction);

    EXPECT_EQ(5U, maximumRangeQuery.getValueOnIntervalFromTopToBottom(0U, 0U));
    EXPECT_EQ(9U, maximumRangeQuery.getValueOnIntervalFromTopToBottom(0U, 1U));
    EXPECT_EQ(9U, maximumRangeQuery.getValueOnIntervalFromTopToBottom(0U, 2U));
    EXPECT_EQ(9U, maximumRangeQuery.getValueOnIntervalFromTopToBottom(0U, 3U));
    EXPECT_EQ(9U, maximumRangeQuery.getValueOnIntervalFromTopToBottom(0U, 4U));
    EXPECT_EQ(9U, maximumRangeQuery.getValueOnIntervalFromTopToBottom(0U, 5U));
    EXPECT_EQ(9U, maximumRangeQuery.getValueOnIntervalFromTopToBottom(0U, 6U));
    EXPECT_EQ(9U, maximumRangeQuery.getValueOnIntervalFromTopToBottom(0U, 7U));
    EXPECT_EQ(10U, maximumRangeQuery.getValueOnIntervalFromTopToBottom(0U, 8U));
    EXPECT_EQ(0U, maximumRangeQuery.getValueOnIntervalFromTopToBottom(0U, 9U));
    EXPECT_EQ(8U, maximumRangeQuery.getValueOnIntervalFromTopToBottom(3U, 6U));
    EXPECT_EQ(8U, maximumRangeQuery.getValueOnIntervalFromTopToBottom(2U, 4U));
}

TEST(RangeQueryWithStaticSegmentTreeTest, GetValueOnIntervalFromTopToBottomWithSumWorksOnExample1)
{
    ValuesForTest values{1U, 3U, 4U, 8U, 6U, 1U, 4U, 2U, 9U};
    RangeQueryForTest sumRangeQuery(values, plusFunction);

    EXPECT_EQ(1U, sumRangeQuery.getValueOnIntervalFromTopToBottom(0U, 0U));
    EXPECT_EQ(4U, sumRangeQuery.getValueOnIntervalFromTopToBottom(0U, 1U));
    EXPECT_EQ(8U, sumRangeQuery.getValueOnIntervalFromTopToBottom(0U, 2U));
    EXPECT_EQ(16U, sumRangeQuery.getValueOnIntervalFromTopToBottom(0U, 3U));
    EXPECT_EQ(22U, sumRangeQuery.getValueOnIntervalFromTopToBottom(0U, 4U));
    EXPECT_EQ(23U, sumRangeQuery.getValueOnIntervalFromTopToBottom(0U, 5U));
    EXPECT_EQ(27U, sumRangeQuery.getValueOnIntervalFromTopToBottom(0U, 6U));
    EXPECT_EQ(29U, sumRangeQuery.getValueOnIntervalFromTopToBottom(0U, 7U));
    EXPECT_EQ(38U, sumRangeQuery.getValueOnIntervalFromTopToBottom(0U, 8U));
    EXPECT_EQ(0U, sumRangeQuery.getValueOnIntervalFromTopToBottom(0U, 9U));
    EXPECT_EQ(26U, sumRangeQuery.getValueOnIntervalFromTopToBottom(1U, 6U));
    EXPECT_EQ(19U, sumRangeQuery.getValueOnIntervalFromTopToBottom(2U, 5U));
    EXPECT_EQ(14U, sumRangeQuery.getValueOnIntervalFromTopToBottom(3U, 4U));
    EXPECT_EQ(6U, sumRangeQuery.getValueOnIntervalFromTopToBottom(4U, 4U));
}

TEST(RangeQueryWithStaticSegmentTreeTest, ChangeValueAtIndexWithSumWorksWithEmptySetOfValues)
{
    ValuesForTest values;
    RangeQueryForTest sumRangeQuery(values, plusFunction);

    sumRangeQuery.changeValueAtIndex(0U, 0U);

    EXPECT_EQ(0U, sumRangeQuery.getValueOnInterval(0U, 0U));
}

TEST(RangeQueryWithStaticSegmentTreeTest, ChangeValueAtIndexWithSumWorksWithOneValue)
{
    ValuesForTest values{5};
    RangeQueryForTest sumRangeQuery(values, plusFunction);

    sumRangeQuery.changeValueAtIndex(0U, 3U);

    EXPECT_EQ(3U, sumRangeQuery.getValueOnInterval(0U, 0U));
}

TEST(RangeQueryWithStaticSegmentTreeTest, ChangeValueAtIndexWithSumWorksOnExample1)
{
    ValuesForTest values{1U, 3U, 4U, 8U, 6U, 1U, 4U, 2U, 9U};
    RangeQueryForTest sumRangeQuery(values, plusFunction);

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
