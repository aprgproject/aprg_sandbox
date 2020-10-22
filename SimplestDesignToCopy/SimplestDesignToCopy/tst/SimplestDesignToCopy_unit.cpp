#include <gtest/gtest.h>
#include <SimplestDesignToCopy.hpp>

#include <iostream>
#include <string>
#include <PathHandlers/AlbaWindowsPathHandler.hpp>

using namespace alba;
using namespace std;

TEST(SampleTest, SampleTest1)
{
    SimplestDesignToCopy entity;
}

TEST(SampleTest, FilesToFind)
{
    AlbaWindowsPathHandler::ListOfPaths files;
    AlbaWindowsPathHandler::ListOfPaths directories;
    AlbaWindowsPathHandler pathHandler(R"(C:\APRG\gsl\gsl-2.1)");
    pathHandler.findFilesAndDirectoriesUnlimitedDepth("*.*", files, directories);

    for(string const& file: files)
    {
        cout<<file<<endl;
    }
}
