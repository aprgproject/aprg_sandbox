#include <Common/Math/Helpers/LogarithmHelpers.hpp>
#include <Common/Randomizer/AlbaUniformNonDeterministicRandomizer.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::mathHelper {

TEST(LogarithmHelpersTest, GetLogarithmWorks) {
    EXPECT_DOUBLE_EQ(INFINITY, getLogarithm(1, 100));
    EXPECT_DOUBLE_EQ(2, getLogarithm(3, 9));
    EXPECT_DOUBLE_EQ(5, getLogarithm(2, 32));
    EXPECT_DOUBLE_EQ(31, getLogarithm(2, 2147483648));
    EXPECT_DOUBLE_EQ(-4, getLogarithm(2, 0.0625));
    EXPECT_DOUBLE_EQ(1.9534452978042594, getLogarithm(4, 15));
}

TEST(LogarithmHelpersTest, GetLogarithmWithBase2OfWorks) {
    EXPECT_EQ(2U, getLogarithmWithBase2Of(4U));
    EXPECT_EQ(3U, getLogarithmWithBase2Of(10U));
    EXPECT_EQ(4U, getLogarithmWithBase2Of(22U));
    EXPECT_EQ(16U, getLogarithmWithBase2Of(123456U));
}

TEST(LogarithmHelpersTest, GetLogarithmForIntegersWorks) {
    EXPECT_EQ(0U, getLogarithmForIntegers(1U, 100U));
    EXPECT_EQ(2U, getLogarithmForIntegers(3U, 9U));
    EXPECT_EQ(5U, getLogarithmForIntegers(2U, 32U));
    EXPECT_EQ(31U, getLogarithmForIntegers(2U, 2147483648U));
    EXPECT_EQ(1U, getLogarithmForIntegers(4U, 15U));
    EXPECT_EQ(2U, getLogarithmForIntegers(4U, 16U));
    EXPECT_EQ(2U, getLogarithmForIntegers(4U, 17U));
}

TEST(LogarithmHelpersTest, GetCeilOfLogarithmForIntegersWorks) {
    EXPECT_EQ(0U, getCeilOfLogarithmForIntegers(1U, 100U));
    EXPECT_EQ(2U, getCeilOfLogarithmForIntegers(3U, 9U));
    EXPECT_EQ(5U, getCeilOfLogarithmForIntegers(2U, 32U));
    EXPECT_EQ(31U, getCeilOfLogarithmForIntegers(2U, 2147483648U));
    EXPECT_EQ(2U, getCeilOfLogarithmForIntegers(4U, 15U));
    EXPECT_EQ(2U, getCeilOfLogarithmForIntegers(4U, 16U));
    EXPECT_EQ(3U, getCeilOfLogarithmForIntegers(4U, 17U));
}

TEST(LogarithmHelpersTest, GetIterativeLogarithmWorks) {
    EXPECT_EQ(2U, getIterativeLogarithm<unsigned int>(3, 9));
    EXPECT_EQ(4U, getIterativeLogarithm<unsigned int>(2, 32));
    EXPECT_EQ(0U, getIterativeLogarithm<unsigned int>(2, 0.0625));
    EXPECT_EQ(0U, getIterativeLogarithm<unsigned int>(2, -1));
    EXPECT_EQ(2U, getIterativeLogarithm<unsigned int>(4, 15));
}

TEST(LogarithmHelpersTest, GetSuperLogarithmWorks) {
    EXPECT_EQ(2, getSuperLogarithm<int>(3, 9));
    EXPECT_EQ(4, getSuperLogarithm<int>(2, 32));
    EXPECT_EQ(0, getSuperLogarithm<int>(2, 0.0625));
    EXPECT_EQ(-1, getSuperLogarithm<int>(2, -1));
    EXPECT_EQ(2, getSuperLogarithm<int>(4, 15));
}

TEST(LogarithmHelpersPerformanceTest, DISABLED_GetLogarithmPerformanceTest_WithIncreasingInput) {
    // Results: ~330ms

    double result(0);
    for (unsigned int base = 2; base < 200; base++) {
        for (unsigned int exponent = 1; exponent < 20000; exponent++) {
            result = std::max(result, getLogarithm(base, exponent));
        }
    }
    EXPECT_DOUBLE_EQ(14.287640242993977, result);
}

TEST(LogarithmHelpersPerformanceTest, DISABLED_GetLogarithmForIntegersPerformanceTest_WithIncreasingInput) {
    // Results: ~100ms

    unsigned int result(0);
    for (unsigned int base = 2; base < 200; base++) {
        for (unsigned int exponent = 1; exponent < 20000; exponent++) {
            result = std::max(result, getLogarithmForIntegers(base, exponent));
        }
    }
    EXPECT_EQ(14U, result);
}

TEST(LogarithmHelpersPerformanceTest, DISABLED_GetLogarithmPerformanceTest_WithRandomInput) {
    // Results: ~850ms

    unsigned int result(0);
    int minValue(2), maxValue(2000);
    AlbaUniformNonDeterministicRandomizer<unsigned int> randomizer(minValue, maxValue);
    for (unsigned int iterations = 1; iterations < 10000000ULL; iterations++) {
        unsigned int base = randomizer.getRandomValue();
        unsigned int exponent = randomizer.getRandomValue();
        result = max(result, getLogarithmForIntegers(base, exponent));
    }
    EXPECT_LT(0ULL, result);
}

TEST(LogarithmHelpersPerformanceTest, DISABLED_GetLogarithmForIntegersPerformanceTest_WithRandomInput) {
    // Results: ~790ms

    unsigned int result(0);
    int minValue(2), maxValue(2000);
    AlbaUniformNonDeterministicRandomizer<unsigned int> randomizer(minValue, maxValue);
    for (unsigned int iterations = 1; iterations < 10000000ULL; iterations++) {
        unsigned int base = randomizer.getRandomValue();
        unsigned int exponent = randomizer.getRandomValue();
        result = max(result, getLogarithmForIntegers(base, exponent));
    }
    EXPECT_LT(0ULL, result);
}

}  // namespace alba::mathHelper
