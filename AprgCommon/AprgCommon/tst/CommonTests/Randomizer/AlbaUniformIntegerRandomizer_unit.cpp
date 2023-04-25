#include <Common/Randomizer/AlbaUniformIntegerRandomizer.hpp>

#include <gtest/gtest.h>

#include <vector>

using namespace std;

namespace alba {

namespace {
using RandomizerForTest = AlbaUniformIntegerRandomizer<int>;
}

TEST(AlbaUniformIntegerRandomizerTest, GetRandomIntegerInUniformDistributionWorks_WithinMinimumAndMaximumValues) {
    constexpr int minimumValue(0);
    constexpr int maximumValue(9);
    RandomizerForTest randomizer(0, 9);
    for (int i = 0; i < 1000; i++) {
        int random(randomizer.getRandomInteger());
        ASSERT_GE(random, minimumValue);
        ASSERT_LE(random, maximumValue);
    }
}

TEST(AlbaUniformIntegerRandomizerTest, GetRandomIntegerInUniformDistributionWorks_AsUniformlyDistributed) {
    constexpr int minimumValue(0);
    constexpr int maximumValue(9);
    RandomizerForTest randomizer(0, 9);
    int numberOfRandomValues(maximumValue - minimumValue + 1);
    int const iterations(1000);
    int const allowedDeviation(static_cast<int>(iterations * 0.1));
    vector<int> hitsForEachValue(static_cast<unsigned long>(numberOfRandomValues), 0);

    for (int i = 0; i < iterations; i++) {
        int random(randomizer.getRandomInteger());
        hitsForEachValue[static_cast<unsigned long>(random)]++;
    }

    ASSERT_FALSE(hitsForEachValue.empty());
    auto&& [maxIterator, minIterator] = std::minmax_element(hitsForEachValue.cbegin(), hitsForEachValue.cend());
    int deviation(*maxIterator - *minIterator);
    EXPECT_LE(deviation, allowedDeviation);
}

}  // namespace alba
