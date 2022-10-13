#include <Algorithm/Search/RangeQuery/RangeQueryWithBlocksWithMultipleRequests.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using ValuesForTest = vector<unsigned int>;
using BlockValuesForTest = vector<unsigned int>;
using RangeQueryForTest = RangeQueryWithBlocksWithMultipleRequests<ValuesForTest, BlockValuesForTest>;
using ValueForTest = typename RangeQueryForTest::Value;
using BlockValueForTest = typename RangeQueryForTest::BlockValue;
using RangesForTest = typename RangeQueryForTest::Ranges;
using RequestAndOutputPairsForTest = typename RangeQueryForTest::RequestAndOutputPairs;

RangeQueryForTest::ValuesFunction plusForARangeOfValues = [](
        ValuesForTest::const_iterator itStart, ValuesForTest::const_iterator itEnd)
{
    return std::accumulate(itStart+1, itEnd, *itStart, plus<ValueForTest>());
};

RangeQueryForTest::ValuesFunction plusForARangeOfBlockValues = [](
        BlockValuesForTest::const_iterator itStart, BlockValuesForTest::const_iterator itEnd)
{
    return std::accumulate(itStart+1, itEnd, *itStart, plus<ValueForTest>());
};

RangeQueryForTest::TwoBlocksFunction plusForAPairOfBlockValues = [](
        BlockValueForTest const blockValue1, BlockValueForTest const blockValue2)
{
    return blockValue1 + blockValue2;
};

RangeQueryForTest::TwoBlocksFunction minusForPairOfBlockValues = [](
        BlockValueForTest const blockValue1, BlockValueForTest const blockValue2)
{
    return blockValue1 - blockValue2;
};

}

TEST(RangeQueryWithBlocksWithMultipleRequestsTest, GetRequestAndOutputPairsUsingMoAlgorithmWithSumWorksOnExample1)
{
    ValuesForTest values{1U, 3U, 4U, 8U, 6U, 1U, 4U, 2U, 9U};
    RangeQueryForTest sumRangeQuery(values, plusForARangeOfValues, plusForARangeOfBlockValues, plusForAPairOfBlockValues, minusForPairOfBlockValues);
    RangesForTest requests
    {{0U, 0U}, {0U, 1U}, {0U, 2U}, {0U, 3U}, {0U, 4U}, {0U, 5U}, {0U, 6U},
        {0U, 7U}, {0U, 8U}, {0U, 9U}, {1U, 6U}, {2U, 5U}, {3U, 4U}, {4U, 4U}};

    RequestAndOutputPairsForTest expectedPairs
    {{{0U, 0U}, 1U}, {{0U, 1U}, 4U}, {{0U, 2U}, 8U}, {{0U, 3U}, 16U}, {{0U, 4U}, 22U}, {{0U, 5U}, 23U}, {{2U, 5U}, 19U},
        {{0U, 6U}, 27U}, {{1U, 6U}, 26U}, {{0U, 7U}, 29U}, {{0U, 8U}, 38U}, {{3U, 4U}, 14U}, {{4U, 4U}, 6U}};
    EXPECT_EQ(expectedPairs, sumRangeQuery.getRequestAndOutputPairsUsingMoAlgorithm(requests));
}

}

}
