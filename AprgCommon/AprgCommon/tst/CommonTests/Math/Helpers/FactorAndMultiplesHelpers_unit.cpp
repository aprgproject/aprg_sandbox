#include <Common/Math/Helpers/FactorAndMulitplesHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace mathHelper
{

TEST(FactorAndMulitplesHelpersTest, IsPrimeWorks)
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

TEST(FactorAndMulitplesHelpersTest, GetGreatestCommonPowerOf2FactorWorks)
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

TEST(FactorAndMulitplesHelpersTest, GetGreatestCommonFactorWorksForUnsignedInteger)
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

TEST(FactorAndMulitplesHelpersTest, GetGreatestCommonFactorWorksForSignedInteger)
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

TEST(FactorAndMulitplesHelpersTest, GetLeastCommonMultipleWorksForUnsignedInteger)
{
    EXPECT_EQ(0U, getLeastCommonMultiple(0U, 0U));
    EXPECT_EQ(1U, getLeastCommonMultiple(1U, 1U));
    EXPECT_EQ(256U, getLeastCommonMultiple(8U, 256U));
    EXPECT_EQ(60U, getLeastCommonMultiple(15U, 20U));
    EXPECT_EQ(262144U, getLeastCommonMultiple(65536U, 262144U));
}

TEST(FactorAndMulitplesHelpersTest, GetLeastCommonMultipleInDoubleWorks)
{
    EXPECT_DOUBLE_EQ(262144, getLeastCommonMultipleInDouble(65536, 262144));
}

TEST(FactorAndMulitplesHelpersTest, GetNumberOfMultiplesInclusiveWorks)
{
    EXPECT_EQ(0U, getNumberOfMultiplesInclusive(0U, 0U));
    EXPECT_EQ(1U, getNumberOfMultiplesInclusive(10U, 10U));
    EXPECT_EQ(1U, getNumberOfMultiplesInclusive(5U, 9U));
    EXPECT_EQ(2U, getNumberOfMultiplesInclusive(5U, 10U));
    EXPECT_EQ(2U, getNumberOfMultiplesInclusive(5U, 11U));
    EXPECT_EQ(0U, getNumberOfMultiplesInclusive(10U, 0U));
    EXPECT_EQ(0U, getNumberOfMultiplesInclusive(10U, 5U));
    EXPECT_EQ(41U, getNumberOfMultiplesInclusive(57U, 2346U));
}

TEST(FactorAndMulitplesHelpersTest, GetMultipleThatIsLessOrEqualWorks)
{
    EXPECT_EQ(0U, getMultipleThatIsLesserOrEqual(0U, 0U));
    EXPECT_EQ(10U, getMultipleThatIsLesserOrEqual(10U, 10U));
    EXPECT_EQ(5U, getMultipleThatIsLesserOrEqual(5U, 9U));
    EXPECT_EQ(10U, getMultipleThatIsLesserOrEqual(5U, 10U));
    EXPECT_EQ(10U, getMultipleThatIsLesserOrEqual(5U, 11U));
    EXPECT_EQ(0U, getMultipleThatIsLesserOrEqual(0U, 10U));
    EXPECT_EQ(0U, getMultipleThatIsLesserOrEqual(10U, 0U));
    EXPECT_EQ(0U, getMultipleThatIsLesserOrEqual(10U, 5U));
    EXPECT_EQ(2337U, getMultipleThatIsLesserOrEqual(57U, 2346U));
}

TEST(FactorAndMulitplesHelpersTest, GetMultipleThatIsGreaterOrEqualWorks)
{
    EXPECT_EQ(0U, getMultipleThatIsGreaterOrEqual(0U, 0U));
    EXPECT_EQ(10U, getMultipleThatIsGreaterOrEqual(10U, 10U));
    EXPECT_EQ(10U, getMultipleThatIsGreaterOrEqual(5U, 9U));
    EXPECT_EQ(10U, getMultipleThatIsGreaterOrEqual(5U, 10U));
    EXPECT_EQ(15U, getMultipleThatIsGreaterOrEqual(5U, 11U));
    EXPECT_EQ(0U, getMultipleThatIsGreaterOrEqual(0U, 10U));
    EXPECT_EQ(0U, getMultipleThatIsGreaterOrEqual(10U, 0U));
    EXPECT_EQ(10U, getMultipleThatIsGreaterOrEqual(10U, 5U));
    EXPECT_EQ(2394U, getMultipleThatIsGreaterOrEqual(57U, 2346U));
}

TEST(FactorAndMulitplesHelpersTest, GetDifferenceFromGreaterMultipleWorks)
{
    EXPECT_EQ(0U, getDifferenceFromGreaterMultiple(0U, 0U));
    EXPECT_EQ(0U, getDifferenceFromGreaterMultiple(10U, 10U));
    EXPECT_EQ(1U, getDifferenceFromGreaterMultiple(5U, 9U));
    EXPECT_EQ(0U, getDifferenceFromGreaterMultiple(5U, 10U));
    EXPECT_EQ(4U, getDifferenceFromGreaterMultiple(5U, 11U));
    EXPECT_EQ(0U, getDifferenceFromGreaterMultiple(0U, 10U));
    EXPECT_EQ(0U, getDifferenceFromGreaterMultiple(10U, 0U));
    EXPECT_EQ(5U, getDifferenceFromGreaterMultiple(10U, 5U));
    EXPECT_EQ(48U, getDifferenceFromGreaterMultiple(57U, 2346U));
}

TEST(FactorAndMulitplesHelpersTest, GetGreatestCommonFactorForAlbaNumberWorks)
{
    EXPECT_EQ(AlbaNumber(0), getGreatestCommonFactor(AlbaNumber(0), AlbaNumber(0)));
    EXPECT_EQ(AlbaNumber(1), getGreatestCommonFactor(AlbaNumber(1), AlbaNumber(1)));
    EXPECT_EQ(AlbaNumber::createFraction(1, 12),
              getGreatestCommonFactor(AlbaNumber::createFraction(1, 6), AlbaNumber::createFraction(1, 4)));
    EXPECT_EQ(AlbaNumber(1), getGreatestCommonFactor(AlbaNumber(0.33), AlbaNumber::createFraction(1, 4)));
    EXPECT_EQ(AlbaNumber::createFraction(1, 4),
              getGreatestCommonFactor(AlbaNumber(5), AlbaNumber::createFraction(1, 4)));
    EXPECT_EQ(AlbaNumber(3), getGreatestCommonFactor(AlbaNumber(6), AlbaNumber(9)));
    EXPECT_EQ(AlbaNumber(9), getGreatestCommonFactor(AlbaNumber(-36), AlbaNumber(27)));
}

TEST(FactorAndMulitplesHelpersTest, GetLeastCommonMultipleForAlbaNumberWorks)
{
    EXPECT_EQ(AlbaNumber(3),
              getLeastCommonMultiple(AlbaNumber::createFraction(3, 2), AlbaNumber::createFraction(1, 3)));
}

}

}
