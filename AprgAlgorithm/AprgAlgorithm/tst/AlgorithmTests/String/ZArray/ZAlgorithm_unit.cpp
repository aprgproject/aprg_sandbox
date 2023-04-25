#include <Algorithm/String/ZArray/ZAlgorithm.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using ZAlgorithmForTest = ZAlgorithm<unsigned int>;
using Indexes = ZAlgorithmForTest::Indexes;
}  // namespace

TEST(ZAlgorithmTest, GetZArrayWorksWithExample1) {
    Indexes expectedIndexes{0U, 0U, 0U, 2U, 0U, 0U, 5U, 0U, 0U, 7U, 0U, 0U, 2U, 0U, 0U, 1U};

    EXPECT_EQ(expectedIndexes, ZAlgorithmForTest::getZArray("ACBACDACBACBACDA"));
}

}  // namespace algorithm

}  // namespace alba
