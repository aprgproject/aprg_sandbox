#include <AprgUniqueProblems/DynamicProgramming/Other/OptimalBinarySearchTree.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(OptimalBinarySearchTreeTest, GetMinimumCostWorksOnExample1)
{
    OptimalBinarySearchTree queryForTest({{10, 34}, {12, 50}});

    EXPECT_EQ(118U, queryForTest.getMinimumCostUsingNaiveRecursion());
    EXPECT_EQ(118U, queryForTest.getMinimumCostUsingTabularDP());
}

TEST(OptimalBinarySearchTreeTest, GetMinimumCostWorksOnExample2)
{
    OptimalBinarySearchTree queryForTest({{10, 34}, {12, 8}, {20, 50}});

    EXPECT_EQ(142U, queryForTest.getMinimumCostUsingNaiveRecursion());
    EXPECT_EQ(142U, queryForTest.getMinimumCostUsingTabularDP());
}

}
