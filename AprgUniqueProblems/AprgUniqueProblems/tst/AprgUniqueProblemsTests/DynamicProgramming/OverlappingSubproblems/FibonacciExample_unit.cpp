#include <AprgUniqueProblems/DynamicProgramming/OverlappingSubproblems/FibonacciExample.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(FibonacciExampleTest, GetNthFibonacciWorksOnExample1)
{
    FibonacciExample fibonacciExample;

    EXPECT_EQ(0U, fibonacciExample.getNthFibonacciUsingNaiveRecursion(0U));
    EXPECT_EQ(0U, fibonacciExample.getNthFibonacciUsingMemoizationDP(0U));
    EXPECT_EQ(0U, fibonacciExample.getNthFibonacciUsingTabularDP(0U));
    EXPECT_EQ(0U, fibonacciExample.getNthFibonacciUsingTabularDPAndSpaceEfficient(0U));
    EXPECT_EQ(0U, fibonacciExample.getNthFibonacciNumberUsingBinetsFormula(0U));
    EXPECT_EQ(0U, fibonacciExample.getNthFibonacciUsingMatrixMultiplication(0U));
    EXPECT_EQ(0U, fibonacciExample.getNthFibonacciUsingMatrixPowerWithLogarithmicTime(0U));
    EXPECT_EQ(0U, fibonacciExample.getNthFibonacciUsingLogarithmicMemoizationDP(0U));
    EXPECT_EQ(0U, fibonacciExample.getNthFibonacciUsingLogarithmicTabularDP(0U));
}

TEST(FibonacciExampleTest, GetNthFibonacciWorksOnExample2)
{
    FibonacciExample fibonacciExample;

    EXPECT_EQ(2U, fibonacciExample.getNthFibonacciUsingNaiveRecursion(3U));
    EXPECT_EQ(2U, fibonacciExample.getNthFibonacciUsingMemoizationDP(3U));
    EXPECT_EQ(2U, fibonacciExample.getNthFibonacciUsingTabularDP(3U));
    EXPECT_EQ(2U, fibonacciExample.getNthFibonacciUsingTabularDPAndSpaceEfficient(3U));
    EXPECT_EQ(2U, fibonacciExample.getNthFibonacciNumberUsingBinetsFormula(3U));
    EXPECT_EQ(2U, fibonacciExample.getNthFibonacciUsingMatrixMultiplication(3U));
    EXPECT_EQ(2U, fibonacciExample.getNthFibonacciUsingMatrixPowerWithLogarithmicTime(3U));
    EXPECT_EQ(2U, fibonacciExample.getNthFibonacciUsingLogarithmicMemoizationDP(3U));
    EXPECT_EQ(2U, fibonacciExample.getNthFibonacciUsingLogarithmicTabularDP(3U));
}

TEST(FibonacciExampleTest, GetNthFibonacciWorksOnExample3)
{
    FibonacciExample fibonacciExample;

    //EXPECT_EQ(102334155U, fibonacciExample.getNthFibonacciUsingNaiveRecursion(40U)); // takes too long
    EXPECT_EQ(102334155U, fibonacciExample.getNthFibonacciUsingMemoizationDP(40U));
    EXPECT_EQ(102334155U, fibonacciExample.getNthFibonacciUsingTabularDP(40U));
    EXPECT_EQ(102334155U, fibonacciExample.getNthFibonacciUsingTabularDPAndSpaceEfficient(40U));
    EXPECT_EQ(102334155U, fibonacciExample.getNthFibonacciNumberUsingBinetsFormula(40U));
    EXPECT_EQ(102334155U, fibonacciExample.getNthFibonacciUsingMatrixMultiplication(40U));
    EXPECT_EQ(102334155U, fibonacciExample.getNthFibonacciUsingMatrixPowerWithLogarithmicTime(40U));
    EXPECT_EQ(102334155U, fibonacciExample.getNthFibonacciUsingLogarithmicMemoizationDP(40U));
    EXPECT_EQ(102334155U, fibonacciExample.getNthFibonacciUsingLogarithmicTabularDP(40U));
}

}