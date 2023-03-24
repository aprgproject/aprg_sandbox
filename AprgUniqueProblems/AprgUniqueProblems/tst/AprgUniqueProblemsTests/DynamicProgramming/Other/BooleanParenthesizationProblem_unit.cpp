#include <AprgUniqueProblems/DynamicProgramming/Other/BooleanParenthesizationProblem.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(BooleanParenthesizationProblemTest, GetNumberOfWaysForTrueWorksOnWrongArguments)
{
    BooleanParenthesizationProblem queryForTest({true, false, true}, {'^'});

    EXPECT_EQ(0U, queryForTest.getNumberOfWaysForTrueUsingNaiveRecursion());
    EXPECT_EQ(0U, queryForTest.getNumberOfWaysForTrueUsingMemoizationDP());
    EXPECT_EQ(0U, queryForTest.getNumberOfWaysForTrueUsingIterativeDP());
}

TEST(BooleanParenthesizationProblemTest, GetNumberOfWaysForTrueWorksOnExample1)
{
    BooleanParenthesizationProblem queryForTest({true, false, true}, {'^', '&'});

    EXPECT_EQ(2U, queryForTest.getNumberOfWaysForTrueUsingNaiveRecursion());
    EXPECT_EQ(2U, queryForTest.getNumberOfWaysForTrueUsingMemoizationDP());
    EXPECT_EQ(2U, queryForTest.getNumberOfWaysForTrueUsingIterativeDP());
}

TEST(BooleanParenthesizationProblemTest, GetNumberOfWaysForTrueWorksOnExample2)
{
    BooleanParenthesizationProblem queryForTest({true, true, false, true}, {'|', '&', '^'});

    EXPECT_EQ(4U, queryForTest.getNumberOfWaysForTrueUsingNaiveRecursion());
    EXPECT_EQ(4U, queryForTest.getNumberOfWaysForTrueUsingMemoizationDP());
    EXPECT_EQ(4U, queryForTest.getNumberOfWaysForTrueUsingIterativeDP());
}

}
