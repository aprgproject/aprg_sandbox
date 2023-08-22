#include <UniqueProblems/DynamicProgramming/Math/MinimumNumberOfSquaresWithSumEqualToN.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba {
TEST(MinimumNumberOfSquaresWithSumEqualToNTest, GetCountWorksOnZero) {
    MinimumNumberOfSquaresWithSumEqualToN queryForTest(0);

    EXPECT_EQ(0, queryForTest.getMinimumCountUsingNaiveRecursion());
    EXPECT_EQ(0, queryForTest.getMinimumCountUsingMemoizationDP());
    EXPECT_EQ(0, queryForTest.getMinimumCountUsingIterativeDP());
    EXPECT_EQ(0, queryForTest.getMinimumCountUsingBfs());
    EXPECT_EQ(
        1, queryForTest.getMinimumCountUsingFewestCoins());  // Answer is 1 because we are using the CoinProblem class
}

TEST(MinimumNumberOfSquaresWithSumEqualToNTest, GetCountWorksOnOne) {
    MinimumNumberOfSquaresWithSumEqualToN queryForTest(1);

    EXPECT_EQ(1, queryForTest.getMinimumCountUsingNaiveRecursion());
    EXPECT_EQ(1, queryForTest.getMinimumCountUsingMemoizationDP());
    EXPECT_EQ(1, queryForTest.getMinimumCountUsingIterativeDP());
    EXPECT_EQ(1, queryForTest.getMinimumCountUsingBfs());
    EXPECT_EQ(1, queryForTest.getMinimumCountUsingFewestCoins());
}

TEST(MinimumNumberOfSquaresWithSumEqualToNTest, GetCountWorksOnAnExactSquare) {
    MinimumNumberOfSquaresWithSumEqualToN queryForTest(100);

    EXPECT_EQ(1, queryForTest.getMinimumCountUsingNaiveRecursion());
    EXPECT_EQ(1, queryForTest.getMinimumCountUsingMemoizationDP());
    EXPECT_EQ(1, queryForTest.getMinimumCountUsingIterativeDP());
    EXPECT_EQ(1, queryForTest.getMinimumCountUsingBfs());
    EXPECT_EQ(1, queryForTest.getMinimumCountUsingFewestCoins());
}

TEST(MinimumNumberOfSquaresWithSumEqualToNTest, GetCountWorksOnExample1) {
    MinimumNumberOfSquaresWithSumEqualToN queryForTest(6);

    EXPECT_EQ(3, queryForTest.getMinimumCountUsingNaiveRecursion());
    EXPECT_EQ(3, queryForTest.getMinimumCountUsingMemoizationDP());
    EXPECT_EQ(3, queryForTest.getMinimumCountUsingIterativeDP());
    EXPECT_EQ(3, queryForTest.getMinimumCountUsingBfs());
    EXPECT_EQ(3, queryForTest.getMinimumCountUsingFewestCoins());
}

TEST(MinimumNumberOfSquaresWithSumEqualToNTest, GetCountWorksOnExample2) {
    MinimumNumberOfSquaresWithSumEqualToN queryForTest(47);

    EXPECT_EQ(4, queryForTest.getMinimumCountUsingNaiveRecursion());
    EXPECT_EQ(4, queryForTest.getMinimumCountUsingMemoizationDP());
    EXPECT_EQ(4, queryForTest.getMinimumCountUsingIterativeDP());
    EXPECT_EQ(4, queryForTest.getMinimumCountUsingBfs());
    EXPECT_EQ(4, queryForTest.getMinimumCountUsingFewestCoins());
}

}  // namespace alba
