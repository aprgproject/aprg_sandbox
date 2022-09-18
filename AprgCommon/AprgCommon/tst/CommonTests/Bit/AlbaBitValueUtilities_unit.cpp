#include <Common/Bit/AlbaBitValueUtilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(AlbaBitValueUtilitiesTest, IsPowerOfTwoWorks)
{
    EXPECT_TRUE(AlbaBitValueUtilities<uint8_t>::isPowerOfTwo(0U));
    EXPECT_TRUE(AlbaBitValueUtilities<uint8_t>::isPowerOfTwo(1U));
    EXPECT_TRUE(AlbaBitValueUtilities<uint8_t>::isPowerOfTwo(2U));
    EXPECT_FALSE(AlbaBitValueUtilities<uint8_t>::isPowerOfTwo(3U));
    EXPECT_TRUE(AlbaBitValueUtilities<uint8_t>::isPowerOfTwo(4U));
}

TEST(AlbaBitValueUtilitiesTest, IsEvenParityWorks)
{
    EXPECT_TRUE(AlbaBitValueUtilities<uint8_t>::isEvenParity(0U));
    EXPECT_FALSE(AlbaBitValueUtilities<uint8_t>::isEvenParity(1U));
    EXPECT_FALSE(AlbaBitValueUtilities<uint8_t>::isEvenParity(2U));
    EXPECT_TRUE(AlbaBitValueUtilities<uint8_t>::isEvenParity(3U));
    EXPECT_FALSE(AlbaBitValueUtilities<uint8_t>::isEvenParity(4U));
}

TEST(AlbaBitValueUtilitiesTest, GetNumberOfBitsWorks)
{
    EXPECT_EQ(8U, AlbaBitValueUtilities<uint8_t>::getNumberOfBits());
    EXPECT_EQ(16U, AlbaBitValueUtilities<uint16_t>::getNumberOfBits());
    EXPECT_EQ(32U, AlbaBitValueUtilities<uint32_t>::getNumberOfBits());
    EXPECT_EQ(64U, AlbaBitValueUtilities<uint64_t>::getNumberOfBits());
    EXPECT_EQ(8U, AlbaBitValueUtilities<int8_t>::getNumberOfBits());
    EXPECT_EQ(16U, AlbaBitValueUtilities<int16_t>::getNumberOfBits());
    EXPECT_EQ(32U, AlbaBitValueUtilities<int32_t>::getNumberOfBits());
    EXPECT_EQ(64U, AlbaBitValueUtilities<int64_t>::getNumberOfBits());
}

TEST(AlbaBitValueUtilitiesTest, GetNumberOfOnesWorks)
{
    EXPECT_EQ(3U, AlbaBitValueUtilities<uint8_t>::getNumberOfOnes(0xA1U));
    EXPECT_EQ(8U, AlbaBitValueUtilities<uint16_t>::getNumberOfOnes(0xA1BAU));
    EXPECT_EQ(16U, AlbaBitValueUtilities<uint32_t>::getNumberOfOnes(0xA1BAA1BAU));
    EXPECT_EQ(32U, AlbaBitValueUtilities<uint64_t>::getNumberOfOnes(0xA1BAA1BAA1BAA1BAU));
}

TEST(AlbaBitValueUtilitiesTest, GetNumberOfConsecutiveZerosFromMsbWorks)
{
    EXPECT_EQ(0U, AlbaBitValueUtilities<uint8_t>::getNumberOfConsecutiveZerosFromMsb(0x80U));
    EXPECT_EQ(3U, AlbaBitValueUtilities<uint8_t>::getNumberOfConsecutiveZerosFromMsb(0x10U));
    EXPECT_EQ(7U, AlbaBitValueUtilities<uint8_t>::getNumberOfConsecutiveZerosFromMsb(0x01U));
    EXPECT_EQ(0U, AlbaBitValueUtilities<uint16_t>::getNumberOfConsecutiveZerosFromMsb(0x8000U));
    EXPECT_EQ(3U, AlbaBitValueUtilities<uint16_t>::getNumberOfConsecutiveZerosFromMsb(0x1000U));
    EXPECT_EQ(15U, AlbaBitValueUtilities<uint16_t>::getNumberOfConsecutiveZerosFromMsb(0x0001U));
    EXPECT_EQ(0U, AlbaBitValueUtilities<uint32_t>::getNumberOfConsecutiveZerosFromMsb(0x80000000U));
    EXPECT_EQ(3U, AlbaBitValueUtilities<uint32_t>::getNumberOfConsecutiveZerosFromMsb(0x10000000U));
    EXPECT_EQ(31U, AlbaBitValueUtilities<uint32_t>::getNumberOfConsecutiveZerosFromMsb(0x00000001U));
    EXPECT_EQ(0U, AlbaBitValueUtilities<uint64_t>::getNumberOfConsecutiveZerosFromMsb(0x8000000000000000U));
    EXPECT_EQ(3U, AlbaBitValueUtilities<uint64_t>::getNumberOfConsecutiveZerosFromMsb(0x1000000000000000U));
    EXPECT_EQ(63U, AlbaBitValueUtilities<uint64_t>::getNumberOfConsecutiveZerosFromMsb(0x0000000000000001U));
}

TEST(AlbaBitValueUtilitiesTest, GetNumberOfConsecutiveZerosFromLsbWorks)
{
    EXPECT_EQ(7U, AlbaBitValueUtilities<uint8_t>::getNumberOfConsecutiveZerosFromLsb(0x80U));
    EXPECT_EQ(3U, AlbaBitValueUtilities<uint8_t>::getNumberOfConsecutiveZerosFromLsb(0x08U));
    EXPECT_EQ(0U, AlbaBitValueUtilities<uint8_t>::getNumberOfConsecutiveZerosFromLsb(0x01U));
    EXPECT_EQ(15U, AlbaBitValueUtilities<uint16_t>::getNumberOfConsecutiveZerosFromLsb(0x8000U));
    EXPECT_EQ(3U, AlbaBitValueUtilities<uint16_t>::getNumberOfConsecutiveZerosFromLsb(0x0008U));
    EXPECT_EQ(0U, AlbaBitValueUtilities<uint16_t>::getNumberOfConsecutiveZerosFromLsb(0x0001U));
    EXPECT_EQ(31U, AlbaBitValueUtilities<uint32_t>::getNumberOfConsecutiveZerosFromLsb(0x80000000U));
    EXPECT_EQ(3U, AlbaBitValueUtilities<uint32_t>::getNumberOfConsecutiveZerosFromLsb(0x00000008U));
    EXPECT_EQ(0U, AlbaBitValueUtilities<uint32_t>::getNumberOfConsecutiveZerosFromLsb(0x00000001U));
    EXPECT_EQ(63U, AlbaBitValueUtilities<uint64_t>::getNumberOfConsecutiveZerosFromLsb(0x8000000000000000U));
    EXPECT_EQ(3U, AlbaBitValueUtilities<uint64_t>::getNumberOfConsecutiveZerosFromLsb(0x0000000000000008U));
    EXPECT_EQ(0U, AlbaBitValueUtilities<uint64_t>::getNumberOfConsecutiveZerosFromLsb(0x0000000000000001U));
}

TEST(AlbaBitValueUtilitiesTest, GetHammingDistanceWorks)
{
    EXPECT_EQ(0U, AlbaBitValueUtilities<uint8_t>::getHammingDistance(0xA1U, 0xA1U));
    EXPECT_EQ(4U, AlbaBitValueUtilities<uint8_t>::getHammingDistance(0xA1U, 0xBAU));
    EXPECT_EQ(4U, AlbaBitValueUtilities<uint8_t>::getHammingDistance(0xBAU, 0xA1U));
    EXPECT_EQ(1U, AlbaBitValueUtilities<uint8_t>::getHammingDistance(0xA1U, 0xA0U));
    EXPECT_EQ(0U, AlbaBitValueUtilities<uint8_t>::getHammingDistance(0xA1U, 0xA1U));
    EXPECT_EQ(1U, AlbaBitValueUtilities<uint8_t>::getHammingDistance(0xA1U, 0xA3U));
    EXPECT_EQ(2U, AlbaBitValueUtilities<uint8_t>::getHammingDistance(0xA1U, 0xA7U));
    EXPECT_EQ(3U, AlbaBitValueUtilities<uint8_t>::getHammingDistance(0xA1U, 0xAFU));
}

TEST(AlbaBitValueUtilitiesTest, GenerationOfOnesWorks)
{
    const unsigned int input = 2;

    EXPECT_EQ(0x00000003U, AlbaBitValueUtilities<uint32_t>::generateOnesWithNumberOfBits(input));
}

TEST(AlbaBitValueUtilitiesTest, GetAllOnesWorks)
{
    EXPECT_EQ(0xFFU, AlbaBitValueUtilities<uint8_t>::getAllOnes());
    EXPECT_EQ(0xFFFFU, AlbaBitValueUtilities<uint16_t>::getAllOnes());
    EXPECT_EQ(0xFFFFFFFFU, AlbaBitValueUtilities<uint32_t>::getAllOnes());
    EXPECT_EQ(0xFFFFFFFFFFFFFFFFU, AlbaBitValueUtilities<uint64_t>::getAllOnes());
}

TEST(AlbaBitValueUtilitiesTest, Get2ToThePowerOfWorks)
{
    EXPECT_EQ(16U, AlbaBitValueUtilities<uint8_t>::get2ToThePowerOf(4U));
    EXPECT_EQ(1024U, AlbaBitValueUtilities<uint16_t>::get2ToThePowerOf(10U));
    EXPECT_EQ(4194304U, AlbaBitValueUtilities<uint32_t>::get2ToThePowerOf(22U));
}

TEST(AlbaBitValueUtilitiesTest, GetLogarithmWithBase2OfWorks)
{
    EXPECT_EQ(2U, AlbaBitValueUtilities<uint8_t>::getLogarithmWithBase2Of(4U));
    EXPECT_EQ(3U, AlbaBitValueUtilities<uint16_t>::getLogarithmWithBase2Of(10U));
    EXPECT_EQ(4U, AlbaBitValueUtilities<uint32_t>::getLogarithmWithBase2Of(22U));
    EXPECT_EQ(16U, AlbaBitValueUtilities<uint32_t>::getLogarithmWithBase2Of(123456U));
}

TEST(AlbaBitValueUtilitiesTest, GetOnesComplementWorks)
{
    EXPECT_EQ(0x5EU, AlbaBitValueUtilities<uint8_t>::getOnesComplement(0xA1U));
    EXPECT_EQ(0x5E45U, AlbaBitValueUtilities<uint16_t>::getOnesComplement(0xA1BAU));
    EXPECT_EQ(0x5E455E45U, AlbaBitValueUtilities<uint32_t>::getOnesComplement(0xA1BAA1BAU));
    EXPECT_EQ(0x5E455E455E455E45U, AlbaBitValueUtilities<uint64_t>::getOnesComplement(0xA1BAA1BAA1BAA1BAU));
}

TEST(AlbaBitValueUtilitiesTest, GetTwosComplementWorks)
{
    EXPECT_EQ(0x5FU, AlbaBitValueUtilities<uint8_t>::getTwosComplement(0xA1U));
    EXPECT_EQ(0x5E46U, AlbaBitValueUtilities<uint16_t>::getTwosComplement(0xA1BAU));
    EXPECT_EQ(0x5E455E46U, AlbaBitValueUtilities<uint32_t>::getTwosComplement(0xA1BAA1BAU));
    EXPECT_EQ(0x5E455E455E455E46U, AlbaBitValueUtilities<uint64_t>::getTwosComplement(0xA1BAA1BAA1BAA1BAU));
}

TEST(AlbaBitValueUtilitiesTest, GetGreatestPowerOf2FactorWorks)
{
    EXPECT_EQ(4U, AlbaBitValueUtilities<uint8_t>::getGreatestPowerOf2Factor(12U));
    EXPECT_EQ(2U, AlbaBitValueUtilities<uint16_t>::getGreatestPowerOf2Factor(1234U));
    EXPECT_EQ(64U, AlbaBitValueUtilities<uint32_t>::getGreatestPowerOf2Factor(123456U));
    EXPECT_EQ(2U, AlbaBitValueUtilities<uint64_t>::getGreatestPowerOf2Factor(12345678901234U));
}

TEST(AlbaBitValueUtilitiesPerformanceTest, DISABLED_GetNumberOfOnesWorks)
{
    // Results: ~1300ms

    using BitValueUtilities = AlbaBitValueUtilities<uint64_t>;

    unsigned int result(0);
    for(uint64_t value=1; value<10000000ULL; value++)
    {
        result = max(result, BitValueUtilities::getNumberOfOnes(value));
    }
    EXPECT_EQ(23U, result);
}

TEST(AlbaBitValueUtilitiesPerformanceTest, DISABLED_GetNumberOfOnesManuallyWorks)
{
    // Results: ~1700ms

    using BitValueUtilities = AlbaBitValueUtilities<uint64_t>;

    unsigned int result(0);
    constexpr unsigned int numberOfBits = BitValueUtilities::getNumberOfBits();
    for(uint64_t value=1; value<10000000ULL; value++)
    {
        unsigned int count(0);
        uint64_t valueForCount(value);
        for(unsigned int bitIndex=0; bitIndex<numberOfBits; bitIndex++)
        {
            if(valueForCount & 1)
            {
                count++;
            }
            valueForCount >>= 1;
        }
        result = max(result, count);
    }
    EXPECT_EQ(23U, result);
}

}
