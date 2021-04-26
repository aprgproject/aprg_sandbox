#include <AprgBitmapFilters.hpp>

#include <PathHandlers/AlbaLocalPathHandler.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

#define APRG_BITMAP_FILTERS_BITMAP_DIRECTORY APRG_DIR R"(AprgBitmapFilters\AprgBitmapFilters\tst\Bitmaps\)"

TEST(BitmapFilterTest, DISABLED_CclTestOneComponentAtATime)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+"CclTest.bmp");
    AlbaLocalPathHandler temporaryFile(bitmapDirectory.getDirectory()+"temporary.bmp");
    temporaryFile.deleteFile();
    sampleFile.copyToNewFile(temporaryFile.getFullPath());

    AprgBitmapFilters bitmapFilter(temporaryFile.getFullPath());
    bitmapFilter.getConnectedComponentsOneComponentAtATime();
    bitmapFilter.setColoredPixelsForDifferentLabelsIntoOutputCanvas();
    bitmapFilter.saveOutputCanvasIntoDifferentFile("CclTestOutput.bmp");
}

TEST(BitmapFilterTest, DISABLED_CclTestTwoPass)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+"CclTest.bmp");
    AlbaLocalPathHandler temporaryFile(bitmapDirectory.getDirectory()+"temporary.bmp");
    temporaryFile.deleteFile();
    sampleFile.copyToNewFile(temporaryFile.getFullPath());

    AprgBitmapFilters bitmapFilter(temporaryFile.getFullPath());
    bitmapFilter.getConnectedComponentsTwoPass();
    bitmapFilter.setColoredPixelsForDifferentLabelsIntoOutputCanvas();
    bitmapFilter.saveOutputCanvasIntoDifferentFile("CclTestOutput.bmp");
}

TEST(BitmapFilterTest, DISABLED_FindPenAndNonPen)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+"sample.bmp");
    AlbaLocalPathHandler temporaryFile(bitmapDirectory.getDirectory()+"temporary.bmp");
    temporaryFile.deleteFile();
    sampleFile.copyToNewFile(temporaryFile.getFullPath());

    AprgBitmapFilters bitmapFilter(temporaryFile.getFullPath());
    bitmapFilter.determinePenPixels(2, 0x08);
    bitmapFilter.setNonPenPixelsToOutputCanvas();
    //bitmapFilter.setBlurredNonPenPixelsToOutputCanvas(3, 0x40); //no blur
    bitmapFilter.saveOutputCanvasIntoDifferentFile("BitmapNonPenPixels.bmp");

    bitmapFilter.clearOutputCanvas();
    bitmapFilter.setPenPixelsToOutputCanvas();
    bitmapFilter.saveOutputCanvasIntoDifferentFile("BitmapPenPixels.bmp");
}

TEST(BitmapFilterTest, DISABLED_FillNonPenGaps)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+"BitmapNonPenPixels.bmp");
    AlbaLocalPathHandler temporaryFile(bitmapDirectory.getDirectory()+"temporary.bmp");
    temporaryFile.deleteFile();
    sampleFile.copyToNewFile(temporaryFile.getFullPath());

    AprgBitmapFilters bitmapFilter(temporaryFile.getFullPath());
    bitmapFilter.setBlankGapsUsingBlurToOutputCanvas(2);
    bitmapFilter.saveOutputCanvasIntoDifferentFile("BitmapNonPenPixelsFilled.bmp");
}

TEST(BitmapFilterTest, DISABLED_FindPenAndNonPenAndFillNonPenGaps)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+"sample.bmp");
    AlbaLocalPathHandler temporaryFile(bitmapDirectory.getDirectory()+"temporary.bmp");
    temporaryFile.deleteFile();
    sampleFile.copyToNewFile(temporaryFile.getFullPath());

    AprgBitmapFilters bitmapFilter(temporaryFile.getFullPath());
    bitmapFilter.determinePenPixels(3, 0x20);
    bitmapFilter.setPenPixelsToOutputCanvas();
    bitmapFilter.saveOutputCanvasIntoDifferentFile("BitmapPenPixels.bmp");

    bitmapFilter.clearOutputCanvas();
    bitmapFilter.setBlurredNonPenPixelsToOutputCanvas(3, 0x40);
    bitmapFilter.saveOutputCanvasIntoDifferentFile("BitmapNonPenPixels.bmp");

    bitmapFilter.clearOutputCanvas();
    bitmapFilter.setBlankGapsUsingBlurToOutputCanvas(2);
    bitmapFilter.saveOutputCanvasIntoDifferentFile("BitmapNonPenPixelsFilled.bmp");
}

TEST(BitmapFilterTest, DISABLED_SpecialPurpose)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+"sample.bmp");
    AlbaLocalPathHandler temporaryFile(bitmapDirectory.getDirectory()+"temporary.bmp");
    temporaryFile.deleteFile();
    sampleFile.copyToNewFile(temporaryFile.getFullPath());

    AprgBitmapFilters bitmapFilter(temporaryFile.getFullPath());
    bitmapFilter.determinePenPixels(3, 0x08);
    bitmapFilter.setPenPixelsToOutputCanvas();
    bitmapFilter.saveOutputCanvasIntoDifferentFile("BitmapPenPixels.bmp");

    bitmapFilter.clearOutputCanvas();
    bitmapFilter.setBlurredNonPenPixelsToOutputCanvas(5, 0x40);
    bitmapFilter.saveOutputCanvasIntoDifferentFile("BitmapNonPenPixels.bmp");

    bitmapFilter.copyOutputCanvasToInputCanvas();
    bitmapFilter.setBlankGapsUsingBlurToOutputCanvas(2);
    bitmapFilter.saveOutputCanvasIntoDifferentFile("BitmapNonPenPixelsFilled.bmp");

}
