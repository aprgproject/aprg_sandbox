#include <Math/AlbaMathHelper.hpp>

#include <gtest/gtest.h>

#include <climits>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

TEST(AlbaMathHelperTest, GetPiWorks)
{
    EXPECT_DOUBLE_EQ(3.14159265358979323846, getPi());
}

TEST(AlbaMathHelperTest, GetEWorks)
{
    EXPECT_DOUBLE_EQ(2.7182818284590452354, getE());
}

TEST(AlbaMathHelperTest, ConvertRadiansToDegreesWorks)
{
    EXPECT_DOUBLE_EQ(180, convertRadiansToDegrees(getPi()));
    EXPECT_DOUBLE_EQ(572.95779513082323, convertRadiansToDegrees(10));
}

TEST(AlbaMathHelperTest, ConvertDegreesToRadiansWorks)
{
    EXPECT_DOUBLE_EQ(getPi(), convertDegreesToRadians(180));
    EXPECT_DOUBLE_EQ(17.191493132144146, convertDegreesToRadians(985));
}

TEST(AlbaMathHelperTest, IntegerTypesCanBeConsideredEqual)
{
    EXPECT_TRUE(isAlmostEqual(static_cast<int>(100), static_cast<int>(100)));
}

TEST(AlbaMathHelperTest, DoubleTypesCanBeConsideredEqual)
{
    EXPECT_TRUE(isAlmostEqual(static_cast<double>(1)/3, static_cast<double>(1)/3));    EXPECT_FALSE(isAlmostEqual(static_cast<double>(1)/3, static_cast<double>(1)/3+0.1));
    EXPECT_TRUE(isAlmostEqual(static_cast<double>(1)/3, static_cast<double>(1)/3+1E-13));
    EXPECT_TRUE(isAlmostEqual(1E-12, 1E-12));
    EXPECT_FALSE(isAlmostEqual(static_cast<double>(0), 1E-11));    EXPECT_FALSE(isAlmostEqual(static_cast<double>(0), 1E-12));
    EXPECT_TRUE(isAlmostEqual(static_cast<double>(0), 1E-13));
    EXPECT_TRUE(isAlmostEqual(static_cast<double>(0), 1E-24));
    EXPECT_TRUE(isAlmostEqual(1E-12, 1E-24));
    EXPECT_TRUE(isAlmostEqual(1E-24, 1E-24));
    EXPECT_FALSE(isAlmostEqual(2.0, INFINITY));
    EXPECT_TRUE(isAlmostEqual(INFINITY, INFINITY));
    EXPECT_FALSE(isAlmostEqual(INFINITY, -INFINITY));
}

TEST(AlbaMathHelperTest, IsAlmostEqualWorksWithDifferenceTolerance)
{
    EXPECT_TRUE(isAlmostEqual(2.54, 2.55, 1E-1));    EXPECT_TRUE(isAlmostEqual(2.54, 2.55, 1E-2));
    EXPECT_FALSE(isAlmostEqual(2.54, 2.55, 1E-3));
    EXPECT_FALSE(isAlmostEqual(2, INFINITY, 1E-3));
    EXPECT_TRUE(isAlmostEqual(INFINITY, INFINITY, 1E-3));
    EXPECT_FALSE(isAlmostEqual(INFINITY, -INFINITY, 1E-3));
}

TEST(AlbaMathHelperTest, IsAlmostAnIntegerWorks)
{
    EXPECT_TRUE(isAlmostAnInteger(0));
    EXPECT_TRUE(isAlmostAnInteger(1));
    EXPECT_TRUE(isAlmostAnInteger(2));
    EXPECT_FALSE(isAlmostAnInteger(3.00000001));
    EXPECT_TRUE(isAlmostAnInteger(3.0000000000001));
}

TEST(AlbaMathHelperTest, IsAlmostAnIntegerWithDifferenceToleranceWorks)
{
    EXPECT_TRUE(isAlmostAnInteger(3.01, 1E-1));
    EXPECT_TRUE(isAlmostAnInteger(3.01, 1E-2));
    EXPECT_FALSE(isAlmostAnInteger(3.01, 1E-3));
}

TEST(AlbaMathHelperTest, IsValueBeyondLimitsWorksForInteger)
{
    EXPECT_TRUE(isValueBeyondLimits<int>(static_cast<double>(INT_MIN)-1));
    EXPECT_FALSE(isValueBeyondLimits<int>(INT_MIN));
    EXPECT_FALSE(isValueBeyondLimits<int>(1000));
    EXPECT_FALSE(isValueBeyondLimits<int>(INT_MAX));
    EXPECT_TRUE(isValueBeyondLimits<int>(static_cast<double>(INT_MAX)+1));
}

TEST(AlbaMathHelperTest, IsValueBeyondUnsignedIntegerLimitsWorks)
{
    EXPECT_TRUE(isValueBeyondLimits<unsigned int>(static_cast<double>(0)-1));
    EXPECT_FALSE(isValueBeyondLimits<unsigned int>(0));
    EXPECT_FALSE(isValueBeyondLimits<unsigned int>(1000));
    EXPECT_FALSE(isValueBeyondLimits<unsigned int>(UINT_MAX));
    EXPECT_TRUE(isValueBeyondLimits<unsigned int>(static_cast<double>(UINT_MAX)+1));
}

TEST(AlbaMathHelperTest, IsValueBeyondShortIntegerLimitsWorks)
{
    EXPECT_TRUE(isValueBeyondLimits<short int>(static_cast<double>(SHRT_MIN)-1));
    EXPECT_FALSE(isValueBeyondLimits<short int>(SHRT_MIN));
    EXPECT_FALSE(isValueBeyondLimits<short int>(1000));
    EXPECT_FALSE(isValueBeyondLimits<short int>(SHRT_MAX));
    EXPECT_TRUE(isValueBeyondLimits<short int>(static_cast<double>(SHRT_MAX)+1));
}

TEST(AlbaMathHelperTest, IsValueBeyondLongIntegerLimitsWorks)
{
    EXPECT_TRUE(isValueBeyondLimits<long int>(static_cast<double>(LONG_MIN)-1));
    EXPECT_FALSE(isValueBeyondLimits<long int>(LONG_MIN));
    EXPECT_FALSE(isValueBeyondLimits<long int>(1000));
    EXPECT_FALSE(isValueBeyondLimits<long int>(LONG_MAX));
    EXPECT_TRUE(isValueBeyondLimits<long int>(static_cast<double>(LONG_MAX)+1));
}

TEST(AlbaMathHelperTest, IsValueBeyondUnsignedLongIntegerLimitsWorks)
{
    EXPECT_TRUE(isValueBeyondLimits<unsigned long int>(static_cast<double>(0)-1));
    EXPECT_FALSE(isValueBeyondLimits<unsigned long int>(0));
    EXPECT_FALSE(isValueBeyondLimits<unsigned long int>(1000));
    EXPECT_FALSE(isValueBeyondLimits<unsigned long int>(ULONG_MAX));
    EXPECT_TRUE(isValueBeyondLimits<unsigned long int>(static_cast<double>(ULONG_MAX)+1));
}

TEST(AlbaMathHelperTest, IsValueBeyondLongLongIntegerLimitsWorks)
{
    EXPECT_TRUE(isValueBeyondLimits<long long int>(static_cast<double>(LLONG_MIN)*2));
    EXPECT_FALSE(isValueBeyondLimits<long long int>(LLONG_MIN));
    EXPECT_FALSE(isValueBeyondLimits<long long int>(1000));
    EXPECT_FALSE(isValueBeyondLimits<long long int>(LLONG_MAX));
    EXPECT_TRUE(isValueBeyondLimits<long long int>(static_cast<double>(LLONG_MAX)*2));
}

TEST(AlbaMathHelperTest, IsValueBeyondUnsignedLongLongIntegerLimitsWorks)
{
    EXPECT_TRUE(isValueBeyondLimits<unsigned long long int>(static_cast<double>(0)-ULLONG_MAX));
    EXPECT_FALSE(isValueBeyondLimits<unsigned long long int>(0));
    EXPECT_FALSE(isValueBeyondLimits<unsigned long long int>(1000));
    EXPECT_FALSE(isValueBeyondLimits<unsigned long long int>(ULLONG_MAX));
    EXPECT_TRUE(isValueBeyondLimits<unsigned long long int>(static_cast<double>(ULLONG_MAX)*2));
}

TEST(AlbaMathHelperTest, IntegerAfterRoundingDoubleValueWorks)
{
    EXPECT_EQ(0, getIntegerAfterRoundingDoubleValue(0));
    EXPECT_EQ(1, getIntegerAfterRoundingDoubleValue(1));
    EXPECT_EQ(2, getIntegerAfterRoundingDoubleValue(1.5));
    EXPECT_EQ(-2, getIntegerAfterRoundingDoubleValue(-1.5));
    EXPECT_EQ(652, getIntegerAfterRoundingDoubleValue(652.426542));
    EXPECT_EQ(-348, getIntegerAfterRoundingDoubleValue(-347.51514));
}

TEST(AlbaMathHelperTest, IntegerPartInDoubleWorks)
{
    EXPECT_EQ(0, getIntegerPartInDouble(0));
    EXPECT_EQ(1, getIntegerPartInDouble(1));
    EXPECT_EQ(1, getIntegerPartInDouble(1.5));
    EXPECT_EQ(-1, getIntegerPartInDouble(-1.5));
    EXPECT_EQ(652, getIntegerPartInDouble(652.426542));
    EXPECT_EQ(-347, getIntegerPartInDouble(-347.51514));
}

TEST(AlbaMathHelperTest, GetUnsignedIntegerAfterRoundingDoubleValueWorks)
{
    EXPECT_EQ(0u, getUnsignedIntegerAfterRoundingDoubleValue(0));
    EXPECT_EQ(1u, getUnsignedIntegerAfterRoundingDoubleValue(1));
    EXPECT_EQ(2u, getUnsignedIntegerAfterRoundingDoubleValue(1.5));
    EXPECT_EQ(4294967294u, getUnsignedIntegerAfterRoundingDoubleValue(-1.5));
    EXPECT_EQ(652u, getUnsignedIntegerAfterRoundingDoubleValue(652.426542));
    EXPECT_EQ(4294966948u, getUnsignedIntegerAfterRoundingDoubleValue(-347.51514));
}

TEST(AlbaMathHelperTest, FractionalPartInDoubleWorks)
{
    EXPECT_DOUBLE_EQ(0, getFractionalPartInDouble(0));
    EXPECT_DOUBLE_EQ(0, getFractionalPartInDouble(1));
    EXPECT_DOUBLE_EQ(0.5, getFractionalPartInDouble(1.5));
    EXPECT_DOUBLE_EQ(-0.5, getFractionalPartInDouble(-1.5));
    EXPECT_DOUBLE_EQ(0.15625, getFractionalPartInDouble(652.15625));
    EXPECT_DOUBLE_EQ(-0.125, getFractionalPartInDouble(-347.125));
}

TEST(AlbaMathHelperTest, GetAbsoluteValueWorksForPrimitiveTypes)
{
    EXPECT_EQ(1, getAbsoluteValue(1));
    EXPECT_EQ(1, getAbsoluteValue(-1));
    EXPECT_EQ(0, getAbsoluteValue(0));
    EXPECT_EQ(0.5, getAbsoluteValue(0.5));
    EXPECT_EQ(0.5, getAbsoluteValue(-0.5));
}

TEST(AlbaMathHelperTest, GetAbsoluteValueWorksForAlbaNumber)
{
    EXPECT_EQ(AlbaNumber(1, 3), getAbsoluteValue(AlbaNumber(1, 3)));
    EXPECT_EQ(AlbaNumber(1, 3), getAbsoluteValue(AlbaNumber(-1, 3)));
}

TEST(AlbaMathHelperTest, GetSignWorksForPrimitiveTypes)
{
    EXPECT_EQ(-1, getSign(-10));
    EXPECT_EQ(1, getSign(0));
    EXPECT_EQ(1, getSign(10));
}

TEST(AlbaMathHelperTest, GetSignWorksForAlbaNumber)
{
    EXPECT_EQ(AlbaNumber(1), getSign(AlbaNumber(1, 3)));
    EXPECT_EQ(AlbaNumber(-1), getSign(AlbaNumber(-1, 3)));
}

TEST(AlbaMathHelperTest, GetPositiveDeltaAsExpected)
{
    EXPECT_EQ(0u, getPositiveDelta(0u, 0u));
    EXPECT_EQ(0u, getPositiveDelta(5u, 5u));
    EXPECT_EQ(5u, getPositiveDelta(5u, 10u));
    EXPECT_EQ(5u, getPositiveDelta(10u, 5u));
    EXPECT_EQ(90, getPositiveDelta(-100,-10));
    EXPECT_EQ(20, getPositiveDelta(10,-10));
    EXPECT_EQ(20, getPositiveDelta(-10,10));
    EXPECT_EQ(90, getPositiveDelta(10,100));
}

TEST(AlbaMathHelperTest, ConvertToIntegerThenSubtractWorks)
{
    EXPECT_EQ(0, convertToIntegerThenSubtract(0u, 0u));
    EXPECT_EQ(0, convertToIntegerThenSubtract(5u, 5u));
    EXPECT_EQ(-5, convertToIntegerThenSubtract(5u, 10u));
    EXPECT_EQ(5, convertToIntegerThenSubtract(10u, 5u));
}

TEST(AlbaMathHelperTest, GetAverageOfTwoNumbersWorksForPrimitiveTypes)
{
    EXPECT_EQ(0, getAverage(-10, 10));
    EXPECT_EQ(55, getAverage(10, 100));
}

TEST(AlbaMathHelperTest, GetAverageOfTwoNumbersWorksForAlbaNumber)
{
    EXPECT_EQ(AlbaNumber(0), getAverage(AlbaNumber(1, 3), AlbaNumber(-1, 3)));
    EXPECT_EQ(AlbaNumber(1, 3), getAverage(AlbaNumber(1, 3), AlbaNumber(1, 3)));
}

TEST(AlbaMathHelperTest, GetAverageOfThreeNumbersWorks)
{
    EXPECT_EQ(0, getAverage(-10, 10, 0));
    EXPECT_EQ(370, getAverage(10, 100, 1000));
}

TEST(AlbaMathHelperTest, GetXSquaredPlusYSquaredWorks)
{
    EXPECT_EQ(25, getXSquaredPlusYSquared(3, 4));
    EXPECT_EQ(169, getXSquaredPlusYSquared(5, -12));
    EXPECT_EQ(625, getXSquaredPlusYSquared(-7, 24));
    EXPECT_EQ(289, getXSquaredPlusYSquared(-8, -15));
}

TEST(AlbaMathHelperTest, GetSquareRootOfXSquaredPlusYSquaredWorks)
{
    EXPECT_EQ(5, getSquareRootOfXSquaredPlusYSquared(3, 4));
    EXPECT_EQ(13, getSquareRootOfXSquaredPlusYSquared(5, -12));
    EXPECT_EQ(25, getSquareRootOfXSquaredPlusYSquared(-7, 24));
    EXPECT_EQ(17, getSquareRootOfXSquaredPlusYSquared(-8, -15));
}

TEST(AlbaMathHelperTest, GetSquareRootOfXSquaredPlusYSquaredPlusZSquaredWorks)
{
    EXPECT_EQ(3, getSquareRootOfXSquaredPlusYSquaredPlusZSquared(1,2,2));
    EXPECT_EQ(15, getSquareRootOfXSquaredPlusYSquaredPlusZSquared(-2,10,11));
    EXPECT_EQ(21, getSquareRootOfXSquaredPlusYSquaredPlusZSquared(4,-13,16));
    EXPECT_EQ(27, getSquareRootOfXSquaredPlusYSquaredPlusZSquared(2,10,-25));
    EXPECT_EQ(7, getSquareRootOfXSquaredPlusYSquaredPlusZSquared(-2,-3,-6));
}

TEST(AlbaMathHelperTest, CumulativeStandardDistributionApproximationWorks)
{
    //comparing with Z table, http://sphweb.bumc.bu.edu/otlt/mph-modules/bs/bs704_probability/standardnormaltable.pdf
    EXPECT_DOUBLE_EQ(0.5, calculateCumulativeStandardDistributionApproximation(0));
    EXPECT_DOUBLE_EQ(0.86433393905361732834, calculateCumulativeStandardDistributionApproximation(1.1));
    EXPECT_DOUBLE_EQ(0.0081975359245961311461, calculateCumulativeStandardDistributionApproximation(-2.4));
    EXPECT_DOUBLE_EQ(0.99996696335237056363, calculateCumulativeStandardDistributionApproximation(3.99));
    EXPECT_DOUBLE_EQ(3.3036647629402369943e-005, calculateCumulativeStandardDistributionApproximation(-3.99));
}

TEST(AlbaMathHelperTest, InverseCumulativeStandardDistributionApproximationWorks)
{
    EXPECT_DOUBLE_EQ(0, calculateInverseCumulativeStandardDistributionApproximation(0.5, 20));
    EXPECT_DOUBLE_EQ(1.0999774932861328125, calculateInverseCumulativeStandardDistributionApproximation(0.86433, 20));
    EXPECT_DOUBLE_EQ(-2.4003314971923828125, calculateInverseCumulativeStandardDistributionApproximation(0.00819, 20));
    EXPECT_DOUBLE_EQ(3.9444065093994140625, calculateInverseCumulativeStandardDistributionApproximation(0.99996, 20));
    EXPECT_DOUBLE_EQ(0, calculateInverseCumulativeStandardDistributionApproximation(3.3036, 20));
}

TEST(AlbaMathHelperTest, ClampLowerBoundWorks)
{
    EXPECT_EQ(3, clampLowerBound(1, 3));
    EXPECT_EQ(3, clampLowerBound(2, 3));
    EXPECT_EQ(3, clampLowerBound(3, 3));
    EXPECT_EQ(4, clampLowerBound(4, 3));
    EXPECT_EQ(5, clampLowerBound(5, 3));
}

TEST(AlbaMathHelperTest, ClampHigherBoundWorks)
{
    EXPECT_EQ(1, clampHigherBound(1, 3));
    EXPECT_EQ(2, clampHigherBound(2, 3));
    EXPECT_EQ(3, clampHigherBound(3, 3));
    EXPECT_EQ(3, clampHigherBound(4, 3));
    EXPECT_EQ(3, clampHigherBound(5, 3));
}

TEST(AlbaMathHelperTest, IsDivisibleWorks)
{
    EXPECT_FALSE(isDivisible(0u, 0u));
    EXPECT_TRUE(isDivisible(0u, 1u));    EXPECT_TRUE(isDivisible(1u, 1u));
    EXPECT_FALSE(isDivisible(1u, 5u));
    EXPECT_TRUE(isDivisible(5u, 1u));
    EXPECT_TRUE(isDivisible(256u, 16u));
    EXPECT_FALSE(isDivisible(256u, 17u));
}

TEST(AlbaMathHelperTest, IsEvenWorks)
{
    EXPECT_TRUE(isEven(0u));
    EXPECT_FALSE(isEven(1u));    EXPECT_TRUE(isEven(256u));
    EXPECT_FALSE(isEven(255u));
}

TEST(AlbaMathHelperTest, IsOddWorks)
{
    EXPECT_FALSE(isOdd(0u));
    EXPECT_TRUE(isOdd(1u));    EXPECT_FALSE(isOdd(256u));
    EXPECT_TRUE(isOdd(255u));
}

TEST(AlbaMathHelperTest, GetGreatestCommonFactorWorksForUnsignedInteger)
{
    EXPECT_EQ(0u, getGreatestCommonFactor(0, 0));
    EXPECT_EQ(8u, getGreatestCommonFactor(0, 8));
    EXPECT_EQ(8u, getGreatestCommonFactor(8, 0));
    EXPECT_EQ(1u, getGreatestCommonFactor(1, 8));
    EXPECT_EQ(1u, getGreatestCommonFactor(8, 1));
    EXPECT_EQ(1u, getGreatestCommonFactor(1, 1));
    EXPECT_EQ(16u, getGreatestCommonFactor(16, 32));
    EXPECT_EQ(14u, getGreatestCommonFactor(98, 56));
    EXPECT_EQ(1u, getGreatestCommonFactor(1234567891, 3));
}

TEST(AlbaMathHelperTest, GetGreatestCommonFactorWorksForAlbaNumber)
{
    EXPECT_EQ(AlbaNumber(0), getGreatestCommonFactor(AlbaNumber(0), AlbaNumber(0)));
    EXPECT_EQ(AlbaNumber(1), getGreatestCommonFactor(AlbaNumber(1), AlbaNumber(1)));
    EXPECT_EQ(AlbaNumber(1, 12), getGreatestCommonFactor(AlbaNumber(1, 6), AlbaNumber(1, 4)));
    EXPECT_EQ(AlbaNumber(1), getGreatestCommonFactor(AlbaNumber(0.33), AlbaNumber(1, 4)));
    EXPECT_EQ(AlbaNumber(1, 4), getGreatestCommonFactor(AlbaNumber(5), AlbaNumber(1, 4)));
    EXPECT_EQ(AlbaNumber(3), getGreatestCommonFactor(AlbaNumber(6), AlbaNumber(9)));
}

TEST(AlbaMathHelperTest, GetLeastCommonMultipleWorksForUnsignedInteger)
{
    EXPECT_EQ(0u, getLeastCommonMultiple(0, 0));
    EXPECT_EQ(1u, getLeastCommonMultiple(1, 1));
    EXPECT_EQ(256u, getLeastCommonMultiple(8, 256));
    EXPECT_EQ(60u, getLeastCommonMultiple(15, 20));
    EXPECT_EQ(262144u, getLeastCommonMultiple(65536, 262144));
}

TEST(AlbaMathHelperTest, GetLeastCommonMultipleWorksForAlbaNumber)
{
    EXPECT_EQ(AlbaNumber(3), getLeastCommonMultiple(AlbaNumber(3, 2), AlbaNumber(1, 3)));
}

TEST(AlbaMathHelperTest, GetLeastCommonMultipleInDoubleWorks)
{
    EXPECT_DOUBLE_EQ(262144, getLeastCommonMultipleInDouble(65536, 262144));
}

TEST(AlbaMathHelperTest, GetDifferenceFromGreaterMultipleWorks)
{
    EXPECT_EQ(0u, getDifferenceFromGreaterMultiple(0, 0));
    EXPECT_EQ(0u, getDifferenceFromGreaterMultiple(10, 10));
    EXPECT_EQ(0u, getDifferenceFromGreaterMultiple(5, 10));
    EXPECT_EQ(5u, getDifferenceFromGreaterMultiple(10, 5));
    EXPECT_EQ(48u, getDifferenceFromGreaterMultiple(57, 2346));
}

TEST(AlbaMathHelperTest, GetFractionDetailsInLowestFormWorks)
{
    FractionDetails fractionDetails1(getFractionDetailsInLowestForm(0, 0));
    EXPECT_EQ(1, fractionDetails1.sign);
    EXPECT_EQ(0u, fractionDetails1.numerator);    EXPECT_EQ(0u, fractionDetails1.denominator);

    FractionDetails fractionDetails2(getFractionDetailsInLowestForm(1, 1));
    EXPECT_EQ(1, fractionDetails2.sign);    EXPECT_EQ(1u, fractionDetails2.numerator);
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

    FractionDetails fractionDetails6(getFractionDetailsInLowestForm(1234567891, -1234567892));
    EXPECT_EQ(-1, fractionDetails6.sign);
    EXPECT_EQ(1234567891u, fractionDetails6.numerator);
    EXPECT_EQ(1234567892u, fractionDetails6.denominator);
}

TEST(AlbaMathHelperTest, GetBestFractionDetailsForDoubleValueWorks)
{
    FractionDetails fractionDetails1(getBestFractionDetailsForDoubleValue(0));
    EXPECT_EQ(1, fractionDetails1.sign);    EXPECT_EQ(0u, fractionDetails1.numerator);
    EXPECT_EQ(1u, fractionDetails1.denominator);

    FractionDetails fractionDetails2(getBestFractionDetailsForDoubleValue(1));    EXPECT_EQ(1, fractionDetails2.sign);
    EXPECT_EQ(1u, fractionDetails2.numerator);
    EXPECT_EQ(1u, fractionDetails2.denominator);

    FractionDetails fractionDetails3(getBestFractionDetailsForDoubleValue(-1));
    EXPECT_EQ(-1, fractionDetails3.sign);
    EXPECT_EQ(1u, fractionDetails3.numerator);
    EXPECT_EQ(1u, fractionDetails3.denominator);

    FractionDetails fractionDetails4(getBestFractionDetailsForDoubleValue(-234));
    EXPECT_EQ(-1, fractionDetails4.sign);
    EXPECT_EQ(234u, fractionDetails4.numerator);
    EXPECT_EQ(1u, fractionDetails4.denominator);

    FractionDetails fractionDetails5(getBestFractionDetailsForDoubleValue(0.3333333333333333333));
    EXPECT_EQ(1, fractionDetails5.sign);
    EXPECT_EQ(1u, fractionDetails5.numerator);
    EXPECT_EQ(3u, fractionDetails5.denominator);

    FractionDetails fractionDetails6(getBestFractionDetailsForDoubleValue(-78.787878787878787878));
    EXPECT_EQ(-1, fractionDetails6.sign);
    EXPECT_EQ(2600u, fractionDetails6.numerator);
    EXPECT_EQ(33u, fractionDetails6.denominator);

    FractionDetails fractionDetails7(getBestFractionDetailsForDoubleValue(2.236067977499789696409));
    EXPECT_EQ(1, fractionDetails7.sign);
    EXPECT_EQ(2446376235u, fractionDetails7.numerator);
    EXPECT_EQ(1094052712u, fractionDetails7.denominator);
}

TEST(AlbaMathHelperTest, IsPerfectCubeForUnsignedIntWorks)
{
    EXPECT_TRUE(isPerfectCube(0u));
    EXPECT_TRUE(isPerfectCube(1u));
    EXPECT_FALSE(isPerfectSquare(8u));
    EXPECT_TRUE(isPerfectSquare(9u));
    EXPECT_TRUE(isPerfectCube(1000u));
    EXPECT_FALSE(isPerfectCube(1001u));
}

TEST(AlbaMathHelperTest, IsPerfectCubeForAlbaNumberWorks)
{
    EXPECT_TRUE(isPerfectCube(AlbaNumber(0)));
    EXPECT_TRUE(isPerfectCube(AlbaNumber(1)));
    EXPECT_FALSE(isPerfectSquare(AlbaNumber(8)));
    EXPECT_TRUE(isPerfectSquare(AlbaNumber(9)));
    EXPECT_TRUE(isPerfectCube(AlbaNumber(1000)));
    EXPECT_FALSE(isPerfectCube(AlbaNumber(1001)));
    EXPECT_TRUE(isPerfectCube(AlbaNumber(1000, 27)));
    EXPECT_FALSE(isPerfectCube(AlbaNumber(1000, 26)));
}

TEST(AlbaMathHelperTest, IsPerfectSquareForUnsignedIntWorks)
{
    EXPECT_TRUE(isPerfectSquare(0u));
    EXPECT_TRUE(isPerfectSquare(1u));
    EXPECT_FALSE(isPerfectSquare(3u));
    EXPECT_TRUE(isPerfectSquare(4u));
    EXPECT_TRUE(isPerfectSquare(100u));
    EXPECT_FALSE(isPerfectSquare(101u));
}

TEST(AlbaMathHelperTest, IsPerfectSquareForAlbaNumberWorks)
{
    EXPECT_TRUE(isPerfectSquare(AlbaNumber(0)));
    EXPECT_TRUE(isPerfectSquare(AlbaNumber(1)));
    EXPECT_FALSE(isPerfectSquare(AlbaNumber(3)));
    EXPECT_TRUE(isPerfectSquare(AlbaNumber(4)));
    EXPECT_TRUE(isPerfectSquare(AlbaNumber(100)));
    EXPECT_FALSE(isPerfectSquare(AlbaNumber(101)));
    EXPECT_TRUE(isPerfectSquare(AlbaNumber(100, 36)));
    EXPECT_FALSE(isPerfectSquare(AlbaNumber(100, 37)));
}

TEST(AlbaMathHelperTest, IsPerfectNthPowerForUnsignedIntWorks)
{
    EXPECT_TRUE(isPerfectNthPower(0u, 0u));
    EXPECT_TRUE(isPerfectNthPower(1u, 1u));
    EXPECT_FALSE(isPerfectNthPower(100u, 0u));
    EXPECT_TRUE(isPerfectNthPower(100u, 1u));
    EXPECT_TRUE(isPerfectNthPower(100u, 2u));
    EXPECT_FALSE(isPerfectNthPower(101u, 2u));
    EXPECT_TRUE(isPerfectNthPower(1000u, 3u));
    EXPECT_FALSE(isPerfectNthPower(1001u, 3u));
}

TEST(AlbaMathHelperTest, IsPerfectNthPowerForAlbaNumberWorks)
{
    EXPECT_TRUE(isPerfectNthPower(AlbaNumber(0u), 0u));
    EXPECT_TRUE(isPerfectNthPower(AlbaNumber(1), 1u));
    EXPECT_FALSE(isPerfectNthPower(AlbaNumber(100), 0u));
    EXPECT_TRUE(isPerfectNthPower(AlbaNumber(100), 1u));
    EXPECT_TRUE(isPerfectNthPower(AlbaNumber(100), 2u));
    EXPECT_FALSE(isPerfectNthPower(AlbaNumber(101), 2u));
    EXPECT_TRUE(isPerfectNthPower(AlbaNumber(100, 36), 2u));
    EXPECT_FALSE(isPerfectNthPower(AlbaNumber(100, 37), 2u));
    EXPECT_TRUE(isPerfectNthPower(AlbaNumber(1000), 3u));
    EXPECT_FALSE(isPerfectNthPower(AlbaNumber(1001), 3u));
    EXPECT_TRUE(isPerfectNthPower(AlbaNumber(1000, 27), 3u));
    EXPECT_FALSE(isPerfectNthPower(AlbaNumber(1001, 26), 3u));
}

TEST(AlbaMathHelperTest, GetRaiseToPowerForIntegersWorks)
{
    EXPECT_EQ(1, getRaiseToPowerForIntegers(0, 0u));
    EXPECT_EQ(1, getRaiseToPowerForIntegers(1, 0u));
    EXPECT_EQ(0, getRaiseToPowerForIntegers(0, 1u));
    EXPECT_EQ(243, getRaiseToPowerForIntegers(3, 5u));
    EXPECT_EQ(-128, getRaiseToPowerForIntegers(-2, 7u));
}

TEST(AlbaMathHelperTest, GetNumberOfDigitsWorks)
{
    EXPECT_EQ(0u, getNumberOfIntegerDigits<unsigned int>(0));
    EXPECT_EQ(1u, getNumberOfIntegerDigits<unsigned int>(1));
    EXPECT_EQ(2u, getNumberOfIntegerDigits<unsigned int>(54));
    EXPECT_EQ(4u, getNumberOfIntegerDigits<unsigned int>(1000));
    EXPECT_EQ(0u, getNumberOfIntegerDigits<int>(0));
    EXPECT_EQ(1u, getNumberOfIntegerDigits<int>(-1));
    EXPECT_EQ(2u, getNumberOfIntegerDigits<int>(-54));
    EXPECT_EQ(4u, getNumberOfIntegerDigits<int>(-1000));
    EXPECT_EQ(0u, getNumberOfIntegerDigits<double>(0));
    EXPECT_EQ(1u, getNumberOfIntegerDigits<double>(1.1));
    EXPECT_EQ(2u, getNumberOfIntegerDigits<double>(-54.123));
    EXPECT_EQ(4u, getNumberOfIntegerDigits<double>(1000.12345));
}

TEST(AlbaMathHelperTest, AreNumberOfDigitsOnTheIntegerLimitWorks)
{
    EXPECT_FALSE(areNumberOfDigitsOnTheIntegerLimit(0));
    EXPECT_FALSE(areNumberOfDigitsOnTheIntegerLimit(1));
    EXPECT_FALSE(areNumberOfDigitsOnTheIntegerLimit(9));
    EXPECT_TRUE(areNumberOfDigitsOnTheIntegerLimit(10));
    EXPECT_TRUE(areNumberOfDigitsOnTheIntegerLimit(11));
}

}