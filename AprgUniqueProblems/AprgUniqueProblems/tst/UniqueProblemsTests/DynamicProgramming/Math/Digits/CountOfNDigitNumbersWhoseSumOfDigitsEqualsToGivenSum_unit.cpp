#include <UniqueProblems/DynamicProgramming/Math/Digits/CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba {
TEST(CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSumTest, GetCountWorksOnZeroWithOneDigit) {
    CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum queryForTest(1, 0);

    EXPECT_EQ(1, queryForTest.getCountUsingNaiveRecursion());
    EXPECT_EQ(1, queryForTest.getCountUsingMemoizationDP());
    EXPECT_EQ(1, queryForTest.getCountUsingIterativeDP());
    EXPECT_EQ(1, queryForTest.getCountUsingIterativeDPAndSpaceEfficient());
    EXPECT_EQ(1, queryForTest.getCountBySearchingValuesWith1And9Increment());
}

TEST(CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSumTest, GetCountWorksOnZeroWithMultipleDigits) {
    CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum queryForTest(2, 0);

    EXPECT_EQ(1, queryForTest.getCountUsingNaiveRecursion());
    EXPECT_EQ(1, queryForTest.getCountUsingMemoizationDP());
    EXPECT_EQ(1, queryForTest.getCountUsingIterativeDP());
    EXPECT_EQ(1, queryForTest.getCountUsingIterativeDPAndSpaceEfficient());
    EXPECT_EQ(1, queryForTest.getCountBySearchingValuesWith1And9Increment());
}

TEST(CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSumTest, GetCountWorksOnExample1) {
    CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum queryForTest(2, 2);

    EXPECT_EQ(2, queryForTest.getCountUsingNaiveRecursion());
    EXPECT_EQ(2, queryForTest.getCountUsingMemoizationDP());
    EXPECT_EQ(2, queryForTest.getCountUsingIterativeDP());
    EXPECT_EQ(2, queryForTest.getCountUsingIterativeDPAndSpaceEfficient());
    EXPECT_EQ(2, queryForTest.getCountBySearchingValuesWith1And9Increment());
}

TEST(CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSumTest, GetCountWorksOnExample2) {
    CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum queryForTest(2, 5);

    EXPECT_EQ(5, queryForTest.getCountUsingNaiveRecursion());
    EXPECT_EQ(5, queryForTest.getCountUsingMemoizationDP());
    EXPECT_EQ(5, queryForTest.getCountUsingIterativeDP());
    EXPECT_EQ(5, queryForTest.getCountUsingIterativeDPAndSpaceEfficient());
    EXPECT_EQ(5, queryForTest.getCountBySearchingValuesWith1And9Increment());
}

TEST(CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSumTest, GetCountWorksOnExample3) {
    CountOfNDigitNumbersWhoseSumOfDigitsEqualsToGivenSum queryForTest(3, 6);

    EXPECT_EQ(21, queryForTest.getCountUsingNaiveRecursion());
    EXPECT_EQ(21, queryForTest.getCountUsingMemoizationDP());
    EXPECT_EQ(21, queryForTest.getCountUsingIterativeDP());
    EXPECT_EQ(21, queryForTest.getCountUsingIterativeDPAndSpaceEfficient());
    EXPECT_EQ(21, queryForTest.getCountBySearchingValuesWith1And9Increment());
}

}  // namespace alba
