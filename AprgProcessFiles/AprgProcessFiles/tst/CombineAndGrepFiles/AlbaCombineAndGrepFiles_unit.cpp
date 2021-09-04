#include <CombineAndGrepFiles/AlbaCombineAndGrepFiles.hpp>

#include <gtest/gtest.h>

#include <string>

namespace alba
{

TEST(AlbaCombineAndGrepFilesTest, DISABLED_TestFilesToBeGrep)
{
    AlbaCombineAndGrepFiles CombineAndGrepFilesObject(R"(D:\W\trunk\C_Application\I_Interface.log)", R"([])", R"([ServiceInterface])");
    CombineAndGrepFilesObject.processDirectory(R"(D:\W\trunk\C_Application\SC_TCOM)");
}

}
