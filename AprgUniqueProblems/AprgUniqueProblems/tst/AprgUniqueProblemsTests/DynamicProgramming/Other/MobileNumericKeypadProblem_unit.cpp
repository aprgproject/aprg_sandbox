#include <AprgUniqueProblems/DynamicProgramming/Other/MobileNumericKeypadProblem.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(MobileNumericKeypadProblemTest, GetMinimumCostWorksOnExample1)
{
    MobileNumericKeypadProblem queryForTest(1);

    EXPECT_EQ(10U, queryForTest.getCountUsingNaiveRecursion());
    EXPECT_EQ(10U, queryForTest.getCountUsingMemoizationDP());
    EXPECT_EQ(10U, queryForTest.getCountUsingTabularDP());
    EXPECT_EQ(10U, queryForTest.getCountUsingTabularDPAndSpaceEfficient());
}
TEST(MobileNumericKeypadProblemTest, GetMinimumCostWorksOnExample2)
{
    MobileNumericKeypadProblem queryForTest(2);

    EXPECT_EQ(36U, queryForTest.getCountUsingNaiveRecursion());
    EXPECT_EQ(36U, queryForTest.getCountUsingMemoizationDP());
    EXPECT_EQ(36U, queryForTest.getCountUsingTabularDP());
    EXPECT_EQ(36U, queryForTest.getCountUsingTabularDPAndSpaceEfficient());
}
TEST(MobileNumericKeypadProblemTest, GetMinimumCostWorksOnExample3)
{
    MobileNumericKeypadProblem queryForTest(10);

    EXPECT_EQ(1944059U, queryForTest.getCountUsingNaiveRecursion());
    EXPECT_EQ(1944059U, queryForTest.getCountUsingMemoizationDP());
    EXPECT_EQ(1944059U, queryForTest.getCountUsingTabularDP());
    EXPECT_EQ(1944059U, queryForTest.getCountUsingTabularDPAndSpaceEfficient());
}
}