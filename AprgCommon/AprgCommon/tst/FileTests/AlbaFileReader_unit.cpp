#include <DirectoryConstants.hpp>
#include <File/AlbaFileReader.hpp>
#include <PathHandlers/AlbaLocalPathHandler.hpp>

#include <gtest/gtest.h>

#include <string>

using namespace std;

namespace alba
{

TEST(FileReadTest, ReadFromTestFile_ConstructorsWorks)
{
    ifstream inputTestFile(APRG_COMMON_TEST_FILE_TO_READ);
    ASSERT_TRUE(inputTestFile.is_open());

    AlbaFileReader fileReader1(inputTestFile);
    EXPECT_EQ(10000, fileReader1.getMaxBufferSize());
    AlbaFileReader fileReader2(inputTestFile, 200);
    EXPECT_EQ(200, fileReader2.getMaxBufferSize());
}

TEST(FileReadTest, ReadFromTestFile_SetAndGetBufferSizeWorks)
{
    ifstream inputTestFile(APRG_COMMON_TEST_FILE_TO_READ);
    ASSERT_TRUE(inputTestFile.is_open());

    AlbaFileReader fileReader(inputTestFile);
    EXPECT_EQ(10000, fileReader.getMaxBufferSize());
    fileReader.setMaxBufferSize(200);
    EXPECT_EQ(200, fileReader.getMaxBufferSize());
}

TEST(FileReadTest, ReadFromTestFile_ReadLineUsingVariousCharacters)
{
    AlbaLocalPathHandler commonTestFileToRead(APRG_COMMON_TEST_FILE_TO_READ);
    ofstream testFile(commonTestFileToRead.getFullPath());
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

    ifstream inputTestFile(commonTestFileToRead.getFullPath());
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
    AlbaLocalPathHandler commonSizeTestFileToRead(ALBA_COMMON_SIZE_TEST_FILE);
    ifstream inputTestFile(commonSizeTestFileToRead.getFullPath());
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
    AlbaLocalPathHandler commonTestFileToRead(APRG_COMMON_TEST_FILE_TO_READ);
    ofstream testFile(commonTestFileToRead.getFullPath());
    ASSERT_TRUE(testFile.is_open());
    testFile << "123!@# \t\n";
    testFile.close();

    ifstream inputTestFile(commonTestFileToRead.getFullPath(), ios::binary);
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
#ifdef OS_WINDOWS
    EXPECT_EQ('\r' ,fileReader.getCharacter());
    EXPECT_EQ('\n' ,fileReader.getCharacter());
#endif
#ifdef OS_LINUX
   EXPECT_EQ('\n' ,fileReader.getCharacter());
#endif
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(fileReader.getCharacter(), 0);
    EXPECT_FALSE(fileReader.isNotFinished());
}

TEST(FileReadTest, ReadFromTestFile_ReadMultipleCharacters)
{
    AlbaLocalPathHandler commonTestFileToRead(APRG_COMMON_TEST_FILE_TO_READ);
    ofstream testFile(commonTestFileToRead.getFullPath());
    ASSERT_TRUE(testFile.is_open());
    testFile << "123!@# \t\n";
    testFile.close();

    ifstream inputTestFile(commonTestFileToRead.getFullPath(), ios::binary);
    ASSERT_TRUE(inputTestFile.is_open());

    AlbaFileReader fileReader(inputTestFile);
    ASSERT_TRUE(inputTestFile.good());
    ASSERT_FALSE(inputTestFile.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    unsigned int numberOfCharacters=3;
    char* charPointer;
    charPointer = fileReader.getCharacters(numberOfCharacters);
    EXPECT_EQ("123", string(charPointer, numberOfCharacters));
    EXPECT_EQ(3u, numberOfCharacters);
    charPointer = fileReader.getCharacters(numberOfCharacters);
    EXPECT_EQ("!@#", string(charPointer, numberOfCharacters));
    EXPECT_EQ(3u, numberOfCharacters);

#ifdef OS_WINDOWS
    charPointer = fileReader.getCharacters(numberOfCharacters);
    EXPECT_EQ(" \t\r", string(charPointer, numberOfCharacters));
    EXPECT_EQ(3u, numberOfCharacters);
    EXPECT_TRUE(fileReader.isNotFinished());
    charPointer = fileReader.getCharacters(numberOfCharacters);
    EXPECT_EQ("\n", string(charPointer, numberOfCharacters));
    EXPECT_EQ(1u, numberOfCharacters);
#endif
#ifdef OS_LINUX
    charPointer = fileReader.getCharacters(numberOfCharacters);
    EXPECT_EQ(" \t\n", string(charPointer, numberOfCharacters));
    EXPECT_EQ(3u, numberOfCharacters);
    EXPECT_TRUE(fileReader.isNotFinished());
    charPointer = fileReader.getCharacters(numberOfCharacters);
    EXPECT_EQ("", string(charPointer, numberOfCharacters));
    EXPECT_EQ(0, numberOfCharacters);
#endif
    EXPECT_FALSE(fileReader.isNotFinished());
}

TEST(FileReadTest, ReadFromTestFile_RequestToReadMultipleCharactersThatIsTheBeyondBufferSize)
{
    AlbaLocalPathHandler commonTestFileToRead(APRG_COMMON_TEST_FILE_TO_READ);
    ofstream testFile(commonTestFileToRead.getFullPath());
    ASSERT_TRUE(testFile.is_open());
    testFile << "12345";
    testFile.close();

    ifstream inputTestFile(commonTestFileToRead.getFullPath(), ios::binary);
    ASSERT_TRUE(inputTestFile.is_open());

    AlbaFileReader fileReader(inputTestFile);
    fileReader.setMaxBufferSize(3);
    ASSERT_TRUE(inputTestFile.good());
    ASSERT_FALSE(inputTestFile.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    unsigned int numberOfCharacters=20000;
    char* charPointer;
    charPointer = fileReader.getCharacters(numberOfCharacters);
    EXPECT_EQ("123", string(charPointer, numberOfCharacters));
    EXPECT_EQ(3u, numberOfCharacters);
    EXPECT_TRUE(fileReader.isNotFinished());
    numberOfCharacters=20000;
    charPointer = fileReader.getCharacters(numberOfCharacters);
    EXPECT_EQ("45", string(charPointer, numberOfCharacters));
    EXPECT_EQ(2, numberOfCharacters);
    EXPECT_FALSE(fileReader.isNotFinished());
}

TEST(FileReadTest, ReadFromTestFile_ReadTwoByteNumbers)
{
    AlbaLocalPathHandler commonTestFileToRead(APRG_COMMON_TEST_FILE_TO_READ);
    ofstream testFile(commonTestFileToRead.getFullPath());
    ASSERT_TRUE(testFile.is_open());
    testFile.put(0x01);
    testFile.put(0x23);
    testFile.put(0x45);
    testFile.put(0x67);
    testFile.put(static_cast<char>(0xA1));
    testFile.put(static_cast<char>(0xBA));
    testFile.close();

    ifstream inputTestFile(commonTestFileToRead.getFullPath(), ios::binary);
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
    AlbaLocalPathHandler commonTestFileToRead(APRG_COMMON_TEST_FILE_TO_READ);
    ofstream testFile(commonTestFileToRead.getFullPath());
    ASSERT_TRUE(testFile.is_open());
    testFile.put(0x01);
    testFile.put(0x23);
    testFile.put(0x45);
    testFile.put(0x67);
    testFile.put(static_cast<char>(0xA1));
    testFile.put(static_cast<char>(0xBA));
    testFile.close();

    ifstream inputTestFile(commonTestFileToRead.getFullPath(), ios::binary);
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
    AlbaLocalPathHandler commonTestFileToRead(APRG_COMMON_TEST_FILE_TO_READ);
    ofstream testFile(commonTestFileToRead.getFullPath());
    ASSERT_TRUE(testFile.is_open());
    testFile.put(0x01);
    testFile.put(0x23);
    testFile.put(0x45);
    testFile.put(0x67);
    testFile.put(static_cast<char>(0xA1));
    testFile.put(static_cast<char>(0xBA));
    testFile.close();

    ifstream inputTestFile(commonTestFileToRead.getFullPath(), ios::binary);
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
    AlbaLocalPathHandler commonTestFileToRead(APRG_COMMON_TEST_FILE_TO_READ);
    ofstream testFile(commonTestFileToRead.getFullPath());
    ASSERT_TRUE(testFile.is_open());
    testFile.put(0x01);
    testFile.put(0x23);
    testFile.put(0x45);
    testFile.put(0x67);
    testFile.put(static_cast<char>(0xA1));
    testFile.put(static_cast<char>(0xBA));
    testFile.close();

    ifstream inputTestFile(commonTestFileToRead.getFullPath(), ios::binary);
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
    AlbaLocalPathHandler commonTestFileToRead(APRG_COMMON_TEST_FILE_TO_READ);
    ofstream testFile(commonTestFileToRead.getFullPath());
    ASSERT_TRUE(testFile.is_open());
    testFile.put(0x01);
    testFile.put(0x23);
    testFile.put(0x45);
    testFile.put(0x67);
    testFile.put(static_cast<char>(0xA1));
    testFile.put(static_cast<char>(0xBA));
    testFile.close();

    ifstream inputTestFile(commonTestFileToRead.getFullPath(), ios::binary);
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
    AlbaLocalPathHandler commonTestFileToRead(APRG_COMMON_TEST_FILE_TO_READ);
    ofstream testFile(commonTestFileToRead.getFullPath());
    ASSERT_TRUE(testFile.is_open());
    testFile.put(0x01);
    testFile.put(0x23);
    testFile.put(0x45);
    testFile.put(0x67);
    testFile.put(static_cast<char>(0xA1));
    testFile.put(static_cast<char>(0xBA));
    testFile.close();

    ifstream inputTestFile(commonTestFileToRead.getFullPath(), ios::binary);
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

}
