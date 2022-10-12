#include <Algorithm/Combinatorics/Combinations/CombinationGeneration.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using Objects = vector<unsigned int>;
using GenerationForTest = CombinationGeneration<Objects>;
using Combinations = GenerationForTest::Combinations;
}

TEST(CombinationGenerationTest, GenerateCombinationsWithLengthWorksWhenCombinationLengthIsLessThanSize)
{
    GenerationForTest generation;

    Combinations actualCombinations(generation.generateCombinationsWithLength({1U, 3U, 5U}, 2U));

    Combinations expectedCombinations{{1U, 3U}, {1U, 5U}, {3U, 5U}};
    EXPECT_EQ(expectedCombinations, actualCombinations);
}

TEST(CombinationGenerationTest, GenerateCombinationsWithLengthWorksWhenCombinationLengthIsEqualToSize)
{
    GenerationForTest generation;

    Combinations actualCombinations(generation.generateCombinationsWithLength({1U, 3U, 5U}, 3U));

    Combinations expectedCombinations{{1U, 3U, 5U}};
    EXPECT_EQ(expectedCombinations, actualCombinations);
}

}

}
