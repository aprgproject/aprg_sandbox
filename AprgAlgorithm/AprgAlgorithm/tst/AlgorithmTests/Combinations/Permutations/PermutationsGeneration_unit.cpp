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

    Permutations expectedPermutations{{1, 3, 5}, {1, 5, 3}, {3, 1, 5}, {3, 5, 1}, {5, 1, 3}, {5, 3, 1}};
    EXPECT_EQ(expectedPermutations, actualPermutations);
}

TEST(PermutationsGenerationTest, GeneratePermutationsByBuildingWorks) {
    Permutations actualPermutations(GenerationForTest::generatePermutationsByBuilding({1, 3, 5}));

    Permutations expectedPermutations{{1, 3, 5}, {1, 5, 3}, {3, 1, 5}, {3, 5, 1}, {5, 1, 3}, {5, 3, 1}};
    EXPECT_EQ(expectedPermutations, actualPermutations);
}

TEST(PermutationsGenerationTest, GeneratePermutationsByBuildingWithLengthWorks) {
    Permutations actualPermutations(GenerationForTest::generatePermutationsByBuildingWithLength({1, 3, 5}, 2));

    Permutations expectedPermutations{{1, 3}, {1, 5}, {3, 1}, {3, 5}, {5, 1}, {5, 3}};
    EXPECT_EQ(expectedPermutations, actualPermutations);
}

TEST(PermutationsGenerationTest, GeneratePermutationsBySwappingWorks) {
    Permutations actualPermutations(GenerationForTest::generatePermutationsBySwapping({1, 3, 5}));

    Permutations expectedPermutations{{1, 3, 5}, {1, 5, 3}, {3, 1, 5}, {3, 5, 1}, {5, 3, 1}, {5, 1, 3}};
    EXPECT_EQ(expectedPermutations, actualPermutations);
}

TEST(PermutationsGenerationTest, GeneratePermutationsBySwappingInRangeWorks) {
    Permutations actualPermutations(GenerationForTest::generatePermutationsBySwappingInRange({1, 3, 5, 7}, 1, 2));

    Permutations expectedPermutations{{{1, 3, 5, 7}, {1, 5, 3, 7}}};
    EXPECT_EQ(expectedPermutations, actualPermutations);
}

}  // namespace algorithm

}  // namespace alba