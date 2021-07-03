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

    bitmapFilter.determinePenPoints(tempSnippet, 3, 0x08);
    bitmapFilter.determinePenCirclesFromPenPoints(tempSnippet, 0x06, 0.80);

    bitmapFilter.drawAnimeColor(tempSnippet);
    bitmapFilter.drawNonPenPoints(tempSnippet, outputSnippet);
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

TEST(BitmapFilterTest, DISABLED_BlurredOutDisimilarColors)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+R"(NonAnimeBitmaps\santanaPixelated.bmp)");
    BitmapFilters bitmapFilter(sampleFile.getFullPath());
    BitmapSnippet outputSnippet(bitmapFilter.getWholeBitmapSnippet());

    bitmapFilter.drawWithBlurredOutDisimilarColors(outputSnippet, 0x02);
    bitmapFilter.saveOutputCanvasIntoFileInTheSameDirectory(outputSnippet, "santanaPixelatedBlurredOut.bmp");
}

TEST(BitmapFilterTest, DISABLED_BlurredColors)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+R"(NonAnimeBitmaps\santanaPixelated.bmp)");
    BitmapFilters bitmapFilter(sampleFile.getFullPath());
    BitmapSnippet outputSnippet(bitmapFilter.getWholeBitmapSnippet());

    bitmapFilter.drawBlurredColors(outputSnippet, 8, 0x20);
    bitmapFilter.saveOutputCanvasIntoFileInTheSameDirectory(outputSnippet, "santanaPixelatedBlurredOut.bmp");
}

TEST(BitmapFilterTest, DISABLED_DeterminePenCircles)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+R"(NonAnimeBitmaps\VeronicaMars.bmp)");    BitmapFilters bitmapFilter(sampleFile.getFullPath());
    BitmapSnippet tempSnippet(bitmapFilter.getWholeBitmapSnippet());
    BitmapSnippet outputSnippet(bitmapFilter.getBlankSnippetWithBackground());

    bitmapFilter.determinePenPoints(tempSnippet, 2, 0x08);
    bitmapFilter.determinePenCirclesFromPenPoints(tempSnippet, 0x06, 0.80);
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
    bitmapFilter.determinePenPoints(tempSnippet, 2, 0x08);
    bitmapFilter.drawPenPoints(tempSnippet, outputSnippet);
    bitmapFilter.saveOutputCanvasIntoFileInTheSameDirectory(outputSnippet, "VeronicaMars_Pen.bmp");

    outputSnippet = bitmapFilter.getBlankSnippetWithBackground();
    bitmapFilter.drawNonPenPoints(tempSnippet, outputSnippet);
    bitmapFilter.saveOutputCanvasIntoFileInTheSameDirectory(outputSnippet, "VeronicaMars_NonPen.bmp");
}

TEST(BitmapFilterTest, DISABLED_FillNonPenGaps)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+R"(NonAnimeBitmaps\VeronicaMarsNonPen.bmp)");
    BitmapFilters bitmapFilter(sampleFile.getFullPath());
    BitmapSnippet outputSnippet(bitmapFilter.getWholeBitmapSnippet());

    bitmapFilter.drawToFillGapsUsingBlur(outputSnippet, 2);
    bitmapFilter.saveOutputCanvasIntoFileInTheSameDirectory(outputSnippet, "VeronicaMarsNonPenFilledGaps.bmp");
}

TEST(BitmapFilterTest, DISABLED_FindPenAndNonPenAndFillNonPenGaps){
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+R"(PenPointsExperiments\sample.bmp)");
    BitmapFilters bitmapFilter(sampleFile.getFullPath());
    BitmapSnippet tempSnippet(bitmapFilter.getWholeBitmapSnippet());
    BitmapSnippet outputSnippet(bitmapFilter.getBlankSnippetWithBackground());

    bitmapFilter.determinePenPoints(tempSnippet, 2, 0x08);
    bitmapFilter.drawPenPoints(tempSnippet, outputSnippet);
    bitmapFilter.saveOutputCanvasIntoFileInTheSameDirectory(outputSnippet, "BitmapPenPoints.bmp");

    outputSnippet = bitmapFilter.getBlankSnippetWithBackground();
    bitmapFilter.drawNonPenPoints(tempSnippet, outputSnippet);
    bitmapFilter.saveOutputCanvasIntoFileInTheSameDirectory(outputSnippet, "BitmapNonPenPoints.bmp");

    outputSnippet = bitmapFilter.getBlankSnippetWithBackground();
    bitmapFilter.drawBlurredNonPenPoints(tempSnippet, outputSnippet, 3, 0x40);
    bitmapFilter.saveOutputCanvasIntoFileInTheSameDirectory(outputSnippet, "BitmapBlurredNonPenPoints.bmp");

    bitmapFilter.drawToFillGapsUsingBlur(outputSnippet, 2);
    bitmapFilter.saveOutputCanvasIntoFileInTheSameDirectory(outputSnippet, "BitmapNonPenPointsFilled.bmp");
}

TEST(BitmapFilterTest, DISABLED_ConvertToAnimeColorWorks)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    BitmapFilters bitmapFilter(bitmapDirectory.getDirectory()+R"(NonAnimeBitmaps\santana_NonPenFilledGaps.bmp)");
    BitmapSnippet outputSnippet(bitmapFilter.getWholeBitmapSnippet());

    bitmapFilter.drawAnimeColor(outputSnippet);
    bitmapFilter.saveOutputCanvasIntoFileInTheSameDirectory(outputSnippet, "santana_NonPenFilledGaps_AnimeColor.bmp");
}

TEST(BitmapFilterTest, DISABLED_GatherAndSaveStatisticsWorks){
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
