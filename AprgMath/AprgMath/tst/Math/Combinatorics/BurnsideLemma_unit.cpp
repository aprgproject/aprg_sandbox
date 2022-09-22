#include <Math/Combinatorics/BurnsideLemma.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace math
{

TEST(BurnsideLemmaTest, GetNumberOfSymmetricCombinationsUsingBurnsideLemmaWorks)
{
    UnsignedIntegerBinaryFunction const getNumberOfCombinationsFunction = [](
            UnsignedInteger const nWays, UnsignedInteger const kthWay)
    {
        return nWays*kthWay;
    };

    EXPECT_EQ(0U, getNumberOfSymmetricCombinationsUsingBurnsideLemma(0U, getNumberOfCombinationsFunction));
    EXPECT_EQ(1U, getNumberOfSymmetricCombinationsUsingBurnsideLemma(1U, getNumberOfCombinationsFunction));
    EXPECT_EQ(3U, getNumberOfSymmetricCombinationsUsingBurnsideLemma(2U, getNumberOfCombinationsFunction));
    EXPECT_EQ(6U, getNumberOfSymmetricCombinationsUsingBurnsideLemma(3U, getNumberOfCombinationsFunction));
    EXPECT_EQ(10U, getNumberOfSymmetricCombinationsUsingBurnsideLemma(4U, getNumberOfCombinationsFunction));
    EXPECT_EQ(15U, getNumberOfSymmetricCombinationsUsingBurnsideLemma(5U, getNumberOfCombinationsFunction));
}

TEST(BurnsideLemmaTest, GetNumberOfCombinationsOfAPearlNecklaceWorks)
{
    EXPECT_EQ(0U, getNumberOfCombinationsOfAPearlNecklace(0U, 0U));
    EXPECT_EQ(0U, getNumberOfCombinationsOfAPearlNecklace(0U, 1U));
    EXPECT_EQ(0U, getNumberOfCombinationsOfAPearlNecklace(4U, 0U));
    EXPECT_EQ(1U, getNumberOfCombinationsOfAPearlNecklace(4U, 1U));
    EXPECT_EQ(6U, getNumberOfCombinationsOfAPearlNecklace(4U, 2U));
    EXPECT_EQ(24U, getNumberOfCombinationsOfAPearlNecklace(4U, 3U));
    EXPECT_EQ(70U, getNumberOfCombinationsOfAPearlNecklace(4U, 4U));
    EXPECT_EQ(11U, getNumberOfCombinationsOfAPearlNecklace(3U, 3U));
    EXPECT_EQ(976887U, getNumberOfCombinationsOfAPearlNecklace(10U, 5U));
}
}

}
