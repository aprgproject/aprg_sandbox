#include <AprgBitmap.hpp>

#include <gtest/gtest.h>
#include <iostream>

using namespace alba;
using namespace std;

#define APRG_BITMAP_MONOCHROME_TEST_FILE APRG_DIR R"(AprgBitmap\AprgBitmap\tst\Bitmaps\Monochrome.bmp)"
#define APRG_BITMAP_16_COLOR_TEST_FILE APRG_DIR R"(AprgBitmap\AprgBitmap\tst\Bitmaps\16ColorBitmap.bmp)"
#define APRG_BITMAP_256_COLOR_TEST_FILE APRG_DIR R"(AprgBitmap\AprgBitmap\tst\Bitmaps\256ColorBitmap.bmp)"
#define APRG_BITMAP_24_BIT_TEST_FILE APRG_DIR R"(AprgBitmap\AprgBitmap\tst\Bitmaps\24BitBitmap.bmp)"

TEST(BitmapTest, TestForMonochromeBitmap)
{    AprgBitmap bitmap(APRG_BITMAP_MONOCHROME_TEST_FILE);
    ASSERT_TRUE(bitmap.isValid());
    ASSERT_EQ(BitmapCompressedMethodType::BI_RGB, bitmap.getCompressedMethodType());
    ASSERT_TRUE(bitmap.isCompressedMethodSupported());
    AprgBitmap::ColorTable colors(bitmap.getColorTable());
    ASSERT_EQ(2, colors.size());
    EXPECT_EQ(colors[0], 0x00000000);
    EXPECT_EQ(colors[1], 0x00FFFFFF);

    bitmap.addPositionInSnippet(AprgBitmap::XY(99, 97));
    bitmap.addPositionInSnippet(AprgBitmap::XY(101, 99));
    bitmap.loadPixels();

    EXPECT_EQ(AprgBitmap::XY(96, 97), bitmap.getPositionOfTopLeftCornerInMemory());
    EXPECT_EQ(AprgBitmap::XY(103, 99), bitmap.getPositionOfBottomRightCornerInMemory());

    AprgBitmap::PixelData pixels(bitmap.getPixelsInMemory());
    unsigned char* reader = reinterpret_cast<unsigned char*>(pixels.getBufferPointer());
    ASSERT_EQ(3, pixels.getSize());
    EXPECT_EQ(0x8F, reader[0]);    EXPECT_EQ(0xF3, reader[1]);
    EXPECT_EQ(0xFF, reader[2]);

    EXPECT_EQ(0x00, bitmap.getPixelInSnippet(AprgBitmap::XY(99, 97)));
    EXPECT_EQ(0x01, bitmap.getPixelInSnippet(AprgBitmap::XY(100, 97)));
    EXPECT_EQ(0x01, bitmap.getPixelInSnippet(AprgBitmap::XY(101, 97)));
    EXPECT_EQ(0x01, bitmap.getPixelInSnippet(AprgBitmap::XY(99, 98)));
    EXPECT_EQ(0x00, bitmap.getPixelInSnippet(AprgBitmap::XY(100, 98)));
    EXPECT_EQ(0x00, bitmap.getPixelInSnippet(AprgBitmap::XY(101, 98)));
    EXPECT_EQ(0x01, bitmap.getPixelInSnippet(AprgBitmap::XY(99, 99)));
    EXPECT_EQ(0x01, bitmap.getPixelInSnippet(AprgBitmap::XY(100, 99)));
    EXPECT_EQ(0x01, bitmap.getPixelInSnippet(AprgBitmap::XY(101, 99)));

    bitmap.setMaximumMemoryConsumption(3);
    EXPECT_EQ(0x01, bitmap.getPixelWithAutomaticChangesToSnippet(AprgBitmap::XY(0, 0)));
    ASSERT_EQ(3, bitmap.getMemoryConsumption());
    EXPECT_EQ(AprgBitmap::XY(0, 0), bitmap.getPositionOfTopLeftCornerInMemory());
    EXPECT_EQ(AprgBitmap::XY(7, 2), bitmap.getPositionOfBottomRightCornerInMemory());

    EXPECT_EQ(0x01, bitmap.getPixelWithAutomaticChangesToSnippet(AprgBitmap::XY(152, 101)));
    ASSERT_EQ(3, bitmap.getMemoryConsumption());
    EXPECT_EQ(AprgBitmap::XY(152, 100), bitmap.getPositionOfTopLeftCornerInMemory());
    EXPECT_EQ(AprgBitmap::XY(159, 102), bitmap.getPositionOfBottomRightCornerInMemory());

    EXPECT_EQ(0x01, bitmap.getPixelWithAutomaticChangesToSnippet(AprgBitmap::XY(17, 114)));
    ASSERT_EQ(3, bitmap.getMemoryConsumption());
    EXPECT_EQ(AprgBitmap::XY(16 , 113), bitmap.getPositionOfTopLeftCornerInMemory());
    EXPECT_EQ(AprgBitmap::XY(23, 115), bitmap.getPositionOfBottomRightCornerInMemory());

    EXPECT_EQ(0x01, bitmap.getPixelWithAutomaticChangesToSnippet(AprgBitmap::XY(174, 173)));
    ASSERT_EQ(3, bitmap.getMemoryConsumption());
    EXPECT_EQ(AprgBitmap::XY(168, 171), bitmap.getPositionOfTopLeftCornerInMemory());
    EXPECT_EQ(AprgBitmap::XY(175, 173), bitmap.getPositionOfBottomRightCornerInMemory());

    EXPECT_EQ(0, bitmap.getPixelWithAutomaticChangesToSnippet(AprgBitmap::XY(180, 180)));
    ASSERT_EQ(3, bitmap.getMemoryConsumption());
    EXPECT_EQ(AprgBitmap::XY(168, 171), bitmap.getPositionOfTopLeftCornerInMemory());
    EXPECT_EQ(AprgBitmap::XY(175, 173), bitmap.getPositionOfBottomRightCornerInMemory());

    EXPECT_EQ(0x00000000, bitmap.getColorUsingPixelValue(0));
    EXPECT_EQ(0x00FFFFFF, bitmap.getColorUsingPixelValue(1));
}
TEST(BitmapTest, TestFor16ColorBitmap)
{
    AprgBitmap bitmap(APRG_BITMAP_16_COLOR_TEST_FILE);
    ASSERT_TRUE(bitmap.isValid());
    ASSERT_EQ(BitmapCompressedMethodType::BI_RGB, bitmap.getCompressedMethodType());
    ASSERT_TRUE(bitmap.isCompressedMethodSupported());
    AprgBitmap::ColorTable colors(bitmap.getColorTable());
    ASSERT_EQ(16, colors.size());
    EXPECT_EQ(colors[0], 0x00000000);    EXPECT_EQ(colors[7], 0x00808080);
    EXPECT_EQ(colors[8], 0x00C0C0C0);
    EXPECT_EQ(colors[15], 0x00FFFFFF);

    bitmap.addPositionInSnippet(AprgBitmap::XY(99, 97));
    bitmap.addPositionInSnippet(AprgBitmap::XY(101, 99));
    bitmap.loadPixels();

    EXPECT_EQ(AprgBitmap::XY(98, 97), bitmap.getPositionOfTopLeftCornerInMemory());
    EXPECT_EQ(AprgBitmap::XY(101, 99), bitmap.getPositionOfBottomRightCornerInMemory());

    AprgBitmap::PixelData pixels(bitmap.getPixelsInMemory());
    unsigned char* reader = reinterpret_cast<unsigned char*>(pixels.getBufferPointer());
    ASSERT_EQ(6, pixels.getSize());
    EXPECT_EQ(0x57, reader[0]);    EXPECT_EQ(0x78, reader[1]);
    EXPECT_EQ(0x87, reader[2]);
    EXPECT_EQ(0x77, reader[3]);
    EXPECT_EQ(0x8F, reader[4]);
    EXPECT_EQ(0xF8, reader[5]);

    EXPECT_EQ(0x07, bitmap.getPixelInSnippet(AprgBitmap::XY(99, 97)));
    EXPECT_EQ(0x07, bitmap.getPixelInSnippet(AprgBitmap::XY(100, 97)));
    EXPECT_EQ(0x08, bitmap.getPixelInSnippet(AprgBitmap::XY(101, 97)));
    EXPECT_EQ(0x07, bitmap.getPixelInSnippet(AprgBitmap::XY(99, 98)));
    EXPECT_EQ(0x07, bitmap.getPixelInSnippet(AprgBitmap::XY(100, 98)));
    EXPECT_EQ(0x07, bitmap.getPixelInSnippet(AprgBitmap::XY(101, 98)));
    EXPECT_EQ(0x0F, bitmap.getPixelInSnippet(AprgBitmap::XY(99, 99)));
    EXPECT_EQ(0x0F, bitmap.getPixelInSnippet(AprgBitmap::XY(100, 99)));
    EXPECT_EQ(0x08, bitmap.getPixelInSnippet(AprgBitmap::XY(101, 99)));

    bitmap.setMaximumMemoryConsumption(6);
    EXPECT_EQ(0x0F, bitmap.getPixelWithAutomaticChangesToSnippet(AprgBitmap::XY(0, 0)));
    ASSERT_EQ(6, bitmap.getMemoryConsumption());
    EXPECT_EQ(AprgBitmap::XY(0, 0), bitmap.getPositionOfTopLeftCornerInMemory());
    EXPECT_EQ(AprgBitmap::XY(3, 2), bitmap.getPositionOfBottomRightCornerInMemory());

    EXPECT_EQ(0x08, bitmap.getPixelWithAutomaticChangesToSnippet(AprgBitmap::XY(152, 101)));
    /*EXPECT_EQ(0x07, bitmap.getPixelWithAutomaticChangesToSnippet(AprgBitmap::XY(17, 114)));
    EXPECT_EQ(0x0F, bitmap.getPixelWithAutomaticChangesToSnippet(AprgBitmap::XY(174, 173)));
    EXPECT_EQ(0, bitmap.getPixelWithAutomaticChangesToSnippet(AprgBitmap::XY(180, 180)));

    EXPECT_EQ(0x00808080, bitmap.getColorUsingPixelValue(0x07));
    EXPECT_EQ(0x00C0C0C0, bitmap.getColorUsingPixelValue(0x08));*/
}

TEST(BitmapTest, TestFor256ColorBitmap)
{
    AprgBitmap bitmap(APRG_BITMAP_256_COLOR_TEST_FILE);
    ASSERT_TRUE(bitmap.isValid());
    ASSERT_EQ(BitmapCompressedMethodType::BI_RGB, bitmap.getCompressedMethodType());
    ASSERT_TRUE(bitmap.isCompressedMethodSupported());
    AprgBitmap::ColorTable colors(bitmap.getColorTable());
    ASSERT_EQ(256, colors.size());
    EXPECT_EQ(colors[0x00], 0x00000000);    EXPECT_EQ(colors[0x53], 0x00604040);
    EXPECT_EQ(colors[0xF5], 0x00A0C0C0);
    EXPECT_EQ(colors[0xFF], 0x00FFFFFF);

    bitmap.addPositionInSnippet(AprgBitmap::XY(99, 97));
    bitmap.addPositionInSnippet(AprgBitmap::XY(101, 99));
    bitmap.loadPixels();

    EXPECT_EQ(AprgBitmap::XY(99, 97), bitmap.getPositionOfTopLeftCornerInMemory());
    EXPECT_EQ(AprgBitmap::XY(101, 99), bitmap.getPositionOfBottomRightCornerInMemory());

    AprgBitmap::PixelData pixels(bitmap.getPixelsInMemory());
    unsigned char* reader = reinterpret_cast<unsigned char*>(pixels.getBufferPointer());
    ASSERT_EQ(9, pixels.getSize());
    EXPECT_EQ(0x53, reader[0]);    EXPECT_EQ(0xA4, reader[1]);
    EXPECT_EQ(0xF5, reader[2]);
    EXPECT_EQ(0xA5, reader[3]);
    EXPECT_EQ(0x9B, reader[4]);    EXPECT_EQ(0xA4, reader[5]);
    EXPECT_EQ(0xF6, reader[6]);
    EXPECT_EQ(0xF6, reader[7]);
    EXPECT_EQ(0x07, reader[8]);

    EXPECT_EQ(0x53, bitmap.getPixelInSnippet(AprgBitmap::XY(99, 97)));
    EXPECT_EQ(0xA4, bitmap.getPixelInSnippet(AprgBitmap::XY(100, 97)));
    EXPECT_EQ(0xF5, bitmap.getPixelInSnippet(AprgBitmap::XY(101, 97)));
    EXPECT_EQ(0xA5, bitmap.getPixelInSnippet(AprgBitmap::XY(99, 98)));
    EXPECT_EQ(0x9B, bitmap.getPixelInSnippet(AprgBitmap::XY(100, 98)));
    EXPECT_EQ(0xA4, bitmap.getPixelInSnippet(AprgBitmap::XY(101, 98)));
    EXPECT_EQ(0xF6, bitmap.getPixelInSnippet(AprgBitmap::XY(99, 99)));
    EXPECT_EQ(0xF6, bitmap.getPixelInSnippet(AprgBitmap::XY(100, 99)));
    EXPECT_EQ(0x07, bitmap.getPixelInSnippet(AprgBitmap::XY(101, 99)));

    EXPECT_EQ(0xFF, bitmap.getPixelWithAutomaticChangesToSnippet(AprgBitmap::XY(0, 0)));
    EXPECT_EQ(0xF5, bitmap.getPixelWithAutomaticChangesToSnippet(AprgBitmap::XY(152, 101)));
    EXPECT_EQ(0x9D, bitmap.getPixelWithAutomaticChangesToSnippet(AprgBitmap::XY(17, 114)));
    EXPECT_EQ(0xFF, bitmap.getPixelWithAutomaticChangesToSnippet(AprgBitmap::XY(174, 173)));
    EXPECT_EQ(0, bitmap.getPixelWithAutomaticChangesToSnippet(AprgBitmap::XY(180, 180)));

    EXPECT_EQ(0x00604040, bitmap.getColorUsingPixelValue(0x53));
    EXPECT_EQ(0x00A0C0C0, bitmap.getColorUsingPixelValue(0xF5));
}

TEST(BitmapTest, TestFor24BitBitmap)
{
    AprgBitmap bitmap(APRG_BITMAP_24_BIT_TEST_FILE);
    ASSERT_TRUE(bitmap.isValid());
    ASSERT_EQ(BitmapCompressedMethodType::BI_RGB, bitmap.getCompressedMethodType());
    ASSERT_TRUE(bitmap.isCompressedMethodSupported());

    AprgBitmap::ColorTable colors(bitmap.getColorTable());
    ASSERT_EQ(0, colors.size());

    bitmap.addPositionInSnippet(AprgBitmap::XY(99, 97));
    bitmap.addPositionInSnippet(AprgBitmap::XY(101, 99));
    bitmap.loadPixels();

    EXPECT_EQ(AprgBitmap::XY(99, 97), bitmap.getPositionOfTopLeftCornerInMemory());
    EXPECT_EQ(AprgBitmap::XY(101, 99), bitmap.getPositionOfBottomRightCornerInMemory());

    AprgBitmap::PixelData pixels(bitmap.getPixelsInMemory());
    unsigned char* reader = reinterpret_cast<unsigned char*>(pixels.getBufferPointer());
    ASSERT_EQ(27, pixels.getSize());
    EXPECT_EQ(0x5F, reader[0]);
    EXPECT_EQ(0x4F, reader[1]);
    EXPECT_EQ(0x56, reader[2]);
    EXPECT_EQ(0x94, reader[3]);
    EXPECT_EQ(0x8A, reader[4]);
    EXPECT_EQ(0x82, reader[5]);
    EXPECT_EQ(0xBA, reader[6]);
    EXPECT_EQ(0xB7, reader[7]);
    EXPECT_EQ(0xA2, reader[8]);
    EXPECT_EQ(0x96, reader[9]);
    EXPECT_EQ(0x8C, reader[10]);
    EXPECT_EQ(0x95, reader[11]);
    EXPECT_EQ(0x6D, reader[12]);
    EXPECT_EQ(0x5F, reader[13]);
    EXPECT_EQ(0x68, reader[14]);
    EXPECT_EQ(0x80, reader[15]);
    EXPECT_EQ(0x76, reader[16]);
    EXPECT_EQ(0x73, reader[17]);
    EXPECT_EQ(0xE6, reader[18]);
    EXPECT_EQ(0xE6, reader[19]);
    EXPECT_EQ(0xE6, reader[20]);
    EXPECT_EQ(0xE9, reader[21]);
    EXPECT_EQ(0xE8, reader[22]);
    EXPECT_EQ(0xE9, reader[23]);
    EXPECT_EQ(0xC3, reader[24]);
    EXPECT_EQ(0xBE, reader[25]);
    EXPECT_EQ(0xC2, reader[26]);

    EXPECT_EQ(0x564F5F, bitmap.getPixelInSnippet(AprgBitmap::XY(99, 97)));
    EXPECT_EQ(0x828A94, bitmap.getPixelInSnippet(AprgBitmap::XY(100, 97)));
    EXPECT_EQ(0xA2B7BA, bitmap.getPixelInSnippet(AprgBitmap::XY(101, 97)));
    EXPECT_EQ(0x958C96, bitmap.getPixelInSnippet(AprgBitmap::XY(99, 98)));
    EXPECT_EQ(0x685F6D, bitmap.getPixelInSnippet(AprgBitmap::XY(100, 98)));
    EXPECT_EQ(0x737680, bitmap.getPixelInSnippet(AprgBitmap::XY(101, 98)));
    EXPECT_EQ(0xE6E6E6, bitmap.getPixelInSnippet(AprgBitmap::XY(99, 99)));
    EXPECT_EQ(0xE9E8E9, bitmap.getPixelInSnippet(AprgBitmap::XY(100, 99)));
    EXPECT_EQ(0xC2BEC3, bitmap.getPixelInSnippet(AprgBitmap::XY(101, 99)));

    EXPECT_EQ(0xFFFFFF, bitmap.getPixelWithAutomaticChangesToSnippet(AprgBitmap::XY(0, 0)));
    EXPECT_EQ(0xAFB3B5, bitmap.getPixelWithAutomaticChangesToSnippet(AprgBitmap::XY(152, 101)));
    EXPECT_EQ(0x916E95, bitmap.getPixelWithAutomaticChangesToSnippet(AprgBitmap::XY(17, 114)));
    EXPECT_EQ(0xFFFFFF, bitmap.getPixelWithAutomaticChangesToSnippet(AprgBitmap::XY(174, 173)));
    EXPECT_EQ(0, bitmap.getPixelWithAutomaticChangesToSnippet(AprgBitmap::XY(180, 180)));

    /*EXPECT_EQ(0x00604040, bitmap.getColorUsingPixelValue(0x53));
    EXPECT_EQ(0x00A0C0C0, bitmap.getColorUsingPixelValue(0xF5));*/
}
