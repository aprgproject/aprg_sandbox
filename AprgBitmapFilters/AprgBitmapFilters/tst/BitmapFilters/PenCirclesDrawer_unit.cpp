#include <BitmapFilters/BitmapFilters.hpp>
#include <BitmapFilters/PenCirclesDrawer.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>

#include <gtest/gtest.h>

using namespace alba::AprgBitmap;
using namespace std;

#define APRG_BITMAP_FILTERS_BITMAP_DIRECTORY APRG_DIR R"(AprgBitmapFilters\SampleBitmaps\)"

namespace alba
{

namespace AprgBitmap
{

TEST(PenCirclesDrawerTest, DrawACircle)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+R"(PenCirclesDrawerTests\EmptyBitmap.bmp)");
    BitmapFilters bitmapFilters(sampleFile.getFullPath());
    BitmapSnippet outputSnippet(bitmapFilters.getWholeBitmapSnippet());

    PenCircles penCircles;
    penCircles.addAsPenCircle(BitmapXY(100, 100), 20, 0x123456);

    PenCirclesDrawer drawer(penCircles, outputSnippet);
    drawer.drawCircles();
    bitmapFilters.saveSnippetIntoFileInTheSameDirectory(outputSnippet, "DrawACircle.bmp");
}

TEST(PenCirclesDrawerTest, DrawTwoConnectedCircles)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler sampleFile(bitmapDirectory.getDirectory()+R"(PenCirclesDrawerTests\EmptyBitmap.bmp)");
    BitmapFilters bitmapFilters(sampleFile.getFullPath());
    BitmapSnippet outputSnippet(bitmapFilters.getWholeBitmapSnippet());

    PenCircles penCircles;
    penCircles.addAsPenCircle(BitmapXY(200, 200), 20, 0x123456);
    penCircles.addAsPenCircle(BitmapXY(50, 50), 40, 0x123456);
    penCircles.connectCircles(BitmapXY(200, 200), BitmapXY(50, 50));

    PenCirclesDrawer drawer(penCircles, outputSnippet);
    drawer.drawCircles();
    drawer.drawCircleConnections();
    bitmapFilters.saveSnippetIntoFileInTheSameDirectory(outputSnippet, "DrawTwoConnectedCircles.bmp");
}

}

}
