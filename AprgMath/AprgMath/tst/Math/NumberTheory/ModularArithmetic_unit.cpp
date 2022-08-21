#include <Math/NumberTheory/ModularArithmetic.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace math
{

TEST(ModularArithmeticTest, CanModuloBeDistributedInAdditionWorks)
{
    EXPECT_TRUE(canModuloBeDistributedInAddition(55U, 3U, 12U));
}

TEST(ModularArithmeticTest, CanModuloBeDistributedInSubtractionWorks)
{
    EXPECT_TRUE(canModuloBeDistributedInSubtraction(55U, 3U, 12U));
}

TEST(ModularArithmeticTest, CanModuloBeDistributedInMultiplicationWorks)
{
    EXPECT_TRUE(canModuloBeDistributedInMultiplication(55U, 3U, 12U));
}

TEST(ModularArithmeticTest, CanModuloBeDistributedInPowerWorks)
{
    EXPECT_TRUE(canModuloBeDistributedInPower(55U, 3U, 12U));
}

TEST(ModularArithmeticTest, CanModuloBeDistributedInEveryIterationOfFactorialWorks)
{
    EXPECT_TRUE(canModuloBeDistributedInEveryIterationOfFactorial(17U, 4U));
}

TEST(ModularArithmeticTest, IsFermatTheoremTrueWorks)
{
    EXPECT_FALSE(isFermatTheoremTrue(15U, 8U)); // Expected false when input is wrong
    EXPECT_FALSE(isFermatTheoremTrue(16U, 8U)); // Expected false when input is wrong
    EXPECT_TRUE(isFermatTheoremTrue(17U, 8U));
}

TEST(ModularArithmeticTest, IsEulerTheoremTrueWorks)
{
    EXPECT_FALSE(isFermatTheoremTrue(16U, 8U)); // Expected false when input is wrong
    EXPECT_TRUE(isEulerTheoremTrue(17U, 8U));
    EXPECT_TRUE(isEulerTheoremTrue(14U, 9U));
}

TEST(ModularArithmeticTest, GetModularExponentiationWorks)
{
    EXPECT_EQ(7U, getModularExponentiation(55U, 3U, 12U));
}

TEST(ModularArithmeticTest, GetModularInverseWorks)
{
    EXPECT_EQ(0U, getModularInverse(2U, 4U));
    EXPECT_EQ(3U, getModularInverse(6U, 17U));
}

TEST(ModularArithmeticTest, GetModularFactorialWorks)
{
    EXPECT_EQ(2U, getModularFactorial(2U, 4U));
    EXPECT_EQ(6U, getModularFactorial(6U, 17U));
}

}

}
