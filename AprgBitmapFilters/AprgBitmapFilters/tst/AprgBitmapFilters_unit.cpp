#include <AprgBitmapFilters.hpp>

#include <PathHandlers/AlbaLocalPathHandler.hpp>

#include <gtest/gtest.h>

using namespace std;

#define APRG_BITMAP_FILTERS_BITMAP_DIRECTORY APRG_DIR R"(AprgBitmapFilters\AprgBitmapFilters\tst\Bitmaps\)"

namespace alba
{

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
        AprgBitmapSnippet tempSnippet(bitmapFilter.getWholeBitmapSnippet());
        AprgBitmapSnippet outputSnippet(bitmapFilter.getBlankSnippetWithBackground());

        bitmapFilter.drawAnimeColor(tempSnippet);
        bitmapFilter.determinePenPixels(tempSnippet, 3, 0x08);
        bitmapFilter.determinePenCirclesFromPenPixels(tempSnippet, 0x06, 0.80);

        bitmapFilter.drawNonPenPixels(tempSnippet, outputSnippet);
        bitmapFilter.drawToFillGapsUsingBlur(outputSnippet, 2);
        bitmapFilter.drawPenCircles(outputSnippet);

        bitmapFilter.saveOutputCanvasIntoFileWithFullFilePath(outputSnippet, outputFilePathHandler.getFullPath());
    }
}

TEST(BitmapFilterTest, DISABLED_DeterminePenCircles)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+R"(NonAnimeBitmaps\Witcher.bmp)");
    AprgBitmapFilters bitmapFilter(sampleFile.getFullPath());
    AprgBitmapSnippet tempSnippet(bitmapFilter.getWholeBitmapSnippet());
    AprgBitmapSnippet outputSnippet(bitmapFilter.getBlankSnippetWithBackground());

    bitmapFilter.determinePenPixels(tempSnippet, 2, 0x08);
    bitmapFilter.determinePenCirclesFromPenPixels(tempSnippet, 0x06, 0.50);
    bitmapFilter.drawPenCircles(outputSnippet);
    bitmapFilter.saveOutputCanvasIntoFileInTheSameDirectory(outputSnippet, "Witcher_PenCircles.bmp");
}

TEST(BitmapFilterTest, DISABLED_DeterminePenAndNonPen)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+R"(NonAnimeBitmaps\JohnMayerDark.bmp)");
    AprgBitmapFilters bitmapFilter(sampleFile.getFullPath());
    AprgBitmapSnippet tempSnippet(bitmapFilter.getWholeBitmapSnippet());
    AprgBitmapSnippet outputSnippet(bitmapFilter.getBlankSnippetWithBackground());

    bitmapFilter.determinePenPixels(tempSnippet, 2, 0x08);
    bitmapFilter.drawPenPixels(tempSnippet, outputSnippet);
    bitmapFilter.saveOutputCanvasIntoFileInTheSameDirectory(outputSnippet, "JohnMayerDark_Pen.bmp");
}

TEST(BitmapFilterTest, DISABLED_ConvertToAnimeColorWorks)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AprgBitmapFilters bitmapFilter(bitmapDirectory.getDirectory()+R"(NonAnimeBitmaps\JohnMayerDark.bmp)");
    AprgBitmapSnippet outputSnippet(bitmapFilter.getWholeBitmapSnippet());

    bitmapFilter.drawAnimeColor(outputSnippet);
    bitmapFilter.saveOutputCanvasIntoFileInTheSameDirectory(outputSnippet, "JohnMayerDark_AnimeOutput.bmp");
}

TEST(BitmapFilterTest, DISABLED_GatherAndSaveStatisticsWorks)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AprgBitmapFilters bitmapFilter(bitmapDirectory.getDirectory()+R"(NonAnimeBitmaps\Foals.bmp)");

    bitmapFilter.gatherAndSaveColorDataAndStatistics();
}

TEST(BitmapFilterTest, DISABLED_CclTestOneComponentAtATime)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+R"(CCL\CclTest.bmp)");
    AprgBitmapFilters bitmapFilter(sampleFile.getFullPath());
    AprgBitmapSnippet outputSnippet(bitmapFilter.getWholeBitmapSnippet());

    bitmapFilter.determineConnectedComponentsByOneComponentAtATime(outputSnippet);
    bitmapFilter.drawNewColorForLabels(outputSnippet);
    bitmapFilter.saveOutputCanvasIntoFileInTheSameDirectory(outputSnippet, "Ccl_OneComponentAtATime.bmp");
}

TEST(BitmapFilterTest, CclTestTwoPass)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+R"(CCL\CclTest.bmp)");
    AprgBitmapFilters bitmapFilter(sampleFile.getFullPath());
    AprgBitmapSnippet outputSnippet(bitmapFilter.getWholeBitmapSnippet());

    bitmapFilter.determineConnectedComponentsUsingTwoPass(outputSnippet);
    bitmapFilter.drawNewColorForLabels(outputSnippet);
    bitmapFilter.saveOutputCanvasIntoFileInTheSameDirectory(outputSnippet, "Ccl_TwoPass.bmp");
}

TEST(BitmapFilterTest, DISABLED_FillNonPenGaps)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+R"(PenPixelsExperiments\BitmapNonPenPixels.bmp)");
    AprgBitmapFilters bitmapFilter(sampleFile.getFullPath());
    AprgBitmapSnippet outputSnippet(bitmapFilter.getWholeBitmapSnippet());

    bitmapFilter.drawToFillGapsUsingBlur(outputSnippet, 2);
    bitmapFilter.saveOutputCanvasIntoFileInTheSameDirectory(outputSnippet, "BitmapNonPenPixelsFilled.bmp");
}

TEST(BitmapFilterTest, DISABLED_FindPenAndNonPenAndFillNonPenGaps)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+R"(PenPixelsExperiments\sample.bmp)");
    AprgBitmapFilters bitmapFilter(sampleFile.getFullPath());
    AprgBitmapSnippet tempSnippet(bitmapFilter.getWholeBitmapSnippet());
    AprgBitmapSnippet outputSnippet(bitmapFilter.getBlankSnippetWithBackground());

    bitmapFilter.determinePenPixels(tempSnippet, 3, 0x20);
    bitmapFilter.drawPenPixels(tempSnippet, outputSnippet);
    bitmapFilter.saveOutputCanvasIntoFileInTheSameDirectory(outputSnippet, "BitmapPenPixels.bmp");

    outputSnippet = bitmapFilter.getBlankSnippetWithBackground();
    bitmapFilter.drawBlurredNonPenPixels(outputSnippet, 3, 0x40);
    bitmapFilter.saveOutputCanvasIntoFileInTheSameDirectory(outputSnippet, "BitmapNonPenPixels.bmp");

    outputSnippet = bitmapFilter.getBlankSnippetWithBackground();
    bitmapFilter.drawToFillGapsUsingBlur(outputSnippet, 2);
    bitmapFilter.saveOutputCanvasIntoFileInTheSameDirectory(outputSnippet, "BitmapNonPenPixelsFilled.bmp");
}

}
