#include <AprgUniqueProblems/DynamicProgramming/Other/EggDroppingPuzzle.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(EggDroppingPuzzleTest, GetMinimumNumberOfOperationsWorksOnExample1)
{
    EggDroppingPuzzle queryForTest(0U, 0U);

    EXPECT_EQ(0U, queryForTest.getMinimumNumberOfTrialsUsingNaiveRecursion());
    EXPECT_EQ(0U, queryForTest.getMinimumNumberOfTrialsUsingMemoizationDP());
    EXPECT_EQ(0U, queryForTest.getMinimumNumberOfTrialsUsingIterativeDP());
}

TEST(EggDroppingPuzzleTest, GetMinimumNumberOfOperationsWorksOnExample2){
    EggDroppingPuzzle queryForTest(1U, 5U);

    EXPECT_EQ(5U, queryForTest.getMinimumNumberOfTrialsUsingNaiveRecursion());
    EXPECT_EQ(5U, queryForTest.getMinimumNumberOfTrialsUsingMemoizationDP());
    EXPECT_EQ(5U, queryForTest.getMinimumNumberOfTrialsUsingIterativeDP());
}

TEST(EggDroppingPuzzleTest, GetMinimumNumberOfOperationsWorksOnExample3){
    EggDroppingPuzzle queryForTest(2U, 10U);

    EXPECT_EQ(4U, queryForTest.getMinimumNumberOfTrialsUsingNaiveRecursion());
    EXPECT_EQ(4U, queryForTest.getMinimumNumberOfTrialsUsingMemoizationDP());
    EXPECT_EQ(4U, queryForTest.getMinimumNumberOfTrialsUsingIterativeDP());
}

TEST(EggDroppingPuzzleTest, GetMinimumNumberOfOperationsWorksOnExample4){
    EggDroppingPuzzle queryForTest(2U, 36U);

    //EXPECT_EQ(8U, queryForTest.getMinimumNumberOfTrialsUsingNaiveRecursion()); // too long
    EXPECT_EQ(8U, queryForTest.getMinimumNumberOfTrialsUsingMemoizationDP());
    EXPECT_EQ(8U, queryForTest.getMinimumNumberOfTrialsUsingIterativeDP());
}

}