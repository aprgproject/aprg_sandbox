#include <AprgUniqueProblems/DynamicProgramming/LevenshteinDistance.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace
{
using Distance=LevenshteinDistance::Distance;
}

TEST(LevenshteinDistanceTest, GetMaxSumInRightOrDownTraversalWorksOnExample1)
{
    LevenshteinDistance searchToTest("MOVIE", "LOVE");

    EXPECT_EQ(2U, searchToTest.getLevenshteinDistance());
}

TEST(LevenshteinDistanceTest, GetMaxSumInRightOrDownTraversalWorksOnExample2)
{
    LevenshteinDistance searchToTest("This is a statement", "This is not a statement");

    EXPECT_EQ(4U, searchToTest.getLevenshteinDistance());
}

}
