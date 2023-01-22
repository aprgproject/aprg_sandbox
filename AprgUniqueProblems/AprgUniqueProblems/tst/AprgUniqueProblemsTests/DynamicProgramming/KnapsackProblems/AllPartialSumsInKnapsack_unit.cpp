#include <AprgUniqueProblems/DynamicProgramming/KnapsackProblems/AllPartialSumsInKnapsack.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace
{
using Value=AllPartialSumsInKnapsack::Value;
using Values=AllPartialSumsInKnapsack::Values;
}

TEST(AllPartialSumsInKnapsackTest, GetAllPossiblePartialSumsWorksOnExample1)
{
    AllPartialSumsInKnapsack queryForTest({1U, 3U, 3U, 5U});

    Values expectedValues{0U, 1U, 3U, 4U, 5U, 6U, 7U, 8U, 9U, 11U, 12U};
    EXPECT_EQ(expectedValues, queryForTest.getAllPossiblePartialSums());
}

TEST(AllPartialSumsInKnapsackTest, GetAllPossiblePartialSumsWithSquareRootAlgorithmWorksOnExample1)
{
    AllPartialSumsInKnapsack queryForTest({1U, 3U, 3U, 5U});

    Values expectedValues{0U, 1U, 3U, 4U, 5U, 6U, 7U, 8U, 9U, 11U, 12U};
    EXPECT_EQ(expectedValues, queryForTest.getAllPossiblePartialSumsWithSquareRootAlgorithm());
}

}
