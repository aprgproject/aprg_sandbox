#include "../../src/FileDirectoryDatabase/FileDirectoryDatabase.hpp"
#include "../MtDirectoryConstants.hpp"
#include "gtest/gtest.h"

#include <fstream>
#include <iostream>
#include <string>

using namespace codeReview;
using namespace std;

TEST(FileDirectoryDatabaseTest, DISABLED_ActualTest)
{
    FileDirectoryDatabase fileDirectoryDatabase;
    fileDirectoryDatabase.addFileOrDirectory("C:\\Qt\\Qt5.3.2\\Tools\\mingw482_32\\i686-w64-mingw32\\include\\c++\\");
    cout<<"FullPath of iostream: "<<fileDirectoryDatabase.getFullPathOfFile("", "iostream")<<endl;
    //fileDirectoryDatabase.printFilesAndDirectories(cout);
}

TEST(FileDirectoryDatabaseTest, FilesAndDirectoriesAreRecognizedWhenAdded)
{
    string directory(MT_FILE_READER_TEST_DIRECTORY);
    FileDirectoryDatabase fileDirectoryDatabase;
    fileDirectoryDatabase.allowNonExistentDirectories();
    fileDirectoryDatabase.addFileOrDirectory(directory+"file3.hpp");
    fileDirectoryDatabase.addFileOrDirectory(directory+"file6.hpp");
    fileDirectoryDatabase.addFileOrDirectory(directory+"file4.hpp");
    fileDirectoryDatabase.addFileOrDirectory(directory+"file1.hpp");
    fileDirectoryDatabase.addFileOrDirectory(directory+"file2.hpp");
    fileDirectoryDatabase.addFileOrDirectory(directory+"file5.hpp");
    fileDirectoryDatabase.addFileOrDirectory(directory+"directoryC\\");
    fileDirectoryDatabase.addFileOrDirectory(directory+"directoryA\\");
    fileDirectoryDatabase.addFileOrDirectory(directory+"directoryB\\");

    //fileDirectoryDatabase.printFilesAndDirectories(cout);

    SetOfDirectories& setOfDirectories = fileDirectoryDatabase.getSetOfDirectoriesReference();
    ASSERT_EQ(setOfDirectories.size(), 3);
    auto itDirectory = setOfDirectories.begin();
    EXPECT_EQ(*(itDirectory++), directory+"directoryA\\");
    EXPECT_EQ(*(itDirectory++), directory+"directoryB\\");
    EXPECT_EQ(*(itDirectory++), directory+"directoryC\\");

    SetOfFiles& setOfFiles = fileDirectoryDatabase.getSetOfFilesReference();
    ASSERT_EQ(setOfFiles.size(), 6);
    auto itFile = setOfFiles.begin();
    EXPECT_EQ(*(itFile++), directory+"file1.hpp");
    EXPECT_EQ(*(itFile++), directory+"file2.hpp");
    EXPECT_EQ(*(itFile++), directory+"file3.hpp");
    EXPECT_EQ(*(itFile++), directory+"file4.hpp");
    EXPECT_EQ(*(itFile++), directory+"file5.hpp");
    EXPECT_EQ(*(itFile++), directory+"file6.hpp");
}

TEST(FileDirectoryDatabaseTest, FullPathOfFilesAreFound)
{
    string directory(MT_FILE_READER_TEST_DIRECTORY);
    FileDirectoryDatabase fileDirectoryDatabase;
    fileDirectoryDatabase.allowNonExistentDirectories();
    fileDirectoryDatabase.addFileOrDirectory(directory+"file3.hpp");
    fileDirectoryDatabase.addFileOrDirectory(directory+"file6.hpp");
    fileDirectoryDatabase.addFileOrDirectory(directory+"file4.hpp");
    fileDirectoryDatabase.addFileOrDirectory(directory+"file1.hpp");
    fileDirectoryDatabase.addFileOrDirectory(directory+"file2.hpp");
    fileDirectoryDatabase.addFileOrDirectory(directory+"file5.hpp");

    EXPECT_EQ(fileDirectoryDatabase.getFullPathOfFile(directory, "file1.hpp"), directory+"file1.hpp");
    EXPECT_EQ(fileDirectoryDatabase.getFullPathOfFile(directory, "file2.hpp"), directory+"file2.hpp");
    EXPECT_EQ(fileDirectoryDatabase.getFullPathOfFile(directory, "file3.hpp"), directory+"file3.hpp");
    EXPECT_EQ(fileDirectoryDatabase.getFullPathOfFile("", "file4.hpp"), directory+"file4.hpp");
    EXPECT_EQ(fileDirectoryDatabase.getFullPathOfFile("", "file5.hpp"), directory+"file5.hpp");
    EXPECT_EQ(fileDirectoryDatabase.getFullPathOfFile("", "file6.hpp"), directory+"file6.hpp");
}
