#include <Algorithm/Combinatorics/Possibilities/PossibilitiesGeneration.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using Objects = vector<unsigned int>;
using GenerationForTest = PossibilitiesGeneration<Objects>;
using Possibilities = GenerationForTest::Possibilities;
}  // namespace

TEST(PossibilitiesGenerationTest, GeneratePossibilitiesUsingRecursionWorks) {
    Possibilities actualPossibilities(GenerationForTest::generatePossibilitiesUsingRecursion({1U, 3U, 5U}));

    Possibilities expectedPossibilities{
        {1U, 1U, 1U}, {1U, 1U, 3U}, {1U, 1U, 5U}, {1U, 3U, 1U}, {1U, 3U, 3U}, {1U, 3U, 5U}, {1U, 5U, 1U},
        {1U, 5U, 3U}, {1U, 5U, 5U}, {3U, 1U, 1U}, {3U, 1U, 3U}, {3U, 1U, 5U}, {3U, 3U, 1U}, {3U, 3U, 3U},
        {3U, 3U, 5U}, {3U, 5U, 1U}, {3U, 5U, 3U}, {3U, 5U, 5U}, {5U, 1U, 1U}, {5U, 1U, 3U}, {5U, 1U, 5U},
        {5U, 3U, 1U}, {5U, 3U, 3U}, {5U, 3U, 5U}, {5U, 5U, 1U}, {5U, 5U, 3U}, {5U, 5U, 5U}};
    EXPECT_EQ(expectedPossibilities, actualPossibilities);
}

TEST(PossibilitiesGenerationTest, GeneratePossibilitiesWithLengthWorks) {
    Possibilities actualPossibilities(GenerationForTest::generatePossibilitiesWithLength({1U, 3U, 5U}, 2U));

    Possibilities expectedPossibilities{{1U, 1U}, {1U, 3U}, {1U, 5U}, {3U, 1U}, {3U, 3U},
                                        {3U, 5U}, {5U, 1U}, {5U, 3U}, {5U, 5U}};
    EXPECT_EQ(expectedPossibilities, actualPossibilities);
}

}  // namespace algorithm

}  // namespace alba
