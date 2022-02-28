#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <FileDestructor.hpp>

#include <gtest/gtest.h>

#include <fstream>

using namespace std;

namespace alba
{

namespace
{

void createAFileInDirectory(string const& directory)
{
    ofstream outputStream(directory + "SomeFile.txt");
    outputStream << "some string" << endl;
}

void retrieveNumberOfFilesAndDirectoriesFromPath(
        AlbaLocalPathHandler & pathHandler,
        unsigned int & numberOfFiles,
        unsigned int & numberOfDirectories)
{
    pathHandler.reInput();
    ListOfPaths files;
    ListOfPaths directories;
    pathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", files, directories);
    numberOfFiles = files.size();
    numberOfDirectories = directories.size();
}

}

TEST(SampleTest, DestroyOneFileTest)
{
    FileDestructor fileDestructor;
    AlbaLocalPathHandler pathHandler(APRG_DIR R"(\FileDestructor\FileDestructor\tst\TestFolderForDestruction)");
    unsigned int numberOfFiles;
    unsigned int numberOfDirectories;
    createAFileInDirectory(pathHandler.getFullPath());
    retrieveNumberOfFilesAndDirectoriesFromPath(pathHandler, numberOfFiles, numberOfDirectories);
    EXPECT_EQ(1U, numberOfFiles);
    EXPECT_EQ(0U, numberOfDirectories);

    fileDestructor.destroy(pathHandler.getFullPath());

    retrieveNumberOfFilesAndDirectoriesFromPath(pathHandler, numberOfFiles, numberOfDirectories);
    EXPECT_EQ(0U, numberOfFiles);
    EXPECT_EQ(0U, numberOfDirectories);
}

}
