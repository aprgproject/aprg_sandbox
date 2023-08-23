#include <UniqueProblems/DynamicProgramming/Math/Digits/TotalNumberOfNonDecreasingNumbersWithNDigits.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(TotalNumberOfNonDecreasingNumbersWithNDigitsTest, GetCountWorksOnExample1) {
    TotalNumberOfNonDecreasingNumbersWithNDigits queryForTest(0);

    EXPECT_EQ(0, queryForTest.getCountUsingNaiveRecursion());
    EXPECT_EQ(0, queryForTest.getCountUsingMemoizationDP());
    EXPECT_EQ(0, queryForTest.getCountUsingIterativeDP());
    EXPECT_EQ(0, queryForTest.getCountUsingIterativeDPAndSpaceEfficient());
    EXPECT_EQ(0, queryForTest.getCountUsingSummationFormula());
}

TEST(TotalNumberOfNonDecreasingNumbersWithNDigitsTest, GetCountWorksOnExample2) {
    TotalNumberOfNonDecreasingNumbersWithNDigits queryForTest(1);

    EXPECT_EQ(10, queryForTest.getCountUsingNaiveRecursion());
    EXPECT_EQ(10, queryForTest.getCountUsingMemoizationDP());
    EXPECT_EQ(10, queryForTest.getCountUsingIterativeDP());
    EXPECT_EQ(10, queryForTest.getCountUsingIterativeDPAndSpaceEfficient());
    EXPECT_EQ(10, queryForTest.getCountUsingSummationFormula());
}

TEST(TotalNumberOfNonDecreasingNumbersWithNDigitsTest, GetCountWorksOnExample3) {
    TotalNumberOfNonDecreasingNumbersWithNDigits queryForTest(2);

    EXPECT_EQ(55, queryForTest.getCountUsingNaiveRecursion());
    EXPECT_EQ(55, queryForTest.getCountUsingMemoizationDP());
    EXPECT_EQ(55, queryForTest.getCountUsingIterativeDP());
    EXPECT_EQ(55, queryForTest.getCountUsingIterativeDPAndSpaceEfficient());
    EXPECT_EQ(55, queryForTest.getCountUsingSummationFormula());
}

TEST(TotalNumberOfNonDecreasingNumbersWithNDigitsTest, GetCountWorksOnExample4) {
    TotalNumberOfNonDecreasingNumbersWithNDigits queryForTest(3);

    EXPECT_EQ(220, queryForTest.getCountUsingNaiveRecursion());
    EXPECT_EQ(220, queryForTest.getCountUsingMemoizationDP());
    EXPECT_EQ(220, queryForTest.getCountUsingIterativeDP());
    EXPECT_EQ(220, queryForTest.getCountUsingIterativeDPAndSpaceEfficient());
    EXPECT_EQ(220, queryForTest.getCountUsingSummationFormula());
}

TEST(TotalNumberOfNonDecreasingNumbersWithNDigitsTest, GetCountWorksOnExample5) {
    TotalNumberOfNonDecreasingNumbersWithNDigits queryForTest(10);

    EXPECT_EQ(92378, queryForTest.getCountUsingNaiveRecursion());
    EXPECT_EQ(92378, queryForTest.getCountUsingMemoizationDP());
    EXPECT_EQ(92378, queryForTest.getCountUsingIterativeDP());
    EXPECT_EQ(92378, queryForTest.getCountUsingIterativeDPAndSpaceEfficient());
    EXPECT_EQ(92378, queryForTest.getCountUsingSummationFormula());
}

}  // namespace alba
