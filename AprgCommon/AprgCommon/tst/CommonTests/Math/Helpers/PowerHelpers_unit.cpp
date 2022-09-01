#include <Common/Math/Helpers/PowerHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace mathHelper
{

TEST(AlbaMathHelperTest, IsPowerOfTwoForUnsignedIntWorks)
{
    EXPECT_TRUE(isPowerOfTwo(0U));
    EXPECT_TRUE(isPowerOfTwo(1U));
    EXPECT_TRUE(isPowerOfTwo(2U));
    EXPECT_FALSE(isPowerOfTwo(3U));
    EXPECT_TRUE(isPowerOfTwo(4U));
}

TEST(AlbaMathHelperTest, IsPerfectSquareForUnsignedIntWorks)
{
    EXPECT_TRUE(isPerfectSquare(0U));
    EXPECT_TRUE(isPerfectSquare(1U));
    EXPECT_FALSE(isPerfectSquare(3U));
    EXPECT_TRUE(isPerfectSquare(4U));
    EXPECT_TRUE(isPerfectSquare(100U));
    EXPECT_FALSE(isPerfectSquare(101U));
}

TEST(AlbaMathHelperTest, IsPerfectCubeForUnsignedIntWorks)
{
    EXPECT_TRUE(isPerfectCube(0U));
    EXPECT_TRUE(isPerfectCube(1U));
    EXPECT_TRUE(isPerfectCube(8U));
    EXPECT_FALSE(isPerfectCube(9U));
    EXPECT_TRUE(isPerfectCube(1000U));
    EXPECT_FALSE(isPerfectCube(1001U));
}

TEST(AlbaMathHelperTest, IsPerfectNthPowerForUnsignedIntWorks)
{
    EXPECT_TRUE(isPerfectNthPower(0U, 0U));
    EXPECT_TRUE(isPerfectNthPower(1U, 1U));
    EXPECT_FALSE(isPerfectNthPower(100U, 0U));
    EXPECT_TRUE(isPerfectNthPower(100U, 1U));
    EXPECT_TRUE(isPerfectNthPower(100U, 2U));
    EXPECT_FALSE(isPerfectNthPower(101U, 2U));
    EXPECT_TRUE(isPerfectNthPower(1000U, 3U));
    EXPECT_FALSE(isPerfectNthPower(1001U, 3U));
}

TEST(AlbaMathHelperTest, IsPerfectCubeForAlbaNumberWorks)
{
    EXPECT_TRUE(isPerfectCube(AlbaNumber(0)));
    EXPECT_TRUE(isPerfectCube(AlbaNumber(1)));
    EXPECT_TRUE(isPerfectCube(AlbaNumber(8)));
    EXPECT_FALSE(isPerfectCube(AlbaNumber(9)));
    EXPECT_TRUE(isPerfectCube(AlbaNumber(1000)));
    EXPECT_FALSE(isPerfectCube(AlbaNumber(1001)));
    EXPECT_TRUE(isPerfectCube(AlbaNumber::createFraction(1000, 27)));
    EXPECT_FALSE(isPerfectCube(AlbaNumber::createFraction(1000, 26)));
}

TEST(AlbaMathHelperTest, IsPerfectSquareForAlbaNumberWorks)
{
    EXPECT_TRUE(isPerfectSquare(AlbaNumber(0)));
    EXPECT_TRUE(isPerfectSquare(AlbaNumber(1)));
    EXPECT_FALSE(isPerfectSquare(AlbaNumber(3)));
    EXPECT_TRUE(isPerfectSquare(AlbaNumber(4)));
    EXPECT_TRUE(isPerfectSquare(AlbaNumber(100)));
    EXPECT_FALSE(isPerfectSquare(AlbaNumber(101)));
    EXPECT_TRUE(isPerfectSquare(AlbaNumber::createFraction(100, 36)));
    EXPECT_FALSE(isPerfectSquare(AlbaNumber::createFraction(100, 37)));
}

TEST(AlbaMathHelperTest, IsPerfectNthPowerForAlbaNumberWorks)
{
    EXPECT_TRUE(isPerfectNthPower(AlbaNumber(0U), 0U));
    EXPECT_TRUE(isPerfectNthPower(AlbaNumber(1), 1U));
    EXPECT_FALSE(isPerfectNthPower(AlbaNumber(100), 0U));
    EXPECT_TRUE(isPerfectNthPower(AlbaNumber(100), 1U));
    EXPECT_TRUE(isPerfectNthPower(AlbaNumber(100), 2U));
    EXPECT_FALSE(isPerfectNthPower(AlbaNumber(101), 2U));
    EXPECT_TRUE(isPerfectNthPower(AlbaNumber::createFraction(100, 36), 2U));
    EXPECT_FALSE(isPerfectNthPower(AlbaNumber::createFraction(100, 37), 2U));
    EXPECT_TRUE(isPerfectNthPower(AlbaNumber(1000), 3U));
    EXPECT_FALSE(isPerfectNthPower(AlbaNumber(1001), 3U));
    EXPECT_TRUE(isPerfectNthPower(AlbaNumber::createFraction(1000, 27), 3U));
    EXPECT_FALSE(isPerfectNthPower(AlbaNumber::createFraction(1001, 26), 3U));
}

TEST(AlbaMathHelperTest, GetRaiseToPowerForIntegersWorks)
{
    EXPECT_EQ(1, getRaiseToPowerForIntegers(0, 0U));
    EXPECT_EQ(1, getRaiseToPowerForIntegers(1, 0U));
    EXPECT_EQ(0, getRaiseToPowerForIntegers(0, 1U));
    EXPECT_EQ(243, getRaiseToPowerForIntegers(3, 5U));
    EXPECT_EQ(-128, getRaiseToPowerForIntegers(-2, 7U));
}

}

}
