#include "gtest/gtest.h"
#include <string>
#include "../src/PathHandlers/AlbaWebPathHandler.hpp"
#include "../src/PathHandlers/AlbaWindowsPathHandler.hpp"

using std::string;
using namespace alba;

#define SIZE_TEST_FILE R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\FileReaderTest\Test2_SizeTest.txt)"

TEST(PathTest, FullPathWithDirectoryAndFileGiven)
{
    AlbaPathHandler pathHandler(R"(\)");
    pathHandler.inputPath(R"(C:\APRG12345\Aprg!@#$%Common\Aprg1111Common\tst\76543.txt)");
    EXPECT_EQ(pathHandler.getDirectory(), R"(C:\APRG12345\Aprg!@#$%Common\Aprg1111Common\tst\)");
    EXPECT_EQ(pathHandler.getFile(), "76543.txt");
    EXPECT_EQ(pathHandler.getFilenameOnly(), "76543");
    EXPECT_EQ(pathHandler.getExtension(), "txt");
    EXPECT_EQ(pathHandler.getPathType(), PathType::File);
    EXPECT_EQ(pathHandler.getImmediateDirectoryName(), "tst");
}

TEST(PathTest, FileOnly)
{
    AlbaPathHandler pathHandler(R"(\)");
    pathHandler.inputPath("src");
    EXPECT_TRUE(pathHandler.getDirectory().empty());
    EXPECT_EQ(pathHandler.getFile(), "src");
    EXPECT_EQ(pathHandler.getFilenameOnly(), "src");
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(pathHandler.getPathType(), PathType::File);
    EXPECT_TRUE(pathHandler.getImmediateDirectoryName().empty());
}

TEST(PathTest, GoUpUntilLastFolder)
{
    AlbaPathHandler pathHandler(R"(\)");
    pathHandler.inputPath(R"(C:\APRG12345\Aprg!@#$%Common\Aprg1111Common\tst\76543.txt)");
    EXPECT_EQ(pathHandler.getFullPath(), R"(C:\APRG12345\Aprg!@#$%Common\Aprg1111Common\tst\76543.txt)");
    EXPECT_EQ(pathHandler.getPathType(), PathType::File);

    pathHandler.goUp();
    EXPECT_EQ(pathHandler.getFullPath(), R"(C:\APRG12345\Aprg!@#$%Common\Aprg1111Common\)");
    EXPECT_EQ(pathHandler.getPathType(), PathType::Directory);

    pathHandler.goUp();
    EXPECT_EQ(pathHandler.getFullPath(), R"(C:\APRG12345\Aprg!@#$%Common\)");
    EXPECT_EQ(pathHandler.getPathType(), PathType::Directory);

    pathHandler.goUp();
    EXPECT_EQ(pathHandler.getFullPath(), R"(C:\APRG12345\)");
    EXPECT_EQ(pathHandler.getPathType(), PathType::Directory);

    pathHandler.goUp();
    EXPECT_EQ(pathHandler.getFullPath(), R"(C:\)");
    EXPECT_EQ(pathHandler.getPathType(), PathType::Directory);

    pathHandler.goUp();
    EXPECT_EQ(pathHandler.getFullPath(), R"(C:\)");
    EXPECT_EQ(pathHandler.getPathType(), PathType::Directory);
}

TEST(WindowsPathTest, FullPathWithOnlyDirectoryGiven_WindowsStyleInput)
{
    AlbaWindowsPathHandler pathHandler;
    pathHandler.inputPath(R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\)");
    EXPECT_EQ(pathHandler.getDrive(), "C");
    EXPECT_EQ(pathHandler.getDirectory(), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\)");
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(pathHandler.getPathType(), PathType::Directory);
}

TEST(WindowsPathTest, FullPathWithOnlyDirectoryGiven_JumbledSlashes)
{
    AlbaWindowsPathHandler pathHandler;
    pathHandler.inputPath(R"(C:\APRG////AprgCommon\\\\/AprgCommon/tst\FilesForTests\)");
    EXPECT_EQ(pathHandler.getDrive(), "C");
    EXPECT_EQ(pathHandler.getDirectory(), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\)");
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(pathHandler.getPathType(), PathType::Directory);
}

TEST(WindowsPathTest, FullPathWithOnlyDirectoryGiven_WithNumbersAndSpecialCharacters)
{
    AlbaWindowsPathHandler pathHandler;
    pathHandler.inputPath(R"(C:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)");
    EXPECT_EQ(pathHandler.getDrive(), "C");
    EXPECT_EQ(pathHandler.getDirectory(), R"(C:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)");
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(pathHandler.getPathType(), PathType::Directory);
}

TEST(WebPathTest, DirectoryWithColonAndFileGivenAndNoProtocol)
{
    AlbaWebPathHandler pathHandler;
    pathHandler.inputPath(R"(\\::://directory!@#$%12345\\\\/\\\\/file.txt)");
    EXPECT_FALSE(pathHandler.hasProtocol());
    EXPECT_TRUE(pathHandler.getProtocol().empty());
    EXPECT_EQ(pathHandler.getDirectory(), R"(\\::://directory!@#$%12345/)");
    EXPECT_EQ(pathHandler.getFile(), "file.txt");
    EXPECT_EQ(pathHandler.getFilenameOnly(), "file");
    EXPECT_EQ(pathHandler.getExtension(), "txt");
    EXPECT_EQ(pathHandler.getPathType(), PathType::File);
}

TEST(WebPathTest, FullPathWithOnlyDirectoryGiven_HttpStyleInput)
{
    AlbaWebPathHandler pathHandler;
    pathHandler.inputPath(R"(hTTp://www.google.com\\\\/\\\\/!@#$%12345\\///)");
    EXPECT_TRUE(pathHandler.hasProtocol());
    EXPECT_EQ(pathHandler.getProtocol(), "http");
    EXPECT_EQ(pathHandler.getDirectory(), "hTTp://www.google.com/!@#$%12345/");
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(pathHandler.getPathType(), PathType::Directory);
}

TEST(WebPathTest, FullPathWithQuestionMark)
{
    AlbaWebPathHandler pathHandler;
    pathHandler.inputPath("http://a.mhcdn.net/store/manga/12114/001.0/compressed/r049.jpg?v=1354256522");
    EXPECT_TRUE(pathHandler.hasProtocol());
    EXPECT_EQ(pathHandler.getProtocol(), "http");
    EXPECT_EQ(pathHandler.getDirectory(), "http://a.mhcdn.net/store/manga/12114/001.0/compressed/");
    EXPECT_EQ(pathHandler.getFile(), "r049.jpg");
    EXPECT_EQ(pathHandler.getFilenameOnly(), "r049");
    EXPECT_EQ(pathHandler.getExtension(), "jpg");
    EXPECT_EQ(pathHandler.getPathType(), PathType::File);
}

TEST(WebPathTest, GotoLinkWhenNoProtocolIsGiven)
{
    AlbaWebPathHandler pathHandler;
    pathHandler.inputPath(R"(hTTp://www.google.com\\\\/\\\\/!@#$%12345\\///NewFile1.txt)");
    pathHandler.gotoLink(R"(NewDirectory1\NewFile2.ext)");

    EXPECT_TRUE(pathHandler.hasProtocol());
    EXPECT_EQ(pathHandler.getProtocol(), "http");
    EXPECT_EQ(pathHandler.getDirectory(), "hTTp://www.google.com/!@#$%12345/NewDirectory1/");
    EXPECT_EQ(pathHandler.getFile(), "NewFile2.ext");
    EXPECT_EQ(pathHandler.getFilenameOnly(), "NewFile2");
    EXPECT_EQ(pathHandler.getExtension(), "ext");
    EXPECT_EQ(pathHandler.getPathType(), PathType::File);
}

TEST(WebPathTest, GotoLinkWhenWithProtocolIsGiven)
{
    AlbaWebPathHandler pathHandler;
    pathHandler.inputPath(R"(hTTp://www.google.com\\\\/\\\\/!@#$%12345\\///)");
    pathHandler.gotoLink(R"(ftP://www.yahoo.com\NewDirectory1\\NewFile2.ext)");

    EXPECT_TRUE(pathHandler.hasProtocol());
    EXPECT_EQ(pathHandler.getProtocol(), "ftp");
    EXPECT_EQ(pathHandler.getDirectory(), "ftP://www.yahoo.com/NewDirectory1/");
    EXPECT_EQ(pathHandler.getFile(), "NewFile2.ext");
    EXPECT_EQ(pathHandler.getFilenameOnly(), "NewFile2");
    EXPECT_EQ(pathHandler.getExtension(), "ext");
    EXPECT_EQ(pathHandler.getPathType(), PathType::File);
}

TEST(WindowsPathTest, FullPathWithDirectoryAndFileGiven_WithNumbersAndSpecialCharacters)
{
    AlbaWindowsPathHandler pathHandler;
    pathHandler.inputPath(R"(C:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\zxcvbnm12345.txt)");
    EXPECT_EQ(pathHandler.getDrive(), "C");
    EXPECT_EQ(pathHandler.getDirectory(), R"(C:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)");
    EXPECT_EQ(pathHandler.getFile(), "zxcvbnm12345.txt");
    EXPECT_EQ(pathHandler.getFilenameOnly(), "zxcvbnm12345");
    EXPECT_EQ(pathHandler.getExtension(), "txt");
    EXPECT_EQ(pathHandler.getPathType(), PathType::File);
}

TEST(WindowsPathTest, FullPathWithDirectoryAndFileNoFileExtensionGiven_WithNumbersAndSpecialCharacters)
{
    AlbaWindowsPathHandler pathHandler;
    pathHandler.inputPath(R"(C:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\zxcvbnm12345.)");
    EXPECT_EQ(pathHandler.getDrive(), "C");
    EXPECT_EQ(pathHandler.getDirectory(), R"(C:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)");
    EXPECT_EQ(pathHandler.getFile(), "zxcvbnm12345.");
    EXPECT_EQ(pathHandler.getFilenameOnly(), "zxcvbnm12345");
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(pathHandler.getPathType(), PathType::File);
}

TEST(WindowsPathTest, FullPathWithDirectoryAndFileExtensionOnlyGiven_WithNumbersAndSpecialCharacters)
{
    AlbaWindowsPathHandler pathHandler;
    pathHandler.inputPath(R"(C:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\.zxcvbnm12345)");
    EXPECT_EQ(pathHandler.getDrive(), "C");
    EXPECT_EQ(pathHandler.getDirectory(), R"(C:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)");
    EXPECT_EQ(pathHandler.getFile(), ".zxcvbnm12345");
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_EQ(pathHandler.getExtension(), "zxcvbnm12345");
    EXPECT_EQ(pathHandler.getPathType(), PathType::File);
}

TEST(WindowsPathTest, FullPathWithDirectoryAndFileNoFileExtensionGiven_WithNumbersAndSpecialCharactersTwoTimes)
{
    AlbaWindowsPathHandler pathHandler;
    pathHandler.inputPath(R"(C:\APRG12345\Aprg!@#$%Common\Aprg1111Common\tst\76543.txt)");
    EXPECT_EQ(pathHandler.getDrive(), "C");
    EXPECT_EQ(pathHandler.getDirectory(), R"(C:\APRG12345\Aprg!@#$%Common\Aprg1111Common\tst\)");
    EXPECT_EQ(pathHandler.getFile(), "76543.txt");
    EXPECT_EQ(pathHandler.getFilenameOnly(), "76543");
    EXPECT_EQ(pathHandler.getExtension(), "txt");
    EXPECT_EQ(pathHandler.getPathType(), PathType::File);

    pathHandler.inputPath(R"(E:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\.zxcvbnm12345)");
    EXPECT_EQ(pathHandler.getDrive(), "E");
    EXPECT_EQ(pathHandler.getDirectory(), R"(E:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)");
    EXPECT_EQ(pathHandler.getFile(), ".zxcvbnm12345");
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_EQ(pathHandler.getExtension(), "zxcvbnm12345");
    EXPECT_EQ(pathHandler.getPathType(), PathType::File);
}

TEST(WindowsPathTest, FullPathWithDirectoryAndFile_DoublePeriodInPath)
{
    AlbaWindowsPathHandler pathHandler;
    pathHandler.inputPath(R"(C:\APRG\..\dir\file.txt)");
    EXPECT_EQ(pathHandler.getDrive(), "C");
    EXPECT_EQ(pathHandler.getDirectory(), R"(C:\dir\)");
    EXPECT_EQ(pathHandler.getFile(), "file.txt");
    EXPECT_EQ(pathHandler.getFilenameOnly(), "file");
    EXPECT_EQ(pathHandler.getExtension(), "txt");
    EXPECT_EQ(pathHandler.getPathType(), PathType::File);

    pathHandler.inputPath(R"(C:\APRG\dir\..\..\file.txt)");
    EXPECT_EQ(pathHandler.getDrive(), "C");
    EXPECT_EQ(pathHandler.getDirectory(), R"(C:\)");
    EXPECT_EQ(pathHandler.getFile(), "file.txt");
    EXPECT_EQ(pathHandler.getFilenameOnly(), "file");
    EXPECT_EQ(pathHandler.getExtension(), "txt");
    EXPECT_EQ(pathHandler.getPathType(), PathType::File);

    pathHandler.inputPath(R"(C:\APRG\dir\..\dir2\dir3\..\file.txt)");
    EXPECT_EQ(pathHandler.getDrive(), "C");
    EXPECT_EQ(pathHandler.getDirectory(), R"(C:\APRG\dir2\)");
    EXPECT_EQ(pathHandler.getFile(), "file.txt");
    EXPECT_EQ(pathHandler.getFilenameOnly(), "file");
    EXPECT_EQ(pathHandler.getExtension(), "txt");
    EXPECT_EQ(pathHandler.getPathType(), PathType::File);
}

TEST(WindowsPathTest, FullPathWithDirectoryAndFile_ActualLocalDirectory)
{
    AlbaWindowsPathHandler pathHandler;
    pathHandler.inputPath(R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File1.log)");
    EXPECT_EQ(pathHandler.getDrive(), "C");
    EXPECT_EQ(pathHandler.getDirectory(), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\)");
    EXPECT_EQ(pathHandler.getFile(), "File1.log");
    EXPECT_EQ(pathHandler.getFilenameOnly(), "File1");
    EXPECT_EQ(pathHandler.getExtension(), "log");
    EXPECT_EQ(pathHandler.getPathType(), PathType::File);
    EXPECT_EQ(pathHandler.isFoundInLocalSystem(), true);

    pathHandler.inputPath(R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\thisFileDoesNotExist.txt)");
    EXPECT_EQ(pathHandler.getDrive(), "C");
    EXPECT_EQ(pathHandler.getDirectory(), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\)");
    EXPECT_EQ(pathHandler.getFile(), "thisFileDoesNotExist.txt");
    EXPECT_EQ(pathHandler.getFilenameOnly(), "thisFileDoesNotExist");
    EXPECT_EQ(pathHandler.getExtension(), "txt");
    EXPECT_EQ(pathHandler.getPathType(), PathType::File);
    EXPECT_EQ(pathHandler.isFoundInLocalSystem(), false);

    pathHandler.inputPath(R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests)");
    EXPECT_EQ(pathHandler.getDrive(), "C");
    EXPECT_EQ(pathHandler.getDirectory(), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\)");
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(pathHandler.getPathType(), PathType::Directory);
    EXPECT_EQ(pathHandler.isFoundInLocalSystem(),true);

    pathHandler.inputPath(R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\)");
    EXPECT_EQ(pathHandler.getDrive(), "C");
    EXPECT_EQ(pathHandler.getDirectory(), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\)");
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(pathHandler.getPathType(), PathType::Directory);
    EXPECT_EQ(pathHandler.isFoundInLocalSystem(),true);
}

TEST(WindowsPathTest, FullPathWithDirectory_FindFileAndDirectoryOneDepth)
{
    AlbaWindowsPathHandler pathHandler;
    pathHandler.inputPath(R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\)");
    ASSERT_EQ(pathHandler.getPathType(), PathType::Directory);
    ASSERT_EQ(pathHandler.isFoundInLocalSystem(), true);

    set<string> listOfFiles;
    set<string> listOfDirectory;
    pathHandler.findFilesAndDirectoriesOneDepth("*.*", listOfFiles, listOfDirectory);
    ASSERT_EQ(listOfFiles.size(), 5);
    auto itFiles = listOfFiles.begin();
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File1.log)");
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File2.txt)");
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File3)");
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File4.mp3)");
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File5.avi)");
    ASSERT_EQ(listOfDirectory.size(), 6);
    auto itDirectories = listOfDirectory.begin();
    EXPECT_EQ(*(itDirectories++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR1\)");
    EXPECT_EQ(*(itDirectories++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR2\)");
    EXPECT_EQ(*(itDirectories++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR3\)");
    EXPECT_EQ(*(itDirectories++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR4\)");
    EXPECT_EQ(*(itDirectories++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR5\)");
    EXPECT_EQ(*(itDirectories++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR6\)");
}

TEST(WindowsPathTest, FullPathWithDirectory_FindFileAndDirectoryMultipleDepthTwo)
{
    AlbaWindowsPathHandler pathHandler;
    pathHandler.inputPath(R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\)");
    ASSERT_EQ(pathHandler.getPathType(), PathType::Directory);
    ASSERT_EQ(pathHandler.isFoundInLocalSystem(), true);

    set<string> listOfFiles;
    set<string> listOfDirectory;
    pathHandler.findFilesAndDirectoriesMultipleDepth("*.*", listOfFiles, listOfDirectory, 2);
    ASSERT_EQ(listOfFiles.size(), 10);
    auto itFiles = listOfFiles.begin();
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR1\File1.log)");
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR2\File2.txt)");
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR3\File3)");
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR4\File4.mp3)");
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR5\File5.avi)");
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File1.log)");
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File2.txt)");
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File3)");
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File4.mp3)");
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File5.avi)");
    ASSERT_EQ(listOfDirectory.size(), 7);
    auto itDirectories = listOfDirectory.begin();
    EXPECT_EQ(*(itDirectories++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR1\)");
    EXPECT_EQ(*(itDirectories++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR2\)");
    EXPECT_EQ(*(itDirectories++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR3\)");
    EXPECT_EQ(*(itDirectories++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR4\)");
    EXPECT_EQ(*(itDirectories++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR5\)");
    EXPECT_EQ(*(itDirectories++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR6\)");
    EXPECT_EQ(*(itDirectories++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR6\SUBDIR1\)");
}

TEST(WindowsPathTest, FullPathWithDirectory_FindFileAndDirectoryUnlimitedDepth)
{
    AlbaWindowsPathHandler pathHandler;
    pathHandler.inputPath(R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\)");
    ASSERT_EQ(pathHandler.getPathType(), PathType::Directory);
    ASSERT_EQ(pathHandler.isFoundInLocalSystem(), true);

    set<string> listOfFiles;
    set<string> listOfDirectory;
    pathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", listOfFiles, listOfDirectory);
    ASSERT_EQ(listOfFiles.size(), 11);
    auto itFiles = listOfFiles.begin();
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR1\File1.log)");
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR2\File2.txt)");
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR3\File3)");
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR4\File4.mp3)");
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR5\File5.avi)");
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR6\SUBDIR1\File6.jpg)");
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File1.log)");
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File2.txt)");
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File3)");
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File4.mp3)");
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File5.avi)");
    ASSERT_EQ(listOfDirectory.size(), 7);
    auto itDirectories = listOfDirectory.begin();
    EXPECT_EQ(*(itDirectories++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR1\)");
    EXPECT_EQ(*(itDirectories++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR2\)");
    EXPECT_EQ(*(itDirectories++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR3\)");
    EXPECT_EQ(*(itDirectories++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR4\)");
    EXPECT_EQ(*(itDirectories++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR5\)");
    EXPECT_EQ(*(itDirectories++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR6\)");
    EXPECT_EQ(*(itDirectories++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR6\SUBDIR1\)");
}

TEST(WindowsPathTest, FullPathWithDirectory_FindFileAndDirectoryUnlimitedDepthWithWildCard)
{
    AlbaWindowsPathHandler pathHandler;
    pathHandler.inputPath(R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\)");
    ASSERT_EQ(pathHandler.getPathType(), PathType::Directory);
    ASSERT_EQ(pathHandler.isFoundInLocalSystem(), true);

    set<string> listOfFiles;
    set<string> listOfDirectory;
    pathHandler.findFilesAndDirectoriesUnlimitedDepth("*.log", listOfFiles, listOfDirectory);
    ASSERT_EQ(listOfFiles.size(), 1);
    auto itFiles = listOfFiles.begin();
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File1.log)");
    ASSERT_EQ(listOfDirectory.size(), 0);
}

TEST(WindowsPathTest, FileSizeTest)
{
    AlbaWindowsPathHandler pathHandler;
    pathHandler.inputPath(SIZE_TEST_FILE);

    ASSERT_EQ(pathHandler.getPathType(), PathType::File);
    ASSERT_EQ(pathHandler.isFoundInLocalSystem(), true);
    EXPECT_DOUBLE_EQ(pathHandler.getFileSizeEstimate(), 5000);
}

TEST(WindowsPathTest, DISABLED_ActualTest)
{
    AlbaWindowsPathHandler pathHandler;
    pathHandler.inputPath(R"(C:\APRG\tcom_flexi3-trunk-cchh\I_Interface\Application_Env\Definitions\)");
    ASSERT_EQ(pathHandler.getPathType(), PathType::Directory);
    ASSERT_EQ(pathHandler.isFoundInLocalSystem(), true);

    set<string> listOfFiles;
    set<string> listOfDirectory;
    pathHandler.findFilesAndDirectoriesOneDepth("TCellId.h", listOfFiles, listOfDirectory);
    ASSERT_EQ(listOfFiles.size(), 1);
    auto itFiles = listOfFiles.begin();
    EXPECT_EQ(*(itFiles++), R"(C:\APRG\tcom_flexi3-trunk-cchh\I_Interface\Application_Env\Definitions\TCellId.h)");
}
