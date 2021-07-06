#include <BitmapFilters/AnimeFilter.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>

#include <gtest/gtest.h>

#include <iostream>

using namespace std;

#define APRG_BITMAP_FILTERS_BITMAP_DIRECTORY APRG_DIR R"(AprgBitmapFilters\SampleBitmaps\)"

namespace alba
{

namespace AprgBitmap
{

TEST(AnimeFilterTest, DISABLED_AnimizeMultipleFilesTest)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler inputDirectory(bitmapDirectory.getDirectory()+R"(AnimizeMultipleFilesTest\input2\)");
    ListOfPaths inputSubDirectories;
    ListOfPaths inputFiles;
    inputDirectory.findFilesAndDirectoriesOneDepth("*.*", inputFiles, inputSubDirectories);

    for(string const& inputFile : inputFiles)
    {
        AlbaLocalPathHandler inputFilePathHandler(inputFile);
        AlbaLocalPathHandler outputFilePathHandler(bitmapDirectory.getDirectory()+R"(AnimizeMultipleFilesTest\output2\Out_)"+inputFilePathHandler.getFile());
        animize(inputFilePathHandler.getFullPath(), outputFilePathHandler.getFullPath());
        cout << "Finished: " << outputFilePathHandler.getFullPath() << endl;
    }
}

TEST(AnimeFilterTest, AnimizeSingleFileTest)
{
    AlbaLocalPathHandler bitmapDirectory(APRG_BITMAP_FILTERS_BITMAP_DIRECTORY);
    AlbaLocalPathHandler inputFilePathHandler(bitmapDirectory.getDirectory()+R"(NonAnimeBitmaps\GilmoreGirls.bmp)");
    AlbaLocalPathHandler outputFilePathHandler(bitmapDirectory.getDirectory()+R"(NonAnimeBitmaps\GilmoreGirls_Animized.bmp)");
    animize(inputFilePathHandler.getFullPath(), outputFilePathHandler.getFullPath());
}

}

}
