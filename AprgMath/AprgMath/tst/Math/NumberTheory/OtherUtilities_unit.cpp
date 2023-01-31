#include <Math/NumberTheory/OtherUtilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace math
{

TEST(OtherUtilitiesTest, IsLagrangeTheoremTrueWorks)
{
    EXPECT_TRUE(isLagrangeTheoremTrue(13U));
    EXPECT_TRUE(isLagrangeTheoremTrue(64U));
    EXPECT_TRUE(isLagrangeTheoremTrue(65U));
    EXPECT_TRUE(isLagrangeTheoremTrue(84U));
}

TEST(OtherUtilitiesTest, IsZeckendorfTheoremTrueWorks)
{
    EXPECT_TRUE(isZeckendorfTheoremTrue(13U));
    EXPECT_TRUE(isZeckendorfTheoremTrue(64U));
    EXPECT_TRUE(isZeckendorfTheoremTrue(65U));
    EXPECT_TRUE(isZeckendorfTheoremTrue(84U));
}

TEST(OtherUtilitiesTest, GetNthFibonacciNumberWorks)
{
    EXPECT_EQ(0U, getNthFibonacciNumber(0U));
    EXPECT_EQ(1U, getNthFibonacciNumber(1U));
    EXPECT_EQ(1U, getNthFibonacciNumber(2U));
    EXPECT_EQ(2U, getNthFibonacciNumber(3U));
    EXPECT_EQ(21U, getNthFibonacciNumber(8U));
    EXPECT_EQ(34U, getNthFibonacciNumber(9U));
}

TEST(OtherUtilitiesTest, GetNthFibonacciNumberUsingBinetsFormulaWorks)
{
    EXPECT_EQ(0U, getNthFibonacciNumberUsingBinetsFormula(0U));
    EXPECT_EQ(1U, getNthFibonacciNumberUsingBinetsFormula(1U));
    EXPECT_EQ(1U, getNthFibonacciNumberUsingBinetsFormula(2U));
    EXPECT_EQ(2U, getNthFibonacciNumberUsingBinetsFormula(3U));
    EXPECT_EQ(21U, getNthFibonacciNumberUsingBinetsFormula(8U));
    EXPECT_EQ(34U, getNthFibonacciNumberUsingBinetsFormula(9U));
}

TEST(OtherUtilitiesTest, GetNthFibonacciUsingMatrixPowerWithLogarithmicTimeWorks)
{
    EXPECT_EQ(0U, getNthFibonacciUsingMatrixPowerWithLogarithmicTime(0U));
    EXPECT_EQ(1U, getNthFibonacciUsingMatrixPowerWithLogarithmicTime(1U));
    EXPECT_EQ(1U, getNthFibonacciUsingMatrixPowerWithLogarithmicTime(2U));
    EXPECT_EQ(2U, getNthFibonacciUsingMatrixPowerWithLogarithmicTime(3U));
    EXPECT_EQ(21U, getNthFibonacciUsingMatrixPowerWithLogarithmicTime(8U));
    EXPECT_EQ(34U, getNthFibonacciUsingMatrixPowerWithLogarithmicTime(9U));
}

TEST(OtherUtilitiesTest, GetNthFibonacciUsingLogarithmicTabularDPTimeWorks)
{
    EXPECT_EQ(0U, getNthFibonacciUsingLogarithmicTabularDP(0U));
    EXPECT_EQ(1U, getNthFibonacciUsingLogarithmicTabularDP(1U));
    EXPECT_EQ(1U, getNthFibonacciUsingLogarithmicTabularDP(2U));
    EXPECT_EQ(2U, getNthFibonacciUsingLogarithmicTabularDP(3U));
    EXPECT_EQ(21U, getNthFibonacciUsingLogarithmicTabularDP(8U));
    EXPECT_EQ(34U, getNthFibonacciUsingLogarithmicTabularDP(9U));
}

TEST(OtherUtilitiesTest, GetFibonacciNumbersBelowThisNumberWorks)
{
    EXPECT_TRUE(getFibonacciNumbersBelowThisNumber(0U).empty());
    EXPECT_EQ((UnsignedIntegers{0U}), getFibonacciNumbersBelowThisNumber(1U));
    EXPECT_EQ((UnsignedIntegers{0U, 1U, 1U}), getFibonacciNumbersBelowThisNumber(2U));
    EXPECT_EQ((UnsignedIntegers{0U, 1U, 1U, 2U}), getFibonacciNumbersBelowThisNumber(3U));
    EXPECT_EQ((UnsignedIntegers{0U, 1U, 1U, 2U, 3U, 5U}), getFibonacciNumbersBelowThisNumber(8U));
    EXPECT_EQ((UnsignedIntegers{0U, 1U, 1U, 2U, 3U, 5U, 8U}), getFibonacciNumbersBelowThisNumber(9U));
}

}

}
