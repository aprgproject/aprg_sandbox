#include <Algorithm/Combinatorics/Combinations/CombinationsGeneration.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using Objects = vector<int>;
using GenerationForTest = CombinationsGeneration<Objects>;
using Combinations = GenerationForTest::Combinations;
}  // namespace

TEST(CombinationsGenerationTest, GenerateCombinationsWithLengthWorksWhenCombinationLengthIsLessThanSize) {
    Combinations actualCombinations(GenerationForTest::generateCombinationsWithLength({1, 3, 5}, 2));

    Combinations expectedCombinations{{1, 3}, {1, 5}, {3, 5}};
    EXPECT_EQ(expectedCombinations, actualCombinations);
}

TEST(CombinationsGenerationTest, GenerateCombinationsWithLengthWorksWhenCombinationLengthIsEqualToSize) {
    Combinations actualCombinations(GenerationForTest::generateCombinationsWithLength({1, 3, 5}, 3));

    Combinations expectedCombinations{{1, 3, 5}};
    EXPECT_EQ(expectedCombinations, actualCombinations);
}

}  // namespace algorithm

}  // namespace alba
