#include <Algorithm/Search/RangeQuery/SegmentTree/RangeQueryWithSparseSegmentTree.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using ValueForTest = unsigned int;
using RangeQueryForTest = RangeQueryWithSparseSegmentTree<ValueForTest>;

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

TEST(RangeQueryWithSparseSegmentTreeTest, GetValueOnIntervalWithMinimumWorksWithZeroNumberOfValues)
{
    RangeQueryForTest minimumRangeQuery(0U, 0U, minimumFunction);

    EXPECT_EQ(0U, minimumRangeQuery.getValueOnInterval(0U, 0U));
}

TEST(RangeQueryWithSparseSegmentTreeTest, GetValueOnIntervalWithMinimumWorksOnExample1)
{
    RangeQueryForTest minimumRangeQuery(9U, 0U, minimumFunction);

    EXPECT_EQ(0U, minimumRangeQuery.getValueOnInterval(0U, 0U));
    EXPECT_EQ(0U, minimumRangeQuery.getValueOnInterval(0U, 1U));
    EXPECT_EQ(0U, minimumRangeQuery.getValueOnInterval(0U, 2U));
    EXPECT_EQ(0U, minimumRangeQuery.getValueOnInterval(0U, 3U));
    EXPECT_EQ(0U, minimumRangeQuery.getValueOnInterval(0U, 4U));
    EXPECT_EQ(0U, minimumRangeQuery.getValueOnInterval(0U, 5U));
    EXPECT_EQ(0U, minimumRangeQuery.getValueOnInterval(0U, 6U));
    EXPECT_EQ(0U, minimumRangeQuery.getValueOnInterval(0U, 7U));
    EXPECT_EQ(0U, minimumRangeQuery.getValueOnInterval(0U, 8U));
    EXPECT_EQ(0U, minimumRangeQuery.getValueOnInterval(0U, 9U));
    EXPECT_EQ(0U, minimumRangeQuery.getValueOnInterval(3U, 6U));
    EXPECT_EQ(0U, minimumRangeQuery.getValueOnInterval(2U, 4U));
}

TEST(RangeQueryWithSparseSegmentTreeTest, GetValueOnIntervalWithMaximumWorksOnExample1)
{
    RangeQueryForTest maximumRangeQuery(9U, 0U, maximumFunction);

    EXPECT_EQ(0U, maximumRangeQuery.getValueOnInterval(0U, 0U));
    EXPECT_EQ(0U, maximumRangeQuery.getValueOnInterval(0U, 1U));
    EXPECT_EQ(0U, maximumRangeQuery.getValueOnInterval(0U, 2U));
    EXPECT_EQ(0U, maximumRangeQuery.getValueOnInterval(0U, 3U));
    EXPECT_EQ(0U, maximumRangeQuery.getValueOnInterval(0U, 4U));
    EXPECT_EQ(0U, maximumRangeQuery.getValueOnInterval(0U, 5U));
    EXPECT_EQ(0U, maximumRangeQuery.getValueOnInterval(0U, 6U));
    EXPECT_EQ(0U, maximumRangeQuery.getValueOnInterval(0U, 7U));
    EXPECT_EQ(0U, maximumRangeQuery.getValueOnInterval(0U, 8U));
    EXPECT_EQ(0U, maximumRangeQuery.getValueOnInterval(0U, 9U));
    EXPECT_EQ(0U, maximumRangeQuery.getValueOnInterval(3U, 6U));
    EXPECT_EQ(0U, maximumRangeQuery.getValueOnInterval(2U, 4U));
}

TEST(RangeQueryWithSparseSegmentTreeTest, GetValueOnIntervalWithSumWorksOnExample1)
{
    RangeQueryForTest sumRangeQuery(9U, 0U, plusFunction);

    EXPECT_EQ(0U, sumRangeQuery.getValueOnInterval(0U, 0U));
    EXPECT_EQ(0U, sumRangeQuery.getValueOnInterval(0U, 1U));
    EXPECT_EQ(0U, sumRangeQuery.getValueOnInterval(0U, 2U));
    EXPECT_EQ(0U, sumRangeQuery.getValueOnInterval(0U, 3U));
    EXPECT_EQ(0U, sumRangeQuery.getValueOnInterval(0U, 4U));
    EXPECT_EQ(0U, sumRangeQuery.getValueOnInterval(0U, 5U));
    EXPECT_EQ(0U, sumRangeQuery.getValueOnInterval(0U, 6U));
    EXPECT_EQ(0U, sumRangeQuery.getValueOnInterval(0U, 7U));
    EXPECT_EQ(0U, sumRangeQuery.getValueOnInterval(0U, 8U));
    EXPECT_EQ(0U, sumRangeQuery.getValueOnInterval(0U, 9U));
    EXPECT_EQ(0U, sumRangeQuery.getValueOnInterval(1U, 6U));
    EXPECT_EQ(0U, sumRangeQuery.getValueOnInterval(2U, 5U));
    EXPECT_EQ(0U, sumRangeQuery.getValueOnInterval(3U, 4U));
    EXPECT_EQ(0U, sumRangeQuery.getValueOnInterval(4U, 4U));
}

TEST(RangeQueryWithSparseSegmentTreeTest, SetValueOnIndexWithMinimumWorksWithZeroNumberOfValues)
{
    RangeQueryForTest minimumRangeQuery(0U, 0U, minimumFunction);

    minimumRangeQuery.setValueOnIndex(0U, 10U);

    EXPECT_EQ(0U, minimumRangeQuery.getValueOnInterval(0U, 0U));
}

TEST(RangeQueryWithSparseSegmentTreeTest, SetValueOnIndexWithMinimumWorksWithOneValue)
{
    RangeQueryForTest minimumRangeQuery(1U, 0U, minimumFunction);

    minimumRangeQuery.setValueOnIndex(0U, 10U);

    EXPECT_EQ(10U, minimumRangeQuery.getValueOnInterval(0U, 0U));
}

TEST(RangeQueryWithSparseSegmentTreeTest, SetValueOnIndexWithMinimumWorksOnExample1)
{
    RangeQueryForTest minimumRangeQuery(9U, 0U, minimumFunction);

    minimumRangeQuery.setValueOnIndex(3U, 10U);
    minimumRangeQuery.setValueOnIndex(4U, 11U);
    minimumRangeQuery.setValueOnIndex(5U, 12U);

    EXPECT_EQ(0U, minimumRangeQuery.getValueOnInterval(0U, 0U));
    EXPECT_EQ(0U, minimumRangeQuery.getValueOnInterval(0U, 1U));
    EXPECT_EQ(0U, minimumRangeQuery.getValueOnInterval(0U, 2U));
    EXPECT_EQ(0U, minimumRangeQuery.getValueOnInterval(0U, 3U));
    EXPECT_EQ(0U, minimumRangeQuery.getValueOnInterval(0U, 4U));
    EXPECT_EQ(0U, minimumRangeQuery.getValueOnInterval(0U, 5U));
    EXPECT_EQ(0U, minimumRangeQuery.getValueOnInterval(0U, 6U));
    EXPECT_EQ(0U, minimumRangeQuery.getValueOnInterval(0U, 7U));
    EXPECT_EQ(0U, minimumRangeQuery.getValueOnInterval(0U, 8U));
    EXPECT_EQ(0U, minimumRangeQuery.getValueOnInterval(0U, 9U));
    EXPECT_EQ(0U, minimumRangeQuery.getValueOnInterval(1U, 6U));
    EXPECT_EQ(0U, minimumRangeQuery.getValueOnInterval(2U, 5U));
    EXPECT_EQ(10U, minimumRangeQuery.getValueOnInterval(3U, 4U));
    EXPECT_EQ(11U, minimumRangeQuery.getValueOnInterval(4U, 4U));
}

TEST(RangeQueryWithSparseSegmentTreeTest, SetValueOnIndexWithMaximumWorksOnExample1)
{
    RangeQueryForTest maximumRangeQuery(9U, 0U, maximumFunction);

    maximumRangeQuery.setValueOnIndex(3U, 10U);
    maximumRangeQuery.setValueOnIndex(4U, 11U);
    maximumRangeQuery.setValueOnIndex(5U, 12U);

    EXPECT_EQ(0U, maximumRangeQuery.getValueOnInterval(0U, 0U));
    EXPECT_EQ(0U, maximumRangeQuery.getValueOnInterval(0U, 1U));
    EXPECT_EQ(0U, maximumRangeQuery.getValueOnInterval(0U, 2U));
    EXPECT_EQ(10U, maximumRangeQuery.getValueOnInterval(0U, 3U));
    EXPECT_EQ(11U, maximumRangeQuery.getValueOnInterval(0U, 4U));
    EXPECT_EQ(12U, maximumRangeQuery.getValueOnInterval(0U, 5U));
    EXPECT_EQ(12U, maximumRangeQuery.getValueOnInterval(0U, 6U));
    EXPECT_EQ(12U, maximumRangeQuery.getValueOnInterval(0U, 7U));
    EXPECT_EQ(12U, maximumRangeQuery.getValueOnInterval(0U, 8U));
    EXPECT_EQ(0U, maximumRangeQuery.getValueOnInterval(0U, 9U));
    EXPECT_EQ(12U, maximumRangeQuery.getValueOnInterval(1U, 6U));
    EXPECT_EQ(12U, maximumRangeQuery.getValueOnInterval(2U, 5U));
    EXPECT_EQ(11U, maximumRangeQuery.getValueOnInterval(3U, 4U));
    EXPECT_EQ(11U, maximumRangeQuery.getValueOnInterval(4U, 4U));
}

TEST(RangeQueryWithSparseSegmentTreeTest, SetValueOnIndexWithSumWorksOnExample1)
{
    RangeQueryForTest sumRangeQuery(9U, 0U, plusFunction);

    sumRangeQuery.setValueOnIndex(3U, 10U);
    sumRangeQuery.setValueOnIndex(4U, 11U);
    sumRangeQuery.setValueOnIndex(5U, 12U);

    EXPECT_EQ(0U, sumRangeQuery.getValueOnInterval(0U, 0U));
    EXPECT_EQ(0U, sumRangeQuery.getValueOnInterval(0U, 1U));
    EXPECT_EQ(0U, sumRangeQuery.getValueOnInterval(0U, 2U));
    EXPECT_EQ(10U, sumRangeQuery.getValueOnInterval(0U, 3U));
    EXPECT_EQ(21U, sumRangeQuery.getValueOnInterval(0U, 4U));
    EXPECT_EQ(33U, sumRangeQuery.getValueOnInterval(0U, 5U));
    EXPECT_EQ(33U, sumRangeQuery.getValueOnInterval(0U, 6U));
    EXPECT_EQ(33U, sumRangeQuery.getValueOnInterval(0U, 7U));
    EXPECT_EQ(33U, sumRangeQuery.getValueOnInterval(0U, 8U));
    EXPECT_EQ(0U, sumRangeQuery.getValueOnInterval(0U, 9U));
    EXPECT_EQ(33U, sumRangeQuery.getValueOnInterval(1U, 6U));
    EXPECT_EQ(33U, sumRangeQuery.getValueOnInterval(2U, 5U));
    EXPECT_EQ(21U, sumRangeQuery.getValueOnInterval(3U, 4U));
    EXPECT_EQ(11U, sumRangeQuery.getValueOnInterval(4U, 4U));
}

}

}
