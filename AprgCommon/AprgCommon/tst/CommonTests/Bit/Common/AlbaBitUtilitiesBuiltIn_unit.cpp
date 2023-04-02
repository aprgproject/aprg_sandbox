#include <Common/Bit/Common/AlbaBitUtilitiesBuiltIn.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(AlbaBitUtilitiesBuiltInTest, IsEvenParityWorks)
{
    EXPECT_TRUE(BitUtilitiesBuiltIn::isEvenParity(0U));
    EXPECT_FALSE(BitUtilitiesBuiltIn::isEvenParity(1U));
    EXPECT_FALSE(BitUtilitiesBuiltIn::isEvenParity(2U));
    EXPECT_TRUE(BitUtilitiesBuiltIn::isEvenParity(3U));
    EXPECT_FALSE(BitUtilitiesBuiltIn::isEvenParity(4U));
}

TEST(AlbaBitUtilitiesBuiltInTest, IsEvenParityWorks_WithoutBuiltIn)
{
    EXPECT_TRUE(BitUtilitiesBuiltIn::BitUtilitiesWithoutBuiltIn::isEvenParity(0U));
    EXPECT_FALSE(BitUtilitiesBuiltIn::BitUtilitiesWithoutBuiltIn::isEvenParity(1U));
    EXPECT_FALSE(BitUtilitiesBuiltIn::BitUtilitiesWithoutBuiltIn::isEvenParity(2U));
    EXPECT_TRUE(BitUtilitiesBuiltIn::BitUtilitiesWithoutBuiltIn::isEvenParity(3U));
    EXPECT_FALSE(BitUtilitiesBuiltIn::BitUtilitiesWithoutBuiltIn::isEvenParity(4U));
}

TEST(AlbaBitUtilitiesBuiltInTest, GetNumberOfOnesWorks)
{
    EXPECT_EQ(3U, BitUtilitiesBuiltIn::getNumberOfOnes<uint8_t>(0xA1U));
    EXPECT_EQ(8U, BitUtilitiesBuiltIn::getNumberOfOnes<uint16_t>(0xA1BAU));
    EXPECT_EQ(16U, BitUtilitiesBuiltIn::getNumberOfOnes<uint32_t>(0xA1BA'A1BAU));
    EXPECT_EQ(32U, BitUtilitiesBuiltIn::getNumberOfOnes<uint64_t>(0xA1BA'A1BA'A1BA'A1BAULL));
}

TEST(AlbaBitUtilitiesBuiltInTest, GetNumberOfOnesWorks_WithoutBuiltIn)
{
    EXPECT_EQ(3U, BitUtilitiesBuiltIn::BitUtilitiesWithoutBuiltIn::getNumberOfOnes<uint8_t>(0xA1U));
    EXPECT_EQ(8U, BitUtilitiesBuiltIn::BitUtilitiesWithoutBuiltIn::getNumberOfOnes<uint16_t>(0xA1BAU));
    EXPECT_EQ(16U, BitUtilitiesBuiltIn::BitUtilitiesWithoutBuiltIn::getNumberOfOnes<uint32_t>(0xA1BA'A1BAU));
    EXPECT_EQ(32U, BitUtilitiesBuiltIn::BitUtilitiesWithoutBuiltIn::getNumberOfOnes<uint64_t>(0xA1BA'A1BA'A1BA'A1BAULL));
}

TEST(AlbaBitUtilitiesBuiltInTest, GetNumberOfConsecutiveZerosFromMsbWorks)
{
    EXPECT_EQ(0U, BitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromMsb<uint8_t>(0x80U));
    EXPECT_EQ(3U, BitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromMsb<uint8_t>(0x10U));
    EXPECT_EQ(7U, BitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromMsb<uint8_t>(0x01U));
    EXPECT_EQ(0U, BitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromMsb<uint16_t>(0x8000U));
    EXPECT_EQ(3U, BitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromMsb<uint16_t>(0x1000U));
    EXPECT_EQ(15U, BitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromMsb<uint16_t>(0x0001U));
    EXPECT_EQ(0U, BitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromMsb<uint32_t>(0x8000'0000U));
    EXPECT_EQ(3U, BitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromMsb<uint32_t>(0x1000'0000U));
    EXPECT_EQ(31U, BitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromMsb<uint32_t>(0x0000'0001U));
    EXPECT_EQ(0U, BitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromMsb<uint64_t>(0x8000'0000'0000'0000ULL));
    EXPECT_EQ(3U, BitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromMsb<uint64_t>(0x1000'0000'0000'0000ULL));
    EXPECT_EQ(63U, BitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromMsb<uint64_t>(0x0000'0000'0000'0001ULL));
}

TEST(AlbaBitUtilitiesBuiltInTest, GetNumberOfConsecutiveZerosFromMsbWorks_WithoutBuiltIn)
{
    EXPECT_EQ(0U, BitUtilitiesBuiltIn::BitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromMsb<uint8_t>(0x80U));
    EXPECT_EQ(3U, BitUtilitiesBuiltIn::BitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromMsb<uint8_t>(0x10U));
    EXPECT_EQ(7U, BitUtilitiesBuiltIn::BitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromMsb<uint8_t>(0x01U));
    EXPECT_EQ(0U, BitUtilitiesBuiltIn::BitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromMsb<uint16_t>(0x8000U));
    EXPECT_EQ(3U, BitUtilitiesBuiltIn::BitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromMsb<uint16_t>(0x1000U));
    EXPECT_EQ(15U, BitUtilitiesBuiltIn::BitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromMsb<uint16_t>(0x0001U));
    EXPECT_EQ(0U, BitUtilitiesBuiltIn::BitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromMsb<uint32_t>(0x8000'0000U));
    EXPECT_EQ(3U, BitUtilitiesBuiltIn::BitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromMsb<uint32_t>(0x1000'0000U));
    EXPECT_EQ(31U, BitUtilitiesBuiltIn::BitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromMsb<uint32_t>(0x0000'0001U));
    EXPECT_EQ(0U, BitUtilitiesBuiltIn::BitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromMsb<uint64_t>(0x8000'0000'0000'0000ULL));
    EXPECT_EQ(3U, BitUtilitiesBuiltIn::BitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromMsb<uint64_t>(0x1000'0000'0000'0000ULL));
    EXPECT_EQ(63U, BitUtilitiesBuiltIn::BitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromMsb<uint64_t>(0x0000'0000'0000'0001ULL));
}

TEST(AlbaBitUtilitiesBuiltInTest, GetNumberOfConsecutiveZerosFromLsbWorks)
{
    EXPECT_EQ(7U, BitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromLsb<uint8_t>(0x80U));
    EXPECT_EQ(3U, BitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromLsb<uint8_t>(0x08U));
    EXPECT_EQ(0U, BitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromLsb<uint8_t>(0x01U));
    EXPECT_EQ(15U, BitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromLsb<uint16_t>(0x8000U));
    EXPECT_EQ(3U, BitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromLsb<uint16_t>(0x0008U));
    EXPECT_EQ(0U, BitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromLsb<uint16_t>(0x0001U));
    EXPECT_EQ(31U, BitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromLsb<uint32_t>(0x8000'0000U));
    EXPECT_EQ(3U, BitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromLsb<uint32_t>(0x0000'0008U));
    EXPECT_EQ(0U, BitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromLsb<uint32_t>(0x0000'0001U));
    EXPECT_EQ(63U, BitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromLsb<uint64_t>(0x8000'0000'0000'0000ULL));
    EXPECT_EQ(3U, BitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromLsb<uint64_t>(0x0000'0000'0000'0008ULL));
    EXPECT_EQ(0U, BitUtilitiesBuiltIn::getNumberOfConsecutiveZerosFromLsb<uint64_t>(0x0000'0000'0000'0001ULL));
}

TEST(AlbaBitUtilitiesBuiltInTest, GetNumberOfConsecutiveZerosFromLsbWorks_WithoutBuiltIn)
{
    EXPECT_EQ(7U, BitUtilitiesBuiltIn::BitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromLsb<uint8_t>(0x80U));
    EXPECT_EQ(3U, BitUtilitiesBuiltIn::BitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromLsb<uint8_t>(0x08U));
    EXPECT_EQ(0U, BitUtilitiesBuiltIn::BitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromLsb<uint8_t>(0x01U));
    EXPECT_EQ(15U, BitUtilitiesBuiltIn::BitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromLsb<uint16_t>(0x8000U));
    EXPECT_EQ(3U, BitUtilitiesBuiltIn::BitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromLsb<uint16_t>(0x0008U));
    EXPECT_EQ(0U, BitUtilitiesBuiltIn::BitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromLsb<uint16_t>(0x0001U));
    EXPECT_EQ(31U, BitUtilitiesBuiltIn::BitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromLsb<uint32_t>(0x8000'0000U));
    EXPECT_EQ(3U, BitUtilitiesBuiltIn::BitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromLsb<uint32_t>(0x0000'0008U));
    EXPECT_EQ(0U, BitUtilitiesBuiltIn::BitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromLsb<uint32_t>(0x0000'0001U));
    EXPECT_EQ(63U, BitUtilitiesBuiltIn::BitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromLsb<uint64_t>(0x8000'0000'0000'0000ULL));
    EXPECT_EQ(3U, BitUtilitiesBuiltIn::BitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromLsb<uint64_t>(0x0000'0000'0000'0008ULL));
    EXPECT_EQ(0U, BitUtilitiesBuiltIn::BitUtilitiesWithoutBuiltIn::getNumberOfConsecutiveZerosFromLsb<uint64_t>(0x0000'0000'0000'0001ULL));
}

}
