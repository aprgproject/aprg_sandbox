#include <Common/Math/Helpers/PowerHelpers.hpp>
#include <Common/Randomizer/AlbaSimpleRandomizer.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace mathHelper
{

TEST(PowerHelpersTest, IsPowerOfTwoForUnsignedIntWorks)
{
    EXPECT_TRUE(isPowerOfTwo(0U));
    EXPECT_TRUE(isPowerOfTwo(1U));
    EXPECT_TRUE(isPowerOfTwo(2U));
    EXPECT_FALSE(isPowerOfTwo(3U));
    EXPECT_TRUE(isPowerOfTwo(4U));
}

TEST(PowerHelpersTest, IsPerfectSquareForUnsignedIntWorks)
{
    EXPECT_TRUE(isPerfectSquare(0U));
    EXPECT_TRUE(isPerfectSquare(1U));
    EXPECT_FALSE(isPerfectSquare(3U));
    EXPECT_TRUE(isPerfectSquare(4U));
    EXPECT_TRUE(isPerfectSquare(100U));
    EXPECT_FALSE(isPerfectSquare(101U));
}

TEST(PowerHelpersTest, IsPerfectCubeForUnsignedIntWorks)
{
    EXPECT_TRUE(isPerfectCube(0U));
    EXPECT_TRUE(isPerfectCube(1U));
    EXPECT_TRUE(isPerfectCube(8U));
    EXPECT_FALSE(isPerfectCube(9U));
    EXPECT_TRUE(isPerfectCube(1000U));
    EXPECT_FALSE(isPerfectCube(1001U));
}

TEST(PowerHelpersTest, IsPerfectNthPowerForUnsignedIntWorks)
{
    EXPECT_TRUE(isPerfectNthPower(0U, 0U));
    EXPECT_TRUE(isPerfectNthPower(1U, 1U));
    EXPECT_FALSE(isPerfectNthPower(100U, 0U));
    EXPECT_TRUE(isPerfectNthPower(100U, 1U));
    EXPECT_TRUE(isPerfectNthPower(100U, 2U));
    EXPECT_FALSE(isPerfectNthPower(101U, 2U));
    EXPECT_TRUE(isPerfectNthPower(1000U, 3U));
    EXPECT_FALSE(isPerfectNthPower(1001U, 3U));
}

TEST(PowerHelpersTest, Get2ToThePowerOfWorks)
{
    EXPECT_EQ(1U, get2ToThePowerOf(0U));
    EXPECT_EQ(2U, get2ToThePowerOf(1U));
    EXPECT_EQ(4U, get2ToThePowerOf(2U));
    EXPECT_EQ(8U, get2ToThePowerOf(3U));
    EXPECT_EQ(16U, get2ToThePowerOf(4U));
}

TEST(PowerHelpersTest, GetRaiseToPowerForIntegersWorks)
{
    EXPECT_EQ(1U, getRaiseToPowerForIntegers(0U, 0U));
    EXPECT_EQ(1U, getRaiseToPowerForIntegers(1U, 0U));
    EXPECT_EQ(0U, getRaiseToPowerForIntegers(0U, 1U));
    EXPECT_EQ(5U, getRaiseToPowerForIntegers(5U, 1U));
    EXPECT_EQ(25U, getRaiseToPowerForIntegers(5U, 2U));
    EXPECT_EQ(243U, getRaiseToPowerForIntegers(3U, 5U));
    EXPECT_EQ(-128, getRaiseToPowerForIntegers(-2, 7));
    EXPECT_EQ(1, getRaiseToPowerForIntegers(-2, -1)); // returns 1 if exponent is negative
}

TEST(PowerHelpersTest, GetRaiseToPowerForIntegersUsingPowWorks)
{
    EXPECT_EQ(1U, getRaiseToPowerForIntegersUsingPow(0U, 0U));
    EXPECT_EQ(1U, getRaiseToPowerForIntegersUsingPow(1U, 0U));
    EXPECT_EQ(0U, getRaiseToPowerForIntegersUsingPow(0U, 1U));
    EXPECT_EQ(243U, getRaiseToPowerForIntegersUsingPow(3U, 5U));
    EXPECT_EQ(-128, getRaiseToPowerForIntegersUsingPow(-2, 7));
    EXPECT_EQ(0, getRaiseToPowerForIntegersUsingPow(-2, -1));
}

TEST(PowerHelpersTest, IsPerfectSquareForAlbaNumberWorks)
{
    EXPECT_TRUE(isPerfectSquare(AlbaNumber(0)));
    EXPECT_TRUE(isPerfectSquare(AlbaNumber(1)));
    EXPECT_FALSE(isPerfectSquare(AlbaNumber(3)));
    EXPECT_TRUE(isPerfectSquare(AlbaNumber(4)));
    EXPECT_TRUE(isPerfectSquare(AlbaNumber(100)));
    EXPECT_FALSE(isPerfectSquare(AlbaNumber(101)));
    EXPECT_TRUE(isPerfectSquare(AlbaNumber::createFraction(100, 36)));
    EXPECT_FALSE(isPerfectSquare(AlbaNumber::createFraction(100, 37)));
}

TEST(PowerHelpersTest, IsPerfectCubeForAlbaNumberWorks)
{
    EXPECT_TRUE(isPerfectCube(AlbaNumber(0)));
    EXPECT_TRUE(isPerfectCube(AlbaNumber(1)));
    EXPECT_TRUE(isPerfectCube(AlbaNumber(8)));
    EXPECT_FALSE(isPerfectCube(AlbaNumber(9)));
    EXPECT_TRUE(isPerfectCube(AlbaNumber(1000)));
    EXPECT_FALSE(isPerfectCube(AlbaNumber(1001)));
    EXPECT_TRUE(isPerfectCube(AlbaNumber::createFraction(1000, 27)));
    EXPECT_FALSE(isPerfectCube(AlbaNumber::createFraction(1000, 26)));
}

TEST(PowerHelpersTest, IsPerfectNthPowerForAlbaNumberWorks)
{
    EXPECT_TRUE(isPerfectNthPower(AlbaNumber(0U), 0U));
    EXPECT_TRUE(isPerfectNthPower(AlbaNumber(1), 1U));
    EXPECT_FALSE(isPerfectNthPower(AlbaNumber(100), 0U));
    EXPECT_TRUE(isPerfectNthPower(AlbaNumber(100), 1U));
    EXPECT_TRUE(isPerfectNthPower(AlbaNumber(100), 2U));
    EXPECT_FALSE(isPerfectNthPower(AlbaNumber(101), 2U));
    EXPECT_TRUE(isPerfectNthPower(AlbaNumber::createFraction(100, 36), 2U));
    EXPECT_FALSE(isPerfectNthPower(AlbaNumber::createFraction(100, 37), 2U));
    EXPECT_TRUE(isPerfectNthPower(AlbaNumber(1000), 3U));
    EXPECT_FALSE(isPerfectNthPower(AlbaNumber(1001), 3U));
    EXPECT_TRUE(isPerfectNthPower(AlbaNumber::createFraction(1000, 27), 3U));
    EXPECT_FALSE(isPerfectNthPower(AlbaNumber::createFraction(1001, 26), 3U));
}

TEST(PowerHelpersPerformanceTest, DISABLED_GetRaiseToPowerForIntegersPerformanceTest_WithIncreasingInput)
{
    // Results: ~1s

    unsigned long long result(0);
    for(unsigned long long base=1; base<2000; base++)
    {
        for(unsigned long long exponent=1; exponent<2000; exponent++)
        {
            result = std::max(result, getRaiseToPowerForIntegers(base, exponent));
        }
    }
    EXPECT_EQ(18446741497450899401ULL, result);
}

TEST(PowerHelpersPerformanceTest, DISABLED_GetRaiseToPowerForIntegersUsingPowPerformanceTest_WithIncreasingInput)
{
    // Results: ~1.3s

    unsigned long long result(0);
    for(unsigned long long base=1; base<2000; base++)
    {
        for(unsigned long long exponent=1; exponent<2000; exponent++)
        {
            result = std::max(result, getRaiseToPowerForIntegersUsingPow(base, exponent));
        }
    }
    EXPECT_EQ(18446744071562067968ULL, result);
}

TEST(PowerHelpersPerformanceTest, DISABLED_GetRaiseToPowerForIntegersPerformanceTest_WithRandomInput)
{
    // Results: ~3.1s

    unsigned long long result(0);
    AlbaSimpleRandomizer randomizer;
    int minValue(1), maxValue(2000);
    for(unsigned long long iterations=1; iterations<10000000ULL; iterations++)
    {
        unsigned long long base = static_cast<unsigned long long>(randomizer.getRandomIntegerInUniformDistribution(minValue, maxValue));
        unsigned long long exponent = static_cast<unsigned long long>(randomizer.getRandomIntegerInUniformDistribution(minValue, maxValue));
        result = max(result, getRaiseToPowerForIntegers(base, exponent));
    }
    EXPECT_LT(0ULL, result);}

TEST(PowerHelpersPerformanceTest, DISABLED_GetRaiseToPowerForIntegersUsingPowPerformanceTest_WithRandomInput)
{    // Results: ~3.1s

    unsigned long long result(0);
    AlbaSimpleRandomizer randomizer;
    int minValue(1), maxValue(2000);
    for(unsigned long long iterations=1; iterations<10000000ULL; iterations++)
    {
        unsigned long long base = static_cast<unsigned long long>(randomizer.getRandomIntegerInUniformDistribution(minValue, maxValue));
        unsigned long long exponent = static_cast<unsigned long long>(randomizer.getRandomIntegerInUniformDistribution(minValue, maxValue));
        result = max(result, getRaiseToPowerForIntegers(base, exponent));
    }
    EXPECT_LT(0ULL, result);}

}
}
