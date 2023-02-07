#include <AprgUniqueProblems/DynamicProgramming/Math/Digits/TotalNumberOfNonDecreasingNumbersWithNDigits.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(TotalNumberOfNonDecreasingNumbersWithNDigitsTest, GetCountWorksOnExample1)
{
    TotalNumberOfNonDecreasingNumbersWithNDigits queryForTest(0U);

    EXPECT_EQ(0U, queryForTest.getCountUsingNaiveRecursion());
    EXPECT_EQ(0U, queryForTest.getCountUsingMemoizationDP());
    EXPECT_EQ(0U, queryForTest.getCountUsingTabularDP());
    EXPECT_EQ(0U, queryForTest.getCountUsingTabularDPAndSpaceEfficient());
}

TEST(TotalNumberOfNonDecreasingNumbersWithNDigitsTest, GetCountWorksOnExample2)
{
    TotalNumberOfNonDecreasingNumbersWithNDigits queryForTest(1U);

    EXPECT_EQ(10U, queryForTest.getCountUsingNaiveRecursion());
    EXPECT_EQ(10U, queryForTest.getCountUsingMemoizationDP());
    EXPECT_EQ(10U, queryForTest.getCountUsingTabularDP());
    EXPECT_EQ(10U, queryForTest.getCountUsingTabularDPAndSpaceEfficient());
}

TEST(TotalNumberOfNonDecreasingNumbersWithNDigitsTest, GetCountWorksOnExample3)
{
    TotalNumberOfNonDecreasingNumbersWithNDigits queryForTest(2U);

    EXPECT_EQ(55U, queryForTest.getCountUsingNaiveRecursion());
    EXPECT_EQ(55U, queryForTest.getCountUsingMemoizationDP());
    EXPECT_EQ(55U, queryForTest.getCountUsingTabularDP());
    EXPECT_EQ(55U, queryForTest.getCountUsingTabularDPAndSpaceEfficient());
}

TEST(TotalNumberOfNonDecreasingNumbersWithNDigitsTest, GetCountWorksOnExample4)
{
    TotalNumberOfNonDecreasingNumbersWithNDigits queryForTest(3U);

    EXPECT_EQ(220U, queryForTest.getCountUsingNaiveRecursion());
    EXPECT_EQ(220U, queryForTest.getCountUsingMemoizationDP());
    EXPECT_EQ(220U, queryForTest.getCountUsingTabularDP());
    EXPECT_EQ(220U, queryForTest.getCountUsingTabularDPAndSpaceEfficient());
}

}
