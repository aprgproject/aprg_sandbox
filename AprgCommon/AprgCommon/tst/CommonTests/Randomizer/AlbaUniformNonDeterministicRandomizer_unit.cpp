#include <Common/Randomizer/AlbaUniformNonDeterministicRandomizer.hpp>

#include <gtest/gtest.h>

#include <vector>

using namespace std;

namespace alba {

namespace {
using IntegerRandomizerForTest = AlbaUniformNonDeterministicRandomizer<int>;
using FloatingPointRandomizerForTest = AlbaUniformNonDeterministicRandomizer<double>;
}  // namespace

TEST(AlbaUniformNonDeterministicRandomizerTest, GetRandomIntegerWorks_WithinMinimumAndMaximumValues) {
    constexpr int minimumValue(0);
    constexpr int maximumValue(9);
    IntegerRandomizerForTest randomizer(minimumValue, maximumValue);

    for (int i = 0; i < 1000; i++) {
        auto randomValue(randomizer.getRandomValue());
        ASSERT_GE(randomValue, minimumValue);
        ASSERT_LE(randomValue, maximumValue);
    }
}

// DISABLED because its not non-deterministic
TEST(AlbaUniformNonDeterministicRandomizerTest, GetRandomIntegerWorks_AsNonDeterministic) {
    constexpr int minimumValue(0);
    constexpr int maximumValue(1000);
    IntegerRandomizerForTest randomizer1(minimumValue, maximumValue);
    IntegerRandomizerForTest randomizer2(minimumValue, maximumValue);
    int const iterations(1000);
    int const allowedDeviationCount(iterations / 10);

    int equalCount(0);
    for (int i = 0; i < iterations; i++) {
        auto random1 = randomizer1.getRandomValue();
        auto random2 = randomizer2.getRandomValue();
        equalCount += (random1 == random2) ? 1 : 0;
    }

    EXPECT_LT(equalCount, allowedDeviationCount);
}

TEST(AlbaUniformNonDeterministicRandomizerTest, GetRandomIntegerWorks_AsUniformlyDistributed) {
    constexpr int minimumValue(0);
    constexpr int maximumValue(9);
    IntegerRandomizerForTest randomizer(minimumValue, maximumValue);
    int numberOfRandomValues(maximumValue - minimumValue + 1);
    int const iterations(1000);
    int const allowedDeviationCount(iterations / 10);
    vector<int> hitsForEachValue(static_cast<unsigned long long>(numberOfRandomValues), 0);

    for (int i = 0; i < iterations; i++) {
        auto randomValue(randomizer.getRandomValue());
        hitsForEachValue[static_cast<unsigned long long>(randomValue)]++;
    }

    ASSERT_FALSE(hitsForEachValue.empty());
    auto&& [minIterator, maxIterator] = std::minmax_element(hitsForEachValue.cbegin(), hitsForEachValue.cend());
    int deviationCount(*maxIterator - *minIterator);
    EXPECT_LT(deviationCount, allowedDeviationCount);
}

TEST(AlbaUniformNonDeterministicRandomizerTest, GetRandomFloatingValueWorks_WithinMinimumAndMaximumValues) {
    constexpr double minimumValue(-11.5);
    constexpr double maximumValue(23.25);
    FloatingPointRandomizerForTest randomizer(minimumValue, maximumValue);

    for (int i = 0; i < 1000; i++) {
        auto randomValue(randomizer.getRandomValue());
        ASSERT_GE(randomValue, minimumValue);
        ASSERT_LE(randomValue, maximumValue);
    }
}

// DISABLED because its not non-deterministic
TEST(AlbaUniformNonDeterministicRandomizerTest, GetRandomFloatingValueWorks_AsNonDeterministic) {
    constexpr double minimumValue(-11.5);
    constexpr double maximumValue(2300.25);
    FloatingPointRandomizerForTest randomizer1(minimumValue, maximumValue);
    FloatingPointRandomizerForTest randomizer2(minimumValue, maximumValue);
    int const iterations(1000);
    int const allowedDeviationCount(iterations / 10);

    int equalCount(0);
    for (int i = 0; i < iterations; i++) {
        equalCount += (randomizer1.getRandomValue() == randomizer2.getRandomValue()) ? 1 : 0;
    }

    EXPECT_LT(equalCount, allowedDeviationCount);
}

TEST(AlbaUniformNonDeterministicRandomizerTest, GetRandomFloatingValueWorks_AsUniformlyDistributed) {
    constexpr int minimumValue(0);
    constexpr int maximumValue(9);
    FloatingPointRandomizerForTest randomizer(static_cast<double>(minimumValue), static_cast<double>(maximumValue));
    int numberOfRandomValues(maximumValue - minimumValue);  // number of integer values for floating point
    int const iterations(1000);
    int const allowedDeviationCount(iterations / 10);
    vector<int> hitsForEachValue(numberOfRandomValues, 0);

    for (int i = 0; i < iterations; i++) {
        auto randomValue(randomizer.getRandomValue());
        hitsForEachValue[static_cast<unsigned long long>(randomValue)]++;
    }

    ASSERT_FALSE(hitsForEachValue.empty());
    auto&& [minIterator, maxIterator] = std::minmax_element(hitsForEachValue.cbegin(), hitsForEachValue.cend());
    int deviationCount(*maxIterator - *minIterator);
    EXPECT_LT(deviationCount, allowedDeviationCount);
}

TEST(AlbaUniformNonDeterministicRandomizerTest, ResetRandomSeedWorks) {
    constexpr int minimumValue(0);
    constexpr int maximumValue(9);
    IntegerRandomizerForTest randomizer(minimumValue, maximumValue);

    randomizer.resetRandomSeed();

    for (int i = 0; i < 1000; i++) {
        auto randomValue(randomizer.getRandomValue());
        ASSERT_GE(randomValue, minimumValue);
        ASSERT_LE(randomValue, maximumValue);
    }
}

}  // namespace alba
