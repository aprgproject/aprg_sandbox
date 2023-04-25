#include <Algorithm/Search/RangeQuery/SegmentTree/RangeQueryWithAccumulatorLazySegmentTreeWithDifferentValuesInUpdate.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using ValuesForTest = vector<unsigned int>;
using RangeQueryForTest = RangeQueryWithAccumulatorLazySegmentTreeWithDifferentValuesInUpdate<ValuesForTest>;
using ValueForTest = RangeQueryForTest::Value;
using IndexForTest = RangeQueryForTest::Index;
RangeQueryForTest::Function plusFunction = plus<>();
RangeQueryForTest::IncrementFunction incrementFunction = [](IndexForTest const intervalStart,
                                                            IndexForTest const intervalEnd) {
    // Increase the first value in range [a,b] by 1, the second value by 2, the third value by 3, and so on.

    ValueForTest incrementValue = 0;
    for (IndexForTest index = intervalStart; index <= intervalEnd; index++) {
        incrementValue += index + 1;
    }
    return incrementValue;
};
}  // namespace

TEST(
    RangeQueryWithAccumulatorLazySegmentTreeWithDifferentValuesInUpdateTest,
    GetValueOnIntervalWithMinimumWorksWithEmptySetOfValues) {
    ValuesForTest values;
    RangeQueryForTest sumRangeQuery(values, plusFunction, incrementFunction);

    EXPECT_EQ(0U, sumRangeQuery.getValueOnInterval(0U, 0U));
}

TEST(
    RangeQueryWithAccumulatorLazySegmentTreeWithDifferentValuesInUpdateTest, GetValueOnIntervalWithSumWorksOnExample1) {
    ValuesForTest values{1U, 3U, 4U, 8U, 6U, 1U, 4U, 2U, 9U};
    RangeQueryForTest sumRangeQuery(values, plusFunction, incrementFunction);

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

TEST(
    RangeQueryWithAccumulatorLazySegmentTreeWithDifferentValuesInUpdateTest,
    IncreaseAtRangeWithSumWorksWithEmptySetOfValues) {
    ValuesForTest values;
    RangeQueryForTest sumRangeQuery(values, plusFunction, incrementFunction);

    sumRangeQuery.increaseAtRange(0U, 5U);

    EXPECT_EQ(0U, sumRangeQuery.getValueOnInterval(0U, 0U));
}

TEST(RangeQueryWithAccumulatorLazySegmentTreeWithDifferentValuesInUpdateTest, IncreaseAtRangeWithSumWorksOnExample1) {
    ValuesForTest values{1U, 3U, 4U, 8U, 6U, 1U, 4U, 2U, 9U};
    RangeQueryForTest sumRangeQuery(values, plusFunction, incrementFunction);

    sumRangeQuery.increaseAtRange(0U, 5U);

    EXPECT_EQ(2U, sumRangeQuery.getValueOnInterval(0U, 0U));
    EXPECT_EQ(7U, sumRangeQuery.getValueOnInterval(0U, 1U));
    EXPECT_EQ(14U, sumRangeQuery.getValueOnInterval(0U, 2U));
    EXPECT_EQ(26U, sumRangeQuery.getValueOnInterval(0U, 3U));
    EXPECT_EQ(37U, sumRangeQuery.getValueOnInterval(0U, 4U));
    EXPECT_EQ(44U, sumRangeQuery.getValueOnInterval(0U, 5U));
    EXPECT_EQ(48U, sumRangeQuery.getValueOnInterval(0U, 6U));
    EXPECT_EQ(50U, sumRangeQuery.getValueOnInterval(0U, 7U));
    EXPECT_EQ(59U, sumRangeQuery.getValueOnInterval(0U, 8U));
    EXPECT_EQ(0U, sumRangeQuery.getValueOnInterval(0U, 9U));
    EXPECT_EQ(46U, sumRangeQuery.getValueOnInterval(1U, 6U));
    EXPECT_EQ(37U, sumRangeQuery.getValueOnInterval(2U, 5U));
    EXPECT_EQ(23U, sumRangeQuery.getValueOnInterval(3U, 4U));
    EXPECT_EQ(11U, sumRangeQuery.getValueOnInterval(4U, 4U));
}

}  // namespace algorithm

}  // namespace alba
