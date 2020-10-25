#include <PathHandlers/AlbaWebPathHandler.hpp>
#include <PathHandlers/AlbaWindowsPathHandler.hpp>

#include <fstream>
#include <gtest/gtest.h>
#include <string>

using namespace std;
using namespace alba;

#define ALBA_PATH_HANDLER_SIZE_TEST_FILE APRG_DIR R"(\AprgCommon\AprgCommon\tst\FilesForTests\FileReaderTest\Test2_SizeTest.txt)"

TEST(PathTest, FullPathWithDirectoryAndFileGiven)
{
    AlbaPathHandler pathHandler(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\Aprg1111Common\tst\76543.txt)", R"(\)");
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

TEST(WindowsPathTest, FullPathWithOnlyDirectoryGiven_WindowsStyleInput)
{
    AlbaWindowsPathHandler pathHandler(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\)");
    EXPECT_EQ("C", pathHandler.getDrive());
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\)", pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
}

TEST(WindowsPathTest, FullPathWithOnlyDirectoryGiven_JumbledSlashes)
{
    AlbaWindowsPathHandler pathHandler(R"(APRG_DRIVE:\APRG////AprgCommon\\\\/AprgCommon/tst\FilesForTests\)");
    EXPECT_EQ("C", pathHandler.getDrive());
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\)", pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
}

TEST(WindowsPathTest, FullPathWithOnlyDirectoryGiven_WithNumbersAndSpecialCharacters)
{
    AlbaWindowsPathHandler pathHandler(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)");
    EXPECT_EQ("C", pathHandler.getDrive());
    EXPECT_EQ(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)", pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
}

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

TEST(WindowsPathTest, FullPathWithDirectoryAndFileGiven_WithNumbersAndSpecialCharacters)
{
    AlbaWindowsPathHandler pathHandler(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\zxcvbnm12345.txt)");
    EXPECT_EQ("C", pathHandler.getDrive());
    EXPECT_EQ(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)", pathHandler.getDirectory());
    EXPECT_EQ("zxcvbnm12345.txt", pathHandler.getFile());
    EXPECT_EQ("zxcvbnm12345", pathHandler.getFilenameOnly());
    EXPECT_EQ("txt", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
}

TEST(WindowsPathTest, FullPathWithDirectoryAndFileNoFileExtensionGiven_WithNumbersAndSpecialCharacters)
{
    AlbaWindowsPathHandler pathHandler(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\zxcvbnm12345.)");
    EXPECT_EQ("C", pathHandler.getDrive());
    EXPECT_EQ(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)", pathHandler.getDirectory());
    EXPECT_EQ("zxcvbnm12345.", pathHandler.getFile());
    EXPECT_EQ("zxcvbnm12345", pathHandler.getFilenameOnly());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
}

TEST(WindowsPathTest, FullPathWithDirectoryAndFileExtensionOnlyGiven_WithNumbersAndSpecialCharacters)
{
    AlbaWindowsPathHandler pathHandler(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\.zxcvbnm12345)");
    EXPECT_EQ("C", pathHandler.getDrive());
    EXPECT_EQ(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)", pathHandler.getDirectory());
    EXPECT_EQ(".zxcvbnm12345", pathHandler.getFile());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_EQ("zxcvbnm12345", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
}

TEST(WindowsPathTest, FullPathWithDirectoryAndFileNoFileExtensionGiven_WithNumbersAndSpecialCharactersTwoTimes)
{
    AlbaWindowsPathHandler pathHandler(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\Aprg1111Common\tst\76543.txt)");
    EXPECT_EQ("C", pathHandler.getDrive());
    EXPECT_EQ(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\Aprg1111Common\tst\)", pathHandler.getDirectory());
    EXPECT_EQ("76543.txt", pathHandler.getFile());
    EXPECT_EQ("76543", pathHandler.getFilenameOnly());
    EXPECT_EQ("txt", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());

    pathHandler.input(R"(e:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\.zxcvbnm12345)");
    EXPECT_EQ("E", pathHandler.getDrive());
    EXPECT_EQ(R"(e:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)", pathHandler.getDirectory());
    EXPECT_EQ(".zxcvbnm12345", pathHandler.getFile());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_EQ("zxcvbnm12345", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
}

TEST(WindowsPathTest, FullPathWithDirectoryAndFile_DoublePeriodInPath)
{
    AlbaWindowsPathHandler pathHandler(R"(APRG_DRIVE:\APRG\..\dir\file.txt)");
    EXPECT_EQ("C", pathHandler.getDrive());
    EXPECT_EQ(R"(C:\dir\)", pathHandler.getDirectory());
    EXPECT_EQ("file.txt", pathHandler.getFile());
    EXPECT_EQ("file", pathHandler.getFilenameOnly());
    EXPECT_EQ("txt", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());

    pathHandler.input(R"(APRG_DRIVE:\APRG\dir\..\..\file.txt)");
    EXPECT_EQ("C", pathHandler.getDrive());
    EXPECT_EQ(R"(C:\)", pathHandler.getDirectory());
    EXPECT_EQ("file.txt", pathHandler.getFile());
    EXPECT_EQ("file", pathHandler.getFilenameOnly());
    EXPECT_EQ("txt", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());

    pathHandler.input(R"(APRG_DRIVE:\APRG\dir\..\dir2\dir3\..\file.txt)");
    EXPECT_EQ("C", pathHandler.getDrive());
    EXPECT_EQ(pathHandler.getDirectory(), R"(APRG_DRIVE:\APRG\dir2\)");
    EXPECT_EQ(pathHandler.getFile(), "file.txt");
    EXPECT_EQ(pathHandler.getFilenameOnly(), "file");
    EXPECT_EQ(pathHandler.getExtension(), "txt");
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
}

TEST(WindowsPathTest, FullPathWithDirectoryAndFile_ActualLocalDirectory)
{
    AlbaWindowsPathHandler pathHandler(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File1.log)");
    EXPECT_EQ("C", pathHandler.getDrive());
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\)", pathHandler.getDirectory());
    EXPECT_EQ("File1.log", pathHandler.getFile());
    EXPECT_EQ("File1", pathHandler.getFilenameOnly());
    EXPECT_EQ("log", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.isFoundInLocalSystem());

    pathHandler.input(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\thisFileDoesNotExist.txt)");
    EXPECT_EQ("C", pathHandler.getDrive());
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\)", pathHandler.getDirectory());
    EXPECT_EQ("thisFileDoesNotExist.txt", pathHandler.getFile());
    EXPECT_EQ("thisFileDoesNotExist", pathHandler.getFilenameOnly());
    EXPECT_EQ("txt", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    EXPECT_FALSE(pathHandler.isFoundInLocalSystem());

    pathHandler.input(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests)");
    EXPECT_EQ("C", pathHandler.getDrive());
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\)", pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.isFoundInLocalSystem());

    pathHandler.input(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\)");
    EXPECT_EQ("C", pathHandler.getDrive());
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\)", pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.isFoundInLocalSystem());
}

TEST(WindowsPathTest, ReInputFileThatIsToBeDeleted_ActualLocalDirectory)
{
    string const pathOfFileToBeDeleted(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\FileToBeDeleted.log)");
    std::ofstream fileToBeDeleted(pathOfFileToBeDeleted);
    fileToBeDeleted.close();

    AlbaWindowsPathHandler pathHandler(pathOfFileToBeDeleted);
    EXPECT_EQ("C", pathHandler.getDrive());
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\)", pathHandler.getDirectory());
    EXPECT_EQ("FileToBeDeleted.log", pathHandler.getFile());
    EXPECT_EQ("FileToBeDeleted", pathHandler.getFilenameOnly());
    EXPECT_EQ("log", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.isFoundInLocalSystem());

    EXPECT_TRUE(pathHandler.deleteFile());

    EXPECT_EQ("C", pathHandler.getDrive());
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\)", pathHandler.getDirectory());
    EXPECT_EQ("FileToBeDeleted.log", pathHandler.getFile());
    EXPECT_EQ("FileToBeDeleted", pathHandler.getFilenameOnly());
    EXPECT_EQ("log", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    EXPECT_FALSE(pathHandler.isFoundInLocalSystem());
}

TEST(WindowsPathTest, ReInputFileThatIsToBeRenamed_ActualLocalDirectory)
{
    string const pathOfFileToBeRenamed(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\FileToBeRenamed.log)");
    std::ofstream fileToBeDeleted(pathOfFileToBeRenamed);
    fileToBeDeleted.close();

    AlbaWindowsPathHandler pathHandler(pathOfFileToBeRenamed);
    EXPECT_EQ("C", pathHandler.getDrive());
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\)", pathHandler.getDirectory());
    EXPECT_EQ("FileToBeRenamed.log", pathHandler.getFile());
    EXPECT_EQ("FileToBeRenamed", pathHandler.getFilenameOnly());
    EXPECT_EQ("log", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.isFoundInLocalSystem());

    EXPECT_TRUE(pathHandler.renameFile("RenamedFile.txt"));

    EXPECT_EQ("C", pathHandler.getDrive());
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\)", pathHandler.getDirectory());
    EXPECT_EQ("RenamedFile.txt", pathHandler.getFile());
    EXPECT_EQ("RenamedFile", pathHandler.getFilenameOnly());
    EXPECT_EQ("txt", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.isFoundInLocalSystem());

    EXPECT_TRUE(pathHandler.deleteFile());
}

TEST(WindowsPathTest, ReInputDirectoryThatIsToBeRenamed_ActualLocalDirectory)
{
    string const pathOfDirectoryToBeRenamed(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR1)");

    AlbaWindowsPathHandler pathHandler(pathOfDirectoryToBeRenamed);
    EXPECT_EQ("C", pathHandler.getDrive());
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR1\)",  pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.isFoundInLocalSystem());

    EXPECT_TRUE(pathHandler.renameImmediateDirectory("RenamedDirectory"));

    EXPECT_EQ("C", pathHandler.getDrive());
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\RenamedDirectory\)", pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.isFoundInLocalSystem());

    EXPECT_TRUE(pathHandler.renameImmediateDirectory("DIR1"));

    EXPECT_EQ("C", pathHandler.getDrive());
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR1\)", pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.isFoundInLocalSystem());
}

TEST(WindowsPathTest, FullPathWithDirectory_FindFileAndDirectoryOneDepth)
{
    AlbaWindowsPathHandler pathHandler(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\)");
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
    ASSERT_TRUE(pathHandler.isFoundInLocalSystem());

    set<string> listOfFiles;
    set<string> listOfDirectory;
    pathHandler.findFilesAndDirectoriesOneDepth("*.*", listOfFiles, listOfDirectory);
    ASSERT_EQ(5, listOfFiles.size());
    auto itFiles = listOfFiles.begin();
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File1.log)", *(itFiles++));
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File2.txt)", *(itFiles++));
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File3)", *(itFiles++));
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File4.mp3)", *(itFiles++));
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File5.avi)", *(itFiles++));
    ASSERT_EQ(6, listOfDirectory.size());
    auto itDirectories = listOfDirectory.begin();
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR1\)", *(itDirectories++));
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR2\)", *(itDirectories++));
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR3\)", *(itDirectories++));
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR4\)", *(itDirectories++));
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR5\)", *(itDirectories++));
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR6\)", *(itDirectories++));
}

TEST(WindowsPathTest, FullPathWithDirectory_FindFileAndDirectoryMultipleDepthTwo)
{
    AlbaWindowsPathHandler pathHandler(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\)");
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
    ASSERT_TRUE(pathHandler.isFoundInLocalSystem());

    set<string> listOfFiles;
    set<string> listOfDirectory;
    pathHandler.findFilesAndDirectoriesMultipleDepth("*.*", listOfFiles, listOfDirectory, 2);
    ASSERT_EQ(10, listOfFiles.size());
    auto itFiles = listOfFiles.begin();
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR1\File1.log)", *(itFiles++));
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR2\File2.txt)", *(itFiles++));
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR3\File3)", *(itFiles++));
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR4\File4.mp3)", *(itFiles++));
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR5\File5.avi)", *(itFiles++));
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File1.log)", *(itFiles++));
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File2.txt)", *(itFiles++));
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File3)", *(itFiles++));
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File4.mp3)", *(itFiles++));
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File5.avi)", *(itFiles++));
    ASSERT_EQ(7, listOfDirectory.size());
    auto itDirectories = listOfDirectory.begin();
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR1\)", *(itDirectories++));
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR2\)", *(itDirectories++));
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR3\)", *(itDirectories++));
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR4\)", *(itDirectories++));
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR5\)", *(itDirectories++));
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR6\)", *(itDirectories++));
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR6\SUBDIR1\)", *(itDirectories++));
}

TEST(WindowsPathTest, FullPathWithDirectory_FindFileAndDirectoryUnlimitedDepth)
{
    AlbaWindowsPathHandler pathHandler(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\)");
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
    ASSERT_TRUE(pathHandler.isFoundInLocalSystem());

    set<string> listOfFiles;
    set<string> listOfDirectory;
    pathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", listOfFiles, listOfDirectory);
    ASSERT_EQ(11, listOfFiles.size());
    auto itFiles = listOfFiles.begin();
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR1\File1.log)", *(itFiles++));
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR2\File2.txt)", *(itFiles++));
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR3\File3)", *(itFiles++));
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR4\File4.mp3)", *(itFiles++));
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR5\File5.avi)", *(itFiles++));
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR6\SUBDIR1\File6.jpg)", *(itFiles++));
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File1.log)", *(itFiles++));
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File2.txt)", *(itFiles++));
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File3)", *(itFiles++));
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File4.mp3)", *(itFiles++));
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File5.avi)", *(itFiles++));
    ASSERT_EQ(7, listOfDirectory.size());
    auto itDirectories = listOfDirectory.begin();
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR1\)", *(itDirectories++));
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR2\)", *(itDirectories++));
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR3\)", *(itDirectories++));
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR4\)", *(itDirectories++));
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR5\)", *(itDirectories++));
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR6\)", *(itDirectories++));
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR6\SUBDIR1\)", *(itDirectories++));
}

TEST(WindowsPathTest, FullPathWithDirectory_FindFileAndDirectoryUnlimitedDepthWithWildCard)
{
    AlbaWindowsPathHandler pathHandler(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\)");
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
    ASSERT_TRUE(pathHandler.isFoundInLocalSystem());

    set<string> listOfFiles;
    set<string> listOfDirectory;
    pathHandler.findFilesAndDirectoriesUnlimitedDepth("*.log", listOfFiles, listOfDirectory);
    ASSERT_EQ(1, listOfFiles.size());
    auto itFiles = listOfFiles.begin();
    EXPECT_EQ(R"(APRG_DRIVE:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File1.log)", *(itFiles++));
    ASSERT_EQ(listOfDirectory.size(), 0);
}

TEST(WindowsPathTest, FileSizeTest_FileIsNotExisting)
{
    AlbaWindowsPathHandler pathHandler("This path does not exist");

    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    ASSERT_FALSE(pathHandler.isFoundInLocalSystem());
    EXPECT_DOUBLE_EQ(0, pathHandler.getFileSizeEstimate());
}

TEST(WindowsPathTest, FileSizeTest_FileIsExisting)
{
    AlbaWindowsPathHandler pathHandler(ALBA_PATH_HANDLER_SIZE_TEST_FILE);

    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    ASSERT_TRUE(pathHandler.isFoundInLocalSystem());
    EXPECT_DOUBLE_EQ(5000, pathHandler.getFileSizeEstimate());
}

TEST(WindowsPathTest, SetCurrentDirectoryFromWindows)
{
    AlbaWindowsPathHandler pathHandler(AlbaWindowsPathHandler::InitialValue::DetectedLocalPath);

    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    ASSERT_TRUE(pathHandler.isFoundInLocalSystem());
    cout<<"SetCurrentDirectoryFromWindows:"<<pathHandler.getFullPath()<<endl;
}
