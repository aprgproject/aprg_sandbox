#include <Bit/AlbaBitManipulation.hpp>

#include <gtest/gtest.h>

using namespace alba;

TEST(AlbaBitManipulationTest, Concatenation_ArgumentsSizeLessThanResult)
{
    // Given
    const unsigned char byte1 = 0xA1;
    const unsigned char byte2 = 0xBA;

    // When
    unsigned int result = AlbaBitManipulation<unsigned int>::concatenateBytes(byte1, byte2);

    // Then
    EXPECT_EQ(result, 0xA1BA);
}

TEST(AlbaBitManipulationTest, Concatenation_ArgumentsSameSizeAsResult)
{
    // Given
    const unsigned char byte1 = 0xA1;
    const unsigned char byte2 = 0xBA;

    // When
    unsigned int result = AlbaBitManipulation<unsigned int>::concatenateBytes(byte1, byte2, byte1, byte2);

    // Then
    EXPECT_EQ(result, 0xA1BAA1BA);
}

TEST(AlbaBitManipulationTest, BytesAreSuccessfullyObtainedWhenU32IsUsed)
{
    // Given
    const unsigned int input = 0x12345678;

    // When

    // Then
    EXPECT_EQ(0x78, AlbaBitManipulation<unsigned int>::getByteAtLeastSignificantPosition<0>(input));
    EXPECT_EQ(0x56, AlbaBitManipulation<unsigned int>::getByteAtLeastSignificantPosition<1>(input));
    EXPECT_EQ(0x34, AlbaBitManipulation<unsigned int>::getByteAtLeastSignificantPosition<2>(input));
    EXPECT_EQ(0x12, AlbaBitManipulation<unsigned int>::getByteAtLeastSignificantPosition<3>(input));
}

TEST(AlbaBitManipulationTest, DataIsSuccessfullySwappedWhenU16IsUsed)
{
    // Given
    const short unsigned int input = 0x1234;

    // When

    // Then
    EXPECT_EQ(0x3412, AlbaBitManipulation<short unsigned int>::swap(input));
}

TEST(AlbaBitManipulationTest, DataIsSuccessfullySwappedWhenU32IsUsed)
{
    // Given
    const unsigned int input = 0x12345678;

    // When

    // Then
    EXPECT_EQ(0x78563412, AlbaBitManipulation<unsigned int>::swap(input));
}

TEST(AlbaBitManipulationTest, DataIsSuccessfullySwappedWhenU64IsUsed)
{
    // Given
    const unsigned long long input = 0x123456789ABCDEF0;

    // When

    // Then
    EXPECT_EQ(0xF0DEBC9A78563412, AlbaBitManipulation<unsigned long long>::swap(input));
}


TEST(AlbaBitManipulationTest, DataIsSuccessfullySwappedForTwoBytes)
{
    // Given
    const short unsigned int input = 0x1234;

    // When

    // Then
    EXPECT_EQ(0x3412, AlbaBitManipulation<short unsigned int>::swapForTwoBytes(input));
}

TEST(AlbaBitManipulationTest, DataIsSuccessfullySwappedForFourBytes)
{
    // Given
    const unsigned int input = 0x12345678;

    // When

    // Then
    EXPECT_EQ(0x78563412, AlbaBitManipulation<unsigned int>::swapForFourBytes(input));
}

TEST(AlbaBitManipulationTest, DataIsSuccessfullySwappedForEightBytes)
{
    // Given
    const unsigned long long input = 0x123456789ABCDEF0;

    // When

    // Then
    EXPECT_EQ(0xF0DEBC9A78563412, AlbaBitManipulation<unsigned long long>::swapForEightBytes(input));
}

TEST(AlbaBitManipulationTest, GenerationOfOnesIsSuccessful)
{
    // Given
    const unsigned int input = 2;

    // When

    // Then
    EXPECT_EQ(0x00000003, AlbaBitManipulation<unsigned int>::generateOnesWithNumberOfBits(input));
}

TEST(AlbaBitManipulationTest, GetAllBitsAsserted)
{
    EXPECT_EQ(0xFFFF, AlbaBitManipulation<short unsigned int>::getAllBitsAsserted());
    EXPECT_EQ(0xFFFFFFFF, AlbaBitManipulation<unsigned int>::getAllBitsAsserted());
    EXPECT_EQ(0xFFFFFFFFFFFFFFFF, AlbaBitManipulation<unsigned long long>::getAllBitsAsserted());
}

