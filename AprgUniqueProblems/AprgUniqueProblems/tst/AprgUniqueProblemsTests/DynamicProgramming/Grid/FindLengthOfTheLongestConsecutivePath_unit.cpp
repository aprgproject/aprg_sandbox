#include <AprgUniqueProblems/DynamicProgramming/Grid/FindLengthOfTheLongestConsecutivePath.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace
{
using Grid=FindLengthOfTheLongestConsecutivePath::ValueGrid;
}

TEST(FindLengthOfTheLongestConsecutivePathTest, GetLongestLengthWorksOnExample1)
{
    Grid inputGrid(3U, 3U,
    {'a', 'c', 'd',
     'h', 'b', 'e',
     'i', 'g', 'f'});
    FindLengthOfTheLongestConsecutivePath queryForTest(inputGrid);
    EXPECT_EQ(9U, queryForTest.getLongestLengthUsingNaiveRecursion());
    EXPECT_EQ(5U, queryForTest.getLongestLengthStartingAtUsingNaiveRecursion(2U, 1U));
    EXPECT_EQ(9U, queryForTest.getLongestLengthUsingMemoizationDP());
    EXPECT_EQ(5U, queryForTest.getLongestLengthStartingAtUsingMemoizationDP(2U, 1U));
}

TEST(FindLengthOfTheLongestConsecutivePathTest, GetLongestLengthWorksOnExample2)
{
    Grid inputGrid(3U, 3U,
    {'b', 'e', 'f',
     'h', 'd', 'a',
     'i', 'c', 'a'});
    FindLengthOfTheLongestConsecutivePath queryForTest(inputGrid);
    EXPECT_EQ(4U, queryForTest.getLongestLengthUsingNaiveRecursion());
    EXPECT_EQ(1U, queryForTest.getLongestLengthStartingAtUsingNaiveRecursion(0U, 0U));
    EXPECT_EQ(4U, queryForTest.getLongestLengthUsingMemoizationDP());
    EXPECT_EQ(1U, queryForTest.getLongestLengthStartingAtUsingMemoizationDP(0U, 0U));
}

}
