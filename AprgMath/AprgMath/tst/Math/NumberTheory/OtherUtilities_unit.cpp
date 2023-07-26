#include <Math/NumberTheory/OtherUtilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace math {

TEST(OtherUtilitiesTest, IsFibonacciNumberWorks) {
    // Is zero really a fibonacci number? Yes! the definitions says so.
    EXPECT_TRUE(isAFibonacciNumber(0U));
    EXPECT_TRUE(isAFibonacciNumber(1U));
    EXPECT_TRUE(isAFibonacciNumber(2U));
    EXPECT_TRUE(isAFibonacciNumber(3U));
    EXPECT_FALSE(isAFibonacciNumber(4U));
    EXPECT_TRUE(isAFibonacciNumber(21U));
    EXPECT_TRUE(isAFibonacciNumber(34U));
    EXPECT_FALSE(isAFibonacciNumber(35U));
}

TEST(OtherUtilitiesTest, IsALuckyNumberWorks) {
    EXPECT_FALSE(isALuckyNumber(0U));
    EXPECT_TRUE(isALuckyNumber(1U));
    EXPECT_FALSE(isALuckyNumber(2U));
    EXPECT_TRUE(isALuckyNumber(3U));
    EXPECT_FALSE(isALuckyNumber(4U));
    EXPECT_FALSE(isALuckyNumber(12U));
    EXPECT_TRUE(isALuckyNumber(13U));
    EXPECT_FALSE(isALuckyNumber(14U));
}

TEST(OtherUtilitiesTest, IsLagrangeTheoremTrueWorks) {
    EXPECT_TRUE(isLagrangeTheoremTrue(13U));
    EXPECT_TRUE(isLagrangeTheoremTrue(64U));
    EXPECT_TRUE(isLagrangeTheoremTrue(65U));
    EXPECT_TRUE(isLagrangeTheoremTrue(84U));
}

TEST(OtherUtilitiesTest, IsZeckendorfTheoremTrueWorks) {
    EXPECT_TRUE(isZeckendorfTheoremTrue(13U));
    EXPECT_TRUE(isZeckendorfTheoremTrue(64U));
    EXPECT_TRUE(isZeckendorfTheoremTrue(65U));
    EXPECT_TRUE(isZeckendorfTheoremTrue(84U));
}

TEST(OtherUtilitiesTest, GetNthFibonacciNumberWorks) {
    EXPECT_EQ(0U, getNthFibonacciNumber(0U));
    EXPECT_EQ(1U, getNthFibonacciNumber(1U));
    EXPECT_EQ(1U, getNthFibonacciNumber(2U));
    EXPECT_EQ(2U, getNthFibonacciNumber(3U));
    EXPECT_EQ(21U, getNthFibonacciNumber(8U));
    EXPECT_EQ(34U, getNthFibonacciNumber(9U));
}

TEST(OtherUtilitiesTest, GetNthFibonacciNumberUsingBinetsFormulaWorks) {
    EXPECT_EQ(0U, getNthFibonacciNumberUsingBinetsFormula(0U));
    EXPECT_EQ(1U, getNthFibonacciNumberUsingBinetsFormula(1U));
    EXPECT_EQ(1U, getNthFibonacciNumberUsingBinetsFormula(2U));
    EXPECT_EQ(2U, getNthFibonacciNumberUsingBinetsFormula(3U));
    EXPECT_EQ(21U, getNthFibonacciNumberUsingBinetsFormula(8U));
    EXPECT_EQ(34U, getNthFibonacciNumberUsingBinetsFormula(9U));
}

TEST(OtherUtilitiesTest, GetNthFibonacciNumberUsingRecursionWorks) {
    EXPECT_EQ(0U, getNthFibonacciNumberUsingRecursion(0U));
    EXPECT_EQ(1U, getNthFibonacciNumberUsingRecursion(1U));
    EXPECT_EQ(1U, getNthFibonacciNumberUsingRecursion(2U));
    EXPECT_EQ(2U, getNthFibonacciNumberUsingRecursion(3U));
    EXPECT_EQ(21U, getNthFibonacciNumberUsingRecursion(8U));
    EXPECT_EQ(34U, getNthFibonacciNumberUsingRecursion(9U));
}

TEST(OtherUtilitiesTest, GetNthFibonacciUsingMatrixPowerWithLogarithmicTimeWorks) {
    EXPECT_EQ(0U, getNthFibonacciUsingMatrixPowerWithLogarithmicTime(0U));
    EXPECT_EQ(1U, getNthFibonacciUsingMatrixPowerWithLogarithmicTime(1U));
    EXPECT_EQ(1U, getNthFibonacciUsingMatrixPowerWithLogarithmicTime(2U));
    EXPECT_EQ(2U, getNthFibonacciUsingMatrixPowerWithLogarithmicTime(3U));
    EXPECT_EQ(21U, getNthFibonacciUsingMatrixPowerWithLogarithmicTime(8U));
    EXPECT_EQ(34U, getNthFibonacciUsingMatrixPowerWithLogarithmicTime(9U));
}

TEST(OtherUtilitiesTest, GetNthFibonacciUsingLogarithmicTabularDPTimeWorks) {
    EXPECT_EQ(0U, getNthFibonacciUsingLogarithmicTabularDP(0U));
    EXPECT_EQ(1U, getNthFibonacciUsingLogarithmicTabularDP(1U));
    EXPECT_EQ(1U, getNthFibonacciUsingLogarithmicTabularDP(2U));
    EXPECT_EQ(2U, getNthFibonacciUsingLogarithmicTabularDP(3U));
    EXPECT_EQ(21U, getNthFibonacciUsingLogarithmicTabularDP(8U));
    EXPECT_EQ(34U, getNthFibonacciUsingLogarithmicTabularDP(9U));
}

TEST(OtherUtilitiesTest, GetFibonacciNumbersBelowThisNumberWorks) {
    EXPECT_TRUE(getFibonacciNumbersBelowThisNumber(0U).empty());
    EXPECT_EQ((UnsignedIntegers{0U}), getFibonacciNumbersBelowThisNumber(1U));
    EXPECT_EQ((UnsignedIntegers{0U, 1U, 1U}), getFibonacciNumbersBelowThisNumber(2U));
    EXPECT_EQ((UnsignedIntegers{0U, 1U, 1U, 2U}), getFibonacciNumbersBelowThisNumber(3U));
    EXPECT_EQ((UnsignedIntegers{0U, 1U, 1U, 2U, 3U, 5U}), getFibonacciNumbersBelowThisNumber(8U));
    EXPECT_EQ((UnsignedIntegers{0U, 1U, 1U, 2U, 3U, 5U, 8U}), getFibonacciNumbersBelowThisNumber(9U));
}

}  // namespace math

}  // namespace alba
