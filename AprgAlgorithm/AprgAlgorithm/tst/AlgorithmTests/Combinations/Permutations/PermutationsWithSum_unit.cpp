#include <Algorithm/Combinatorics/Permutations/PermutationsWithSum.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using Values = vector<int>;
using GenerationForTest = PermutationsWithSum<Values>;
using Permutations = GenerationForTest::Permutations;
}  // namespace

TEST(PermutationsWithSumTest, GetPermutationsWithSumUsingLoopsWorks) {
    Values inputValues{1, 2, 3, 4};
    GenerationForTest generation(inputValues);

    Permutations actualPermutations(generation.getPermutationsWithSumUsingLoops(4));

    Permutations expectedPermutations{{1, 1, 1, 1}, {1, 1, 2}, {1, 2, 1}, {1, 3}, {2, 1, 1}, {2, 2}, {3, 1}, {4}};
    EXPECT_EQ(expectedPermutations, actualPermutations);
}

}  // namespace algorithm

}  // namespace alba
