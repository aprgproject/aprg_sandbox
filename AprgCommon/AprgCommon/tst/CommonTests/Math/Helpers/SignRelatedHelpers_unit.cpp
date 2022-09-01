#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace mathHelper
{

TEST(AlbaMathHelperTest, GetAbsoluteValueWorksForPrimitiveTypes)
{
    EXPECT_EQ(1, getAbsoluteValue(1));
    EXPECT_EQ(1, getAbsoluteValue(-1));
    EXPECT_EQ(0, getAbsoluteValue(0));
    EXPECT_EQ(0.5, getAbsoluteValue(0.5));
    EXPECT_EQ(0.5, getAbsoluteValue(-0.5));
}

TEST(AlbaMathHelperTest, GetAbsoluteValueForAlbaNumberWorks)
{
    EXPECT_EQ(AlbaNumber::createFraction(1, 3), getAbsoluteValue(AlbaNumber::createFraction(1, 3)));
    EXPECT_EQ(AlbaNumber::createFraction(1, 3), getAbsoluteValue(AlbaNumber::createFraction(-1, 3)));
}

TEST(AlbaMathHelperTest, GetSignWorksForPrimitiveTypes)
{
    EXPECT_EQ(-1, getSign(-10));
    EXPECT_EQ(1, getSign(0));
    EXPECT_EQ(1, getSign(10));
}

TEST(AlbaMathHelperTest, GetSignForAlbaNumberWorks)
{
    EXPECT_EQ(AlbaNumber(1), getSign(AlbaNumber::createFraction(1, 3)));
    EXPECT_EQ(AlbaNumber(-1), getSign(AlbaNumber::createFraction(-1, 3)));
}

TEST(AlbaMathHelperTest, GetPositiveDeltaWorksForPrimitiveTypes)
{
    EXPECT_EQ(0U, getPositiveDelta(0U, 0U));
    EXPECT_EQ(0U, getPositiveDelta(5U, 5U));
    EXPECT_EQ(5U, getPositiveDelta(5U, 10U));
    EXPECT_EQ(5U, getPositiveDelta(10U, 5U));
    EXPECT_EQ(90, getPositiveDelta(-100,-10));
    EXPECT_EQ(20, getPositiveDelta(10,-10));
    EXPECT_EQ(20, getPositiveDelta(-10,10));
    EXPECT_EQ(90, getPositiveDelta(10,100));
}

TEST(AlbaMathHelperTest, GetPositiveDeltaForAlbaNumberWorks)
{
    EXPECT_EQ(AlbaNumber(4.444), getPositiveDelta(AlbaNumber(1.234), AlbaNumber(5.678)));
    EXPECT_EQ(AlbaNumber(4.444), getPositiveDelta(AlbaNumber(5.678), AlbaNumber(1.234)));
}

TEST(AlbaMathHelperTest, ConvertToIntegerThenSubtractWorks)
{
    EXPECT_EQ(0, convertToIntegerThenSubtract(0U, 0U));
    EXPECT_EQ(0, convertToIntegerThenSubtract(5U, 5U));
    EXPECT_EQ(4, convertToIntegerThenSubtract(5U, 1U));
    EXPECT_EQ(-4, convertToIntegerThenSubtract(1U, 5U));
}

}

}
