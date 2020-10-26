#include <CPlusPlusFileFixer/CPlusPlusFileFixer.hpp>

#include <gtest/gtest.h>

#include <string>

using namespace alba;

TEST(CPlusPlusFileFixerTest, TestFilesToBeGrep)
{
    CPlusPlusFileFixer fixer;
    fixer.processDirectory(R"(C:\APRG\)");
    //fixer.processFile(R"(C:\APRG\AprgCommon\AprgCommon\tst\AlbaStringHelper_unit.cpp)");
}


