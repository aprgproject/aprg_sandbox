#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <CommonTests/DirectoryConstants.hpp>

#include <gtest/gtest.h>

#include <string>

using namespace std;

namespace alba {

void writeTextWithSpaces(ofstream& testFile) {
    testFile << "1         \n";
    testFile << "12        \n";
    testFile << "123       \n";
    testFile << "1234      \n";
    testFile << "12345     \n";
    testFile << "123456    \n";
    testFile << "1234567   \n";
    testFile << "12345678  \n";
    testFile << "123456789 \n";
    testFile << "1234567890\n";
    testFile << "abcdefghijklmnopqrstuvwxyz                \n";
    testFile << "\n";
    testFile << "    \n";
    testFile << "        \n";
    testFile << "            \n";
    testFile << "                \n";
    testFile << "                \n";
    testFile << "         \n";
    testFile << "               \n";
    testFile << "ABCDEFGHIJKLMNOPQRSTUVWXYZ\n";
    testFile << R"(!@#$%^&*()[]{}<>:;"'/\?)";
    testFile << "\n";
}

TEST(AlbaFileReaderTest, ConstructorsWorks) {
    AlbaLocalPathHandler testFilePath(APRG_COMMON_TEST_FILE_TO_READ);
    ifstream inputTestFile(testFilePath.getFullPath());
    ASSERT_TRUE(inputTestFile.is_open());

    AlbaFileReader fileReader1(inputTestFile);
    EXPECT_EQ(10000U, fileReader1.getMaxBufferSize());
    AlbaFileReader fileReader2(inputTestFile, 200);
    EXPECT_EQ(200U, fileReader2.getMaxBufferSize());
}

TEST(AlbaFileReaderTest, SetAndGetBufferSizeWorks) {
    AlbaLocalPathHandler testFilePath(APRG_COMMON_TEST_FILE_TO_READ);
    ifstream inputTestFile(testFilePath.getFullPath());
    ASSERT_TRUE(inputTestFile.is_open());

    AlbaFileReader fileReader(inputTestFile);
    EXPECT_EQ(10000U, fileReader.getMaxBufferSize());
    fileReader.setMaxBufferSize(200);
    EXPECT_EQ(200U, fileReader.getMaxBufferSize());
}

TEST(AlbaFileReaderTest, SkipLineWorksUsingVariousCharacters) {
    AlbaLocalPathHandler testFilePath(APRG_COMMON_TEST_FILE_TO_READ);
    ofstream testFile(testFilePath.getFullPath());
    ASSERT_TRUE(testFile.is_open());
    writeTextWithSpaces(testFile);
    testFile.close();

    ifstream inputTestFile(testFilePath.getFullPath());
    ASSERT_TRUE(inputTestFile.is_open());

    AlbaFileReader fileReader(inputTestFile);
    ASSERT_TRUE(inputTestFile.good());
    ASSERT_FALSE(inputTestFile.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    for (int i = 0; i < 21; i++) {
        fileReader.skipLine();
        EXPECT_TRUE(fileReader.isNotFinished());
    }
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_TRUE(fileReader.getLine().empty());
    EXPECT_FALSE(fileReader.isNotFinished());
}

TEST(AlbaFileReaderTest, GetLineWorksUsingVariousCharacters) {
    AlbaLocalPathHandler testFilePath(APRG_COMMON_TEST_FILE_TO_READ);
    ofstream testFile(testFilePath.getFullPath());
    ASSERT_TRUE(testFile.is_open());
    writeTextWithSpaces(testFile);
    testFile.close();

    ifstream inputTestFile(testFilePath.getFullPath());
    ASSERT_TRUE(inputTestFile.is_open());

    AlbaFileReader fileReader(inputTestFile);
    ASSERT_TRUE(inputTestFile.good());
    ASSERT_FALSE(inputTestFile.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ("1         ", fileReader.getLine());
    EXPECT_EQ("12        ", fileReader.getLine());
    EXPECT_EQ("123       ", fileReader.getLine());
    EXPECT_EQ("1234      ", fileReader.getLine());
    EXPECT_EQ("12345     ", fileReader.getLine());
    EXPECT_EQ("123456    ", fileReader.getLine());
    EXPECT_EQ("1234567   ", fileReader.getLine());
    EXPECT_EQ("12345678  ", fileReader.getLine());
    EXPECT_EQ("123456789 ", fileReader.getLine());
    EXPECT_EQ("1234567890", fileReader.getLine());
    EXPECT_EQ("abcdefghijklmnopqrstuvwxyz                ", fileReader.getLine());
    EXPECT_EQ("", fileReader.getLine());
    EXPECT_EQ("    ", fileReader.getLine());
    EXPECT_EQ("        ", fileReader.getLine());
    EXPECT_EQ("            ", fileReader.getLine());
    EXPECT_EQ("                ", fileReader.getLine());
    EXPECT_EQ("                ", fileReader.getLine());
    EXPECT_EQ("         ", fileReader.getLine());
    EXPECT_EQ("               ", fileReader.getLine());
    EXPECT_EQ("ABCDEFGHIJKLMNOPQRSTUVWXYZ", fileReader.getLine());
    EXPECT_EQ(R"(!@#$%^&*()[]{}<>:;"'/\?)", fileReader.getLine());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_TRUE(fileReader.getLine().empty());
    EXPECT_FALSE(fileReader.isNotFinished());
}

TEST(AlbaFileReaderTest, GetLineAndIgnoreWhiteSpacesWorksUsingVariousCharacters) {
    AlbaLocalPathHandler testFilePath(APRG_COMMON_TEST_FILE_TO_READ);
    ofstream testFile(testFilePath.getFullPath());
    ASSERT_TRUE(testFile.is_open());
    writeTextWithSpaces(testFile);
    testFile.close();

    ifstream inputTestFile(testFilePath.getFullPath());
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
    EXPECT_TRUE(fileReader.getLineAndIgnoreWhiteSpaces().empty());
    EXPECT_FALSE(fileReader.isNotFinished());
}

TEST(AlbaFileReaderTest, ReadLineWithSizeLimit) {
    AlbaLocalPathHandler commonSizeTestFileToRead(ALBA_COMMON_SIZE_TEST_FILE);
    ifstream inputTestFile(commonSizeTestFileToRead.getFullPath());
    ASSERT_TRUE(inputTestFile.is_open());

    AlbaFileReader fileReader(inputTestFile);
    fileReader.setMaxBufferSize(2000);
    EXPECT_EQ(5000U, fileReader.getFileSize());
    ASSERT_TRUE(inputTestFile.good());
    ASSERT_FALSE(inputTestFile.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(2000U, fileReader.getLineAndIgnoreWhiteSpaces().length());
    EXPECT_EQ(2000U, fileReader.getLineAndIgnoreWhiteSpaces().length());
    EXPECT_EQ(1000U, fileReader.getLineAndIgnoreWhiteSpaces().length());
    EXPECT_FALSE(fileReader.isNotFinished());
    EXPECT_TRUE(fileReader.getLineAndIgnoreWhiteSpaces().empty());
}

TEST(AlbaFileReaderTest, ReadSingleCharacterFromBinaryFile) {
    AlbaLocalPathHandler testFilePath(APRG_COMMON_TEST_FILE_TO_READ);
    ofstream testFile(testFilePath.getFullPath());
    ASSERT_TRUE(testFile.is_open());
    testFile << "123!@# \t\n";
    testFile.close();

    ifstream inputTestFile(testFilePath.getFullPath(), ios::binary);
    ASSERT_TRUE(inputTestFile.is_open());

    AlbaFileReader fileReader(inputTestFile);
    ASSERT_TRUE(inputTestFile.good());
    ASSERT_FALSE(inputTestFile.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ('1', fileReader.getCharacter());
    EXPECT_EQ('2', fileReader.getCharacter());
    EXPECT_EQ('3', fileReader.getCharacter());
    EXPECT_EQ('!', fileReader.getCharacter());
    EXPECT_EQ('@', fileReader.getCharacter());
    EXPECT_EQ('#', fileReader.getCharacter());
    EXPECT_EQ(' ', fileReader.getCharacter());
    EXPECT_EQ('\t', fileReader.getCharacter());
#ifdef OS_WINDOWS
    EXPECT_EQ('\r', fileReader.getCharacter());
    EXPECT_EQ('\n', fileReader.getCharacter());
#endif
#ifdef OS_LINUX
    EXPECT_EQ('\n', fileReader.getCharacter());
#endif
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(fileReader.getCharacter(), 0);
    EXPECT_FALSE(fileReader.isNotFinished());
}

TEST(AlbaFileReaderTest, ReadMultipleCharacters) {
    AlbaLocalPathHandler testFilePath(APRG_COMMON_TEST_FILE_TO_READ);
    ofstream testFile(testFilePath.getFullPath());
    ASSERT_TRUE(testFile.is_open());
    testFile << "123!@# \t\n";
    testFile.close();

    ifstream inputTestFile(testFilePath.getFullPath(), ios::binary);
    ASSERT_TRUE(inputTestFile.is_open());

    AlbaFileReader fileReader(inputTestFile);
    ASSERT_TRUE(inputTestFile.good());
    ASSERT_FALSE(inputTestFile.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    size_t numberOfCharacters = 3U;
    char* charPointer;
    charPointer = fileReader.getCharacters(numberOfCharacters);
    EXPECT_EQ("123", string(charPointer, numberOfCharacters));
    EXPECT_EQ(3U, numberOfCharacters);
    charPointer = fileReader.getCharacters(numberOfCharacters);
    EXPECT_EQ("!@#", string(charPointer, numberOfCharacters));
    EXPECT_EQ(3U, numberOfCharacters);

#ifdef OS_WINDOWS
    charPointer = fileReader.getCharacters(numberOfCharacters);
    EXPECT_EQ(" \t\r", string(charPointer, numberOfCharacters));
    EXPECT_EQ(3U, numberOfCharacters);
    EXPECT_TRUE(fileReader.isNotFinished());
    charPointer = fileReader.getCharacters(numberOfCharacters);
    EXPECT_EQ("\n", string(charPointer, numberOfCharacters));
    EXPECT_EQ(1U, numberOfCharacters);
#endif
#ifdef OS_LINUX
    charPointer = fileReader.getCharacters(numberOfCharacters);
    EXPECT_EQ(" \t\n", string(charPointer, numberOfCharacters));
    EXPECT_EQ(3U, numberOfCharacters);
    EXPECT_TRUE(fileReader.isNotFinished());
    charPointer = fileReader.getCharacters(numberOfCharacters);
    EXPECT_TRUE(string(charPointer, numberOfCharacters).empty());
    EXPECT_EQ(0U, numberOfCharacters);
#endif
    EXPECT_FALSE(fileReader.isNotFinished());
}

TEST(AlbaFileReaderTest, RequestToReadMultipleCharactersThatIsTheBeyondBufferSize) {
    AlbaLocalPathHandler testFilePath(APRG_COMMON_TEST_FILE_TO_READ);
    ofstream testFile(testFilePath.getFullPath());
    ASSERT_TRUE(testFile.is_open());
    testFile << "12345";
    testFile.close();

    ifstream inputTestFile(testFilePath.getFullPath(), ios::binary);
    ASSERT_TRUE(inputTestFile.is_open());

    AlbaFileReader fileReader(inputTestFile);
    fileReader.setMaxBufferSize(3);
    ASSERT_TRUE(inputTestFile.good());
    ASSERT_FALSE(inputTestFile.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    size_t numberOfCharacters = 20000;
    char* charPointer;
    charPointer = fileReader.getCharacters(numberOfCharacters);
    EXPECT_EQ("123", string(charPointer, numberOfCharacters));
    EXPECT_EQ(3U, numberOfCharacters);
    EXPECT_TRUE(fileReader.isNotFinished());
    numberOfCharacters = 20000;
    charPointer = fileReader.getCharacters(numberOfCharacters);
    EXPECT_EQ("45", string(charPointer, numberOfCharacters));
    EXPECT_EQ(2U, numberOfCharacters);
    EXPECT_FALSE(fileReader.isNotFinished());
}

TEST(AlbaFileReaderTest, ReadOneByteNumbers) {
    AlbaLocalPathHandler testFilePath(APRG_COMMON_TEST_FILE_TO_READ);
    ofstream testFile(testFilePath.getFullPath());
    ASSERT_TRUE(testFile.is_open());
    testFile.put(0x01);
    testFile.put(0x23);
    testFile.put(0x45);
    testFile.put(0x67);
    testFile.put(static_cast<char>(0xA1));
    testFile.put(static_cast<char>(0xBA));
    testFile.close();

    ifstream inputTestFile(testFilePath.getFullPath(), ios::binary);
    ASSERT_TRUE(inputTestFile.is_open());

    AlbaFileReader fileReader(inputTestFile);
    ASSERT_TRUE(inputTestFile.good());
    ASSERT_FALSE(inputTestFile.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(0x01U, fileReader.getOneByteData<uint8_t>());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(0x23U, fileReader.getOneByteData<uint8_t>());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(0x45U, fileReader.getOneByteData<uint8_t>());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(0x67U, fileReader.getOneByteData<uint8_t>());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(0xA1U, fileReader.getOneByteData<uint8_t>());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(0xBAU, fileReader.getOneByteData<uint8_t>());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(0x0U, fileReader.getOneByteData<uint8_t>());
    EXPECT_FALSE(fileReader.isNotFinished());
}

TEST(AlbaFileReaderTest, ReadTwoByteNumbers) {
    AlbaLocalPathHandler testFilePath(APRG_COMMON_TEST_FILE_TO_READ);
    ofstream testFile(testFilePath.getFullPath());
    ASSERT_TRUE(testFile.is_open());
    testFile.put(0x01);
    testFile.put(0x23);
    testFile.put(0x45);
    testFile.put(0x67);
    testFile.put(static_cast<char>(0xA1));
    testFile.put(static_cast<char>(0xBA));
    testFile.close();

    ifstream inputTestFile(testFilePath.getFullPath(), ios::binary);
    ASSERT_TRUE(inputTestFile.is_open());

    AlbaFileReader fileReader(inputTestFile);
    ASSERT_TRUE(inputTestFile.good());
    ASSERT_FALSE(inputTestFile.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(0x0123U, fileReader.getTwoByteData<uint16_t>());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(0x4567U, fileReader.getTwoByteData<uint16_t>());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(0xA1BAU, fileReader.getTwoByteData<uint16_t>());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(0x0U, fileReader.getTwoByteData<uint16_t>());
    EXPECT_FALSE(fileReader.isNotFinished());
}

TEST(AlbaFileReaderTest, ReadFourByteNumbers) {
    AlbaLocalPathHandler testFilePath(APRG_COMMON_TEST_FILE_TO_READ);
    ofstream testFile(testFilePath.getFullPath());
    ASSERT_TRUE(testFile.is_open());
    testFile.put(0x01);
    testFile.put(0x23);
    testFile.put(0x45);
    testFile.put(0x67);
    testFile.put(static_cast<char>(0xA1));
    testFile.put(static_cast<char>(0xBA));
    testFile.close();

    ifstream inputTestFile(testFilePath.getFullPath(), ios::binary);
    ASSERT_TRUE(inputTestFile.is_open());

    AlbaFileReader fileReader(inputTestFile);
    ASSERT_TRUE(inputTestFile.good());
    ASSERT_FALSE(inputTestFile.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(0x01234567U, fileReader.getFourByteData<uint32_t>());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(0xA1BAU, fileReader.getFourByteData<uint32_t>());
    EXPECT_FALSE(fileReader.isNotFinished());
}

TEST(AlbaFileReaderTest, ReadEightByteNumbers) {
    AlbaLocalPathHandler testFilePath(APRG_COMMON_TEST_FILE_TO_READ);
    ofstream testFile(testFilePath.getFullPath());
    ASSERT_TRUE(testFile.is_open());
    testFile.put(0x01);
    testFile.put(0x23);
    testFile.put(0x45);
    testFile.put(0x67);
    testFile.put(static_cast<char>(0xA1));
    testFile.put(static_cast<char>(0xBA));
    testFile.close();

    ifstream inputTestFile(testFilePath.getFullPath(), ios::binary);
    ASSERT_TRUE(inputTestFile.is_open());

    AlbaFileReader fileReader(inputTestFile);
    ASSERT_TRUE(inputTestFile.good());
    ASSERT_FALSE(inputTestFile.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(0x000001234567A1BAU, fileReader.getEightByteData<uint64_t>());
    EXPECT_FALSE(fileReader.isNotFinished());
}

TEST(AlbaFileReaderTest, ReadSwappedTwoByteNumbers) {
    AlbaLocalPathHandler testFilePath(APRG_COMMON_TEST_FILE_TO_READ);
    ofstream testFile(testFilePath.getFullPath());
    ASSERT_TRUE(testFile.is_open());
    testFile.put(0x01);
    testFile.put(0x23);
    testFile.put(0x45);
    testFile.put(0x67);
    testFile.put(static_cast<char>(0xA1));
    testFile.put(static_cast<char>(0xBA));
    testFile.close();

    ifstream inputTestFile(testFilePath.getFullPath(), ios::binary);
    ASSERT_TRUE(inputTestFile.is_open());

    AlbaFileReader fileReader(inputTestFile);
    ASSERT_TRUE(inputTestFile.good());
    ASSERT_FALSE(inputTestFile.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(0x2301U, fileReader.getTwoByteSwappedData<uint16_t>());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(0x6745U, fileReader.getTwoByteSwappedData<uint16_t>());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(0xBAA1U, fileReader.getTwoByteSwappedData<uint16_t>());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(0x0U, fileReader.getTwoByteSwappedData<uint16_t>());
    EXPECT_FALSE(fileReader.isNotFinished());
}

TEST(AlbaFileReaderTest, ReadSwappedFourByteNumbers) {
    AlbaLocalPathHandler testFilePath(APRG_COMMON_TEST_FILE_TO_READ);
    ofstream testFile(testFilePath.getFullPath());
    ASSERT_TRUE(testFile.is_open());
    testFile.put(0x01);
    testFile.put(0x23);
    testFile.put(0x45);
    testFile.put(0x67);
    testFile.put(static_cast<char>(0xA1));
    testFile.put(static_cast<char>(0xBA));
    testFile.close();

    ifstream inputTestFile(testFilePath.getFullPath(), ios::binary);
    ASSERT_TRUE(inputTestFile.is_open());

    AlbaFileReader fileReader(inputTestFile);
    ASSERT_TRUE(inputTestFile.good());
    ASSERT_FALSE(inputTestFile.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(0x67452301U, fileReader.getFourByteSwappedData<uint32_t>());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(0xBAA10000U, fileReader.getFourByteSwappedData<uint32_t>());
    EXPECT_FALSE(fileReader.isNotFinished());
}

TEST(AlbaFileReaderTest, ReadSwappedEightByteNumbers) {
    AlbaLocalPathHandler testFilePath(APRG_COMMON_TEST_FILE_TO_READ);
    ofstream testFile(testFilePath.getFullPath());
    ASSERT_TRUE(testFile.is_open());
    testFile.put(0x01);
    testFile.put(0x23);
    testFile.put(0x45);
    testFile.put(0x67);
    testFile.put(static_cast<char>(0xA1));
    testFile.put(static_cast<char>(0xBA));
    testFile.close();

    ifstream inputTestFile(testFilePath.getFullPath(), ios::binary);
    ASSERT_TRUE(inputTestFile.is_open());

    AlbaFileReader fileReader(inputTestFile);
    ASSERT_TRUE(inputTestFile.good());
    ASSERT_FALSE(inputTestFile.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(0xBAA1674523010000U, fileReader.getEightByteSwappedData<uint64_t>());
    EXPECT_FALSE(fileReader.isNotFinished());
}

TEST(AlbaFileReaderTest, FileContentsCanBeSavedInMemoryBuffer) {
    AlbaLocalPathHandler testFilePath(APRG_COMMON_TEST_FILE_TO_READ);
    ofstream testFile(testFilePath.getFullPath());
    ASSERT_TRUE(testFile.is_open());
    testFile.put(0x01);
    testFile.put(0x23);
    testFile.put(0x45);
    testFile.put(0x67);
    testFile.put(static_cast<char>(0xA1));
    testFile.put(static_cast<char>(0xBA));
    testFile.close();

    ifstream inputTestFile(testFilePath.getFullPath(), ios::binary);
    ASSERT_TRUE(inputTestFile.is_open());

    AlbaFileReader fileReader(inputTestFile);
    ASSERT_TRUE(inputTestFile.good());
    ASSERT_FALSE(inputTestFile.eof());
    EXPECT_TRUE(fileReader.isNotFinished());

    AlbaMemoryBuffer buffer;
    fileReader.saveDataToMemoryBuffer(buffer, 8);
    uint8_t* reader = reinterpret_cast<uint8_t*>(buffer.getBufferPointer());
    EXPECT_EQ(0x01U, reader[0]);
    EXPECT_EQ(0x23U, reader[1]);
    EXPECT_EQ(0x45U, reader[2]);
    EXPECT_EQ(0x67U, reader[3]);
    EXPECT_EQ(0xA1U, reader[4]);
    EXPECT_EQ(0xBAU, reader[5]);
    EXPECT_FALSE(fileReader.isNotFinished());
}

}  // namespace alba
