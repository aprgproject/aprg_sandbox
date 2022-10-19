#include <Algorithm/Search/RangeQuery/SegmentTree/RangeQueryWithSparseSegmentTree.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using ValueForTest = double;
using RangeQueryForTest = RangeQueryWithSparseSegmentTree<ValueForTest>;
RangeQueryForTest::Function multipliesFunction = multiplies<ValueForTest>();
}

TEST(RangeQueryWithSparseSegmentTreeTest, GetValueOnIntervalWithGeometricSumWorksWithEmptySetOfValues)
{
    RangeQueryForTest geometricSumRangeQuery(0U, 1U, multipliesFunction);

    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnInterval(0U, 0U));
}

TEST(RangeQueryWithSparseSegmentTreeTest, GetValueOnIntervalWithGeometricSumWorksOnExample1)
{
    RangeQueryForTest geometricSumRangeQuery(9U, 1U, multipliesFunction);

    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getValueOnInterval(0U, 0U));
    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getValueOnInterval(0U, 1U));
    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getValueOnInterval(0U, 2U));
    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getValueOnInterval(0U, 3U));
    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getValueOnInterval(0U, 4U));
    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getValueOnInterval(0U, 5U));
    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getValueOnInterval(0U, 6U));
    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getValueOnInterval(0U, 7U));
    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getValueOnInterval(0U, 8U));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnInterval(0U, 9U));
    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getValueOnInterval(1U, 6U));
    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getValueOnInterval(2U, 5U));
    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getValueOnInterval(3U, 4U));
    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getValueOnInterval(4U, 4U));
}

TEST(RangeQueryWithSparseSegmentTreeTest, SetValueAtIndexWithGeometricSumWorksWithEmptySetOfValues)
{
    RangeQueryForTest geometricSumRangeQuery(0U, 1U, multipliesFunction);

    geometricSumRangeQuery.setValueOnIndex(0U, 10U);

    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnInterval(0U, 0U));
}

TEST(RangeQueryWithSparseSegmentTreeTest, SetValueAtIndexWithGeometricSumWorksOnExample1)
{
    RangeQueryForTest geometricSumRangeQuery(9U, 1U, multipliesFunction);

    geometricSumRangeQuery.setValueOnIndex(3U, 10U);
    geometricSumRangeQuery.setValueOnIndex(4U, 11U);
    geometricSumRangeQuery.setValueOnIndex(5U, 12U);

    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getValueOnInterval(0U, 0U));
    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getValueOnInterval(0U, 1U));
    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getValueOnInterval(0U, 2U));
    EXPECT_DOUBLE_EQ(10, geometricSumRangeQuery.getValueOnInterval(0U, 3U));
    EXPECT_DOUBLE_EQ(110, geometricSumRangeQuery.getValueOnInterval(0U, 4U));
    EXPECT_DOUBLE_EQ(1320, geometricSumRangeQuery.getValueOnInterval(0U, 5U));
    EXPECT_DOUBLE_EQ(1320, geometricSumRangeQuery.getValueOnInterval(0U, 6U));
    EXPECT_DOUBLE_EQ(1320, geometricSumRangeQuery.getValueOnInterval(0U, 7U));
    EXPECT_DOUBLE_EQ(1320, geometricSumRangeQuery.getValueOnInterval(0U, 8U));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnInterval(0U, 9U));
    EXPECT_DOUBLE_EQ(1320, geometricSumRangeQuery.getValueOnInterval(1U, 6U));
    EXPECT_DOUBLE_EQ(1320, geometricSumRangeQuery.getValueOnInterval(2U, 5U));
    EXPECT_DOUBLE_EQ(110, geometricSumRangeQuery.getValueOnInterval(3U, 4U));
    EXPECT_DOUBLE_EQ(11, geometricSumRangeQuery.getValueOnInterval(4U, 4U));
}

}

}
