#include <Bit/AlbaBitManipulation.hpp>

#include <gtest/gtest.h>

using namespace alba;

TEST(AlbaBitManipulationTest, ShiftBytesToTheLeftWorks)
{
    EXPECT_EQ(0xA1u, AlbaBitManipulation<unsigned int>::shiftBytesToTheLeft<0>(0xA1));
    EXPECT_EQ(0xA100u, AlbaBitManipulation<unsigned int>::shiftBytesToTheLeft<1>(0xA1));
    EXPECT_EQ(0xA10000u, AlbaBitManipulation<unsigned int>::shiftBytesToTheLeft<2>(0xA1));
    EXPECT_EQ(0xA1000000u, AlbaBitManipulation<unsigned int>::shiftBytesToTheLeft<3>(0xA1));
}

TEST(AlbaBitManipulationTest, ShiftBytesToTheRightWorks)
{
    EXPECT_EQ(0xA1000000u, AlbaBitManipulation<unsigned int>::shiftBytesToTheRight<0>(0xA1000000));
    EXPECT_EQ(0xA10000u, AlbaBitManipulation<unsigned int>::shiftBytesToTheRight<1>(0xA1000000));
    EXPECT_EQ(0xA100u, AlbaBitManipulation<unsigned int>::shiftBytesToTheRight<2>(0xA1000000));
    EXPECT_EQ(0xA1u, AlbaBitManipulation<unsigned int>::shiftBytesToTheRight<3>(0xA1000000));
}

TEST(AlbaBitManipulationTest, ShiftNibblesToTheLeftWorks)
{
    EXPECT_EQ(0xA1u, AlbaBitManipulation<unsigned int>::shiftNibblesToTheLeft<0>(0xA1));
    EXPECT_EQ(0xA10u, AlbaBitManipulation<unsigned int>::shiftNibblesToTheLeft<1>(0xA1));
    EXPECT_EQ(0xA100u, AlbaBitManipulation<unsigned int>::shiftNibblesToTheLeft<2>(0xA1));
    EXPECT_EQ(0xA1000u, AlbaBitManipulation<unsigned int>::shiftNibblesToTheLeft<3>(0xA1));
    EXPECT_EQ(0xA10000u, AlbaBitManipulation<unsigned int>::shiftNibblesToTheLeft<4>(0xA1));
    EXPECT_EQ(0xA100000u, AlbaBitManipulation<unsigned int>::shiftNibblesToTheLeft<5>(0xA1));
    EXPECT_EQ(0xA1000000u, AlbaBitManipulation<unsigned int>::shiftNibblesToTheLeft<6>(0xA1));
    EXPECT_EQ(0x10000000u, AlbaBitManipulation<unsigned int>::shiftNibblesToTheLeft<7>(0xA1));
}

TEST(AlbaBitManipulationTest, ShiftNibblesToTheRightWorks)
{
    EXPECT_EQ(0xA1000000u, AlbaBitManipulation<unsigned int>::shiftNibblesToTheRight<0>(0xA1000000));
    EXPECT_EQ(0xA100000u, AlbaBitManipulation<unsigned int>::shiftNibblesToTheRight<1>(0xA1000000));
    EXPECT_EQ(0xA10000u, AlbaBitManipulation<unsigned int>::shiftNibblesToTheRight<2>(0xA1000000));
    EXPECT_EQ(0xA1000u, AlbaBitManipulation<unsigned int>::shiftNibblesToTheRight<3>(0xA1000000));
    EXPECT_EQ(0xA100u, AlbaBitManipulation<unsigned int>::shiftNibblesToTheRight<4>(0xA1000000));
    EXPECT_EQ(0xA10u, AlbaBitManipulation<unsigned int>::shiftNibblesToTheRight<5>(0xA1000000));
    EXPECT_EQ(0xA1u, AlbaBitManipulation<unsigned int>::shiftNibblesToTheRight<6>(0xA1000000));
    EXPECT_EQ(0xAu, AlbaBitManipulation<unsigned int>::shiftNibblesToTheRight<7>(0xA1000000));
}

TEST(AlbaBitManipulationTest, ConcatenationBytes_ArgumentsSizeLessThanResult)
{
    // Given
    const unsigned char byte1 = 0xA1;
    const unsigned char byte2 = 0xBA;
    // When
    unsigned int result = AlbaBitManipulation<unsigned int>::concatenateBytes(byte1, byte2);
    // Then
    EXPECT_EQ(0xA1BAu, result);
}

TEST(AlbaBitManipulationTest, ConcatenationBytes_ArgumentsSameSizeAsResult)
{
    // Given
    const unsigned char byte1 = 0xA1;    const unsigned char byte2 = 0xBA;

    // When
    unsigned int result = AlbaBitManipulation<unsigned int>::concatenateBytes(byte1, byte2, byte1, byte2);
    // Then
    EXPECT_EQ(0xA1BAA1BAu, result);
}

TEST(AlbaBitManipulationTest, ConcatenationNibbles_ArgumentsSizeLessThanResult)
{
    // Given
    const unsigned char byte1 = 0xA1;
    const unsigned char byte2 = 0xBA;

    // When
    unsigned int result = AlbaBitManipulation<unsigned int>::concatenateNibbles(byte1, byte2);

    // Then
    EXPECT_EQ(0x1Au, result);
}

TEST(AlbaBitManipulationTest, ConcatenationNibbles_ArgumentsSameSizeAsResult)
{
    // Given
    const unsigned char byte1 = 0xA1;
    const unsigned char byte2 = 0xBA;

    // When
    unsigned int result = AlbaBitManipulation<unsigned int>::concatenateNibbles(byte1, byte2, byte1, byte2, byte1, byte2, byte1, byte2);

    // Then
    EXPECT_EQ(0x1A1A1A1Au, result);
}

TEST(AlbaBitManipulationTest, BytesAreSuccessfullyObtainedWhenU32IsUsed)
{
    // Given    const unsigned int input = 0x12345678;

    // When
    // Then
    EXPECT_EQ(0x78u, AlbaBitManipulation<unsigned int>::getByteAt<0>(input));
    EXPECT_EQ(0x56u, AlbaBitManipulation<unsigned int>::getByteAt<1>(input));
    EXPECT_EQ(0x34u, AlbaBitManipulation<unsigned int>::getByteAt<2>(input));
    EXPECT_EQ(0x12u, AlbaBitManipulation<unsigned int>::getByteAt<3>(input));
}

TEST(AlbaBitManipulationTest, NibblesAreSuccessfullyObtainedWhenU32IsUsed)
{
    // Given
    const unsigned int input = 0x12345678;

    // When

    // Then
    EXPECT_EQ(0x8u, AlbaBitManipulation<unsigned int>::getNibbleAt<0>(input));
    EXPECT_EQ(0x7u, AlbaBitManipulation<unsigned int>::getNibbleAt<1>(input));
    EXPECT_EQ(0x6u, AlbaBitManipulation<unsigned int>::getNibbleAt<2>(input));
    EXPECT_EQ(0x5u, AlbaBitManipulation<unsigned int>::getNibbleAt<3>(input));
    EXPECT_EQ(0x4u, AlbaBitManipulation<unsigned int>::getNibbleAt<4>(input));
    EXPECT_EQ(0x3u, AlbaBitManipulation<unsigned int>::getNibbleAt<5>(input));
    EXPECT_EQ(0x2u, AlbaBitManipulation<unsigned int>::getNibbleAt<6>(input));
    EXPECT_EQ(0x1u, AlbaBitManipulation<unsigned int>::getNibbleAt<7>(input));
}

TEST(AlbaBitManipulationTest, DataIsSuccessfullySwappedWhenU16IsUsed)
{
    // Given    const short unsigned int input = 0x1234;

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
