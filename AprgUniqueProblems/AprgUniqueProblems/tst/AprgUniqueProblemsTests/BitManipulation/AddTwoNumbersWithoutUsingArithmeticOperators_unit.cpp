#include <AprgUniqueProblems/BitManipulation/AddTwoNumbersWithoutUsingArithmeticOperators.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(AddTwoNumbersWithoutUsingArithmeticOperatorsTest, GetSumWorksOnExample1) {
    AddTwoNumbersWithoutUsingArithmeticOperators solution;

    EXPECT_EQ(0U, solution.getSum(0U, 0U));
    EXPECT_EQ(1U, solution.getSum(0U, 1U));
    EXPECT_EQ(1U, solution.getSum(1U, 0U));
    EXPECT_EQ(2U, solution.getSum(1U, 1U));
    EXPECT_EQ(9U, solution.getSum(4U, 5U));
    EXPECT_EQ(9U, solution.getSum(5U, 4U));
    EXPECT_EQ(173U, solution.getSum(78U, 95U));
}

}  // namespace alba
