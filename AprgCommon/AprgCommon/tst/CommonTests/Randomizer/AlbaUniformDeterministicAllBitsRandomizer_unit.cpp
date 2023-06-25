#include <Common/Randomizer/AlbaUniformDeterministicAllBitsRandomizer.hpp>

#include <gtest/gtest.h>

#include <vector>

using namespace std;

namespace alba {

namespace {
using IntegerRandomizerForTest = AlbaUniformDeterministicAllBitsRandomizer<int>;
using FloatingPointRandomizerForTest = AlbaUniformDeterministicAllBitsRandomizer<double>;
}  // namespace

TEST(AlbaUniformDeterministicAllBitsRandomizerTest, DefaultConstructorWorks) {
    IntegerRandomizerForTest randomizer;

    EXPECT_NO_FATAL_FAILURE(randomizer.getRandomValue());
}

TEST(AlbaUniformDeterministicAllBitsRandomizerTest, SetRandomSeedWorks) {
    constexpr long long minimumValue(static_cast<long long>(numeric_limits<int>::min()));
    constexpr long long maximumValue(static_cast<long long>(numeric_limits<int>::max()));
    constexpr double customSeed(10);
    IntegerRandomizerForTest randomizer(customSeed);

    constexpr int newCustomSeed(42);
    randomizer.setRandomSeed(newCustomSeed);

    for (int i = 0; i < 1000; i++) {
        long long randomValue(static_cast<long long>(randomizer.getRandomValue()));
        ASSERT_GE(randomValue, minimumValue);
        ASSERT_LE(randomValue, maximumValue);
    }
}

TEST(AlbaUniformDeterministicAllBitsRandomizerTest, GetRandomIntegerWorks_WithinMinimumAndMaximumValues) {
    constexpr long long minimumValue(static_cast<long long>(numeric_limits<int>::min()));
    constexpr long long maximumValue(static_cast<long long>(numeric_limits<int>::max()));    constexpr int customSeed(5);
    IntegerRandomizerForTest randomizer(customSeed);

    for (int i = 0; i < 1000; i++) {        long long randomValue(static_cast<long long>(randomizer.getRandomValue()));
        ASSERT_GE(randomValue, minimumValue);
        ASSERT_LE(randomValue, maximumValue);
    }
}

TEST(AlbaUniformDeterministicAllBitsRandomizerTest, GetRandomIntegerWorks_AsDeterministic) {
    constexpr int customSeed(5);
    IntegerRandomizerForTest randomizer1(customSeed);
    IntegerRandomizerForTest randomizer2(customSeed);

    for (int i = 0; i < 1000; i++) {
        ASSERT_EQ(randomizer1.getRandomValue(), randomizer2.getRandomValue());
    }
}

TEST(AlbaUniformDeterministicAllBitsRandomizerTest, GetRandomFloatingValueWorks_AsDeterministic) {
    constexpr double customSeed(10);
    FloatingPointRandomizerForTest randomizer1(customSeed);
    FloatingPointRandomizerForTest randomizer2(customSeed);

    for (int i = 0; i < 1000; i++) {
        ASSERT_EQ(randomizer1.getRandomValue(), randomizer2.getRandomValue());
    }
}

// Dont test if uniformly distributed because its too large just trust the C++ implementation

}  // namespace alba