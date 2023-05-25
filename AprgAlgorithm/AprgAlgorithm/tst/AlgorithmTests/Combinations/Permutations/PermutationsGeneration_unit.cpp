#include <Algorithm/Combinatorics/Permutations/PermutationsGeneration.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using Objects = vector<int>;
using GenerationForTest = PermutationsGeneration<Objects>;
using Permutations = GenerationForTest::Permutations;
}  // namespace

TEST(PermutationsGenerationTest, GeneratePermutationsUsingCppFunctionsWorks) {
    Permutations actualPermutations(GenerationForTest::generatePermutationsUsingCppFunctions({1, 3, 5}));

    Permutations expectedPermutations{{1, 3, 5}, {1, 5, 3}, {3, 1, 5},
                                      {3, 5, 1}, {5, 1, 3}, {5, 3, 1}};
    EXPECT_EQ(expectedPermutations, actualPermutations);
}

TEST(PermutationsGenerationTest, GeneratePermutationsUsingRecursionWorks) {
    Permutations actualPermutations(GenerationForTest::generatePermutationsUsingRecursion({1, 3, 5}));

    Permutations expectedPermutations{{1, 3, 5}, {1, 5, 3}, {3, 1, 5},
                                      {3, 5, 1}, {5, 1, 3}, {5, 3, 1}};
    EXPECT_EQ(expectedPermutations, actualPermutations);
}

TEST(PermutationsGenerationTest, GeneratePermutationsWithLengthWorks) {
    Permutations actualPermutations(GenerationForTest::generatePermutationsWithLength({1, 3, 5}, 2));

    Permutations expectedPermutations{{1, 3}, {1, 5}, {3, 1}, {3, 5}, {5, 1}, {5, 3}};
    EXPECT_EQ(expectedPermutations, actualPermutations);
}

}  // namespace algorithm

}  // namespace alba
