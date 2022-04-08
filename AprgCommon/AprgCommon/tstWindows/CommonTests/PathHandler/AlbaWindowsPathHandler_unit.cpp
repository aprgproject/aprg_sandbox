#include <Common/PathHandler/AlbaWindowsPathHandler.hpp>
#include <CommonTests/DirectoryConstants.hpp>
#include <CommonTests/PathHandler/AlbaWindowsPathHandlerTest.hpp>

#include <gtest/gtest.h>

#include <fstream>
#include <string>

using namespace std;

namespace alba
{

TEST_F(AlbaWindowsPathHandlerTest, FullPathWithOnlyDirectoryGiven_WindowsStyleInput)
{
    AlbaWindowsPathHandler pathHandler(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\)");
    EXPECT_EQ(getDriveOfAprgDir(), pathHandler.getDriveOrRoot());
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\)"), pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
}

TEST_F(AlbaWindowsPathHandlerTest, FullPathWithOnlyDirectoryGiven_JumbledSlashes)
{
    AlbaWindowsPathHandler pathHandler(pathOfAprgDirectory + R"(////AprgCommon\\\\\FilesForTests\)");
    EXPECT_EQ(getDriveOfAprgDir(), pathHandler.getDriveOrRoot());
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\)"), pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
}

TEST_F(AlbaWindowsPathHandlerTest, FullPathWithOnlyDirectoryGiven_JumbledSlashesWithDirectoryDoesNotExists)
{
    AlbaWindowsPathHandler pathHandler(APRG_DIR R"(\////AprgCommon\\\\/AprgCommon/tst\DirectoryDoesNotExists\)");
    EXPECT_EQ(getDriveOfAprgDir(), pathHandler.getDriveOrRoot());
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\AprgCommon\tst\DirectoryDoesNotExists\)"), pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
}

TEST_F(AlbaWindowsPathHandlerTest, FullPathWithOnlyDirectoryGiven_WithNumbersAndSpecialCharacters)
{
    AlbaWindowsPathHandler pathHandler(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)");
    EXPECT_EQ("APRG_DRIVE", pathHandler.getDriveOrRoot());
    EXPECT_EQ(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)", pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
}

TEST_F(AlbaWindowsPathHandlerTest, FullPathWithDirectoryAndFileGiven_WithNumbersAndSpecialCharacters)
{
    AlbaWindowsPathHandler pathHandler(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\zxcvbnm12345.txt)");
    EXPECT_EQ("APRG_DRIVE", pathHandler.getDriveOrRoot());
    EXPECT_EQ(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)", pathHandler.getDirectory());
    EXPECT_EQ("zxcvbnm12345.txt", pathHandler.getFile());
    EXPECT_EQ("zxcvbnm12345", pathHandler.getFilenameOnly());
    EXPECT_EQ("txt", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
}

TEST_F(AlbaWindowsPathHandlerTest, FullPathWithDirectoryAndFileNoFileExtensionGiven_WithNumbersAndSpecialCharacters)
{
    AlbaWindowsPathHandler pathHandler(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\zxcvbnm12345.)");
    EXPECT_EQ("APRG_DRIVE", pathHandler.getDriveOrRoot());
    EXPECT_EQ(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)", pathHandler.getDirectory());
    EXPECT_EQ("zxcvbnm12345.", pathHandler.getFile());
    EXPECT_EQ("zxcvbnm12345", pathHandler.getFilenameOnly());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
}

TEST_F(AlbaWindowsPathHandlerTest, FullPathWithDirectoryAndFileExtensionOnlyGiven_WithNumbersAndSpecialCharacters)
{
    AlbaWindowsPathHandler pathHandler(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\.zxcvbnm12345)");
    EXPECT_EQ("APRG_DRIVE", pathHandler.getDriveOrRoot());
    EXPECT_EQ(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)", pathHandler.getDirectory());
    EXPECT_EQ(".zxcvbnm12345", pathHandler.getFile());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_EQ("zxcvbnm12345", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
}

TEST_F(AlbaWindowsPathHandlerTest, FullPathWithDirectoryAndFileNoFileExtensionGiven_WithNumbersAndSpecialCharactersTwoTimes)
{
    AlbaWindowsPathHandler pathHandler(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\Aprg1111Common\tst\76543.txt)");
    EXPECT_EQ("APRG_DRIVE", pathHandler.getDriveOrRoot());
    EXPECT_EQ(R"(APRG_DRIVE:\APRG12345\Aprg!@#$%Common\Aprg1111Common\tst\)", pathHandler.getDirectory());
    EXPECT_EQ("76543.txt", pathHandler.getFile());
    EXPECT_EQ("76543", pathHandler.getFilenameOnly());
    EXPECT_EQ("txt", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());

    pathHandler.input(R"(e:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\.zxcvbnm12345)");
    EXPECT_EQ("E", pathHandler.getDriveOrRoot());
    EXPECT_EQ(R"(e:\APRG12345\Aprg!@#$%Common\AprgCommon\tst\)", pathHandler.getDirectory());
    EXPECT_EQ(".zxcvbnm12345", pathHandler.getFile());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_EQ("zxcvbnm12345", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
}

TEST_F(AlbaWindowsPathHandlerTest, FullPathWithDirectoryAndFile_DoublePeriodInPath)
{
    AlbaWindowsPathHandler pathHandler(pathOfAprgDirectory + R"(..\dir\file.txt)");
    EXPECT_EQ(getDriveOfAprgDir(), pathHandler.getDriveOrRoot());
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(..\dir\)"), pathHandler.getDirectory());
    EXPECT_EQ("file.txt", pathHandler.getFile());
    EXPECT_EQ("file", pathHandler.getFilenameOnly());
    EXPECT_EQ("txt", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());

    pathHandler.input(pathOfAprgDirectory + R"(dir\..\..\file.txt)");
    EXPECT_EQ(getDriveOfAprgDir(), pathHandler.getDriveOrRoot());
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(dir\..\..\)"), pathHandler.getDirectory());
    EXPECT_EQ("file.txt", pathHandler.getFile());
    EXPECT_EQ("file", pathHandler.getFilenameOnly());
    EXPECT_EQ("txt", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());

    pathHandler.input(pathOfAprgDirectory + R"(dir\..\dir2\dir3\..\file.txt)");
    EXPECT_EQ(getDriveOfAprgDir(), pathHandler.getDriveOrRoot());
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(dir2\)"), pathHandler.getDirectory());
    EXPECT_EQ("file.txt", pathHandler.getFile());
    EXPECT_EQ("file", pathHandler.getFilenameOnly());
    EXPECT_EQ("txt", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
}

TEST_F(AlbaWindowsPathHandlerTest, FullPathWithDirectoryAndFile_ActualLocalDirectory)
{
    AlbaWindowsPathHandler pathHandler(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\File1.log)");
    EXPECT_EQ(getDriveOfAprgDir(), pathHandler.getDriveOrRoot());
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\)"), pathHandler.getDirectory());
    EXPECT_EQ("File1.log", pathHandler.getFile());
    EXPECT_EQ("File1", pathHandler.getFilenameOnly());
    EXPECT_EQ("log", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.isFoundInLocalSystem());

    pathHandler.input(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\thisFileDoesNotExist.txt)");
    EXPECT_EQ(getDriveOfAprgDir(), pathHandler.getDriveOrRoot());
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\)"), pathHandler.getDirectory());
    EXPECT_EQ("thisFileDoesNotExist.txt", pathHandler.getFile());
    EXPECT_EQ("thisFileDoesNotExist", pathHandler.getFilenameOnly());
    EXPECT_EQ("txt", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    EXPECT_FALSE(pathHandler.isFoundInLocalSystem());

    pathHandler.input(pathOfAprgDirectory + R"(AprgCommon\FilesForTests)");
    EXPECT_EQ(getDriveOfAprgDir(), pathHandler.getDriveOrRoot());
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\)"), pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.isFoundInLocalSystem());

    pathHandler.input(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\)");
    EXPECT_EQ(getDriveOfAprgDir(), pathHandler.getDriveOrRoot());
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\)"), pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.isFoundInLocalSystem());
}

TEST_F(AlbaWindowsPathHandlerTest, ReInputFileThatIsToBeDeleted_ActualLocalDirectory)
{
    string const pathOfFileToBeDeleted(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\FileToBeDeleted.log)");
    std::ofstream fileToBeDeleted(pathOfFileToBeDeleted);
    fileToBeDeleted.close();

    AlbaWindowsPathHandler pathHandler(pathOfFileToBeDeleted);
    EXPECT_EQ(getDriveOfAprgDir(), pathHandler.getDriveOrRoot());
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\)"), pathHandler.getDirectory());
    EXPECT_EQ("FileToBeDeleted.log", pathHandler.getFile());
    EXPECT_EQ("FileToBeDeleted", pathHandler.getFilenameOnly());
    EXPECT_EQ("log", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.isFoundInLocalSystem());

    EXPECT_TRUE(pathHandler.deleteFile());

    EXPECT_EQ(getDriveOfAprgDir(), pathHandler.getDriveOrRoot());
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\)"), pathHandler.getDirectory());
    EXPECT_EQ("FileToBeDeleted.log", pathHandler.getFile());
    EXPECT_EQ("FileToBeDeleted", pathHandler.getFilenameOnly());
    EXPECT_EQ("log", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    EXPECT_FALSE(pathHandler.isFoundInLocalSystem());
}

TEST_F(AlbaWindowsPathHandlerTest, ReInputFileThatIsToBeRenamed_ActualLocalDirectory)
{
    string const pathOfFileToBeRenamed(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\FileToBeRenamed.log)");
    std::ofstream fileToBeDeleted(pathOfFileToBeRenamed);
    fileToBeDeleted.close();

    AlbaWindowsPathHandler pathHandler(pathOfFileToBeRenamed);
    EXPECT_EQ(getDriveOfAprgDir(), pathHandler.getDriveOrRoot());
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\)"), pathHandler.getDirectory());
    EXPECT_EQ("FileToBeRenamed.log", pathHandler.getFile());
    EXPECT_EQ("FileToBeRenamed", pathHandler.getFilenameOnly());
    EXPECT_EQ("log", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.isFoundInLocalSystem());

    EXPECT_TRUE(pathHandler.renameFile("RenamedFile.txt"));

    EXPECT_EQ(getDriveOfAprgDir(), pathHandler.getDriveOrRoot());
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\)"), pathHandler.getDirectory());
    EXPECT_EQ("RenamedFile.txt", pathHandler.getFile());
    EXPECT_EQ("RenamedFile", pathHandler.getFilenameOnly());
    EXPECT_EQ("txt", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.isFoundInLocalSystem());

    EXPECT_TRUE(pathHandler.deleteFile());
}

TEST_F(AlbaWindowsPathHandlerTest, FileIsCopiedToNewFile_ActualLocalDirectory)
{
    string const pathOfFileToBeCopied(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\FileToBeCopied.log)");
    string const pathOfCopiedFile("CopiedFile.log");
    std::ofstream fileToBeCopied(pathOfFileToBeCopied);
    fileToBeCopied.close();

    AlbaWindowsPathHandler pathHandler(pathOfFileToBeCopied);
    EXPECT_EQ(getDriveOfAprgDir(), pathHandler.getDriveOrRoot());
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\)"), pathHandler.getDirectory());
    EXPECT_EQ("FileToBeCopied.log", pathHandler.getFile());
    EXPECT_EQ("FileToBeCopied", pathHandler.getFilenameOnly());
    EXPECT_EQ("log", pathHandler.getExtension());
    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.isFoundInLocalSystem());

    EXPECT_TRUE(pathHandler.copyToNewFile(pathHandler.getDirectory()+pathOfCopiedFile));

    AlbaWindowsPathHandler pathHandlerOfCopiedFile(pathHandler.getDirectory()+pathOfCopiedFile);
    EXPECT_EQ(getDriveOfAprgDir(), pathHandlerOfCopiedFile.getDriveOrRoot());
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\)"), pathHandlerOfCopiedFile.getDirectory());
    EXPECT_EQ("CopiedFile.log", pathHandlerOfCopiedFile.getFile());
    EXPECT_EQ("CopiedFile", pathHandlerOfCopiedFile.getFilenameOnly());
    EXPECT_EQ("log", pathHandlerOfCopiedFile.getExtension());
    EXPECT_EQ(PathType::File, pathHandlerOfCopiedFile.getPathType());
    EXPECT_TRUE(pathHandlerOfCopiedFile.isFoundInLocalSystem());

    EXPECT_TRUE(pathHandler.deleteFile());
    EXPECT_TRUE(pathHandlerOfCopiedFile.deleteFile());
}

TEST_F(AlbaWindowsPathHandlerTest, ReInputDirectoryThatIsToBeRenamed_ActualLocalDirectory)
{
    string const pathOfDirectoryToBeRenamed(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\DIR1)");

    AlbaWindowsPathHandler pathHandler(pathOfDirectoryToBeRenamed);
    EXPECT_EQ(getDriveOfAprgDir(), pathHandler.getDriveOrRoot());
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\DIR1\)"),  pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.isFoundInLocalSystem());

    EXPECT_TRUE(pathHandler.renameImmediateDirectory("RenamedDirectory"));

    EXPECT_EQ(getDriveOfAprgDir(), pathHandler.getDriveOrRoot());
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\RenamedDirectory\)"), pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.isFoundInLocalSystem());

    EXPECT_TRUE(pathHandler.renameImmediateDirectory("DIR1"));

    EXPECT_EQ(getDriveOfAprgDir(), pathHandler.getDriveOrRoot());
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\DIR1\)"), pathHandler.getDirectory());
    EXPECT_TRUE(pathHandler.getFile().empty());
    EXPECT_TRUE(pathHandler.getFilenameOnly().empty());
    EXPECT_TRUE(pathHandler.getExtension().empty());
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
    EXPECT_TRUE(pathHandler.isFoundInLocalSystem());
}

TEST_F(AlbaWindowsPathHandlerTest, FullPathWithDirectory_FindFileAndDirectoryOneDepth)
{
    AlbaWindowsPathHandler pathHandler(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\)");
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
    ASSERT_TRUE(pathHandler.isFoundInLocalSystem());

    set<string> listOfFiles;
    set<string> listOfDirectory;
    pathHandler.findFilesAndDirectoriesOneDepth("*.*", listOfFiles, listOfDirectory);
    ASSERT_EQ(5U, listOfFiles.size());
    auto itFiles = listOfFiles.begin();
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\File1.log)"), *(itFiles++));
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\File2.txt)"), *(itFiles++));
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\File3)"), *(itFiles++));
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\File4.mp3)"), *(itFiles++));
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\File5.avi)"), *(itFiles++));
    ASSERT_EQ(6U, listOfDirectory.size());
    auto itDirectories = listOfDirectory.begin();
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\DIR1\)"), *(itDirectories++));
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\DIR2\)"), *(itDirectories++));
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\DIR3\)"), *(itDirectories++));
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\DIR4\)"), *(itDirectories++));
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\DIR5\)"), *(itDirectories++));
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\DIR6\)"), *(itDirectories++));
}

TEST_F(AlbaWindowsPathHandlerTest, FullPathWithDirectory_FindFileAndDirectoryMultipleDepthTwo)
{
    AlbaWindowsPathHandler pathHandler(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\)");
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
    ASSERT_TRUE(pathHandler.isFoundInLocalSystem());

    set<string> listOfFiles;
    set<string> listOfDirectory;
    pathHandler.findFilesAndDirectoriesMultipleDepth("*.*", listOfFiles, listOfDirectory, 2);
    ASSERT_EQ(10U, listOfFiles.size());
    auto itFiles = listOfFiles.begin();
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\DIR1\File1.log)"), *(itFiles++));
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\DIR2\File2.txt)"), *(itFiles++));
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\DIR3\File3)"), *(itFiles++));
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\DIR4\File4.mp3)"), *(itFiles++));
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\DIR5\File5.avi)"), *(itFiles++));
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\File1.log)"), *(itFiles++));
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\File2.txt)"), *(itFiles++));
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\File3)"), *(itFiles++));
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\File4.mp3)"), *(itFiles++));
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\File5.avi)"), *(itFiles++));
    ASSERT_EQ(7U, listOfDirectory.size());
    auto itDirectories = listOfDirectory.begin();
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\DIR1\)"), *(itDirectories++));
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\DIR2\)"), *(itDirectories++));
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\DIR3\)"), *(itDirectories++));
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\DIR4\)"), *(itDirectories++));
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\DIR5\)"), *(itDirectories++));
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\DIR6\)"), *(itDirectories++));
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\DIR6\SUBDIR1\)"), *(itDirectories++));
}

TEST_F(AlbaWindowsPathHandlerTest, FullPathWithDirectory_FindFileAndDirectoryUnlimitedDepth)
{
    AlbaWindowsPathHandler pathHandler(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\)");
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
    ASSERT_TRUE(pathHandler.isFoundInLocalSystem());

    set<string> listOfFiles;
    set<string> listOfDirectory;
    pathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", listOfFiles, listOfDirectory);
    ASSERT_EQ(11U, listOfFiles.size());
    auto itFiles = listOfFiles.begin();
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\DIR1\File1.log)"), *(itFiles++));
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\DIR2\File2.txt)"), *(itFiles++));
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\DIR3\File3)"), *(itFiles++));
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\DIR4\File4.mp3)"), *(itFiles++));
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\DIR5\File5.avi)"), *(itFiles++));
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\DIR6\SUBDIR1\File6.jpg)"), *(itFiles++));
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\File1.log)"), *(itFiles++));
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\File2.txt)"), *(itFiles++));
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\File3)"), *(itFiles++));
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\File4.mp3)"), *(itFiles++));
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\File5.avi)"), *(itFiles++));
    ASSERT_EQ(7U, listOfDirectory.size());
    auto itDirectories = listOfDirectory.begin();
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\DIR1\)"), *(itDirectories++));
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\DIR2\)"), *(itDirectories++));
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\DIR3\)"), *(itDirectories++));
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\DIR4\)"), *(itDirectories++));
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\DIR5\)"), *(itDirectories++));
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\DIR6\)"), *(itDirectories++));
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\DIR6\SUBDIR1\)"), *(itDirectories++));
}

TEST_F(AlbaWindowsPathHandlerTest, FullPathWithDirectory_FindFileAndDirectoryUnlimitedDepthWithWildCard)
{
    AlbaWindowsPathHandler pathHandler(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\)");
    EXPECT_EQ(PathType::Directory, pathHandler.getPathType());
    ASSERT_TRUE(pathHandler.isFoundInLocalSystem());

    set<string> listOfFiles;
    set<string> listOfDirectory;
    pathHandler.findFilesAndDirectoriesUnlimitedDepth("*.log", listOfFiles, listOfDirectory);
    ASSERT_EQ(1U, listOfFiles.size());
    auto itFiles = listOfFiles.begin();
    EXPECT_EQ(convertToSimplestPath(pathOfAprgDirectory + R"(AprgCommon\FilesForTests\DirectoryTest\File1.log)"), *(itFiles++));
    ASSERT_EQ(0U, listOfDirectory.size());
}

TEST_F(AlbaWindowsPathHandlerTest, FileSizeTest_FileIsNotExisting)
{
    AlbaWindowsPathHandler pathHandler("This path does not exist");

    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    ASSERT_FALSE(pathHandler.isFoundInLocalSystem());
    EXPECT_DOUBLE_EQ(0, pathHandler.getFileSizeEstimate());
}

TEST_F(AlbaWindowsPathHandlerTest, FileSizeTest_FileIsExisting)
{
    AlbaWindowsPathHandler pathHandler(ALBA_COMMON_SIZE_TEST_FILE);

    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    ASSERT_TRUE(pathHandler.isFoundInLocalSystem());
    EXPECT_DOUBLE_EQ(5000, pathHandler.getFileSizeEstimate());
}

TEST_F(AlbaWindowsPathHandlerTest, SetCurrentDirectoryFromDetectedLocalPath)
{
    AlbaWindowsPathHandler pathHandler(PathInitialValueSource::DetectedLocalPath);

    EXPECT_EQ(PathType::File, pathHandler.getPathType());
    ASSERT_TRUE(pathHandler.isFoundInLocalSystem());
}

}
