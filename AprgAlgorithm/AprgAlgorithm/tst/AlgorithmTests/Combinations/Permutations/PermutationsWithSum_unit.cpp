#include <Algorithm/Combinatorics/Permutations/PermutationsWithSum.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using Values = vector<unsigned int>;
using GenerationForTest = PermutationsWithSum<Values>;
using Permutations = GenerationForTest::Permutations;
}

TEST(PermutationsWithSumTest, GetPermutationsWithSumUsingLoopsWorks)
{
    Values inputValues{1U, 2U, 3U, 4U};
    GenerationForTest generation(inputValues);

    Permutations actualPermutations(generation.getPermutationsWithSumUsingLoops(4U));

    Permutations expectedPermutations{{1U, 1U, 1U, 1U}, {1U, 1U, 2U}, {1U, 2U, 1U}, {1U, 3U}, {2U, 1U, 1U}, {2U, 2U}, {3U, 1U}, {4U}};
    EXPECT_EQ(expectedPermutations, actualPermutations);
}

}

}
