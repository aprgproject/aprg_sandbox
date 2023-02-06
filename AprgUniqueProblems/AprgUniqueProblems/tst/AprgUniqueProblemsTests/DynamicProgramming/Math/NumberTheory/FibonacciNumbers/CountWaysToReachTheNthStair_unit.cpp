#include <AprgUniqueProblems/DynamicProgramming/Math/NumberTheory/FibonacciProblems/CountWaysToReachTheNthStair.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(CountWaysToReachTheNthStairTest, GetCountWorksOnExample1)
{
    CountWaysToReachTheNthStair queryForTest(1U);

    EXPECT_EQ(1U, queryForTest.getCountUsingFibonacci());
}

TEST(CountWaysToReachTheNthStairTest, GetCountWorksOnExample2)
{
    CountWaysToReachTheNthStair queryForTest(2U);

    EXPECT_EQ(2U, queryForTest.getCountUsingFibonacci());
}

TEST(CountWaysToReachTheNthStairTest, GetCountWorksOnExample3)
{
    CountWaysToReachTheNthStair queryForTest(4U);

    EXPECT_EQ(5U, queryForTest.getCountUsingFibonacci());
}

TEST(CountWaysToReachTheNthStairTest, GetCountWorksOnExample4)
{
    CountWaysToReachTheNthStair queryForTest(10U);

    EXPECT_EQ(89U, queryForTest.getCountUsingFibonacci());
}


}
