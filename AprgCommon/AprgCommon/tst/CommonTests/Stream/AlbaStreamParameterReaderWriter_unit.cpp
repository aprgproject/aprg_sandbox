#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/Stream/AlbaStreamParameterReader.hpp>
#include <Common/Stream/AlbaStreamParameterWriter.hpp>
#include <CommonTests/DirectoryConstants.hpp>

#include <gtest/gtest.h>

#include <fstream>
#include <string>

using namespace std;

namespace alba
{

TEST(ReaderWriterParameterTest, EmptyFileTest)
{
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

TEST(ReaderWriterParameterTest, SingleParameterTest)
{
    AlbaLocalPathHandler testFilePath(APRG_COMMON_TEST_FILE_TO_WRITE);
    ofstream writeTestFile(testFilePath.getFullPath());
    ASSERT_TRUE(writeTestFile.is_open());

    AlbaStreamParameterWriter writer(writeTestFile);
    writer.writeData(12345U);
    writer.writeData(-12345);
    writer.writeData(1.2345);
    writer.writeData<string>("12345");

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

TEST(ReaderWriterParameterTest, VectorTest)
{
    AlbaLocalPathHandler testFilePath(APRG_COMMON_TEST_FILE_TO_WRITE);
    ofstream writeTestFile(testFilePath.getFullPath());
    ASSERT_TRUE(writeTestFile.is_open());

    vector<unsigned int> vectorToSave{1,2,3,4,5};
    AlbaStreamParameterWriter writer(writeTestFile);
    writer.writeVectorData(vectorToSave);

    ifstream readTestFile(testFilePath.getFullPath());
    ASSERT_TRUE(readTestFile.is_open());

    vector<unsigned int> retrievedVector;
    AlbaStreamParameterReader reader(readTestFile);
    ASSERT_TRUE(readTestFile.good());
    ASSERT_FALSE(readTestFile.eof());
    reader.readVectorData(retrievedVector);
    ASSERT_EQ(5U, retrievedVector.size());
    EXPECT_EQ(1U, retrievedVector.at(0));
    EXPECT_EQ(2U, retrievedVector.at(1));
    EXPECT_EQ(3U, retrievedVector.at(2));
    EXPECT_EQ(4U, retrievedVector.at(3));
    EXPECT_EQ(5U, retrievedVector.at(4));
}

TEST(ReaderWriterParameterTest, MapTest)
{
    AlbaLocalPathHandler testFilePath(APRG_COMMON_TEST_FILE_TO_WRITE);
    ofstream writeTestFile(testFilePath.getFullPath());
    ASSERT_TRUE(writeTestFile.is_open());

    map<unsigned int, string> mapToSave{{1, "one"}, {2, "two"}, {3, "three"}};
    AlbaStreamParameterWriter writer(writeTestFile);
    writer.writeMapData(mapToSave);

    ifstream readTestFile(testFilePath.getFullPath());
    ASSERT_TRUE(readTestFile.is_open());

    map<unsigned int, string> retrievedmap;
    AlbaStreamParameterReader reader(readTestFile);
    ASSERT_TRUE(readTestFile.good());
    ASSERT_FALSE(readTestFile.eof());
    reader.readMapData(retrievedmap);
    ASSERT_EQ(3U, retrievedmap.size());
    EXPECT_EQ("one", retrievedmap.at(1));
    EXPECT_EQ("two", retrievedmap.at(2));
    EXPECT_EQ("three", retrievedmap.at(3));
}

}
