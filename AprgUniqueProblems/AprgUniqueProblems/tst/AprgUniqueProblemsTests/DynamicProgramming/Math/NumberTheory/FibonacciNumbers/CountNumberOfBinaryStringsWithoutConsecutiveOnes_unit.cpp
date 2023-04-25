#include <AprgUniqueProblems/DynamicProgramming/Math/NumberTheory/FibonacciProblems/CountNumberOfBinaryStringsWithoutConsecutiveOnes.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(CountNumberOfBinaryStringsWithoutConsecutiveOnesTest, GetCountWorksOnExample1) {
    CountNumberOfBinaryStringsWithoutConsecutiveOnes queryForTest(1U);

    EXPECT_EQ(2U, queryForTest.getCountUsingNaiveRecursion());
    EXPECT_EQ(2U, queryForTest.getCountUsingIterativeDP());
    EXPECT_EQ(2U, queryForTest.getCountUsingIterativeDPAndSpaceEfficient());
    EXPECT_EQ(2U, queryForTest.getCountUsingFibonacci());
}

TEST(CountNumberOfBinaryStringsWithoutConsecutiveOnesTest, GetCountWorksOnExample2) {
    CountNumberOfBinaryStringsWithoutConsecutiveOnes queryForTest(2U);

    EXPECT_EQ(3U, queryForTest.getCountUsingNaiveRecursion());
    EXPECT_EQ(3U, queryForTest.getCountUsingIterativeDP());
    EXPECT_EQ(3U, queryForTest.getCountUsingIterativeDPAndSpaceEfficient());
    EXPECT_EQ(3U, queryForTest.getCountUsingFibonacci());
}

TEST(CountNumberOfBinaryStringsWithoutConsecutiveOnesTest, GetCountWorksOnExample3) {
    CountNumberOfBinaryStringsWithoutConsecutiveOnes queryForTest(3U);

    EXPECT_EQ(5U, queryForTest.getCountUsingNaiveRecursion());
    EXPECT_EQ(5U, queryForTest.getCountUsingIterativeDP());
    EXPECT_EQ(5U, queryForTest.getCountUsingIterativeDPAndSpaceEfficient());
    EXPECT_EQ(5U, queryForTest.getCountUsingFibonacci());
}

TEST(CountNumberOfBinaryStringsWithoutConsecutiveOnesTest, GetCountWorksOnExample4) {
    CountNumberOfBinaryStringsWithoutConsecutiveOnes queryForTest(10U);

    EXPECT_EQ(144U, queryForTest.getCountUsingNaiveRecursion());
    EXPECT_EQ(144U, queryForTest.getCountUsingIterativeDP());
    EXPECT_EQ(144U, queryForTest.getCountUsingIterativeDPAndSpaceEfficient());
    EXPECT_EQ(144U, queryForTest.getCountUsingFibonacci());
}

}  // namespace alba
