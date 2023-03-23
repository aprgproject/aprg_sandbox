#include <AprgUniqueProblems/DynamicProgramming/String/LevenshteinDistance.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace
{
using Distance=LevenshteinDistance::Index;
}

TEST(LevenshteinDistanceTest, GetLevenshteinDistanceWorksOnExample1)
{
    LevenshteinDistance queryForTest("MOVIE", "LOVE");

    EXPECT_EQ(2U, queryForTest.getLevenshteinDistanceUsingNaiveRecursion());
    EXPECT_EQ(2U, queryForTest.getLevenshteinDistanceUsingMemoizationDP());
    EXPECT_EQ(2U, queryForTest.getLevenshteinDistanceUsingIterativeDP());
    EXPECT_EQ(2U, queryForTest.getLevenshteinDistanceUsingIterativeDPAndSpaceEfficient());
}

TEST(LevenshteinDistanceTest, GetLevenshteinDistanceWorksOnExample2)
{
    LevenshteinDistance queryForTest("This is a statement", "This is not a statement");

    EXPECT_EQ(4U, queryForTest.getLevenshteinDistanceUsingNaiveRecursion());    EXPECT_EQ(4U, queryForTest.getLevenshteinDistanceUsingMemoizationDP());
    EXPECT_EQ(4U, queryForTest.getLevenshteinDistanceUsingIterativeDP());
    EXPECT_EQ(4U, queryForTest.getLevenshteinDistanceUsingIterativeDPAndSpaceEfficient());
}

}
