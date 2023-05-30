#include <AprgUniqueProblems/DynamicProgramming/Other/BooleanParenthesizationProblem.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(BooleanParenthesizationProblemTest, GetNumberOfWaysForTrueWorksOnWrongArguments) {
    BooleanParenthesizationProblem queryForTest({true, false, true}, {'^'});

    EXPECT_EQ(0, queryForTest.getNumberOfWaysForTrueUsingNaiveRecursion());
    EXPECT_EQ(0, queryForTest.getNumberOfWaysForTrueUsingMemoizationDP());
    EXPECT_EQ(0, queryForTest.getNumberOfWaysForTrueUsingIterativeDP());
}

TEST(BooleanParenthesizationProblemTest, GetNumberOfWaysForTrueWorksOnExample1) {
    BooleanParenthesizationProblem queryForTest({true, false, true}, {'^', '&'});

    EXPECT_EQ(2, queryForTest.getNumberOfWaysForTrueUsingNaiveRecursion());
    EXPECT_EQ(2, queryForTest.getNumberOfWaysForTrueUsingMemoizationDP());
    EXPECT_EQ(2, queryForTest.getNumberOfWaysForTrueUsingIterativeDP());
}

TEST(BooleanParenthesizationProblemTest, GetNumberOfWaysForTrueWorksOnExample2) {
    BooleanParenthesizationProblem queryForTest({true, true, false, true}, {'|', '&', '^'});

    EXPECT_EQ(4, queryForTest.getNumberOfWaysForTrueUsingNaiveRecursion());
    EXPECT_EQ(4, queryForTest.getNumberOfWaysForTrueUsingMemoizationDP());
    EXPECT_EQ(4, queryForTest.getNumberOfWaysForTrueUsingIterativeDP());
}

}  // namespace alba
