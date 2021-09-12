#include <CPlusPlusFileFixer/CPlusPlusFileFixer.hpp>
#include <DirectoryConstants.hpp>
#include <File/AlbaFileReader.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>

#include <gtest/gtest.h>

#include <fstream>
#include <string>

using namespace std;

namespace alba
{

TEST(CPlusPlusFileFixerTest, DISABLED_ActualRun)
{
    //CPlusPlusFileFixer fixer;
    //fixer.processDirectory(R"(N:\Branches\APRG_LINUX_COPY\)");
}

TEST(CPlusPlusFileFixerTest, CPlusPlusFileHeadersAreCorrected)
{
    CPlusPlusFileFixer fixer;
    AlbaLocalPathHandler file1ToReadPathHandler(APRG_PROCESS_FILES_TEST_FILE1_TO_READ);
    ofstream testFile(file1ToReadPathHandler.getFullPath());
    ASSERT_TRUE(testFile.is_open());
    testFile << R"(#include <file2.hpp>)" << endl;
    testFile << R"(#include<string>)" << endl;
    testFile << R"(#include <gtest/gtest.h> )" << endl;
    testFile << R"(#include <windows.h> )" << endl;
    testFile << R"(#include <sys/types.h> )" << endl;
    testFile << "   #pragma once\t\t\t " << endl;
    testFile << R"()"<< endl;
    testFile << R"(#include "file1.hpp")" << endl;
    testFile << R"()"<< endl;
    testFile << R"(#include <QDebug>)" << endl;
    testFile << R"(#include <QtWidgets>)" << endl;
    testFile << R"(#include <Test1\Test1.hpp>)" << endl;
    testFile << R"(#include <Test1\Test1_unit.hpp>)" << endl;
    testFile << R"(         This is a line in the code)" << endl;
    testFile << "       \t\t\t\t       This is another line in the code    " << endl;
    testFile.close();

    fixer.processFile(file1ToReadPathHandler.getFullPath());

    ifstream inputTestFile(file1ToReadPathHandler.getFullPath());
    ASSERT_TRUE(inputTestFile.is_open());

    AlbaFileReader fileReader(inputTestFile);
    ASSERT_TRUE(inputTestFile.good());
    ASSERT_FALSE(inputTestFile.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(R"(#pragma once)", fileReader.getLine());
    EXPECT_EQ(R"()", fileReader.getLine());
    EXPECT_EQ(R"(#include "file1.hpp")", fileReader.getLine());
    EXPECT_EQ(R"()", fileReader.getLine());
    EXPECT_EQ(R"(#include <Test1/Test1.hpp>)", fileReader.getLine());
    EXPECT_EQ(R"(#include <Test1/Test1_unit.hpp>)", fileReader.getLine());
    EXPECT_EQ(R"(#include <file2.hpp>)", fileReader.getLine());
    EXPECT_EQ(R"()", fileReader.getLine());
    EXPECT_EQ(R"(#include <QDebug>)", fileReader.getLine());
    EXPECT_EQ(R"(#include <QtWidgets>)", fileReader.getLine());
    EXPECT_EQ(R"(#include <gtest/gtest.h>)", fileReader.getLine());
    EXPECT_EQ(R"(#include <sys/types.h>)", fileReader.getLine());
    EXPECT_EQ(R"(#include <windows.h>)", fileReader.getLine());
    EXPECT_EQ(R"()", fileReader.getLine());
    EXPECT_EQ(R"(#include <string>)", fileReader.getLine());
    EXPECT_EQ(R"()", fileReader.getLine());
    EXPECT_EQ(R"(         This is a line in the code)", fileReader.getLine());
    EXPECT_EQ("       \t\t\t\t       This is another line in the code    ", fileReader.getLine());
    EXPECT_TRUE(fileReader.getLine().empty());
    EXPECT_FALSE(fileReader.isNotFinished());
}
TEST(CPlusPlusFileFixerTest, TrailingEmptyLineAreRemoved)
{
    CPlusPlusFileFixer fixer;    AlbaLocalPathHandler file1ToReadPathHandler(APRG_PROCESS_FILES_TEST_FILE1_TO_READ);
    ofstream testFile(file1ToReadPathHandler.getFullPath());
    ASSERT_TRUE(testFile.is_open());
    testFile << R"(         This is a line in the code)" << endl;
    testFile << "       \t\t\t\t       This is another line in the code    " << endl;
    testFile << R"()"<< endl;
    testFile << R"()"<< endl;
    testFile << R"()"<< endl;
    testFile << R"()"<< endl;
    testFile << R"()"<< endl;
    testFile.close();

    fixer.processFile(file1ToReadPathHandler.getFullPath());

    ifstream inputTestFile(file1ToReadPathHandler.getFullPath());
    ASSERT_TRUE(inputTestFile.is_open());

    AlbaFileReader fileReader(inputTestFile);
    ASSERT_TRUE(inputTestFile.good());
    ASSERT_FALSE(inputTestFile.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(R"(         This is a line in the code)", fileReader.getLine());
    EXPECT_EQ("       \t\t\t\t       This is another line in the code    ", fileReader.getLine());
    EXPECT_TRUE(fileReader.getLine().empty());
    EXPECT_FALSE(fileReader.isNotFinished());
}
TEST(CPlusPlusFileFixerTest, NamespaceFormattingIsCorrected)
{
    CPlusPlusFileFixer fixer;    AlbaLocalPathHandler file1ToReadPathHandler(APRG_PROCESS_FILES_TEST_FILE1_TO_READ);
    ofstream testFile(file1ToReadPathHandler.getFullPath());
    ASSERT_TRUE(testFile.is_open());
    testFile << R"(namespace samplenamespace {)" << endl;
    testFile << R"(})" << endl;
    testFile.close();

    fixer.processFile(file1ToReadPathHandler.getFullPath());

    ifstream inputTestFile(file1ToReadPathHandler.getFullPath());
    ASSERT_TRUE(inputTestFile.is_open());

    AlbaFileReader fileReader(inputTestFile);
    ASSERT_TRUE(inputTestFile.good());
    ASSERT_FALSE(inputTestFile.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(R"(namespace samplenamespace )", fileReader.getLine());
    EXPECT_EQ(R"({)", fileReader.getLine());
    EXPECT_EQ(R"(})", fileReader.getLine());
    EXPECT_TRUE(fileReader.getLine().empty());
    EXPECT_FALSE(fileReader.isNotFinished());
}
TEST(CPlusPlusFileFixerTest, SmallUInNumberIsConvertedToCapitalU)
{
    CPlusPlusFileFixer fixer;    AlbaLocalPathHandler file1ToReadPathHandler(APRG_PROCESS_FILES_TEST_FILE1_TO_READ);
    ofstream testFile(file1ToReadPathHandler.getFullPath());
    ASSERT_TRUE(testFile.is_open());
    testFile << R"(u)" << endl;
    testFile << R"(u1)" << endl;
    testFile << R"(uname)" << endl;
    testFile << R"(u_)" << endl;
    testFile << R"(u )" << endl;
    testFile << R"(5uname)" << endl;
    testFile << R"(5u1)" << endl;
    testFile << R"(5u_)" << endl;
    testFile << R"(5U)" << endl;
    testFile << R"(5U )" << endl;
    testFile << R"(5U/)" << endl;
    testFile << R"(10050U)" << endl;
    testFile << R"(1uname 99u)" << endl;
    testFile.close();

    fixer.processFile(file1ToReadPathHandler.getFullPath());

    ifstream inputTestFile(file1ToReadPathHandler.getFullPath());
    ASSERT_TRUE(inputTestFile.is_open());

    AlbaFileReader fileReader(inputTestFile);
    ASSERT_TRUE(inputTestFile.good());
    ASSERT_FALSE(inputTestFile.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(R"(u)", fileReader.getLine());
    EXPECT_EQ(R"(u1)", fileReader.getLine());
    EXPECT_EQ(R"(uname)", fileReader.getLine());
    EXPECT_EQ(R"(u_)", fileReader.getLine());
    EXPECT_EQ(R"(u )", fileReader.getLine());
    EXPECT_EQ(R"(5uname)", fileReader.getLine());
    EXPECT_EQ(R"(5u1)", fileReader.getLine());
    EXPECT_EQ(R"(5u_)", fileReader.getLine());
    EXPECT_EQ(R"(5U)", fileReader.getLine());
    EXPECT_EQ(R"(5U )", fileReader.getLine());
    EXPECT_EQ(R"(5U/)", fileReader.getLine());
    EXPECT_EQ(R"(10050U)", fileReader.getLine());
    EXPECT_EQ(R"(1uname 99U)", fileReader.getLine());
    EXPECT_TRUE(fileReader.getLine().empty());
    EXPECT_FALSE(fileReader.isNotFinished());
}
TEST(CPlusPlusFileFixerTest, DISABLED_TwoCascadingLoopsDetection)
{
    CPlusPlusFileFixer fixer;    AlbaLocalPathHandler file1ToReadPathHandler(APRG_PROCESS_FILES_TEST_FILE1_TO_READ);
    ofstream testFile(file1ToReadPathHandler.getFullPath());
    ASSERT_TRUE(testFile.is_open());
    testFile << R"(for(SomeDetailsHere))" << endl;
    testFile << R"(    while(SomeAdditionalDetailsHere))" << endl;
    testFile << R"(         while(SomeAdditionalDetailsHere))" << endl;
    testFile << R"(         })" << endl;
    testFile << R"(    })" << endl;
    testFile << R"(})" << endl;
    testFile.close();

    fixer.processFile(file1ToReadPathHandler.getFullPath());
}

}
