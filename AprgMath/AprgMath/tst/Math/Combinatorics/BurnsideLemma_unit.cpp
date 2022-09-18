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
    EXPECT_EQ(24U, getNumberOfCombinationsOfAPearlNecklace(4U, 3U));
}

}

}
