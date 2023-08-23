#include <UniqueProblems/BitManipulation/CountTotalSetBitsInAllNumbersFrom1ToN.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(CountTotalSetBitsInAllNumbersFrom1ToNTest, GetTotalSetBitsUsingPopcountWorksOnExample1) {
    CountTotalSetBitsInAllNumbersFrom1ToN solution;

    EXPECT_EQ(0U, solution.getTotalSetBitsUsingPopcount(0U));
    EXPECT_EQ(1U, solution.getTotalSetBitsUsingPopcount(1U));
    EXPECT_EQ(2U, solution.getTotalSetBitsUsingPopcount(2U));
    EXPECT_EQ(4U, solution.getTotalSetBitsUsingPopcount(3U));
    EXPECT_EQ(5U, solution.getTotalSetBitsUsingPopcount(4U));
    EXPECT_EQ(7U, solution.getTotalSetBitsUsingPopcount(5U));
    EXPECT_EQ(9U, solution.getTotalSetBitsUsingPopcount(6U));
    EXPECT_EQ(12U, solution.getTotalSetBitsUsingPopcount(7U));
    EXPECT_EQ(13U, solution.getTotalSetBitsUsingPopcount(8U));
    EXPECT_EQ(319U, solution.getTotalSetBitsUsingPopcount(100U));
}

TEST(CountTotalSetBitsInAllNumbersFrom1ToNTest, GetTotalSetBitsUsingPreComputedBitCountsWorksOnExample1) {
    CountTotalSetBitsInAllNumbersFrom1ToN solution;

    EXPECT_EQ(0U, solution.getTotalSetBitsUsingPreComputedBitCounts(0U));
    EXPECT_EQ(1U, solution.getTotalSetBitsUsingPreComputedBitCounts(1U));
    EXPECT_EQ(2U, solution.getTotalSetBitsUsingPreComputedBitCounts(2U));
    EXPECT_EQ(4U, solution.getTotalSetBitsUsingPreComputedBitCounts(3U));
    EXPECT_EQ(5U, solution.getTotalSetBitsUsingPreComputedBitCounts(4U));
    EXPECT_EQ(7U, solution.getTotalSetBitsUsingPreComputedBitCounts(5U));
    EXPECT_EQ(9U, solution.getTotalSetBitsUsingPreComputedBitCounts(6U));
    EXPECT_EQ(12U, solution.getTotalSetBitsUsingPreComputedBitCounts(7U));
    EXPECT_EQ(13U, solution.getTotalSetBitsUsingPreComputedBitCounts(8U));
    EXPECT_EQ(319U, solution.getTotalSetBitsUsingPreComputedBitCounts(100U));
}

TEST(CountTotalSetBitsInAllNumbersFrom1ToNTest, GetTotalSetBitsUsingBitCountsWorksOnExample1) {
    CountTotalSetBitsInAllNumbersFrom1ToN solution;

    EXPECT_EQ(0U, solution.getTotalSetBitsUsingBitCounts(0U));
    EXPECT_EQ(1U, solution.getTotalSetBitsUsingBitCounts(1U));
    EXPECT_EQ(2U, solution.getTotalSetBitsUsingBitCounts(2U));
    EXPECT_EQ(4U, solution.getTotalSetBitsUsingBitCounts(3U));
    EXPECT_EQ(5U, solution.getTotalSetBitsUsingBitCounts(4U));
    EXPECT_EQ(7U, solution.getTotalSetBitsUsingBitCounts(5U));
    EXPECT_EQ(9U, solution.getTotalSetBitsUsingBitCounts(6U));
    EXPECT_EQ(12U, solution.getTotalSetBitsUsingBitCounts(7U));
    EXPECT_EQ(13U, solution.getTotalSetBitsUsingBitCounts(8U));
    EXPECT_EQ(319U, solution.getTotalSetBitsUsingBitCounts(100U));
}

}  // namespace alba
