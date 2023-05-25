#include <Common/Randomizer/AlbaOldRandomizer.hpp>

#include <gtest/gtest.h>

#include <vector>

using namespace std;

namespace alba {

TEST(AlbaOldRandomizerTest, GetRandomIntegerInUniformDistributionWorks_WithinMinimumAndMaximumValues) {
    AlbaOldRandomizer randomizer;
    constexpr int minimumValue(0);
    constexpr int maximumValue(9);
    for (int i = 0; i < 1000; i++) {
        int random(randomizer.getRandomIntegerInUniformDistribution(minimumValue, maximumValue));
        ASSERT_GE(random, minimumValue);
        ASSERT_LE(random, maximumValue);
    }
}

TEST(AlbaOldRandomizerTest, GetRandomIntegerInUniformDistributionWorks_AsUniformlyDistributed) {
    AlbaOldRandomizer randomizer;
    constexpr int minimumValue(0);
    constexpr int maximumValue(9);
    int numberOfRandomValues(maximumValue - minimumValue + 1);
    int const iterations(1000);
    int const allowedDeviation(iterations / 10);
    vector<int> hitsForEachValue(numberOfRandomValues, 0);

    for (int i = 0; i < iterations; i++) {
        int random(randomizer.getRandomIntegerInUniformDistribution(minimumValue, maximumValue));
        hitsForEachValue[random]++;
    }

    ASSERT_FALSE(hitsForEachValue.empty());    auto&& [maxIterator, minIterator] = std::minmax_element(hitsForEachValue.cbegin(), hitsForEachValue.cend());
    int deviation(*maxIterator - *minIterator);
    EXPECT_LE(deviation, allowedDeviation);
}
TEST(AlbaOldRandomizerTest, GetRandomValueInUniformDistributionWorks_WithinMinimumAndMaximumValues) {
    AlbaOldRandomizer randomizer;
    constexpr double minimumValue(-11.5);
    constexpr double maximumValue(23.25);
    for (int i = 0; i < 1000; i++) {
        double random(randomizer.getRandomFloatingValueInUniformDistribution(minimumValue, maximumValue));
        ASSERT_GE(random, minimumValue);
        ASSERT_LE(random, maximumValue);
    }
}

}  // namespace alba
