#include "../../../src/FileDirectoryDatabase/CMake/CMakeDatabase.hpp"
#include "../../MtDirectoryConstants.hpp"
#include "gtest/gtest.h"

#include <fstream>
#include <iostream>
#include <string>

using namespace codeReview;
using namespace std;

TEST(CMakeDatabaseTest, FilesAndDirectoriesAreRecognizedWhenAdded) {
    string directory(MT_FILE_READER_TEST_DIRECTORY);
    CMakeDatabase fileDirectoryDatabase;
    fileDirectoryDatabase.allowNonExistentDirectories();
    fileDirectoryDatabase.addFileOrDirectory(directory + "file3.hpp");
    fileDirectoryDatabase.addFileOrDirectory(directory + "file6.hpp");
    fileDirectoryDatabase.addFileOrDirectory(directory + "file4.hpp");
    fileDirectoryDatabase.addFileOrDirectory(directory + "file1.hpp");
    fileDirectoryDatabase.addFileOrDirectory(directory + "file2.hpp");
    fileDirectoryDatabase.addFileOrDirectory(directory + "file5.hpp");
    fileDirectoryDatabase.addFileOrDirectory(directory + "directoryC\\");
    fileDirectoryDatabase.addFileOrDirectory(directory + "directoryA\\");
    fileDirectoryDatabase.addFileOrDirectory(directory + "directoryB\\");

    SetOfDirectories& setOfDirectories = fileDirectoryDatabase.getSetOfDirectoriesReference();
    ASSERT_EQ(setOfDirectories.size(), 3);
    auto itDirectory = setOfDirectories.begin();
    EXPECT_EQ(*(itDirectory++), directory + "directoryA\\");
    EXPECT_EQ(*(itDirectory++), directory + "directoryB\\");
    EXPECT_EQ(*(itDirectory++), directory + "directoryC\\");

    SetOfFiles& setOfFiles = fileDirectoryDatabase.getSetOfFilesReference();
    ASSERT_EQ(setOfFiles.size(), 6);
    auto itFile = setOfFiles.begin();
    EXPECT_EQ(*(itFile++), directory + "file1.hpp");
    EXPECT_EQ(*(itFile++), directory + "file2.hpp");
    EXPECT_EQ(*(itFile++), directory + "file3.hpp");
    EXPECT_EQ(*(itFile++), directory + "file4.hpp");
    EXPECT_EQ(*(itFile++), directory + "file5.hpp");
    EXPECT_EQ(*(itFile++), directory + "file6.hpp");
}

TEST(CMakeDatabaseTest, SubDirectoriesCanBeAdded) {
    string directory(MT_FILE_READER_TEST_DIRECTORY);
    CMakeDatabase fileDirectoryDatabase;
    fileDirectoryDatabase.allowNonExistentDirectories();
    CMakeDatabase& subFileDirectoryDatabase = fileDirectoryDatabase.addCMakeSubDirectory();
    subFileDirectoryDatabase.addFileOrDirectory(directory + "file3.hpp");
    subFileDirectoryDatabase.addFileOrDirectory(directory + "file6.hpp");
    subFileDirectoryDatabase.addFileOrDirectory(directory + "file4.hpp");
    subFileDirectoryDatabase.addFileOrDirectory(directory + "file1.hpp");
    subFileDirectoryDatabase.addFileOrDirectory(directory + "file2.hpp");
    subFileDirectoryDatabase.addFileOrDirectory(directory + "file5.hpp");
    subFileDirectoryDatabase.addFileOrDirectory(directory + "directoryC\\");
    subFileDirectoryDatabase.addFileOrDirectory(directory + "directoryA\\");
    subFileDirectoryDatabase.addFileOrDirectory(directory + "directoryB\\");

    ASSERT_EQ(fileDirectoryDatabase.getSubCMakeDatabasesReference().size(), 1);
    CMakeDatabase& subFileDirectoryDatabaseTest = fileDirectoryDatabase.getSubCMakeDatabasesReference()[0];
    SetOfDirectories& setOfDirectories = subFileDirectoryDatabaseTest.getSetOfDirectoriesReference();
    ASSERT_EQ(setOfDirectories.size(), 3);
    auto itDirectory = setOfDirectories.begin();
    EXPECT_EQ(*(itDirectory++), directory + "directoryA\\");
    EXPECT_EQ(*(itDirectory++), directory + "directoryB\\");
    EXPECT_EQ(*(itDirectory++), directory + "directoryC\\");

    SetOfFiles& setOfFiles = subFileDirectoryDatabaseTest.getSetOfFilesReference();
    ASSERT_EQ(setOfFiles.size(), 6);
    auto itFile = setOfFiles.begin();
    EXPECT_EQ(*(itFile++), directory + "file1.hpp");
    EXPECT_EQ(*(itFile++), directory + "file2.hpp");
    EXPECT_EQ(*(itFile++), directory + "file3.hpp");
    EXPECT_EQ(*(itFile++), directory + "file4.hpp");
    EXPECT_EQ(*(itFile++), directory + "file5.hpp");
    EXPECT_EQ(*(itFile++), directory + "file6.hpp");
}

TEST(CMakeDatabaseTest, SearchCMakeFileDirectoryInnerDirection) {
    string directory(MT_FILE_READER_TEST_DIRECTORY);
    CMakeDatabase mainDirectory;
    mainDirectory.allowNonExistentDirectories();
    mainDirectory.addFileOrDirectory(directory + "file3.hpp");
    mainDirectory.addFileOrDirectory(directory + "file1.hpp");
    mainDirectory.addFileOrDirectory(directory + "file2.hpp");
    mainDirectory.addFileOrDirectory(directory + "directoryC\\");
    mainDirectory.addFileOrDirectory(directory + "directoryA\\");
    mainDirectory.addFileOrDirectory(directory + "directoryB\\");
    CMakeDatabase& sub1 = mainDirectory.addCMakeSubDirectory();
    sub1.addFileOrDirectory(directory + "file3sub1.hpp");
    sub1.addFileOrDirectory(directory + "file1sub1.hpp");
    sub1.addFileOrDirectory(directory + "file2sub1.hpp");
    sub1.addFileOrDirectory(directory + "directoryCsub1\\");
    sub1.addFileOrDirectory(directory + "directoryAsub1\\");
    sub1.addFileOrDirectory(directory + "directoryBsub1\\");
    CMakeDatabase& sub2 = sub1.addCMakeSubDirectory();
    sub2.addFileOrDirectory(directory + "file3sub2.hpp");
    sub2.addFileOrDirectory(directory + "file1sub2.hpp");
    sub2.addFileOrDirectory(directory + "file2sub2.hpp");
    sub2.addFileOrDirectory(directory + "directoryCsub2\\");
    sub2.addFileOrDirectory(directory + "directoryAsub2\\");
    sub2.addFileOrDirectory(directory + "directoryBsub2\\");
    CMakeDatabase& sub3 = sub2.addCMakeSubDirectory();
    sub3.addFileOrDirectory(directory + "file3sub3.hpp");
    sub3.addFileOrDirectory(directory + "file1sub3.hpp");
    sub3.addFileOrDirectory(directory + "file2sub3.hpp");
    sub3.addFileOrDirectory(directory + "directoryCsub3\\");
    sub3.addFileOrDirectory(directory + "directoryAsub3\\");
    sub3.addFileOrDirectory(directory + "directoryBsub3\\");

    bool isFound;
    string correctFullPath;
    CMakeDatabase& foundCMakeDatabase = mainDirectory.find_InnerDirection("file2sub2", isFound, correctFullPath);
    ASSERT_TRUE(isFound);
    EXPECT_EQ(correctFullPath, directory + "file2sub2.hpp");

    SetOfDirectories& setOfDirectories = foundCMakeDatabase.getSetOfDirectoriesReference();
    ASSERT_EQ(setOfDirectories.size(), 3);
    auto itDirectory = setOfDirectories.begin();
    EXPECT_EQ(*(itDirectory++), directory + "directoryAsub2\\");
    EXPECT_EQ(*(itDirectory++), directory + "directoryBsub2\\");
    EXPECT_EQ(*(itDirectory++), directory + "directoryCsub2\\");

    SetOfFiles& setOfFiles = foundCMakeDatabase.getSetOfFilesReference();
    ASSERT_EQ(setOfFiles.size(), 3);
    auto itFile = setOfFiles.begin();
    EXPECT_EQ(*(itFile++), directory + "file1sub2.hpp");
    EXPECT_EQ(*(itFile++), directory + "file2sub2.hpp");
    EXPECT_EQ(*(itFile++), directory + "file3sub2.hpp");
}

TEST(CMakeDatabaseTest, SearchCMakeFileDirectoryOuterDirection) {
    string directory(MT_FILE_READER_TEST_DIRECTORY);
    CMakeDatabase mainDirectory;
    mainDirectory.allowNonExistentDirectories();
    mainDirectory.addFileOrDirectory(directory + "file3.hpp");
    mainDirectory.addFileOrDirectory(directory + "file1.hpp");
    mainDirectory.addFileOrDirectory(directory + "file2.hpp");
    mainDirectory.addFileOrDirectory(directory + "directoryC\\");
    mainDirectory.addFileOrDirectory(directory + "directoryA\\");
    mainDirectory.addFileOrDirectory(directory + "directoryB\\");
    CMakeDatabase& sub1 = mainDirectory.addCMakeSubDirectory();
    sub1.addFileOrDirectory(directory + "file3sub1.hpp");
    sub1.addFileOrDirectory(directory + "file1sub1.hpp");
    sub1.addFileOrDirectory(directory + "file2sub1.hpp");
    sub1.addFileOrDirectory(directory + "directoryCsub1\\");
    sub1.addFileOrDirectory(directory + "directoryAsub1\\");
    sub1.addFileOrDirectory(directory + "directoryBsub1\\");
    CMakeDatabase& sub2 = sub1.addCMakeSubDirectory();
    sub2.addFileOrDirectory(directory + "file3sub2.hpp");
    sub2.addFileOrDirectory(directory + "file1sub2.hpp");
    sub2.addFileOrDirectory(directory + "file2sub2.hpp");
    sub2.addFileOrDirectory(directory + "directoryCsub2\\");
    sub2.addFileOrDirectory(directory + "directoryAsub2\\");
    sub2.addFileOrDirectory(directory + "directoryBsub2\\");
    CMakeDatabase& sub3 = sub2.addCMakeSubDirectory();
    sub3.addFileOrDirectory(directory + "file3sub3.hpp");
    sub3.addFileOrDirectory(directory + "file1sub3.hpp");
    sub3.addFileOrDirectory(directory + "file2sub3.hpp");
    sub3.addFileOrDirectory(directory + "directoryCsub3\\");
    sub3.addFileOrDirectory(directory + "directoryAsub3\\");
    sub3.addFileOrDirectory(directory + "directoryBsub3\\");

    bool isFound;
    string correctFullPath;
    CMakeDatabase& foundCMakeDatabase = sub3.find_OuterDirection("file2sub2", isFound, correctFullPath);
    ASSERT_TRUE(isFound);
    EXPECT_EQ(correctFullPath, directory + "file2sub2.hpp");

    SetOfDirectories& setOfDirectories = foundCMakeDatabase.getSetOfDirectoriesReference();
    ASSERT_EQ(setOfDirectories.size(), 3);
    auto itDirectory = setOfDirectories.begin();
    EXPECT_EQ(*(itDirectory++), directory + "directoryAsub2\\");
    EXPECT_EQ(*(itDirectory++), directory + "directoryBsub2\\");
    EXPECT_EQ(*(itDirectory++), directory + "directoryCsub2\\");

    SetOfFiles& setOfFiles = foundCMakeDatabase.getSetOfFilesReference();
    ASSERT_EQ(setOfFiles.size(), 3);
    auto itFile = setOfFiles.begin();
    EXPECT_EQ(*(itFile++), directory + "file1sub2.hpp");
    EXPECT_EQ(*(itFile++), directory + "file2sub2.hpp");
    EXPECT_EQ(*(itFile++), directory + "file3sub2.hpp");
}
