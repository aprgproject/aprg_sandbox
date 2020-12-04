#include <Math/AlbaMathHelper.hpp>

#include <gtest/gtest.h>

#include <iostream>

using namespace alba;
using namespace std;
using namespace alba::mathHelper;

TEST(AlbaMathHelperTest, AbsoluteValueCanbeComputed)
{
    EXPECT_EQ(1, getAbsoluteValue(1));
    EXPECT_EQ(1, getAbsoluteValue(-1));
    EXPECT_EQ(0, getAbsoluteValue(0));
    EXPECT_EQ(0.5, getAbsoluteValue(0.5));
    EXPECT_EQ(0.5, getAbsoluteValue(-0.5));
}

TEST(AlbaMathHelperTest, LowerBoundCanbeComputed)
{
    EXPECT_EQ(3, clampLowerBound(1, 3));
    EXPECT_EQ(3, clampLowerBound(2, 3));
    EXPECT_EQ(3, clampLowerBound(3, 3));
    EXPECT_EQ(4, clampLowerBound(4, 3));
    EXPECT_EQ(5, clampLowerBound(5, 3));
}

TEST(AlbaMathHelperTest, HigherBoundCanbeComputed)
{
    EXPECT_EQ(1, clampHigherBound(1, 3));
    EXPECT_EQ(2, clampHigherBound(2, 3));
    EXPECT_EQ(3, clampHigherBound(3, 3));
    EXPECT_EQ(3, clampHigherBound(4, 3));
    EXPECT_EQ(3, clampHigherBound(5, 3));
}

TEST(AlbaMathHelperTest, DifferenceFromGreaterMultipleCanBeComputed)
{
    EXPECT_EQ(0, getDifferenceFromGreaterMultiple(0, 0));
    EXPECT_EQ(0, getDifferenceFromGreaterMultiple(10, 10));
    EXPECT_EQ(0, getDifferenceFromGreaterMultiple(5, 10));
    EXPECT_EQ(5, getDifferenceFromGreaterMultiple(10, 5));
    EXPECT_EQ(48, getDifferenceFromGreaterMultiple(57, 2346));
}