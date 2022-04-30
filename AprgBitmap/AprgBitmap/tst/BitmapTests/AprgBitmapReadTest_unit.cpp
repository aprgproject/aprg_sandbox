#include <Bitmap/Bitmap.hpp>

#include <gtest/gtest.h>

#include <iostream>

using namespace std;

#define APRG_BITMAP_MONOCHROME_TEST_FILE APRG_DIR R"(\AprgBitmap\FilesForTests\SampleBitmaps\Monochrome.bmp)"
#define APRG_BITMAP_16_COLOR_TEST_FILE APRG_DIR R"(\AprgBitmap\FilesForTests\SampleBitmaps\16ColorBitmap.bmp)"
#define APRG_BITMAP_256_COLOR_TEST_FILE APRG_DIR R"(\AprgBitmap\FilesForTests\SampleBitmaps\256ColorBitmap.bmp)"
#define APRG_BITMAP_24_BIT_TEST_FILE APRG_DIR R"(\AprgBitmap\FilesForTests\SampleBitmaps\24BitBitmap.bmp)"
#define APRG_BITMAP_32_BIT_TEST_FILE APRG_DIR R"(\AprgBitmap\FilesForTests\SampleBitmaps\32BitBitmap.bmp)"

namespace alba
{

namespace AprgBitmap
{

TEST(BitmapReadTest, TestForMonochromeBitmap)
{
    Bitmap bitmap(APRG_BITMAP_MONOCHROME_TEST_FILE);
    ASSERT_TRUE(bitmap.getConfiguration().isValid());
    ASSERT_EQ(CompressedMethodType::BI_RGB, bitmap.getConfiguration().getCompressedMethodType());
    ASSERT_TRUE(bitmap.getConfiguration().isCompressedMethodSupported());

    Colors colors(bitmap.getConfiguration().getColorTable());
    ASSERT_EQ(2U, colors.size());
    EXPECT_EQ(0x00000000U, colors[0]);
    EXPECT_EQ(0x00FFFFFFU, colors[1]);
    EXPECT_EQ(0x00000000U, bitmap.getConfiguration().getColorUsingPixelValue(0));
    EXPECT_EQ(0x00FFFFFFU, bitmap.getConfiguration().getColorUsingPixelValue(1));

    BitmapSnippet snippet(bitmap.getSnippetReadFromFile(BitmapXY(99, 97), BitmapXY(101, 99)));
    EXPECT_EQ(BitmapXY(96, 97), snippet.getTopLeftCorner());
    EXPECT_EQ(BitmapXY(103, 99), snippet.getBottomRightCorner());

    PixelData pixels(snippet.getPixelDataReference());
    unsigned char* reader = reinterpret_cast<unsigned char*>(pixels.getBufferPointer());
    ASSERT_EQ(3U, pixels.getSize());
    EXPECT_EQ(0x8F, reader[0]);
    EXPECT_EQ(0xF3, reader[1]);
    EXPECT_EQ(0xFF, reader[2]);

    EXPECT_EQ(0x00U, snippet.getPixelAt(BitmapXY(99, 97)));
    EXPECT_EQ(0x01U, snippet.getPixelAt(BitmapXY(100, 97)));
    EXPECT_EQ(0x01U, snippet.getPixelAt(BitmapXY(101, 97)));
    EXPECT_EQ(0x01U, snippet.getPixelAt(BitmapXY(99, 98)));
    EXPECT_EQ(0x00U, snippet.getPixelAt(BitmapXY(100, 98)));
    EXPECT_EQ(0x00U, snippet.getPixelAt(BitmapXY(101, 98)));
    EXPECT_EQ(0x01U, snippet.getPixelAt(BitmapXY(99, 99)));
    EXPECT_EQ(0x01U, snippet.getPixelAt(BitmapXY(100, 99)));
    EXPECT_EQ(0x01U, snippet.getPixelAt(BitmapXY(101, 99)));

    BitmapSnippet snippet1(bitmap.getSnippetReadFromFileWithNumberOfBytesToRead(BitmapXY(0, 0), 3));
    ASSERT_EQ(3U, snippet1.getPixelDataSize());
    EXPECT_EQ(0x01U, snippet1.getPixelAt(BitmapXY(0, 0)));
    EXPECT_EQ(0xFFFFFFU, snippet1.getColorAt(BitmapXY(0, 0)));
    EXPECT_EQ(BitmapXY(0, 0), snippet1.getTopLeftCorner());
    EXPECT_EQ(BitmapXY(7, 2), snippet1.getBottomRightCorner());

    BitmapSnippet snippet2(bitmap.getSnippetReadFromFileWithNumberOfBytesToRead(BitmapXY(152, 101), 3));
    ASSERT_EQ(3U, snippet2.getPixelDataSize());
    EXPECT_EQ(0x01U, snippet2.getPixelAt(BitmapXY(152, 101)));
    EXPECT_EQ(0xFFFFFFU, snippet2.getColorAt(BitmapXY(152, 101)));
    EXPECT_EQ(BitmapXY(152, 100), snippet2.getTopLeftCorner());
    EXPECT_EQ(BitmapXY(159, 102), snippet2.getBottomRightCorner());

    BitmapSnippet snippet3(bitmap.getSnippetReadFromFileWithNumberOfBytesToRead(BitmapXY(17, 114), 3));
    ASSERT_EQ(3U, snippet3.getPixelDataSize());
    EXPECT_EQ(0x01U, snippet3.getPixelAt(BitmapXY(17, 114)));
    EXPECT_EQ(0xFFFFFFU, snippet3.getColorAt(BitmapXY(17, 114)));
    EXPECT_EQ(BitmapXY(16, 113), snippet3.getTopLeftCorner());
    EXPECT_EQ(BitmapXY(23, 115), snippet3.getBottomRightCorner());

    BitmapSnippet snippet4(bitmap.getSnippetReadFromFileWithNumberOfBytesToRead(BitmapXY(174, 173), 3));
    ASSERT_EQ(3U, snippet4.getPixelDataSize());
    EXPECT_EQ(0x01U, snippet4.getPixelAt(BitmapXY(174, 173)));
    EXPECT_EQ(0xFFFFFFU, snippet4.getColorAt(BitmapXY(174, 173)));
    EXPECT_EQ(BitmapXY(168, 171), snippet4.getTopLeftCorner());
    EXPECT_EQ(BitmapXY(174, 173), snippet4.getBottomRightCorner());

    BitmapSnippet snippet5(bitmap.getSnippetReadFromFileWithNumberOfBytesToRead(BitmapXY(180, 180), 3));
    ASSERT_EQ(0U, snippet5.getPixelDataSize());
    EXPECT_EQ(0x0U, snippet5.getColorAt(BitmapXY(180, 180)));
}

TEST(BitmapReadTest, TestFor16ColorBitmap)
{
    Bitmap bitmap(APRG_BITMAP_16_COLOR_TEST_FILE);
    ASSERT_TRUE(bitmap.getConfiguration().isValid());
    ASSERT_EQ(CompressedMethodType::BI_RGB, bitmap.getConfiguration().getCompressedMethodType());
    ASSERT_TRUE(bitmap.getConfiguration().isCompressedMethodSupported());

    Colors colors(bitmap.getConfiguration().getColorTable());
    ASSERT_EQ(16U, colors.size());
    EXPECT_EQ(0x00000000U, colors[0]);
    EXPECT_EQ(0x00808080U, colors[7]);
    EXPECT_EQ(0x00C0C0C0U, colors[8]);
    EXPECT_EQ(0x00FFFFFFU, colors[15]);
    EXPECT_EQ(0x00808080U, bitmap.getConfiguration().getColorUsingPixelValue(0x07));
    EXPECT_EQ(0x00C0C0C0U, bitmap.getConfiguration().getColorUsingPixelValue(0x08));

    BitmapSnippet snippet(bitmap.getSnippetReadFromFile(BitmapXY(99, 97), BitmapXY(101, 99)));
    EXPECT_EQ(BitmapXY(98, 97), snippet.getTopLeftCorner());
    EXPECT_EQ(BitmapXY(101, 99), snippet.getBottomRightCorner());

    PixelData pixels(snippet.getPixelDataReference());
    unsigned char* reader = reinterpret_cast<unsigned char*>(pixels.getBufferPointer());
    ASSERT_EQ(6U, pixels.getSize());
    EXPECT_EQ(0x57, reader[0]);
    EXPECT_EQ(0x78, reader[1]);
    EXPECT_EQ(0x87, reader[2]);
    EXPECT_EQ(0x77, reader[3]);
    EXPECT_EQ(0x8F, reader[4]);
    EXPECT_EQ(0xF8, reader[5]);

    EXPECT_EQ(0x07U, snippet.getPixelAt(BitmapXY(99, 97)));
    EXPECT_EQ(0x07U, snippet.getPixelAt(BitmapXY(100, 97)));
    EXPECT_EQ(0x08U, snippet.getPixelAt(BitmapXY(101, 97)));
    EXPECT_EQ(0x07U, snippet.getPixelAt(BitmapXY(99, 98)));
    EXPECT_EQ(0x07U, snippet.getPixelAt(BitmapXY(100, 98)));
    EXPECT_EQ(0x07U, snippet.getPixelAt(BitmapXY(101, 98)));
    EXPECT_EQ(0x0FU, snippet.getPixelAt(BitmapXY(99, 99)));
    EXPECT_EQ(0x0FU, snippet.getPixelAt(BitmapXY(100, 99)));
    EXPECT_EQ(0x08U, snippet.getPixelAt(BitmapXY(101, 99)));

    BitmapSnippet snippet1(bitmap.getSnippetReadFromFileWithNumberOfBytesToRead(BitmapXY(0, 0), 6));
    ASSERT_EQ(6U, snippet1.getPixelDataSize());
    EXPECT_EQ(0x0FU, snippet1.getPixelAt(BitmapXY(0, 0)));
    EXPECT_EQ(0xFFFFFFU, snippet1.getColorAt(BitmapXY(0, 0)));
    EXPECT_EQ(BitmapXY(0, 0), snippet1.getTopLeftCorner());
    EXPECT_EQ(BitmapXY(1, 5), snippet1.getBottomRightCorner());

    BitmapSnippet snippet2(bitmap.getSnippetReadFromFileWithNumberOfBytesToRead(BitmapXY(152, 101), 6));
    ASSERT_EQ(6U, snippet2.getPixelDataSize());
    EXPECT_EQ(0x08U, snippet2.getPixelAt(BitmapXY(152, 101)));
    EXPECT_EQ(0xC0C0C0U, snippet2.getColorAt(BitmapXY(152, 101)));
    EXPECT_EQ(BitmapXY(150, 100), snippet2.getTopLeftCorner());
    EXPECT_EQ(BitmapXY(153, 102), snippet2.getBottomRightCorner());

    BitmapSnippet snippet3(bitmap.getSnippetReadFromFileWithNumberOfBytesToRead(BitmapXY(17, 114), 6));
    ASSERT_EQ(6U, snippet3.getPixelDataSize());
    EXPECT_EQ(0x07U, snippet3.getPixelAt(BitmapXY(17, 114)));
    EXPECT_EQ(0x808080U, snippet3.getColorAt(BitmapXY(17, 114)));
    EXPECT_EQ(BitmapXY(16, 113), snippet3.getTopLeftCorner());
    EXPECT_EQ(BitmapXY(19, 115), snippet3.getBottomRightCorner());

    BitmapSnippet snippet4(bitmap.getSnippetReadFromFileWithNumberOfBytesToRead(BitmapXY(174, 173), 6));
    ASSERT_EQ(6U, snippet4.getPixelDataSize());
    EXPECT_EQ(0x0FU, snippet4.getPixelAt(BitmapXY(174, 173)));
    EXPECT_EQ(0xFFFFFFU, snippet4.getColorAt(BitmapXY(174, 173)));
    EXPECT_EQ(BitmapXY(172, 171), snippet4.getTopLeftCorner());
    EXPECT_EQ(BitmapXY(174, 173), snippet4.getBottomRightCorner());

    BitmapSnippet snippet5(bitmap.getSnippetReadFromFileWithNumberOfBytesToRead(BitmapXY(180, 180), 3));
    ASSERT_EQ(0U, snippet5.getPixelDataSize());
    EXPECT_EQ(0x0U, snippet5.getColorAt(BitmapXY(180, 180)));
}


TEST(BitmapReadTest, TestFor256ColorBitmap)
{
    Bitmap bitmap(APRG_BITMAP_256_COLOR_TEST_FILE);
    ASSERT_TRUE(bitmap.getConfiguration().isValid());
    ASSERT_EQ(CompressedMethodType::BI_RGB, bitmap.getConfiguration().getCompressedMethodType());
    ASSERT_TRUE(bitmap.getConfiguration().isCompressedMethodSupported());

    Colors colors(bitmap.getConfiguration().getColorTable());
    ASSERT_EQ(256U, colors.size());
    EXPECT_EQ(0x00000000U, colors[0x00]);
    EXPECT_EQ(0x00604040U, colors[0x53]);
    EXPECT_EQ(0x00A0C0C0U, colors[0xF5]);
    EXPECT_EQ(0x00FFFFFFU, colors[0xFF]);
    EXPECT_EQ(0x00604040U, bitmap.getConfiguration().getColorUsingPixelValue(0x53));
    EXPECT_EQ(0x00A0C0C0U, bitmap.getConfiguration().getColorUsingPixelValue(0xF5));

    BitmapSnippet snippet(bitmap.getSnippetReadFromFile(BitmapXY(99, 97), BitmapXY(101, 99)));
    EXPECT_EQ(BitmapXY(99, 97), snippet.getTopLeftCorner());
    EXPECT_EQ(BitmapXY(101, 99), snippet.getBottomRightCorner());

    PixelData pixels(snippet.getPixelDataReference());
    unsigned char* reader = reinterpret_cast<unsigned char*>(pixels.getBufferPointer());
    ASSERT_EQ(9U, pixels.getSize());
    EXPECT_EQ(0x53, reader[0]);
    EXPECT_EQ(0xA4, reader[1]);
    EXPECT_EQ(0xF5, reader[2]);
    EXPECT_EQ(0xA5, reader[3]);
    EXPECT_EQ(0x9B, reader[4]);
    EXPECT_EQ(0xA4, reader[5]);
    EXPECT_EQ(0xF6, reader[6]);
    EXPECT_EQ(0xF6, reader[7]);
    EXPECT_EQ(0x07, reader[8]);

    EXPECT_EQ(0x53U, snippet.getPixelAt(BitmapXY(99, 97)));
    EXPECT_EQ(0xA4U, snippet.getPixelAt(BitmapXY(100, 97)));
    EXPECT_EQ(0xF5U, snippet.getPixelAt(BitmapXY(101, 97)));
    EXPECT_EQ(0xA5U, snippet.getPixelAt(BitmapXY(99, 98)));
    EXPECT_EQ(0x9BU, snippet.getPixelAt(BitmapXY(100, 98)));
    EXPECT_EQ(0xA4U, snippet.getPixelAt(BitmapXY(101, 98)));
    EXPECT_EQ(0xF6U, snippet.getPixelAt(BitmapXY(99, 99)));
    EXPECT_EQ(0xF6U, snippet.getPixelAt(BitmapXY(100, 99)));
    EXPECT_EQ(0x07U, snippet.getPixelAt(BitmapXY(101, 99)));

    BitmapSnippet snippet1(bitmap.getSnippetReadFromFileWithNumberOfBytesToRead(BitmapXY(0, 0), 9));
    ASSERT_EQ(8U, snippet1.getPixelDataSize());
    EXPECT_EQ(0xFFU, snippet1.getPixelAt(BitmapXY(0, 0)));
    EXPECT_EQ(0xFFFFFFU, snippet1.getColorAt(BitmapXY(0, 0)));
    EXPECT_EQ(BitmapXY(0, 0), snippet1.getTopLeftCorner());
    EXPECT_EQ(BitmapXY(1, 3), snippet1.getBottomRightCorner());

    BitmapSnippet snippet2(bitmap.getSnippetReadFromFileWithNumberOfBytesToRead(BitmapXY(152, 101), 9));
    ASSERT_EQ(9U, snippet2.getPixelDataSize());
    EXPECT_EQ(0xF5U, snippet2.getPixelAt(BitmapXY(152, 101)));
    EXPECT_EQ(0xA0C0C0U, snippet2.getColorAt(BitmapXY(152, 101)));
    EXPECT_EQ(BitmapXY(151, 100), snippet2.getTopLeftCorner());
    EXPECT_EQ(BitmapXY(153, 102), snippet2.getBottomRightCorner());

    BitmapSnippet snippet3(bitmap.getSnippetReadFromFileWithNumberOfBytesToRead(BitmapXY(17, 114), 9));
    ASSERT_EQ(9U, snippet3.getPixelDataSize());
    EXPECT_EQ(0x9DU, snippet3.getPixelAt(BitmapXY(17, 114)));
    EXPECT_EQ(0xA06080U, snippet3.getColorAt(BitmapXY(17, 114)));
    EXPECT_EQ(BitmapXY(16, 113), snippet3.getTopLeftCorner());
    EXPECT_EQ(BitmapXY(18, 115), snippet3.getBottomRightCorner());

    BitmapSnippet snippet4(bitmap.getSnippetReadFromFileWithNumberOfBytesToRead(BitmapXY(174, 173), 9));
    ASSERT_EQ(8U, snippet4.getPixelDataSize());
    EXPECT_EQ(0xFFU, snippet4.getPixelAt(BitmapXY(174, 173)));
    EXPECT_EQ(0xFFFFFFU, snippet4.getColorAt(BitmapXY(174, 173)));
    EXPECT_EQ(BitmapXY(173, 170), snippet4.getTopLeftCorner());
    EXPECT_EQ(BitmapXY(174, 173), snippet4.getBottomRightCorner());

    BitmapSnippet snippet5(bitmap.getSnippetReadFromFileWithNumberOfBytesToRead(BitmapXY(180, 180), 9));
    ASSERT_EQ(0U, snippet5.getPixelDataSize());
    EXPECT_EQ(0x0U, snippet5.getColorAt(BitmapXY(180, 180)));
}

TEST(BitmapReadTest, TestFor24BitBitmap)
{
    Bitmap bitmap(APRG_BITMAP_24_BIT_TEST_FILE);
    ASSERT_TRUE(bitmap.getConfiguration().isValid());
    ASSERT_EQ(CompressedMethodType::BI_RGB, bitmap.getConfiguration().getCompressedMethodType());
    ASSERT_TRUE(bitmap.getConfiguration().isCompressedMethodSupported());

    Colors colors(bitmap.getConfiguration().getColorTable());
    ASSERT_EQ(0U, colors.size());
    EXPECT_EQ(0xA1BA0000U, bitmap.getConfiguration().getColorUsingPixelValue(0xA1BA0000));
    EXPECT_EQ(0xFFFFFFFFU, bitmap.getConfiguration().getColorUsingPixelValue(0xFFFFFFFF));

    BitmapSnippet snippet(bitmap.getSnippetReadFromFile(BitmapXY(99, 97), BitmapXY(101, 99)));
    EXPECT_EQ(BitmapXY(99, 97), snippet.getTopLeftCorner());
    EXPECT_EQ(BitmapXY(101, 99), snippet.getBottomRightCorner());

    PixelData pixels(snippet.getPixelDataReference());
    unsigned char* reader = reinterpret_cast<unsigned char*>(pixels.getBufferPointer());
    ASSERT_EQ(27U, pixels.getSize());
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

    EXPECT_EQ(0x564F5FU, snippet.getPixelAt(BitmapXY(99, 97)));
    EXPECT_EQ(0x828A94U, snippet.getPixelAt(BitmapXY(100, 97)));
    EXPECT_EQ(0xA2B7BAU, snippet.getPixelAt(BitmapXY(101, 97)));
    EXPECT_EQ(0x958C96U, snippet.getPixelAt(BitmapXY(99, 98)));
    EXPECT_EQ(0x685F6DU, snippet.getPixelAt(BitmapXY(100, 98)));
    EXPECT_EQ(0x737680U, snippet.getPixelAt(BitmapXY(101, 98)));
    EXPECT_EQ(0xE6E6E6U, snippet.getPixelAt(BitmapXY(99, 99)));
    EXPECT_EQ(0xE9E8E9U, snippet.getPixelAt(BitmapXY(100, 99)));
    EXPECT_EQ(0xC2BEC3U, snippet.getPixelAt(BitmapXY(101, 99)));

    BitmapSnippet snippet1(bitmap.getSnippetReadFromFileWithNumberOfBytesToRead(BitmapXY(0, 0), 27));
    ASSERT_EQ(24U, snippet1.getPixelDataSize());
    EXPECT_EQ(0xFFFFFFU, snippet1.getPixelAt(BitmapXY(0, 0)));
    EXPECT_EQ(0xFFFFFFU, snippet1.getColorAt(BitmapXY(0, 0)));
    EXPECT_EQ(BitmapXY(0, 0), snippet1.getTopLeftCorner());
    EXPECT_EQ(BitmapXY(1, 3), snippet1.getBottomRightCorner());

    BitmapSnippet snippet2(bitmap.getSnippetReadFromFileWithNumberOfBytesToRead(BitmapXY(152, 101), 27));
    ASSERT_EQ(27U, snippet2.getPixelDataSize());
    EXPECT_EQ(0xAFB3B5U, snippet2.getPixelAt(BitmapXY(152, 101)));
    EXPECT_EQ(0xAFB3B5U, snippet2.getColorAt(BitmapXY(152, 101)));
    EXPECT_EQ(BitmapXY(151, 100), snippet2.getTopLeftCorner());
    EXPECT_EQ(BitmapXY(153, 102), snippet2.getBottomRightCorner());

    BitmapSnippet snippet3(bitmap.getSnippetReadFromFileWithNumberOfBytesToRead(BitmapXY(17, 114), 27));
    ASSERT_EQ(27U, snippet3.getPixelDataSize());
    EXPECT_EQ(0x916E95U, snippet3.getPixelAt(BitmapXY(17, 114)));
    EXPECT_EQ(0x916E95U, snippet3.getColorAt(BitmapXY(17, 114)));
    EXPECT_EQ(BitmapXY(16, 113), snippet3.getTopLeftCorner());
    EXPECT_EQ(BitmapXY(18, 115), snippet3.getBottomRightCorner());

    BitmapSnippet snippet4(bitmap.getSnippetReadFromFileWithNumberOfBytesToRead(BitmapXY(174, 173), 27));
    ASSERT_EQ(24U, snippet4.getPixelDataSize());
    EXPECT_EQ(0xFFFFFFU, snippet4.getPixelAt(BitmapXY(174, 173)));
    EXPECT_EQ(0xFFFFFFU, snippet4.getColorAt(BitmapXY(174, 173)));
    EXPECT_EQ(BitmapXY(173, 170), snippet4.getTopLeftCorner());
    EXPECT_EQ(BitmapXY(174, 173), snippet4.getBottomRightCorner());

    BitmapSnippet snippet5(bitmap.getSnippetReadFromFileWithNumberOfBytesToRead(BitmapXY(180, 180), 27));
    ASSERT_EQ(0U, snippet5.getPixelDataSize());
    EXPECT_EQ(0x0U, snippet5.getColorAt(BitmapXY(180, 180)));
}

TEST(BitmapReadTest, TestFor32BitBitmap)
{
    Bitmap bitmap(APRG_BITMAP_32_BIT_TEST_FILE);
    ASSERT_TRUE(bitmap.getConfiguration().isValid());
    ASSERT_EQ(CompressedMethodType::BI_RGB, bitmap.getConfiguration().getCompressedMethodType());
    ASSERT_TRUE(bitmap.getConfiguration().isCompressedMethodSupported());

    Colors colors(bitmap.getConfiguration().getColorTable());
    ASSERT_EQ(0U, colors.size());
    EXPECT_EQ(0xA1BA0000U, bitmap.getConfiguration().getColorUsingPixelValue(0xA1BA0000));
    EXPECT_EQ(0xFFFFFFFFU, bitmap.getConfiguration().getColorUsingPixelValue(0xFFFFFFFF));

    BitmapSnippet snippet(bitmap.getSnippetReadFromFile(BitmapXY(49, 49), BitmapXY(51, 51)));
    EXPECT_EQ(BitmapXY(49, 49), snippet.getTopLeftCorner());
    EXPECT_EQ(BitmapXY(51, 51), snippet.getBottomRightCorner());

    PixelData pixels(snippet.getPixelDataReference());
    ASSERT_EQ(36U, pixels.getSize());
    EXPECT_EQ(0x00442E47U, snippet.getPixelAt(BitmapXY(49, 49)));
    EXPECT_EQ(0x00442E47U, snippet.getColorAt(BitmapXY(49, 49)));
}

TEST(BitmapReadTest, TestForMonochromeBitmapWithOutOfRangeValues)
{
    Bitmap bitmap(APRG_BITMAP_MONOCHROME_TEST_FILE);
    ASSERT_TRUE(bitmap.getConfiguration().isValid());
    ASSERT_EQ(CompressedMethodType::BI_RGB, bitmap.getConfiguration().getCompressedMethodType());
    ASSERT_TRUE(bitmap.getConfiguration().isCompressedMethodSupported());

    Colors colors(bitmap.getConfiguration().getColorTable());
    ASSERT_EQ(2U, colors.size());
    EXPECT_EQ(0x00000000U, colors[0]);
    EXPECT_EQ(0x00FFFFFFU, colors[1]);
    EXPECT_EQ(0x00000000U, bitmap.getConfiguration().getColorUsingPixelValue(0));
    EXPECT_EQ(0x00FFFFFFU, bitmap.getConfiguration().getColorUsingPixelValue(1));

    BitmapSnippet snippet(bitmap.getSnippetReadFromFileWithOutOfRangeCoordinates(-100, -100, 99999999, 99999999));
    EXPECT_EQ(BitmapXY(0, 0), snippet.getTopLeftCorner());
    EXPECT_EQ(BitmapXY(174, 173), snippet.getBottomRightCorner());

    EXPECT_EQ(0x00000000U, snippet.getPixelAt(BitmapXY(99999999, 99999999)));
}

TEST(BitmapReadTest, TestForFileThatDoesExist)
{
    Bitmap bitmap("FileThatDoesNotExist");
    BitmapSnippet snippet(bitmap.getSnippetReadFromFileWithOutOfRangeCoordinates(-100, -100, 99999999, 99999999));
    EXPECT_EQ(BitmapXY(0, 0), snippet.getTopLeftCorner());
    EXPECT_EQ(BitmapXY(0, 0), snippet.getBottomRightCorner());
}

TEST(BitmapReadTest, DISABLED_ExperimentTest)
{
    Bitmap bitmap(APRG_DIR R"(\AprgLocalUserAutomation\TestFiles\BitmapFromClipboard.bmp)");
    EXPECT_TRUE(bitmap.getConfiguration().isValid());    EXPECT_TRUE(bitmap.getConfiguration().isCompressedMethodSupported());
}

}
}
