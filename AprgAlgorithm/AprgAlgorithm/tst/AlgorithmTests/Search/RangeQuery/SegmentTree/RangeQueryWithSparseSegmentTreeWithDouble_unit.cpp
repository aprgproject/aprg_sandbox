#include <Algorithm/Search/RangeQuery/SegmentTree/RangeQueryWithSparseSegmentTree.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using ValueForTest = double;
using RangeQueryForTest = RangeQueryWithSparseSegmentTree<ValueForTest>;
RangeQueryForTest::Function multipliesFunction = multiplies<>();
}  // namespace

TEST(RangeQueryWithSparseSegmentTreeTest, GetValueOnIntervalWithGeometricSumWorksWithEmptySetOfValues) {
    RangeQueryForTest geometricSumRangeQuery(0, 1, multipliesFunction);

    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnInterval(0, 0));
}

TEST(RangeQueryWithSparseSegmentTreeTest, GetValueOnIntervalWithGeometricSumWorksOnExample1) {
    RangeQueryForTest geometricSumRangeQuery(9, 1, multipliesFunction);

    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getValueOnInterval(0, 0));
    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getValueOnInterval(0, 1));
    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getValueOnInterval(0, 2));
    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getValueOnInterval(0, 3));
    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getValueOnInterval(0, 4));
    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getValueOnInterval(0, 5));
    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getValueOnInterval(0, 6));
    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getValueOnInterval(0, 7));
    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getValueOnInterval(0, 8));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnInterval(0, 9));
    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getValueOnInterval(1, 6));
    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getValueOnInterval(2, 5));
    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getValueOnInterval(3, 4));
    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getValueOnInterval(4, 4));
}

TEST(RangeQueryWithSparseSegmentTreeTest, SetValueAtIndexWithGeometricSumWorksWithEmptySetOfValues) {
    RangeQueryForTest geometricSumRangeQuery(0, 1, multipliesFunction);

    geometricSumRangeQuery.setValueOnIndex(0, 10);

    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnInterval(0, 0));
}

TEST(RangeQueryWithSparseSegmentTreeTest, SetValueAtIndexWithGeometricSumWorksOnExample1) {
    RangeQueryForTest geometricSumRangeQuery(9, 1, multipliesFunction);

    geometricSumRangeQuery.setValueOnIndex(3, 10);
    geometricSumRangeQuery.setValueOnIndex(4, 11);
    geometricSumRangeQuery.setValueOnIndex(5, 12);

    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getValueOnInterval(0, 0));
    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getValueOnInterval(0, 1));
    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getValueOnInterval(0, 2));
    EXPECT_DOUBLE_EQ(10, geometricSumRangeQuery.getValueOnInterval(0, 3));
    EXPECT_DOUBLE_EQ(110, geometricSumRangeQuery.getValueOnInterval(0, 4));
    EXPECT_DOUBLE_EQ(1320, geometricSumRangeQuery.getValueOnInterval(0, 5));
    EXPECT_DOUBLE_EQ(1320, geometricSumRangeQuery.getValueOnInterval(0, 6));
    EXPECT_DOUBLE_EQ(1320, geometricSumRangeQuery.getValueOnInterval(0, 7));
    EXPECT_DOUBLE_EQ(1320, geometricSumRangeQuery.getValueOnInterval(0, 8));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnInterval(0, 9));
    EXPECT_DOUBLE_EQ(1320, geometricSumRangeQuery.getValueOnInterval(1, 6));
    EXPECT_DOUBLE_EQ(1320, geometricSumRangeQuery.getValueOnInterval(2, 5));
    EXPECT_DOUBLE_EQ(110, geometricSumRangeQuery.getValueOnInterval(3, 4));
    EXPECT_DOUBLE_EQ(11, geometricSumRangeQuery.getValueOnInterval(4, 4));
}

}  // namespace algorithm

}  // namespace alba
