#include <Common/Math/AlbaMathConstants.hpp>
#include <Common/Math/AlbaMathHelper.hpp>

#include <gtest/gtest.h>

#include <climits>
#include <cmath>

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
    EXPECT_TRUE(isAlmostEqual(static_cast<double>(1)/3, static_cast<double>(1)/3));
    EXPECT_FALSE(isAlmostEqual(static_cast<double>(1)/3, static_cast<double>(1)/3+0.1));
    EXPECT_TRUE(isAlmostEqual(static_cast<double>(1)/3, static_cast<double>(1)/3+1E-13));
    EXPECT_TRUE(isAlmostEqual(1E-12, 1E-12));
    EXPECT_FALSE(isAlmostEqual(static_cast<double>(0), 1E-11));
    EXPECT_FALSE(isAlmostEqual(static_cast<double>(0), 1E-12));
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
    EXPECT_TRUE(isAlmostEqual(2.54, 2.55, 1E-1));
    EXPECT_TRUE(isAlmostEqual(2.54, 2.55, 1E-2));
    EXPECT_FALSE(isAlmostEqual(2.54, 2.55, 1E-3));
    EXPECT_FALSE(isAlmostEqual(2, INFINITY, 1E-3));
    EXPECT_TRUE(isAlmostEqual(INFINITY, INFINITY, 1E-3));
    EXPECT_FALSE(isAlmostEqual(INFINITY, -INFINITY, 1E-3));
}

TEST(AlbaMathHelperTest, IsAlmostAnIntegerWorks)
{
    EXPECT_TRUE((isAlmostAnInteger<float, int>(0)));
    EXPECT_TRUE((isAlmostAnInteger<float, int>(1)));
    EXPECT_TRUE((isAlmostAnInteger<float, int>(2)));
    EXPECT_FALSE((isAlmostAnInteger<float, int>(3.00001)));
    EXPECT_TRUE((isAlmostAnInteger<float, int>(3.0000000000001)));
    EXPECT_TRUE((isAlmostAnInteger<double, int>(0)));
    EXPECT_TRUE((isAlmostAnInteger<double, int>(1)));
    EXPECT_TRUE((isAlmostAnInteger<double, int>(2)));
    EXPECT_FALSE((isAlmostAnInteger<double, int>(3.00000001)));
    EXPECT_TRUE((isAlmostAnInteger<double, int>(3.0000000000001)));
}

TEST(AlbaMathHelperTest, IsAlmostAnIntegerWithDifferenceToleranceWorks)
{
    EXPECT_TRUE(isAlmostAnInteger(3.01, 1E-1));
    EXPECT_TRUE(isAlmostAnInteger(3.01, 1E-2));
    EXPECT_FALSE(isAlmostAnInteger(3.01, 1E-3));
    EXPECT_TRUE(isAlmostAnInteger(1524157877611644672, 1E-3));
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
    EXPECT_TRUE(isValueBeyondLimits<long int>(static_cast<double>(LONG_MIN)-100000));
    EXPECT_FALSE(isValueBeyondLimits<long int>(LONG_MIN));
    EXPECT_FALSE(isValueBeyondLimits<long int>(1000));
    EXPECT_FALSE(isValueBeyondLimits<long int>(LONG_MAX));
    EXPECT_TRUE(isValueBeyondLimits<long int>(static_cast<double>(LONG_MAX)+100000));
}

TEST(AlbaMathHelperTest, IsValueBeyondUnsignedLongIntegerLimitsWorks)
{
    EXPECT_TRUE(isValueBeyondLimits<unsigned long int>(static_cast<double>(0)-100000));
    EXPECT_FALSE(isValueBeyondLimits<unsigned long int>(0));
    EXPECT_FALSE(isValueBeyondLimits<unsigned long int>(1000));
    EXPECT_FALSE(isValueBeyondLimits<unsigned long int>(ULONG_MAX));
    EXPECT_TRUE(isValueBeyondLimits<unsigned long int>(static_cast<double>(ULONG_MAX)+100000));
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

TEST(AlbaMathHelperTest, GetIntegerAfterRoundingADoubleValueWorks)
{
    EXPECT_EQ(0, getIntegerAfterRoundingADoubleValue<int>(0));
    EXPECT_EQ(1, getIntegerAfterRoundingADoubleValue<int>(1));
    EXPECT_EQ(2, getIntegerAfterRoundingADoubleValue<int>(1.5));
    EXPECT_EQ(-2, getIntegerAfterRoundingADoubleValue<int>(-1.5));
    EXPECT_EQ(652, getIntegerAfterRoundingADoubleValue<int>(652.426542));
    EXPECT_EQ(-348, getIntegerAfterRoundingADoubleValue<int>(-347.51514));
    EXPECT_EQ(0U, getIntegerAfterRoundingADoubleValue<unsigned int>(0));
    EXPECT_EQ(1U, getIntegerAfterRoundingADoubleValue<unsigned int>(1));
    EXPECT_EQ(2U, getIntegerAfterRoundingADoubleValue<unsigned int>(1.5));
    EXPECT_EQ(4294967294U, getIntegerAfterRoundingADoubleValue<unsigned int>(-1.5));
    EXPECT_EQ(652U, getIntegerAfterRoundingADoubleValue<unsigned int>(652.426542));
    EXPECT_EQ(4294966948U, getIntegerAfterRoundingADoubleValue<unsigned int>(-347.51514));
}

TEST(AlbaMathHelperTest, GetIntegerAfterFloorOfDoubleValueWorks)
{
    EXPECT_EQ(0, getIntegerAfterFloorOfDoubleValue<int>(0));
    EXPECT_EQ(1, getIntegerAfterFloorOfDoubleValue<int>(1));
    EXPECT_EQ(1, getIntegerAfterFloorOfDoubleValue<int>(1.5));
    EXPECT_EQ(-2, getIntegerAfterFloorOfDoubleValue<int>(-1.5));
    EXPECT_EQ(652, getIntegerAfterFloorOfDoubleValue<int>(652.426542));
    EXPECT_EQ(-348, getIntegerAfterFloorOfDoubleValue<int>(-347.51514));
    EXPECT_EQ(0U, getIntegerAfterFloorOfDoubleValue<unsigned int>(0));
    EXPECT_EQ(1U, getIntegerAfterFloorOfDoubleValue<unsigned int>(1));
    EXPECT_EQ(1U, getIntegerAfterFloorOfDoubleValue<unsigned int>(1.5));
    EXPECT_EQ(4294967294U, getIntegerAfterFloorOfDoubleValue<unsigned int>(-1.5));
    EXPECT_EQ(652U, getIntegerAfterFloorOfDoubleValue<unsigned int>(652.426542));
    EXPECT_EQ(4294966948U, getIntegerAfterFloorOfDoubleValue<unsigned int>(-347.51514));
}

TEST(AlbaMathHelperTest, GetIntegerAfterCeilingOfDoubleValueWorks)
{
    EXPECT_EQ(0, getIntegerAfterCeilingOfDoubleValue<int>(0));
    EXPECT_EQ(1, getIntegerAfterCeilingOfDoubleValue<int>(1));
    EXPECT_EQ(2, getIntegerAfterCeilingOfDoubleValue<int>(1.5));
    EXPECT_EQ(-1, getIntegerAfterCeilingOfDoubleValue<int>(-1.5));
    EXPECT_EQ(653, getIntegerAfterCeilingOfDoubleValue<int>(652.426542));
    EXPECT_EQ(-347, getIntegerAfterCeilingOfDoubleValue<int>(-347.51514));
    EXPECT_EQ(0U, getIntegerAfterCeilingOfDoubleValue<unsigned int>(0));
    EXPECT_EQ(1U, getIntegerAfterCeilingOfDoubleValue<unsigned int>(1));
    EXPECT_EQ(2U, getIntegerAfterCeilingOfDoubleValue<unsigned int>(1.5));
    EXPECT_EQ(4294967295U, getIntegerAfterCeilingOfDoubleValue<unsigned int>(-1.5));
    EXPECT_EQ(653U, getIntegerAfterCeilingOfDoubleValue<unsigned int>(652.426542));
    EXPECT_EQ(4294966949U, getIntegerAfterCeilingOfDoubleValue<unsigned int>(-347.51514));
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

TEST(AlbaMathHelperTest, FractionalPartInDoubleWorks)
{
    EXPECT_DOUBLE_EQ(0, getFractionalPartInDouble(0));
    EXPECT_DOUBLE_EQ(0, getFractionalPartInDouble(1));
    EXPECT_DOUBLE_EQ(0.5, getFractionalPartInDouble(1.5));
    EXPECT_DOUBLE_EQ(-0.5, getFractionalPartInDouble(-1.5));
    EXPECT_DOUBLE_EQ(0.15625, getFractionalPartInDouble(652.15625));
    EXPECT_DOUBLE_EQ(-0.125, getFractionalPartInDouble(-347.125));
}

TEST(AlbaMathHelperTest, ConvertIfInfinityToNearestFiniteValueWorks)
{
    EXPECT_DOUBLE_EQ(45.625, convertIfInfinityToNearestFiniteValue(AlbaNumber(45.625)).getDouble());
    EXPECT_DOUBLE_EQ(1.7976931348623157e+308, convertIfInfinityToNearestFiniteValue(AlbaNumber(AlbaNumber::Value::PositiveInfinity)).getDouble());
    EXPECT_DOUBLE_EQ(-1.7976931348623157e+308, convertIfInfinityToNearestFiniteValue(AlbaNumber(AlbaNumber::Value::NegativeInfinity)).getDouble());
}

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

TEST(AlbaMathHelperTest, GetAverageOfTwoNumbersWorksForPrimitiveTypes)
{
    EXPECT_EQ(0, getAverage(-10, 10));
    EXPECT_EQ(55, getAverage(10, 100));
}

TEST(AlbaMathHelperTest, GetAverageOfTwoNumbersForAlbaNumberWorks)
{
    EXPECT_EQ(AlbaNumber(0),
              getAverage(AlbaNumber::createFraction(1, 3), AlbaNumber::createFraction(-1, 3)));
    EXPECT_EQ(AlbaNumber::createFraction(1, 3),
              getAverage(AlbaNumber::createFraction(1, 3), AlbaNumber::createFraction(1, 3)));
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

TEST(AlbaMathHelperTest,  GetLogarithmWorks)
{
    EXPECT_DOUBLE_EQ(2, getLogarithm(3, 9));
    EXPECT_DOUBLE_EQ(5, getLogarithm(2, 32));
    EXPECT_DOUBLE_EQ(-4, getLogarithm(2, 0.0625));
    EXPECT_DOUBLE_EQ(1.9534452978042594, getLogarithm(4, 15));
}

TEST(AlbaMathHelperTest,  GetIterativeLogarithmWorks)
{
    EXPECT_EQ(2U, getIterativeLogarithm(3, 9));
    EXPECT_EQ(4U, getIterativeLogarithm(2, 32));
    EXPECT_EQ(0U, getIterativeLogarithm(2, 0.0625));
    EXPECT_EQ(0U, getIterativeLogarithm(2, -1));
    EXPECT_EQ(2U, getIterativeLogarithm(4, 15));
}

TEST(AlbaMathHelperTest,  GetSuperLogarithmWorks)
{
    EXPECT_EQ(2, getSuperLogarithm(3, 9));
    EXPECT_EQ(4, getSuperLogarithm(2, 32));
    EXPECT_EQ(0, getSuperLogarithm(2, 0.0625));
    EXPECT_EQ(-1, getSuperLogarithm(2, -1));
    EXPECT_EQ(2, getSuperLogarithm(4, 15));
}

TEST(AlbaMathHelperTest, GetQuadraticWorksWithRealRootsOnlyWithInputHavingRealRoots)
{
    AlbaNumbers quadraticRoots(getQuadraticRoots(RootType::RealRootsOnly, 8, 22, 15));

    ASSERT_EQ(2U, quadraticRoots.size());
    EXPECT_EQ(AlbaNumber(-1.25), quadraticRoots.at(0));
    EXPECT_EQ(AlbaNumber(-1.5), quadraticRoots.at(1));
}

TEST(AlbaMathHelperTest, GetQuadraticWorksWithRealRootsOnlyWithInputHavingImaginaryRoots)
{
    AlbaNumbers quadraticRoots(getQuadraticRoots(RootType::RealRootsOnly, 1, 0, 4));

    EXPECT_TRUE(quadraticRoots.empty());
}

TEST(AlbaMathHelperTest, GetQuadraticWorksWithRealAndImaginaryRootsWithInputHavingRealRoots)
{
    AlbaNumbers quadraticRoots(getQuadraticRoots(RootType::RealAndImaginaryRoots, 8, 22, 15));

    ASSERT_EQ(2U, quadraticRoots.size());
    EXPECT_EQ(AlbaNumber(-1.25), quadraticRoots.at(0));
    EXPECT_EQ(AlbaNumber(-1.5), quadraticRoots.at(1));
}

TEST(AlbaMathHelperTest, GetQuadraticWorksWithRealAndImaginaryRootsWithInputHavingImaginaryRoots)
{
    AlbaNumbers quadraticRoots(getQuadraticRoots(RootType::RealAndImaginaryRoots, 1, 0, 4));

    ASSERT_EQ(2U, quadraticRoots.size());
    EXPECT_EQ(AlbaNumber::createComplexNumber(0, 2), quadraticRoots.at(0));
    EXPECT_EQ(AlbaNumber::createComplexNumber(0, -2), quadraticRoots.at(1));
}

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

    //Find the number of permutations of a two digit number with values 1, 2, 3, and 4.
    EXPECT_EQ(12U, getNumberOfPermutations(4U, 2U));

    //If four people enter a bus in which there are ten vacant seats, how many ways are there for the four to be seated?
    EXPECT_EQ(5040U, getNumberOfPermutations(10U, 4U));

    //In how many ways may five books to be arranged on a shelf?
    EXPECT_EQ(120U, getNumberOfPermutations(5U, 5U));

    //Find the number of permutations of the eight letters of the word "gargling".
    EXPECT_EQ(6720U, getFactorial(8U)/getFactorial(3U));

    //Find the number of permutations of the 11 letters of the word "mississippi".
    EXPECT_EQ(34650U, getFactorial(11U)/(getFactorial(4U)*getFactorial(4U)*getFactorial(2U)));

    //How many ways can four boys and three girls be seated in a row containing seven seats if the boys and girls must alternate?
    EXPECT_EQ(144U, getFactorial(4U)*getFactorial(3U));

    //In how many ways can 8 people be seated around a table?
    EXPECT_EQ(5040U, getFactorial(8U)/8U);
}

TEST(AlbaMathHelperTest, GetNumberOfCombinationsWorks)
{
    EXPECT_EQ(1U, getNumberOfCombinations(4U, 4U));
    EXPECT_EQ(1U, getNumberOfCombinations(4U, 0U));
    EXPECT_EQ(4U, getNumberOfCombinations(4U, 1U));
    EXPECT_EQ(0U, getNumberOfCombinations(4U, 5U));

    //How many different sums of money can be made by taking one coin from a penny, a nickel, a dime, and a quarter?
    EXPECT_EQ(4U, getNumberOfCombinations(4U, 1U));

    //How many different sums of money can be made by taking two coins from a penny, a nickel, a dime, and a quarter?
    EXPECT_EQ(6U, getNumberOfCombinations(4U, 2U));

    //How many different sums of money can be made from a penny, a nickel, a dime, and a quarter?
    EXPECT_EQ(15U, getNumberOfCombinations(4U, 1U) + getNumberOfCombinations(4U, 2U) + getNumberOfCombinations(4U, 3U) + getNumberOfCombinations(4U, 4U));

    //In a class of 15 boys and 10 girls, in how many ways may a committee made up of 3 boys and 2 girls be selected?
    EXPECT_EQ(20475U, getNumberOfCombinations(15U, 3U) * getNumberOfCombinations(10U, 2U));

    //On a certain examination, the student must answer 8 out of the 12 question, including 5 of the first 6.
    //How many ways may he write the examination?
    EXPECT_EQ(120U, getNumberOfCombinations(6U, 5U) * getNumberOfCombinations(6U, 3U));
}

TEST(AlbaMathHelperTest, GetValueAtPascalTriangleWorks)
{
    EXPECT_EQ(1U, getValueAtPascalTriangle(0U, 0U));    EXPECT_EQ(1U, getValueAtPascalTriangle(4U, 4U));
    EXPECT_EQ(1U, getValueAtPascalTriangle(4U, 0U));
    EXPECT_EQ(4U, getValueAtPascalTriangle(4U, 1U));
    EXPECT_EQ(6U, getValueAtPascalTriangle(4U, 2U));    EXPECT_EQ(0U, getValueAtPascalTriangle(4U, 5U));
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

TEST(AlbaMathHelperTest, GetCumulativeStandardDistributionApproximationWorks)
{
    //comparing with Z table, http://sphweb.bumc.bu.edu/otlt/mph-modules/bs/bs704_probability/standardnormaltable.pdf
    EXPECT_DOUBLE_EQ(0.5, getCumulativeStandardDistributionApproximation(0));
    EXPECT_DOUBLE_EQ(0.86433393905361732834, getCumulativeStandardDistributionApproximation(1.1));
    EXPECT_DOUBLE_EQ(0.0081975359245961311461, getCumulativeStandardDistributionApproximation(-2.4));
    EXPECT_DOUBLE_EQ(0.99996696335237056363, getCumulativeStandardDistributionApproximation(3.99));
    EXPECT_DOUBLE_EQ(3.3036647629402369943e-005, getCumulativeStandardDistributionApproximation(-3.99));
}

TEST(AlbaMathHelperTest, GetInverseCumulativeStandardDistributionApproximationWorks)
{
    EXPECT_DOUBLE_EQ(0, getInverseCumulativeStandardDistributionApproximation(0.5, 20));
    EXPECT_DOUBLE_EQ(1.0999774932861328125, getInverseCumulativeStandardDistributionApproximation(0.86433, 20));
    EXPECT_DOUBLE_EQ(-2.4003314971923828125, getInverseCumulativeStandardDistributionApproximation(0.00819, 20));
    EXPECT_DOUBLE_EQ(3.9444065093994140625, getInverseCumulativeStandardDistributionApproximation(0.99996, 20));
    EXPECT_DOUBLE_EQ(0, getInverseCumulativeStandardDistributionApproximation(3.3036, 20));
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
    EXPECT_FALSE(isDivisible(0U, 0U));
    EXPECT_TRUE(isDivisible(0U, 1U));
    EXPECT_TRUE(isDivisible(1U, 1U));
    EXPECT_FALSE(isDivisible(1U, 5U));
    EXPECT_TRUE(isDivisible(5U, 1U));
    EXPECT_TRUE(isDivisible(256U, 16U));
    EXPECT_FALSE(isDivisible(256U, 17U));
}

TEST(AlbaMathHelperTest, IsEvenWorks)
{
    EXPECT_TRUE(isEven(0U));
    EXPECT_FALSE(isEven(1U));
    EXPECT_TRUE(isEven(256U));
    EXPECT_FALSE(isEven(255U));
}

TEST(AlbaMathHelperTest, IsOddWorks)
{
    EXPECT_FALSE(isOdd(0U));
    EXPECT_TRUE(isOdd(1U));
    EXPECT_FALSE(isOdd(256U));
    EXPECT_TRUE(isOdd(255U));
}

TEST(AlbaMathHelperTest, IsPrimeWorks)
{
    EXPECT_FALSE(isPrime(0U));
    EXPECT_FALSE(isPrime(1U));
    EXPECT_TRUE(isPrime(2U));
    EXPECT_TRUE(isPrime(3U));
    EXPECT_FALSE(isPrime(4U));
    EXPECT_TRUE(isPrime(5U));
    EXPECT_FALSE(isPrime(24U));
    EXPECT_TRUE(isPrime(67U));
}

TEST(AlbaMathHelperTest, GetGreatestCommonFactorWorksForUnsignedInteger)
{
    EXPECT_EQ(0U, getGreatestCommonFactor(0U, 0U));
    EXPECT_EQ(8U, getGreatestCommonFactor(0U, 8U));
    EXPECT_EQ(8U, getGreatestCommonFactor(8U, 0U));
    EXPECT_EQ(1U, getGreatestCommonFactor(1U, 8U));
    EXPECT_EQ(1U, getGreatestCommonFactor(8U, 1U));
    EXPECT_EQ(1U, getGreatestCommonFactor(1U, 1U));
    EXPECT_EQ(16U, getGreatestCommonFactor(16U, 32U));
    EXPECT_EQ(14U, getGreatestCommonFactor(98U, 56U));
    EXPECT_EQ(1U, getGreatestCommonFactor(1234567891U, 3U));
    EXPECT_EQ(1U, getGreatestCommonFactor(3U, 1234567891U));
}

TEST(AlbaMathHelperTest, GetGreatestCommonFactorWorksForSignedInteger)
{
    EXPECT_EQ(0, getGreatestCommonFactor<int>(0, 0));
    EXPECT_EQ(8, getGreatestCommonFactor(0, -8));
    EXPECT_EQ(8, getGreatestCommonFactor(-8, 0));
    EXPECT_EQ(1, getGreatestCommonFactor(1, -8));
    EXPECT_EQ(1, getGreatestCommonFactor(-8, 1));
    EXPECT_EQ(1, getGreatestCommonFactor<int>(1, 1));
    EXPECT_EQ(16, getGreatestCommonFactor(16, -32));
    EXPECT_EQ(16, getGreatestCommonFactor(-16, 32));
    EXPECT_EQ(14, getGreatestCommonFactor(98, -56));
    EXPECT_EQ(14, getGreatestCommonFactor(-98, 56));
    EXPECT_EQ(1, getGreatestCommonFactor(-1234567891, 3));
    EXPECT_EQ(1, getGreatestCommonFactor(3, -1234567891));
}

TEST(AlbaMathHelperTest, GetGreatestCommonFactorForAlbaNumberWorks)
{
    EXPECT_EQ(AlbaNumber(0), getGreatestCommonFactor(AlbaNumber(0), AlbaNumber(0)));    EXPECT_EQ(AlbaNumber(1), getGreatestCommonFactor(AlbaNumber(1), AlbaNumber(1)));
    EXPECT_EQ(AlbaNumber::createFraction(1, 12),
              getGreatestCommonFactor(AlbaNumber::createFraction(1, 6), AlbaNumber::createFraction(1, 4)));
    EXPECT_EQ(AlbaNumber(1), getGreatestCommonFactor(AlbaNumber(0.33), AlbaNumber::createFraction(1, 4)));    EXPECT_EQ(AlbaNumber::createFraction(1, 4),
              getGreatestCommonFactor(AlbaNumber(5), AlbaNumber::createFraction(1, 4)));
    EXPECT_EQ(AlbaNumber(3), getGreatestCommonFactor(AlbaNumber(6), AlbaNumber(9)));
    EXPECT_EQ(AlbaNumber(9), getGreatestCommonFactor(AlbaNumber(-36), AlbaNumber(27)));
}

TEST(AlbaMathHelperTest, GetLeastCommonMultipleWorksForUnsignedInteger)
{
    EXPECT_EQ(0U, getLeastCommonMultiple(0U, 0U));
    EXPECT_EQ(1U, getLeastCommonMultiple(1U, 1U));
    EXPECT_EQ(256U, getLeastCommonMultiple(8U, 256U));
    EXPECT_EQ(60U, getLeastCommonMultiple(15U, 20U));
    EXPECT_EQ(262144U, getLeastCommonMultiple(65536U, 262144U));
}

TEST(AlbaMathHelperTest, GetLeastCommonMultipleForAlbaNumberWorks)
{
    EXPECT_EQ(AlbaNumber(3),
              getLeastCommonMultiple(AlbaNumber::createFraction(3, 2), AlbaNumber::createFraction(1, 3)));
}

TEST(AlbaMathHelperTest, GetGreatestCommonPowerOf2FactorWorks)
{
    EXPECT_EQ(0U, getGreatestPowerOf2Factor(0U));
    EXPECT_EQ(1U, getGreatestPowerOf2Factor(1U));
    EXPECT_EQ(2U, getGreatestPowerOf2Factor(2U));
    EXPECT_EQ(4U, getGreatestPowerOf2Factor(4U));
    EXPECT_EQ(8U, getGreatestPowerOf2Factor(8U));
    EXPECT_EQ(16U, getGreatestPowerOf2Factor(16U));
    EXPECT_EQ(1U, getGreatestPowerOf2Factor(5U));
    EXPECT_EQ(2U, getGreatestPowerOf2Factor(10U));
    EXPECT_EQ(4U, getGreatestPowerOf2Factor(12U));
}

TEST(AlbaMathHelperTest, GetLeastCommonMultipleInDoubleWorks)
{
    EXPECT_DOUBLE_EQ(262144, getLeastCommonMultipleInDouble(65536, 262144));
}

TEST(AlbaMathHelperTest, GetDifferenceFromGreaterMultipleWorks)
{
    EXPECT_EQ(0U, getDifferenceFromGreaterMultiple(0U, 0U));
    EXPECT_EQ(0U, getDifferenceFromGreaterMultiple(10U, 10U));
    EXPECT_EQ(0U, getDifferenceFromGreaterMultiple(5U, 10U));
    EXPECT_EQ(5U, getDifferenceFromGreaterMultiple(10U, 5U));
    EXPECT_EQ(48U, getDifferenceFromGreaterMultiple(57U, 2346U));
}

TEST(AlbaMathHelperTest, GetFractionDetailsInLowestFormWorks)
{
    FractionDetails fractionDetails1(getFractionDetailsInLowestForm(0, 0));
    EXPECT_EQ(1, fractionDetails1.sign);
    EXPECT_EQ(0U, fractionDetails1.numerator);
    EXPECT_EQ(0U, fractionDetails1.denominator);

    FractionDetails fractionDetails2(getFractionDetailsInLowestForm(1, 1));
    EXPECT_EQ(1, fractionDetails2.sign);
    EXPECT_EQ(1U, fractionDetails2.numerator);
    EXPECT_EQ(1U, fractionDetails2.denominator);

    FractionDetails fractionDetails3(getFractionDetailsInLowestForm(16, -32));
    EXPECT_EQ(-1, fractionDetails3.sign);
    EXPECT_EQ(1U, fractionDetails3.numerator);
    EXPECT_EQ(2U, fractionDetails3.denominator);

    FractionDetails fractionDetails4(getFractionDetailsInLowestForm(-98, 56));
    EXPECT_EQ(-1, fractionDetails4.sign);
    EXPECT_EQ(7U, fractionDetails4.numerator);
    EXPECT_EQ(4U, fractionDetails4.denominator);

    FractionDetails fractionDetails5(getFractionDetailsInLowestForm(-15, -20));
    EXPECT_EQ(1, fractionDetails5.sign);
    EXPECT_EQ(3U, fractionDetails5.numerator);
    EXPECT_EQ(4U, fractionDetails5.denominator);

    FractionDetails fractionDetails6(getFractionDetailsInLowestForm(1234567891, -1234567892));
    EXPECT_EQ(-1, fractionDetails6.sign);
    EXPECT_EQ(1234567891U, fractionDetails6.numerator);
    EXPECT_EQ(1234567892U, fractionDetails6.denominator);
}

TEST(AlbaMathHelperTest, GetBestFractionDetailsForDoubleValueWorks)
{
    FractionDetails fractionDetails1(getBestFractionDetailsForDoubleValue(0));
    EXPECT_EQ(1, fractionDetails1.sign);
    EXPECT_EQ(0U, fractionDetails1.numerator);
    EXPECT_EQ(1U, fractionDetails1.denominator);

    FractionDetails fractionDetails2(getBestFractionDetailsForDoubleValue(1));
    EXPECT_EQ(1, fractionDetails2.sign);
    EXPECT_EQ(1U, fractionDetails2.numerator);
    EXPECT_EQ(1U, fractionDetails2.denominator);

    FractionDetails fractionDetails3(getBestFractionDetailsForDoubleValue(-1));
    EXPECT_EQ(-1, fractionDetails3.sign);
    EXPECT_EQ(1U, fractionDetails3.numerator);
    EXPECT_EQ(1U, fractionDetails3.denominator);

    FractionDetails fractionDetails4(getBestFractionDetailsForDoubleValue(-234));
    EXPECT_EQ(-1, fractionDetails4.sign);
    EXPECT_EQ(234U, fractionDetails4.numerator);
    EXPECT_EQ(1U, fractionDetails4.denominator);

    FractionDetails fractionDetails5(getBestFractionDetailsForDoubleValue(0.3333333333333333333));
    EXPECT_EQ(1, fractionDetails5.sign);
    EXPECT_EQ(1U, fractionDetails5.numerator);
    EXPECT_EQ(3U, fractionDetails5.denominator);

    FractionDetails fractionDetails6(getBestFractionDetailsForDoubleValue(-78.787878787878787878));
    EXPECT_EQ(-1, fractionDetails6.sign);
    EXPECT_EQ(2600U, fractionDetails6.numerator);
    EXPECT_EQ(33U, fractionDetails6.denominator);

    FractionDetails fractionDetails7(getBestFractionDetailsForDoubleValue(2.236067977499789696409));
    EXPECT_EQ(1, fractionDetails7.sign);
    EXPECT_EQ(2446376235U, fractionDetails7.numerator);
    EXPECT_EQ(1094052712U, fractionDetails7.denominator);

    FractionDetails fractionDetails8(getBestFractionDetailsForDoubleValue(POSITIVE_INFINITY_DOUBLE_VALUE));
    EXPECT_EQ(1, fractionDetails8.sign);
    EXPECT_EQ(1U, fractionDetails8.numerator);
    EXPECT_EQ(0U, fractionDetails8.denominator);

    FractionDetails fractionDetails9(getBestFractionDetailsForDoubleValue(NEGATIVE_INFINITY_DOUBLE_VALUE));
    EXPECT_EQ(-1, fractionDetails9.sign);
    EXPECT_EQ(1U, fractionDetails9.numerator);
    EXPECT_EQ(0U, fractionDetails9.denominator);

    FractionDetails fractionDetails10(getBestFractionDetailsForDoubleValue(NAN_DOUBLE_VALUE));
    EXPECT_EQ(1, fractionDetails10.sign);
    EXPECT_EQ(0U, fractionDetails10.numerator);
    EXPECT_EQ(1U, fractionDetails10.denominator);
}

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

TEST(AlbaMathHelperTest, GetNumberOfDigitsOnBaseWorks)
{
    EXPECT_EQ(4U, getNumberOfDigitsOnBase<unsigned int>(10, 1000));
    EXPECT_EQ(10U, getNumberOfDigitsOnBase<unsigned int>(2, 1000));
    EXPECT_EQ(4U, getNumberOfDigitsOnBase<unsigned int>(8, 1000));
    EXPECT_EQ(3U, getNumberOfDigitsOnBase<unsigned int>(16, 1000));
    EXPECT_EQ(2U, getNumberOfDigitsOnBase<unsigned int>(32, 1000));
}

TEST(AlbaMathHelperTest, GetNumberOfIntegerDigitsWorks)
{
    EXPECT_EQ(0U, getNumberOfIntegerDigits<unsigned int>(0));
    EXPECT_EQ(1U, getNumberOfIntegerDigits<unsigned int>(1));
    EXPECT_EQ(2U, getNumberOfIntegerDigits<unsigned int>(54));
    EXPECT_EQ(4U, getNumberOfIntegerDigits<unsigned int>(1000));
    EXPECT_EQ(0U, getNumberOfIntegerDigits<int>(0));
    EXPECT_EQ(1U, getNumberOfIntegerDigits<int>(-1));
    EXPECT_EQ(2U, getNumberOfIntegerDigits<int>(-54));
    EXPECT_EQ(4U, getNumberOfIntegerDigits<int>(-1000));
    EXPECT_EQ(0U, getNumberOfIntegerDigits<double>(0));
    EXPECT_EQ(1U, getNumberOfIntegerDigits<double>(1.1));
    EXPECT_EQ(2U, getNumberOfIntegerDigits<double>(-54.123));
    EXPECT_EQ(4U, getNumberOfIntegerDigits<double>(1000.12345));
}

TEST(AlbaMathHelperTest, AreNumberOfDigitsOnTheIntegerLimitWorks)
{
    EXPECT_FALSE(areNumberOfDigitsOnTheIntegerLimit<int>(0));
    EXPECT_FALSE(areNumberOfDigitsOnTheIntegerLimit<int>(1));
    EXPECT_TRUE(areNumberOfDigitsOnTheIntegerLimit<int>(9));
    EXPECT_TRUE(areNumberOfDigitsOnTheIntegerLimit<int>(10));
    EXPECT_TRUE(areNumberOfDigitsOnTheIntegerLimit<int>(11));
}

TEST(AlbaMathHelperTest, CreateComplexNumberFromDataWorks)
{
    AlbaNumber::ComplexNumberData complexData{3.5, 4.5};

    AlbaComplexNumber<float> expectedComplexNumber(3.5, 4.5);
    EXPECT_EQ(expectedComplexNumber, createComplexNumberFromData(complexData));
}

}
