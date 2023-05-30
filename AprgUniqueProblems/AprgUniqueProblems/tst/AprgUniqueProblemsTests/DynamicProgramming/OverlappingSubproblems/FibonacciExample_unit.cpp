#include <AprgUniqueProblems/DynamicProgramming/OverlappingSubproblems/FibonacciExample.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(FibonacciExampleTest, GetNthFibonacciWorksOnExample1) {
    FibonacciExample fibonacciExample;

    EXPECT_EQ(0, fibonacciExample.getNthFibonacciUsingNaiveRecursion(0));
    EXPECT_EQ(0, fibonacciExample.getNthFibonacciUsingMemoizationDP(0));
    EXPECT_EQ(0, fibonacciExample.getNthFibonacciUsingIterativeDP(0));
    EXPECT_EQ(0, fibonacciExample.getNthFibonacciUsingIterativeDPAndSpaceEfficient(0));
    EXPECT_EQ(0, fibonacciExample.getNthFibonacciNumberUsingBinetsFormula(0));
    EXPECT_EQ(0, fibonacciExample.getNthFibonacciUsingMatrixMultiplication(0));
    EXPECT_EQ(0, fibonacciExample.getNthFibonacciUsingMatrixPowerWithLogarithmicTime(0));
    EXPECT_EQ(0, fibonacciExample.getNthFibonacciUsingLogarithmicMemoizationDP(0));
    EXPECT_EQ(0, fibonacciExample.getNthFibonacciUsingLogarithmicIterativeDP(0));
}

TEST(FibonacciExampleTest, GetNthFibonacciWorksOnExample2) {
    FibonacciExample fibonacciExample;

    EXPECT_EQ(2, fibonacciExample.getNthFibonacciUsingNaiveRecursion(3));
    EXPECT_EQ(2, fibonacciExample.getNthFibonacciUsingMemoizationDP(3));
    EXPECT_EQ(2, fibonacciExample.getNthFibonacciUsingIterativeDP(3));
    EXPECT_EQ(2, fibonacciExample.getNthFibonacciUsingIterativeDPAndSpaceEfficient(3));
    EXPECT_EQ(2, fibonacciExample.getNthFibonacciNumberUsingBinetsFormula(3));
    EXPECT_EQ(2, fibonacciExample.getNthFibonacciUsingMatrixMultiplication(3));
    EXPECT_EQ(2, fibonacciExample.getNthFibonacciUsingMatrixPowerWithLogarithmicTime(3));
    EXPECT_EQ(2, fibonacciExample.getNthFibonacciUsingLogarithmicMemoizationDP(3));
    EXPECT_EQ(2, fibonacciExample.getNthFibonacciUsingLogarithmicIterativeDP(3));
}

TEST(FibonacciExampleTest, GetNthFibonacciWorksOnExample3) {
    FibonacciExample fibonacciExample;

    // EXPECT_EQ(102334155, fibonacciExample.getNthFibonacciUsingNaiveRecursion(40)); // takes too long
    EXPECT_EQ(102334155, fibonacciExample.getNthFibonacciUsingMemoizationDP(40));
    EXPECT_EQ(102334155, fibonacciExample.getNthFibonacciUsingIterativeDP(40));
    EXPECT_EQ(102334155, fibonacciExample.getNthFibonacciUsingIterativeDPAndSpaceEfficient(40));
    EXPECT_EQ(102334155, fibonacciExample.getNthFibonacciNumberUsingBinetsFormula(40));
    EXPECT_EQ(102334155, fibonacciExample.getNthFibonacciUsingMatrixMultiplication(40));
    EXPECT_EQ(102334155, fibonacciExample.getNthFibonacciUsingMatrixPowerWithLogarithmicTime(40));
    EXPECT_EQ(102334155, fibonacciExample.getNthFibonacciUsingLogarithmicMemoizationDP(40));
    EXPECT_EQ(102334155, fibonacciExample.getNthFibonacciUsingLogarithmicIterativeDP(40));
}

}  // namespace alba
