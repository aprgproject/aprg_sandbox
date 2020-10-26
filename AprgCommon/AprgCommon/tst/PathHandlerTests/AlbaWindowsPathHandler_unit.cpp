#include <PathHandlers/AlbaWindowsPathHandler.hpp>

#include <fstream>
#include <gtest/gtest.h>
#include <string>

using namespace std;
using namespace alba;

#define APRG_DIR_SIMPLFIED R"(C:\APRG)"
#define ALBA_PATH_HANDLER_SIZE_TEST_FILE APRG_DIR R"(\AprgCommon\AprgCommon\tst\FilesForTests\FileReaderTest\Test2_SizeTest.txt)"

TEST(WindowsPathTest, FullPathWithOnlyDirectoryGiven_WindowsStyleInput)
{
    AlbaWindowsPathHandler pathHandler(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\)");
    EXPECT_EQ("C", pathHandler.getDriveOrRoot());
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\)", pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
}

TEST(WindowsPathTest, FullPathWithOnlyDirectoryGiven_JumbledSlashes)
{
    AlbaWindowsPathHandler pathHandler(APRG_DIR_SIMPLFIED R"(////AprgCommon\\\\/AprgCommon/tst\FilesForTests\)");
    EXPECT_EQ("C", pathHandler.getDriveOrRoot());
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\)", pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
}

TEST(WindowsPathTest, FullPathWithOnlyDirectoryGiven_WithNumbersAndSpecialCharacters)
{
    AlbaWindowsPathHandler pathHandler(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)");
    EXPECT_EQ("APRG_DRIVE", pathHandler.getDriveOrRoot());
    EXPECT_EQ(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)", pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
}

TEST(WindowsPathTest, FullPathWithDirectoryAndFileGiven_WithNumbersAndSpecialCharacters)
{
    AlbaWindowsPathHandler pathHandler(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\zxcvbnm12345.txt)");
    EXPECT_EQ("APRG_DRIVE", pathHandler.getDriveOrRoot());
    EXPECT_EQ(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)", pathHandler.getDirectory());
    EXPECT_EQ("zxcvbnm12345.txt", pathHandler.getFile());
    EXPECT_EQ("zxcvbnm12345", pathHandler.getFilenameOnly());    EXPECT_EQ("txt", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
}

TEST(WindowsPathTest, FullPathWithDirectoryAndFileNoFileExtensionGiven_WithNumbersAndSpecialCharacters)
{
    AlbaWindowsPathHandler pathHandler(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\zxcvbnm12345.)");
    EXPECT_EQ("APRG_DRIVE", pathHandler.getDriveOrRoot());
    EXPECT_EQ(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)", pathHandler.getDirectory());
    EXPECT_EQ("zxcvbnm12345.", pathHandler.getFile());
    EXPECT_EQ("zxcvbnm12345", pathHandler.getFilenameOnly());    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
}

TEST(WindowsPathTest, FullPathWithDirectoryAndFileExtensionOnlyGiven_WithNumbersAndSpecialCharacters)
{
    AlbaWindowsPathHandler pathHandler(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\.zxcvbnm12345)");
    EXPECT_EQ("APRG_DRIVE", pathHandler.getDriveOrRoot());
    EXPECT_EQ(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)", pathHandler.getDirectory());
    EXPECT_EQ(".zxcvbnm12345", pathHandler.getFile());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());    EXPECT_EQ("zxcvbnm12345", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
}

TEST(WindowsPathTest, FullPathWithDirectoryAndFileNoFileExtensionGiven_WithNumbersAndSpecialCharactersTwoTimes)
{
    AlbaWindowsPathHandler pathHandler(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\Aprg1111Common\tst\76543.txt)");
    EXPECT_EQ("APRG_DRIVE", pathHandler.getDriveOrRoot());
    EXPECT_EQ(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\Aprg1111Common\tst\)", pathHandler.getDirectory());
    EXPECT_EQ("76543.txt", pathHandler.getFile());
    EXPECT_EQ("76543", pathHandler.getFilenameOnly());    EXPECT_EQ("txt", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());

    pathHandler.input(R"(e:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\.zxcvbnm12345)");
    EXPECT_EQ("E", pathHandler.getDriveOrRoot());
    EXPECT_EQ(R"(e:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)", pathHandler.getDirectory());
    EXPECT_EQ(".zxcvbnm12345", pathHandler.getFile());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());    EXPECT_EQ("zxcvbnm12345", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
}

TEST(WindowsPathTest, FullPathWithDirectoryAndFile_DoublePeriodInPath)
{
    AlbaWindowsPathHandler pathHandler(APRG_DIR_SIMPLFIED R"(\..\dir\file.txt)");
    EXPECT_EQ("C", pathHandler.getDriveOrRoot());
    EXPECT_EQ(R"(C:\dir\)", pathHandler.getDirectory());
    EXPECT_EQ("file.txt", pathHandler.getFile());
    EXPECT_EQ("file", pathHandler.getFilenameOnly());    EXPECT_EQ("txt", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());

    pathHandler.input(APRG_DIR_SIMPLFIED R"(\dir\..\..\file.txt)");
    EXPECT_EQ("C", pathHandler.getDriveOrRoot());
    EXPECT_EQ(R"(C:\)", pathHandler.getDirectory());
    EXPECT_EQ("file.txt", pathHandler.getFile());
    EXPECT_EQ("file", pathHandler.getFilenameOnly());    EXPECT_EQ("txt", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());

    pathHandler.input(APRG_DIR_SIMPLFIED R"(\dir\..\dir2\dir3\..\file.txt)");
    EXPECT_EQ("C", pathHandler.getDriveOrRoot());
    EXPECT_EQ(pathHandler.getDirectory(), APRG_DIR_SIMPLFIED R"(\dir2\)");
    EXPECT_EQ(pathHandler.getFile(), "file.txt");
    EXPECT_EQ(pathHandler.getFilenameOnly(), "file");    EXPECT_EQ(pathHandler.getExtension(), "txt");
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
}

TEST(WindowsPathTest, FullPathWithDirectoryAndFile_ActualLocalDirectory)
{
    AlbaWindowsPathHandler pathHandler(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File1.log)");
    EXPECT_EQ("C", pathHandler.getDriveOrRoot());
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\)", pathHandler.getDirectory());
    EXPECT_EQ("File1.log", pathHandler.getFile());
    EXPECT_EQ("File1", pathHandler.getFilenameOnly());    EXPECT_EQ("log", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.isFoundInLocalSystem());

    pathHandler.input(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\thisFileDoesNotExist.txt)");
    EXPECT_EQ("C", pathHandler.getDriveOrRoot());
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\)", pathHandler.getDirectory());
    EXPECT_EQ("thisFileDoesNotExist.txt", pathHandler.getFile());
    EXPECT_EQ("thisFileDoesNotExist", pathHandler.getFilenameOnly());    EXPECT_EQ("txt", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    EXPECT_FALSE(pathHandler.isFoundInLocalSystem());

    pathHandler.input(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests)");
    EXPECT_EQ("C", pathHandler.getDriveOrRoot());
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\)", pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.isFoundInLocalSystem());

    pathHandler.input(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\)");
    EXPECT_EQ("C", pathHandler.getDriveOrRoot());
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\)", pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.isFoundInLocalSystem());
}
TEST(WindowsPathTest, ReInputFileThatIsToBeDeleted_ActualLocalDirectory)
{
    string const pathOfFileToBeDeleted(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\FileToBeDeleted.log)");
    std::ofstream fileToBeDeleted(pathOfFileToBeDeleted);
    fileToBeDeleted.close();

    AlbaWindowsPathHandler pathHandler(pathOfFileToBeDeleted);
    EXPECT_EQ("C", pathHandler.getDriveOrRoot());
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\)", pathHandler.getDirectory());
    EXPECT_EQ("FileToBeDeleted.log", pathHandler.getFile());
    EXPECT_EQ("FileToBeDeleted", pathHandler.getFilenameOnly());    EXPECT_EQ("log", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.isFoundInLocalSystem());

    EXPECT_TRUE(pathHandler.deleteFile());

    EXPECT_EQ("C", pathHandler.getDriveOrRoot());
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\)", pathHandler.getDirectory());
    EXPECT_EQ("FileToBeDeleted.log", pathHandler.getFile());
    EXPECT_EQ("FileToBeDeleted", pathHandler.getFilenameOnly());    EXPECT_EQ("log", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    EXPECT_FALSE(pathHandler.isFoundInLocalSystem());
}
TEST(WindowsPathTest, ReInputFileThatIsToBeRenamed_ActualLocalDirectory)
{
    string const pathOfFileToBeRenamed(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\FileToBeRenamed.log)");
    std::ofstream fileToBeDeleted(pathOfFileToBeRenamed);
    fileToBeDeleted.close();

    AlbaWindowsPathHandler pathHandler(pathOfFileToBeRenamed);
    EXPECT_EQ("C", pathHandler.getDriveOrRoot());
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\)", pathHandler.getDirectory());
    EXPECT_EQ("FileToBeRenamed.log", pathHandler.getFile());
    EXPECT_EQ("FileToBeRenamed", pathHandler.getFilenameOnly());    EXPECT_EQ("log", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.isFoundInLocalSystem());

    EXPECT_TRUE(pathHandler.renameFile("RenamedFile.txt"));

    EXPECT_EQ("C", pathHandler.getDriveOrRoot());
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\)", pathHandler.getDirectory());
    EXPECT_EQ("RenamedFile.txt", pathHandler.getFile());
    EXPECT_EQ("RenamedFile", pathHandler.getFilenameOnly());    EXPECT_EQ("txt", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.isFoundInLocalSystem());
    EXPECT_TRUE(pathHandler.deleteFile());
}

TEST(WindowsPathTest, ReInputDirectoryThatIsToBeRenamed_ActualLocalDirectory)
{
    string const pathOfDirectoryToBeRenamed(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR1)");

    AlbaWindowsPathHandler pathHandler(pathOfDirectoryToBeRenamed);
    EXPECT_EQ("C", pathHandler.getDriveOrRoot());
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR1\)",  pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.isFoundInLocalSystem());

    EXPECT_TRUE(pathHandler.renameImmediateDirectory("RenamedDirectory"));

    EXPECT_EQ("C", pathHandler.getDriveOrRoot());
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\RenamedDirectory\)", pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.isFoundInLocalSystem());

    EXPECT_TRUE(pathHandler.renameImmediateDirectory("DIR1"));

    EXPECT_EQ("C", pathHandler.getDriveOrRoot());
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR1\)", pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.isFoundInLocalSystem());
}
TEST(WindowsPathTest, FullPathWithDirectory_FindFileAndDirectoryOneDepth)
{
    AlbaWindowsPathHandler pathHandler(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\)");
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
    ASSERT_TRUE(pathHandler.isFoundInLocalSystem());

    set<string> listOfFiles;
    set<string> listOfDirectory;
    pathHandler.findFilesAndDirectoriesOneDepth("*.*", listOfFiles, listOfDirectory);
    ASSERT_EQ(5, listOfFiles.size());
    auto itFiles = listOfFiles.begin();
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File1.log)", *(itFiles++));
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File2.txt)", *(itFiles++));
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File3)", *(itFiles++));
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File4.mp3)", *(itFiles++));
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File5.avi)", *(itFiles++));
    ASSERT_EQ(6, listOfDirectory.size());
    auto itDirectories = listOfDirectory.begin();
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR1\)", *(itDirectories++));
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR2\)", *(itDirectories++));
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR3\)", *(itDirectories++));
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR4\)", *(itDirectories++));
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR5\)", *(itDirectories++));
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR6\)", *(itDirectories++));
}

TEST(WindowsPathTest, FullPathWithDirectory_FindFileAndDirectoryMultipleDepthTwo)
{
    AlbaWindowsPathHandler pathHandler(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\)");
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
    ASSERT_TRUE(pathHandler.isFoundInLocalSystem());

    set<string> listOfFiles;
    set<string> listOfDirectory;
    pathHandler.findFilesAndDirectoriesMultipleDepth("*.*", listOfFiles, listOfDirectory, 2);
    ASSERT_EQ(10, listOfFiles.size());
    auto itFiles = listOfFiles.begin();
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR1\File1.log)", *(itFiles++));
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR2\File2.txt)", *(itFiles++));
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR3\File3)", *(itFiles++));
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR4\File4.mp3)", *(itFiles++));
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR5\File5.avi)", *(itFiles++));
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File1.log)", *(itFiles++));
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File2.txt)", *(itFiles++));
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File3)", *(itFiles++));
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File4.mp3)", *(itFiles++));
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File5.avi)", *(itFiles++));
    ASSERT_EQ(7, listOfDirectory.size());
    auto itDirectories = listOfDirectory.begin();
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR1\)", *(itDirectories++));
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR2\)", *(itDirectories++));
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR3\)", *(itDirectories++));
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR4\)", *(itDirectories++));
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR5\)", *(itDirectories++));
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR6\)", *(itDirectories++));
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR6\SUBDIR1\)", *(itDirectories++));
}

TEST(WindowsPathTest, FullPathWithDirectory_FindFileAndDirectoryUnlimitedDepth)
{
    AlbaWindowsPathHandler pathHandler(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\)");
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
    ASSERT_TRUE(pathHandler.isFoundInLocalSystem());

    set<string> listOfFiles;
    set<string> listOfDirectory;
    pathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", listOfFiles, listOfDirectory);
    ASSERT_EQ(11, listOfFiles.size());
    auto itFiles = listOfFiles.begin();
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR1\File1.log)", *(itFiles++));
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR2\File2.txt)", *(itFiles++));
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR3\File3)", *(itFiles++));
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR4\File4.mp3)", *(itFiles++));
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR5\File5.avi)", *(itFiles++));
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR6\SUBDIR1\File6.jpg)", *(itFiles++));
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File1.log)", *(itFiles++));
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File2.txt)", *(itFiles++));
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File3)", *(itFiles++));
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File4.mp3)", *(itFiles++));
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File5.avi)", *(itFiles++));
    ASSERT_EQ(7, listOfDirectory.size());
    auto itDirectories = listOfDirectory.begin();
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR1\)", *(itDirectories++));
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR2\)", *(itDirectories++));
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR3\)", *(itDirectories++));
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR4\)", *(itDirectories++));
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR5\)", *(itDirectories++));
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR6\)", *(itDirectories++));
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\DIR6\SUBDIR1\)", *(itDirectories++));
}

TEST(WindowsPathTest, FullPathWithDirectory_FindFileAndDirectoryUnlimitedDepthWithWildCard)
{
    AlbaWindowsPathHandler pathHandler(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\)");
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
    ASSERT_TRUE(pathHandler.isFoundInLocalSystem());

    set<string> listOfFiles;
    set<string> listOfDirectory;
    pathHandler.findFilesAndDirectoriesUnlimitedDepth("*.log", listOfFiles, listOfDirectory);
    ASSERT_EQ(1, listOfFiles.size());
    auto itFiles = listOfFiles.begin();
    EXPECT_EQ(APRG_DIR_SIMPLFIED R"(\AprgCommon\AprgCommon\tst\FilesForTests\DirectoryTest\File1.log)", *(itFiles++));
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
    AlbaWindowsPathHandler pathHandler(PathInitialValueSource::DetectedLocalPath);

    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    ASSERT_TRUE(pathHandler.isFoundInLocalSystem());    cout<<"SetCurrentDirectoryFromWindows:"<<pathHandler.getFullPath()<<endl;
}