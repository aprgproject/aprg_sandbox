#include <AprgUniqueProblems/DynamicProgramming/Other/PrintMaximumNumberOfAs.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(PrintMaximumNumberOfAsTest, GetMaxCountOfAOnScreenOnZero)
{
    PrintMaximumNumberOfAs queryForTest(0U);

    EXPECT_EQ(0U, queryForTest.getMaxCountOfAOnScreenUsingNaiveRecursion());
    EXPECT_EQ(0U, queryForTest.getMaxCountOfAOnScreenUsingMemoizationDP());
    EXPECT_EQ(0U, queryForTest.getMaxCountOfAOnScreenUsingIterativeDP());
    EXPECT_EQ(0U, queryForTest.getMaxCountOfAOnScreenUsingIterativeDPAndSpaceEfficient());
}

TEST(PrintMaximumNumberOfAsTest, GetMaxCountOfAOnScreenOnExample1)
{
    PrintMaximumNumberOfAs queryForTest(1U);

    EXPECT_EQ(1U, queryForTest.getMaxCountOfAOnScreenUsingNaiveRecursion());
    EXPECT_EQ(1U, queryForTest.getMaxCountOfAOnScreenUsingMemoizationDP());
    EXPECT_EQ(1U, queryForTest.getMaxCountOfAOnScreenUsingIterativeDP());
    EXPECT_EQ(1U, queryForTest.getMaxCountOfAOnScreenUsingIterativeDPAndSpaceEfficient());
}

TEST(PrintMaximumNumberOfAsTest, GetMaxCountOfAOnScreenOnExample2)
{
    PrintMaximumNumberOfAs queryForTest(3U);

    EXPECT_EQ(3U, queryForTest.getMaxCountOfAOnScreenUsingNaiveRecursion());
    EXPECT_EQ(3U, queryForTest.getMaxCountOfAOnScreenUsingMemoizationDP());
    EXPECT_EQ(3U, queryForTest.getMaxCountOfAOnScreenUsingIterativeDP());
    EXPECT_EQ(3U, queryForTest.getMaxCountOfAOnScreenUsingIterativeDPAndSpaceEfficient());
}

TEST(PrintMaximumNumberOfAsTest, GetMaxCountOfAOnScreenOnExample3)
{
    PrintMaximumNumberOfAs queryForTest(7U);

    EXPECT_EQ(9U, queryForTest.getMaxCountOfAOnScreenUsingNaiveRecursion());
    EXPECT_EQ(9U, queryForTest.getMaxCountOfAOnScreenUsingMemoizationDP());
    EXPECT_EQ(9U, queryForTest.getMaxCountOfAOnScreenUsingIterativeDP());
    EXPECT_EQ(9U, queryForTest.getMaxCountOfAOnScreenUsingIterativeDPAndSpaceEfficient());
}

TEST(PrintMaximumNumberOfAsTest, GetMaxCountOfAOnScreenOnExample4)
{
    PrintMaximumNumberOfAs queryForTest(11U);

    //EXPECT_EQ(27U, queryForTest.getMaxCountOfAOnScreenUsingNaiveRecursion()); // too long
    EXPECT_EQ(27U, queryForTest.getMaxCountOfAOnScreenUsingMemoizationDP());
    EXPECT_EQ(27U, queryForTest.getMaxCountOfAOnScreenUsingIterativeDP());
    EXPECT_EQ(27U, queryForTest.getMaxCountOfAOnScreenUsingIterativeDPAndSpaceEfficient());
}


}
