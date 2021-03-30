#include <Math/AlbaMathHelper.hpp>

#include <gtest/gtest.h>

#include <iostream>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

TEST(AlbaMathHelperTest, DoubleTypesCanBeConsideredEqual)
{
    EXPECT_TRUE(isConsideredEqual(static_cast<double>(1)/3,static_cast<double>(1)/3));
    EXPECT_FALSE(isConsideredEqual(static_cast<double>(1)/3,static_cast<double>(1)/3+0.1));
    EXPECT_TRUE(isConsideredEqual(static_cast<double>(1)/3,static_cast<double>(1)/3+0.000000000001));
    EXPECT_FALSE(isConsideredEqual(static_cast<double>(0),0.000000000001));
    EXPECT_FALSE(isConsideredEqual(0.000000000001,0.000000000000000000000001));
    EXPECT_TRUE(isConsideredEqual(0.000000000000000000000001,0.000000000000000000000001));
}

TEST(AlbaMathHelperTest, IntegerTypesCanBeConsideredEqual)
{
    EXPECT_TRUE(isConsideredEqual(static_cast<int>(100), static_cast<int>(100)));
}

TEST(AlbaMathHelperTest, DistanceOfTwoNumbersCanBeComputed)
{
    EXPECT_EQ(90, getDistance(-100,-10));
    EXPECT_EQ(20, getDistance(10,-10));
    EXPECT_EQ(20, getDistance(-10,10));
    EXPECT_EQ(90, getDistance(10,100));
}

TEST(AlbaMathHelperTest, AverageOfTwoNumbersCanBeComputed)
{
    EXPECT_EQ(0, getAverage(-10,10));
    EXPECT_EQ(55, getAverage(10,100));
}

TEST(AlbaMathHelperTest, AbsoluteValueCanBeComputed)
{
    EXPECT_EQ(1, getAbsoluteValue(1));
    EXPECT_EQ(1, getAbsoluteValue(-1));
    EXPECT_EQ(0, getAbsoluteValue(0));
    EXPECT_EQ(0.5, getAbsoluteValue(0.5));
    EXPECT_EQ(0.5, getAbsoluteValue(-0.5));
}

TEST(AlbaMathHelperTest, SquareRootOfXSquaredPlusYSquaredCanBeComputed)
{
    EXPECT_EQ(5, getSquareRootOfXSquaredPlusYSquared(3,4));
    EXPECT_EQ(13, getSquareRootOfXSquaredPlusYSquared(5,-12));
    EXPECT_EQ(25, getSquareRootOfXSquaredPlusYSquared(-7,24));
    EXPECT_EQ(17, getSquareRootOfXSquaredPlusYSquared(-8,-15));
}

TEST(AlbaMathHelperTest, SquareRootOfXSquaredPlusYSquaredPlusZSquaredCanBeComputed)
{
    EXPECT_EQ(3, getSquareRootOfXSquaredPlusYSquaredPlusZSquared(1,2,2));
    EXPECT_EQ(15, getSquareRootOfXSquaredPlusYSquaredPlusZSquared(-2,10,11));
    EXPECT_EQ(21, getSquareRootOfXSquaredPlusYSquaredPlusZSquared(4,-13,16));
    EXPECT_EQ(27, getSquareRootOfXSquaredPlusYSquaredPlusZSquared(2,10,-25));
    EXPECT_EQ(7, getSquareRootOfXSquaredPlusYSquaredPlusZSquared(-2,-3,-6));
}

TEST(AlbaMathHelperTest, SignCanBeFetched)
{
    EXPECT_EQ(-1, getSign(-10));
    EXPECT_EQ(1, getSign(0));
    EXPECT_EQ(1, getSign(10));
}

TEST(AlbaMathHelperTest, LowerBoundCanBeComputed)
{
    EXPECT_EQ(3, clampLowerBound(1, 3));
    EXPECT_EQ(3, clampLowerBound(2, 3));
    EXPECT_EQ(3, clampLowerBound(3, 3));
    EXPECT_EQ(4, clampLowerBound(4, 3));
    EXPECT_EQ(5, clampLowerBound(5, 3));
}

TEST(AlbaMathHelperTest, HigherBoundCanBeComputed)
{
    EXPECT_EQ(1, clampHigherBound(1, 3));
    EXPECT_EQ(2, clampHigherBound(2, 3));
    EXPECT_EQ(3, clampHigherBound(3, 3));
    EXPECT_EQ(3, clampHigherBound(4, 3));
    EXPECT_EQ(3, clampHigherBound(5, 3));
}

TEST(AlbaMathHelperTest, DifferenceFromGreaterMultipleCanBeComputed)
{
    EXPECT_EQ(0u, getDifferenceFromGreaterMultiple(0, 0));
    EXPECT_EQ(0u, getDifferenceFromGreaterMultiple(10, 10));
    EXPECT_EQ(0u, getDifferenceFromGreaterMultiple(5, 10));
    EXPECT_EQ(5u, getDifferenceFromGreaterMultiple(10, 5));
    EXPECT_EQ(48u, getDifferenceFromGreaterMultiple(57, 2346));
}

TEST(AlbaMathHelperTest, CumulativeStandardDistributionApproximationCanBeComputed)
{
    //comparing with Z table, http://sphweb.bumc.bu.edu/otlt/mph-modules/bs/bs704_probability/standardnormaltable.pdf
    EXPECT_DOUBLE_EQ(0.5, calculateCumulativeStandardDistributionApproximation(0));
    EXPECT_DOUBLE_EQ(0.86433393905361732834, calculateCumulativeStandardDistributionApproximation(1.1));
    EXPECT_DOUBLE_EQ(0.0081975359245961311461, calculateCumulativeStandardDistributionApproximation(-2.4));
    EXPECT_DOUBLE_EQ(0.99996696335237056363, calculateCumulativeStandardDistributionApproximation(3.99));
    EXPECT_DOUBLE_EQ(3.3036647629402369943e-005, calculateCumulativeStandardDistributionApproximation(-3.99));
}

TEST(AlbaMathHelperTest, InverseCumulativeStandardDistributionApproximationCanBeComputed)
{
    EXPECT_DOUBLE_EQ(0, calculateInverseCumulativeStandardDistributionApproximation(0.5, 20));
    EXPECT_DOUBLE_EQ(1.0999774932861328125, calculateInverseCumulativeStandardDistributionApproximation(0.86433, 20));
    EXPECT_DOUBLE_EQ(-2.4003314971923828125, calculateInverseCumulativeStandardDistributionApproximation(0.00819, 20));
    EXPECT_DOUBLE_EQ(3.9444065093994140625, calculateInverseCumulativeStandardDistributionApproximation(0.99996, 20));
    EXPECT_DOUBLE_EQ(0, calculateInverseCumulativeStandardDistributionApproximation(3.3036, 20));
}

}
