#include <PathHandlers/AlbaPathHandler.hpp>

#include <gtest/gtest.h>

#include <fstream>
#include <string>

using namespace std;using namespace alba;

TEST(PathTest, FullPathWithDirectoryAndFileGiven)
{    AlbaPathHandler pathHandler(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\Aprg1111Common\tst\76543.txt)", R"(\)");
    EXPECT_EQ(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\Aprg1111Common\tst\)", pathHandler.getDirectory());
    EXPECT_EQ("76543.txt", pathHandler.getFile());
    EXPECT_EQ("76543", pathHandler.getFilenameOnly());
    EXPECT_EQ("txt", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    EXPECT_EQ("tst", pathHandler.getImmediateDirectoryName());
}

TEST(PathTest, FileOnly)
{
    AlbaPathHandler pathHandler("src", R"(\)");
    EXPECT_TRUE(pathHandler.getDirectory().empty());
    EXPECT_EQ("src", pathHandler.getFile());
    EXPECT_EQ("src", pathHandler.getFilenameOnly());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.getImmediateDirectoryName().empty());
}

TEST(PathTest, ReInputFile)
{
    AlbaPathHandler pathHandler("src", R"(\)");
    pathHandler.reInput();
    EXPECT_TRUE(pathHandler.getDirectory().empty());
    EXPECT_EQ("src", pathHandler.getFile());
    EXPECT_EQ("src", pathHandler.getFilenameOnly());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.getImmediateDirectoryName().empty());
}

TEST(PathTest, GoUpUntilLastFolder)
{
    AlbaPathHandler pathHandler(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\Aprg1111Common\tst\76543.txt)", R"(\)");
    EXPECT_EQ(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\Aprg1111Common\tst\76543.txt)", pathHandler.getFullPath());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());

    pathHandler.goUp();
    EXPECT_EQ(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\Aprg1111Common\)", pathHandler.getFullPath());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());

    pathHandler.goUp();
    EXPECT_EQ(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\)", pathHandler.getFullPath());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());

    pathHandler.goUp();
    EXPECT_EQ(R"(APRG_DRIVE:\APRG12345\)", pathHandler.getFullPath());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());

    pathHandler.goUp();
    EXPECT_EQ(R"(APRG_DRIVE:\)", pathHandler.getFullPath());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());

    pathHandler.goUp();
    EXPECT_EQ(R"(APRG_DRIVE:\)", pathHandler.getFullPath());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
}
