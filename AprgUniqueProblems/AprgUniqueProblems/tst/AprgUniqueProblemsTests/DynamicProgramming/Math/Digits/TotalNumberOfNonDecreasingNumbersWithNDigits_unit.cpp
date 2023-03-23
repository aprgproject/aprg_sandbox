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
    EXPECT_EQ(0U, queryForTest.getCountUsingIterativeDP());
    EXPECT_EQ(0U, queryForTest.getCountUsingIterativeDPAndSpaceEfficient());
    EXPECT_EQ(0U, queryForTest.getCountUsingSummationFormula());
}
TEST(TotalNumberOfNonDecreasingNumbersWithNDigitsTest, GetCountWorksOnExample2)
{
    TotalNumberOfNonDecreasingNumbersWithNDigits queryForTest(1U);

    EXPECT_EQ(10U, queryForTest.getCountUsingNaiveRecursion());
    EXPECT_EQ(10U, queryForTest.getCountUsingMemoizationDP());
    EXPECT_EQ(10U, queryForTest.getCountUsingIterativeDP());
    EXPECT_EQ(10U, queryForTest.getCountUsingIterativeDPAndSpaceEfficient());
    EXPECT_EQ(10U, queryForTest.getCountUsingSummationFormula());
}
TEST(TotalNumberOfNonDecreasingNumbersWithNDigitsTest, GetCountWorksOnExample3)
{
    TotalNumberOfNonDecreasingNumbersWithNDigits queryForTest(2U);

    EXPECT_EQ(55U, queryForTest.getCountUsingNaiveRecursion());
    EXPECT_EQ(55U, queryForTest.getCountUsingMemoizationDP());
    EXPECT_EQ(55U, queryForTest.getCountUsingIterativeDP());
    EXPECT_EQ(55U, queryForTest.getCountUsingIterativeDPAndSpaceEfficient());
    EXPECT_EQ(55U, queryForTest.getCountUsingSummationFormula());
}
TEST(TotalNumberOfNonDecreasingNumbersWithNDigitsTest, GetCountWorksOnExample4)
{
    TotalNumberOfNonDecreasingNumbersWithNDigits queryForTest(3U);

    EXPECT_EQ(220U, queryForTest.getCountUsingNaiveRecursion());
    EXPECT_EQ(220U, queryForTest.getCountUsingMemoizationDP());
    EXPECT_EQ(220U, queryForTest.getCountUsingIterativeDP());
    EXPECT_EQ(220U, queryForTest.getCountUsingIterativeDPAndSpaceEfficient());
    EXPECT_EQ(220U, queryForTest.getCountUsingSummationFormula());
}
TEST(TotalNumberOfNonDecreasingNumbersWithNDigitsTest, GetCountWorksOnExample5)
{
    TotalNumberOfNonDecreasingNumbersWithNDigits queryForTest(10U);

    EXPECT_EQ(92378U, queryForTest.getCountUsingNaiveRecursion());
    EXPECT_EQ(92378U, queryForTest.getCountUsingMemoizationDP());
    EXPECT_EQ(92378U, queryForTest.getCountUsingIterativeDP());
    EXPECT_EQ(92378U, queryForTest.getCountUsingIterativeDPAndSpaceEfficient());
    EXPECT_EQ(92378U, queryForTest.getCountUsingSummationFormula());
}
}
