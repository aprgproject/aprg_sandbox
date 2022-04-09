#include <BitmapFilters/AnimizeColor.hpp>
#include <BitmapFilters/BitmapFilters.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <gtest/gtest.h>

using namespace std;

#define APRG_BITMAP_FILTERS_BITMAP_DIRECTORY APRG_DIR R"(\AprgBitmapFilters\FilesForTests\SampleBitmaps\)"

namespace alba
{
namespace AprgBitmap
{
TEST(BitmapFiltersTest, DISABLED_BlurringDisimilarColors)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+R"(NonAnimeBitmaps\santanaPixelated.bmp)");
    BitmapFilters bitmapFilters(sampleFile.getFullPath());
    BitmapSnippet outputSnippet(bitmapFilters.getWholeBitmapSnippet());

    bitmapFilters.drawWithBlurringDisimilarColors(outputSnippet, 5, 0x02);
    bitmapFilters.saveSnippetIntoFileInTheSameDirectory(outputSnippet, "santanaPixelatedBlurredOut.bmp");
}

TEST(BitmapFiltersTest, DISABLED_BlurUsingSnakeLikeTraversal)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+R"(NonAnimeBitmaps\santanaPixelated.bmp)");
    BitmapFilters bitmapFilters(sampleFile.getFullPath());
    BitmapSnippet outputSnippet(bitmapFilters.getWholeBitmapSnippet());

    bitmapFilters.drawWithBlurUsingSnakeLikeTraversal(outputSnippet, 0x08);
    bitmapFilters.saveSnippetIntoFileInTheSameDirectory(outputSnippet, "santanaPixelatedBlurredOut.bmp");
}

TEST(BitmapFiltersTest, DISABLED_BlurredColors)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+R"(NonAnimeBitmaps\santanaPixelated.bmp)");
    BitmapFilters bitmapFilters(sampleFile.getFullPath());
    BitmapSnippet outputSnippet(bitmapFilters.getWholeBitmapSnippet());

    bitmapFilters.drawBlurredColorsUsingCircles(outputSnippet, 8, 0x20);
    bitmapFilters.saveSnippetIntoFileInTheSameDirectory(outputSnippet, "santanaPixelatedBlurredOut.bmp");
}

TEST(BitmapFiltersTest, DISABLED_DeterminePenCircles)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+R"(NonAnimeBitmaps\JohnMayerVideoBlurredAnimizedColor.bmp)");
    BitmapFilters bitmapFilters(sampleFile.getFullPath());
    BitmapSnippet tempSnippet(bitmapFilters.getWholeBitmapSnippet());
    BitmapSnippet outputSnippet(bitmapFilters.getBlankSnippetWithBackground());
    PenPoints penPoints;
    PenCircles penCircles;

    bitmapFilters.determinePenPoints(penPoints, tempSnippet, 2, 0x08);
    bitmapFilters.drawPenPoints(penPoints, tempSnippet, outputSnippet);
    bitmapFilters.saveSnippetIntoFileInTheSameDirectory(outputSnippet, "JohnMayerVideoBlurredAnimizedColor_1PenPoints.bmp");

    outputSnippet=bitmapFilters.getBlankSnippetWithBackground();
    bitmapFilters.determinePenCirclesFromPenPoints(penCircles, penPoints, tempSnippet, 0x08, 0.80);
    bitmapFilters.drawPenCircles(penCircles, outputSnippet);
    bitmapFilters.saveSnippetIntoFileInTheSameDirectory(outputSnippet, "JohnMayerVideoBlurredAnimizedColor_2PenCircles.bmp");
}

TEST(BitmapFiltersTest, DISABLED_DeterminePenAndNonPen)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+R"(NonAnimeBitmaps\VeronicaMars.bmp)");
    BitmapFilters bitmapFilters(sampleFile.getFullPath());
    BitmapSnippet tempSnippet(bitmapFilters.getWholeBitmapSnippet());
    BitmapSnippet outputSnippet(bitmapFilters.getBlankSnippetWithBackground());
    PenPoints penPoints;

    bitmapFilters.determinePenPoints(penPoints, tempSnippet, 2, 0x08);
    bitmapFilters.drawPenPoints(penPoints, tempSnippet, outputSnippet);
    bitmapFilters.saveSnippetIntoFileInTheSameDirectory(outputSnippet, "VeronicaMars_Pen.bmp");

    outputSnippet = bitmapFilters.getBlankSnippetWithBackground();
    bitmapFilters.drawNonPenPoints(penPoints, tempSnippet, outputSnippet);
    bitmapFilters.saveSnippetIntoFileInTheSameDirectory(outputSnippet, "VeronicaMars_NonPen.bmp");
}

TEST(BitmapFiltersTest, DISABLED_FillGaps)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+R"(NonAnimeBitmaps\White.bmp)");
    BitmapFilters bitmapFilters(sampleFile.getFullPath());
    BitmapSnippet outputSnippet(bitmapFilters.getWholeBitmapSnippet());

    bitmapFilters.drawToFillGapsUsingBlur(outputSnippet, 2);
    bitmapFilters.saveSnippetIntoFileInTheSameDirectory(outputSnippet, "White_FilledGaps.bmp");
}

TEST(BitmapFiltersTest, DISABLED_FindPenAndNonPenAndFillNonPenGaps)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+R"(PenPointsExperiments\sample.bmp)");
    BitmapFilters bitmapFilters(sampleFile.getFullPath());
    BitmapSnippet tempSnippet(bitmapFilters.getWholeBitmapSnippet());
    BitmapSnippet outputSnippet(bitmapFilters.getBlankSnippetWithBackground());
    PenPoints penPoints;

    bitmapFilters.determinePenPoints(penPoints, tempSnippet, 2, 0x08);
    bitmapFilters.drawPenPoints(penPoints, tempSnippet, outputSnippet);
    bitmapFilters.saveSnippetIntoFileInTheSameDirectory(outputSnippet, "BitmapPenPoints.bmp");

    outputSnippet = bitmapFilters.getBlankSnippetWithBackground();
    bitmapFilters.drawNonPenPoints(penPoints, tempSnippet, outputSnippet);
    bitmapFilters.saveSnippetIntoFileInTheSameDirectory(outputSnippet, "BitmapNonPenPoints.bmp");

    outputSnippet = bitmapFilters.getBlankSnippetWithBackground();
    bitmapFilters.drawBlurredNonPenPoints(penPoints, tempSnippet, outputSnippet, 3, 0x40);
    bitmapFilters.saveSnippetIntoFileInTheSameDirectory(outputSnippet, "BitmapBlurredNonPenPoints.bmp");

    bitmapFilters.drawToFillGapsUsingBlur(outputSnippet, 2);
    bitmapFilters.saveSnippetIntoFileInTheSameDirectory(outputSnippet, "BitmapNonPenPointsFilled.bmp");
}

TEST(BitmapFiltersTest, DISABLED_ConvertToAnimeColorWorks)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    string inputBitmapFile=bitmapDirectory.getDirectory()+R"(NonAnimeBitmaps\santana_NonPenFilledGaps.bmp)";
    BitmapFilters bitmapFilters(inputBitmapFile);
    BitmapSnippet outputSnippet(bitmapFilters.getWholeBitmapSnippet());
    AnimizeColor animizeColor;
    animizeColor.gatherStatistics(inputBitmapFile);
    animizeColor.calculateNewValues();

    bitmapFilters.drawAnimeColor(outputSnippet, animizeColor);
    bitmapFilters.saveSnippetIntoFileInTheSameDirectory(outputSnippet, "santana_NonPenFilledGaps_AnimeColor.bmp");
}

TEST(BitmapFiltersTest, DISABLED_GatherAndSaveStatisticsWorks)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    BitmapFilters bitmapFilters(bitmapDirectory.getDirectory()+R"(NonAnimeBitmaps\Foals.bmp)");

    bitmapFilters.gatherAndSaveColorDataAndStatistics();
}

TEST(BitmapFiltersTest, DISABLED_CclTestOneComponentAtATime)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+R"(CCL\CclTest.bmp)");
    BitmapFilters bitmapFilters(sampleFile.getFullPath());
    BitmapSnippet outputSnippet(bitmapFilters.getWholeBitmapSnippet());

    bitmapFilters.determineConnectedComponentsByOneComponentAtATime(outputSnippet);
    bitmapFilters.drawNewColorForLabels(outputSnippet);
    bitmapFilters.saveSnippetIntoFileInTheSameDirectory(outputSnippet, "Ccl_OneComponentAtATime.bmp");
}

TEST(BitmapFiltersTest, DISABLED_CclTestTwoPass)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+R"(CCL\CclTest.bmp)");
    BitmapFilters bitmapFilters(sampleFile.getFullPath());
    BitmapSnippet outputSnippet(bitmapFilters.getWholeBitmapSnippet());

    bitmapFilters.determineConnectedComponentsUsingTwoPass(outputSnippet);
    bitmapFilters.drawNewColorForLabels(outputSnippet);
    bitmapFilters.saveSnippetIntoFileInTheSameDirectory(outputSnippet, "Ccl_TwoPass.bmp");
}

}

}
