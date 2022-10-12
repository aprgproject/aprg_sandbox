#include <Algorithm/Combinatorics/Combinations/CombinationsGeneration.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using Objects = vector<unsigned int>;
using GenerationForTest = CombinationsGeneration<Objects>;
using Combinations = GenerationForTest::Combinations;
}

TEST(CombinationsGenerationTest, GenerateCombinationsWithLengthWorksWhenCombinationLengthIsLessThanSize)
{
    GenerationForTest generation;

    Combinations actualCombinations(generation.generateCombinationsWithLength({1U, 3U, 5U}, 2U));

    Combinations expectedCombinations{{1U, 3U}, {1U, 5U}, {3U, 5U}};
    EXPECT_EQ(expectedCombinations, actualCombinations);
}

TEST(CombinationsGenerationTest, GenerateCombinationsWithLengthWorksWhenCombinationLengthIsEqualToSize)
{
    GenerationForTest generation;

    Combinations actualCombinations(generation.generateCombinationsWithLength({1U, 3U, 5U}, 3U));

    Combinations expectedCombinations{{1U, 3U, 5U}};
    EXPECT_EQ(expectedCombinations, actualCombinations);
}

}

}
