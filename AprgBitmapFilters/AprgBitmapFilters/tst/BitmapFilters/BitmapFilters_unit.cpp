#include <BitmapFilters/AnimizeColor.hpp>
#include <BitmapFilters/BitmapFilters.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>

#include <gtest/gtest.h>

using namespace std;

#define APRG_BITMAP_FILTERS_BITMAP_DIRECTORY APRG_DIR R"(AprgBitmapFilters\SampleBitmaps\)"

namespace alba
{

namespace AprgBitmap
{

TEST(BitmapFiltersTest, DISABLED_BlurringDisimilarColors)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+R"(NonAnimeBitmaps\santanaPixelated.bmp)");
    BitmapFilters bitmapFilter(sampleFile.getFullPath());
    BitmapSnippet outputSnippet(bitmapFilter.getWholeBitmapSnippet());

    bitmapFilter.drawWithBlurringDisimilarColors(outputSnippet, 5, 0x02);
    bitmapFilter.saveSnippetIntoFileInTheSameDirectory(outputSnippet, "santanaPixelatedBlurredOut.bmp");
}

TEST(BitmapFiltersTest, DISABLED_BlurUsingSnakeLikeTraversal)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+R"(NonAnimeBitmaps\santanaPixelated.bmp)");
    BitmapFilters bitmapFilter(sampleFile.getFullPath());
    BitmapSnippet outputSnippet(bitmapFilter.getWholeBitmapSnippet());

    bitmapFilter.drawWithBlurUsingSnakeLikeTraversal(outputSnippet, 0x08);
    bitmapFilter.saveSnippetIntoFileInTheSameDirectory(outputSnippet, "santanaPixelatedBlurredOut.bmp");
}

TEST(BitmapFiltersTest, DISABLED_BlurredColors)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+R"(NonAnimeBitmaps\santanaPixelated.bmp)");
    BitmapFilters bitmapFilter(sampleFile.getFullPath());
    BitmapSnippet outputSnippet(bitmapFilter.getWholeBitmapSnippet());

    bitmapFilter.drawBlurredColorsUsingCircles(outputSnippet, 8, 0x20);
    bitmapFilter.saveSnippetIntoFileInTheSameDirectory(outputSnippet, "santanaPixelatedBlurredOut.bmp");
}

TEST(BitmapFiltersTest, DISABLED_DeterminePenCircles)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+R"(NonAnimeBitmaps\VeronicaMars.bmp)");
    BitmapFilters bitmapFilter(sampleFile.getFullPath());
    BitmapSnippet tempSnippet(bitmapFilter.getWholeBitmapSnippet());
    BitmapSnippet outputSnippet(bitmapFilter.getBlankSnippetWithBackground());
    PenPoints penPoints;
    PenCircles penCircles;

    bitmapFilter.determinePenPoints(penPoints, tempSnippet, 2, 0x08);
    bitmapFilter.determinePenCirclesFromPenPoints(penCircles, penPoints, tempSnippet, 0x08, 0.80);
    bitmapFilter.drawPenCircles(penCircles, outputSnippet);
    bitmapFilter.saveSnippetIntoFileInTheSameDirectory(outputSnippet, "VeronicaMars_PenCircles.bmp");
}

TEST(BitmapFiltersTest, DeterminePenAndNonPen)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+R"(NonAnimeBitmaps\VeronicaMars.bmp)");
    BitmapFilters bitmapFilter(sampleFile.getFullPath());
    BitmapSnippet tempSnippet(bitmapFilter.getWholeBitmapSnippet());
    BitmapSnippet outputSnippet(bitmapFilter.getBlankSnippetWithBackground());
    PenPoints penPoints;

    bitmapFilter.determinePenPoints(penPoints, tempSnippet, 2, 0x08);
    bitmapFilter.drawPenPoints(penPoints, tempSnippet, outputSnippet);
    bitmapFilter.saveSnippetIntoFileInTheSameDirectory(outputSnippet, "VeronicaMars_Pen.bmp");

    outputSnippet = bitmapFilter.getBlankSnippetWithBackground();
    bitmapFilter.drawNonPenPoints(penPoints, tempSnippet, outputSnippet);
    bitmapFilter.saveSnippetIntoFileInTheSameDirectory(outputSnippet, "VeronicaMars_NonPen.bmp");
}

TEST(BitmapFiltersTest, DISABLED_FillNonPenGaps)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+R"(NonAnimeBitmaps\VeronicaMarsNonPen.bmp)");
    BitmapFilters bitmapFilter(sampleFile.getFullPath());
    BitmapSnippet outputSnippet(bitmapFilter.getWholeBitmapSnippet());

    bitmapFilter.drawToFillGapsUsingBlur(outputSnippet, 2);
    bitmapFilter.saveSnippetIntoFileInTheSameDirectory(outputSnippet, "VeronicaMarsNonPenFilledGaps.bmp");
}

TEST(BitmapFiltersTest, DISABLED_FindPenAndNonPenAndFillNonPenGaps)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+R"(PenPointsExperiments\sample.bmp)");
    BitmapFilters bitmapFilter(sampleFile.getFullPath());
    BitmapSnippet tempSnippet(bitmapFilter.getWholeBitmapSnippet());
    BitmapSnippet outputSnippet(bitmapFilter.getBlankSnippetWithBackground());
    PenPoints penPoints;

    bitmapFilter.determinePenPoints(penPoints, tempSnippet, 2, 0x08);
    bitmapFilter.drawPenPoints(penPoints, tempSnippet, outputSnippet);
    bitmapFilter.saveSnippetIntoFileInTheSameDirectory(outputSnippet, "BitmapPenPoints.bmp");

    outputSnippet = bitmapFilter.getBlankSnippetWithBackground();
    bitmapFilter.drawNonPenPoints(penPoints, tempSnippet, outputSnippet);
    bitmapFilter.saveSnippetIntoFileInTheSameDirectory(outputSnippet, "BitmapNonPenPoints.bmp");

    outputSnippet = bitmapFilter.getBlankSnippetWithBackground();
    bitmapFilter.drawBlurredNonPenPoints(penPoints, tempSnippet, outputSnippet, 3, 0x40);
    bitmapFilter.saveSnippetIntoFileInTheSameDirectory(outputSnippet, "BitmapBlurredNonPenPoints.bmp");

    bitmapFilter.drawToFillGapsUsingBlur(outputSnippet, 2);
    bitmapFilter.saveSnippetIntoFileInTheSameDirectory(outputSnippet, "BitmapNonPenPointsFilled.bmp");
}

TEST(BitmapFiltersTest, DISABLED_ConvertToAnimeColorWorks)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    string inputBitmapFile=bitmapDirectory.getDirectory()+R"(NonAnimeBitmaps\santana_NonPenFilledGaps.bmp)";
    BitmapFilters bitmapFilter(inputBitmapFile);
    BitmapSnippet outputSnippet(bitmapFilter.getWholeBitmapSnippet());
    AnimizeColor animizeColor;
    animizeColor.gatherStatistics(inputBitmapFile);
    animizeColor.calculateNewValues();

    bitmapFilter.drawAnimeColor(outputSnippet, animizeColor);
    bitmapFilter.saveSnippetIntoFileInTheSameDirectory(outputSnippet, "santana_NonPenFilledGaps_AnimeColor.bmp");
}

TEST(BitmapFiltersTest, DISABLED_GatherAndSaveStatisticsWorks)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    BitmapFilters bitmapFilter(bitmapDirectory.getDirectory()+R"(NonAnimeBitmaps\Foals.bmp)");

    bitmapFilter.gatherAndSaveColorDataAndStatistics();
}

TEST(BitmapFiltersTest, DISABLED_CclTestOneComponentAtATime)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+R"(CCL\CclTest.bmp)");
    BitmapFilters bitmapFilter(sampleFile.getFullPath());
    BitmapSnippet outputSnippet(bitmapFilter.getWholeBitmapSnippet());

    bitmapFilter.determineConnectedComponentsByOneComponentAtATime(outputSnippet);
    bitmapFilter.drawNewColorForLabels(outputSnippet);
    bitmapFilter.saveSnippetIntoFileInTheSameDirectory(outputSnippet, "Ccl_OneComponentAtATime.bmp");
}

TEST(BitmapFiltersTest, DISABLED_CclTestTwoPass)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+R"(CCL\CclTest.bmp)");
    BitmapFilters bitmapFilter(sampleFile.getFullPath());
    BitmapSnippet outputSnippet(bitmapFilter.getWholeBitmapSnippet());

    bitmapFilter.determineConnectedComponentsUsingTwoPass(outputSnippet);
    bitmapFilter.drawNewColorForLabels(outputSnippet);
    bitmapFilter.saveSnippetIntoFileInTheSameDirectory(outputSnippet, "Ccl_TwoPass.bmp");
}

}

}
