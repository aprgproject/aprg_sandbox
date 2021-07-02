#include <BitmapFilters/BitmapFilters.hpp>

#include <PathHandlers/AlbaLocalPathHandler.hpp>

#include <gtest/gtest.h>

#include <iostream>

using namespace std;

#define APRG_BITMAP_FILTERS_BITMAP_DIRECTORY APRG_DIR R"(AprgBitmapFilters\SampleBitmaps\)"

namespace alba
{

namespace AprgBitmap
{

void animize(string const& inputFile, string const& outputFile)
{
    BitmapFilters bitmapFilter(inputFile);
    BitmapSnippet tempSnippet(bitmapFilter.getWholeBitmapSnippet());
    BitmapSnippet outputSnippet(bitmapFilter.getBlankSnippetWithBackground());

    bitmapFilter.determinePenPixels(tempSnippet, 3, 0x08);
    bitmapFilter.determinePenCirclesFromPenPixels(tempSnippet, 0x06, 0.80);

    bitmapFilter.drawAnimeColor(tempSnippet);
    bitmapFilter.drawNonPenPixels(tempSnippet, outputSnippet);
    bitmapFilter.drawToFillGapsUsingBlur(outputSnippet, 2);
    bitmapFilter.drawPenCircles(tempSnippet, outputSnippet);

    bitmapFilter.saveOutputCanvasIntoFileWithFullFilePath(outputSnippet, outputFile);
}

TEST(BitmapFilterTest, DISABLED_AnimizeMultipleFilesTest)
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
        animize(inputFilePathHandler.getFullPath(), outputFilePathHandler.getFullPath());
        cout << "Finished: " << outputFilePathHandler.getFullPath() << endl;
    }
}

TEST(BitmapFilterTest, DISABLED_AnimizeSingleFileTest)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler inputFilePathHandler(bitmapDirectory.getDirectory()+R"(NonAnimeBitmaps\GilmoreGirls.bmp)");
    AlbaLocalPathHandler outputFilePathHandler(bitmapDirectory.getDirectory()+R"(NonAnimeBitmaps\GilmoreGirls_Animized.bmp)");
    animize(inputFilePathHandler.getFullPath(), outputFilePathHandler.getFullPath());
}

TEST(BitmapFilterTest, DISABLED_DeterminePenCircles)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+R"(NonAnimeBitmaps\VeronicaMars.bmp)");
    BitmapFilters bitmapFilter(sampleFile.getFullPath());
    BitmapSnippet tempSnippet(bitmapFilter.getWholeBitmapSnippet());
    BitmapSnippet outputSnippet(bitmapFilter.getBlankSnippetWithBackground());

    bitmapFilter.determinePenPixels(tempSnippet, 2, 0x08);
    bitmapFilter.determinePenCirclesFromPenPixels(tempSnippet, 0x06, 0.80);
    bitmapFilter.drawPenCircles(tempSnippet, outputSnippet);
    bitmapFilter.saveOutputCanvasIntoFileInTheSameDirectory(outputSnippet, "VeronicaMars_PenCircles.bmp");
}

TEST(BitmapFilterTest, DISABLED_DeterminePenAndNonPen)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+R"(NonAnimeBitmaps\VeronicaMars.bmp)");
    BitmapFilters bitmapFilter(sampleFile.getFullPath());
    BitmapSnippet tempSnippet(bitmapFilter.getWholeBitmapSnippet());
    BitmapSnippet outputSnippet(bitmapFilter.getBlankSnippetWithBackground());

    bitmapFilter.determinePenPixels(tempSnippet, 2, 0x08);
    bitmapFilter.drawPenPixels(tempSnippet, outputSnippet);
    bitmapFilter.saveOutputCanvasIntoFileInTheSameDirectory(outputSnippet, "VeronicaMars_Pen.bmp");
}

TEST(BitmapFilterTest, DISABLED_FillNonPenGaps)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+R"(PenPixelsExperiments\BitmapNonPenPixels.bmp)");
    BitmapFilters bitmapFilter(sampleFile.getFullPath());
    BitmapSnippet outputSnippet(bitmapFilter.getWholeBitmapSnippet());

    bitmapFilter.drawToFillGapsUsingBlur(outputSnippet, 2);
    bitmapFilter.saveOutputCanvasIntoFileInTheSameDirectory(outputSnippet, "BitmapNonPenPixelsFilledNewAlgo.bmp");
}

TEST(BitmapFilterTest, DISABLED_FindPenAndNonPenAndFillNonPenGaps)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+R"(PenPixelsExperiments\sample.bmp)");
    BitmapFilters bitmapFilter(sampleFile.getFullPath());
    BitmapSnippet tempSnippet(bitmapFilter.getWholeBitmapSnippet());
    BitmapSnippet outputSnippet(bitmapFilter.getBlankSnippetWithBackground());

    bitmapFilter.determinePenPixels(tempSnippet, 2, 0x08);
    bitmapFilter.drawPenPixels(tempSnippet, outputSnippet);
    bitmapFilter.saveOutputCanvasIntoFileInTheSameDirectory(outputSnippet, "BitmapPenPixels.bmp");

    outputSnippet = bitmapFilter.getBlankSnippetWithBackground();
    bitmapFilter.drawNonPenPixels(tempSnippet, outputSnippet);
    bitmapFilter.saveOutputCanvasIntoFileInTheSameDirectory(outputSnippet, "BitmapNonPenPixels.bmp");

    outputSnippet = bitmapFilter.getBlankSnippetWithBackground();
    bitmapFilter.drawBlurredNonPenPixels(tempSnippet, outputSnippet, 3, 0x40);
    bitmapFilter.saveOutputCanvasIntoFileInTheSameDirectory(outputSnippet, "BitmapBlurredNonPenPixels.bmp");

    bitmapFilter.drawToFillGapsUsingBlur(outputSnippet, 2);
    bitmapFilter.saveOutputCanvasIntoFileInTheSameDirectory(outputSnippet, "BitmapNonPenPixelsFilled.bmp");
}

TEST(BitmapFilterTest, DISABLED_ConvertToAnimeColorWorks)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    BitmapFilters bitmapFilter(bitmapDirectory.getDirectory()+R"(NonAnimeBitmaps\JohnMayerDark.bmp)");
    BitmapSnippet outputSnippet(bitmapFilter.getWholeBitmapSnippet());

    bitmapFilter.drawAnimeColor(outputSnippet);
    bitmapFilter.saveOutputCanvasIntoFileInTheSameDirectory(outputSnippet, "JohnMayerDark_AnimeOutput.bmp");
}

TEST(BitmapFilterTest, DISABLED_GatherAndSaveStatisticsWorks)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    BitmapFilters bitmapFilter(bitmapDirectory.getDirectory()+R"(NonAnimeBitmaps\Foals.bmp)");

    bitmapFilter.gatherAndSaveColorDataAndStatistics();
}

TEST(BitmapFilterTest, DISABLED_CclTestOneComponentAtATime)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+R"(CCL\CclTest.bmp)");
    BitmapFilters bitmapFilter(sampleFile.getFullPath());
    BitmapSnippet outputSnippet(bitmapFilter.getWholeBitmapSnippet());

    bitmapFilter.determineConnectedComponentsByOneComponentAtATime(outputSnippet);
    bitmapFilter.drawNewColorForLabels(outputSnippet);
    bitmapFilter.saveOutputCanvasIntoFileInTheSameDirectory(outputSnippet, "Ccl_OneComponentAtATime.bmp");
}

TEST(BitmapFilterTest, DISABLED_CclTestTwoPass)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+R"(CCL\CclTest.bmp)");
    BitmapFilters bitmapFilter(sampleFile.getFullPath());
    BitmapSnippet outputSnippet(bitmapFilter.getWholeBitmapSnippet());

    bitmapFilter.determineConnectedComponentsUsingTwoPass(outputSnippet);
    bitmapFilter.drawNewColorForLabels(outputSnippet);
    bitmapFilter.saveOutputCanvasIntoFileInTheSameDirectory(outputSnippet, "Ccl_TwoPass.bmp");
}

}

}
