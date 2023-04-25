#include <Algorithm/Search/RangeQuery/Blocks/RangeQueryWithBlocks.hpp>

#include <gtest/gtest.h>

#include <numeric>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using ValuesForTest = vector<unsigned int>;
using BlockValuesForTest = vector<unsigned int>;
using RangeQueryForTest = RangeQueryWithBlocks<ValuesForTest, BlockValuesForTest>;
using ValueForTest = typename RangeQueryForTest::Value;

RangeQueryForTest::ValuesFunction plusForARangeOfValues = [](ValuesForTest::const_iterator itStart,
                                                             ValuesForTest::const_iterator itEnd) {
    return std::accumulate(itStart + 1, itEnd, *itStart, plus<>());
};

RangeQueryForTest::ValuesFunction countFoursForARangeOfValues = [](ValuesForTest::const_iterator itStart,
                                                                   ValuesForTest::const_iterator itEnd) {
    return std::count(itStart, itEnd, 4U);
};

RangeQueryForTest::ValuesFunction plusForARangeOfBlockValues = [](BlockValuesForTest::const_iterator itStart,
                                                                  BlockValuesForTest::const_iterator itEnd) {
    return std::accumulate(itStart + 1, itEnd, *itStart, plus<>());
};

}  // namespace

TEST(RangeQueryWithBlocksTest, GetBlockSizeWithSumWorksOnExample1) {
    ValuesForTest values{1U, 3U, 4U, 8U, 6U, 1U, 4U, 2U, 9U};
    RangeQueryForTest sumRangeQuery(values, 2U, plusForARangeOfValues, plusForARangeOfBlockValues);

    EXPECT_EQ(4U, sumRangeQuery.getBlockSize());
}

TEST(RangeQueryWithBlocksTest, GetBlockSizeWithCountWorksOnExample1) {
    ValuesForTest values{4U, 2U, 5U, 4U, 2U, 4U, 3U, 3U, 4U};
    RangeQueryForTest countRangeQuery(values, 2U, countFoursForARangeOfValues, plusForARangeOfBlockValues);

    EXPECT_EQ(4U, countRangeQuery.getBlockSize());
}

TEST(RangeQueryWithBlocksTest, GetBlocksWithSumWorksOnExample1) {
    ValuesForTest values{1U, 3U, 4U, 8U, 6U, 1U, 4U, 2U, 9U};
    RangeQueryForTest sumRangeQuery(values, 2U, plusForARangeOfValues, plusForARangeOfBlockValues);

    BlockValuesForTest blocks{16U, 13U, 9U};
    EXPECT_EQ(blocks, sumRangeQuery.getBlocks());
}

TEST(RangeQueryWithBlocksTest, GetBlocksWithCountWorksOnExample1) {
    ValuesForTest values{4U, 2U, 5U, 4U, 2U, 4U, 3U, 3U, 4U};
    RangeQueryForTest countRangeQuery(values, 2U, countFoursForARangeOfValues, plusForARangeOfBlockValues);

    BlockValuesForTest blocks{2U, 1U, 1U};
    EXPECT_EQ(blocks, countRangeQuery.getBlocks());
}

TEST(RangeQueryWithBlocksTest, GetResultOnIntervalWithSumWorksWithEmptySetOfValues) {
    ValuesForTest values;
    RangeQueryForTest sumRangeQuery(values, 2U, plusForARangeOfValues, plusForARangeOfBlockValues);

    EXPECT_EQ(0U, sumRangeQuery.getResultOnInterval(0U, 0U));
}

TEST(RangeQueryWithBlocksTest, GetResultOnIntervalWithSumWorksOnExample1) {
    ValuesForTest values{1U, 3U, 4U, 8U, 6U, 1U, 4U, 2U, 9U};
    RangeQueryForTest sumRangeQuery(values, 2U, plusForARangeOfValues, plusForARangeOfBlockValues);

    EXPECT_EQ(1U, sumRangeQuery.getResultOnInterval(0U, 0U));
    EXPECT_EQ(4U, sumRangeQuery.getResultOnInterval(0U, 1U));
    EXPECT_EQ(8U, sumRangeQuery.getResultOnInterval(0U, 2U));
    EXPECT_EQ(16U, sumRangeQuery.getResultOnInterval(0U, 3U));
    EXPECT_EQ(22U, sumRangeQuery.getResultOnInterval(0U, 4U));
    EXPECT_EQ(23U, sumRangeQuery.getResultOnInterval(0U, 5U));
    EXPECT_EQ(27U, sumRangeQuery.getResultOnInterval(0U, 6U));
    EXPECT_EQ(29U, sumRangeQuery.getResultOnInterval(0U, 7U));
    EXPECT_EQ(38U, sumRangeQuery.getResultOnInterval(0U, 8U));
    EXPECT_EQ(0U, sumRangeQuery.getResultOnInterval(0U, 9U));
    EXPECT_EQ(26U, sumRangeQuery.getResultOnInterval(1U, 6U));
    EXPECT_EQ(19U, sumRangeQuery.getResultOnInterval(2U, 5U));
    EXPECT_EQ(14U, sumRangeQuery.getResultOnInterval(3U, 4U));
    EXPECT_EQ(6U, sumRangeQuery.getResultOnInterval(4U, 4U));
}

TEST(RangeQueryWithBlocksTest, GetResultOnIntervalWithCountWorksOnExample1) {
    ValuesForTest values{4U, 2U, 5U, 4U, 2U, 4U, 3U, 3U, 4U};
    RangeQueryForTest countRangeQuery(values, 2U, countFoursForARangeOfValues, plusForARangeOfBlockValues);

    EXPECT_EQ(1U, countRangeQuery.getResultOnInterval(0U, 0U));
    EXPECT_EQ(1U, countRangeQuery.getResultOnInterval(0U, 1U));
    EXPECT_EQ(1U, countRangeQuery.getResultOnInterval(0U, 2U));
    EXPECT_EQ(2U, countRangeQuery.getResultOnInterval(0U, 3U));
    EXPECT_EQ(2U, countRangeQuery.getResultOnInterval(0U, 4U));
    EXPECT_EQ(3U, countRangeQuery.getResultOnInterval(0U, 5U));
    EXPECT_EQ(3U, countRangeQuery.getResultOnInterval(0U, 6U));
    EXPECT_EQ(3U, countRangeQuery.getResultOnInterval(0U, 7U));
    EXPECT_EQ(4U, countRangeQuery.getResultOnInterval(0U, 8U));
    EXPECT_EQ(0U, countRangeQuery.getResultOnInterval(0U, 9U));
    EXPECT_EQ(2U, countRangeQuery.getResultOnInterval(1U, 6U));
    EXPECT_EQ(2U, countRangeQuery.getResultOnInterval(2U, 5U));
    EXPECT_EQ(1U, countRangeQuery.getResultOnInterval(3U, 4U));
    EXPECT_EQ(0U, countRangeQuery.getResultOnInterval(4U, 4U));
}

TEST(RangeQueryWithBlocksTest, ChangeValueAtIndexWithSumWorksWithEmptySetOfValues) {
    ValuesForTest values;
    RangeQueryForTest sumRangeQuery(values, 2U, plusForARangeOfValues, plusForARangeOfBlockValues);

    sumRangeQuery.changeValueAtIndex(0U, 0U);

    EXPECT_EQ(0U, sumRangeQuery.getResultOnInterval(0U, 0U));
}

TEST(RangeQueryWithBlocksTest, ChangeValueAtIndexWithSumWorksOnExample1) {
    ValuesForTest values{1U, 3U, 4U, 8U, 6U, 1U, 4U, 2U, 9U};
    RangeQueryForTest sumRangeQuery(values, 2U, plusForARangeOfValues, plusForARangeOfBlockValues);

    sumRangeQuery.changeValueAtIndex(3U, 3U);

    EXPECT_EQ(1U, sumRangeQuery.getResultOnInterval(0U, 0U));
    EXPECT_EQ(4U, sumRangeQuery.getResultOnInterval(0U, 1U));
    EXPECT_EQ(8U, sumRangeQuery.getResultOnInterval(0U, 2U));
    EXPECT_EQ(11U, sumRangeQuery.getResultOnInterval(0U, 3U));
    EXPECT_EQ(17U, sumRangeQuery.getResultOnInterval(0U, 4U));
    EXPECT_EQ(18U, sumRangeQuery.getResultOnInterval(0U, 5U));
    EXPECT_EQ(22U, sumRangeQuery.getResultOnInterval(0U, 6U));
    EXPECT_EQ(24U, sumRangeQuery.getResultOnInterval(0U, 7U));
    EXPECT_EQ(33U, sumRangeQuery.getResultOnInterval(0U, 8U));
    EXPECT_EQ(0U, sumRangeQuery.getResultOnInterval(0U, 9U));
    EXPECT_EQ(21U, sumRangeQuery.getResultOnInterval(1U, 6U));
    EXPECT_EQ(14U, sumRangeQuery.getResultOnInterval(2U, 5U));
    EXPECT_EQ(9U, sumRangeQuery.getResultOnInterval(3U, 4U));
    EXPECT_EQ(6U, sumRangeQuery.getResultOnInterval(4U, 4U));
}

TEST(RangeQueryWithBlocksTest, ChangeValueAtIndexWithSumWorksTwiceOnExample1) {
    ValuesForTest values{1U, 3U, 4U, 8U, 6U, 1U, 4U, 2U, 9U};
    RangeQueryForTest sumRangeQuery(values, 2U, plusForARangeOfValues, plusForARangeOfBlockValues);

    sumRangeQuery.changeValueAtIndex(3U, 3U);
    sumRangeQuery.changeValueAtIndex(3U, 13U);

    EXPECT_EQ(1U, sumRangeQuery.getResultOnInterval(0U, 0U));
    EXPECT_EQ(4U, sumRangeQuery.getResultOnInterval(0U, 1U));
    EXPECT_EQ(8U, sumRangeQuery.getResultOnInterval(0U, 2U));
    EXPECT_EQ(21U, sumRangeQuery.getResultOnInterval(0U, 3U));
    EXPECT_EQ(27U, sumRangeQuery.getResultOnInterval(0U, 4U));
    EXPECT_EQ(28U, sumRangeQuery.getResultOnInterval(0U, 5U));
    EXPECT_EQ(32U, sumRangeQuery.getResultOnInterval(0U, 6U));
    EXPECT_EQ(34U, sumRangeQuery.getResultOnInterval(0U, 7U));
    EXPECT_EQ(43U, sumRangeQuery.getResultOnInterval(0U, 8U));
    EXPECT_EQ(0U, sumRangeQuery.getResultOnInterval(0U, 9U));
    EXPECT_EQ(31U, sumRangeQuery.getResultOnInterval(1U, 6U));
    EXPECT_EQ(24U, sumRangeQuery.getResultOnInterval(2U, 5U));
    EXPECT_EQ(19U, sumRangeQuery.getResultOnInterval(3U, 4U));
    EXPECT_EQ(6U, sumRangeQuery.getResultOnInterval(4U, 4U));
}

TEST(RangeQueryWithBlocksTest, ChangeValueAtIndexWithCountWorksOnExample1) {
    ValuesForTest values{4U, 2U, 5U, 4U, 2U, 4U, 3U, 3U, 4U};
    RangeQueryForTest countRangeQuery(values, 2U, countFoursForARangeOfValues, plusForARangeOfBlockValues);

    countRangeQuery.changeValueAtIndex(0U, 3U);

    EXPECT_EQ(0U, countRangeQuery.getResultOnInterval(0U, 0U));
    EXPECT_EQ(0U, countRangeQuery.getResultOnInterval(0U, 1U));
    EXPECT_EQ(0U, countRangeQuery.getResultOnInterval(0U, 2U));
    EXPECT_EQ(1U, countRangeQuery.getResultOnInterval(0U, 3U));
    EXPECT_EQ(1U, countRangeQuery.getResultOnInterval(0U, 4U));
    EXPECT_EQ(2U, countRangeQuery.getResultOnInterval(0U, 5U));
    EXPECT_EQ(2U, countRangeQuery.getResultOnInterval(0U, 6U));
    EXPECT_EQ(2U, countRangeQuery.getResultOnInterval(0U, 7U));
    EXPECT_EQ(3U, countRangeQuery.getResultOnInterval(0U, 8U));
    EXPECT_EQ(0U, countRangeQuery.getResultOnInterval(0U, 9U));
    EXPECT_EQ(2U, countRangeQuery.getResultOnInterval(1U, 6U));
    EXPECT_EQ(2U, countRangeQuery.getResultOnInterval(2U, 5U));
    EXPECT_EQ(1U, countRangeQuery.getResultOnInterval(3U, 4U));
    EXPECT_EQ(0U, countRangeQuery.getResultOnInterval(4U, 4U));
}

TEST(RangeQueryWithBlocksTest, SquareRootSizeExampleWorks) {
    // Note that having sqrt(n) of blocks is special:
    // The idea is to divide the array into blocks of size sqrt(n) so that each block contains the sum of elements
    // inside the block. Since the number of single elements is O(sqrt(n)) and the number of blocks is also O(sqrt(n)),
    // the sum query takes O(sqrt(n)) time. The purpose of the block size sqrt(n) is that it balances two things:
    // -> the array is divided into sqrt(n) blocks, each of which contains sqrt(n) elements.
    // So all operations take O(sqrt(n)) time.

    ValuesForTest values{5U, 8U, 6U, 3U, 2U, 5U, 2U, 6U, 7U, 1U, 7U, 5U, 6U, 2U, 6U, 2U};
    RangeQueryForTest sumRangeQuery(values, 4U, plusForARangeOfValues, plusForARangeOfBlockValues);

    EXPECT_EQ(44U, sumRangeQuery.getResultOnInterval(3U, 12U));

    sumRangeQuery.changeValueAtIndex(5U, 0U);

    EXPECT_EQ(39U, sumRangeQuery.getResultOnInterval(3U, 12U));
}

}  // namespace algorithm

}  // namespace alba
