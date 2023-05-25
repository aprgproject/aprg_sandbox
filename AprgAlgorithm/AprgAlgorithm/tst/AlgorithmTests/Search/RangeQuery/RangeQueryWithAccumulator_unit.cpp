#include <Algorithm/Search/RangeQuery/RangeQueryWithAccumulator.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using ValuesForTest = vector<int>;
using RangeQueryForTest = RangeQueryWithAccumulator<ValuesForTest>;
using ValueForTest = RangeQueryForTest::Value;
RangeQueryForTest::AccumulatorFunction plusAccumulator = plus<>();
RangeQueryForTest::AccumulatorFunction minusAccumulator = minus<>();
RangeQueryForTest::AccumulatorFunction multipliesAccumulator = multiplies<>();
RangeQueryForTest::AccumulatorFunction dividesAccumulator = divides<>();
}  // namespace

TEST(RangeQueryWithAccumulatorTest, GetAccumulatedValueOnIntervalWithSumWorksWithEmptySetOfValues) {
    ValuesForTest values;
    RangeQueryForTest sumRangeQuery(values, plusAccumulator, minusAccumulator);

    EXPECT_EQ(0, sumRangeQuery.getAccumulatedValueOnInterval(0, 0));
}

TEST(RangeQueryWithAccumulatorTest, GetAccumulatedValueOnIntervalWithSumWorksOnExample1) {
    ValuesForTest values{1, 3, 4, 8, 6, 1, 4, 2, 9};
    RangeQueryForTest sumRangeQuery(values, plusAccumulator, minusAccumulator);

    EXPECT_EQ(1, sumRangeQuery.getAccumulatedValueOnInterval(0, 0));
    EXPECT_EQ(4, sumRangeQuery.getAccumulatedValueOnInterval(0, 1));
    EXPECT_EQ(8, sumRangeQuery.getAccumulatedValueOnInterval(0, 2));
    EXPECT_EQ(16, sumRangeQuery.getAccumulatedValueOnInterval(0, 3));
    EXPECT_EQ(22, sumRangeQuery.getAccumulatedValueOnInterval(0, 4));
    EXPECT_EQ(23, sumRangeQuery.getAccumulatedValueOnInterval(0, 5));
    EXPECT_EQ(27, sumRangeQuery.getAccumulatedValueOnInterval(0, 6));
    EXPECT_EQ(29, sumRangeQuery.getAccumulatedValueOnInterval(0, 7));
    EXPECT_EQ(38, sumRangeQuery.getAccumulatedValueOnInterval(0, 8));
    EXPECT_EQ(0, sumRangeQuery.getAccumulatedValueOnInterval(0, 9));
    ;
    EXPECT_EQ(26, sumRangeQuery.getAccumulatedValueOnInterval(1, 6));
    EXPECT_EQ(19, sumRangeQuery.getAccumulatedValueOnInterval(2, 5));
    EXPECT_EQ(14, sumRangeQuery.getAccumulatedValueOnInterval(3, 4));
    EXPECT_EQ(6, sumRangeQuery.getAccumulatedValueOnInterval(4, 4));
}

TEST(RangeQueryWithAccumulatorTest, GetAccumulatedValueOnIntervalWithSumWorksOnExample2) {
    ValuesForTest values{1, 3, 4, 3, 6, 1, 4, 2, 9};
    RangeQueryForTest sumRangeQuery(values, plusAccumulator, minusAccumulator);

    EXPECT_EQ(1, sumRangeQuery.getAccumulatedValueOnInterval(0, 0));
    EXPECT_EQ(4, sumRangeQuery.getAccumulatedValueOnInterval(0, 1));
    EXPECT_EQ(8, sumRangeQuery.getAccumulatedValueOnInterval(0, 2));
    EXPECT_EQ(11, sumRangeQuery.getAccumulatedValueOnInterval(0, 3));
    EXPECT_EQ(17, sumRangeQuery.getAccumulatedValueOnInterval(0, 4));
    EXPECT_EQ(18, sumRangeQuery.getAccumulatedValueOnInterval(0, 5));
    EXPECT_EQ(22, sumRangeQuery.getAccumulatedValueOnInterval(0, 6));
    EXPECT_EQ(24, sumRangeQuery.getAccumulatedValueOnInterval(0, 7));
    EXPECT_EQ(33, sumRangeQuery.getAccumulatedValueOnInterval(0, 8));
    EXPECT_EQ(0, sumRangeQuery.getAccumulatedValueOnInterval(0, 9));
    EXPECT_EQ(21, sumRangeQuery.getAccumulatedValueOnInterval(1, 6));
    EXPECT_EQ(14, sumRangeQuery.getAccumulatedValueOnInterval(2, 5));
    EXPECT_EQ(9, sumRangeQuery.getAccumulatedValueOnInterval(3, 4));
    EXPECT_EQ(6, sumRangeQuery.getAccumulatedValueOnInterval(4, 4));
}

TEST(RangeQueryWithAccumulatorTest, GetAccumulatedValueOnIntervalWithGeometricSumWorksOnExample1) {
    ValuesForTest values{1, 3, 4, 8, 6, 1, 4, 2, 9};
    RangeQueryForTest geometricSumRangeQuery(values, multipliesAccumulator, dividesAccumulator);

    EXPECT_EQ(1, geometricSumRangeQuery.getAccumulatedValueOnInterval(0, 0));
    EXPECT_EQ(3, geometricSumRangeQuery.getAccumulatedValueOnInterval(0, 1));
    EXPECT_EQ(12, geometricSumRangeQuery.getAccumulatedValueOnInterval(0, 2));
    EXPECT_EQ(96, geometricSumRangeQuery.getAccumulatedValueOnInterval(0, 3));
    EXPECT_EQ(576, geometricSumRangeQuery.getAccumulatedValueOnInterval(0, 4));
    EXPECT_EQ(576, geometricSumRangeQuery.getAccumulatedValueOnInterval(0, 5));
    EXPECT_EQ(2304, geometricSumRangeQuery.getAccumulatedValueOnInterval(0, 6));
    EXPECT_EQ(4608, geometricSumRangeQuery.getAccumulatedValueOnInterval(0, 7));
    EXPECT_EQ(41472, geometricSumRangeQuery.getAccumulatedValueOnInterval(0, 8));
    EXPECT_EQ(0, geometricSumRangeQuery.getAccumulatedValueOnInterval(0, 9));
    EXPECT_EQ(2304, geometricSumRangeQuery.getAccumulatedValueOnInterval(1, 6));
    EXPECT_EQ(192, geometricSumRangeQuery.getAccumulatedValueOnInterval(2, 5));
    EXPECT_EQ(48, geometricSumRangeQuery.getAccumulatedValueOnInterval(3, 4));
    EXPECT_EQ(6, geometricSumRangeQuery.getAccumulatedValueOnInterval(4, 4));
}

TEST(RangeQueryWithAccumulatorTest, GetAccumulatedValueOnIntervalWithGeometricSumWorksOnExample2) {
    ValuesForTest values{1, 3, 4, 3, 6, 1, 4, 2, 9};
    RangeQueryForTest geometricSumRangeQuery(values, multipliesAccumulator, dividesAccumulator);

    EXPECT_EQ(1, geometricSumRangeQuery.getAccumulatedValueOnInterval(0, 0));
    EXPECT_EQ(3, geometricSumRangeQuery.getAccumulatedValueOnInterval(0, 1));
    EXPECT_EQ(12, geometricSumRangeQuery.getAccumulatedValueOnInterval(0, 2));
    EXPECT_EQ(36, geometricSumRangeQuery.getAccumulatedValueOnInterval(0, 3));
    EXPECT_EQ(216, geometricSumRangeQuery.getAccumulatedValueOnInterval(0, 4));
    EXPECT_EQ(216, geometricSumRangeQuery.getAccumulatedValueOnInterval(0, 5));
    EXPECT_EQ(864, geometricSumRangeQuery.getAccumulatedValueOnInterval(0, 6));
    EXPECT_EQ(1728, geometricSumRangeQuery.getAccumulatedValueOnInterval(0, 7));
    EXPECT_EQ(15552, geometricSumRangeQuery.getAccumulatedValueOnInterval(0, 8));
    EXPECT_EQ(0, geometricSumRangeQuery.getAccumulatedValueOnInterval(0, 9));
    EXPECT_EQ(864, geometricSumRangeQuery.getAccumulatedValueOnInterval(1, 6));
    EXPECT_EQ(72, geometricSumRangeQuery.getAccumulatedValueOnInterval(2, 5));
    EXPECT_EQ(18, geometricSumRangeQuery.getAccumulatedValueOnInterval(3, 4));
    EXPECT_EQ(6, geometricSumRangeQuery.getAccumulatedValueOnInterval(4, 4));
}

}  // namespace algorithm

}  // namespace alba
