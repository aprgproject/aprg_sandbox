#include <AprgColorStatistics.hpp>

#include <PathHandlers/AlbaLocalPathHandler.hpp>

#include <gtest/gtest.h>

using namespace std;

#define APRG_BITMAP_FILTERS_BITMAP_DIRECTORY APRG_DIR R"(AprgBitmapFilters\AprgBitmapFilters\tst\Bitmaps\)"

namespace alba
{

TEST(ColorStatisticsTest, GatherAndSaveStatistics)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);

    gatherAndSaveColorStatistics(bitmapDirectory.getDirectory()+R"(NonAnimeBitmaps\JohnMayerDark.bmp)");
}

}
