#include <Algorithm/String/ZArray/ZAlgorithm.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using ZAlgorithmForTest = ZAlgorithm<int>;
using Indexes = ZAlgorithmForTest::Indexes;
}  // namespace

TEST(ZAlgorithmTest, GetZArrayWorksWithExample1) {
    Indexes expectedIndexes{0, 0, 0, 2, 0, 0, 5, 0, 0, 7, 0, 0, 2, 0, 0, 1};

    EXPECT_EQ(expectedIndexes, ZAlgorithmForTest::getZArray("ACBACDACBACBACDA"));
}

}  // namespace algorithm

}  // namespace alba
