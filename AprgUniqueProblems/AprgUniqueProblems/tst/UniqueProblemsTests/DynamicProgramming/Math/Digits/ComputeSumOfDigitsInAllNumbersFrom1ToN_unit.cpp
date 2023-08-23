#include <UniqueProblems/DynamicProgramming/Math/Digits/ComputeSumOfDigitsInAllNumbersFrom1ToN.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(ComputeSumOfDigitsInAllNumbersFrom1ToNTest, GetCountWorksOnZero) {
    ComputeSumOfDigitsInAllNumbersFrom1ToN queryForTest(0);

    EXPECT_EQ(0, queryForTest.getValueUsingNaiveSolution());
    EXPECT_EQ(0, queryForTest.getValueUsingMemoizationDP());
    EXPECT_EQ(0, queryForTest.getValueUsingSummationValues());
}

TEST(ComputeSumOfDigitsInAllNumbersFrom1ToNTest, GetCountWorksOnExample1) {
    ComputeSumOfDigitsInAllNumbersFrom1ToN queryForTest(5);

    EXPECT_EQ(15, queryForTest.getValueUsingNaiveSolution());
    EXPECT_EQ(15, queryForTest.getValueUsingMemoizationDP());
    EXPECT_EQ(15, queryForTest.getValueUsingSummationValues());
}

TEST(ComputeSumOfDigitsInAllNumbersFrom1ToNTest, GetCountWorksOnExample2) {
    ComputeSumOfDigitsInAllNumbersFrom1ToN queryForTest(12);

    EXPECT_EQ(51, queryForTest.getValueUsingNaiveSolution());
    EXPECT_EQ(51, queryForTest.getValueUsingMemoizationDP());
    EXPECT_EQ(51, queryForTest.getValueUsingSummationValues());
}

TEST(ComputeSumOfDigitsInAllNumbersFrom1ToNTest, GetCountWorksOnExample3) {
    ComputeSumOfDigitsInAllNumbersFrom1ToN queryForTest(28);

    EXPECT_EQ(154, queryForTest.getValueUsingNaiveSolution());
    EXPECT_EQ(154, queryForTest.getValueUsingMemoizationDP());
    EXPECT_EQ(154, queryForTest.getValueUsingSummationValues());
}

TEST(ComputeSumOfDigitsInAllNumbersFrom1ToNTest, GetCountWorksOnExample4) {
    ComputeSumOfDigitsInAllNumbersFrom1ToN queryForTest(328);

    EXPECT_EQ(3241, queryForTest.getValueUsingNaiveSolution());
    EXPECT_EQ(3241, queryForTest.getValueUsingMemoizationDP());
    EXPECT_EQ(3241, queryForTest.getValueUsingSummationValues());
}

TEST(ComputeSumOfDigitsInAllNumbersFrom1ToNTest, GetCountWorksOnExample5) {
    ComputeSumOfDigitsInAllNumbersFrom1ToN queryForTest(69446);

    EXPECT_EQ(1452882, queryForTest.getValueUsingNaiveSolution());
    EXPECT_EQ(1452882, queryForTest.getValueUsingMemoizationDP());
    EXPECT_EQ(1452882, queryForTest.getValueUsingSummationValues());
}

}  // namespace alba
