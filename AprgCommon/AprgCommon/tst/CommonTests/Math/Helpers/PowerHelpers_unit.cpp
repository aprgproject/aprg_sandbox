#include <Common/Math/Helpers/PowerHelpers.hpp>
#include <Common/Randomizer/AlbaUniformNonDeterministicRandomizer.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::mathHelper {

TEST(PowerHelpersTest, IsPowerOfTwoForUnsignedIntWorks) {
    EXPECT_TRUE(isPowerOfTwo(0));
    EXPECT_TRUE(isPowerOfTwo(1));
    EXPECT_TRUE(isPowerOfTwo(2));
    EXPECT_FALSE(isPowerOfTwo(3));
    EXPECT_TRUE(isPowerOfTwo(4));
}

TEST(PowerHelpersTest, IsPerfectSquareForUnsignedIntWorks) {
    EXPECT_TRUE(isPerfectSquare(0));
    EXPECT_TRUE(isPerfectSquare(1));
    EXPECT_FALSE(isPerfectSquare(3));
    EXPECT_TRUE(isPerfectSquare(4));
    EXPECT_TRUE(isPerfectSquare(100));
    EXPECT_FALSE(isPerfectSquare(101));
}

TEST(PowerHelpersTest, IsPerfectCubeForUnsignedIntWorks) {
    EXPECT_TRUE(isPerfectCube(0));
    EXPECT_TRUE(isPerfectCube(1));
    EXPECT_TRUE(isPerfectCube(8));
    EXPECT_FALSE(isPerfectCube(9));
    EXPECT_TRUE(isPerfectCube(1000));
    EXPECT_FALSE(isPerfectCube(1001));
}

TEST(PowerHelpersTest, IsPerfectNthPowerForUnsignedIntWorks) {
    EXPECT_TRUE(isPerfectNthPower(0, 0));
    EXPECT_TRUE(isPerfectNthPower(1, 1));
    EXPECT_FALSE(isPerfectNthPower(100, 0));
    EXPECT_TRUE(isPerfectNthPower(100, 1));
    EXPECT_TRUE(isPerfectNthPower(100, 2));
    EXPECT_FALSE(isPerfectNthPower(101, 2));
    EXPECT_TRUE(isPerfectNthPower(1000, 3));
    EXPECT_FALSE(isPerfectNthPower(1001, 3));
}

TEST(PowerHelpersTest, Get2ToThePowerOfWorks) {
    EXPECT_EQ(1, get2ToThePowerOf(0));
    EXPECT_EQ(2, get2ToThePowerOf(1));
    EXPECT_EQ(4, get2ToThePowerOf(2));
    EXPECT_EQ(8, get2ToThePowerOf(3));
    EXPECT_EQ(16, get2ToThePowerOf(4));
}

TEST(PowerHelpersTest, GetRaiseToPowerForIntegersWorks) {
    EXPECT_EQ(1, getRaiseToPowerForIntegers(0, 0));
    EXPECT_EQ(1, getRaiseToPowerForIntegers(1, 0));
    EXPECT_EQ(0, getRaiseToPowerForIntegers(0, 1));
    EXPECT_EQ(5, getRaiseToPowerForIntegers(5, 1));
    EXPECT_EQ(25, getRaiseToPowerForIntegers(5, 2));
    EXPECT_EQ(243, getRaiseToPowerForIntegers(3, 5));
    EXPECT_EQ(-128, getRaiseToPowerForIntegers(-2, 7));
    EXPECT_EQ(1, getRaiseToPowerForIntegers(-2, -1));  // returns 1 if exponent is negative
}

TEST(PowerHelpersTest, GetRaiseToPowerForIntegersUsingPowWorks) {
    EXPECT_EQ(1, getRaiseToPowerForIntegersUsingPow(0, 0));
    EXPECT_EQ(1, getRaiseToPowerForIntegersUsingPow(1, 0));
    EXPECT_EQ(0, getRaiseToPowerForIntegersUsingPow(0, 1));
    EXPECT_EQ(243, getRaiseToPowerForIntegersUsingPow(3, 5));
    EXPECT_EQ(-128, getRaiseToPowerForIntegersUsingPow(-2, 7));
    EXPECT_EQ(0, getRaiseToPowerForIntegersUsingPow(-2, -1));
}

TEST(PowerHelpersTest, IsPerfectSquareForAlbaNumberWorks) {
    EXPECT_TRUE(isPerfectSquare(AlbaNumber(0)));
    EXPECT_TRUE(isPerfectSquare(AlbaNumber(1)));
    EXPECT_FALSE(isPerfectSquare(AlbaNumber(3)));
    EXPECT_TRUE(isPerfectSquare(AlbaNumber(4)));
    EXPECT_TRUE(isPerfectSquare(AlbaNumber(100)));
    EXPECT_FALSE(isPerfectSquare(AlbaNumber(101)));
    EXPECT_TRUE(isPerfectSquare(AlbaNumber::createFraction(100, 36)));
    EXPECT_FALSE(isPerfectSquare(AlbaNumber::createFraction(100, 37)));
}

TEST(PowerHelpersTest, IsPerfectCubeForAlbaNumberWorks) {
    EXPECT_TRUE(isPerfectCube(AlbaNumber(0)));
    EXPECT_TRUE(isPerfectCube(AlbaNumber(1)));
    EXPECT_TRUE(isPerfectCube(AlbaNumber(8)));
    EXPECT_FALSE(isPerfectCube(AlbaNumber(9)));
    EXPECT_TRUE(isPerfectCube(AlbaNumber(1000)));
    EXPECT_FALSE(isPerfectCube(AlbaNumber(1001)));
    EXPECT_TRUE(isPerfectCube(AlbaNumber::createFraction(1000, 27)));
    EXPECT_FALSE(isPerfectCube(AlbaNumber::createFraction(1000, 26)));
}

TEST(PowerHelpersTest, IsPerfectNthPowerForAlbaNumberWorks) {
    EXPECT_TRUE(isPerfectNthPower(AlbaNumber(0), 0));
    EXPECT_TRUE(isPerfectNthPower(AlbaNumber(1), 1));
    EXPECT_FALSE(isPerfectNthPower(AlbaNumber(100), 0));
    EXPECT_TRUE(isPerfectNthPower(AlbaNumber(100), 1));
    EXPECT_TRUE(isPerfectNthPower(AlbaNumber(100), 2));
    EXPECT_FALSE(isPerfectNthPower(AlbaNumber(101), 2));
    EXPECT_TRUE(isPerfectNthPower(AlbaNumber::createFraction(100, 36), 2));
    EXPECT_FALSE(isPerfectNthPower(AlbaNumber::createFraction(100, 37), 2));
    EXPECT_TRUE(isPerfectNthPower(AlbaNumber(1000), 3));
    EXPECT_FALSE(isPerfectNthPower(AlbaNumber(1001), 3));
    EXPECT_TRUE(isPerfectNthPower(AlbaNumber::createFraction(1000, 27), 3));
    EXPECT_FALSE(isPerfectNthPower(AlbaNumber::createFraction(1001, 26), 3));
}

TEST(PowerHelpersPerformanceTest, DISABLED_GetRaiseToPowerForIntegersPerformanceTest_WithIncreasingInput) {
    // Results: ~1s

    long long result(0);
    for (long long base = 1; base < 2000; base++) {
        for (long long exponent = 1; exponent < 2000; exponent++) {
            result = std::max(result, getRaiseToPowerForIntegers(base, exponent));
        }
    }
    EXPECT_EQ(9223358334150761985LL, result);
}

TEST(PowerHelpersPerformanceTest, DISABLED_GetRaiseToPowerForIntegersUsingPowPerformanceTest_WithIncreasingInput) {
    // Results: ~1.3s

    long long result(0);
    for (long long base = 1; base < 2000; base++) {
        for (long long exponent = 1; exponent < 2000; exponent++) {
            result = std::max(result, getRaiseToPowerForIntegersUsingPow(base, exponent));
        }
    }
    EXPECT_EQ(2146689000LL, result);
}

TEST(PowerHelpersPerformanceTest, DISABLED_GetRaiseToPowerForIntegersPerformanceTest_WithRandomInput) {
    // Results: ~3.1s

    long long result(0);
    int minValue(1), maxValue(2000);
    AlbaUniformNonDeterministicRandomizer<long long> randomizer(minValue, maxValue);
    for (long long iterations = 1; iterations < 10000000LL; iterations++) {
        long long base = randomizer.getRandomValue();
        long long exponent = randomizer.getRandomValue();
        result = max(result, getRaiseToPowerForIntegers(base, exponent));
    }
    EXPECT_LT(0LL, result);
}

TEST(PowerHelpersPerformanceTest, DISABLED_GetRaiseToPowerForIntegersUsingPowPerformanceTest_WithRandomInput) {
    // Results: ~3.1s

    long long result(0);
    int minValue(1), maxValue(2000);
    AlbaUniformNonDeterministicRandomizer<long long> randomizer(minValue, maxValue);
    for (long long iterations = 1; iterations < 10000000LL; iterations++) {
        long long base = randomizer.getRandomValue();
        long long exponent = randomizer.getRandomValue();
        result = max(result, getRaiseToPowerForIntegers(base, exponent));
    }
    EXPECT_LT(0LL, result);
}

}  // namespace alba::mathHelper
