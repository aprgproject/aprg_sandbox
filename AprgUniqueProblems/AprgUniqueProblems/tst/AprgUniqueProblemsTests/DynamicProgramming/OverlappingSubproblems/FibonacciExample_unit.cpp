#include <AprgUniqueProblems/DynamicProgramming/OverlappingSubproblems/FibonacciExample.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(FibonacciExampleTest, DISABLED_GetFibonacciUsingRecursionWorks) // takes too long
{
    FibonacciExample fibonacciExample;

    EXPECT_EQ(102334155U, fibonacciExample.getFibonacciUsingRecursion(40U));
}

TEST(FibonacciExampleTest, GetFibonacciUsingMemoizationWorks)
{
    FibonacciExample fibonacciExample;

    EXPECT_EQ(102334155U, fibonacciExample.getFibonacciUsingMemoization(40U));
}

TEST(FibonacciExampleTest, GetFibonacciUsingTabulationWorks)
{
    FibonacciExample fibonacciExample;

    EXPECT_EQ(102334155U, fibonacciExample.getFibonacciUsingTabulation(40U));
}

}
