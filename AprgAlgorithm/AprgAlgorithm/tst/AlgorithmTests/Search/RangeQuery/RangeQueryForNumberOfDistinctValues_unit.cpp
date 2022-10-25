#include <Algorithm/Search/RangeQuery/RangeQueryForNumberOfDistinctValues.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
constexpr unsigned int MAX_VALUE = 50U;
using ValuesForTest = vector<unsigned int>;
using RangeQueryForTest = RangeQueryForNumberOfDistinctValues<ValuesForTest, MAX_VALUE>;
using RangesForTest = typename RangeQueryForTest::Ranges;
using InputAndOutputPairsForTest = typename RangeQueryForTest::InputAndOutputPairs;

}

TEST(RangeQueryForNumberOfDistinctValuesTest, GetCountOfDistinctValuesOnIntervalWorksOnExample1)
{
    ValuesForTest values{4U, 2U, 5U, 4U, 2U, 4U, 3U, 3U, 4U};
    RangeQueryForTest countRangeQuery(values);

    EXPECT_EQ(1U, countRangeQuery.getCountOfDistinctValuesOnInterval(0U, 0U));
    EXPECT_EQ(2U, countRangeQuery.getCountOfDistinctValuesOnInterval(0U, 1U));
    EXPECT_EQ(3U, countRangeQuery.getCountOfDistinctValuesOnInterval(0U, 2U));
    EXPECT_EQ(3U, countRangeQuery.getCountOfDistinctValuesOnInterval(0U, 3U));
    EXPECT_EQ(3U, countRangeQuery.getCountOfDistinctValuesOnInterval(0U, 4U));
    EXPECT_EQ(3U, countRangeQuery.getCountOfDistinctValuesOnInterval(0U, 5U));
    EXPECT_EQ(4U, countRangeQuery.getCountOfDistinctValuesOnInterval(0U, 6U));
    EXPECT_EQ(4U, countRangeQuery.getCountOfDistinctValuesOnInterval(0U, 7U));
    EXPECT_EQ(4U, countRangeQuery.getCountOfDistinctValuesOnInterval(0U, 8U));
    EXPECT_EQ(0U, countRangeQuery.getCountOfDistinctValuesOnInterval(0U, 9U));
    EXPECT_EQ(4U, countRangeQuery.getCountOfDistinctValuesOnInterval(1U, 6U));
    EXPECT_EQ(3U, countRangeQuery.getCountOfDistinctValuesOnInterval(2U, 5U));
    EXPECT_EQ(2U, countRangeQuery.getCountOfDistinctValuesOnInterval(3U, 4U));
    EXPECT_EQ(1U, countRangeQuery.getCountOfDistinctValuesOnInterval(4U, 4U));
}

TEST(RangeQueryForNumberOfDistinctValuesTest, GetInputAndOutputPairsUsingMoAlgorithmWorksOnExample1)
{
    ValuesForTest values{4U, 2U, 5U, 4U, 2U, 4U, 3U, 3U, 4U};
    RangeQueryForTest countRangeQuery(values);
    RangesForTest inputRanges
    {{0U, 0U}, {0U, 1U}, {0U, 2U}, {0U, 3U}, {0U, 4U}, {0U, 5U}, {0U, 6U},
        {0U, 7U}, {0U, 8U}, {0U, 9U}, {1U, 6U}, {2U, 5U}, {3U, 4U}, {4U, 4U}};

    InputAndOutputPairsForTest expectedPairs
    {{{0U, 0U}, 1U}, {{0U, 1U}, 2U}, {{0U, 2U}, 3U}, {{0U, 3U}, 3U}, {{0U, 4U}, 3U}, {{0U, 5U}, 3U}, {{2U, 5U}, 3U},
        {{0U, 6U}, 4U}, {{1U, 6U}, 4U}, {{0U, 7U}, 4U}, {{0U, 8U}, 4U}, {{3U, 4U}, 2U}, {{4U, 4U}, 1U}};
    EXPECT_EQ(expectedPairs, countRangeQuery.getInputAndOutputPairsUsingMoAlgorithm(inputRanges));
}

}

}
