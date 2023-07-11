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
    EXPECT_EQ(1, getRaiseToPowerForIntegers(-2, -1));  // this is wrong, but its easier on impl
}

TEST(PowerHelpersTest, GetRaiseToPowerForIntegersUsingPowWorks) {
    EXPECT_EQ(1, getRaiseToPowerForIntegersUsingPow(0, 0));
    EXPECT_EQ(1, getRaiseToPowerForIntegersUsingPow(1, 0));
    EXPECT_EQ(0, getRaiseToPowerForIntegersUsingPow(0, 1));
    EXPECT_EQ(243, getRaiseToPowerForIntegersUsingPow(3, 5));
    EXPECT_EQ(-128, getRaiseToPowerForIntegersUsingPow(-2, 7));
    EXPECT_EQ(0, getRaiseToPowerForIntegersUsingPow(-2, -1));
}

TEST(PowerHelpersTest, GetRaiseToPowerBasedOnTypeWorks) {
    // Integer
    EXPECT_EQ(1, getRaiseToPowerBasedOnType(0, 0));
    EXPECT_EQ(1, getRaiseToPowerBasedOnType(1, 0));
    EXPECT_EQ(0, getRaiseToPowerBasedOnType(0, 1));
    EXPECT_EQ(243, getRaiseToPowerBasedOnType(3, 5));
    EXPECT_EQ(-128, getRaiseToPowerBasedOnType(-2, 7));
    EXPECT_EQ(1, getRaiseToPowerBasedOnType(-2, -1));  // this is wrong, but its easier on impl

    // Floating point
    EXPECT_DOUBLE_EQ(1.0, getRaiseToPowerBasedOnType(0.0, 0.0));
    EXPECT_DOUBLE_EQ(1.009576582776887, getRaiseToPowerBasedOnType(1.1, 0.1));
    EXPECT_DOUBLE_EQ(0.079432823472428138, getRaiseToPowerBasedOnType(0.1, 1.1));
    EXPECT_DOUBLE_EQ(320.58606331731562, getRaiseToPowerBasedOnType(3.1, 5.1));
    EXPECT_TRUE(isnan(getRaiseToPowerBasedOnType(-2.1, 7.1)));
    EXPECT_TRUE(isnan(getRaiseToPowerBasedOnType(-2.1, -1.1)));
}

TEST(PowerHelpersTest, GetNthRootWithGuessAndNumberOfIterationsWorks) {
    EXPECT_EQ(1, getNthRoot(0, 1, 1, 0));
    EXPECT_EQ(0, getNthRoot(0, 1, 1, 1));
    EXPECT_EQ(1, getNthRoot(36, 2, 1, 0));
    EXPECT_EQ(18, getNthRoot(36, 2, 1, 1));
    EXPECT_EQ(10, getNthRoot(36, 2, 1, 2));
    EXPECT_EQ(6, getNthRoot(36, 2, 1, 3));
    EXPECT_EQ(6, getNthRoot(36, 2, 1, 4));

    EXPECT_DOUBLE_EQ(1.0, getNthRoot(0.0, 1.0, 1.0, 0));
    EXPECT_DOUBLE_EQ(0.0, getNthRoot(0.0, 1.0, 1.0, 1));
    EXPECT_DOUBLE_EQ(18.5, getNthRoot(36.0, 2.0, 1.0, 1));
    EXPECT_DOUBLE_EQ(10.222972972972974, getNthRoot(36.0, 2.0, 1.0, 2));
    EXPECT_DOUBLE_EQ(6.8722267376431292, getNthRoot(36.0, 2.0, 1.0, 3));
    EXPECT_DOUBLE_EQ(6.0553517448494789, getNthRoot(36.0, 2.0, 1.0, 4));
    EXPECT_DOUBLE_EQ(6.0002529841194185, getNthRoot(36.0, 2.0, 1.0, 5));
}

TEST(PowerHelpersTest, GetNthRootWorks) {
    EXPECT_EQ(6, getNthRoot(6, 1));
    EXPECT_EQ(6, getNthRoot(36, 2));
    EXPECT_EQ(6, getNthRoot(216, 3));
    EXPECT_EQ(6, getNthRoot(40, 2));
    EXPECT_EQ(6, getNthRoot(220, 3));

    EXPECT_DOUBLE_EQ(0.0, getNthRoot(0.0, 1.0));
    EXPECT_DOUBLE_EQ(1.0, getNthRoot(1.0, 1.0));
    EXPECT_DOUBLE_EQ(6, getNthRoot(36.0, 2.0));
}

TEST(PowerHelpersTest, GetSquareRootUsingNewtonMethodWorks) {
    EXPECT_EQ(1, getSquareRootUsingNewtonMethod(0, 1, 0));
    EXPECT_EQ(0, getSquareRootUsingNewtonMethod(0, 1, 1));
    EXPECT_EQ(1, getSquareRootUsingNewtonMethod(36, 1, 0));
    EXPECT_EQ(18, getSquareRootUsingNewtonMethod(36, 1, 1));
    EXPECT_EQ(10, getSquareRootUsingNewtonMethod(36, 1, 2));
    EXPECT_EQ(6, getSquareRootUsingNewtonMethod(36, 1, 3));
    EXPECT_EQ(6, getSquareRootUsingNewtonMethod(36, 1, 4));

    EXPECT_DOUBLE_EQ(1.0, getSquareRootUsingNewtonMethod(0.0, 1.0, 0));
    EXPECT_DOUBLE_EQ(0.5, getSquareRootUsingNewtonMethod(0.0, 1.0, 1));
    EXPECT_DOUBLE_EQ(18.5, getSquareRootUsingNewtonMethod(36.0, 1.0, 1));
    EXPECT_DOUBLE_EQ(10.222972972972974, getSquareRootUsingNewtonMethod(36.0, 1.0, 2));
    EXPECT_DOUBLE_EQ(6.8722267376431292, getSquareRootUsingNewtonMethod(36.0, 1.0, 3));
    EXPECT_DOUBLE_EQ(6.0553517448494789, getSquareRootUsingNewtonMethod(36.0, 1.0, 4));
    EXPECT_DOUBLE_EQ(6.0002529841194185, getSquareRootUsingNewtonMethod(36.0, 1.0, 5));
}

TEST(PowerHelpersTest, GetEToTheXWorks) {
    EXPECT_DOUBLE_EQ(1, getEToTheX(0.0, 0.0));
    EXPECT_DOUBLE_EQ(1, getEToTheX(0.0, 1.0));
    EXPECT_DOUBLE_EQ(1, getEToTheX(1.0, 0.0));
    EXPECT_DOUBLE_EQ(2.7182815255731922, getEToTheX(1.0, 10.0));
    EXPECT_DOUBLE_EQ(7.3887125220458554, getEToTheX(2.0, 10.0));
}

TEST(PowerHelpersTest, GetSquareRootUsingBinarySearchWorks) {
    EXPECT_EQ(0, getSquareRootUsingBinarySearch(0));
    EXPECT_EQ(1, getSquareRootUsingBinarySearch(1));    EXPECT_EQ(1, getSquareRootUsingBinarySearch(2));
    EXPECT_EQ(1, getSquareRootUsingBinarySearch(3));
    EXPECT_EQ(6, getSquareRootUsingBinarySearch(36));
    EXPECT_EQ(5, getSquareRootUsingBinarySearch(34));    EXPECT_EQ(5, getSquareRootUsingBinarySearch(35));
    EXPECT_EQ(6, getSquareRootUsingBinarySearch(37));
    EXPECT_EQ(6, getSquareRootUsingBinarySearch(38));

    // EXPECT_DOUBLE_EQ(0, getSquareRootUsingBinarySearch(0.0));  // static assert should happen
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
