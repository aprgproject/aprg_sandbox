#include <AprgBitmap.hpp>

#include <gtest/gtest.h>
#include <iostream>

using namespace alba;
using namespace std;

#define APRG_BITMAP_MONOCHROME_TEST_FILE APRG_DIR R"(AprgBitmap\AprgBitmap\tst\Bitmaps\Monochrome.bmp)"
#define APRG_BITMAP_16COLOR_TEST_FILE APRG_DIR R"(AprgBitmap\AprgBitmap\tst\Bitmaps\16ColorBitmap.bmp)"
#define APRG_BITMAP_256COLOR_TEST_FILE APRG_DIR R"(AprgBitmap\AprgBitmap\tst\Bitmaps\256ColorBitmap.bmp)"

TEST(BitmapTest, TestForMonochromeBitmap)
{
    AprgBitmap bitmap(APRG_BITMAP_MONOCHROME_TEST_FILE);
    ASSERT_TRUE(bitmap.isValid());
    ASSERT_EQ(BitmapCompressedMethodType::BI_RGB, bitmap.getCompressedMethodType());
    ASSERT_TRUE(bitmap.isCompressedMethodSupported());

    AprgBitmap::ColorTable colors(bitmap.getColorTable());
    ASSERT_EQ(2, colors.size());
    EXPECT_EQ(colors[0], 0x00000000);
    EXPECT_EQ(colors[1], 0x00FFFFFF);

    bitmap.addPositionToLoadInMemory(AprgBitmap::XY(99, 97));
    bitmap.addPositionToLoadInMemory(AprgBitmap::XY(101, 99));
    bitmap.loadPixels();

    EXPECT_EQ(AprgBitmap::XY(96, 97), bitmap.getPositionOfTopLeftCornerInMemory());
    EXPECT_EQ(AprgBitmap::XY(103, 99), bitmap.getPositionOfBottomRightCornerInMemory());

    AprgBitmap::Pixels pixels(bitmap.getPixelsInMemory());
    unsigned char* reader = reinterpret_cast<unsigned char*>(pixels.getBufferPointer());
    ASSERT_EQ(3, pixels.getSize());
    EXPECT_EQ(0x8F, reader[0]);
    EXPECT_EQ(0xF3, reader[1]);
    EXPECT_EQ(0xFF, reader[2]);

    EXPECT_EQ(0x00, bitmap.getPixelAtPositionRestrictedToSnippet(AprgBitmap::XY(99, 97)));
    EXPECT_EQ(0x01, bitmap.getPixelAtPositionRestrictedToSnippet(AprgBitmap::XY(100, 97)));
    EXPECT_EQ(0x01, bitmap.getPixelAtPositionRestrictedToSnippet(AprgBitmap::XY(101, 97)));
    EXPECT_EQ(0x01, bitmap.getPixelAtPositionRestrictedToSnippet(AprgBitmap::XY(99, 98)));
    EXPECT_EQ(0x00, bitmap.getPixelAtPositionRestrictedToSnippet(AprgBitmap::XY(100, 98)));
    EXPECT_EQ(0x00, bitmap.getPixelAtPositionRestrictedToSnippet(AprgBitmap::XY(101, 98)));
    EXPECT_EQ(0x01, bitmap.getPixelAtPositionRestrictedToSnippet(AprgBitmap::XY(99, 99)));
    EXPECT_EQ(0x01, bitmap.getPixelAtPositionRestrictedToSnippet(AprgBitmap::XY(100, 99)));
    EXPECT_EQ(0x01, bitmap.getPixelAtPositionRestrictedToSnippet(AprgBitmap::XY(101, 99)));

    EXPECT_EQ(0x01, bitmap.getPixelAtPositionWithAutomaticChangesToSnippet(AprgBitmap::XY(152, 101)));
    EXPECT_EQ(0x01, bitmap.getPixelAtPositionWithAutomaticChangesToSnippet(AprgBitmap::XY(17, 114)));
    EXPECT_EQ(0x01, bitmap.getPixelAtPositionWithAutomaticChangesToSnippet(AprgBitmap::XY(113, 11)));

    EXPECT_EQ(0x00000000, bitmap.getColorUsingPixelValue(0));
    EXPECT_EQ(0x00FFFFFF, bitmap.getColorUsingPixelValue(1));
}

TEST(BitmapTest, TestFor16ColorBitmap)
{
    AprgBitmap bitmap(APRG_BITMAP_16COLOR_TEST_FILE);
    ASSERT_TRUE(bitmap.isValid());
    ASSERT_EQ(BitmapCompressedMethodType::BI_RGB, bitmap.getCompressedMethodType());
    ASSERT_TRUE(bitmap.isCompressedMethodSupported());

    AprgBitmap::ColorTable colors(bitmap.getColorTable());
    ASSERT_EQ(16, colors.size());
    EXPECT_EQ(colors[0], 0x00000000);
    EXPECT_EQ(colors[7], 0x00808080);
    EXPECT_EQ(colors[8], 0x00C0C0C0);
    EXPECT_EQ(colors[15], 0x00FFFFFF);

    bitmap.addPositionToLoadInMemory(AprgBitmap::XY(99, 97));
    bitmap.addPositionToLoadInMemory(AprgBitmap::XY(101, 99));
    bitmap.loadPixels();

    EXPECT_EQ(AprgBitmap::XY(98, 97), bitmap.getPositionOfTopLeftCornerInMemory());
    EXPECT_EQ(AprgBitmap::XY(101, 99), bitmap.getPositionOfBottomRightCornerInMemory());

    AprgBitmap::Pixels pixels(bitmap.getPixelsInMemory());
    unsigned char* reader = reinterpret_cast<unsigned char*>(pixels.getBufferPointer());
    ASSERT_EQ(6, pixels.getSize());
    EXPECT_EQ(0x57, reader[0]);
    EXPECT_EQ(0x78, reader[1]);
    EXPECT_EQ(0x87, reader[2]);
    EXPECT_EQ(0x77, reader[3]);
    EXPECT_EQ(0x8F, reader[4]);
    EXPECT_EQ(0xF8, reader[5]);

    EXPECT_EQ(0x07, bitmap.getPixelAtPositionRestrictedToSnippet(AprgBitmap::XY(99, 97)));
    EXPECT_EQ(0x07, bitmap.getPixelAtPositionRestrictedToSnippet(AprgBitmap::XY(100, 97)));
    EXPECT_EQ(0x08, bitmap.getPixelAtPositionRestrictedToSnippet(AprgBitmap::XY(101, 97)));
    EXPECT_EQ(0x07, bitmap.getPixelAtPositionRestrictedToSnippet(AprgBitmap::XY(99, 98)));
    EXPECT_EQ(0x07, bitmap.getPixelAtPositionRestrictedToSnippet(AprgBitmap::XY(100, 98)));
    EXPECT_EQ(0x07, bitmap.getPixelAtPositionRestrictedToSnippet(AprgBitmap::XY(101, 98)));
    EXPECT_EQ(0x0F, bitmap.getPixelAtPositionRestrictedToSnippet(AprgBitmap::XY(99, 99)));
    EXPECT_EQ(0x0F, bitmap.getPixelAtPositionRestrictedToSnippet(AprgBitmap::XY(100, 99)));
    EXPECT_EQ(0x08, bitmap.getPixelAtPositionRestrictedToSnippet(AprgBitmap::XY(101, 99)));

    EXPECT_EQ(0x08, bitmap.getPixelAtPositionWithAutomaticChangesToSnippet(AprgBitmap::XY(152, 101)));
    EXPECT_EQ(0x07, bitmap.getPixelAtPositionWithAutomaticChangesToSnippet(AprgBitmap::XY(17, 114)));
    EXPECT_EQ(0x07, bitmap.getPixelAtPositionWithAutomaticChangesToSnippet(AprgBitmap::XY(113, 11)));

    EXPECT_EQ(0x00808080, bitmap.getColorUsingPixelValue(0x07));
    EXPECT_EQ(0x00C0C0C0, bitmap.getColorUsingPixelValue(0x08));
}

TEST(BitmapTest, TestFor256ColorBitmap)
{
    AprgBitmap bitmap(APRG_BITMAP_256COLOR_TEST_FILE);
    ASSERT_TRUE(bitmap.isValid());
    ASSERT_EQ(BitmapCompressedMethodType::BI_RGB, bitmap.getCompressedMethodType());
    ASSERT_TRUE(bitmap.isCompressedMethodSupported());

    AprgBitmap::ColorTable colors(bitmap.getColorTable());
    ASSERT_EQ(256, colors.size());
    EXPECT_EQ(colors[0x00], 0x00000000);
    EXPECT_EQ(colors[0x53], 0x00604040);
    EXPECT_EQ(colors[0xF5], 0x00A0C0C0);
    EXPECT_EQ(colors[0xFF], 0x00FFFFFF);

    bitmap.addPositionToLoadInMemory(AprgBitmap::XY(99, 97));
    bitmap.addPositionToLoadInMemory(AprgBitmap::XY(101, 99));
    bitmap.loadPixels();

    EXPECT_EQ(AprgBitmap::XY(99, 97), bitmap.getPositionOfTopLeftCornerInMemory());
    EXPECT_EQ(AprgBitmap::XY(101, 99), bitmap.getPositionOfBottomRightCornerInMemory());

    AprgBitmap::Pixels pixels(bitmap.getPixelsInMemory());
    unsigned char* reader = reinterpret_cast<unsigned char*>(pixels.getBufferPointer());
    ASSERT_EQ(9, pixels.getSize());
    EXPECT_EQ(0x53, reader[0]);
    EXPECT_EQ(0xA4, reader[1]);
    EXPECT_EQ(0xF5, reader[2]);
    EXPECT_EQ(0xA5, reader[3]);
    EXPECT_EQ(0x9B, reader[4]);
    EXPECT_EQ(0xA4, reader[5]);
    EXPECT_EQ(0xF6, reader[6]);
    EXPECT_EQ(0xF6, reader[7]);
    EXPECT_EQ(0x07, reader[8]);

    EXPECT_EQ(0x53, bitmap.getPixelAtPositionRestrictedToSnippet(AprgBitmap::XY(99, 97)));
    EXPECT_EQ(0xA4, bitmap.getPixelAtPositionRestrictedToSnippet(AprgBitmap::XY(100, 97)));
    EXPECT_EQ(0xF5, bitmap.getPixelAtPositionRestrictedToSnippet(AprgBitmap::XY(101, 97)));
    EXPECT_EQ(0xA5, bitmap.getPixelAtPositionRestrictedToSnippet(AprgBitmap::XY(99, 98)));
    EXPECT_EQ(0x9B, bitmap.getPixelAtPositionRestrictedToSnippet(AprgBitmap::XY(100, 98)));
    EXPECT_EQ(0xA4, bitmap.getPixelAtPositionRestrictedToSnippet(AprgBitmap::XY(101, 98)));
    EXPECT_EQ(0xF6, bitmap.getPixelAtPositionRestrictedToSnippet(AprgBitmap::XY(99, 99)));
    EXPECT_EQ(0xF6, bitmap.getPixelAtPositionRestrictedToSnippet(AprgBitmap::XY(100, 99)));
    EXPECT_EQ(0x07, bitmap.getPixelAtPositionRestrictedToSnippet(AprgBitmap::XY(101, 99)));

    EXPECT_EQ(0xF5, bitmap.getPixelAtPositionWithAutomaticChangesToSnippet(AprgBitmap::XY(152, 101)));
    EXPECT_EQ(0x9D, bitmap.getPixelAtPositionWithAutomaticChangesToSnippet(AprgBitmap::XY(17, 114)));
    EXPECT_EQ(0xF7, bitmap.getPixelAtPositionWithAutomaticChangesToSnippet(AprgBitmap::XY(113, 11)));

    EXPECT_EQ(0x00604040, bitmap.getColorUsingPixelValue(0x53));
    EXPECT_EQ(0x00A0C0C0, bitmap.getColorUsingPixelValue(0xF5));
}

