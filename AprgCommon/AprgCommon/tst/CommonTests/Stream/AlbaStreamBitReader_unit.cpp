#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/Stream/AlbaStreamBitReader.hpp>
#include <CommonTests/DirectoryConstants.hpp>

#include <gtest/gtest.h>

#include <fstream>
#include <string>

using namespace std;

namespace alba
{

TEST(AlbaStreamBitReaderTest, WriteBoolDataWorks)
{
    AlbaLocalPathHandler testFilePath(APRG_COMMON_TEST_FILE_TO_READ);
    ofstream writeTestFile(testFilePath.getFullPath(), std::ofstream::binary);
    writeTestFile.put('A');
    writeTestFile.close();
    ifstream readTestFile(testFilePath.getFullPath(), std::ofstream::binary);
    ASSERT_TRUE(readTestFile.is_open());

    AlbaStreamBitReader reader(readTestFile);
    EXPECT_FALSE(reader.readBoolData());
    EXPECT_TRUE(reader.readBoolData());
    EXPECT_FALSE(reader.readBoolData());
    EXPECT_FALSE(reader.readBoolData());
    EXPECT_FALSE(reader.readBoolData());
    EXPECT_FALSE(reader.readBoolData());
    EXPECT_FALSE(reader.readBoolData());
    EXPECT_TRUE(reader.readBoolData());
    EXPECT_TRUE(reader.noRemainingBitsInBuffer());
}

TEST(AlbaStreamBitReaderTest, WriteCharDataWorks)
{
    AlbaLocalPathHandler testFilePath(APRG_COMMON_TEST_FILE_TO_READ);
    ofstream writeTestFile(testFilePath.getFullPath(), std::ofstream::binary);
    writeTestFile.put('.');
    writeTestFile.put('/');
    writeTestFile.put('*');
    writeTestFile.close();
    ifstream readTestFile(testFilePath.getFullPath(), std::ofstream::binary);
    ASSERT_TRUE(readTestFile.is_open());

    AlbaStreamBitReader reader(readTestFile);
    EXPECT_EQ('.', reader.readCharData());
    EXPECT_EQ('/', reader.readCharData());
    EXPECT_EQ('*', reader.readCharData());
    EXPECT_TRUE(reader.noRemainingBitsInBuffer());
}

TEST(AlbaStreamBitReaderTest, WriteNumberDataWorks)
{
    AlbaLocalPathHandler testFilePath(APRG_COMMON_TEST_FILE_TO_READ);
    ofstream writeTestFile(testFilePath.getFullPath(), std::ofstream::binary);
    writeTestFile.put(0x01);
    writeTestFile.put(0x02);
    writeTestFile.put(0x03);
    writeTestFile.put(0x04);
    writeTestFile.put(0x01);
    writeTestFile.put(0x02);
    writeTestFile.put(0x03);
    writeTestFile.put(0x04);
    writeTestFile.close();
    ifstream readTestFile(testFilePath.getFullPath(), std::ofstream::binary);
    ASSERT_TRUE(readTestFile.is_open());

    AlbaStreamBitReader reader(readTestFile);
    EXPECT_EQ(0x01020304U, reader.readNumberData<unsigned int>(AlbaStreamBitEndianType::BigEndian));
    EXPECT_EQ(0x04030201U, reader.readNumberData<unsigned int>(AlbaStreamBitEndianType::LittleEndian));
    EXPECT_TRUE(reader.noRemainingBitsInBuffer());
}

}
