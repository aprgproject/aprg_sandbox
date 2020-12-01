#include <Bit/AlbaBitManipulation.hpp>

#include <gtest/gtest.h>

using namespace alba;

TEST(AlbaBitManipulationTest, ShiftLeftWorks)
{
    EXPECT_EQ(0xA1u, AlbaBitManipulation<unsigned int>::shiftLeft<0>(0xA1));
    EXPECT_EQ(0xA100u, AlbaBitManipulation<unsigned int>::shiftLeft<1>(0xA1));
    EXPECT_EQ(0xA10000u, AlbaBitManipulation<unsigned int>::shiftLeft<2>(0xA1));
    EXPECT_EQ(0xA1000000u, AlbaBitManipulation<unsigned int>::shiftLeft<3>(0xA1));
}

TEST(AlbaBitManipulationTest, ShiftRightWorks)
{
    EXPECT_EQ(0xA1000000u, AlbaBitManipulation<unsigned int>::shiftRight<0>(0xA1000000));
    EXPECT_EQ(0xA10000u, AlbaBitManipulation<unsigned int>::shiftRight<1>(0xA1000000));
    EXPECT_EQ(0xA100u, AlbaBitManipulation<unsigned int>::shiftRight<2>(0xA1000000));
    EXPECT_EQ(0xA1u, AlbaBitManipulation<unsigned int>::shiftRight<3>(0xA1000000));
}

TEST(AlbaBitManipulationTest, Concatenation_ArgumentsSizeLessThanResult)
{
    // Given
    const unsigned char byte1 = 0xA1;
    const unsigned char byte2 = 0xBA;

    // When
    unsigned int result = AlbaBitManipulation<unsigned int>::concatenateBytes(byte1, byte2);

    // Then
    EXPECT_EQ(0xA1BAu, result);
}

TEST(AlbaBitManipulationTest, Concatenation_ArgumentsSameSizeAsResult)
{
    // Given
    const unsigned char byte1 = 0xA1;
    const unsigned char byte2 = 0xBA;

    // When
    unsigned int result = AlbaBitManipulation<unsigned int>::concatenateBytes(byte1, byte2, byte1, byte2);

    // Then
    EXPECT_EQ(0xA1BAA1BAu, result);
}

TEST(AlbaBitManipulationTest, BytesAreSuccessfullyObtainedWhenU32IsUsed)
{
    // Given
    const unsigned int input = 0x12345678;

    // When

    // Then
    EXPECT_EQ(0x78u, AlbaBitManipulation<unsigned int>::getByteAt<0>(input));
    EXPECT_EQ(0x56u, AlbaBitManipulation<unsigned int>::getByteAt<1>(input));
    EXPECT_EQ(0x34u, AlbaBitManipulation<unsigned int>::getByteAt<2>(input));
    EXPECT_EQ(0x12u, AlbaBitManipulation<unsigned int>::getByteAt<3>(input));
}

TEST(AlbaBitManipulationTest, DataIsSuccessfullySwappedWhenU16IsUsed)
{
    // Given
    const short unsigned int input = 0x1234;

    // When

    // Then
    EXPECT_EQ(0x3412u, AlbaBitManipulation<short unsigned int>::swap(input));
}

TEST(AlbaBitManipulationTest, DataIsSuccessfullySwappedWhenU32IsUsed)
{
    // Given
    const unsigned int input = 0x12345678;

    // When

    // Then
    EXPECT_EQ(0x78563412u, AlbaBitManipulation<unsigned int>::swap(input));
}

TEST(AlbaBitManipulationTest, DataIsSuccessfullySwappedWhenU64IsUsed)
{
    // Given
    const unsigned long long input = 0x123456789ABCDEF0;

    // When

    // Then
    EXPECT_EQ(0xF0DEBC9A78563412u, AlbaBitManipulation<unsigned long long>::swap(input));
}


TEST(AlbaBitManipulationTest, DataIsSuccessfullySwappedForTwoBytes)
{
    // Given
    const short unsigned int input = 0x1234;

    // When

    // Then
    EXPECT_EQ(0x3412u, AlbaBitManipulation<short unsigned int>::swapForTwoBytes(input));
}

TEST(AlbaBitManipulationTest, DataIsSuccessfullySwappedForFourBytes)
{
    // Given
    const unsigned int input = 0x12345678;

    // When

    // Then
    EXPECT_EQ(0x78563412u, AlbaBitManipulation<unsigned int>::swapForFourBytes(input));
}

TEST(AlbaBitManipulationTest, DataIsSuccessfullySwappedForEightBytes)
{
    // Given
    const unsigned long long input = 0x123456789ABCDEF0;

    // When

    // Then
    EXPECT_EQ(0xF0DEBC9A78563412u, AlbaBitManipulation<unsigned long long>::swapForEightBytes(input));
}

TEST(AlbaBitManipulationTest, GenerationOfOnesIsSuccessful)
{
    // Given
    const unsigned int input = 2;

    // When

    // Then
    EXPECT_EQ(0x00000003u, AlbaBitManipulation<unsigned int>::generateOnesWithNumberOfBits(input));
}

TEST(AlbaBitManipulationTest, GetAllBitsAsserted)
{
    EXPECT_EQ(0xFFFFu, AlbaBitManipulation<short unsigned int>::getAllBitsAsserted());
    EXPECT_EQ(0xFFFFFFFFu, AlbaBitManipulation<unsigned int>::getAllBitsAsserted());
    EXPECT_EQ(0xFFFFFFFFFFFFFFFFu, AlbaBitManipulation<unsigned long long>::getAllBitsAsserted());
}
