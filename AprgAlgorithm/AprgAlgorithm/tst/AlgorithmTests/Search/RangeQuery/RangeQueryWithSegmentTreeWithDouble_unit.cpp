#include <Algorithm/Search/RangeQuery/RangeQueryWithSegmentTree.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using ValuesForTest = vector<double>;
using RangeQueryForTest = RangeQueryWithSegmentTree<ValuesForTest>;
using ValueForTest = RangeQueryForTest::Value;

RangeQueryForTest::Function multipliesFunction = [](ValueForTest const& value1, ValueForTest const& value2)
{
    return multiplies<ValueForTest>()(value1, value2);
};
}

TEST(RangeQueryWithSegmentTreeTest, GetValueOnIntervalWithGeometricSumWorksWithEmptySetOfValues)
{
    ValuesForTest values;
    RangeQueryForTest geometricSumRangeQuery(values, multipliesFunction);

    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnInterval(0U, 0U));
}

TEST(RangeQueryWithSegmentTreeTest, GetValueOnIntervalWithGeometricSumWorksOnExample1)
{
    ValuesForTest values{1, 3, 4, 8, 6, 1, 4, 2, 9};
    RangeQueryForTest geometricSumRangeQuery(values, multipliesFunction);

    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getValueOnInterval(0U, 0U));
    EXPECT_DOUBLE_EQ(3, geometricSumRangeQuery.getValueOnInterval(0U, 1U));
    EXPECT_DOUBLE_EQ(12, geometricSumRangeQuery.getValueOnInterval(0U, 2U));
    EXPECT_DOUBLE_EQ(96, geometricSumRangeQuery.getValueOnInterval(0U, 3U));
    EXPECT_DOUBLE_EQ(576, geometricSumRangeQuery.getValueOnInterval(0U, 4U));
    EXPECT_DOUBLE_EQ(576, geometricSumRangeQuery.getValueOnInterval(0U, 5U));
    EXPECT_DOUBLE_EQ(2304, geometricSumRangeQuery.getValueOnInterval(0U, 6U));
    EXPECT_DOUBLE_EQ(4608, geometricSumRangeQuery.getValueOnInterval(0U, 7U));
    EXPECT_DOUBLE_EQ(41472, geometricSumRangeQuery.getValueOnInterval(0U, 8U));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnInterval(0U, 9U));
    EXPECT_DOUBLE_EQ(2304, geometricSumRangeQuery.getValueOnInterval(1U, 6U));
    EXPECT_DOUBLE_EQ(192, geometricSumRangeQuery.getValueOnInterval(2U, 5U));
    EXPECT_DOUBLE_EQ(48, geometricSumRangeQuery.getValueOnInterval(3U, 4U));
    EXPECT_DOUBLE_EQ(6, geometricSumRangeQuery.getValueOnInterval(4U, 4U));
}

TEST(RangeQueryWithSegmentTreeTest, ChangeValueAtIndexWithGeometricSumWorksWithEmptySetOfValues)
{
    ValuesForTest values;
    RangeQueryForTest geometricSumRangeQuery(values, multipliesFunction);

    geometricSumRangeQuery.changeValueAtIndex(3U, 3);

    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnInterval(0U, 0U));
}

TEST(RangeQueryWithSegmentTreeTest, ChangeValueAtIndexWithGeometricSumWorksOnExample1)
{
    ValuesForTest values{1, 3, 4, 8, 6, 1, 4, 2, 9};
    RangeQueryForTest geometricSumRangeQuery(values, multipliesFunction);

    geometricSumRangeQuery.changeValueAtIndex(3U, 3);

    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getValueOnInterval(0U, 0U));
    EXPECT_DOUBLE_EQ(3, geometricSumRangeQuery.getValueOnInterval(0U, 1U));
    EXPECT_DOUBLE_EQ(12, geometricSumRangeQuery.getValueOnInterval(0U, 2U));
    EXPECT_DOUBLE_EQ(36, geometricSumRangeQuery.getValueOnInterval(0U, 3U));
    EXPECT_DOUBLE_EQ(216, geometricSumRangeQuery.getValueOnInterval(0U, 4U));
    EXPECT_DOUBLE_EQ(216, geometricSumRangeQuery.getValueOnInterval(0U, 5U));
    EXPECT_DOUBLE_EQ(864, geometricSumRangeQuery.getValueOnInterval(0U, 6U));
    EXPECT_DOUBLE_EQ(1728, geometricSumRangeQuery.getValueOnInterval(0U, 7U));
    EXPECT_DOUBLE_EQ(15552, geometricSumRangeQuery.getValueOnInterval(0U, 8U));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnInterval(0U, 9U));
    EXPECT_DOUBLE_EQ(864, geometricSumRangeQuery.getValueOnInterval(1U, 6U));
    EXPECT_DOUBLE_EQ(72, geometricSumRangeQuery.getValueOnInterval(2U, 5U));
    EXPECT_DOUBLE_EQ(18, geometricSumRangeQuery.getValueOnInterval(3U, 4U));
    EXPECT_DOUBLE_EQ(6, geometricSumRangeQuery.getValueOnInterval(4U, 4U));
}

}

}
