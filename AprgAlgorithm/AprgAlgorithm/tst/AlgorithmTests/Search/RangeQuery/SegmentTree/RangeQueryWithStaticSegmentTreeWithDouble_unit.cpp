#include <Algorithm/Search/RangeQuery/SegmentTree/RangeQueryWithStaticSegmentTree.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using ValuesForTest = vector<double>;
using RangeQueryForTest = RangeQueryWithStaticSegmentTree<ValuesForTest>;
using ValueForTest = RangeQueryForTest::Value;
RangeQueryForTest::Function multipliesFunction = multiplies<>();
}  // namespace

TEST(RangeQueryWithStaticSegmentTreeTest, GetValueOnIntervalWithGeometricSumWorksWithEmptySetOfValues) {
    ValuesForTest values;
    RangeQueryForTest geometricSumRangeQuery(values, multipliesFunction);

    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnInterval(0, 0));
}

TEST(RangeQueryWithStaticSegmentTreeTest, GetValueOnIntervalWithGeometricSumWorksOnExample1) {
    ValuesForTest values{1, 3, 4, 8, 6, 1, 4, 2, 9};
    RangeQueryForTest geometricSumRangeQuery(values, multipliesFunction);

    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getValueOnInterval(0, 0));
    EXPECT_DOUBLE_EQ(3, geometricSumRangeQuery.getValueOnInterval(0, 1));
    EXPECT_DOUBLE_EQ(12, geometricSumRangeQuery.getValueOnInterval(0, 2));
    EXPECT_DOUBLE_EQ(96, geometricSumRangeQuery.getValueOnInterval(0, 3));
    EXPECT_DOUBLE_EQ(576, geometricSumRangeQuery.getValueOnInterval(0, 4));
    EXPECT_DOUBLE_EQ(576, geometricSumRangeQuery.getValueOnInterval(0, 5));
    EXPECT_DOUBLE_EQ(2304, geometricSumRangeQuery.getValueOnInterval(0, 6));
    EXPECT_DOUBLE_EQ(4608, geometricSumRangeQuery.getValueOnInterval(0, 7));
    EXPECT_DOUBLE_EQ(41472, geometricSumRangeQuery.getValueOnInterval(0, 8));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnInterval(0, 9));
    EXPECT_DOUBLE_EQ(2304, geometricSumRangeQuery.getValueOnInterval(1, 6));
    EXPECT_DOUBLE_EQ(192, geometricSumRangeQuery.getValueOnInterval(2, 5));
    EXPECT_DOUBLE_EQ(48, geometricSumRangeQuery.getValueOnInterval(3, 4));
    EXPECT_DOUBLE_EQ(6, geometricSumRangeQuery.getValueOnInterval(4, 4));
}

TEST(RangeQueryWithStaticSegmentTreeTest, ChangeValueAtIndexWithGeometricSumWorksWithEmptySetOfValues) {
    ValuesForTest values;
    RangeQueryForTest geometricSumRangeQuery(values, multipliesFunction);

    geometricSumRangeQuery.changeValueAtIndex(3, 3);

    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnInterval(0, 0));
}

TEST(RangeQueryWithStaticSegmentTreeTest, ChangeValueAtIndexWithGeometricSumWorksOnExample1) {
    ValuesForTest values{1, 3, 4, 8, 6, 1, 4, 2, 9};
    RangeQueryForTest geometricSumRangeQuery(values, multipliesFunction);

    geometricSumRangeQuery.changeValueAtIndex(3, 3);

    EXPECT_DOUBLE_EQ(1, geometricSumRangeQuery.getValueOnInterval(0, 0));
    EXPECT_DOUBLE_EQ(3, geometricSumRangeQuery.getValueOnInterval(0, 1));
    EXPECT_DOUBLE_EQ(12, geometricSumRangeQuery.getValueOnInterval(0, 2));
    EXPECT_DOUBLE_EQ(36, geometricSumRangeQuery.getValueOnInterval(0, 3));
    EXPECT_DOUBLE_EQ(216, geometricSumRangeQuery.getValueOnInterval(0, 4));
    EXPECT_DOUBLE_EQ(216, geometricSumRangeQuery.getValueOnInterval(0, 5));
    EXPECT_DOUBLE_EQ(864, geometricSumRangeQuery.getValueOnInterval(0, 6));
    EXPECT_DOUBLE_EQ(1728, geometricSumRangeQuery.getValueOnInterval(0, 7));
    EXPECT_DOUBLE_EQ(15552, geometricSumRangeQuery.getValueOnInterval(0, 8));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnInterval(0, 9));
    EXPECT_DOUBLE_EQ(864, geometricSumRangeQuery.getValueOnInterval(1, 6));
    EXPECT_DOUBLE_EQ(72, geometricSumRangeQuery.getValueOnInterval(2, 5));
    EXPECT_DOUBLE_EQ(18, geometricSumRangeQuery.getValueOnInterval(3, 4));
    EXPECT_DOUBLE_EQ(6, geometricSumRangeQuery.getValueOnInterval(4, 4));
}

}  // namespace algorithm

}  // namespace alba
