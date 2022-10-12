#include <Algorithm/Combinatorics/Permutations/PermutationsGeneration.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using Objects = vector<unsigned int>;
using GenerationForTest = PermutationsGeneration<Objects>;
using Permutations = GenerationForTest::Permutations;
}

TEST(PermutationsGenerationTest, GeneratePermutationsUsingCppFunctionsWorks)
{
    GenerationForTest generation;

    Permutations actualPermutations(generation.generatePermutationsUsingCppFunctions({1U, 3U, 5U}));

    Permutations expectedPermutations{{1U, 3U, 5U}, {1U, 5U, 3U}, {3U, 1U, 5U}, {3U, 5U, 1U}, {5U, 1U, 3U}, {5U, 3U, 1U}};
    EXPECT_EQ(expectedPermutations, actualPermutations);
}

TEST(PermutationsGenerationTest, GeneratePermutationsUsingRecursionWorks)
{
    GenerationForTest generation;

    Permutations actualPermutations(generation.generatePermutationsUsingRecursion({1U, 3U, 5U}));

    Permutations expectedPermutations{{1U, 3U, 5U}, {1U, 5U, 3U}, {3U, 1U, 5U}, {3U, 5U, 1U}, {5U, 1U, 3U}, {5U, 3U, 1U}};
    EXPECT_EQ(expectedPermutations, actualPermutations);
}

TEST(PermutationsGenerationTest, GeneratePermutationsWithLengthWorks)
{
    GenerationForTest generation;

    Permutations actualPermutations(generation.generatePermutationsWithLength({1U, 3U, 5U}, 2U));

    Permutations expectedPermutations{{1U, 3U}, {1U, 5U}, {3U, 1U}, {3U, 5U}, {5U, 1U}, {5U, 3U}};
    EXPECT_EQ(expectedPermutations, actualPermutations);
}

}

}
