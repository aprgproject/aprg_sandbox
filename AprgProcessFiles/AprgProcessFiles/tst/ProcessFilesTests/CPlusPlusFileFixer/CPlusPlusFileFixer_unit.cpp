#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <ProcessFiles/CPlusPlusFileFixer/CPlusPlusFileFixer.hpp>
#include <ProcessFilesTests/DirectoryConstants.hpp>

#include <gtest/gtest.h>

#include <fstream>
#include <string>

using namespace std;

namespace alba
{

TEST(CPlusPlusFileFixerTest, DISABLED_ActualRun)
{
    CPlusPlusFileFixer fixer;
    fixer.processDirectory(R"(N:\Branches\APRG_TEMP\)");
}

TEST(CPlusPlusFileFixerTest, CPlusPlusFileHeadersAreCorrected)
{
    CPlusPlusFileFixer fixer;
    AlbaLocalPathHandler file1ToReadPathHandler(APRG_PROCESS_FILES_TEST_FILE1_TO_READ);
    ofstream testFile(file1ToReadPathHandler.getFullPath());
    ASSERT_TRUE(testFile.is_open());
    testFile << R"(#include <file2.hpp>)" << "\n";
    testFile << R"(#include<string>)" << "\n";
    testFile << R"(#include <gtest/gtest.h> )" << "\n";
    testFile << R"(#include <windows.h> )" << "\n";
    testFile << R"(#include <sys/types.h> )" << "\n";
    testFile << "   #pragma once\t\t\t \n";
    testFile << R"()" << "\n";
    testFile << R"(#include "file1.hpp")" << "\n";
    testFile << R"()" << "\n";
    testFile << R"(#include <QDebug>)" << "\n";
    testFile << R"(#include <QtWidgets>)" << "\n";
    testFile << R"(#include <Test1\Test1.hpp>)" << "\n";
    testFile << R"(#include <Test1\Test1_unit.hpp>)" << "\n";
    testFile << R"(         This is a line in the code)" << "\n";
    testFile << "       \t\t\t\t       This is another line in the code    \n";
    testFile.close();

    fixer.processFile(file1ToReadPathHandler.getFullPath());
    ifstream inputTestFile(file1ToReadPathHandler.getFullPath());
    ASSERT_TRUE(inputTestFile.is_open());
    AlbaFileReader fileReader(inputTestFile);    ASSERT_TRUE(inputTestFile.good());
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

TEST(CPlusPlusFileFixerTest, CPlusPlusFileMainHeaderIsConvertedToQuotationHeader)
{
    CPlusPlusFileFixer fixer;
    AlbaLocalPathHandler file1ToReadPathHandler(APRG_PROCESS_FILES_TEST_FILE1_TO_READ);
    ofstream testFile(file1ToReadPathHandler.getFullPath());
    ASSERT_TRUE(testFile.is_open());
    testFile << R"(#include <)" << file1ToReadPathHandler.getFile() << R"(>)" << "\n";
    testFile << R"(#include <DirectoryDoesNotMatch/)" << file1ToReadPathHandler.getFile() << R"(>)" << "\n";
    testFile.close();

    fixer.processFile(file1ToReadPathHandler.getFullPath());
    ifstream inputTestFile(file1ToReadPathHandler.getFullPath());
    ASSERT_TRUE(inputTestFile.is_open());
    AlbaFileReader fileReader(inputTestFile);    ASSERT_TRUE(inputTestFile.good());
    ASSERT_FALSE(inputTestFile.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(R"(#include "Test1.txt")", fileReader.getLine());
    EXPECT_EQ(R"()", fileReader.getLine());
    EXPECT_EQ(R"(#include <DirectoryDoesNotMatch/Test1.txt>)", fileReader.getLine());
    EXPECT_TRUE(fileReader.getLine().empty());
    EXPECT_TRUE(fileReader.getLine().empty());
    EXPECT_FALSE(fileReader.isNotFinished());
}

TEST(CPlusPlusFileFixerTest, TrailingEmptyLineAreRemoved)
{
    CPlusPlusFileFixer fixer;
    AlbaLocalPathHandler file1ToReadPathHandler(APRG_PROCESS_FILES_TEST_FILE1_TO_READ);
    ofstream testFile(file1ToReadPathHandler.getFullPath());
    ASSERT_TRUE(testFile.is_open());
    testFile << R"(         This is a line in the code)" << "\n";
    testFile << "       \t\t\t\t       This is another line in the code    \n";
    testFile << "\n\n\n\n\n";
    testFile.close();

    fixer.processFile(file1ToReadPathHandler.getFullPath());
    ifstream inputTestFile(file1ToReadPathHandler.getFullPath());
    ASSERT_TRUE(inputTestFile.is_open());
    AlbaFileReader fileReader(inputTestFile);    ASSERT_TRUE(inputTestFile.good());
    ASSERT_FALSE(inputTestFile.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(R"(         This is a line in the code)", fileReader.getLine());
    EXPECT_EQ("       \t\t\t\t       This is another line in the code    ", fileReader.getLine());
    EXPECT_TRUE(fileReader.getLine().empty());
    EXPECT_FALSE(fileReader.isNotFinished());
}

TEST(CPlusPlusFileFixerTest, NamespaceFormattingIsCorrected)
{
    CPlusPlusFileFixer fixer;
    AlbaLocalPathHandler file1ToReadPathHandler(APRG_PROCESS_FILES_TEST_FILE1_TO_READ);
    ofstream testFile(file1ToReadPathHandler.getFullPath());
    ASSERT_TRUE(testFile.is_open());
    testFile << R"(namespace samplenamespace {)" << "\n";
    testFile << R"(})" << "\n";
    testFile.close();

    fixer.processFile(file1ToReadPathHandler.getFullPath());
    ifstream inputTestFile(file1ToReadPathHandler.getFullPath());
    ASSERT_TRUE(inputTestFile.is_open());
    AlbaFileReader fileReader(inputTestFile);    ASSERT_TRUE(inputTestFile.good());
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
    CPlusPlusFileFixer fixer;
    AlbaLocalPathHandler file1ToReadPathHandler(APRG_PROCESS_FILES_TEST_FILE1_TO_READ);
    ofstream testFile(file1ToReadPathHandler.getFullPath());
    ASSERT_TRUE(testFile.is_open());
    testFile << R"(u)" << "\n";
    testFile << R"(u1)" << "\n";
    testFile << R"(uname)" << "\n";
    testFile << R"(u_)" << "\n";
    testFile << R"(u )" << "\n";
    testFile << R"(5uname)" << "\n";
    testFile << R"(5u1)" << "\n";
    testFile << R"(5u_)" << "\n";
    testFile << R"(5U)" << "\n";
    testFile << R"(5U )" << "\n";
    testFile << R"(5U/)" << "\n";
    testFile << R"(10050U)" << "\n";
    testFile << R"(1uname 99u)" << "\n";
    testFile.close();

    fixer.processFile(file1ToReadPathHandler.getFullPath());
    ifstream inputTestFile(file1ToReadPathHandler.getFullPath());
    ASSERT_TRUE(inputTestFile.is_open());
    AlbaFileReader fileReader(inputTestFile);    ASSERT_TRUE(inputTestFile.good());
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
    CPlusPlusFileFixer fixer;
    AlbaLocalPathHandler file1ToReadPathHandler(APRG_PROCESS_FILES_TEST_FILE1_TO_READ);
    ofstream testFile(file1ToReadPathHandler.getFullPath());
    ASSERT_TRUE(testFile.is_open());
    testFile << R"(for(SomeDetailsHere))" << "\n";
    testFile << R"(    while(SomeAdditionalDetailsHere))" << "\n";
    testFile << R"(         while(SomeAdditionalDetailsHere))" << "\n";
    testFile << R"(         })" << "\n";
    testFile << R"(    })" << "\n";
    testFile << R"(})" << "\n";
    testFile.close();

    fixer.processFile(file1ToReadPathHandler.getFullPath());}

}