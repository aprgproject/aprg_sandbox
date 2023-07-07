#include <Algorithm/String/ZAlgorithm/ZAlgorithm.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using ZAlgorithmForTest = ZAlgorithm<int>;
using Indexes = ZAlgorithmForTest::Indexes;
}  // namespace

TEST(ZAlgorithmTest, GetPrefixLengthsUsingTheZAlgorithmWorksWithExample1) {
    Indexes expectedIndexes{0, 5, 4, 3, 2, 1};

    EXPECT_EQ(expectedIndexes, ZAlgorithmForTest::getPrefixLengthsUsingTheZAlgorithm("aaaaaa"));
}

TEST(ZAlgorithmTest, GetPrefixLengthsUsingTheZAlgorithmWorksWithExample2) {
    Indexes expectedIndexes{0, 1, 0, 0, 3, 1, 0, 0, 2, 2, 1, 0};

    EXPECT_EQ(expectedIndexes, ZAlgorithmForTest::getPrefixLengthsUsingTheZAlgorithm("aabcaabxaaaz"));
}

TEST(ZAlgorithmTest, GetPrefixLengthsUsingTheZAlgorithmWorksWithExample3) {
    Indexes expectedIndexes{0, 0, 0, 2, 0, 0, 5, 0, 0, 7, 0, 0, 2, 0, 0, 1};

    EXPECT_EQ(expectedIndexes, ZAlgorithmForTest::getPrefixLengthsUsingTheZAlgorithm("ACBACDACBACBACDA"));
}

}  // namespace algorithm

}  // namespace alba
