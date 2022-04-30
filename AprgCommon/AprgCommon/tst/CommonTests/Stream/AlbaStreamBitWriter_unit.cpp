#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/Stream/AlbaStreamBitWriter.hpp>
#include <CommonTests/DirectoryConstants.hpp>

#include <gtest/gtest.h>

#include <fstream>
#include <string>

using namespace std;

namespace alba
{

TEST(AlbaStreamBitWriterTest, WriteBoolDataWorks)
{
    AlbaLocalPathHandler testFilePath(APRG_COMMON_TEST_FILE_TO_WRITE);
    ofstream writeTestFile(testFilePath.getFullPath(), std::ofstream::binary);
    ASSERT_TRUE(writeTestFile.is_open());

    AlbaStreamBitWriter writer(writeTestFile);
    writer.writeBoolData(false);
    writer.writeBoolData(false);
    writer.writeBoolData(true);
    writer.writeBoolData(true);
    writer.writeBoolData(false);
    writer.writeBoolData(false);
    writer.writeBoolData(true);
    writer.writeBoolData(true);
    writeTestFile.close();

    ifstream readTestFile(testFilePath.getFullPath());
    ASSERT_TRUE(readTestFile.is_open());
    AlbaFileReader fileReader(readTestFile);
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(R"(3)", fileReader.getLine());
    EXPECT_TRUE(fileReader.getLine().empty());
    EXPECT_FALSE(fileReader.isNotFinished());
}

TEST(AlbaStreamBitWriterTest, WriteCharDataWorks)
{
    AlbaLocalPathHandler testFilePath(APRG_COMMON_TEST_FILE_TO_WRITE);
    ofstream writeTestFile(testFilePath.getFullPath(), std::ofstream::binary);
    ASSERT_TRUE(writeTestFile.is_open());

    AlbaStreamBitWriter writer(writeTestFile);
    writer.writeCharData('.');
    writer.writeCharData('/');
    writer.writeCharData('*');
    writeTestFile.close();

    ifstream readTestFile(testFilePath.getFullPath());
    ASSERT_TRUE(readTestFile.is_open());
    AlbaFileReader fileReader(readTestFile);
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(R"(./*)", fileReader.getLine());
    EXPECT_TRUE(fileReader.getLine().empty());
    EXPECT_FALSE(fileReader.isNotFinished());
}

TEST(AlbaStreamBitWriterTest, WriteStringDataWorks)
{
    AlbaLocalPathHandler testFilePath(APRG_COMMON_TEST_FILE_TO_WRITE);
    ofstream writeTestFile(testFilePath.getFullPath(), std::ofstream::binary);
    ASSERT_TRUE(writeTestFile.is_open());

    AlbaStreamBitWriter writer(writeTestFile);
    writer.writeStringData("A1BA");
    writeTestFile.close();

    ifstream readTestFile(testFilePath.getFullPath());
    ASSERT_TRUE(readTestFile.is_open());
    AlbaFileReader fileReader(readTestFile);
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(R"(A1BA)", fileReader.getLine());
    EXPECT_TRUE(fileReader.getLine().empty());
    EXPECT_FALSE(fileReader.isNotFinished());
}

TEST(AlbaStreamBitWriterTest, WriteNumberDataWorks)
{
    AlbaLocalPathHandler testFilePath(APRG_COMMON_TEST_FILE_TO_WRITE);
    ofstream writeTestFile(testFilePath.getFullPath(), std::ofstream::binary);
    ASSERT_TRUE(writeTestFile.is_open());

    AlbaStreamBitWriter writer(writeTestFile);
    writer.writeNumberData<unsigned int>(AlbaStreamBitEndianType::BigEndian, 0x01020304);
    writer.writeNumberData<unsigned int>(AlbaStreamBitEndianType::LittleEndian, 0x01020304);
    writeTestFile.close();

    ifstream readTestFile(testFilePath.getFullPath());
    ASSERT_TRUE(readTestFile.is_open());
    AlbaFileReader fileReader(readTestFile);
    EXPECT_EQ(0x01020304U, fileReader.getFourByteData<unsigned int>());
    EXPECT_EQ(0x04030201U, fileReader.getFourByteData<unsigned int>());
    EXPECT_TRUE(fileReader.getLine().empty());
    EXPECT_FALSE(fileReader.isNotFinished());
}

TEST(AlbaStreamBitWriterTest, FlushWorks)
{
    AlbaLocalPathHandler testFilePath(APRG_COMMON_TEST_FILE_TO_WRITE);
    ofstream writeTestFile(testFilePath.getFullPath(), std::ofstream::binary);
    ASSERT_TRUE(writeTestFile.is_open());
    AlbaStreamBitWriter writer(writeTestFile);
    writer.writeBoolData(true);

    writer.flush();
    writeTestFile.close();

    ifstream readTestFile(testFilePath.getFullPath());
    ASSERT_TRUE(readTestFile.is_open());
    AlbaFileReader fileReader(readTestFile);
    EXPECT_EQ(0x80U, fileReader.getOneByteData<unsigned char>());
    EXPECT_TRUE(fileReader.getLine().empty());
    EXPECT_FALSE(fileReader.isNotFinished());
}

}
