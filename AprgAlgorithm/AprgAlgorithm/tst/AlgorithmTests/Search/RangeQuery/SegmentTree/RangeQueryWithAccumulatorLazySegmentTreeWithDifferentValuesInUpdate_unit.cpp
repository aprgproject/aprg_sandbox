#include <Algorithm/Search/RangeQuery/SegmentTree/RangeQueryWithAccumulatorLazySegmentTreeWithDifferentValuesInUpdate.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using ValuesForTest = vector<int>;
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

    EXPECT_EQ(0, sumRangeQuery.getValueOnInterval(0, 0));
}

TEST(
    RangeQueryWithAccumulatorLazySegmentTreeWithDifferentValuesInUpdateTest, GetValueOnIntervalWithSumWorksOnExample1) {
    ValuesForTest values{1, 3, 4, 8, 6, 1, 4, 2, 9};
    RangeQueryForTest sumRangeQuery(values, plusFunction, incrementFunction);

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
    EXPECT_EQ(26, sumRangeQuery.getValueOnInterval(1, 6));
    EXPECT_EQ(19, sumRangeQuery.getValueOnInterval(2, 5));
    EXPECT_EQ(14, sumRangeQuery.getValueOnInterval(3, 4));
    EXPECT_EQ(6, sumRangeQuery.getValueOnInterval(4, 4));
}

TEST(
    RangeQueryWithAccumulatorLazySegmentTreeWithDifferentValuesInUpdateTest,
    IncreaseAtRangeWithSumWorksWithEmptySetOfValues) {
    ValuesForTest values;
    RangeQueryForTest sumRangeQuery(values, plusFunction, incrementFunction);

    sumRangeQuery.increaseAtRange(0, 5);

    EXPECT_EQ(0, sumRangeQuery.getValueOnInterval(0, 0));
}

TEST(RangeQueryWithAccumulatorLazySegmentTreeWithDifferentValuesInUpdateTest, IncreaseAtRangeWithSumWorksOnExample1) {
    ValuesForTest values{1, 3, 4, 8, 6, 1, 4, 2, 9};
    RangeQueryForTest sumRangeQuery(values, plusFunction, incrementFunction);

    sumRangeQuery.increaseAtRange(0, 5);

    EXPECT_EQ(2, sumRangeQuery.getValueOnInterval(0, 0));
    EXPECT_EQ(7, sumRangeQuery.getValueOnInterval(0, 1));
    EXPECT_EQ(14, sumRangeQuery.getValueOnInterval(0, 2));
    EXPECT_EQ(26, sumRangeQuery.getValueOnInterval(0, 3));
    EXPECT_EQ(37, sumRangeQuery.getValueOnInterval(0, 4));
    EXPECT_EQ(44, sumRangeQuery.getValueOnInterval(0, 5));
    EXPECT_EQ(48, sumRangeQuery.getValueOnInterval(0, 6));
    EXPECT_EQ(50, sumRangeQuery.getValueOnInterval(0, 7));
    EXPECT_EQ(59, sumRangeQuery.getValueOnInterval(0, 8));
    EXPECT_EQ(0, sumRangeQuery.getValueOnInterval(0, 9));
    EXPECT_EQ(46, sumRangeQuery.getValueOnInterval(1, 6));
    EXPECT_EQ(37, sumRangeQuery.getValueOnInterval(2, 5));
    EXPECT_EQ(23, sumRangeQuery.getValueOnInterval(3, 4));
    EXPECT_EQ(11, sumRangeQuery.getValueOnInterval(4, 4));
}

}  // namespace algorithm

}  // namespace alba
