#include <AprgBitmap.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

#define APRG_BITMAP_MONOCHROME_TEST_FILE APRG_DIR R"(AprgBitmap\AprgBitmap\tst\Bitmaps\Monochrome.bmp)"

TEST(SampleTest, MonochromeTest)
{
    AprgBitmap bitmap(APRG_BITMAP_MONOCHROME_TEST_FILE);
    EXPECT_TRUE(bitmap.isValid());
    EXPECT_EQ(BitmapCompressedMethodType::BI_RGB, bitmap.getCompressedMethodType());
    EXPECT_TRUE(bitmap.isCompressedMethodSupported());

}