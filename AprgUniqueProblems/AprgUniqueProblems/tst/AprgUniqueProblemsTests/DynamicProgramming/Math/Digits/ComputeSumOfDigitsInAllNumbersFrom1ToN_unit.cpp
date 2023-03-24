#include <AprgUniqueProblems/DynamicProgramming/Math/Digits/ComputeSumOfDigitsInAllNumbersFrom1ToN.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(ComputeSumOfDigitsInAllNumbersFrom1ToNTest, GetCountWorksOnZero)
{
    ComputeSumOfDigitsInAllNumbersFrom1ToN queryForTest(0U);

    EXPECT_EQ(0U, queryForTest.getValueUsingNaiveSolution());
    EXPECT_EQ(0U, queryForTest.getValueUsingMemoizationDP());
    EXPECT_EQ(0U, queryForTest.getValueUsingSummationValues());
}

TEST(ComputeSumOfDigitsInAllNumbersFrom1ToNTest, GetCountWorksOnExample1)
{
    ComputeSumOfDigitsInAllNumbersFrom1ToN queryForTest(5U);

    EXPECT_EQ(15U, queryForTest.getValueUsingNaiveSolution());
    EXPECT_EQ(15U, queryForTest.getValueUsingMemoizationDP());
    EXPECT_EQ(15U, queryForTest.getValueUsingSummationValues());
}

TEST(ComputeSumOfDigitsInAllNumbersFrom1ToNTest, GetCountWorksOnExample2)
{
    ComputeSumOfDigitsInAllNumbersFrom1ToN queryForTest(12U);

    EXPECT_EQ(51U, queryForTest.getValueUsingNaiveSolution());
    EXPECT_EQ(51U, queryForTest.getValueUsingMemoizationDP());
    EXPECT_EQ(51U, queryForTest.getValueUsingSummationValues());
}

TEST(ComputeSumOfDigitsInAllNumbersFrom1ToNTest, GetCountWorksOnExample3)
{
    ComputeSumOfDigitsInAllNumbersFrom1ToN queryForTest(28U);

    EXPECT_EQ(154U, queryForTest.getValueUsingNaiveSolution());
    EXPECT_EQ(154U, queryForTest.getValueUsingMemoizationDP());
    EXPECT_EQ(154U, queryForTest.getValueUsingSummationValues());
}

TEST(ComputeSumOfDigitsInAllNumbersFrom1ToNTest, GetCountWorksOnExample4)
{
    ComputeSumOfDigitsInAllNumbersFrom1ToN queryForTest(328U);

    EXPECT_EQ(3241U, queryForTest.getValueUsingNaiveSolution());
    EXPECT_EQ(3241U, queryForTest.getValueUsingMemoizationDP());
    EXPECT_EQ(3241U, queryForTest.getValueUsingSummationValues());
}

TEST(ComputeSumOfDigitsInAllNumbersFrom1ToNTest, GetCountWorksOnExample5)
{
    ComputeSumOfDigitsInAllNumbersFrom1ToN queryForTest(69446U);

    EXPECT_EQ(1452882U, queryForTest.getValueUsingNaiveSolution());
    EXPECT_EQ(1452882U, queryForTest.getValueUsingMemoizationDP());
    EXPECT_EQ(1452882U, queryForTest.getValueUsingSummationValues());
}

}
