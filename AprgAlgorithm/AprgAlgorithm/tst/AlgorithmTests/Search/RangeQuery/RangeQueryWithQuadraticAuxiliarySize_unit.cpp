#include <Algorithm/Search/RangeQuery/RangeQueryWithQuadraticAuxiliarySize.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using ValuesForTest = vector<unsigned int>;
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

    EXPECT_EQ(0U, minimumRangeQuery.getValueOnInterval(0U, 0U));
}

TEST(RangeQueryWithQuadraticAuxiliarySizeTest, GetValueOnIntervalWithMinimumWorksOnExample1) {
    ValuesForTest values{5U, 9U, 4U, 8U, 6U, 1U, 4U, 2U, 0U};
    RangeQueryForTest minimumRangeQuery(values, minimumSelector);

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

TEST(RangeQueryWithQuadraticAuxiliarySizeTest, GetValueOnIntervalWithMaximumWorksOnExample1) {
    ValuesForTest values{5U, 9U, 4U, 8U, 6U, 1U, 4U, 2U, 10U};
    RangeQueryForTest maximumRangeQuery(values, maximumSelector);

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

TEST(RangeQueryWithQuadraticAuxiliarySizeTest, GetValueOnIntervalWithSumWorksOnExample1) {
    ValuesForTest values{1U, 3U, 4U, 8U, 6U, 1U, 4U, 2U, 9U};
    RangeQueryForTest sumRangeQuery(values, plusAccumulator);

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
    ;
    EXPECT_EQ(26U, sumRangeQuery.getValueOnInterval(1U, 6U));
    EXPECT_EQ(19U, sumRangeQuery.getValueOnInterval(2U, 5U));
    EXPECT_EQ(14U, sumRangeQuery.getValueOnInterval(3U, 4U));
    EXPECT_EQ(6U, sumRangeQuery.getValueOnInterval(4U, 4U));
}

TEST(RangeQueryWithQuadraticAuxiliarySizeTest, GetValueOnIntervalWithSumWorksOnExample2) {
    ValuesForTest values{1U, 3U, 4U, 3U, 6U, 1U, 4U, 2U, 9U};
    RangeQueryForTest sumRangeQuery(values, plusAccumulator);

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

TEST(RangeQueryWithQuadraticAuxiliarySizeTest, GetValueOnIntervalWithGeometricSumWorksOnExample1) {
    ValuesForTest values{1U, 3U, 4U, 8U, 6U, 1U, 4U, 2U, 9U};
    RangeQueryForTest geometricSumRangeQuery(values, multipliesAccumulator);

    EXPECT_EQ(1U, geometricSumRangeQuery.getValueOnInterval(0U, 0U));
    EXPECT_EQ(3U, geometricSumRangeQuery.getValueOnInterval(0U, 1U));
    EXPECT_EQ(12U, geometricSumRangeQuery.getValueOnInterval(0U, 2U));
    EXPECT_EQ(96U, geometricSumRangeQuery.getValueOnInterval(0U, 3U));
    EXPECT_EQ(576U, geometricSumRangeQuery.getValueOnInterval(0U, 4U));
    EXPECT_EQ(576U, geometricSumRangeQuery.getValueOnInterval(0U, 5U));
    EXPECT_EQ(2304U, geometricSumRangeQuery.getValueOnInterval(0U, 6U));
    EXPECT_EQ(4608U, geometricSumRangeQuery.getValueOnInterval(0U, 7U));
    EXPECT_EQ(41472U, geometricSumRangeQuery.getValueOnInterval(0U, 8U));
    EXPECT_EQ(0U, geometricSumRangeQuery.getValueOnInterval(0U, 9U));
    EXPECT_EQ(2304U, geometricSumRangeQuery.getValueOnInterval(1U, 6U));
    EXPECT_EQ(192U, geometricSumRangeQuery.getValueOnInterval(2U, 5U));
    EXPECT_EQ(48U, geometricSumRangeQuery.getValueOnInterval(3U, 4U));
    EXPECT_EQ(6U, geometricSumRangeQuery.getValueOnInterval(4U, 4U));
}

TEST(RangeQueryWithQuadraticAuxiliarySizeTest, GetValueOnIntervalWithGeometricSumWorksOnExample2) {
    ValuesForTest values{1U, 3U, 4U, 3U, 6U, 1U, 4U, 2U, 9U};
    RangeQueryForTest geometricSumRangeQuery(values, multipliesAccumulator);

    EXPECT_EQ(1U, geometricSumRangeQuery.getValueOnInterval(0U, 0U));
    EXPECT_EQ(3U, geometricSumRangeQuery.getValueOnInterval(0U, 1U));
    EXPECT_EQ(12U, geometricSumRangeQuery.getValueOnInterval(0U, 2U));
    EXPECT_EQ(36U, geometricSumRangeQuery.getValueOnInterval(0U, 3U));
    EXPECT_EQ(216U, geometricSumRangeQuery.getValueOnInterval(0U, 4U));
    EXPECT_EQ(216U, geometricSumRangeQuery.getValueOnInterval(0U, 5U));
    EXPECT_EQ(864U, geometricSumRangeQuery.getValueOnInterval(0U, 6U));
    EXPECT_EQ(1728U, geometricSumRangeQuery.getValueOnInterval(0U, 7U));
    EXPECT_EQ(15552U, geometricSumRangeQuery.getValueOnInterval(0U, 8U));
    EXPECT_EQ(0U, geometricSumRangeQuery.getValueOnInterval(0U, 9U));
    EXPECT_EQ(864U, geometricSumRangeQuery.getValueOnInterval(1U, 6U));
    EXPECT_EQ(72U, geometricSumRangeQuery.getValueOnInterval(2U, 5U));
    EXPECT_EQ(18U, geometricSumRangeQuery.getValueOnInterval(3U, 4U));
    EXPECT_EQ(6U, geometricSumRangeQuery.getValueOnInterval(4U, 4U));
}

}  // namespace algorithm

}  // namespace alba
