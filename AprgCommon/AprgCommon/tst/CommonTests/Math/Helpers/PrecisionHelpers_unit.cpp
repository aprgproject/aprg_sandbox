#include <Common/Math/Helpers/PrecisionHelpers.hpp>

#include <climits>

#include <gtest/gtest.h>

using namespace std;
namespace alba
{

namespace mathHelper
{

TEST(PrecisionHelpersTest, IntegerTypesCanBeConsideredEqual)
{
    EXPECT_TRUE(isAlmostEqual(static_cast<int>(100), static_cast<int>(100)));
}

TEST(PrecisionHelpersTest, DoubleTypesCanBeConsideredEqual)
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
    EXPECT_FALSE(isAlmostEqual<double>(2.0, INFINITY));
    EXPECT_TRUE(isAlmostEqual(INFINITY, INFINITY));
    EXPECT_FALSE(isAlmostEqual(INFINITY, -INFINITY));
}
TEST(PrecisionHelpersTest, IsAlmostAnIntegerWorks)
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

TEST(PrecisionHelpersTest, IsValueWithinLimitsWorksForInteger)
{
    EXPECT_FALSE(isValueWithinLimits<int>(static_cast<double>(INT_MIN)-1));
    EXPECT_TRUE(isValueWithinLimits<int>(INT_MIN));
    EXPECT_TRUE(isValueWithinLimits<int>(1000));
    EXPECT_TRUE(isValueWithinLimits<int>(INT_MAX));
    EXPECT_FALSE(isValueWithinLimits<int>(static_cast<double>(INT_MAX)+1));
}

TEST(PrecisionHelpersTest, IsValueWithinUnsignedIntegerLimitsWorks)
{
    EXPECT_FALSE(isValueWithinLimits<unsigned int>(static_cast<double>(0)-1));
    EXPECT_TRUE(isValueWithinLimits<unsigned int>(0));
    EXPECT_TRUE(isValueWithinLimits<unsigned int>(1000));
    EXPECT_TRUE(isValueWithinLimits<unsigned int>(UINT_MAX));
    EXPECT_FALSE(isValueWithinLimits<unsigned int>(static_cast<double>(UINT_MAX)+1));
}

TEST(PrecisionHelpersTest, IsValueWithinShortIntegerLimitsWorks)
{
    EXPECT_FALSE(isValueWithinLimits<short int>(static_cast<double>(SHRT_MIN)-1));
    EXPECT_TRUE(isValueWithinLimits<short int>(SHRT_MIN));
    EXPECT_TRUE(isValueWithinLimits<short int>(1000));
    EXPECT_TRUE(isValueWithinLimits<short int>(SHRT_MAX));
    EXPECT_FALSE(isValueWithinLimits<short int>(static_cast<double>(SHRT_MAX)+1));
}

TEST(PrecisionHelpersTest, IsValueWithinLongIntegerLimitsWorks)
{
    EXPECT_FALSE(isValueWithinLimits<long int>(static_cast<double>(LONG_MIN)-100000));
    EXPECT_TRUE(isValueWithinLimits<long int>(LONG_MIN));
    EXPECT_TRUE(isValueWithinLimits<long int>(1000));
    EXPECT_TRUE(isValueWithinLimits<long int>(LONG_MAX));
    EXPECT_FALSE(isValueWithinLimits<long int>(static_cast<double>(LONG_MAX)+100000));
}

TEST(PrecisionHelpersTest, IsValueWithinUnsignedLongIntegerLimitsWorks)
{
    EXPECT_FALSE(isValueWithinLimits<unsigned long int>(static_cast<double>(0)-100000));
    EXPECT_TRUE(isValueWithinLimits<unsigned long int>(0));
    EXPECT_TRUE(isValueWithinLimits<unsigned long int>(1000));
    EXPECT_TRUE(isValueWithinLimits<unsigned long int>(ULONG_MAX));
    EXPECT_FALSE(isValueWithinLimits<unsigned long int>(static_cast<double>(ULONG_MAX)+100000));
}

TEST(PrecisionHelpersTest, IsValueWithinLongLongIntegerLimitsWorks)
{
    EXPECT_FALSE(isValueWithinLimits<long long int>(static_cast<double>(LLONG_MIN)*2));
    EXPECT_TRUE(isValueWithinLimits<long long int>(LLONG_MIN));
    EXPECT_TRUE(isValueWithinLimits<long long int>(1000));
    EXPECT_TRUE(isValueWithinLimits<long long int>(LLONG_MAX));
    EXPECT_FALSE(isValueWithinLimits<long long int>(static_cast<double>(LLONG_MAX)*2));
}

TEST(PrecisionHelpersTest, IsValueWithinUnsignedLongLongIntegerLimitsWorks)
{
    EXPECT_FALSE(isValueWithinLimits<unsigned long long int>(static_cast<double>(0)-ULLONG_MAX));
    EXPECT_TRUE(isValueWithinLimits<unsigned long long int>(0));
    EXPECT_TRUE(isValueWithinLimits<unsigned long long int>(1000));
    EXPECT_TRUE(isValueWithinLimits<unsigned long long int>(ULLONG_MAX));
    EXPECT_FALSE(isValueWithinLimits<unsigned long long int>(static_cast<double>(ULLONG_MAX)*2));
}

TEST(PrecisionHelpersTest, IsValueBeyondLimitsWorksForInteger)
{
    EXPECT_TRUE(isValueBeyondLimits<int>(static_cast<double>(INT_MIN)-1));
    EXPECT_FALSE(isValueBeyondLimits<int>(INT_MIN));
    EXPECT_FALSE(isValueBeyondLimits<int>(1000));
    EXPECT_FALSE(isValueBeyondLimits<int>(INT_MAX));
    EXPECT_TRUE(isValueBeyondLimits<int>(static_cast<double>(INT_MAX)+1));
}

TEST(PrecisionHelpersTest, IsValueBeyondUnsignedIntegerLimitsWorks)
{
    EXPECT_TRUE(isValueBeyondLimits<unsigned int>(static_cast<double>(0)-1));
    EXPECT_FALSE(isValueBeyondLimits<unsigned int>(0));
    EXPECT_FALSE(isValueBeyondLimits<unsigned int>(1000));
    EXPECT_FALSE(isValueBeyondLimits<unsigned int>(UINT_MAX));
    EXPECT_TRUE(isValueBeyondLimits<unsigned int>(static_cast<double>(UINT_MAX)+1));
}

TEST(PrecisionHelpersTest, IsValueBeyondShortIntegerLimitsWorks)
{
    EXPECT_TRUE(isValueBeyondLimits<short int>(static_cast<double>(SHRT_MIN)-1));
    EXPECT_FALSE(isValueBeyondLimits<short int>(SHRT_MIN));
    EXPECT_FALSE(isValueBeyondLimits<short int>(1000));
    EXPECT_FALSE(isValueBeyondLimits<short int>(SHRT_MAX));
    EXPECT_TRUE(isValueBeyondLimits<short int>(static_cast<double>(SHRT_MAX)+1));
}

TEST(PrecisionHelpersTest, IsValueBeyondLongIntegerLimitsWorks)
{
    EXPECT_TRUE(isValueBeyondLimits<long int>(static_cast<double>(LONG_MIN)-100000));
    EXPECT_FALSE(isValueBeyondLimits<long int>(LONG_MIN));
    EXPECT_FALSE(isValueBeyondLimits<long int>(1000));
    EXPECT_FALSE(isValueBeyondLimits<long int>(LONG_MAX));
    EXPECT_TRUE(isValueBeyondLimits<long int>(static_cast<double>(LONG_MAX)+100000));
}

TEST(PrecisionHelpersTest, IsValueBeyondUnsignedLongIntegerLimitsWorks)
{
    EXPECT_TRUE(isValueBeyondLimits<unsigned long int>(static_cast<double>(0)-100000));
    EXPECT_FALSE(isValueBeyondLimits<unsigned long int>(0));
    EXPECT_FALSE(isValueBeyondLimits<unsigned long int>(1000));
    EXPECT_FALSE(isValueBeyondLimits<unsigned long int>(ULONG_MAX));
    EXPECT_TRUE(isValueBeyondLimits<unsigned long int>(static_cast<double>(ULONG_MAX)+100000));
}

TEST(PrecisionHelpersTest, IsValueBeyondLongLongIntegerLimitsWorks)
{
    EXPECT_TRUE(isValueBeyondLimits<long long int>(static_cast<double>(LLONG_MIN)*2));
    EXPECT_FALSE(isValueBeyondLimits<long long int>(LLONG_MIN));
    EXPECT_FALSE(isValueBeyondLimits<long long int>(1000));
    EXPECT_FALSE(isValueBeyondLimits<long long int>(LLONG_MAX));
    EXPECT_TRUE(isValueBeyondLimits<long long int>(static_cast<double>(LLONG_MAX)*2));
}

TEST(PrecisionHelpersTest, IsValueBeyondUnsignedLongLongIntegerLimitsWorks)
{
    EXPECT_TRUE(isValueBeyondLimits<unsigned long long int>(static_cast<double>(0)-ULLONG_MAX));
    EXPECT_FALSE(isValueBeyondLimits<unsigned long long int>(0));
    EXPECT_FALSE(isValueBeyondLimits<unsigned long long int>(1000));
    EXPECT_FALSE(isValueBeyondLimits<unsigned long long int>(ULLONG_MAX));
    EXPECT_TRUE(isValueBeyondLimits<unsigned long long int>(static_cast<double>(ULLONG_MAX)*2));
}

TEST(PrecisionHelpersTest, GetIntegerAfterRoundingADoubleValueWorks)
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

TEST(PrecisionHelpersTest, GetIntegerAfterFloorOfDoubleValueWorks)
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

TEST(PrecisionHelpersTest, GetIntegerAfterCeilingOfDoubleValueWorks)
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

TEST(PrecisionHelpersTest, GetIntegerPartOfDoubleValueWorks)
{
    EXPECT_EQ(0, getIntegerPartOfDoubleValue<int>(0));
    EXPECT_EQ(1, getIntegerPartOfDoubleValue<int>(1));
    EXPECT_EQ(1, getIntegerPartOfDoubleValue<int>(1.5));
    EXPECT_EQ(-1, getIntegerPartOfDoubleValue<int>(-1.5));
    EXPECT_EQ(652, getIntegerPartOfDoubleValue<int>(652.426542));
    EXPECT_EQ(-347, getIntegerPartOfDoubleValue<int>(-347.51514));
}

TEST(PrecisionHelpersTest, IsAlmostEqualWorksWithDifferenceTolerance)
{
    EXPECT_TRUE(isAlmostEqual(2.54, 2.55, 1E-1));
    EXPECT_TRUE(isAlmostEqual(2.54, 2.55, 1E-2));
    EXPECT_FALSE(isAlmostEqual(2.54, 2.55, 1E-3));
    EXPECT_FALSE(isAlmostEqual(2, INFINITY, 1E-3));
    EXPECT_TRUE(isAlmostEqual(INFINITY, INFINITY, 1E-3));
    EXPECT_FALSE(isAlmostEqual(INFINITY, -INFINITY, 1E-3));
}

TEST(PrecisionHelpersTest, IsAlmostAnIntegerWithDifferenceToleranceWorks)
{
    EXPECT_TRUE(isAlmostAnInteger(3.01, 1E-1));
    EXPECT_TRUE(isAlmostAnInteger(3.01, 1E-2));
    EXPECT_FALSE(isAlmostAnInteger(3.01, 1E-3));
    EXPECT_TRUE(isAlmostAnInteger(1524157877611644672, 1E-3));
}

TEST(PrecisionHelpersTest, FractionalPartInDoubleWorks)
{
    EXPECT_DOUBLE_EQ(0, getFractionalPartInDouble(0));
    EXPECT_DOUBLE_EQ(0, getFractionalPartInDouble(1));
    EXPECT_DOUBLE_EQ(0.5, getFractionalPartInDouble(1.5));
    EXPECT_DOUBLE_EQ(-0.5, getFractionalPartInDouble(-1.5));
    EXPECT_DOUBLE_EQ(0.15625, getFractionalPartInDouble(652.15625));
    EXPECT_DOUBLE_EQ(-0.125, getFractionalPartInDouble(-347.125));
}

TEST(PrecisionHelpersTest, ConvertIfInfinityToNearestFiniteValueWorks)
{
    EXPECT_DOUBLE_EQ(45.625, convertIfInfinityToNearestFiniteValue(AlbaNumber(45.625)).getDouble());
    EXPECT_DOUBLE_EQ(1.7976931348623157e+308, convertIfInfinityToNearestFiniteValue(AlbaNumber(AlbaNumber::Value::PositiveInfinity)).getDouble());
    EXPECT_DOUBLE_EQ(-1.7976931348623157e+308, convertIfInfinityToNearestFiniteValue(AlbaNumber(AlbaNumber::Value::NegativeInfinity)).getDouble());
}

}

}
