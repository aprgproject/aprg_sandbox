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
    EXPECT_EQ(2, getLogarithmWithBase2Of(4));
    EXPECT_EQ(3, getLogarithmWithBase2Of(10));
    EXPECT_EQ(4, getLogarithmWithBase2Of(22));
    EXPECT_EQ(16, getLogarithmWithBase2Of(123456));
}

TEST(LogarithmHelpersTest, GetLogarithmForIntegersWorks) {
    EXPECT_EQ(0, getLogarithmForIntegers(1, 100));
    EXPECT_EQ(2, getLogarithmForIntegers(3, 9));
    EXPECT_EQ(5, getLogarithmForIntegers(2, 32));
    EXPECT_EQ(31LL, getLogarithmForIntegers(2LL, 2147483648LL));
    EXPECT_EQ(1, getLogarithmForIntegers(4, 15));
    EXPECT_EQ(2, getLogarithmForIntegers(4, 16));
    EXPECT_EQ(2, getLogarithmForIntegers(4, 17));
}

TEST(LogarithmHelpersTest, GetCeilOfLogarithmForIntegersWorks) {
    EXPECT_EQ(0, getCeilOfLogarithmForIntegers(1, 100));
    EXPECT_EQ(2, getCeilOfLogarithmForIntegers(3, 9));
    EXPECT_EQ(5, getCeilOfLogarithmForIntegers(2, 32));
    EXPECT_EQ(31LL, getCeilOfLogarithmForIntegers(2LL, 2147483648LL));
    EXPECT_EQ(2, getCeilOfLogarithmForIntegers(4, 15));
    EXPECT_EQ(2, getCeilOfLogarithmForIntegers(4, 16));
    EXPECT_EQ(3, getCeilOfLogarithmForIntegers(4, 17));
}

TEST(LogarithmHelpersTest, GetIterativeLogarithmWorks) {
    EXPECT_EQ(2, getIterativeLogarithm<int>(3, 9));
    EXPECT_EQ(4, getIterativeLogarithm<int>(2, 32));
    EXPECT_EQ(0, getIterativeLogarithm<int>(2, 0.0625));
    EXPECT_EQ(0, getIterativeLogarithm<int>(2, -1));
    EXPECT_EQ(2, getIterativeLogarithm<int>(4, 15));
}

TEST(LogarithmHelpersTest, GetSuperLogarithmWorks) {    EXPECT_EQ(2, getSuperLogarithm<int>(3, 9));
    EXPECT_EQ(4, getSuperLogarithm<int>(2, 32));
    EXPECT_EQ(0, getSuperLogarithm<int>(2, 0.0625));
    EXPECT_EQ(-1, getSuperLogarithm<int>(2, -1));    EXPECT_EQ(2, getSuperLogarithm<int>(4, 15));
}

TEST(LogarithmHelpersPerformanceTest, DISABLED_GetLogarithmPerformanceTest_WithIncreasingInput) {
    // Results: ~330ms

    double result(0);
    for (int base = 2; base < 200; base++) {
        for (int exponent = 1; exponent < 20000; exponent++) {
            result = std::max(result, getLogarithm(base, exponent));
        }
    }    EXPECT_DOUBLE_EQ(14.287640242993977, result);
}

TEST(LogarithmHelpersPerformanceTest, DISABLED_GetLogarithmForIntegersPerformanceTest_WithIncreasingInput) {
    // Results: ~100ms

    int result(0);
    for (int base = 2; base < 200; base++) {
        for (int exponent = 1; exponent < 20000; exponent++) {
            result = std::max(result, getLogarithmForIntegers(base, exponent));
        }
    }
    EXPECT_EQ(14, result);
}

TEST(LogarithmHelpersPerformanceTest, DISABLED_GetLogarithmPerformanceTest_WithRandomInput) {
    // Results: ~850ms

    int result(0);
    int minValue(2), maxValue(2000);
    AlbaUniformNonDeterministicRandomizer<int> randomizer(minValue, maxValue);
    for (int iterations = 1; iterations < 10000000LL; iterations++) {
        int base = randomizer.getRandomValue();
        int exponent = randomizer.getRandomValue();
        result = max(result, getLogarithmForIntegers(base, exponent));
    }
    EXPECT_LT(0LL, result);
}

TEST(LogarithmHelpersPerformanceTest, DISABLED_GetLogarithmForIntegersPerformanceTest_WithRandomInput) {
    // Results: ~790ms

    int result(0);
    int minValue(2), maxValue(2000);
    AlbaUniformNonDeterministicRandomizer<int> randomizer(minValue, maxValue);
    for (int iterations = 1; iterations < 10000000LL; iterations++) {
        int base = randomizer.getRandomValue();
        int exponent = randomizer.getRandomValue();
        result = max(result, getLogarithmForIntegers(base, exponent));
    }
    EXPECT_LT(0LL, result);
}

}  // namespace alba::mathHelper