#include <AprgBitmap.hpp>

#include <gtest/gtest.h>

#include <iostream>
#include <cmath>

using namespace alba;
using namespace std;

#define APRG_BITMAP_WRITE_TEST_FILE APRG_DIR R"(AprgBitmap\AprgBitmap\tst\Bitmaps\WriteTestFile.bmp)"

TEST(BitmapWriteTest, TestForWritingBitmap)
{
    AprgBitmap bitmap(APRG_BITMAP_WRITE_TEST_FILE);
    ASSERT_TRUE(bitmap.getConfiguration().isValid());
    ASSERT_EQ(CompressedMethodType::BI_RGB, bitmap.getConfiguration().getCompressedMethodType());
    ASSERT_TRUE(bitmap.getConfiguration().isCompressedMethodSupported());

    AprgBitmapSnippet snippet(bitmap.getSnippetReadFromFile(BitmapXY(50, 50), BitmapXY(150, 150)));

    for(unsigned i=50; i<=150; i++)
    {
        snippet.setPixelAt(BitmapXY(i, round((double)100+40*(sin((double)i/10)))), 0x00FF0000);
    }
    bitmap.setSnippetWriteToFile(snippet);
}


TEST(BitmapWriteTest, TestForWritingMissingBitmapFile)
{
    AprgBitmap bitmap("FileThatDoesNotExist");
    ASSERT_FALSE(bitmap.getConfiguration().isValid());

    AprgBitmapSnippet snippet(bitmap.getSnippetReadFromFile(BitmapXY(50, 50), BitmapXY(150, 150)));
    for(unsigned i=50; i<=150; i++)
    {
        snippet.setPixelAt(BitmapXY(i, round((double)100+40*(sin((double)i/10)))), 0x00FF0000);
    }
    bitmap.setSnippetWriteToFile(snippet);
}
