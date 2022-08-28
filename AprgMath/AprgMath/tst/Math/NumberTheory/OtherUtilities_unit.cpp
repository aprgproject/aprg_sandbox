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

TEST(OtherUtilitiesTest, GetFibonacciNumbersBelowThisNumberWorks)
{
    EXPECT_TRUE(getFibonacciNumbersBelowThisNumber(0U).empty());
    EXPECT_TRUE(getFibonacciNumbersBelowThisNumber(1U).empty());
    EXPECT_EQ((UnsignedIntegers{1U, 1U}), getFibonacciNumbersBelowThisNumber(2U));
    EXPECT_EQ((UnsignedIntegers{1U, 1U, 2U}), getFibonacciNumbersBelowThisNumber(3U));
    EXPECT_EQ((UnsignedIntegers{1U, 1U, 2U, 3U, 5U}), getFibonacciNumbersBelowThisNumber(8U));
    EXPECT_EQ((UnsignedIntegers{1U, 1U, 2U, 3U, 5U, 8U}), getFibonacciNumbersBelowThisNumber(9U));
}

}

}
