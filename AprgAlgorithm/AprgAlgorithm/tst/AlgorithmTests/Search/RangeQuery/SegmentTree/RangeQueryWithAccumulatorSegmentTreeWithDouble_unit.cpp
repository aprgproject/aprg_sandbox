#include <Algorithm/Search/RangeQuery/SegmentTree/RangeQueryWithAccumulatorLazySegmentTree.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using ValuesForTest = vector<double>;
using RangeQueryForTest = RangeQueryWithAccumulatorLazySegmentTree<ValuesForTest>;
using ValueForTest = RangeQueryForTest::Value;
RangeQueryForTest::Function multipliesFunction = multiplies<>();
RangeQueryForTest::Function dividesFunction = divides<>();
}  // namespace

TEST(RangeQueryWithAccumulatorLazySegmentTreeTest, GetValueOnIntervalWithGeometricSumWorksWithEmptySetOfValues) {
    ValuesForTest values;
    RangeQueryForTest geometricSumRangeQuery(values, multipliesFunction, dividesFunction, 1);

    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnInterval(0, 0));
}

TEST(RangeQueryWithAccumulatorLazySegmentTreeTest, GetValueOnIntervalWithGeometricSumWorksOnExample1) {
    ValuesForTest values{1, 3, 4, 8, 6, 1, 4, 2, 9};
    RangeQueryForTest geometricSumRangeQuery(values, multipliesFunction, dividesFunction, 1);

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

TEST(RangeQueryWithAccumulatorLazySegmentTreeTest, IncreaseAtRangeWithGeometricSumWorksWithEmptySetOfValues) {
    ValuesForTest values;
    RangeQueryForTest geometricSumRangeQuery(values, multipliesFunction, dividesFunction, 1);

    geometricSumRangeQuery.increaseAtRange(0, 5, 4);

    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnInterval(0, 0));
}

TEST(RangeQueryWithAccumulatorLazySegmentTreeTest, IncreaseAtRangeWithGeometricSumWorksOnExample1) {
    ValuesForTest values{1, 3, 4, 8, 6, 1, 4, 2, 9};
    RangeQueryForTest geometricSumRangeQuery(values, multipliesFunction, dividesFunction, 1);

    geometricSumRangeQuery.increaseAtRange(0, 5, 4);

    // {4, 12, 16, 32, 24, 4, 4, 2, 9}
    EXPECT_DOUBLE_EQ(4, geometricSumRangeQuery.getValueOnInterval(0, 0));
    EXPECT_DOUBLE_EQ(48, geometricSumRangeQuery.getValueOnInterval(0, 1));
    EXPECT_DOUBLE_EQ(768, geometricSumRangeQuery.getValueOnInterval(0, 2));
    EXPECT_DOUBLE_EQ(24576, geometricSumRangeQuery.getValueOnInterval(0, 3));
    EXPECT_DOUBLE_EQ(589824, geometricSumRangeQuery.getValueOnInterval(0, 4));
    EXPECT_DOUBLE_EQ(2359296, geometricSumRangeQuery.getValueOnInterval(0, 5));
    EXPECT_DOUBLE_EQ(9437184, geometricSumRangeQuery.getValueOnInterval(0, 6));
    EXPECT_DOUBLE_EQ(18874368, geometricSumRangeQuery.getValueOnInterval(0, 7));
    EXPECT_DOUBLE_EQ(169869312, geometricSumRangeQuery.getValueOnInterval(0, 8));
    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnInterval(0, 9));
    EXPECT_DOUBLE_EQ(2359296, geometricSumRangeQuery.getValueOnInterval(1, 6));
    EXPECT_DOUBLE_EQ(49152, geometricSumRangeQuery.getValueOnInterval(2, 5));
    EXPECT_DOUBLE_EQ(768, geometricSumRangeQuery.getValueOnInterval(3, 4));
    EXPECT_DOUBLE_EQ(24, geometricSumRangeQuery.getValueOnInterval(4, 4));
}

TEST(RangeQueryWithAccumulatorLazySegmentTreeTest, ChangeValueAtIndexWithGeometricSumWorksWithEmptySetOfValues) {
    ValuesForTest values;
    RangeQueryForTest geometricSumRangeQuery(values, multipliesFunction, dividesFunction, 1);

    geometricSumRangeQuery.changeValueAtIndex(3, 3);

    EXPECT_DOUBLE_EQ(0, geometricSumRangeQuery.getValueOnInterval(0, 0));
}

TEST(RangeQueryWithAccumulatorLazySegmentTreeTest, ChangeValueAtIndexWithGeometricSumWorksOnExample1) {
    ValuesForTest values{1, 3, 4, 8, 6, 1, 4, 2, 9};
    RangeQueryForTest geometricSumRangeQuery(values, multipliesFunction, dividesFunction, 1);

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
