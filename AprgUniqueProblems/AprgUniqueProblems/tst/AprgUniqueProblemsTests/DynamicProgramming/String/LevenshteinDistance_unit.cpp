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
    LevenshteinDistance searchToTest("MOVIE", "LOVE");

    EXPECT_EQ(2U, searchToTest.getLevenshteinDistanceUsingRecursion());
    EXPECT_EQ(2U, searchToTest.getLevenshteinDistanceUsingTabularDP());
    EXPECT_EQ(2U, searchToTest.getLevenshteinDistanceUsingEfficientSpaceDP());
    EXPECT_EQ(2U, searchToTest.getLevenshteinDistanceUsingMemoizationDP());
}

TEST(LevenshteinDistanceTest, GetLevenshteinDistanceWorksOnExample2)
{
    LevenshteinDistance searchToTest("This is a statement", "This is not a statement");

    EXPECT_EQ(4U, searchToTest.getLevenshteinDistanceUsingRecursion());
    EXPECT_EQ(4U, searchToTest.getLevenshteinDistanceUsingTabularDP());
    EXPECT_EQ(4U, searchToTest.getLevenshteinDistanceUsingEfficientSpaceDP());
    EXPECT_EQ(4U, searchToTest.getLevenshteinDistanceUsingMemoizationDP());
}

}
