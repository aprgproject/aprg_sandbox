#include <Algorithm/Combinatorics/Subsets/SubsetGenerationUsingRecursion.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using Objects = vector<unsigned int>;
using GenerationForTest = SubsetGenerationUsingRecursion<Objects>;
using Subsets = GenerationForTest::Subsets;
}  // namespace

TEST(SubsetGenerationUsingRecursionTest, GenerateOrderedSubsetsUsingDfsWorks) {
    Subsets actualSubsets(GenerationForTest::generateOrderedSubsetsUsingDfs({1U, 3U, 5U}));

    Subsets expectedSubsets{{}, {1U}, {1U, 3U}, {1U, 3U, 5U}, {1U, 5U}, {3U}, {3U, 5U}, {5U}};
    EXPECT_EQ(expectedSubsets, actualSubsets);
}

TEST(SubsetGenerationUsingRecursionTest, GenerateSubsetsUsingOnlyRecursionWorks) {
    Subsets actualSubsets(GenerationForTest::generateSubsetsUsingOnlyRecursion({1U, 3U, 5U}));

    Subsets expectedSubsets{{}, {5U}, {3U}, {3U, 5U}, {1U}, {1U, 5U}, {1U, 3U}, {1U, 3U, 5U}};
    EXPECT_EQ(expectedSubsets, actualSubsets);
}

}  // namespace algorithm

}  // namespace alba
