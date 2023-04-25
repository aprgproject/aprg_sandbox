#include <Algorithm/Combinatorics/Combinations/CombinationsWithSum.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using Values = vector<unsigned int>;
using GenerationForTest = CombinationsWithSum<Values>;
using Combinations = GenerationForTest::Combinations;
}  // namespace

TEST(CombinationsWithSumTest, GetCombinationsWithSumUsingRecursionWorks) {
    Values inputValues{1U, 2U, 3U, 4U};
    GenerationForTest generation(inputValues);

    Combinations actualCombinations(generation.getCombinationsWithSumUsingRecursion(4U));

    Combinations expectedCombinations{{1U, 1U, 1U, 1U}, {1U, 1U, 2U}, {1U, 3U}, {2U, 2U}, {4U}};
    EXPECT_EQ(expectedCombinations, actualCombinations);
}

TEST(CombinationsWithSumTest, GetCombinationsWithSumUsingLoopsWorks) {
    Values inputValues{1U, 2U, 3U, 4U};
    GenerationForTest generation(inputValues);

    Combinations actualCombinations(generation.getCombinationsWithSumUsingLoops(4U));

    Combinations expectedCombinations{{1U, 1U, 1U, 1U}, {1U, 1U, 2U}, {1U, 3U}, {2U, 2U}, {4U}};
    EXPECT_EQ(expectedCombinations, actualCombinations);
}

}  // namespace algorithm

}  // namespace alba
