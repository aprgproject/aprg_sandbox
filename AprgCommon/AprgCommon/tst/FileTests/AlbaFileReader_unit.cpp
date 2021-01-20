#include <DirectoryConstants.hpp>
#include <File/AlbaFileReader.hpp>

#include <gtest/gtest.h>

#include <string>

using namespace alba;
using namespace std;

TEST(FileReadTest, ReadFromTestFile_ReadLineUsingVariousCharacters)
{
    ofstream testFile(APRG_COMMON_TEST_FILE_TO_READ);
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


    ifstream inputTestFile(APRG_COMMON_TEST_FILE_TO_READ);
    ASSERT_TRUE(inputTestFile.is_open());

    AlbaFileReader fileReader(inputTestFile);
    ASSERT_TRUE(inputTestFile.good());
    ASSERT_FALSE(inputTestFile.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ("1", fileReader.getLineAndIgnoreWhiteSpaces());
    EXPECT_EQ("12", fileReader.getLineAndIgnoreWhiteSpaces());
    EXPECT_EQ("123", fileReader.getLineAndIgnoreWhiteSpaces());
    EXPECT_EQ("1234", fileReader.getLineAndIgnoreWhiteSpaces());
    EXPECT_EQ("12345", fileReader.getLineAndIgnoreWhiteSpaces());
    EXPECT_EQ("123456", fileReader.getLineAndIgnoreWhiteSpaces());
    EXPECT_EQ("1234567", fileReader.getLineAndIgnoreWhiteSpaces());
    EXPECT_EQ("12345678", fileReader.getLineAndIgnoreWhiteSpaces());
    EXPECT_EQ("123456789", fileReader.getLineAndIgnoreWhiteSpaces());
    EXPECT_EQ("1234567890", fileReader.getLineAndIgnoreWhiteSpaces());
    EXPECT_EQ("abcdefghijklmnopqrstuvwxyz", fileReader.getLineAndIgnoreWhiteSpaces());
    EXPECT_EQ("ABCDEFGHIJKLMNOPQRSTUVWXYZ", fileReader.getLineAndIgnoreWhiteSpaces());
    EXPECT_EQ(R"(!@#$%^&*()[]{}<>:;"'/\?)", fileReader.getLineAndIgnoreWhiteSpaces());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ("", fileReader.getLineAndIgnoreWhiteSpaces());
    EXPECT_FALSE(fileReader.isNotFinished());
}

TEST(FileReadTest, ReadFromTestFile_ReadLineWithSizeLimit)
{
    ifstream inputTestFile(ALBA_COMMON_SIZE_TEST_FILE);
    ASSERT_TRUE(inputTestFile.is_open());

    AlbaFileReader fileReader(inputTestFile);
    fileReader.setMaxBufferSize(2000);
    EXPECT_EQ(5000, fileReader.getFileSize());
    ASSERT_TRUE(inputTestFile.good());
    ASSERT_FALSE(inputTestFile.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(2000u, fileReader.getLineAndIgnoreWhiteSpaces().length());
    EXPECT_EQ(2000u, fileReader.getLineAndIgnoreWhiteSpaces().length());
    EXPECT_EQ(1000u, fileReader.getLineAndIgnoreWhiteSpaces().length());
    EXPECT_FALSE(fileReader.isNotFinished());
    EXPECT_EQ("", fileReader.getLineAndIgnoreWhiteSpaces());
}

TEST(FileReadTest, ReadFromTestFile_ReadSingleCharacterFromBinaryFile)
{
    ofstream testFile(APRG_COMMON_TEST_FILE_TO_READ);
    ASSERT_TRUE(testFile.is_open());
    testFile << "123!@# \t\n";
    testFile.close();


    ifstream inputTestFile(APRG_COMMON_TEST_FILE_TO_READ, ios::binary);
    ASSERT_TRUE(inputTestFile.is_open());

    AlbaFileReader fileReader(inputTestFile);
    ASSERT_TRUE(inputTestFile.good());
    ASSERT_FALSE(inputTestFile.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ('1' ,fileReader.getCharacter());
    EXPECT_EQ('2' ,fileReader.getCharacter());
    EXPECT_EQ('3' ,fileReader.getCharacter());
    EXPECT_EQ('!' ,fileReader.getCharacter());
    EXPECT_EQ('@' ,fileReader.getCharacter());
    EXPECT_EQ('#' ,fileReader.getCharacter());
    EXPECT_EQ(' ' ,fileReader.getCharacter());
    EXPECT_EQ('\t' ,fileReader.getCharacter());
    EXPECT_EQ('\r' ,fileReader.getCharacter());
    EXPECT_EQ('\n' ,fileReader.getCharacter());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(fileReader.getCharacter(), 0);
    EXPECT_FALSE(fileReader.isNotFinished());
}

TEST(FileReadTest, ReadFromTestFile_ReadMultipleCharacters)
{
    ofstream testFile(APRG_COMMON_TEST_FILE_TO_READ);
    ASSERT_TRUE(testFile.is_open());
    testFile << "123!@# \t\n";
    testFile.close();


    ifstream inputTestFile(APRG_COMMON_TEST_FILE_TO_READ, ios::binary);
    ASSERT_TRUE(inputTestFile.is_open());

    AlbaFileReader fileReader(inputTestFile);
    ASSERT_TRUE(inputTestFile.good());
    ASSERT_FALSE(inputTestFile.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    unsigned int numberOfCharacters=3;
    EXPECT_EQ("123", string(fileReader.getCharacters(numberOfCharacters), numberOfCharacters));
    EXPECT_EQ(3u, numberOfCharacters);
    EXPECT_EQ("!@#", string(fileReader.getCharacters(numberOfCharacters), numberOfCharacters));
    EXPECT_EQ(3u, numberOfCharacters);
    EXPECT_EQ(" \t\r", string(fileReader.getCharacters(numberOfCharacters), numberOfCharacters));
    EXPECT_EQ(3u, numberOfCharacters);
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ("\n", string(fileReader.getCharacters(numberOfCharacters), 1));
    EXPECT_EQ(1u, numberOfCharacters);
    EXPECT_FALSE(fileReader.isNotFinished());
}
TEST(FileReadTest, ReadFromTestFile_ReadTwoByteNumbers)
{
    ofstream testFile(APRG_COMMON_TEST_FILE_TO_READ);    ASSERT_TRUE(testFile.is_open());
    testFile.put(0x01);
    testFile.put(0x23);
    testFile.put(0x45);
    testFile.put(0x67);
    testFile.put((char)0xA1);
    testFile.put((char)0xBA);
    testFile.close();


    ifstream inputTestFile(APRG_COMMON_TEST_FILE_TO_READ, ios::binary);
    ASSERT_TRUE(inputTestFile.is_open());

    AlbaFileReader fileReader(inputTestFile);
    ASSERT_TRUE(inputTestFile.good());
    ASSERT_FALSE(inputTestFile.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(0x0123u, fileReader.getTwoByteData<unsigned int>());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(0x4567u, fileReader.getTwoByteData<unsigned int>());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(0xA1BAu, fileReader.getTwoByteData<unsigned int>());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(0x0u, fileReader.getTwoByteData<unsigned int>());
    EXPECT_FALSE(fileReader.isNotFinished());
}
TEST(FileReadTest, ReadFromTestFile_ReadFourByteNumbers)
{
    ofstream testFile(APRG_COMMON_TEST_FILE_TO_READ);    ASSERT_TRUE(testFile.is_open());
    testFile.put(0x01);
    testFile.put(0x23);
    testFile.put(0x45);
    testFile.put(0x67);
    testFile.put((char)0xA1);
    testFile.put((char)0xBA);
    testFile.close();


    ifstream inputTestFile(APRG_COMMON_TEST_FILE_TO_READ, ios::binary);
    ASSERT_TRUE(inputTestFile.is_open());

    AlbaFileReader fileReader(inputTestFile);
    ASSERT_TRUE(inputTestFile.good());
    ASSERT_FALSE(inputTestFile.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(0x01234567u, fileReader.getFourByteData<unsigned int>());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(0xA1BAu, fileReader.getFourByteData<unsigned int>());
    EXPECT_FALSE(fileReader.isNotFinished());
}
TEST(FileReadTest, ReadFromTestFile_ReadEightByteNumbers)
{
    ofstream testFile(APRG_COMMON_TEST_FILE_TO_READ);    ASSERT_TRUE(testFile.is_open());
    testFile.put(0x01);
    testFile.put(0x23);
    testFile.put(0x45);
    testFile.put(0x67);
    testFile.put((char)0xA1);
    testFile.put((char)0xBA);
    testFile.close();


    ifstream inputTestFile(APRG_COMMON_TEST_FILE_TO_READ, ios::binary);
    ASSERT_TRUE(inputTestFile.is_open());

    AlbaFileReader fileReader(inputTestFile);
    ASSERT_TRUE(inputTestFile.good());
    ASSERT_FALSE(inputTestFile.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(0x000001234567A1BAu, fileReader.getEightByteData<unsigned long long>());
    EXPECT_FALSE(fileReader.isNotFinished());
}
TEST(FileReadTest, ReadFromTestFile_ReadSwappedTwoByteNumbers)
{
    ofstream testFile(APRG_COMMON_TEST_FILE_TO_READ);    ASSERT_TRUE(testFile.is_open());
    testFile.put(0x01);
    testFile.put(0x23);
    testFile.put(0x45);
    testFile.put(0x67);
    testFile.put((char)0xA1);
    testFile.put((char)0xBA);
    testFile.close();


    ifstream inputTestFile(APRG_COMMON_TEST_FILE_TO_READ, ios::binary);
    ASSERT_TRUE(inputTestFile.is_open());

    AlbaFileReader fileReader(inputTestFile);
    ASSERT_TRUE(inputTestFile.good());
    ASSERT_FALSE(inputTestFile.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(0x2301u, fileReader.getTwoByteSwappedData<unsigned int>());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(0x6745u, fileReader.getTwoByteSwappedData<unsigned int>());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(0xBAA1u, fileReader.getTwoByteSwappedData<unsigned int>());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(0x0u, fileReader.getTwoByteSwappedData<unsigned int>());
    EXPECT_FALSE(fileReader.isNotFinished());
}
TEST(FileReadTest, ReadFromTestFile_ReadSwappedEightByteNumbers)
{
    ofstream testFile(APRG_COMMON_TEST_FILE_TO_READ);    ASSERT_TRUE(testFile.is_open());
    testFile.put(0x01);
    testFile.put(0x23);
    testFile.put(0x45);
    testFile.put(0x67);
    testFile.put((char)0xA1);
    testFile.put((char)0xBA);
    testFile.close();


    ifstream inputTestFile(APRG_COMMON_TEST_FILE_TO_READ, ios::binary);
    ASSERT_TRUE(inputTestFile.is_open());

    AlbaFileReader fileReader(inputTestFile);
    ASSERT_TRUE(inputTestFile.good());
    ASSERT_FALSE(inputTestFile.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(0xBAA1674523010000u, fileReader.getEightByteSwappedData<unsigned long long>());
    EXPECT_FALSE(fileReader.isNotFinished());
}
TEST(FileReadTest, ReadFromTestFile_FileContentsCanBeSavedInMemoryBuffer)
{
    ofstream testFile(APRG_COMMON_TEST_FILE_TO_READ);    ASSERT_TRUE(testFile.is_open());
    testFile.put(0x01);
    testFile.put(0x23);
    testFile.put(0x45);
    testFile.put(0x67);
    testFile.put((char)0xA1);
    testFile.put((char)0xBA);
    testFile.close();


    ifstream inputTestFile(APRG_COMMON_TEST_FILE_TO_READ, ios::binary);
    ASSERT_TRUE(inputTestFile.is_open());

    AlbaFileReader fileReader(inputTestFile);
    ASSERT_TRUE(inputTestFile.good());
    ASSERT_FALSE(inputTestFile.eof());
    EXPECT_TRUE(fileReader.isNotFinished());

    AlbaMemoryBuffer buffer;
    fileReader.saveDataToMemoryBuffer(buffer, 8);
    unsigned char* reader = reinterpret_cast<unsigned char*>(buffer.getBufferPointer());
    EXPECT_EQ(0x01u, reader[0]);
    EXPECT_EQ(0x23u, reader[1]);
    EXPECT_EQ(0x45u, reader[2]);
    EXPECT_EQ(0x67u, reader[3]);
    EXPECT_EQ(0xA1u, reader[4]);
    EXPECT_EQ(0xBAu, reader[5]);
    EXPECT_FALSE(fileReader.isNotFinished());
}