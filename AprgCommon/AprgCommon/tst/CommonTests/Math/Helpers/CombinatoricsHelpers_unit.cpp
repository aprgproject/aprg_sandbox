#include <Common/Math/Helpers/CombinatoricsHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace mathHelper
{

TEST(AlbaMathHelperTest, GetFactorialWorks)
{
    EXPECT_EQ(1U, getFactorial(0U));
    EXPECT_EQ(1U, getFactorial(1U));
    EXPECT_EQ(120U, getFactorial(5U));
    EXPECT_EQ(3628800U, getFactorial(10U));
}

TEST(AlbaMathHelperTest, GetNumberOfPermutationsWorks)
{
    EXPECT_EQ(24U, getNumberOfPermutations(4U, 4U));
    EXPECT_EQ(1U, getNumberOfPermutations(4U, 0U));
    EXPECT_EQ(4U, getNumberOfPermutations(4U, 1U));
    EXPECT_EQ(0U, getNumberOfPermutations(4U, 5U));
}

TEST(AlbaMathHelperTest, GetNumberOfCombinationsWorks)
{
    EXPECT_EQ(1U, getNumberOfCombinations(4U, 4U));
    EXPECT_EQ(1U, getNumberOfCombinations(4U, 0U));
    EXPECT_EQ(4U, getNumberOfCombinations(4U, 1U));
    EXPECT_EQ(0U, getNumberOfCombinations(4U, 5U));
}

TEST(AlbaMathHelperTest, GetValueAtPascalTriangleWorks)
{
    EXPECT_EQ(1U, getValueAtPascalTriangle(0U, 0U));
    EXPECT_EQ(1U, getValueAtPascalTriangle(4U, 4U));
    EXPECT_EQ(1U, getValueAtPascalTriangle(4U, 0U));
    EXPECT_EQ(4U, getValueAtPascalTriangle(4U, 1U));
    EXPECT_EQ(6U, getValueAtPascalTriangle(4U, 2U));
    EXPECT_EQ(0U, getValueAtPascalTriangle(4U, 5U));
}

TEST(AlbaMathHelperTest, GetStirlingNumberOfTheSecondKindWorks)
{
    EXPECT_EQ(1, getStirlingNumberOfTheSecondKind(0, 0));
    EXPECT_EQ(0, getStirlingNumberOfTheSecondKind(3, 0));
    EXPECT_EQ(1, getStirlingNumberOfTheSecondKind(3, 1));
    EXPECT_EQ(3, getStirlingNumberOfTheSecondKind(3, 2));
    EXPECT_EQ(1, getStirlingNumberOfTheSecondKind(3, 3));
    EXPECT_EQ(0, getStirlingNumberOfTheSecondKind(10, 0));
    EXPECT_EQ(1, getStirlingNumberOfTheSecondKind(10, 1));
    EXPECT_EQ(511, getStirlingNumberOfTheSecondKind(10, 2));
    EXPECT_EQ(42525, getStirlingNumberOfTheSecondKind(10, 5));
    EXPECT_EQ(1, getStirlingNumberOfTheSecondKind(10, 10));
}

}

}
