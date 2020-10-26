#include <CPlusPlusFileFixer/CPlusPlusFileFixer.hpp>

#include <gtest/gtest.h>
#include <string>

using namespace alba;

TEST(CPlusPlusFileFixerTest, TestFilesToBeGrep)
{
    CPlusPlusFileFixer fixer;
    fixer.processFile(R"(C:\APRG\AprgCommon\AprgCommon\src\PathHandlers\AlbaWindowsPathHandler.hpp)");
}
