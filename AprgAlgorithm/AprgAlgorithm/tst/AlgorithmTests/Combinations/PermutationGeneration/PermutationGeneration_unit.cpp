#include <Algorithm/Combinatorics/PermutationGeneration/PermutationGeneration.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using Objects = vector<unsigned int>;
using GenerationForTest = PermutationGenerationUsingRecursion<Objects>;
using Permutations = GenerationForTest::Permutations;
}

TEST(PermutationGenerationUsingRecursionTest, GeneratePermutationsUsingMethod1Works)
{
    GenerationForTest generation;

    Permutations actualPermutations(generation.generatePermutationsUsingMethod1({1U, 3U, 5U}));

    Permutations expectedPermutations{{1U, 3U, 5U}, {1U, 5U, 3U}, {3U, 1U, 5U}, {3U, 5U, 1U}, {5U, 1U, 3U}, {5U, 3U, 1U}};
    EXPECT_EQ(expectedPermutations, actualPermutations);
}

TEST(PermutationGenerationUsingRecursionTest, GeneratePermutationsUsingMethod2Works)
{
    GenerationForTest generation;

    Permutations actualPermutations(generation.generatePermutationsUsingMethod2({1U, 3U, 5U}));

    Permutations expectedPermutations{{1U, 3U, 5U}, {1U, 5U, 3U}, {3U, 1U, 5U}, {3U, 5U, 1U}, {5U, 1U, 3U}, {5U, 3U, 1U}};
    EXPECT_EQ(expectedPermutations, actualPermutations);
}

}

}
