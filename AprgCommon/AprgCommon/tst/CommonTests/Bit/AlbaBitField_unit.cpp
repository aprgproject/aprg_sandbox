#include <Common/Bit/AlbaBitField.hpp>

#include <gtest/gtest.h>

namespace alba
{

TEST(AlbaSingleBitFieldTest, BitFieldWithOneBitWorks)
{
    AlbaSingleBitField<unsigned char, 1> bitField0{0};
    AlbaSingleBitField<unsigned char, 1> bitField1{1};

    EXPECT_EQ(1U, sizeof(AlbaSingleBitField<unsigned char, 1>));
    EXPECT_EQ(0U, bitField0.value);
    EXPECT_EQ(1U, bitField1.value);
}

TEST(AlbaSingleBitFieldTest, BitFieldWithTwoBitsWorks)
{
    AlbaSingleBitField<unsigned char, 2> bitField0{0};
    AlbaSingleBitField<unsigned char, 2> bitField1{3};

    EXPECT_EQ(1U, sizeof(AlbaSingleBitField<unsigned char, 1>));
    EXPECT_EQ(0U, bitField0.value);
    EXPECT_EQ(3U, bitField1.value);
}

TEST(AlbaSingleBitFieldTest, BitFieldWithThreeBitsWorks)
{
    AlbaSingleBitField<unsigned char, 3> bitField0{0};
    AlbaSingleBitField<unsigned char, 3> bitField1{7};

    EXPECT_EQ(1U, sizeof(AlbaSingleBitField<unsigned char, 1>));
    EXPECT_EQ(0U, bitField0.value);
    EXPECT_EQ(7U, bitField1.value);
}

TEST(AlbaSingleBitFieldTest, BitFieldWith28BitsWorks)
{
    AlbaSingleBitField<unsigned int, 28> bitField0{0};
    AlbaSingleBitField<unsigned int, 28> bitField1{268435455};

    EXPECT_EQ(4U, sizeof(AlbaSingleBitField<unsigned int, 28>));
    EXPECT_EQ(0U, bitField0.value);
    EXPECT_EQ(268435455U, bitField1.value);
}

}
