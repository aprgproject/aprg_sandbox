#include <Common/Bit/AlbaBitManipulation.hpp>

#include <gtest/gtest.h>

namespace alba
{

TEST(AlbaBitManipulationTest, ShiftBytesToTheLeftWorks)
{
    EXPECT_EQ(0xA1U, AlbaBitManipulation<unsigned int>::shiftBytesToTheLeft<0>(0xA1));
    EXPECT_EQ(0xA100U, AlbaBitManipulation<unsigned int>::shiftBytesToTheLeft<1>(0xA1));
    EXPECT_EQ(0xA10000U, AlbaBitManipulation<unsigned int>::shiftBytesToTheLeft<2>(0xA1));
    EXPECT_EQ(0xA1000000U, AlbaBitManipulation<unsigned int>::shiftBytesToTheLeft<3>(0xA1));
}

TEST(AlbaBitManipulationTest, ShiftBytesToTheRightWorks)
{
    EXPECT_EQ(0xA1000000U, AlbaBitManipulation<unsigned int>::shiftBytesToTheRight<0>(0xA1000000));
    EXPECT_EQ(0xA10000U, AlbaBitManipulation<unsigned int>::shiftBytesToTheRight<1>(0xA1000000));
    EXPECT_EQ(0xA100U, AlbaBitManipulation<unsigned int>::shiftBytesToTheRight<2>(0xA1000000));
    EXPECT_EQ(0xA1U, AlbaBitManipulation<unsigned int>::shiftBytesToTheRight<3>(0xA1000000));
}

TEST(AlbaBitManipulationTest, ShiftNibblesToTheLeftWorks)
{
    EXPECT_EQ(0xA1U, AlbaBitManipulation<unsigned int>::shiftNibblesToTheLeft<0>(0xA1));
    EXPECT_EQ(0xA10U, AlbaBitManipulation<unsigned int>::shiftNibblesToTheLeft<1>(0xA1));
    EXPECT_EQ(0xA100U, AlbaBitManipulation<unsigned int>::shiftNibblesToTheLeft<2>(0xA1));
    EXPECT_EQ(0xA1000U, AlbaBitManipulation<unsigned int>::shiftNibblesToTheLeft<3>(0xA1));
    EXPECT_EQ(0xA10000U, AlbaBitManipulation<unsigned int>::shiftNibblesToTheLeft<4>(0xA1));
    EXPECT_EQ(0xA100000U, AlbaBitManipulation<unsigned int>::shiftNibblesToTheLeft<5>(0xA1));
    EXPECT_EQ(0xA1000000U, AlbaBitManipulation<unsigned int>::shiftNibblesToTheLeft<6>(0xA1));
    EXPECT_EQ(0x10000000U, AlbaBitManipulation<unsigned int>::shiftNibblesToTheLeft<7>(0xA1));
}

TEST(AlbaBitManipulationTest, ShiftNibblesToTheRightWorks)
{
    EXPECT_EQ(0xA1000000U, AlbaBitManipulation<unsigned int>::shiftNibblesToTheRight<0>(0xA1000000));
    EXPECT_EQ(0xA100000U, AlbaBitManipulation<unsigned int>::shiftNibblesToTheRight<1>(0xA1000000));
    EXPECT_EQ(0xA10000U, AlbaBitManipulation<unsigned int>::shiftNibblesToTheRight<2>(0xA1000000));
    EXPECT_EQ(0xA1000U, AlbaBitManipulation<unsigned int>::shiftNibblesToTheRight<3>(0xA1000000));
    EXPECT_EQ(0xA100U, AlbaBitManipulation<unsigned int>::shiftNibblesToTheRight<4>(0xA1000000));
    EXPECT_EQ(0xA10U, AlbaBitManipulation<unsigned int>::shiftNibblesToTheRight<5>(0xA1000000));
    EXPECT_EQ(0xA1U, AlbaBitManipulation<unsigned int>::shiftNibblesToTheRight<6>(0xA1000000));
    EXPECT_EQ(0xAU, AlbaBitManipulation<unsigned int>::shiftNibblesToTheRight<7>(0xA1000000));
}

TEST(AlbaBitManipulationTest, ShiftBitsToTheLeftWorks)
{
    EXPECT_EQ(0xA1U, AlbaBitManipulation<unsigned int>::shiftBitsToTheLeft<0>(0xA1));
    EXPECT_EQ(0x508U, AlbaBitManipulation<unsigned int>::shiftBitsToTheLeft<3>(0xA1));
    EXPECT_EQ(0x14200000U, AlbaBitManipulation<unsigned int>::shiftBitsToTheLeft<21>(0xA1));
    EXPECT_EQ(0x20000000U, AlbaBitManipulation<unsigned int>::shiftBitsToTheLeft<29>(0xA1));
    EXPECT_EQ(0x80000000U, AlbaBitManipulation<unsigned int>::shiftBitsToTheLeft<31>(0xA1));
}

TEST(AlbaBitManipulationTest, ShiftBitsToTheRightWorks)
{
    EXPECT_EQ(0xA1000000U, AlbaBitManipulation<unsigned int>::shiftBitsToTheRight<0>(0xA1000000));
    EXPECT_EQ(0x14200000U, AlbaBitManipulation<unsigned int>::shiftBitsToTheRight<3>(0xA1000000));
    EXPECT_EQ(0x508U, AlbaBitManipulation<unsigned int>::shiftBitsToTheRight<21>(0xA1000000));
    EXPECT_EQ(0x5U, AlbaBitManipulation<unsigned int>::shiftBitsToTheRight<29>(0xA1000000));
    EXPECT_EQ(0x1U, AlbaBitManipulation<unsigned int>::shiftBitsToTheRight<31>(0xA1000000));
}

TEST(AlbaBitManipulationTest, RotateBitToTheLeftWorks)
{
    EXPECT_EQ(0x142U, AlbaBitManipulation<unsigned int>::rotateBitToTheLeft<1>(0xA1));
    EXPECT_EQ(0xA10U, AlbaBitManipulation<unsigned int>::rotateBitToTheLeft<4>(0xA1));
    EXPECT_EQ(0xA100U, AlbaBitManipulation<unsigned int>::rotateBitToTheLeft<8>(0xA1));
    EXPECT_EQ(0x1000000AU, AlbaBitManipulation<unsigned int>::rotateBitToTheLeft<28>(0xA1));
}

TEST(AlbaBitManipulationTest, RotateBitToTheRightWorks)
{
    EXPECT_EQ(0x50800000U, AlbaBitManipulation<unsigned int>::rotateBitToTheRight<1>(0xA1000000));
    EXPECT_EQ(0xA100000U, AlbaBitManipulation<unsigned int>::rotateBitToTheRight<4>(0xA1000000));
    EXPECT_EQ(0xA10000U, AlbaBitManipulation<unsigned int>::rotateBitToTheRight<8>(0xA1000000));
    EXPECT_EQ(0x1000000AU, AlbaBitManipulation<unsigned int>::rotateBitToTheRight<28>(0xA1000000));
}

TEST(AlbaBitManipulationTest, RotateBitToTheLeftWithShiftValueWorks)
{
    EXPECT_EQ(0x142U, AlbaBitManipulation<unsigned int>::rotateBitToTheLeftWithShiftValue(0xA1, 1U));
    EXPECT_EQ(0xA10U, AlbaBitManipulation<unsigned int>::rotateBitToTheLeftWithShiftValue(0xA1, 4U));
    EXPECT_EQ(0xA100U, AlbaBitManipulation<unsigned int>::rotateBitToTheLeftWithShiftValue(0xA1, 8U));
    EXPECT_EQ(0x1000000AU, AlbaBitManipulation<unsigned int>::rotateBitToTheLeftWithShiftValue(0xA1, 28U));
}

TEST(AlbaBitManipulationTest, RotateBitToTheRightWithShiftValueWorks)
{
    EXPECT_EQ(0x50800000U, AlbaBitManipulation<unsigned int>::rotateBitToTheRightWithShiftValue(0xA1000000, 1U));
    EXPECT_EQ(0xA100000U, AlbaBitManipulation<unsigned int>::rotateBitToTheRightWithShiftValue(0xA1000000, 4U));
    EXPECT_EQ(0xA10000U, AlbaBitManipulation<unsigned int>::rotateBitToTheRightWithShiftValue(0xA1000000, 8U));
    EXPECT_EQ(0x1000000AU, AlbaBitManipulation<unsigned int>::rotateBitToTheRightWithShiftValue(0xA1000000, 28U));
}

TEST(AlbaBitManipulationTest, ConcatenationBytesWorksWithArgumentsSizeLessThanResult)
{
    // Given
    const unsigned char byte1 = 0xA1;
    const unsigned char byte2 = 0xBA;

    // When
    unsigned int result = AlbaBitManipulation<unsigned int>::concatenateBytes(byte1, byte2);

    // Then
    EXPECT_EQ(0xA1BAU, result);
}

TEST(AlbaBitManipulationTest, ConcatenationBytesWorksWithArgumentsSameSizeAsResult)
{
    // Given
    const unsigned char byte1 = 0xA1;
    const unsigned char byte2 = 0xBA;

    // When
    unsigned int result = AlbaBitManipulation<unsigned int>::concatenateBytes(byte1, byte2, byte1, byte2);

    // Then
    EXPECT_EQ(0xA1BAA1BAU, result);
}

TEST(AlbaBitManipulationTest, ConcatenationNibblesWorksWithArgumentsSizeLessThanResult)
{
    // Given
    const unsigned char byte1 = 0xA1;
    const unsigned char byte2 = 0xBA;

    // When
    unsigned int result = AlbaBitManipulation<unsigned int>::concatenateNibbles(byte1, byte2);

    // Then
    EXPECT_EQ(0x1AU, result);
}

TEST(AlbaBitManipulationTest, ConcatenationNibblesWorksWithArgumentsSameSizeAsResult)
{
    // Given
    const unsigned char byte1 = 0xA1;
    const unsigned char byte2 = 0xBA;

    // When
    unsigned int result = AlbaBitManipulation<unsigned int>::concatenateNibbles(byte1, byte2, byte1, byte2, byte1, byte2, byte1, byte2);

    // Then
    EXPECT_EQ(0x1A1A1A1AU, result);
}

TEST(AlbaBitManipulationTest, BytesAreSuccessfullyObtainedWhenU32IsUsed)
{
    // Given
    const unsigned int input = 0x12345678;

    // When

    // Then
    EXPECT_EQ(0x78U, AlbaBitManipulation<unsigned int>::getByteAt<0>(input));
    EXPECT_EQ(0x56U, AlbaBitManipulation<unsigned int>::getByteAt<1>(input));
    EXPECT_EQ(0x34U, AlbaBitManipulation<unsigned int>::getByteAt<2>(input));
    EXPECT_EQ(0x12U, AlbaBitManipulation<unsigned int>::getByteAt<3>(input));
}

TEST(AlbaBitManipulationTest, NibblesAreSuccessfullyObtainedWhenU32IsUsed)
{
    // Given
    const unsigned int input = 0x12345678;

    // When

    // Then
    EXPECT_EQ(0x8U, AlbaBitManipulation<unsigned int>::getNibbleAt<0>(input));
    EXPECT_EQ(0x7U, AlbaBitManipulation<unsigned int>::getNibbleAt<1>(input));
    EXPECT_EQ(0x6U, AlbaBitManipulation<unsigned int>::getNibbleAt<2>(input));
    EXPECT_EQ(0x5U, AlbaBitManipulation<unsigned int>::getNibbleAt<3>(input));
    EXPECT_EQ(0x4U, AlbaBitManipulation<unsigned int>::getNibbleAt<4>(input));
    EXPECT_EQ(0x3U, AlbaBitManipulation<unsigned int>::getNibbleAt<5>(input));
    EXPECT_EQ(0x2U, AlbaBitManipulation<unsigned int>::getNibbleAt<6>(input));
    EXPECT_EQ(0x1U, AlbaBitManipulation<unsigned int>::getNibbleAt<7>(input));
}

TEST(AlbaBitManipulationTest, BitsAreSuccessfullyObtainedWhenU32IsUsed)
{
    // Given
    const unsigned int input = 0x12345678;

    // When

    // Then
    EXPECT_EQ(0x0U, AlbaBitManipulation<unsigned int>::getBitAt<0>(input));
    EXPECT_EQ(0x1U, AlbaBitManipulation<unsigned int>::getBitAt<3>(input));
    EXPECT_EQ(0x1U, AlbaBitManipulation<unsigned int>::getBitAt<21>(input));
    EXPECT_EQ(0x0U, AlbaBitManipulation<unsigned int>::getBitAt<29>(input));
    EXPECT_EQ(0x0U, AlbaBitManipulation<unsigned int>::getBitAt<31>(input));
}

TEST(AlbaBitManipulationTest, DataIsSuccessfullySwappedWhenU16IsUsed)
{
    // Given
    const uint16_t input = 0x1234;

    // When

    // Then
    EXPECT_EQ(0x3412U, AlbaBitManipulation<uint16_t>::swap(input));
}

TEST(AlbaBitManipulationTest, DataIsSuccessfullySwappedWhenU32IsUsed)
{
    // Given
    const uint32_t input = 0x12345678;

    // When

    // Then
    EXPECT_EQ(0x78563412U, AlbaBitManipulation<uint32_t>::swap(input));
}

TEST(AlbaBitManipulationTest, DataIsSuccessfullySwappedWhenU64IsUsed)
{
    // Given
    const uint64_t input = 0x123456789ABCDEF0;

    // When

    // Then
    EXPECT_EQ(0xF0DEBC9A78563412U, AlbaBitManipulation<uint64_t>::swap(input));
}


TEST(AlbaBitManipulationTest, DataIsSuccessfullySwappedForTwoBytes)
{
    // Given
    const uint16_t input = 0x1234;

    // When

    // Then
    EXPECT_EQ(0x3412U, AlbaBitManipulation<uint16_t>::swapForTwoBytes(input));
}

TEST(AlbaBitManipulationTest, DataIsSuccessfullySwappedForFourBytes)
{
    // Given
    const uint32_t input = 0x12345678;

    // When

    // Then
    EXPECT_EQ(0x78563412U, AlbaBitManipulation<uint32_t>::swapForFourBytes(input));
}

TEST(AlbaBitManipulationTest, DataIsSuccessfullySwappedForEightBytes)
{
    // Given
    const uint64_t input = 0x123456789ABCDEF0;

    // When

    // Then
    EXPECT_EQ(0xF0DEBC9A78563412U, AlbaBitManipulation<uint64_t>::swapForEightBytes(input));
}

}
