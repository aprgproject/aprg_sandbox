#include <PathHandlers/AlbaWebPathHandler.hpp>

#include <gtest/gtest.h>

#include <fstream>
#include <string>

using namespace std;
using namespace alba;

TEST(WebPathTest, DirectoryWithColonAndFileGivenAndNoProtocol)
{
    AlbaWebPathHandler pathHandler(R"(\\::://directory!@#$%12345\\\\/\\\\/file.txt)");
    EXPECT_FALSE(pathHandler.hasProtocol());
    EXPECT_TRUE(pathHandler.getProtocol().empty());
    EXPECT_EQ(R"(\\::://directory!@#$%12345/)", pathHandler.getDirectory());
    EXPECT_EQ("file.txt", pathHandler.getFile());
    EXPECT_EQ("file", pathHandler.getFilenameOnly());
    EXPECT_EQ("txt", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
}

TEST(WebPathTest, FullPathWithOnlyDirectoryGiven_HttpStyleInput)
{
    AlbaWebPathHandler pathHandler(R"(hTTp://www.google.com\\\\/\\\\/!@#$%12345\\///)");
    EXPECT_TRUE(pathHandler.hasProtocol());
    EXPECT_EQ("http", pathHandler.getProtocol());
    EXPECT_EQ("hTTp://www.google.com/!@#$%12345/", pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
}

TEST(WebPathTest, FullPathWithQuestionMark)
{
    AlbaWebPathHandler pathHandler("http://a.mhcdn.net/store/manga/12114/001.0/compressed/r049.jpg?v=1354256522");
    EXPECT_TRUE(pathHandler.hasProtocol());
    EXPECT_EQ("http", pathHandler.getProtocol());
    EXPECT_EQ("http://a.mhcdn.net/store/manga/12114/001.0/compressed/", pathHandler.getDirectory());
    EXPECT_EQ("r049.jpg", pathHandler.getFile());
    EXPECT_EQ("r049", pathHandler.getFilenameOnly());
    EXPECT_EQ("jpg", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
}

TEST(WebPathTest, GotoLinkWhenNoProtocolIsGiven)
{
    AlbaWebPathHandler pathHandler(R"(hTTp://www.google.com\\\\/\\\\/!@#$%12345\\///NewFile1.txt)");
    pathHandler.gotoLink(R"(NewDirectory1\NewFile2.ext)");

    EXPECT_TRUE(pathHandler.hasProtocol());
    EXPECT_EQ("http", pathHandler.getProtocol());
    EXPECT_EQ("hTTp://www.google.com/!@#$%12345/NewDirectory1/", pathHandler.getDirectory());
    EXPECT_EQ("NewFile2.ext", pathHandler.getFile());
    EXPECT_EQ("NewFile2", pathHandler.getFilenameOnly());
    EXPECT_EQ("ext", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
}

TEST(WebPathTest, GotoLinkWhenWithProtocolIsGiven)
{
    AlbaWebPathHandler pathHandler(R"(hTTp://www.google.com\\\\/\\\\/!@#$%12345\\///)");
    pathHandler.gotoLink(R"(ftP://www.yahoo.com\NewDirectory1\\NewFile2.ext)");

    EXPECT_TRUE(pathHandler.hasProtocol());
    EXPECT_EQ("ftp", pathHandler.getProtocol());
    EXPECT_EQ("ftP://www.yahoo.com/NewDirectory1/", pathHandler.getDirectory());
    EXPECT_EQ("NewFile2.ext", pathHandler.getFile());
    EXPECT_EQ("NewFile2", pathHandler.getFilenameOnly());
    EXPECT_EQ("ext", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
}
