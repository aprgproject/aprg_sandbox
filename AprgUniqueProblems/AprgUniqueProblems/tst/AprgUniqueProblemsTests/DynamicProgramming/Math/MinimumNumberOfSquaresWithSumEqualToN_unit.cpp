#include <AprgUniqueProblems/DynamicProgramming/Math/MinimumNumberOfSquaresWithSumEqualToN.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(MinimumNumberOfSquaresWithSumEqualToNTest, GetCountWorksOnZero) {
    MinimumNumberOfSquaresWithSumEqualToN queryForTest(0U);

    EXPECT_EQ(0U, queryForTest.getMinimumCountUsingNaiveRecursion());
    EXPECT_EQ(0U, queryForTest.getMinimumCountUsingMemoizationDP());
    EXPECT_EQ(0U, queryForTest.getMinimumCountUsingIterativeDP());
    EXPECT_EQ(0U, queryForTest.getMinimumCountUsingBfs());
    EXPECT_EQ(
        1U, queryForTest.getMinimumCountUsingFewestCoins());  // Answer is 1 because we are using the CoinProblem class
}

TEST(MinimumNumberOfSquaresWithSumEqualToNTest, GetCountWorksOnOne) {
    MinimumNumberOfSquaresWithSumEqualToN queryForTest(1U);

    EXPECT_EQ(1U, queryForTest.getMinimumCountUsingNaiveRecursion());
    EXPECT_EQ(1U, queryForTest.getMinimumCountUsingMemoizationDP());
    EXPECT_EQ(1U, queryForTest.getMinimumCountUsingIterativeDP());
    EXPECT_EQ(1U, queryForTest.getMinimumCountUsingBfs());
    EXPECT_EQ(1U, queryForTest.getMinimumCountUsingFewestCoins());
}

TEST(MinimumNumberOfSquaresWithSumEqualToNTest, GetCountWorksOnAnExactSquare) {
    MinimumNumberOfSquaresWithSumEqualToN queryForTest(100U);

    EXPECT_EQ(1U, queryForTest.getMinimumCountUsingNaiveRecursion());
    EXPECT_EQ(1U, queryForTest.getMinimumCountUsingMemoizationDP());
    EXPECT_EQ(1U, queryForTest.getMinimumCountUsingIterativeDP());
    EXPECT_EQ(1U, queryForTest.getMinimumCountUsingBfs());
    EXPECT_EQ(1U, queryForTest.getMinimumCountUsingFewestCoins());
}

TEST(MinimumNumberOfSquaresWithSumEqualToNTest, GetCountWorksOnExample1) {
    MinimumNumberOfSquaresWithSumEqualToN queryForTest(6U);

    EXPECT_EQ(3U, queryForTest.getMinimumCountUsingNaiveRecursion());
    EXPECT_EQ(3U, queryForTest.getMinimumCountUsingMemoizationDP());
    EXPECT_EQ(3U, queryForTest.getMinimumCountUsingIterativeDP());
    EXPECT_EQ(3U, queryForTest.getMinimumCountUsingBfs());
    EXPECT_EQ(3U, queryForTest.getMinimumCountUsingFewestCoins());
}

TEST(MinimumNumberOfSquaresWithSumEqualToNTest, GetCountWorksOnExample2) {
    MinimumNumberOfSquaresWithSumEqualToN queryForTest(47U);

    EXPECT_EQ(4U, queryForTest.getMinimumCountUsingNaiveRecursion());
    EXPECT_EQ(4U, queryForTest.getMinimumCountUsingMemoizationDP());
    EXPECT_EQ(4U, queryForTest.getMinimumCountUsingIterativeDP());
    EXPECT_EQ(4U, queryForTest.getMinimumCountUsingBfs());
    EXPECT_EQ(4U, queryForTest.getMinimumCountUsingFewestCoins());
}

}  // namespace alba
