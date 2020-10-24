#include <File/AlbaFileReader.hpp>

#include <gtest/gtest.h>
#include <string>
using namespace alba;
using namespace std;
#define ALBA_FILE_READER_TEST_FILE R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\FileReaderTest\Test1.txt)"
#define ALBA_FILE_READER_SIZE_TEST_FILE R"(C:\APRG\AprgCommon\AprgCommon\tst\FilesForTests\FileReaderTest\Test2_SizeTest.txt)"

TEST(FileReadTest, ReadFromTestFile_VariousCharacterTests)
{
    ofstream testFile(ALBA_FILE_READER_TEST_FILE);
    ASSERT_TRUE(testFile.is_open());
    testFile << "1         " << endl;
    testFile << "12        " << endl;
    testFile << "123       " << endl;
    testFile << "1234      " << endl;
    testFile << "12345     " << endl;
    testFile << "123456    " << endl;
    testFile << "1234567   " << endl;
    testFile << "12345678  " << endl;
    testFile << "123456789 " << endl;
    testFile << "1234567890" << endl;
    testFile << "abcdefghijklmnopqrstuvwxyz                                                                          "  << endl;
    testFile << "" << endl;
    testFile << "    " << endl;
    testFile << "        " << endl;
    testFile << "            " << endl;
    testFile << "                " << endl;
    testFile << "                " << endl;
    testFile << "         " << endl;
    testFile << "               " << endl;
    testFile << "ABCDEFGHIJKLMNOPQRSTUVWXYZ" << endl;
    testFile << R"(!@#$%^&*()[]{}<>:;"'/\?)" << endl;
    testFile.close();


    ifstream inputTestFile(ALBA_FILE_READER_TEST_FILE);
    ASSERT_TRUE(inputTestFile.is_open());

    AlbaFileReader fileReader(inputTestFile);
    ASSERT_TRUE(inputTestFile.good());
    ASSERT_FALSE(inputTestFile.eof());
    EXPECT_EQ(fileReader.getLineAndIgnoreWhiteSpaces(), "1");
    EXPECT_EQ(fileReader.getLineAndIgnoreWhiteSpaces(), "12");
    EXPECT_EQ(fileReader.getLineAndIgnoreWhiteSpaces(), "123");
    EXPECT_EQ(fileReader.getLineAndIgnoreWhiteSpaces(), "1234");
    EXPECT_EQ(fileReader.getLineAndIgnoreWhiteSpaces(), "12345");
    EXPECT_EQ(fileReader.getLineAndIgnoreWhiteSpaces(), "123456");
    EXPECT_EQ(fileReader.getLineAndIgnoreWhiteSpaces(), "1234567");
    EXPECT_EQ(fileReader.getLineAndIgnoreWhiteSpaces(), "12345678");
    EXPECT_EQ(fileReader.getLineAndIgnoreWhiteSpaces(), "123456789");
    EXPECT_EQ(fileReader.getLineAndIgnoreWhiteSpaces(), "1234567890");
    EXPECT_EQ(fileReader.getLineAndIgnoreWhiteSpaces(), "abcdefghijklmnopqrstuvwxyz");
    EXPECT_EQ(fileReader.getLineAndIgnoreWhiteSpaces(), "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    EXPECT_EQ(fileReader.getLineAndIgnoreWhiteSpaces(), R"(!@#$%^&*()[]{}<>:;"'/\?)");
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(fileReader.getLineAndIgnoreWhiteSpaces(), "");
    EXPECT_FALSE(fileReader.isNotFinished());
}

TEST(FileReadTest, ReadFromTestFile_SizeTest)
{
    ifstream inputTestFile(ALBA_FILE_READER_SIZE_TEST_FILE);
    ASSERT_TRUE(inputTestFile.is_open());

    AlbaFileReader fileReader(inputTestFile);
    fileReader.setMaxBufferSize(2000);
    EXPECT_EQ(fileReader.getFileSize(), 5000);
    ASSERT_TRUE(inputTestFile.good());
    ASSERT_FALSE(inputTestFile.eof());
    EXPECT_EQ(fileReader.getLineAndIgnoreWhiteSpaces().length(), 2000);
    EXPECT_EQ(fileReader.getLineAndIgnoreWhiteSpaces().length(), 2000);
    EXPECT_EQ(fileReader.getLineAndIgnoreWhiteSpaces().length(), 1000);
    EXPECT_FALSE(fileReader.isNotFinished());
    EXPECT_EQ(fileReader.getLineAndIgnoreWhiteSpaces(), "");
}
