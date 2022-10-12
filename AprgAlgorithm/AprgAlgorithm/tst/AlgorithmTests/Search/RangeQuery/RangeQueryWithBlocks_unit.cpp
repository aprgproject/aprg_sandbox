#include <Algorithm/Search/RangeQuery/RangeQueryWithBlocks.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using ValuesForTest = vector<unsigned int>;
using RangeQueryForTest = RangeQueryWithBlocks<ValuesForTest>;
using ValueForTest = RangeQueryForTest::Value;

RangeQueryForTest::Function plusFunction = [](ValueForTest const& value1, ValueForTest const& value2)
{
    return plus<ValueForTest>()(value1, value2);
};

}

TEST(RangeQueryWithBlocksTest, GetValueOnIntervalWithSumWorksWithEmptySetOfValues)
{
    ValuesForTest values;
    RangeQueryForTest sumRangeQuery(2U, values, plusFunction);

    EXPECT_EQ(0U, sumRangeQuery.getValueOnInterval(0U, 0U));
}

TEST(RangeQueryWithBlocksTest, GetValueOnIntervalWithSumWorksOnExample1)
{
    ValuesForTest values{1U, 3U, 4U, 8U, 6U, 1U, 4U, 2U, 9U};
    RangeQueryForTest sumRangeQuery(2U, values, plusFunction);

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

TEST(RangeQueryWithBlocksTest, ChangeValueAtIndexWithSumWorksWithEmptySetOfValues)
{
    ValuesForTest values;
    RangeQueryForTest sumRangeQuery(2U, values, plusFunction);

    sumRangeQuery.changeValueAtIndex(0U, 0U);

    EXPECT_EQ(0U, sumRangeQuery.getValueOnInterval(0U, 0U));
}

TEST(RangeQueryWithBlocksTest, ChangeValueAtIndexWithSumWorksOnExample1)
{
    ValuesForTest values{1U, 3U, 4U, 8U, 6U, 1U, 4U, 2U, 9U};
    RangeQueryForTest sumRangeQuery(2U, values, plusFunction);

    sumRangeQuery.changeValueAtIndex(3U, 3U);

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

TEST(RangeQueryWithBlocksTest, ChangeValueAtIndexWithSumWorksTwiceOnExample1)
{
    ValuesForTest values{1U, 3U, 4U, 8U, 6U, 1U, 4U, 2U, 9U};
    RangeQueryForTest sumRangeQuery(2U, values, plusFunction);

    sumRangeQuery.changeValueAtIndex(3U, 3U);
    sumRangeQuery.changeValueAtIndex(3U, 13U);

    EXPECT_EQ(1U, sumRangeQuery.getValueOnInterval(0U, 0U));
    EXPECT_EQ(4U, sumRangeQuery.getValueOnInterval(0U, 1U));
    EXPECT_EQ(8U, sumRangeQuery.getValueOnInterval(0U, 2U));
    EXPECT_EQ(21U, sumRangeQuery.getValueOnInterval(0U, 3U));
    EXPECT_EQ(27U, sumRangeQuery.getValueOnInterval(0U, 4U));
    EXPECT_EQ(28U, sumRangeQuery.getValueOnInterval(0U, 5U));
    EXPECT_EQ(32U, sumRangeQuery.getValueOnInterval(0U, 6U));
    EXPECT_EQ(34U, sumRangeQuery.getValueOnInterval(0U, 7U));
    EXPECT_EQ(43U, sumRangeQuery.getValueOnInterval(0U, 8U));
    EXPECT_EQ(0U, sumRangeQuery.getValueOnInterval(0U, 9U));
    EXPECT_EQ(31U, sumRangeQuery.getValueOnInterval(1U, 6U));
    EXPECT_EQ(24U, sumRangeQuery.getValueOnInterval(2U, 5U));
    EXPECT_EQ(19U, sumRangeQuery.getValueOnInterval(3U, 4U));
    EXPECT_EQ(6U, sumRangeQuery.getValueOnInterval(4U, 4U));
}

TEST(RangeQueryWithBlocksTest, SquareRootSizeExampleWorks)
{
    // Note that having sqrt(n) of blocks is special:
    // The idea is to divide the array into blocks of size sqrt(n) so that each block contains the sum of elements inside the block.
    // Since the number of single elements is O(sqrt(n)) and the number of blocks is also O(sqrt(n)), the sum query takes O(sqrt(n)) time.
    // The purpose of the block size sqrt(n) is that it balances two things:
    // -> the array is divided into sqrt(n) blocks, each of which contains sqrt(n) elements.
    // So all operations take O(sqrt(n)) time.

    ValuesForTest values{5U, 8U, 6U, 3U, 2U, 5U, 2U, 6U, 7U, 1U, 7U, 5U, 6U, 2U, 6U, 2U};
    RangeQueryForTest sumRangeQuery(4U, values, plusFunction);

    EXPECT_EQ(44U, sumRangeQuery.getValueOnInterval(3U, 12U));

    sumRangeQuery.changeValueAtIndex(5U, 0U);

    EXPECT_EQ(39U, sumRangeQuery.getValueOnInterval(3U, 12U));
}

}

}
