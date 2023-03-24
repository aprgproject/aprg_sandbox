#include <AprgUniqueProblems/DynamicProgramming/Math/Digits/CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSumTest, GetCountWorksOnZeroWithOneDigit)
{
    CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum queryForTest(1U, 0U);

    EXPECT_EQ(1U, queryForTest.getCountUsingNaiveRecursion());
    EXPECT_EQ(1U, queryForTest.getCountUsingMemoizationDP());
    EXPECT_EQ(1U, queryForTest.getCountUsingIterativeDP());
    EXPECT_EQ(1U, queryForTest.getCountUsingIterativeDPAndSpaceEfficient());
    EXPECT_EQ(1U, queryForTest.getCountBySearchingValuesWith1And9Increment());
}

TEST(CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSumTest, GetCountWorksOnZeroWithMultipleDigits)
{
    CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum queryForTest(2U, 0U);

    EXPECT_EQ(1U, queryForTest.getCountUsingNaiveRecursion());
    EXPECT_EQ(1U, queryForTest.getCountUsingMemoizationDP());
    EXPECT_EQ(1U, queryForTest.getCountUsingIterativeDP());
    EXPECT_EQ(1U, queryForTest.getCountUsingIterativeDPAndSpaceEfficient());
    EXPECT_EQ(1U, queryForTest.getCountBySearchingValuesWith1And9Increment());
}

TEST(CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSumTest, GetCountWorksOnExample1)
{
    CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum queryForTest(2U, 2U);

    EXPECT_EQ(2U, queryForTest.getCountUsingNaiveRecursion());
    EXPECT_EQ(2U, queryForTest.getCountUsingMemoizationDP());
    EXPECT_EQ(2U, queryForTest.getCountUsingIterativeDP());
    EXPECT_EQ(2U, queryForTest.getCountUsingIterativeDPAndSpaceEfficient());
    EXPECT_EQ(2U, queryForTest.getCountBySearchingValuesWith1And9Increment());
}

TEST(CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSumTest, GetCountWorksOnExample2)
{
    CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum queryForTest(2U, 5U);

    EXPECT_EQ(5U, queryForTest.getCountUsingNaiveRecursion());
    EXPECT_EQ(5U, queryForTest.getCountUsingMemoizationDP());
    EXPECT_EQ(5U, queryForTest.getCountUsingIterativeDP());
    EXPECT_EQ(5U, queryForTest.getCountUsingIterativeDPAndSpaceEfficient());
    EXPECT_EQ(5U, queryForTest.getCountBySearchingValuesWith1And9Increment());
}

TEST(CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSumTest, GetCountWorksOnExample3)
{
    CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum queryForTest(3U, 6U);

    EXPECT_EQ(21U, queryForTest.getCountUsingNaiveRecursion());
    EXPECT_EQ(21U, queryForTest.getCountUsingMemoizationDP());
    EXPECT_EQ(21U, queryForTest.getCountUsingIterativeDP());
    EXPECT_EQ(21U, queryForTest.getCountUsingIterativeDPAndSpaceEfficient());
    EXPECT_EQ(21U, queryForTest.getCountBySearchingValuesWith1And9Increment());
}

}
