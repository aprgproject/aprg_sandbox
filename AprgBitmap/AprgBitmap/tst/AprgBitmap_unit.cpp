#include <AprgBitmap.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

#define APRG_BITMAP_MONOCHROME_TEST_FILE APRG_DIR R"(AprgBitmap\AprgBitmap\tst\Bitmaps\Monochrome.bmp)"

TEST(SampleTest, MonochromeTest)
{
    AprgBitmap bitmap(APRG_BITMAP_MONOCHROME_TEST_FILE);
    EXPECT_TRUE(bitmap.isValid());
    EXPECT_TRUE(bitmap.isHeaderValid());
    EXPECT_TRUE(bitmap.isNumberOfColorPlanesValid());
    EXPECT_TRUE(bitmap.isNumberOfBitsPerPixelValid());
}
