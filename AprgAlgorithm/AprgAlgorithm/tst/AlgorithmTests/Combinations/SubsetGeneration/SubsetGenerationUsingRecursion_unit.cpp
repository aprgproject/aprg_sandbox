#include <Algorithm/Combinatorics/SubsetGeneration/SubsetGenerationUsingRecursion.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using Objects = vector<unsigned int>;
using GenerationForTest = SubsetGenerationUsingRecursion<Objects>;
using Subsets = GenerationForTest::Subsets;
}

TEST(SubsetGenerationUsingRecursionTest, GenerateOrderedSubsetsUsingDfsWorks)
{
    GenerationForTest generation;

    Subsets actualSubsets(generation.generateOrderedSubsetsUsingDfs({1U, 3U, 5U}));

    Subsets expectedSubsets{{}, {1U}, {1U, 3U}, {1U, 3U, 5U}, {1U, 5U}, {3U}, {3U, 5U}, {5U}};
    EXPECT_EQ(expectedSubsets, actualSubsets);
}

TEST(SubsetGenerationUsingRecursionTest, GenerateSubsetsUsingOnlyRecursionWorks)
{
    GenerationForTest generation;

    Subsets actualSubsets(generation.generateSubsetsUsingOnlyRecursion({1U, 3U, 5U}));

    Subsets expectedSubsets{{}, {5U}, {3U}, {3U, 5U}, {1U}, {1U, 5U}, {1U, 3U}, {1U, 3U, 5U}};
    EXPECT_EQ(expectedSubsets, actualSubsets);
}

}

}
