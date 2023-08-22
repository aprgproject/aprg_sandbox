#include <UniqueProblems/RandomProblems/Rand7FromRand5.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba {
TEST(Rand7FromRand5Test, GetRandomFrom0To6Works_AsUniformlyDistributed) {
    Rand7FromRand5 rand7FromRand5;
    int const iterations(1000);
    int const allowedDeviationCount(iterations / 10);
    vector<int> hitsForEachValue(7, 0);

    for (int i = 0; i < iterations; i++) {
        auto randomValue(rand7FromRand5.getRandomFrom0To6());
        hitsForEachValue[randomValue]++;
    }

    ASSERT_FALSE(hitsForEachValue.empty());
    auto&& [minIterator, maxIterator] = std::minmax_element(hitsForEachValue.cbegin(), hitsForEachValue.cend());
    int deviationCount(*maxIterator - *minIterator);
    EXPECT_LT(deviationCount, allowedDeviationCount);
}

}  // namespace alba
