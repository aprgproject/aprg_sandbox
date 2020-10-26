#include <CombineAndGrepFiles/AlbaCombineAndGrepFiles.hpp>

#include <gtest/gtest.h>

#include <string>

using namespace alba;

TEST(AlbaCombineAndGrepFilesTest, TestFilesToBeGrep)
{
    AlbaCombineAndGrepFiles CombineAndGrepFilesObject(R"(D:\W\trunk\C_Application\I_Interface.log)", R"([])", R"([ServiceInterface])");
    CombineAndGrepFilesObject.processDirectory(R"(D:\W\trunk\C_Application\SC_TCOM)");
}


