#include <Common/Randomizer/AlbaUniformFloatingPointRandomizer.hpp>

#include <gtest/gtest.h>

#include <vector>

using namespace std;

namespace alba {

namespace {
using RandomizerForTest = AlbaUniformFloatingPointRandomizer<double>;
}

TEST(AlbaUniformFloatingPointRandomizerTest, GetRandomValueInUniformDistributionWorks_WithinMinimumAndMaximumValues) {
    constexpr double minimumValue(-11.5);
    constexpr double maximumValue(23.25);
    RandomizerForTest randomizer(-11.5, 23.25);
    for (int i = 0; i < 1000; i++) {
        double random(randomizer.getRandomFloatingPointValue());
        ASSERT_GE(random, minimumValue);
        ASSERT_LE(random, maximumValue);
    }
}

}  // namespace alba
