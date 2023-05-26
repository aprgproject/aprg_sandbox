#include <AprgUniqueProblems/DynamicProgramming/KnapsackProblems/AllPartialSumsInKnapsack.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace {
using Value = AllPartialSumsInKnapsack::Value;
using Values = AllPartialSumsInKnapsack::Values;
}  // namespace

TEST(AllPartialSumsInKnapsackTest, GetAllPossiblePartialSumsWorksOnExample1) {
    AllPartialSumsInKnapsack queryForTest({1, 3, 3, 5});

    Values expectedValues{0, 1, 3, 4, 5, 6, 7, 8, 9, 11, 12};
    EXPECT_EQ(expectedValues, queryForTest.getAllPossiblePartialSums());
}

TEST(AllPartialSumsInKnapsackTest, GetAllPossiblePartialSumsWithSquareRootAlgorithmWorksOnExample1) {
    AllPartialSumsInKnapsack queryForTest({1, 3, 3, 5});

    Values expectedValues{0, 1, 3, 4, 5, 6, 7, 8, 9, 11, 12};
    EXPECT_EQ(expectedValues, queryForTest.getAllPossiblePartialSumsWithSquareRootAlgorithm());
}
}  // namespace alba