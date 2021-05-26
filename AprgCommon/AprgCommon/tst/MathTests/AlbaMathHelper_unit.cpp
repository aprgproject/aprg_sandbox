#include <Math/AlbaMathHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

TEST(AlbaMathHelperTest, IsDivisibleWorksAsExpected)
{
    EXPECT_TRUE(isDivisible(1u, 1u));
    EXPECT_FALSE(isDivisible(1u, 5u));
    EXPECT_TRUE(isDivisible(5u, 1u));
    EXPECT_TRUE(isDivisible(256u, 16u));
    EXPECT_FALSE(isDivisible(256u, 17u));
}

TEST(AlbaMathHelperTest, DoubleTypesCanBeConsideredEqual)
{
    EXPECT_TRUE(isAlmostEqual(static_cast<double>(1)/3,static_cast<double>(1)/3));    EXPECT_FALSE(isAlmostEqual(static_cast<double>(1)/3,static_cast<double>(1)/3+0.1));
    EXPECT_TRUE(isAlmostEqual(static_cast<double>(1)/3,static_cast<double>(1)/3+1E-13));
    EXPECT_TRUE(isAlmostEqual(1E-12,1E-12));
    EXPECT_TRUE(isAlmostEqual(static_cast<double>(0),1E-12));    EXPECT_TRUE(isAlmostEqual(static_cast<double>(0),1E-24));
    EXPECT_TRUE(isAlmostEqual(1E-12,1E-24));
    EXPECT_TRUE(isAlmostEqual(1E-24,1E-24));
}

TEST(AlbaMathHelperTest, IntegerTypesCanBeConsideredEqual)
{
    EXPECT_TRUE(isAlmostEqual(static_cast<int>(100), static_cast<int>(100)));
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

TEST(AlbaMathHelperTest, FractionDetailsInLowestFormCanBeComputed)
{
    FractionDetails fractionDetails1(getFractionDetailsInLowestForm(0, 0));
    EXPECT_EQ(1, fractionDetails1.sign);
    EXPECT_EQ(0u, fractionDetails1.numerator);
    EXPECT_EQ(0u, fractionDetails1.denominator);

    FractionDetails fractionDetails2(getFractionDetailsInLowestForm(1, 1));
    EXPECT_EQ(1, fractionDetails2.sign);
    EXPECT_EQ(1u, fractionDetails2.numerator);
    EXPECT_EQ(1u, fractionDetails2.denominator);

    FractionDetails fractionDetails3(getFractionDetailsInLowestForm(16, -32));
    EXPECT_EQ(-1, fractionDetails3.sign);
    EXPECT_EQ(1u, fractionDetails3.numerator);
    EXPECT_EQ(2u, fractionDetails3.denominator);

    FractionDetails fractionDetails4(getFractionDetailsInLowestForm(-98, 56));
    EXPECT_EQ(-1, fractionDetails4.sign);
    EXPECT_EQ(7u, fractionDetails4.numerator);
    EXPECT_EQ(4u, fractionDetails4.denominator);

    FractionDetails fractionDetails5(getFractionDetailsInLowestForm(-15, -20));
    EXPECT_EQ(1, fractionDetails5.sign);
    EXPECT_EQ(3u, fractionDetails5.numerator);
    EXPECT_EQ(4u, fractionDetails5.denominator);
}

TEST(AlbaMathHelperTest, GreatestCommonFactorCanBeComputed)
{
    EXPECT_EQ(0u, getGreatestCommonFactor(0, 0));
    EXPECT_EQ(1u, getGreatestCommonFactor(1, 1));
    EXPECT_EQ(16u, getGreatestCommonFactor(16, 32));
    EXPECT_EQ(14u, getGreatestCommonFactor(98, 56));
}

TEST(AlbaMathHelperTest, LeastCommonMultipleCanBeComputed)
{
    EXPECT_EQ(0u, getLeastCommonMultiple(0, 0));
    EXPECT_EQ(1u, getLeastCommonMultiple(1, 1));
    EXPECT_EQ(256u, getLeastCommonMultiple(8, 256));
    EXPECT_EQ(60u, getLeastCommonMultiple(15, 20));
}

TEST(AlbaMathHelperTest, DifferenceFromGreaterMultipleCanBeComputed)
{
    EXPECT_EQ(0u, getDifferenceFromGreaterMultiple(0, 0));    EXPECT_EQ(0u, getDifferenceFromGreaterMultiple(10, 10));
    EXPECT_EQ(0u, getDifferenceFromGreaterMultiple(5, 10));
    EXPECT_EQ(5u, getDifferenceFromGreaterMultiple(10, 5));
    EXPECT_EQ(48u, getDifferenceFromGreaterMultiple(57, 2346));}

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
