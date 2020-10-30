#include <CPlusPlusFileFixer/CPlusPlusFileFixer.hpp>
#include <DirectoryConstants.hpp>
#include <File/AlbaFileReader.hpp>

#include <gtest/gtest.h>

#include <fstream>
#include <string>

using namespace alba;
using namespace std;

TEST(CPlusPlusFileFixerTest, ActualRun)
{
    CPlusPlusFileFixer fixer;
    fixer.processDirectory(R"(C:\APRG_CLEAN_COPY\)");
    //fixer.processDirectory(R"(C:\APRG\TcomTools\)");
    //fixer.processFile(R"(C:\APRG\AprgCommon\AprgCommon\tst\AlbaStringHelper_unit.cpp)");
}

TEST(CPlusPlusFileFixerTest, CPlusPlusFileHeadersTest)
{
    CPlusPlusFileFixer fixer;
    ofstream testFile(APRG_PROCESS_FILES_TEST_FILE_TO_READ);
    ASSERT_TRUE(testFile.is_open());
    testFile << R"(#include <file2.hpp>)" << endl;
    testFile << R"(#include<string>)" << endl;
    testFile << R"(#include <gtest/gtest.h> )" << endl;
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

    fixer.processFile(APRG_PROCESS_FILES_TEST_FILE_TO_READ);

    ifstream inputTestFile(APRG_PROCESS_FILES_TEST_FILE_TO_READ);
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
    EXPECT_EQ(R"()", fileReader.getLine());
    EXPECT_EQ(R"(#include <file2.hpp>)", fileReader.getLine());
    EXPECT_EQ(R"()", fileReader.getLine());
    EXPECT_EQ(R"(#include <QDebug>)", fileReader.getLine());
    EXPECT_EQ(R"(#include <QtWidgets>)", fileReader.getLine());
    EXPECT_EQ(R"(#include <gtest/gtest.h>)", fileReader.getLine());
    EXPECT_EQ(R"()", fileReader.getLine());
    EXPECT_EQ(R"(#include <string>)", fileReader.getLine());
    EXPECT_EQ(R"()", fileReader.getLine());
    EXPECT_EQ(R"(         This is a line in the code)", fileReader.getLine());
    EXPECT_EQ("       \t\t\t\t       This is another line in the code    ", fileReader.getLine());
    EXPECT_EQ("", fileReader.getLine());
    EXPECT_FALSE(fileReader.isNotFinished());
}

TEST(CPlusPlusFileFixerTest, RemoveTrailingEmptyLineTest)
{
    CPlusPlusFileFixer fixer;
    ofstream testFile(APRG_PROCESS_FILES_TEST_FILE_TO_READ);
    ASSERT_TRUE(testFile.is_open());
    testFile << R"(         This is a line in the code)" << endl;
    testFile << "       \t\t\t\t       This is another line in the code    " << endl;
    testFile << R"()"<< endl;
    testFile << R"()"<< endl;
    testFile << R"()"<< endl;
    testFile << R"()"<< endl;
    testFile << R"()"<< endl;
    testFile.close();

    fixer.processFile(APRG_PROCESS_FILES_TEST_FILE_TO_READ);

    ifstream inputTestFile(APRG_PROCESS_FILES_TEST_FILE_TO_READ);
    ASSERT_TRUE(inputTestFile.is_open());

    AlbaFileReader fileReader(inputTestFile);
    ASSERT_TRUE(inputTestFile.good());
    ASSERT_FALSE(inputTestFile.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(R"(         This is a line in the code)", fileReader.getLine());
    EXPECT_EQ("       \t\t\t\t       This is another line in the code    ", fileReader.getLine());
    EXPECT_EQ("", fileReader.getLine());
    EXPECT_FALSE(fileReader.isNotFinished());
}

TEST(CPlusPlusFileFixerTest, NamespaceCorrection)
{
    CPlusPlusFileFixer fixer;
    ofstream testFile(APRG_PROCESS_FILES_TEST_FILE_TO_READ);
    ASSERT_TRUE(testFile.is_open());
    testFile << R"(namespace samplenamespace {)" << endl;
    testFile << R"(})" << endl;
    testFile.close();

    fixer.processFile(APRG_PROCESS_FILES_TEST_FILE_TO_READ);

    ifstream inputTestFile(APRG_PROCESS_FILES_TEST_FILE_TO_READ);
    ASSERT_TRUE(inputTestFile.is_open());

    AlbaFileReader fileReader(inputTestFile);
    ASSERT_TRUE(inputTestFile.good());
    ASSERT_FALSE(inputTestFile.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(R"(namespace samplenamespace )", fileReader.getLine());
    EXPECT_EQ(R"({)", fileReader.getLine());
    EXPECT_EQ(R"(})", fileReader.getLine());
    EXPECT_EQ("", fileReader.getLine());
    EXPECT_FALSE(fileReader.isNotFinished());
}

TEST(CPlusPlusFileFixerTest, DISABLED_TwoCascadingLoopsDetection)
{
    CPlusPlusFileFixer fixer;
    ofstream testFile(APRG_PROCESS_FILES_TEST_FILE_TO_READ);
    ASSERT_TRUE(testFile.is_open());
    testFile << R"(for(SomeDetailsHere))" << endl;
    testFile << R"(    while(SomeAdditionalDetailsHere))" << endl;
    testFile << R"(         while(SomeAdditionalDetailsHere))" << endl;
    testFile << R"(         })" << endl;
    testFile << R"(    })" << endl;
    testFile << R"(})" << endl;
    testFile.close();

    fixer.processFile(APRG_PROCESS_FILES_TEST_FILE_TO_READ);
}
