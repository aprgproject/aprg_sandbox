#include <AprgUniqueProblems/DynamicProgramming/Other/PrintMaximumNumberOfAs.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(PrintMaximumNumberOfAsTest, GetMaxCountOfAOnScreenOnZero) {
    PrintMaximumNumberOfAs queryForTest(0);

    EXPECT_EQ(0, queryForTest.getMaxCountOfAOnScreenUsingNaiveRecursion());
    EXPECT_EQ(0, queryForTest.getMaxCountOfAOnScreenUsingMemoizationDP());
    EXPECT_EQ(0, queryForTest.getMaxCountOfAOnScreenUsingIterativeDP());
    EXPECT_EQ(0, queryForTest.getMaxCountOfAOnScreenUsingIterativeDPAndSpaceEfficient());
}

TEST(PrintMaximumNumberOfAsTest, GetMaxCountOfAOnScreenOnExample1) {
    PrintMaximumNumberOfAs queryForTest(1);

    EXPECT_EQ(1, queryForTest.getMaxCountOfAOnScreenUsingNaiveRecursion());
    EXPECT_EQ(1, queryForTest.getMaxCountOfAOnScreenUsingMemoizationDP());
    EXPECT_EQ(1, queryForTest.getMaxCountOfAOnScreenUsingIterativeDP());
    EXPECT_EQ(1, queryForTest.getMaxCountOfAOnScreenUsingIterativeDPAndSpaceEfficient());
}

TEST(PrintMaximumNumberOfAsTest, GetMaxCountOfAOnScreenOnExample2) {
    PrintMaximumNumberOfAs queryForTest(3);

    EXPECT_EQ(3, queryForTest.getMaxCountOfAOnScreenUsingNaiveRecursion());
    EXPECT_EQ(3, queryForTest.getMaxCountOfAOnScreenUsingMemoizationDP());
    EXPECT_EQ(3, queryForTest.getMaxCountOfAOnScreenUsingIterativeDP());
    EXPECT_EQ(3, queryForTest.getMaxCountOfAOnScreenUsingIterativeDPAndSpaceEfficient());
}

TEST(PrintMaximumNumberOfAsTest, GetMaxCountOfAOnScreenOnExample3) {
    PrintMaximumNumberOfAs queryForTest(7);

    EXPECT_EQ(9, queryForTest.getMaxCountOfAOnScreenUsingNaiveRecursion());
    EXPECT_EQ(9, queryForTest.getMaxCountOfAOnScreenUsingMemoizationDP());
    EXPECT_EQ(9, queryForTest.getMaxCountOfAOnScreenUsingIterativeDP());
    EXPECT_EQ(9, queryForTest.getMaxCountOfAOnScreenUsingIterativeDPAndSpaceEfficient());
}

TEST(PrintMaximumNumberOfAsTest, GetMaxCountOfAOnScreenOnExample4) {
    PrintMaximumNumberOfAs queryForTest(11);

    // EXPECT_EQ(27, queryForTest.getMaxCountOfAOnScreenUsingNaiveRecursion()); // too long
    EXPECT_EQ(27, queryForTest.getMaxCountOfAOnScreenUsingMemoizationDP());
    EXPECT_EQ(27, queryForTest.getMaxCountOfAOnScreenUsingIterativeDP());
    EXPECT_EQ(27, queryForTest.getMaxCountOfAOnScreenUsingIterativeDPAndSpaceEfficient());
}

}  // namespace alba
