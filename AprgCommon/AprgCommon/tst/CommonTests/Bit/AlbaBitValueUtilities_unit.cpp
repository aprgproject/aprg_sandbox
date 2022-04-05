#include <Common/Bit/AlbaBitValueUtilities.hpp>

#include <gtest/gtest.h>

namespace alba
{

TEST(AlbaBitValueUtilitiesTest, GenerationOfOnesWorks)
{
    const unsigned int input = 2;

    EXPECT_EQ(0x00000003U, AlbaBitValueUtilities<uint32_t>::generateOnesWithNumberOfBits(input));
}

TEST(AlbaBitValueUtilitiesTest, GetAllBitsAssertedWorks)
{
    EXPECT_EQ(0xFFU, AlbaBitValueUtilities<uint8_t>::getAllBitsAsserted());
    EXPECT_EQ(0xFFFFU, AlbaBitValueUtilities<uint16_t>::getAllBitsAsserted());
    EXPECT_EQ(0xFFFFFFFFU, AlbaBitValueUtilities<uint32_t>::getAllBitsAsserted());
    EXPECT_EQ(0xFFFFFFFFFFFFFFFFU, AlbaBitValueUtilities<uint64_t>::getAllBitsAsserted());
}

TEST(AlbaBitValueUtilitiesTest, GetNumberOfBitsWorks)
{
    EXPECT_EQ(8U, AlbaBitValueUtilities<uint8_t>::getNumberOfBits());
    EXPECT_EQ(16U, AlbaBitValueUtilities<uint16_t>::getNumberOfBits());
    EXPECT_EQ(32U, AlbaBitValueUtilities<uint32_t>::getNumberOfBits());
    EXPECT_EQ(64U, AlbaBitValueUtilities<uint64_t>::getNumberOfBits());
}

TEST(AlbaBitValueUtilitiesTest, GetNumberOfBitsAssertedWorks)
{
    EXPECT_EQ(3U, AlbaBitValueUtilities<uint8_t>::getNumberOfBitsAsserted(0xA1U));
    EXPECT_EQ(8U, AlbaBitValueUtilities<uint16_t>::getNumberOfBitsAsserted(0xA1BAU));
    EXPECT_EQ(16U, AlbaBitValueUtilities<uint32_t>::getNumberOfBitsAsserted(0xA1BAA1BAU));
    EXPECT_EQ(32U, AlbaBitValueUtilities<uint64_t>::getNumberOfBitsAsserted(0xA1BAA1BAA1BAA1BAU));
}

}
