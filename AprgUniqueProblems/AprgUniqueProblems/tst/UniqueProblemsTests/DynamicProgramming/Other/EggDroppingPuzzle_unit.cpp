#include <UniqueProblems/DynamicProgramming/Other/EggDroppingPuzzle.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba {
TEST(EggDroppingPuzzleTest, GetMinimumNumberOfOperationsWorksOnExample1) {
    EggDroppingPuzzle queryForTest(0, 0);

    EXPECT_EQ(0, queryForTest.getMinimumNumberOfTrialsUsingNaiveRecursion());
    EXPECT_EQ(0, queryForTest.getMinimumNumberOfTrialsUsingMemoizationDP());
    EXPECT_EQ(0, queryForTest.getMinimumNumberOfTrialsUsingIterativeDP());
}

TEST(EggDroppingPuzzleTest, GetMinimumNumberOfOperationsWorksOnExample2) {
    EggDroppingPuzzle queryForTest(1, 5);

    EXPECT_EQ(5, queryForTest.getMinimumNumberOfTrialsUsingNaiveRecursion());
    EXPECT_EQ(5, queryForTest.getMinimumNumberOfTrialsUsingMemoizationDP());
    EXPECT_EQ(5, queryForTest.getMinimumNumberOfTrialsUsingIterativeDP());
}

TEST(EggDroppingPuzzleTest, GetMinimumNumberOfOperationsWorksOnExample3) {
    EggDroppingPuzzle queryForTest(2, 10);

    EXPECT_EQ(4, queryForTest.getMinimumNumberOfTrialsUsingNaiveRecursion());
    EXPECT_EQ(4, queryForTest.getMinimumNumberOfTrialsUsingMemoizationDP());
    EXPECT_EQ(4, queryForTest.getMinimumNumberOfTrialsUsingIterativeDP());
}

TEST(EggDroppingPuzzleTest, GetMinimumNumberOfOperationsWorksOnExample4) {
    EggDroppingPuzzle queryForTest(2, 36);

    // EXPECT_EQ(8, queryForTest.getMinimumNumberOfTrialsUsingNaiveRecursion()); // too long
    EXPECT_EQ(8, queryForTest.getMinimumNumberOfTrialsUsingMemoizationDP());
    EXPECT_EQ(8, queryForTest.getMinimumNumberOfTrialsUsingIterativeDP());
}

}  // namespace alba
