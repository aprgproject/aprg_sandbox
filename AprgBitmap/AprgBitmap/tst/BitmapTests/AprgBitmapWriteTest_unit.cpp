#include <Bitmap/Bitmap.hpp>

#include <gtest/gtest.h>

#include <cmath>

using namespace std;

#define APRG_BITMAP_WRITE_TEST_FILE APRG_DIR R"(\AprgBitmap\FilesForTests\SampleBitmaps\WriteTestFile.bmp)"

namespace alba {

namespace AprgBitmap {

TEST(BitmapWriteTest, TestForWritingBitmap) {
    Bitmap bitmap(APRG_BITMAP_WRITE_TEST_FILE);
    ASSERT_TRUE(bitmap.getConfiguration().isValid());
    ASSERT_EQ(CompressedMethodType::RGB, bitmap.getConfiguration().getCompressedMethodType());
    ASSERT_TRUE(bitmap.getConfiguration().isCompressedMethodSupported());

    BitmapSnippet snippet(bitmap.getSnippetReadFromFile(BitmapXY(50, 50), BitmapXY(150, 150)));

    for (unsigned i = 50; i <= 150; i++) {
        snippet.setPixelAt(BitmapXY(i, round((double)100 + 40 * (sin((double)i / 10)))), 0x00FF0000);
    }
    bitmap.setSnippetWriteToFile(snippet);
}

TEST(BitmapWriteTest, TestForWritingMissingBitmapFile) {
    Bitmap bitmap("FileThatDoesNotExist");
    ASSERT_FALSE(bitmap.getConfiguration().isValid());

    BitmapSnippet snippet(bitmap.getSnippetReadFromFile(BitmapXY(50, 50), BitmapXY(150, 150)));
    for (unsigned i = 50; i <= 150; i++) {
        snippet.setPixelAt(BitmapXY(i, round((double)100 + 40 * (sin((double)i / 10)))), 0x00FF0000);
    }
    bitmap.setSnippetWriteToFile(snippet);
}

}  // namespace AprgBitmap

}  // namespace alba
