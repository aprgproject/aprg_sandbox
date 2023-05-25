#include <Algorithm/Search/RangeQuery/Blocks/RangeQueryWithBlocksWithMultipleRequests.hpp>

#include <gtest/gtest.h>

#include <numeric>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using ValuesForTest = vector<int>;
using BlockValuesForTest = vector<int>;
using RangeQueryForTest = RangeQueryWithBlocksWithMultipleRequests<ValuesForTest, BlockValuesForTest>;
using ValueForTest = typename RangeQueryForTest::Value;
using BlockValueForTest = typename RangeQueryForTest::BlockValue;
using RangesForTest = typename RangeQueryForTest::Ranges;
using InputAndOutputPairsForTest = typename RangeQueryForTest::InputAndOutputPairs;

RangeQueryForTest::TwoBlocksFunction plusForAPairOfBlockValues = plus<>();
RangeQueryForTest::TwoBlocksFunction minusForPairOfBlockValues = minus<>();

RangeQueryForTest::ValuesFunction plusForARangeOfValues = [](ValuesForTest::const_iterator itStart,
                                                             ValuesForTest::const_iterator itEnd) {
    return std::accumulate(itStart + 1, itEnd, *itStart, plus<>());
};

RangeQueryForTest::ValuesFunction plusForARangeOfBlockValues = [](BlockValuesForTest::const_iterator itStart,
                                                                  BlockValuesForTest::const_iterator itEnd) {
    return std::accumulate(itStart + 1, itEnd, *itStart, plus<>());
};
}  // namespace

TEST(RangeQueryWithBlocksWithMultipleRequestsTest, GetInputAndOutputPairsUsingMoAlgorithmWithSumWorksOnExample1) {
    ValuesForTest values{1, 3, 4, 8, 6, 1, 4, 2, 9};
    RangeQueryForTest sumRangeQuery(
        values, plusForARangeOfValues, plusForARangeOfBlockValues, plusForAPairOfBlockValues,
        minusForPairOfBlockValues);
    RangesForTest inputRanges{{0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6},
                              {0, 7}, {0, 8}, {0, 9}, {1, 6}, {2, 5}, {3, 4}, {4, 4}};

    InputAndOutputPairsForTest expectedPairs{{{0, 0}, 1},  {{0, 1}, 4},  {{0, 2}, 8},  {{0, 3}, 16}, {{0, 4}, 22},
                                             {{0, 5}, 23}, {{2, 5}, 19}, {{0, 6}, 27}, {{1, 6}, 26}, {{0, 7}, 29},
                                             {{0, 8}, 38}, {{3, 4}, 14}, {{4, 4}, 6}};
    EXPECT_EQ(expectedPairs, sumRangeQuery.getInputAndOutputPairsUsingMoAlgorithm(inputRanges));
}

}  // namespace algorithm

}  // namespace alba
