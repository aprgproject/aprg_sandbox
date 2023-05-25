#include <Algorithm/Search/RangeQuery/Blocks/RangeQueryWithBlocks.hpp>

#include <gtest/gtest.h>

#include <numeric>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using ValuesForTest = vector<int>;
using BlockValuesForTest = vector<int>;
using RangeQueryForTest = RangeQueryWithBlocks<ValuesForTest, BlockValuesForTest>;
using ValueForTest = typename RangeQueryForTest::Value;

RangeQueryForTest::ValuesFunction plusForARangeOfValues = [](ValuesForTest::const_iterator itStart,
                                                             ValuesForTest::const_iterator itEnd) {
    return std::accumulate(itStart + 1, itEnd, *itStart, plus<>());
};

RangeQueryForTest::ValuesFunction countFoursForARangeOfValues = [](ValuesForTest::const_iterator itStart,
                                                                   ValuesForTest::const_iterator itEnd) {
    return std::count(itStart, itEnd, 4);
};

RangeQueryForTest::ValuesFunction plusForARangeOfBlockValues = [](BlockValuesForTest::const_iterator itStart,
                                                                  BlockValuesForTest::const_iterator itEnd) {
    return std::accumulate(itStart + 1, itEnd, *itStart, plus<>());
};

}  // namespace

TEST(RangeQueryWithBlocksTest, GetBlockSizeWithSumWorksOnExample1) {
    ValuesForTest values{1, 3, 4, 8, 6, 1, 4, 2, 9};
    RangeQueryForTest sumRangeQuery(values, 2, plusForARangeOfValues, plusForARangeOfBlockValues);

    EXPECT_EQ(4, sumRangeQuery.getBlockSize());
}

TEST(RangeQueryWithBlocksTest, GetBlockSizeWithCountWorksOnExample1) {
    ValuesForTest values{4, 2, 5, 4, 2, 4, 3, 3, 4};
    RangeQueryForTest countRangeQuery(values, 2, countFoursForARangeOfValues, plusForARangeOfBlockValues);

    EXPECT_EQ(4, countRangeQuery.getBlockSize());
}

TEST(RangeQueryWithBlocksTest, GetBlocksWithSumWorksOnExample1) {
    ValuesForTest values{1, 3, 4, 8, 6, 1, 4, 2, 9};
    RangeQueryForTest sumRangeQuery(values, 2, plusForARangeOfValues, plusForARangeOfBlockValues);

    BlockValuesForTest blocks{16, 13, 9};
    EXPECT_EQ(blocks, sumRangeQuery.getBlocks());
}

TEST(RangeQueryWithBlocksTest, GetBlocksWithCountWorksOnExample1) {
    ValuesForTest values{4, 2, 5, 4, 2, 4, 3, 3, 4};
    RangeQueryForTest countRangeQuery(values, 2, countFoursForARangeOfValues, plusForARangeOfBlockValues);

    BlockValuesForTest blocks{2, 1, 1};
    EXPECT_EQ(blocks, countRangeQuery.getBlocks());
}

TEST(RangeQueryWithBlocksTest, GetResultOnIntervalWithSumWorksWithEmptySetOfValues) {
    ValuesForTest values;
    RangeQueryForTest sumRangeQuery(values, 2, plusForARangeOfValues, plusForARangeOfBlockValues);

    EXPECT_EQ(0, sumRangeQuery.getResultOnInterval(0, 0));
}

TEST(RangeQueryWithBlocksTest, GetResultOnIntervalWithSumWorksOnExample1) {
    ValuesForTest values{1, 3, 4, 8, 6, 1, 4, 2, 9};
    RangeQueryForTest sumRangeQuery(values, 2, plusForARangeOfValues, plusForARangeOfBlockValues);

    EXPECT_EQ(1, sumRangeQuery.getResultOnInterval(0, 0));
    EXPECT_EQ(4, sumRangeQuery.getResultOnInterval(0, 1));
    EXPECT_EQ(8, sumRangeQuery.getResultOnInterval(0, 2));
    EXPECT_EQ(16, sumRangeQuery.getResultOnInterval(0, 3));
    EXPECT_EQ(22, sumRangeQuery.getResultOnInterval(0, 4));
    EXPECT_EQ(23, sumRangeQuery.getResultOnInterval(0, 5));
    EXPECT_EQ(27, sumRangeQuery.getResultOnInterval(0, 6));
    EXPECT_EQ(29, sumRangeQuery.getResultOnInterval(0, 7));
    EXPECT_EQ(38, sumRangeQuery.getResultOnInterval(0, 8));
    EXPECT_EQ(0, sumRangeQuery.getResultOnInterval(0, 9));
    EXPECT_EQ(26, sumRangeQuery.getResultOnInterval(1, 6));
    EXPECT_EQ(19, sumRangeQuery.getResultOnInterval(2, 5));
    EXPECT_EQ(14, sumRangeQuery.getResultOnInterval(3, 4));
    EXPECT_EQ(6, sumRangeQuery.getResultOnInterval(4, 4));
}

TEST(RangeQueryWithBlocksTest, GetResultOnIntervalWithCountWorksOnExample1) {
    ValuesForTest values{4, 2, 5, 4, 2, 4, 3, 3, 4};
    RangeQueryForTest countRangeQuery(values, 2, countFoursForARangeOfValues, plusForARangeOfBlockValues);

    EXPECT_EQ(1, countRangeQuery.getResultOnInterval(0, 0));
    EXPECT_EQ(1, countRangeQuery.getResultOnInterval(0, 1));
    EXPECT_EQ(1, countRangeQuery.getResultOnInterval(0, 2));
    EXPECT_EQ(2, countRangeQuery.getResultOnInterval(0, 3));
    EXPECT_EQ(2, countRangeQuery.getResultOnInterval(0, 4));
    EXPECT_EQ(3, countRangeQuery.getResultOnInterval(0, 5));
    EXPECT_EQ(3, countRangeQuery.getResultOnInterval(0, 6));
    EXPECT_EQ(3, countRangeQuery.getResultOnInterval(0, 7));
    EXPECT_EQ(4, countRangeQuery.getResultOnInterval(0, 8));
    EXPECT_EQ(0, countRangeQuery.getResultOnInterval(0, 9));
    EXPECT_EQ(2, countRangeQuery.getResultOnInterval(1, 6));
    EXPECT_EQ(2, countRangeQuery.getResultOnInterval(2, 5));
    EXPECT_EQ(1, countRangeQuery.getResultOnInterval(3, 4));
    EXPECT_EQ(0, countRangeQuery.getResultOnInterval(4, 4));
}

TEST(RangeQueryWithBlocksTest, ChangeValueAtIndexWithSumWorksWithEmptySetOfValues) {
    ValuesForTest values;
    RangeQueryForTest sumRangeQuery(values, 2, plusForARangeOfValues, plusForARangeOfBlockValues);

    sumRangeQuery.changeValueAtIndex(0, 0);

    EXPECT_EQ(0, sumRangeQuery.getResultOnInterval(0, 0));
}

TEST(RangeQueryWithBlocksTest, ChangeValueAtIndexWithSumWorksOnExample1) {
    ValuesForTest values{1, 3, 4, 8, 6, 1, 4, 2, 9};
    RangeQueryForTest sumRangeQuery(values, 2, plusForARangeOfValues, plusForARangeOfBlockValues);

    sumRangeQuery.changeValueAtIndex(3, 3);

    EXPECT_EQ(1, sumRangeQuery.getResultOnInterval(0, 0));
    EXPECT_EQ(4, sumRangeQuery.getResultOnInterval(0, 1));
    EXPECT_EQ(8, sumRangeQuery.getResultOnInterval(0, 2));
    EXPECT_EQ(11, sumRangeQuery.getResultOnInterval(0, 3));
    EXPECT_EQ(17, sumRangeQuery.getResultOnInterval(0, 4));
    EXPECT_EQ(18, sumRangeQuery.getResultOnInterval(0, 5));
    EXPECT_EQ(22, sumRangeQuery.getResultOnInterval(0, 6));
    EXPECT_EQ(24, sumRangeQuery.getResultOnInterval(0, 7));
    EXPECT_EQ(33, sumRangeQuery.getResultOnInterval(0, 8));
    EXPECT_EQ(0, sumRangeQuery.getResultOnInterval(0, 9));
    EXPECT_EQ(21, sumRangeQuery.getResultOnInterval(1, 6));
    EXPECT_EQ(14, sumRangeQuery.getResultOnInterval(2, 5));
    EXPECT_EQ(9, sumRangeQuery.getResultOnInterval(3, 4));
    EXPECT_EQ(6, sumRangeQuery.getResultOnInterval(4, 4));
}

TEST(RangeQueryWithBlocksTest, ChangeValueAtIndexWithSumWorksTwiceOnExample1) {
    ValuesForTest values{1, 3, 4, 8, 6, 1, 4, 2, 9};
    RangeQueryForTest sumRangeQuery(values, 2, plusForARangeOfValues, plusForARangeOfBlockValues);

    sumRangeQuery.changeValueAtIndex(3, 3);
    sumRangeQuery.changeValueAtIndex(3, 13);

    EXPECT_EQ(1, sumRangeQuery.getResultOnInterval(0, 0));
    EXPECT_EQ(4, sumRangeQuery.getResultOnInterval(0, 1));
    EXPECT_EQ(8, sumRangeQuery.getResultOnInterval(0, 2));
    EXPECT_EQ(21, sumRangeQuery.getResultOnInterval(0, 3));
    EXPECT_EQ(27, sumRangeQuery.getResultOnInterval(0, 4));
    EXPECT_EQ(28, sumRangeQuery.getResultOnInterval(0, 5));
    EXPECT_EQ(32, sumRangeQuery.getResultOnInterval(0, 6));
    EXPECT_EQ(34, sumRangeQuery.getResultOnInterval(0, 7));
    EXPECT_EQ(43, sumRangeQuery.getResultOnInterval(0, 8));
    EXPECT_EQ(0, sumRangeQuery.getResultOnInterval(0, 9));
    EXPECT_EQ(31, sumRangeQuery.getResultOnInterval(1, 6));
    EXPECT_EQ(24, sumRangeQuery.getResultOnInterval(2, 5));
    EXPECT_EQ(19, sumRangeQuery.getResultOnInterval(3, 4));
    EXPECT_EQ(6, sumRangeQuery.getResultOnInterval(4, 4));
}

TEST(RangeQueryWithBlocksTest, ChangeValueAtIndexWithCountWorksOnExample1) {
    ValuesForTest values{4, 2, 5, 4, 2, 4, 3, 3, 4};
    RangeQueryForTest countRangeQuery(values, 2, countFoursForARangeOfValues, plusForARangeOfBlockValues);

    countRangeQuery.changeValueAtIndex(0, 3);

    EXPECT_EQ(0, countRangeQuery.getResultOnInterval(0, 0));
    EXPECT_EQ(0, countRangeQuery.getResultOnInterval(0, 1));
    EXPECT_EQ(0, countRangeQuery.getResultOnInterval(0, 2));
    EXPECT_EQ(1, countRangeQuery.getResultOnInterval(0, 3));
    EXPECT_EQ(1, countRangeQuery.getResultOnInterval(0, 4));
    EXPECT_EQ(2, countRangeQuery.getResultOnInterval(0, 5));
    EXPECT_EQ(2, countRangeQuery.getResultOnInterval(0, 6));
    EXPECT_EQ(2, countRangeQuery.getResultOnInterval(0, 7));
    EXPECT_EQ(3, countRangeQuery.getResultOnInterval(0, 8));
    EXPECT_EQ(0, countRangeQuery.getResultOnInterval(0, 9));
    EXPECT_EQ(2, countRangeQuery.getResultOnInterval(1, 6));
    EXPECT_EQ(2, countRangeQuery.getResultOnInterval(2, 5));
    EXPECT_EQ(1, countRangeQuery.getResultOnInterval(3, 4));
    EXPECT_EQ(0, countRangeQuery.getResultOnInterval(4, 4));
}

TEST(RangeQueryWithBlocksTest, SquareRootSizeExampleWorks) {
    // Note that having sqrt(n) of blocks is special:
    // The idea is to divide the array into blocks of size sqrt(n) so that each block contains the sum of elements
    // inside the block. Since the number of single elements is O(sqrt(n)) and the number of blocks is also O(sqrt(n)),
    // the sum query takes O(sqrt(n)) time. The purpose of the block size sqrt(n) is that it balances two things:
    // -> the array is divided into sqrt(n) blocks, each of which contains sqrt(n) elements.
    // So all operations take O(sqrt(n)) time.

    ValuesForTest values{5, 8, 6, 3, 2, 5, 2, 6, 7, 1, 7, 5, 6, 2, 6, 2};
    RangeQueryForTest sumRangeQuery(values, 4, plusForARangeOfValues, plusForARangeOfBlockValues);

    EXPECT_EQ(44, sumRangeQuery.getResultOnInterval(3, 12));

    sumRangeQuery.changeValueAtIndex(5, 0);

    EXPECT_EQ(39, sumRangeQuery.getResultOnInterval(3, 12));
}

}  // namespace algorithm

}  // namespace alba
