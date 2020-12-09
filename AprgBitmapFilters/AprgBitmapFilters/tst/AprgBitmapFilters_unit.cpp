#include <AprgBitmapFilters.hpp>

#include <PathHandlers/AlbaLocalPathHandler.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

#define APRG_BITMAP_FILTERS_BITMAP_DIRECTORY APRG_DIR R"(AprgBitmapFilters\AprgBitmapFilters\tst\Bitmaps\)"

TEST(BitmapFilterTest, DISABLED_FindPenAndNonPen)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+"sample.bmp");
    AlbaLocalPathHandler temporaryFile(bitmapDirectory.getDirectory()+"temporary.bmp");
    temporaryFile.deleteFile();
    sampleFile.copyToNewFile(temporaryFile.getFullPath());

    AprgBitmapFilters bitmapFilter(temporaryFile.getFullPath());
    bitmapFilter.findPenPixel(3, 0x30);
    bitmapFilter.saveBlurredNonPenPixelsToCanvas(5, 0x40);
    bitmapFilter.saveCanvasToBitmapFile();
    temporaryFile.copyToNewFile(temporaryFile.getDirectory()+"BitmapNonPenPixels.bmp");

    bitmapFilter.clearCanvas();
    bitmapFilter.setPenPixelsToCanvas();
    bitmapFilter.saveCanvasToBitmapFile();
    temporaryFile.copyToNewFile(temporaryFile.getDirectory()+"BitmapPenPixels.bmp");
}

TEST(BitmapFilterTest, FillNonPenGaps)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+"BitmapNonPenPixels.bmp");
    AlbaLocalPathHandler temporaryFile(bitmapDirectory.getDirectory()+"temporary.bmp");
    temporaryFile.deleteFile();
    sampleFile.copyToNewFile(temporaryFile.getFullPath());

    AprgBitmapFilters bitmapFilter(temporaryFile.getFullPath());
    bitmapFilter.saveFilledGapsUsingBlurToCanvas(2);
    bitmapFilter.saveCanvasToBitmapFile();
    temporaryFile.copyToNewFile(temporaryFile.getDirectory()+"BitmapNonPenPixelsFilled.bmp");
}