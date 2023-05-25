#include <Algorithm/Search/RangeQuery/RangeQueryWithQuadraticAuxiliarySize.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using ValuesForTest = vector<int>;
using RangeQueryForTest = RangeQueryWithQuadraticAuxiliarySize<ValuesForTest>;
using ValueForTest = RangeQueryForTest::Value;

RangeQueryForTest::Function minimumSelector = [](ValueForTest const& value1, ValueForTest const& value2) {
    return min(value1, value2);
};

RangeQueryForTest::Function maximumSelector = [](ValueForTest const& value1, ValueForTest const& value2) {
    return max(value1, value2);
};
RangeQueryForTest::Function plusAccumulator = plus<>();
RangeQueryForTest::Function multipliesAccumulator = multiplies<>();
}  // namespace

TEST(RangeQueryWithQuadraticAuxiliarySizeTest, GetValueOnIntervalWithMinimumWorksWithEmptySetOfValues) {
    ValuesForTest values;
    RangeQueryForTest minimumRangeQuery(values, minimumSelector);

    EXPECT_EQ(0, minimumRangeQuery.getValueOnInterval(0, 0));
}

TEST(RangeQueryWithQuadraticAuxiliarySizeTest, GetValueOnIntervalWithMinimumWorksOnExample1) {
    ValuesForTest values{5, 9, 4, 8, 6, 1, 4, 2, 0};
    RangeQueryForTest minimumRangeQuery(values, minimumSelector);

    EXPECT_EQ(5, minimumRangeQuery.getValueOnInterval(0, 0));
    EXPECT_EQ(5, minimumRangeQuery.getValueOnInterval(0, 1));
    EXPECT_EQ(4, minimumRangeQuery.getValueOnInterval(0, 2));
    EXPECT_EQ(4, minimumRangeQuery.getValueOnInterval(0, 3));
    EXPECT_EQ(4, minimumRangeQuery.getValueOnInterval(0, 4));
    EXPECT_EQ(1, minimumRangeQuery.getValueOnInterval(0, 5));
    EXPECT_EQ(1, minimumRangeQuery.getValueOnInterval(0, 6));
    EXPECT_EQ(1, minimumRangeQuery.getValueOnInterval(0, 7));
    EXPECT_EQ(0, minimumRangeQuery.getValueOnInterval(0, 8));
    EXPECT_EQ(0, minimumRangeQuery.getValueOnInterval(0, 9));
    EXPECT_EQ(1, minimumRangeQuery.getValueOnInterval(3, 6));
    EXPECT_EQ(4, minimumRangeQuery.getValueOnInterval(2, 4));
}

TEST(RangeQueryWithQuadraticAuxiliarySizeTest, GetValueOnIntervalWithMaximumWorksOnExample1) {
    ValuesForTest values{5, 9, 4, 8, 6, 1, 4, 2, 10};
    RangeQueryForTest maximumRangeQuery(values, maximumSelector);

    EXPECT_EQ(5, maximumRangeQuery.getValueOnInterval(0, 0));
    EXPECT_EQ(9, maximumRangeQuery.getValueOnInterval(0, 1));
    EXPECT_EQ(9, maximumRangeQuery.getValueOnInterval(0, 2));
    EXPECT_EQ(9, maximumRangeQuery.getValueOnInterval(0, 3));
    EXPECT_EQ(9, maximumRangeQuery.getValueOnInterval(0, 4));
    EXPECT_EQ(9, maximumRangeQuery.getValueOnInterval(0, 5));
    EXPECT_EQ(9, maximumRangeQuery.getValueOnInterval(0, 6));
    EXPECT_EQ(9, maximumRangeQuery.getValueOnInterval(0, 7));
    EXPECT_EQ(10, maximumRangeQuery.getValueOnInterval(0, 8));
    EXPECT_EQ(0, maximumRangeQuery.getValueOnInterval(0, 9));
    EXPECT_EQ(8, maximumRangeQuery.getValueOnInterval(3, 6));
    EXPECT_EQ(8, maximumRangeQuery.getValueOnInterval(2, 4));
}

TEST(RangeQueryWithQuadraticAuxiliarySizeTest, GetValueOnIntervalWithSumWorksOnExample1) {
    ValuesForTest values{1, 3, 4, 8, 6, 1, 4, 2, 9};
    RangeQueryForTest sumRangeQuery(values, plusAccumulator);

    EXPECT_EQ(1, sumRangeQuery.getValueOnInterval(0, 0));
    EXPECT_EQ(4, sumRangeQuery.getValueOnInterval(0, 1));
    EXPECT_EQ(8, sumRangeQuery.getValueOnInterval(0, 2));
    EXPECT_EQ(16, sumRangeQuery.getValueOnInterval(0, 3));
    EXPECT_EQ(22, sumRangeQuery.getValueOnInterval(0, 4));
    EXPECT_EQ(23, sumRangeQuery.getValueOnInterval(0, 5));
    EXPECT_EQ(27, sumRangeQuery.getValueOnInterval(0, 6));
    EXPECT_EQ(29, sumRangeQuery.getValueOnInterval(0, 7));
    EXPECT_EQ(38, sumRangeQuery.getValueOnInterval(0, 8));
    EXPECT_EQ(0, sumRangeQuery.getValueOnInterval(0, 9));
    ;
    EXPECT_EQ(26, sumRangeQuery.getValueOnInterval(1, 6));
    EXPECT_EQ(19, sumRangeQuery.getValueOnInterval(2, 5));
    EXPECT_EQ(14, sumRangeQuery.getValueOnInterval(3, 4));
    EXPECT_EQ(6, sumRangeQuery.getValueOnInterval(4, 4));
}

TEST(RangeQueryWithQuadraticAuxiliarySizeTest, GetValueOnIntervalWithSumWorksOnExample2) {
    ValuesForTest values{1, 3, 4, 3, 6, 1, 4, 2, 9};
    RangeQueryForTest sumRangeQuery(values, plusAccumulator);

    EXPECT_EQ(1, sumRangeQuery.getValueOnInterval(0, 0));
    EXPECT_EQ(4, sumRangeQuery.getValueOnInterval(0, 1));
    EXPECT_EQ(8, sumRangeQuery.getValueOnInterval(0, 2));
    EXPECT_EQ(11, sumRangeQuery.getValueOnInterval(0, 3));
    EXPECT_EQ(17, sumRangeQuery.getValueOnInterval(0, 4));
    EXPECT_EQ(18, sumRangeQuery.getValueOnInterval(0, 5));
    EXPECT_EQ(22, sumRangeQuery.getValueOnInterval(0, 6));
    EXPECT_EQ(24, sumRangeQuery.getValueOnInterval(0, 7));
    EXPECT_EQ(33, sumRangeQuery.getValueOnInterval(0, 8));
    EXPECT_EQ(0, sumRangeQuery.getValueOnInterval(0, 9));
    EXPECT_EQ(21, sumRangeQuery.getValueOnInterval(1, 6));
    EXPECT_EQ(14, sumRangeQuery.getValueOnInterval(2, 5));
    EXPECT_EQ(9, sumRangeQuery.getValueOnInterval(3, 4));
    EXPECT_EQ(6, sumRangeQuery.getValueOnInterval(4, 4));
}

TEST(RangeQueryWithQuadraticAuxiliarySizeTest, GetValueOnIntervalWithGeometricSumWorksOnExample1) {
    ValuesForTest values{1, 3, 4, 8, 6, 1, 4, 2, 9};
    RangeQueryForTest geometricSumRangeQuery(values, multipliesAccumulator);

    EXPECT_EQ(1, geometricSumRangeQuery.getValueOnInterval(0, 0));
    EXPECT_EQ(3, geometricSumRangeQuery.getValueOnInterval(0, 1));
    EXPECT_EQ(12, geometricSumRangeQuery.getValueOnInterval(0, 2));
    EXPECT_EQ(96, geometricSumRangeQuery.getValueOnInterval(0, 3));
    EXPECT_EQ(576, geometricSumRangeQuery.getValueOnInterval(0, 4));
    EXPECT_EQ(576, geometricSumRangeQuery.getValueOnInterval(0, 5));
    EXPECT_EQ(2304, geometricSumRangeQuery.getValueOnInterval(0, 6));
    EXPECT_EQ(4608, geometricSumRangeQuery.getValueOnInterval(0, 7));
    EXPECT_EQ(41472, geometricSumRangeQuery.getValueOnInterval(0, 8));
    EXPECT_EQ(0, geometricSumRangeQuery.getValueOnInterval(0, 9));
    EXPECT_EQ(2304, geometricSumRangeQuery.getValueOnInterval(1, 6));
    EXPECT_EQ(192, geometricSumRangeQuery.getValueOnInterval(2, 5));
    EXPECT_EQ(48, geometricSumRangeQuery.getValueOnInterval(3, 4));
    EXPECT_EQ(6, geometricSumRangeQuery.getValueOnInterval(4, 4));
}

TEST(RangeQueryWithQuadraticAuxiliarySizeTest, GetValueOnIntervalWithGeometricSumWorksOnExample2) {
    ValuesForTest values{1, 3, 4, 3, 6, 1, 4, 2, 9};
    RangeQueryForTest geometricSumRangeQuery(values, multipliesAccumulator);

    EXPECT_EQ(1, geometricSumRangeQuery.getValueOnInterval(0, 0));
    EXPECT_EQ(3, geometricSumRangeQuery.getValueOnInterval(0, 1));
    EXPECT_EQ(12, geometricSumRangeQuery.getValueOnInterval(0, 2));
    EXPECT_EQ(36, geometricSumRangeQuery.getValueOnInterval(0, 3));
    EXPECT_EQ(216, geometricSumRangeQuery.getValueOnInterval(0, 4));
    EXPECT_EQ(216, geometricSumRangeQuery.getValueOnInterval(0, 5));
    EXPECT_EQ(864, geometricSumRangeQuery.getValueOnInterval(0, 6));
    EXPECT_EQ(1728, geometricSumRangeQuery.getValueOnInterval(0, 7));
    EXPECT_EQ(15552, geometricSumRangeQuery.getValueOnInterval(0, 8));
    EXPECT_EQ(0, geometricSumRangeQuery.getValueOnInterval(0, 9));
    EXPECT_EQ(864, geometricSumRangeQuery.getValueOnInterval(1, 6));
    EXPECT_EQ(72, geometricSumRangeQuery.getValueOnInterval(2, 5));
    EXPECT_EQ(18, geometricSumRangeQuery.getValueOnInterval(3, 4));
    EXPECT_EQ(6, geometricSumRangeQuery.getValueOnInterval(4, 4));
}

}  // namespace algorithm

}  // namespace alba
