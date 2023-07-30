#include <Algorithm/Random/ReservoirSampling.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

using ValuesForTest = vector<int>;
using ReservoirSamplingForTest = ReservoirSampling<ValuesForTest>;
using ValueForTest = ReservoirSamplingForTest::Value;
using Samples = ReservoirSamplingForTest::Samples;

TEST(ReservoirSamplingTest, GetReservoirSamplingWorksOnExample1) {
    ValuesForTest values{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ReservoirSamplingForTest reservoirSampling;

    EXPECT_NE((Samples{}), reservoirSampling.getSamples(values.begin().operator->(), values.size(), 5));
}

TEST(ReservoirSamplingTest, GetReservoirSamplingWorksOnExample2) {
    ValuesForTest values{5, 9, 4, 8, 6, 1, 4, 2, 0};
    ReservoirSamplingForTest reservoirSampling;

    EXPECT_NE((Samples{}), reservoirSampling.getSamples(values.begin().operator->(), values.size(), 5));
}

TEST(ReservoirSamplingTest, GetReservoirSamplingWorksOnExample3) {
    ValuesForTest values{1, 3, 2, 4, 5, 6, 8, 7};
    ReservoirSamplingForTest reservoirSampling;

    EXPECT_NE((Samples{}), reservoirSampling.getSamples(values.begin().operator->(), values.size(), 5));
}

}  // namespace algorithm
}  // namespace alba