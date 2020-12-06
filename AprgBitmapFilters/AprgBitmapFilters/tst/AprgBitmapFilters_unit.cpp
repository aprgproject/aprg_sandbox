#include <AprgBitmapFilters.hpp>

#include <PathHandlers/AlbaLocalPathHandler.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

#define APRG_BITMAP_FILTERS_SAMPLE_BITMAP APRG_DIR R"(AprgBitmapFilters\AprgBitmapFilters\tst\Bitmaps\sample.bmp)"
#define APRG_BITMAP_FILTERS_OUTPUT_BITMAP APRG_DIR R"(AprgBitmapFilters\AprgBitmapFilters\tst\Bitmaps\output.bmp)"

TEST(BitmapFilterTest, BitmapFilterFindPen)
{
    AlbaLocalPathHandler sampleFile(APRG_BITMAP_FILTERS_SAMPLE_BITMAP);
    AlbaLocalPathHandler outputFile(APRG_BITMAP_FILTERS_OUTPUT_BITMAP);
    outputFile.deleteFile();
    sampleFile.copyToNewFile(outputFile.getFullPath());

    AprgBitmapFilters bitmapFilter(outputFile.getFullPath());
    bitmapFilter.findPenPixel(3);
    bitmapFilter.saveNotPenPixelsToCanvas();
    bitmapFilter.saveCanvasToBitmapFile();
    outputFile.copyToNewFile(outputFile.getDirectory()+"BitmapNotPenPixels.bmp");

    bitmapFilter.clearCanvas();
    bitmapFilter.setPenPixelsToCanvas();
    bitmapFilter.saveCanvasToBitmapFile();
    outputFile.copyToNewFile(outputFile.getDirectory()+"BitmapPenPixels.bmp");
}
