#include <Algorithm/Search/RangeQuery/RangeQueryForNumberOfDistinctValues.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
constexpr int MAX_VALUE = 50;
using ValuesForTest = vector<int>;
using RangeQueryForTest = RangeQueryForNumberOfDistinctValues<ValuesForTest, MAX_VALUE>;
using RangesForTest = typename RangeQueryForTest::Ranges;
using InputAndOutputPairsForTest = typename RangeQueryForTest::InputAndOutputPairs;

}  // namespace

TEST(RangeQueryForNumberOfDistinctValuesTest, GetCountOfDistinctValuesOnIntervalWorksOnExample1) {
    ValuesForTest values{4, 2, 5, 4, 2, 4, 3, 3, 4};
    RangeQueryForTest countRangeQuery(values);

    EXPECT_EQ(1, countRangeQuery.getCountOfDistinctValuesOnInterval(0, 0));
    EXPECT_EQ(2, countRangeQuery.getCountOfDistinctValuesOnInterval(0, 1));
    EXPECT_EQ(3, countRangeQuery.getCountOfDistinctValuesOnInterval(0, 2));
    EXPECT_EQ(3, countRangeQuery.getCountOfDistinctValuesOnInterval(0, 3));
    EXPECT_EQ(3, countRangeQuery.getCountOfDistinctValuesOnInterval(0, 4));
    EXPECT_EQ(3, countRangeQuery.getCountOfDistinctValuesOnInterval(0, 5));
    EXPECT_EQ(4, countRangeQuery.getCountOfDistinctValuesOnInterval(0, 6));
    EXPECT_EQ(4, countRangeQuery.getCountOfDistinctValuesOnInterval(0, 7));
    EXPECT_EQ(4, countRangeQuery.getCountOfDistinctValuesOnInterval(0, 8));
    EXPECT_EQ(0, countRangeQuery.getCountOfDistinctValuesOnInterval(0, 9));
    EXPECT_EQ(4, countRangeQuery.getCountOfDistinctValuesOnInterval(1, 6));
    EXPECT_EQ(3, countRangeQuery.getCountOfDistinctValuesOnInterval(2, 5));
    EXPECT_EQ(2, countRangeQuery.getCountOfDistinctValuesOnInterval(3, 4));
    EXPECT_EQ(1, countRangeQuery.getCountOfDistinctValuesOnInterval(4, 4));
}

TEST(RangeQueryForNumberOfDistinctValuesTest, GetInputAndOutputPairsUsingMoAlgorithmWorksOnExample1) {
    ValuesForTest values{4, 2, 5, 4, 2, 4, 3, 3, 4};
    RangeQueryForTest countRangeQuery(values);
    RangesForTest inputRanges{{0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6},
                              {0, 7}, {0, 8}, {0, 9}, {1, 6}, {2, 5}, {3, 4}, {4, 4}};

    InputAndOutputPairsForTest expectedPairs{{{0, 0}, 1}, {{0, 1}, 2}, {{0, 2}, 3}, {{0, 3}, 3}, {{0, 4}, 3},
                                             {{0, 5}, 3}, {{2, 5}, 3}, {{0, 6}, 4}, {{1, 6}, 4}, {{0, 7}, 4},
                                             {{0, 8}, 4}, {{3, 4}, 2}, {{4, 4}, 1}};
    EXPECT_EQ(expectedPairs, countRangeQuery.getInputAndOutputPairsUsingMoAlgorithm(inputRanges));
}

}  // namespace algorithm

}  // namespace alba
