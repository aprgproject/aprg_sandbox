#include <AprgUniqueProblems/DynamicProgramming/KnapsackProblem.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace
{
using Value=KnapsackProblem::Value;
using Values=KnapsackProblem::Values;
}

TEST(KnapsackProblemTest, GetAllPossiblePartialSumsWorksOnExample1)
{
    KnapsackProblem searchToTest({1U, 3U, 3U, 5U});

    EXPECT_EQ((Values{0U, 1U, 3U, 4U, 5U, 6U, 7U, 8U, 9U, 11U, 12U}), searchToTest.getAllPossiblePartialSums());
}

}
