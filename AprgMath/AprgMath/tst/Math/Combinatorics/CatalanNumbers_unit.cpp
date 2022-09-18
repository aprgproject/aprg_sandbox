#include <Math/Combinatorics/CatalanNumbers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace math
{

TEST(CatalanNumbersTest, GetCatalanNumberWorks)
{
    EXPECT_EQ(1U, getCatalanNumber(0U));
    EXPECT_EQ(1U, getCatalanNumber(1U));
    EXPECT_EQ(2U, getCatalanNumber(2U));
    EXPECT_EQ(5U, getCatalanNumber(3U));
    EXPECT_EQ(14U, getCatalanNumber(4U));
    EXPECT_EQ(42U, getCatalanNumber(5U));
    EXPECT_EQ(16796U, getCatalanNumber(10U));
    EXPECT_EQ(9694845U, getCatalanNumber(15U));
    EXPECT_EQ(129644790U, getCatalanNumber(17U));
}

TEST(CatalanNumbersTest, GetNumberOfBinaryTreesWorks)
{
    EXPECT_EQ(1U, getNumberOfBinaryTrees(0U));
    EXPECT_EQ(1U, getNumberOfBinaryTrees(1U));
    EXPECT_EQ(2U, getNumberOfBinaryTrees(2U));
    EXPECT_EQ(5U, getNumberOfBinaryTrees(3U));
    EXPECT_EQ(14U, getNumberOfBinaryTrees(4U));
    EXPECT_EQ(42U, getNumberOfBinaryTrees(5U));
    EXPECT_EQ(16796U, getNumberOfBinaryTrees(10U));
    EXPECT_EQ(9694845U, getNumberOfBinaryTrees(15U));
    EXPECT_EQ(129644790U, getNumberOfBinaryTrees(17U));
}

TEST(CatalanNumbersTest, GetNumberOfRootedTreesWorks)
{
    EXPECT_EQ(1U, getNumberOfRootedTrees(1U));
    EXPECT_EQ(1U, getNumberOfRootedTrees(2U));
    EXPECT_EQ(2U, getNumberOfRootedTrees(3U));
    EXPECT_EQ(5U, getNumberOfRootedTrees(4U));
    EXPECT_EQ(14U, getNumberOfRootedTrees(5U));
    EXPECT_EQ(42U, getNumberOfRootedTrees(6U));
    EXPECT_EQ(16796U, getNumberOfRootedTrees(11U));
    EXPECT_EQ(9694845U, getNumberOfRootedTrees(16U));
    EXPECT_EQ(129644790U, getNumberOfRootedTrees(18U));
}

}

}