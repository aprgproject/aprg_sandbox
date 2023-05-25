#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/Stream/AlbaStreamParameterReader.hpp>
#include <Common/Stream/AlbaStreamParameterWriter.hpp>
#include <CommonTests/DirectoryConstants.hpp>

#include <gtest/gtest.h>

#include <fstream>
#include <string>

using namespace std;

namespace alba {

TEST(ReaderWriterParameterTest, EmptyFileTest) {
    ifstream readTestFile(AlbaLocalPathHandler(APRG_COMMON_EMPTY_TEST_FILE).getFullPath());
    ASSERT_TRUE(readTestFile.is_open());

    AlbaStreamParameterReader reader(readTestFile);
    ASSERT_TRUE(readTestFile.good());
    ASSERT_FALSE(readTestFile.eof());
    EXPECT_EQ(0U, reader.readData<unsigned int>());
    EXPECT_EQ(0, reader.readData<int>());
    EXPECT_EQ(0, reader.readData<double>());
    EXPECT_TRUE(reader.readData<string>().empty());
}

TEST(ReaderWriterParameterTest, SingleParameterTest) {
    AlbaLocalPathHandler testFilePath(APRG_COMMON_TEST_FILE_TO_WRITE);
    ofstream writeTestFile(testFilePath.getFullPath());
    ASSERT_TRUE(writeTestFile.is_open());

    AlbaStreamParameterWriter writer(writeTestFile);
    writer.writeData(12345U);
    writer.writeData(-12345);
    writer.writeData(1.2345);
    writer.writeData<string>("12345");
    writer.flush();

    ifstream readTestFile(testFilePath.getFullPath());
    ASSERT_TRUE(readTestFile.is_open());

    AlbaStreamParameterReader reader(readTestFile);
    ASSERT_TRUE(readTestFile.good());
    ASSERT_FALSE(readTestFile.eof());
    EXPECT_EQ(12345U, reader.readData<unsigned int>());
    EXPECT_EQ(-12345, reader.readData<int>());
    EXPECT_EQ(1.2345, reader.readData<double>());
    EXPECT_EQ("12345", reader.readData<string>());
}

TEST(ReaderWriterParameterTest, VectorTest) {
    AlbaLocalPathHandler testFilePath(APRG_COMMON_TEST_FILE_TO_WRITE);
    ofstream writeTestFile(testFilePath.getFullPath());
    ASSERT_TRUE(writeTestFile.is_open());

    vector<int> sampleVector{1, 2, 3, 4, 5};
    AlbaStreamParameterWriter writer(writeTestFile);
    writer.writeVectorData(sampleVector);
    writer.flush();

    ifstream readTestFile(testFilePath.getFullPath());
    ASSERT_TRUE(readTestFile.is_open());

    vector<int> retrievedVector;
    AlbaStreamParameterReader reader(readTestFile);
    ASSERT_TRUE(readTestFile.good());
    ASSERT_FALSE(readTestFile.eof());
    reader.readVectorData(retrievedVector);
    EXPECT_EQ(sampleVector, retrievedVector);
}

TEST(ReaderWriterParameterTest, MapTest) {
    AlbaLocalPathHandler testFilePath(APRG_COMMON_TEST_FILE_TO_WRITE);
    ofstream writeTestFile(testFilePath.getFullPath());
    ASSERT_TRUE(writeTestFile.is_open());

    map<int, string> sampleMap{{1, "one"}, {2, "two"}, {3, "three"}};
    AlbaStreamParameterWriter writer(writeTestFile);
    writer.writeMapData(sampleMap);
    writer.flush();

    ifstream readTestFile(testFilePath.getFullPath());
    ASSERT_TRUE(readTestFile.is_open());

    map<int, string> retrievedmap;
    AlbaStreamParameterReader reader(readTestFile);
    ASSERT_TRUE(readTestFile.good());
    ASSERT_FALSE(readTestFile.eof());
    reader.readMapData(retrievedmap);
    EXPECT_EQ(sampleMap, retrievedmap);
}

}  // namespace alba
