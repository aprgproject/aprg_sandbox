#include <Algorithm/Combinatorics/Possibilities/PossibilitiesGeneration.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using Objects = vector<unsigned int>;
using GenerationForTest = PossibilitiesGeneration<Objects>;
using Possibilities = GenerationForTest::Possibilities;
}

TEST(PossibilitiesGenerationTest, GeneratePossibilitiesUsingRecursionWorks)
{
    GenerationForTest generation;

    Possibilities actualPossibilities(generation.generatePossibilitiesUsingRecursion({1U, 3U, 5U}));

    Possibilities expectedPossibilities
    {{1U, 1U, 1U}, {1U, 1U, 3U}, {1U, 1U, 5U}, {1U, 3U, 1U}, {1U, 3U, 3U}, {1U, 3U, 5U}, {1U, 5U, 1U}, {1U, 5U, 3U}, {1U, 5U, 5U},
        {3U, 1U, 1U}, {3U, 1U, 3U}, {3U, 1U, 5U}, {3U, 3U, 1U}, {3U, 3U, 3U}, {3U, 3U, 5U}, {3U, 5U, 1U}, {3U, 5U, 3U}, {3U, 5U, 5U},
        {5U, 1U, 1U}, {5U, 1U, 3U}, {5U, 1U, 5U}, {5U, 3U, 1U}, {5U, 3U, 3U}, {5U, 3U, 5U}, {5U, 5U, 1U}, {5U, 5U, 3U}, {5U, 5U, 5U}};
    EXPECT_EQ(expectedPossibilities, actualPossibilities);
}

TEST(PossibilitiesGenerationTest, GeneratePossibilitiesWithLengthWorks)
{
    GenerationForTest generation;

    Possibilities actualPossibilities(generation.generatePossibilitiesWithLength({1U, 3U, 5U}, 2U));

    Possibilities expectedPossibilities{{1U, 1U}, {1U, 3U}, {1U, 5U}, {3U, 1U}, {3U, 3U}, {3U, 5U}, {5U, 1U}, {5U, 3U}, {5U, 5U}};
    EXPECT_EQ(expectedPossibilities, actualPossibilities);
}

}

}
