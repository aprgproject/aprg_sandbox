#include <Common/Bit/AlbaBitValueUtilities.hpp>

#include <gtest/gtest.h>

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

TEST(AlbaBitValueUtilitiesTest, GetTwosComplementWorks)
{
    EXPECT_EQ(0x5FU, AlbaBitValueUtilities<uint8_t>::getTwosComplement(0xA1U));
    EXPECT_EQ(0x5E46U, AlbaBitValueUtilities<uint16_t>::getTwosComplement(0xA1BAU));
    EXPECT_EQ(0x5E455E46U, AlbaBitValueUtilities<uint32_t>::getTwosComplement(0xA1BAA1BAU));
    EXPECT_EQ(0x5E455E455E455E46U, AlbaBitValueUtilities<uint64_t>::getTwosComplement(0xA1BAA1BAA1BAA1BAU));
}

}
