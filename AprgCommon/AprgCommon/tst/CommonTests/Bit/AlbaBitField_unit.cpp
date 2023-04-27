#include <Common/Bit/AlbaBitField.hpp>

#include <gtest/gtest.h>

namespace alba {

TEST(AlbaSingleBitFieldTest, BitFieldWithOneBitWorks) {
    AlbaSingleBitField<uint8_t, 1> bitField0{0};
    AlbaSingleBitField<uint8_t, 1> bitField1{1};

    EXPECT_EQ(1U, sizeof(AlbaSingleBitField<uint8_t, 1>));
    EXPECT_EQ(0U, bitField0.value);
    EXPECT_EQ(1U, bitField1.value);
}

TEST(AlbaSingleBitFieldTest, BitFieldWithTwoBitsWorks) {
    AlbaSingleBitField<uint8_t, 2> bitField0{0};
    AlbaSingleBitField<uint8_t, 2> bitField1{3};

    EXPECT_EQ(1U, sizeof(AlbaSingleBitField<uint8_t, 1>));
    EXPECT_EQ(0U, bitField0.value);
    EXPECT_EQ(3U, bitField1.value);
}

TEST(AlbaSingleBitFieldTest, BitFieldWithThreeBitsWorks) {
    AlbaSingleBitField<uint8_t, 3> bitField0{0};
    AlbaSingleBitField<uint8_t, 3> bitField1{7};

    EXPECT_EQ(1U, sizeof(AlbaSingleBitField<uint8_t, 1>));
    EXPECT_EQ(0U, bitField0.value);
    EXPECT_EQ(7U, bitField1.value);
}

TEST(AlbaSingleBitFieldTest, BitFieldWith28BitsWorks) {
    AlbaSingleBitField<uint32_t, 28> bitField0{0};
    AlbaSingleBitField<uint32_t, 28> bitField1{268435455};

    EXPECT_EQ(4U, sizeof(AlbaSingleBitField<uint32_t, 28>));
    EXPECT_EQ(0U, bitField0.value);
    EXPECT_EQ(268435455U, bitField1.value);
}

}  // namespace alba
