#include <AprgUniqueProblems/DynamicProgramming/Other/MobileNumericKeypadProblem.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(MobileNumericKeypadProblemTest, GetMinimumCostWorksOnExample1) {
    MobileNumericKeypadProblem queryForTest(1);

    EXPECT_EQ(10, queryForTest.getCountUsingNaiveRecursion());
    EXPECT_EQ(10, queryForTest.getCountUsingMemoizationDP());
    EXPECT_EQ(10, queryForTest.getCountUsingIterativeDP());
    EXPECT_EQ(10, queryForTest.getCountUsingIterativeDPAndSpaceEfficient());
}

TEST(MobileNumericKeypadProblemTest, GetMinimumCostWorksOnExample2) {
    MobileNumericKeypadProblem queryForTest(2);

    EXPECT_EQ(36, queryForTest.getCountUsingNaiveRecursion());
    EXPECT_EQ(36, queryForTest.getCountUsingMemoizationDP());
    EXPECT_EQ(36, queryForTest.getCountUsingIterativeDP());
    EXPECT_EQ(36, queryForTest.getCountUsingIterativeDPAndSpaceEfficient());
}

TEST(MobileNumericKeypadProblemTest, GetMinimumCostWorksOnExample3) {
    MobileNumericKeypadProblem queryForTest(10);

    EXPECT_EQ(1944059, queryForTest.getCountUsingNaiveRecursion());
    EXPECT_EQ(1944059, queryForTest.getCountUsingMemoizationDP());
    EXPECT_EQ(1944059, queryForTest.getCountUsingIterativeDP());
    EXPECT_EQ(1944059, queryForTest.getCountUsingIterativeDPAndSpaceEfficient());
}

}  // namespace alba
