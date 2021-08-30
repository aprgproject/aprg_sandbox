#include <BitmapFilters/AnimizeColor.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>

#include <gtest/gtest.h>
using namespace std;

#define APRG_BITMAP_FILTERS_BITMAP_DIRECTORY APRG_DIR R"(AprgBitmapFilters\SampleBitmaps\)"
namespace alba
{

namespace AprgBitmap
{

TEST(AnimizeColorTest, DISABLED_GatherAndSaveStatistics)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);

    gatherAndSaveDataInAnimizeColor(bitmapDirectory.getDirectory()+R"(NonAnimeBitmaps\Foals.bmp)");
}

}

}
