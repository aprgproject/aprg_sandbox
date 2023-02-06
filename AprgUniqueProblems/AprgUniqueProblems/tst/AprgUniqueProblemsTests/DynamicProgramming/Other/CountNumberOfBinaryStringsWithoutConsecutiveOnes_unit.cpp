#include <AprgUniqueProblems/DynamicProgramming/Other/CountNumberOfBinaryStringsWithoutConsecutiveOnes.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(CountNumberOfBinaryStringsWithoutConsecutiveOnesTest, GetCountWorksOnExample1)
{
    CountNumberOfBinaryStringsWithoutConsecutiveOnes queryForTest(1U);

    EXPECT_EQ(2U, queryForTest.getCountUsingNaiveRecursion());
    EXPECT_EQ(2U, queryForTest.getCountUsingTabularDP());
    EXPECT_EQ(2U, queryForTest.getCountUsingTabularDPAndSpaceEfficient());
    EXPECT_EQ(2U, queryForTest.getCountUsingFibonacci());
}

TEST(CountNumberOfBinaryStringsWithoutConsecutiveOnesTest, GetCountWorksOnExample2)
{
    CountNumberOfBinaryStringsWithoutConsecutiveOnes queryForTest(2U);

    EXPECT_EQ(3U, queryForTest.getCountUsingNaiveRecursion());
    EXPECT_EQ(3U, queryForTest.getCountUsingTabularDP());
    EXPECT_EQ(3U, queryForTest.getCountUsingTabularDPAndSpaceEfficient());
    EXPECT_EQ(3U, queryForTest.getCountUsingFibonacci());
}

TEST(CountNumberOfBinaryStringsWithoutConsecutiveOnesTest, GetCountWorksOnExample3)
{
    CountNumberOfBinaryStringsWithoutConsecutiveOnes queryForTest(3U);

    EXPECT_EQ(5U, queryForTest.getCountUsingNaiveRecursion());
    EXPECT_EQ(5U, queryForTest.getCountUsingTabularDP());
    EXPECT_EQ(5U, queryForTest.getCountUsingTabularDPAndSpaceEfficient());
    EXPECT_EQ(5U, queryForTest.getCountUsingFibonacci());
}

TEST(CountNumberOfBinaryStringsWithoutConsecutiveOnesTest, GetCountWorksOnExample4)
{
    CountNumberOfBinaryStringsWithoutConsecutiveOnes queryForTest(10U);

    EXPECT_EQ(144U, queryForTest.getCountUsingNaiveRecursion());
    EXPECT_EQ(144U, queryForTest.getCountUsingTabularDP());
    EXPECT_EQ(144U, queryForTest.getCountUsingTabularDPAndSpaceEfficient());
    EXPECT_EQ(144U, queryForTest.getCountUsingFibonacci());
}

TEST(CountNumberOfBinaryStringsWithoutConsecutiveOnesTest, CheckTest)
{
    CountNumberOfBinaryStringsWithoutConsecutiveOnes queryForTest(11U);

    EXPECT_EQ(3U, queryForTest.getCountUsingMultipleReturns());
    EXPECT_EQ(3U, queryForTest.getCountUsingSingleReturn());
    EXPECT_EQ(3U, queryForTest.getCountUsingTernaryReturn());
}


}