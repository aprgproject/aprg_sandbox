#include <Common/File/AlbaFileReader.hpp>
#include <CommonTestsUtilities/DirectoryConstants.hpp>
#include <CommonTestsUtilities/File/BaseFileReaderTest.hpp>

#include <gtest/gtest.h>
#include <string>

using namespace std;

namespace alba {

struct AlbaFileReaderTest : public BaseFileReaderTest {
    AlbaFileReaderTest() : BaseFileReaderTest(APRG_COMMON_TEST_FILE_TO_READ) {}
};

void writeTextWithSpaces(ofstream& writeStream) {
    writeStream << "1         \n";
    writeStream << "12        \n";
    writeStream << "123       \n";
    writeStream << "1234      \n";
    writeStream << "12345     \n";
    writeStream << "123456    \n";
    writeStream << "1234567   \n";
    writeStream << "12345678  \n";
    writeStream << "123456789 \n";
    writeStream << "1234567890\n";
    writeStream << "abcdefghijklmnopqrstuvwxyz                \n";
    writeStream << "\n";
    writeStream << "    \n";
    writeStream << "        \n";
    writeStream << "            \n";
    writeStream << "                \n";
    writeStream << "                \n";
    writeStream << "         \n";
    writeStream << "               \n";
    writeStream << "ABCDEFGHIJKLMNOPQRSTUVWXYZ\n";
    writeStream << R"(!@#$%^&*()[]{}<>:;"'/\?)";
    writeStream << "\n";
}

TEST_F(AlbaFileReaderTest, ConstructorsWorks) {
    ifstream testFileReadStream(testFilePathHandler.getFullPath());
    ASSERT_TRUE(testFileReadStream.is_open());

    AlbaFileReader fileReader1(testFileReadStream);
    EXPECT_EQ(10000U, fileReader1.getMaxBufferSize());
    AlbaFileReader fileReader2(testFileReadStream, 200);
    EXPECT_EQ(200U, fileReader2.getMaxBufferSize());
}

TEST_F(AlbaFileReaderTest, SetAndGetBufferSizeWorks) {
    ifstream testFileReadStream(testFilePathHandler.getFullPath());
    ASSERT_TRUE(testFileReadStream.is_open());

    AlbaFileReader fileReader(testFileReadStream);
    EXPECT_EQ(10000U, fileReader.getMaxBufferSize());
    fileReader.setMaxBufferSize(200);
    EXPECT_EQ(200U, fileReader.getMaxBufferSize());
}

TEST_F(AlbaFileReaderTest, SkipLineWorksUsingVariousCharacters) {
    writeTextWithSpaces(testFileWriteStream);
    testFileWriteStream.close();

    ifstream testFileReadStream(testFilePathHandler.getFullPath());
    ASSERT_TRUE(testFileReadStream.is_open());

    AlbaFileReader fileReader(testFileReadStream);
    ASSERT_TRUE(testFileReadStream.good());
    ASSERT_FALSE(testFileReadStream.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    for (int i = 0; i < 21; i++) {
        fileReader.skipLine();        EXPECT_TRUE(fileReader.isNotFinished());
    }
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_TRUE(fileReader.getLine().empty());
    EXPECT_FALSE(fileReader.isNotFinished());
}

TEST_F(AlbaFileReaderTest, GetLineWorksUsingVariousCharacters) {
    writeTextWithSpaces(testFileWriteStream);
    testFileWriteStream.close();

    ifstream testFileReadStream(testFilePathHandler.getFullPath());
    ASSERT_TRUE(testFileReadStream.is_open());

    AlbaFileReader fileReader(testFileReadStream);
    ASSERT_TRUE(testFileReadStream.good());
    ASSERT_FALSE(testFileReadStream.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ("1         ", fileReader.getLine());
    EXPECT_EQ("12        ", fileReader.getLine());    EXPECT_EQ("123       ", fileReader.getLine());
    EXPECT_EQ("1234      ", fileReader.getLine());
    EXPECT_EQ("12345     ", fileReader.getLine());
    EXPECT_EQ("123456    ", fileReader.getLine());    EXPECT_EQ("1234567   ", fileReader.getLine());
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

TEST_F(AlbaFileReaderTest, GetLineAndIgnoreWhiteSpacesWorksUsingVariousCharacters) {
    writeTextWithSpaces(testFileWriteStream);
    testFileWriteStream.close();

    ifstream testFileReadStream(testFilePathHandler.getFullPath());
    ASSERT_TRUE(testFileReadStream.is_open());

    AlbaFileReader fileReader(testFileReadStream);
    ASSERT_TRUE(testFileReadStream.good());
    ASSERT_FALSE(testFileReadStream.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ("1", fileReader.getLineAndIgnoreWhiteSpaces());
    EXPECT_EQ("12", fileReader.getLineAndIgnoreWhiteSpaces());    EXPECT_EQ("123", fileReader.getLineAndIgnoreWhiteSpaces());
    EXPECT_EQ("1234", fileReader.getLineAndIgnoreWhiteSpaces());
    EXPECT_EQ("12345", fileReader.getLineAndIgnoreWhiteSpaces());
    EXPECT_EQ("123456", fileReader.getLineAndIgnoreWhiteSpaces());    EXPECT_EQ("1234567", fileReader.getLineAndIgnoreWhiteSpaces());
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

TEST_F(AlbaFileReaderTest, ReadLineWithSizeLimit) {
    AlbaLocalPathHandler commonSizeTestFileToRead(ALBA_COMMON_SIZE_TEST_FILE);
    ifstream testFileReadStream(commonSizeTestFileToRead.getFullPath());
    ASSERT_TRUE(testFileReadStream.is_open());

    AlbaFileReader fileReader(testFileReadStream);
    fileReader.setMaxBufferSize(2000);
    EXPECT_EQ(5000U, fileReader.getFileSize());
    ASSERT_TRUE(testFileReadStream.good());
    ASSERT_FALSE(testFileReadStream.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(2000U, fileReader.getLineAndIgnoreWhiteSpaces().length());
    EXPECT_EQ(2000U, fileReader.getLineAndIgnoreWhiteSpaces().length());    EXPECT_EQ(1000U, fileReader.getLineAndIgnoreWhiteSpaces().length());
    EXPECT_FALSE(fileReader.isNotFinished());
    EXPECT_TRUE(fileReader.getLineAndIgnoreWhiteSpaces().empty());
}

TEST_F(AlbaFileReaderTest, ReadSingleCharacterFromBinaryFile) {
    testFileWriteStream << "123!@# \t\n";
    testFileWriteStream.close();

    ifstream testFileReadStream(testFilePathHandler.getFullPath(), ios::binary);
    ASSERT_TRUE(testFileReadStream.is_open());

    AlbaFileReader fileReader(testFileReadStream);
    ASSERT_TRUE(testFileReadStream.good());
    ASSERT_FALSE(testFileReadStream.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ('1', fileReader.getCharacter());
    EXPECT_EQ('2', fileReader.getCharacter());    EXPECT_EQ('3', fileReader.getCharacter());
    EXPECT_EQ('!', fileReader.getCharacter());
    EXPECT_EQ('@', fileReader.getCharacter());
    EXPECT_EQ('#', fileReader.getCharacter());    EXPECT_EQ(' ', fileReader.getCharacter());
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

TEST_F(AlbaFileReaderTest, ReadMultipleCharacters) {
    testFileWriteStream << "123!@# \t\n";
    testFileWriteStream.close();

    ifstream testFileReadStream(testFilePathHandler.getFullPath(), ios::binary);
    ASSERT_TRUE(testFileReadStream.is_open());

    AlbaFileReader fileReader(testFileReadStream);
    ASSERT_TRUE(testFileReadStream.good());
    ASSERT_FALSE(testFileReadStream.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    size_t numberOfCharacters = 3U;
    char* charPointer;    charPointer = fileReader.getCharacters(numberOfCharacters);
    EXPECT_EQ("123", string(charPointer, numberOfCharacters));
    EXPECT_EQ(3U, numberOfCharacters);
    charPointer = fileReader.getCharacters(numberOfCharacters);    EXPECT_EQ("!@#", string(charPointer, numberOfCharacters));
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

TEST_F(AlbaFileReaderTest, RequestToReadMultipleCharactersThatIsTheBeyondBufferSize) {
    testFileWriteStream << "12345";
    testFileWriteStream.close();

    ifstream testFileReadStream(testFilePathHandler.getFullPath(), ios::binary);
    ASSERT_TRUE(testFileReadStream.is_open());

    AlbaFileReader fileReader(testFileReadStream);
    fileReader.setMaxBufferSize(3);
    ASSERT_TRUE(testFileReadStream.good());
    ASSERT_FALSE(testFileReadStream.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    size_t numberOfCharacters = 20000;
    char* charPointer;    charPointer = fileReader.getCharacters(numberOfCharacters);
    EXPECT_EQ("123", string(charPointer, numberOfCharacters));
    EXPECT_EQ(3U, numberOfCharacters);
    EXPECT_TRUE(fileReader.isNotFinished());    numberOfCharacters = 20000;
    charPointer = fileReader.getCharacters(numberOfCharacters);
    EXPECT_EQ("45", string(charPointer, numberOfCharacters));
    EXPECT_EQ(2U, numberOfCharacters);
    EXPECT_FALSE(fileReader.isNotFinished());
}

TEST_F(AlbaFileReaderTest, ReadOneByteNumbers) {
    testFileWriteStream.put(0x01);
    testFileWriteStream.put(0x23);
    testFileWriteStream.put(0x45);
    testFileWriteStream.put(0x67);
    testFileWriteStream.put(static_cast<char>(0xA1));
    testFileWriteStream.put(static_cast<char>(0xBA));
    testFileWriteStream.close();

    ifstream testFileReadStream(testFilePathHandler.getFullPath(), ios::binary);
    ASSERT_TRUE(testFileReadStream.is_open());

    AlbaFileReader fileReader(testFileReadStream);
    ASSERT_TRUE(testFileReadStream.good());
    ASSERT_FALSE(testFileReadStream.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(0x01U, fileReader.getOneByteData<uint8_t>());
    EXPECT_TRUE(fileReader.isNotFinished());    EXPECT_EQ(0x23U, fileReader.getOneByteData<uint8_t>());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(0x45U, fileReader.getOneByteData<uint8_t>());
    EXPECT_TRUE(fileReader.isNotFinished());    EXPECT_EQ(0x67U, fileReader.getOneByteData<uint8_t>());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(0xA1U, fileReader.getOneByteData<uint8_t>());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(0xBAU, fileReader.getOneByteData<uint8_t>());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(0x0U, fileReader.getOneByteData<uint8_t>());
    EXPECT_FALSE(fileReader.isNotFinished());
}

TEST_F(AlbaFileReaderTest, ReadTwoByteNumbers) {
    testFileWriteStream.put(0x01);
    testFileWriteStream.put(0x23);
    testFileWriteStream.put(0x45);
    testFileWriteStream.put(0x67);
    testFileWriteStream.put(static_cast<char>(0xA1));
    testFileWriteStream.put(static_cast<char>(0xBA));
    testFileWriteStream.close();

    ifstream testFileReadStream(testFilePathHandler.getFullPath(), ios::binary);
    ASSERT_TRUE(testFileReadStream.is_open());

    AlbaFileReader fileReader(testFileReadStream);
    ASSERT_TRUE(testFileReadStream.good());
    ASSERT_FALSE(testFileReadStream.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(0x0123U, fileReader.getTwoByteData<uint16_t>());
    EXPECT_TRUE(fileReader.isNotFinished());    EXPECT_EQ(0x4567U, fileReader.getTwoByteData<uint16_t>());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(0xA1BAU, fileReader.getTwoByteData<uint16_t>());
    EXPECT_TRUE(fileReader.isNotFinished());    EXPECT_EQ(0x0U, fileReader.getTwoByteData<uint16_t>());
    EXPECT_FALSE(fileReader.isNotFinished());
}

TEST_F(AlbaFileReaderTest, ReadFourByteNumbers) {
    testFileWriteStream.put(0x01);
    testFileWriteStream.put(0x23);
    testFileWriteStream.put(0x45);
    testFileWriteStream.put(0x67);
    testFileWriteStream.put(static_cast<char>(0xA1));
    testFileWriteStream.put(static_cast<char>(0xBA));
    testFileWriteStream.close();

    ifstream testFileReadStream(testFilePathHandler.getFullPath(), ios::binary);
    ASSERT_TRUE(testFileReadStream.is_open());

    AlbaFileReader fileReader(testFileReadStream);
    ASSERT_TRUE(testFileReadStream.good());
    ASSERT_FALSE(testFileReadStream.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(0x01234567U, fileReader.getFourByteData<uint32_t>());
    EXPECT_TRUE(fileReader.isNotFinished());    EXPECT_EQ(0xA1BAU, fileReader.getFourByteData<uint32_t>());
    EXPECT_FALSE(fileReader.isNotFinished());
}

TEST_F(AlbaFileReaderTest, ReadEightByteNumbers) {
    testFileWriteStream.put(0x01);
    testFileWriteStream.put(0x23);
    testFileWriteStream.put(0x45);
    testFileWriteStream.put(0x67);
    testFileWriteStream.put(static_cast<char>(0xA1));
    testFileWriteStream.put(static_cast<char>(0xBA));
    testFileWriteStream.close();

    ifstream testFileReadStream(testFilePathHandler.getFullPath(), ios::binary);
    ASSERT_TRUE(testFileReadStream.is_open());

    AlbaFileReader fileReader(testFileReadStream);
    ASSERT_TRUE(testFileReadStream.good());
    ASSERT_FALSE(testFileReadStream.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(0x000001234567A1BAU, fileReader.getEightByteData<uint64_t>());
    EXPECT_FALSE(fileReader.isNotFinished());
}

TEST_F(AlbaFileReaderTest, ReadSwappedTwoByteNumbers) {
    testFileWriteStream.put(0x01);
    testFileWriteStream.put(0x23);
    testFileWriteStream.put(0x45);
    testFileWriteStream.put(0x67);
    testFileWriteStream.put(static_cast<char>(0xA1));
    testFileWriteStream.put(static_cast<char>(0xBA));
    testFileWriteStream.close();

    ifstream testFileReadStream(testFilePathHandler.getFullPath(), ios::binary);
    ASSERT_TRUE(testFileReadStream.is_open());

    AlbaFileReader fileReader(testFileReadStream);
    ASSERT_TRUE(testFileReadStream.good());
    ASSERT_FALSE(testFileReadStream.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(0x2301U, fileReader.getTwoByteSwappedData<uint16_t>());
    EXPECT_TRUE(fileReader.isNotFinished());    EXPECT_EQ(0x6745U, fileReader.getTwoByteSwappedData<uint16_t>());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(0xBAA1U, fileReader.getTwoByteSwappedData<uint16_t>());
    EXPECT_TRUE(fileReader.isNotFinished());    EXPECT_EQ(0x0U, fileReader.getTwoByteSwappedData<uint16_t>());
    EXPECT_FALSE(fileReader.isNotFinished());
}

TEST_F(AlbaFileReaderTest, ReadSwappedFourByteNumbers) {
    testFileWriteStream.put(0x01);
    testFileWriteStream.put(0x23);
    testFileWriteStream.put(0x45);
    testFileWriteStream.put(0x67);
    testFileWriteStream.put(static_cast<char>(0xA1));
    testFileWriteStream.put(static_cast<char>(0xBA));
    testFileWriteStream.close();

    ifstream testFileReadStream(testFilePathHandler.getFullPath(), ios::binary);
    ASSERT_TRUE(testFileReadStream.is_open());

    AlbaFileReader fileReader(testFileReadStream);
    ASSERT_TRUE(testFileReadStream.good());
    ASSERT_FALSE(testFileReadStream.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(0x67452301U, fileReader.getFourByteSwappedData<uint32_t>());
    EXPECT_TRUE(fileReader.isNotFinished());    EXPECT_EQ(0xBAA10000U, fileReader.getFourByteSwappedData<uint32_t>());
    EXPECT_FALSE(fileReader.isNotFinished());
}

TEST_F(AlbaFileReaderTest, ReadSwappedEightByteNumbers) {
    testFileWriteStream.put(0x01);
    testFileWriteStream.put(0x23);
    testFileWriteStream.put(0x45);
    testFileWriteStream.put(0x67);
    testFileWriteStream.put(static_cast<char>(0xA1));
    testFileWriteStream.put(static_cast<char>(0xBA));
    testFileWriteStream.close();

    ifstream testFileReadStream(testFilePathHandler.getFullPath(), ios::binary);
    ASSERT_TRUE(testFileReadStream.is_open());

    AlbaFileReader fileReader(testFileReadStream);
    ASSERT_TRUE(testFileReadStream.good());
    ASSERT_FALSE(testFileReadStream.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(0xBAA1674523010000U, fileReader.getEightByteSwappedData<uint64_t>());
    EXPECT_FALSE(fileReader.isNotFinished());
}

TEST_F(AlbaFileReaderTest, FileContentsCanBeSavedInMemoryBuffer) {
    testFileWriteStream.put(0x01);
    testFileWriteStream.put(0x23);
    testFileWriteStream.put(0x45);
    testFileWriteStream.put(0x67);
    testFileWriteStream.put(static_cast<char>(0xA1));
    testFileWriteStream.put(static_cast<char>(0xBA));
    testFileWriteStream.close();

    ifstream testFileReadStream(testFilePathHandler.getFullPath(), ios::binary);
    ASSERT_TRUE(testFileReadStream.is_open());

    AlbaFileReader fileReader(testFileReadStream);
    ASSERT_TRUE(testFileReadStream.good());
    ASSERT_FALSE(testFileReadStream.eof());
    EXPECT_TRUE(fileReader.isNotFinished());

    AlbaMemoryBuffer buffer;    fileReader.saveDataToMemoryBuffer(buffer, 8);
    EXPECT_EQ(8U, buffer.getSize());
    EXPECT_EQ(0x01U, buffer[0]);
    EXPECT_EQ(0x23U, buffer[1]);    EXPECT_EQ(0x45U, buffer[2]);
    EXPECT_EQ(0x67U, buffer[3]);
    EXPECT_EQ(0xA1U, buffer[4]);
    EXPECT_EQ(0xBAU, buffer[5]);
    EXPECT_FALSE(fileReader.isNotFinished());
}

}  // namespace alba
