#include <AprgBitmapFilters.hpp>

#include <PathHandlers/AlbaLocalPathHandler.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

#define APRG_BITMAP_FILTERS_BITMAP_DIRECTORY APRG_DIR R"(AprgBitmapFilters\AprgBitmapFilters\tst\Bitmaps\)"


TEST(BitmapFilterTest, DISABLED_AnimizeTest)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler inputDirectory(bitmapDirectory.getDirectory()+R"(AnimizeTests\input\)");
    ListOfPaths inputSubDirectories;
    ListOfPaths inputFiles;
    inputDirectory.findFilesAndDirectoriesOneDepth("*.*", inputFiles, inputSubDirectories);

    for(string const& inputFile : inputFiles)
    {
        AlbaLocalPathHandler inputFilePathHandler(inputFile);
        AlbaLocalPathHandler outputFilePathHandler(bitmapDirectory.getDirectory()+R"(AnimizeTests\output\Out_)"+inputFilePathHandler.getFile());
        AprgBitmapFilters bitmapFilter(inputFilePathHandler.getFullPath());

        bitmapFilter.drawToAnimeColorToOutputCanvas();
        bitmapFilter.copyOutputCanvasToInputCanvas();

        bitmapFilter.determinePenPixels(3, 0x08);
        bitmapFilter.determinePenCircles(0x06, 0.80);

        bitmapFilter.clearOutputCanvas();
        //bitmapFilter.drawPenPixelsToOutputCanvas(); //remove
        bitmapFilter.drawNonPenPixelsToOutputCanvas();
        bitmapFilter.drawBlankGapsUsingBlurInOutputCanvas(2);
        bitmapFilter.drawPenCirclesToOutputCanvas();

        bitmapFilter.saveOutputCanvasIntoFileWithFullFilePath(outputFilePathHandler.getFullPath());
    }
}

TEST(BitmapFilterTest, DISABLED_GatherAndSaveStatisticsWorks)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AprgBitmapFilters bitmapFilter(bitmapDirectory.getDirectory()+R"(NonAnimeBitmaps\GilmoreGirls.bmp)");
    bitmapFilter.gatherAndSaveColorDataAndStatistics();
}

TEST(BitmapFilterTest, DISABLED_ConvertToAnimeColorWorks)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AprgBitmapFilters bitmapFilter(bitmapDirectory.getDirectory()+R"(NonAnimeBitmaps\Foals.bmp)");
    bitmapFilter.drawToAnimeColorToOutputCanvas();
    bitmapFilter.saveOutputCanvasIntoFileInTheSameDirectory("AnimeOutput.bmp");
}

TEST(BitmapFilterTest, DISABLED_CclTestOneComponentAtATime)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+R"(CCL\CclTest.bmp)");
    AprgBitmapFilters bitmapFilter(sampleFile.getFullPath());
    bitmapFilter.getConnectedComponentsOneComponentAtATime();
    bitmapFilter.saveOutputCanvasIntoFileInTheSameDirectory("CclTestOutput.bmp");
}

TEST(BitmapFilterTest, DISABLED_CclTestTwoPass)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+R"(CCL\CclTest.bmp)");
    AprgBitmapFilters bitmapFilter(sampleFile.getFullPath());
    bitmapFilter.getConnectedComponentsTwoPass();
    bitmapFilter.saveOutputCanvasIntoFileInTheSameDirectory("CclTestOutput.bmp");
}

TEST(BitmapFilterTest, DISABLED_DeterminePenAndNonPen)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+R"(PenPixelsExperiments\AnimeOutput.bmp)");

    AprgBitmapFilters bitmapFilter(sampleFile.getFullPath());
    bitmapFilter.determinePenPixels(2, 0x08);
    bitmapFilter.drawPenPixelsToOutputCanvas();
    bitmapFilter.saveOutputCanvasIntoFileInTheSameDirectory("BitmapPenPixels.bmp");
}

TEST(BitmapFilterTest, DISABLED_DeterminePenCircles)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+R"(PenPixelsExperiments\AnimeOutput.bmp)");

    AprgBitmapFilters bitmapFilter(sampleFile.getFullPath());
    bitmapFilter.determinePenPixels(2, 0x08);
    bitmapFilter.determinePenCircles(0x06, 0.20);
    bitmapFilter.drawPenCirclesToOutputCanvas();
    bitmapFilter.saveOutputCanvasIntoFileInTheSameDirectory("BitmapPenCircles.bmp");
}

TEST(BitmapFilterTest, DISABLED_FillNonPenGaps)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+R"(PenPixelsExperiments\BitmapNonPenPixels.bmp)");

    AprgBitmapFilters bitmapFilter(sampleFile.getFullPath());
    bitmapFilter.drawBlankGapsUsingBlurInOutputCanvas(2);
    bitmapFilter.saveOutputCanvasIntoFileInTheSameDirectory("BitmapNonPenPixelsFilled.bmp");
}

TEST(BitmapFilterTest, DISABLED_FindPenAndNonPenAndFillNonPenGaps)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+R"(PenPixelsExperiments\sample.bmp)");

    AprgBitmapFilters bitmapFilter(sampleFile.getFullPath());
    bitmapFilter.determinePenPixels(3, 0x20);
    bitmapFilter.drawPenPixelsToOutputCanvas();
    bitmapFilter.saveOutputCanvasIntoFileInTheSameDirectory("BitmapPenPixels.bmp");

    bitmapFilter.clearOutputCanvas();
    bitmapFilter.drawBlurredNonPenPixelsToOutputCanvas(3, 0x40);
    bitmapFilter.saveOutputCanvasIntoFileInTheSameDirectory("BitmapNonPenPixels.bmp");

    bitmapFilter.clearOutputCanvas();
    bitmapFilter.drawBlankGapsUsingBlurInOutputCanvas(2);
    bitmapFilter.saveOutputCanvasIntoFileInTheSameDirectory("BitmapNonPenPixelsFilled.bmp");
}

TEST(BitmapFilterTest, DISABLED_SpecialPurpose)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+R"(PenPixelsExperiments\sample.bmp)");

    AprgBitmapFilters bitmapFilter(sampleFile.getFullPath());
    bitmapFilter.determinePenPixels(3, 0x08);
    bitmapFilter.drawPenPixelsToOutputCanvas();
    bitmapFilter.saveOutputCanvasIntoFileInTheSameDirectory("BitmapPenPixels.bmp");

    bitmapFilter.clearOutputCanvas();
    bitmapFilter.drawBlurredNonPenPixelsToOutputCanvas(5, 0x40);
    bitmapFilter.saveOutputCanvasIntoFileInTheSameDirectory("BitmapNonPenPixels.bmp");

    bitmapFilter.copyOutputCanvasToInputCanvas();
    bitmapFilter.drawBlankGapsUsingBlurInOutputCanvas(2);
    bitmapFilter.saveOutputCanvasIntoFileInTheSameDirectory("BitmapNonPenPixelsFilled.bmp");

}
