#include <Algorithm/Combinatorics/Subsets/SubsetGenerationUsingBits.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using Objects = vector<unsigned int>;
using GenerationForTest = SubsetGenerationUsingBits<Objects, unsigned int>;
using Subsets = GenerationForTest::Subsets;
}

TEST(SubsetGenerationUsingBitsTest, GenerateSubsetsUsingBitsWorks)
{
    GenerationForTest generation;

    Subsets actualSubsets(generation.generateSubsetsUsingBits({1U, 3U, 5U}));

    Subsets expectedSubsets{{}, {1U}, {3U}, {1U, 3U}, {5U}, {1U, 5U}, {3U, 5U}, {1U, 3U, 5U}};
    EXPECT_EQ(expectedSubsets, actualSubsets);
}

}

}
