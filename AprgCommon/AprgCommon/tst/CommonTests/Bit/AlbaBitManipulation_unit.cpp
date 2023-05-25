#include <Common/Bit/AlbaBitManipulation.hpp>

#include <gtest/gtest.h>

namespace alba {

TEST(AlbaBitManipulationTest, ShiftBytesToTheLeftWorks) {
    EXPECT_EQ(0x0000'00A1U, AlbaBitManipulation<uint32_t>::shiftBytesToTheLeft<0>(0xA1));
    EXPECT_EQ(0x0000'A100U, AlbaBitManipulation<uint32_t>::shiftBytesToTheLeft<1>(0xA1));
    EXPECT_EQ(0x00A1'0000U, AlbaBitManipulation<uint32_t>::shiftBytesToTheLeft<2>(0xA1));
    EXPECT_EQ(0xA100'0000U, AlbaBitManipulation<uint32_t>::shiftBytesToTheLeft<3>(0xA1));
}

TEST(AlbaBitManipulationTest, ShiftBytesToTheRightWorks) {
    EXPECT_EQ(0xA100'0000U, AlbaBitManipulation<uint32_t>::shiftBytesToTheRight<0>(0xA100'0000));
    EXPECT_EQ(0x00A1'0000U, AlbaBitManipulation<uint32_t>::shiftBytesToTheRight<1>(0xA100'0000));
    EXPECT_EQ(0x0000'A100U, AlbaBitManipulation<uint32_t>::shiftBytesToTheRight<2>(0xA100'0000));
    EXPECT_EQ(0x0000'00A1U, AlbaBitManipulation<uint32_t>::shiftBytesToTheRight<3>(0xA100'0000));
}

TEST(AlbaBitManipulationTest, ShiftNibblesToTheLeftWorks) {
    EXPECT_EQ(0x0000'00A1U, AlbaBitManipulation<uint32_t>::shiftNibblesToTheLeft<0>(0xA1));
    EXPECT_EQ(0x0000'0A10U, AlbaBitManipulation<uint32_t>::shiftNibblesToTheLeft<1>(0xA1));
    EXPECT_EQ(0x0000'A100U, AlbaBitManipulation<uint32_t>::shiftNibblesToTheLeft<2>(0xA1));
    EXPECT_EQ(0x000A'1000U, AlbaBitManipulation<uint32_t>::shiftNibblesToTheLeft<3>(0xA1));
    EXPECT_EQ(0x00A1'0000U, AlbaBitManipulation<uint32_t>::shiftNibblesToTheLeft<4>(0xA1));
    EXPECT_EQ(0x0A10'0000U, AlbaBitManipulation<uint32_t>::shiftNibblesToTheLeft<5>(0xA1));
    EXPECT_EQ(0xA100'0000U, AlbaBitManipulation<uint32_t>::shiftNibblesToTheLeft<6>(0xA1));
    EXPECT_EQ(0x1000'0000U, AlbaBitManipulation<uint32_t>::shiftNibblesToTheLeft<7>(0xA1));
}

TEST(AlbaBitManipulationTest, ShiftNibblesToTheRightWorks) {
    EXPECT_EQ(0xA100'0000U, AlbaBitManipulation<uint32_t>::shiftNibblesToTheRight<0>(0xA100'0000));
    EXPECT_EQ(0x0A10'0000U, AlbaBitManipulation<uint32_t>::shiftNibblesToTheRight<1>(0xA100'0000));
    EXPECT_EQ(0x00A1'0000U, AlbaBitManipulation<uint32_t>::shiftNibblesToTheRight<2>(0xA100'0000));
    EXPECT_EQ(0x000A'1000U, AlbaBitManipulation<uint32_t>::shiftNibblesToTheRight<3>(0xA100'0000));
    EXPECT_EQ(0x0000'A100U, AlbaBitManipulation<uint32_t>::shiftNibblesToTheRight<4>(0xA100'0000));
    EXPECT_EQ(0x0000'0A10U, AlbaBitManipulation<uint32_t>::shiftNibblesToTheRight<5>(0xA100'0000));
    EXPECT_EQ(0x0000'00A1U, AlbaBitManipulation<uint32_t>::shiftNibblesToTheRight<6>(0xA100'0000));
    EXPECT_EQ(0x0000'000AU, AlbaBitManipulation<uint32_t>::shiftNibblesToTheRight<7>(0xA100'0000));
}

TEST(AlbaBitManipulationTest, ShiftBitsToTheLeftWorks) {
    EXPECT_EQ(0x0000'00A1U, AlbaBitManipulation<uint32_t>::shiftBitsToTheLeft<0>(0xA1));
    EXPECT_EQ(0x0000'0508U, AlbaBitManipulation<uint32_t>::shiftBitsToTheLeft<3>(0xA1));
    EXPECT_EQ(0x1420'0000U, AlbaBitManipulation<uint32_t>::shiftBitsToTheLeft<21>(0xA1));
    EXPECT_EQ(0x2000'0000U, AlbaBitManipulation<uint32_t>::shiftBitsToTheLeft<29>(0xA1));
    EXPECT_EQ(0x8000'0000U, AlbaBitManipulation<uint32_t>::shiftBitsToTheLeft<31>(0xA1));
}

TEST(AlbaBitManipulationTest, ShiftBitsToTheRightWorks) {
    EXPECT_EQ(0xA100'0000U, AlbaBitManipulation<uint32_t>::shiftBitsToTheRight<0>(0xA100'0000));
    EXPECT_EQ(0x1420'0000U, AlbaBitManipulation<uint32_t>::shiftBitsToTheRight<3>(0xA100'0000));
    EXPECT_EQ(0x0000'0508U, AlbaBitManipulation<uint32_t>::shiftBitsToTheRight<21>(0xA100'0000));
    EXPECT_EQ(0x0000'0005U, AlbaBitManipulation<uint32_t>::shiftBitsToTheRight<29>(0xA100'0000));
    EXPECT_EQ(0x0000'0001U, AlbaBitManipulation<uint32_t>::shiftBitsToTheRight<31>(0xA100'0000));
}

TEST(AlbaBitManipulationTest, RotateBitToTheLeftWorks) {
    EXPECT_EQ(0x0000'0142U, AlbaBitManipulation<uint32_t>::rotateBitToTheLeft<1>(0xA1));
    EXPECT_EQ(0x0000'0A10U, AlbaBitManipulation<uint32_t>::rotateBitToTheLeft<4>(0xA1));
    EXPECT_EQ(0x0000'A100U, AlbaBitManipulation<uint32_t>::rotateBitToTheLeft<8>(0xA1));
    EXPECT_EQ(0x1000'000AU, AlbaBitManipulation<uint32_t>::rotateBitToTheLeft<28>(0xA1));
}

TEST(AlbaBitManipulationTest, RotateBitToTheRightWorks) {
    EXPECT_EQ(0x5080'0000U, AlbaBitManipulation<uint32_t>::rotateBitToTheRight<1>(0xA100'0000));
    EXPECT_EQ(0x0A10'0000U, AlbaBitManipulation<uint32_t>::rotateBitToTheRight<4>(0xA100'0000));
    EXPECT_EQ(0x00A1'0000U, AlbaBitManipulation<uint32_t>::rotateBitToTheRight<8>(0xA100'0000));
    EXPECT_EQ(0x1000'000AU, AlbaBitManipulation<uint32_t>::rotateBitToTheRight<28>(0xA100'0000));
}

TEST(AlbaBitManipulationTest, RotateBitToTheLeftWithShiftValueWorks) {
    EXPECT_EQ(0x0000'0142U, AlbaBitManipulation<uint32_t>::rotateBitToTheLeftWithShiftValue(0xA1, 1U));
    EXPECT_EQ(0x0000'0A10U, AlbaBitManipulation<uint32_t>::rotateBitToTheLeftWithShiftValue(0xA1, 4U));
    EXPECT_EQ(0x0000'A100U, AlbaBitManipulation<uint32_t>::rotateBitToTheLeftWithShiftValue(0xA1, 8U));
    EXPECT_EQ(0x1000'000AU, AlbaBitManipulation<uint32_t>::rotateBitToTheLeftWithShiftValue(0xA1, 28U));
}

TEST(AlbaBitManipulationTest, RotateBitToTheRightWithShiftValueWorks) {
    EXPECT_EQ(0x5080'0000U, AlbaBitManipulation<uint32_t>::rotateBitToTheRightWithShiftValue(0xA100'0000, 1U));
    EXPECT_EQ(0x0A10'0000U, AlbaBitManipulation<uint32_t>::rotateBitToTheRightWithShiftValue(0xA100'0000, 4U));
    EXPECT_EQ(0x00A1'0000U, AlbaBitManipulation<uint32_t>::rotateBitToTheRightWithShiftValue(0xA100'0000, 8U));
    EXPECT_EQ(0x1000'000AU, AlbaBitManipulation<uint32_t>::rotateBitToTheRightWithShiftValue(0xA100'0000, 28U));
}

TEST(AlbaBitManipulationTest, ConcatenationBytesWorksWithArgumentsSizeLessThanResult) {
    // Given
    const uint8_t byte1 = 0xA1;
    const uint8_t byte2 = 0xBA;

    // When
    uint32_t result = AlbaBitManipulation<uint32_t>::concatenateBytes(byte1, byte2);

    // Then
    EXPECT_EQ(0xA1BAU, result);
}

TEST(AlbaBitManipulationTest, ConcatenationBytesWorksWithArgumentsSameSizeAsResult) {
    // Given
    const uint8_t byte1 = 0xA1;
    const uint8_t byte2 = 0xBA;

    // When
    uint32_t result = AlbaBitManipulation<uint32_t>::concatenateBytes(byte1, byte2, byte1, byte2);

    // Then
    EXPECT_EQ(0xA1BAA1BAU, result);
}

TEST(AlbaBitManipulationTest, ConcatenationNibblesWorksWithArgumentsSizeLessThanResult) {
    // Given
    const uint8_t byte1 = 0xA1;
    const uint8_t byte2 = 0xBA;

    // When
    uint32_t result = AlbaBitManipulation<uint32_t>::concatenateNibbles(byte1, byte2);

    // Then
    EXPECT_EQ(0x1AU, result);
}

TEST(AlbaBitManipulationTest, ConcatenationNibblesWorksWithArgumentsSameSizeAsResult) {
    // Given
    const uint8_t byte1 = 0xA1;
    const uint8_t byte2 = 0xBA;

    // When
    uint32_t result =
        AlbaBitManipulation<uint32_t>::concatenateNibbles(byte1, byte2, byte1, byte2, byte1, byte2, byte1, byte2);

    // Then
    EXPECT_EQ(0x1A1A1A1AU, result);
}

TEST(AlbaBitManipulationTest, BytesAreSuccessfullyObtainedWhenU32IsUsed) {
    // Given
    const uint32_t input = 0x12345678;

    // When

    // Then
    EXPECT_EQ(0x78U, AlbaBitManipulation<uint32_t>::getByteAt<0>(input));
    EXPECT_EQ(0x56U, AlbaBitManipulation<uint32_t>::getByteAt<1>(input));
    EXPECT_EQ(0x34U, AlbaBitManipulation<uint32_t>::getByteAt<2>(input));
    EXPECT_EQ(0x12U, AlbaBitManipulation<uint32_t>::getByteAt<3>(input));
}

TEST(AlbaBitManipulationTest, NibblesAreSuccessfullyObtainedWhenU32IsUsed) {
    // Given
    const uint32_t input = 0x12345678;

    // When

    // Then
    EXPECT_EQ(0x8U, AlbaBitManipulation<uint32_t>::getNibbleAt<0>(input));
    EXPECT_EQ(0x7U, AlbaBitManipulation<uint32_t>::getNibbleAt<1>(input));
    EXPECT_EQ(0x6U, AlbaBitManipulation<uint32_t>::getNibbleAt<2>(input));
    EXPECT_EQ(0x5U, AlbaBitManipulation<uint32_t>::getNibbleAt<3>(input));
    EXPECT_EQ(0x4U, AlbaBitManipulation<uint32_t>::getNibbleAt<4>(input));
    EXPECT_EQ(0x3U, AlbaBitManipulation<uint32_t>::getNibbleAt<5>(input));
    EXPECT_EQ(0x2U, AlbaBitManipulation<uint32_t>::getNibbleAt<6>(input));
    EXPECT_EQ(0x1U, AlbaBitManipulation<uint32_t>::getNibbleAt<7>(input));
}

TEST(AlbaBitManipulationTest, BitsAreSuccessfullyObtainedWhenU32IsUsed) {
    // Given
    const uint32_t input = 0x12345678;

    // When

    // Then
    EXPECT_EQ(0x0U, AlbaBitManipulation<uint32_t>::getBitAt<0>(input));
    EXPECT_EQ(0x1U, AlbaBitManipulation<uint32_t>::getBitAt<3>(input));
    EXPECT_EQ(0x1U, AlbaBitManipulation<uint32_t>::getBitAt<21>(input));
    EXPECT_EQ(0x0U, AlbaBitManipulation<uint32_t>::getBitAt<29>(input));
    EXPECT_EQ(0x0U, AlbaBitManipulation<uint32_t>::getBitAt<31>(input));
}

TEST(AlbaBitManipulationTest, DataIsSuccessfullySwappedWhenU16IsUsed) {
    // Given
    const uint16_t input = 0x1234;

    // When

    // Then
    EXPECT_EQ(0x3412U, AlbaBitManipulation<uint16_t>::swap(input));
}

TEST(AlbaBitManipulationTest, DataIsSuccessfullySwappedWhenU32IsUsed) {
    // Given
    const uint32_t input = 0x12345678;

    // When

    // Then
    EXPECT_EQ(0x78563412U, AlbaBitManipulation<uint32_t>::swap(input));
}

TEST(AlbaBitManipulationTest, DataIsSuccessfullySwappedWhenU64IsUsed) {
    // Given
    const uint64_t input = 0x1234'5678'9ABC'DEF0;

    // When

    // Then
    EXPECT_EQ(0xF0DE'BC9A'7856'3412U, AlbaBitManipulation<uint64_t>::swap(input));
}

TEST(AlbaBitManipulationTest, DataIsSuccessfullySwappedForTwoBytes) {
    // Given
    const uint16_t input = 0x1234;

    // When

    // Then
    EXPECT_EQ(0x3412U, AlbaBitManipulation<uint16_t>::swapForTwoBytes(input));
}

TEST(AlbaBitManipulationTest, DataIsSuccessfullySwappedForFourBytes) {
    // Given
    const uint32_t input = 0x1234'5678;

    // When

    // Then
    EXPECT_EQ(0x7856'3412U, AlbaBitManipulation<uint32_t>::swapForFourBytes(input));
}

TEST(AlbaBitManipulationTest, DataIsSuccessfullySwappedForEightBytes) {
    // Given
    const uint64_t input = 0x1234'5678'9ABC'DEF0;

    // When

    // Then
    EXPECT_EQ(0xF0DE'BC9A'7856'3412U, AlbaBitManipulation<uint64_t>::swapForEightBytes(input));
}

}  // namespace alba
