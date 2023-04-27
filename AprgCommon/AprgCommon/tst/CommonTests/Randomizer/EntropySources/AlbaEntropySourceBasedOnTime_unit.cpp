#include <Common/Randomizer/EntropySources/AlbaEntropySourceBasedOnTime.hpp>

#include <gtest/gtest.h>

#include <vector>

using namespace std;

namespace alba {

TEST(AlbaEntropySourceBasedOnTimeTest, DISABLED_OperatorWorks_AsNonDeterministic) {
    // This does not work because checking source1 and source2 are too close to be different.
    AlbaEntropySourceBasedOnTime source1;
    AlbaEntropySourceBasedOnTime source2;
    int const iterations(1000);
    int const allowedDeviationCount(iterations / 10);

    int equalCount(0);
    for (int i = 0; i < iterations; i++) {
        equalCount += (source1() == source2()) ? 1 : 0;
    }

    EXPECT_LT(equalCount, allowedDeviationCount);
}

TEST(AlbaEntropySourceBasedOnTimeTest, EntropyIsNotZero) {
    AlbaEntropySourceBasedOnTime source;

    EXPECT_NE(0, source.operator()());
}

}  // namespace alba
