#include <AprgUniqueProblems/DynamicProgramming/Math/Digits/CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSumTest, GetCountWorksOnExample1)
{
    CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum queryForTest(1U, 0U);

    EXPECT_EQ(1U, queryForTest.getCountUsingNaiveRecursion());
    EXPECT_EQ(1U, queryForTest.getCountUsingMemoizationDP());
    EXPECT_EQ(1U, queryForTest.getCountUsingTabularDP());
    EXPECT_EQ(1U, queryForTest.getCountUsingTabularDPAndSpaceEfficient());
    //EXPECT_EQ(1U, queryForTest.getCountUsing1And9());
}

TEST(CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSumTest, GetCountWorksOnExample2)
{
    CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum queryForTest(2U, 2U);

    EXPECT_EQ(2U, queryForTest.getCountUsingNaiveRecursion());
    EXPECT_EQ(2U, queryForTest.getCountUsingMemoizationDP());
    EXPECT_EQ(2U, queryForTest.getCountUsingTabularDP());
    EXPECT_EQ(2U, queryForTest.getCountUsingTabularDPAndSpaceEfficient());
    EXPECT_EQ(2U, queryForTest.getCountBySearchingValuesWith1And9Increment());
}

TEST(CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSumTest, GetCountWorksOnExample3)
{
    CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum queryForTest(2U, 5U);

    EXPECT_EQ(5U, queryForTest.getCountUsingNaiveRecursion());
    EXPECT_EQ(5U, queryForTest.getCountUsingMemoizationDP());
    EXPECT_EQ(5U, queryForTest.getCountUsingTabularDP());
    EXPECT_EQ(5U, queryForTest.getCountUsingTabularDPAndSpaceEfficient());
    EXPECT_EQ(5U, queryForTest.getCountBySearchingValuesWith1And9Increment());
}

TEST(CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSumTest, GetCountWorksOnExample4)
{
    CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum queryForTest(3U, 6U);

    EXPECT_EQ(21U, queryForTest.getCountUsingNaiveRecursion());
    EXPECT_EQ(21U, queryForTest.getCountUsingMemoizationDP());
    EXPECT_EQ(21U, queryForTest.getCountUsingTabularDP());
    EXPECT_EQ(21U, queryForTest.getCountUsingTabularDPAndSpaceEfficient());
    EXPECT_EQ(21U, queryForTest.getCountBySearchingValuesWith1And9Increment());
}

}
