#include <BitmapFilters/ColorStatistics.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <gtest/gtest.h>

using namespace std;

#define APRG_BITMAP_FILTERS_BITMAP_DIRECTORY APRG_DIR R"(AprgBitmapFilters\SampleBitmaps\)"

namespace alba
{

namespace AprgBitmap
{

TEST(ColorStatisticsTest, DISABLED_GatherAndSaveStatistics)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);

    gatherAndSaveColorStatistics(bitmapDirectory.getDirectory()+R"(NonAnimeBitmaps\JohnMayerDark.bmp)");
}

}

}
