#include <Common/Randomizer/AlbaSimpleRandomizer.hpp>

#include <gtest/gtest.h>

#include <vector>

using namespace std;

namespace alba {

TEST(AlbaSimpleRandomizerTest, GetRandomIntegerInUniformDistributionWorks_WithinMinimumAndMaximumValues) {
    AlbaSimpleRandomizer randomizer;
    constexpr int minimumValue(0);
    constexpr int maximumValue(9);
    for (int i = 0; i < 1000; i++) {
        int random(randomizer.getRandomIntegerInUniformDistribution(minimumValue, maximumValue));
        ASSERT_GE(random, minimumValue);
        ASSERT_LE(random, maximumValue);
    }
}

TEST(AlbaSimpleRandomizerTest, GetRandomIntegerInUniformDistributionWorks_AsUniformlyDistributed) {
    AlbaSimpleRandomizer randomizer;
    constexpr int minimumValue(0);
    constexpr int maximumValue(9);
    int numberOfRandomValues(maximumValue - minimumValue + 1);
    int const iterations(1000);
    int const allowedDeviation(iterations/10);
    vector<int> hitsForEachValue(static_cast<unsigned long>(numberOfRandomValues), 0);

    for (int i = 0; i < iterations; i++) {        int random(randomizer.getRandomIntegerInUniformDistribution(minimumValue, maximumValue));
        hitsForEachValue[static_cast<unsigned long>(random)]++;
    }
    ASSERT_FALSE(hitsForEachValue.empty());
    auto&& [maxIterator, minIterator] = std::minmax_element(hitsForEachValue.cbegin(), hitsForEachValue.cend());
    int deviation(*maxIterator - *minIterator);
    EXPECT_LE(deviation, allowedDeviation);
}

TEST(AlbaSimpleRandomizerTest, GetRandomValueInUniformDistributionWorks_WithinMinimumAndMaximumValues) {
    AlbaSimpleRandomizer randomizer;
    constexpr double minimumValue(-11.5);
    constexpr double maximumValue(23.25);
    for (int i = 0; i < 1000; i++) {
        double random(randomizer.getRandomFloatingValueInUniformDistribution(minimumValue, maximumValue));
        ASSERT_GE(random, minimumValue);
        ASSERT_LE(random, maximumValue);
    }
}

}  // namespace alba
