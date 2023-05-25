#include <Algorithm/Combinatorics/Subsets/SubsetGenerationUsingBits.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using Objects = vector<int>;
using GenerationForTest = SubsetGenerationUsingBits<Objects, int>;
using Subsets = GenerationForTest::Subsets;
}  // namespace

TEST(SubsetGenerationUsingBitsTest, GenerateSubsetsUsingBitsWorks) {
    Subsets actualSubsets(GenerationForTest::generateSubsetsUsingBits({1, 3, 5}));

    Subsets expectedSubsets{{}, {1}, {3}, {1, 3}, {5}, {1, 5}, {3, 5}, {1, 3, 5}};
    EXPECT_EQ(expectedSubsets, actualSubsets);
}

}  // namespace algorithm

}  // namespace alba
