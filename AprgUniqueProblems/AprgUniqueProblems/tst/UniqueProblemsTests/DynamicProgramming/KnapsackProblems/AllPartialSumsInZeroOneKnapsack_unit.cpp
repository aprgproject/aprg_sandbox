#include <UniqueProblems/DynamicProgramming/KnapsackProblems/AllPartialSumsInZeroOneKnapsack.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba {
namespace {
using Value = AllPartialSumsInZeroOneKnapsack::Value;
using Values = AllPartialSumsInZeroOneKnapsack::Values;
}  // namespace

TEST(AllPartialSumsInZeroOneKnapsackTest, GetAllPossiblePartialSumsWorksOnExample1) {
    AllPartialSumsInZeroOneKnapsack queryForTest({1, 3, 3, 5});

    Values expectedValues{0, 1, 3, 4, 5, 6, 7, 8, 9, 11, 12};
    EXPECT_EQ(expectedValues, queryForTest.getAllPossiblePartialSums());
}

TEST(AllPartialSumsInZeroOneKnapsackTest, GetAllPossiblePartialSumsWithSquareRootAlgorithmWorksOnExample1) {
    AllPartialSumsInZeroOneKnapsack queryForTest({1, 3, 3, 5});

    Values expectedValues{0, 1, 3, 4, 5, 6, 7, 8, 9, 11, 12};
    EXPECT_EQ(expectedValues, queryForTest.getAllPossiblePartialSumsWithSquareRootAlgorithm());
}

}  // namespace alba
