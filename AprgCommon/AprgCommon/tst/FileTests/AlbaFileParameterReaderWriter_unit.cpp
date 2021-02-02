#include <DirectoryConstants.hpp>
#include <File/AlbaFileParameterReader.hpp>
#include <File/AlbaFileParameterWriter.hpp>

#include <gtest/gtest.h>

#include <string>

using namespace alba;
using namespace std;

TEST(ReaderWriterParameterTest, EmptyFileTest)
{
    ifstream readTestFile(APRG_COMMON_EMPTY_TEST_FILE);
    ASSERT_TRUE(readTestFile.is_open());

    AlbaFileParameterReader reader(readTestFile);
    ASSERT_TRUE(readTestFile.good());
    ASSERT_FALSE(readTestFile.eof());
    EXPECT_EQ(0u, reader.readData<unsigned int>());
    EXPECT_EQ(0, reader.readData<int>());
    EXPECT_EQ(0, reader.readData<double>());
    EXPECT_TRUE(reader.readData<string>().empty());
}

TEST(ReaderWriterParameterTest, SingleParameterTest)
{
    ofstream writeTestFile(APRG_COMMON_TEST_FILE_TO_READ_WRITE);
    ASSERT_TRUE(writeTestFile.is_open());

    AlbaFileParameterWriter writer(writeTestFile);
    writer.writeData(12345u);
    writer.writeData(-12345);
    writer.writeData(1.2345);
    writer.writeData<string>("12345");

    ifstream readTestFile(APRG_COMMON_TEST_FILE_TO_READ_WRITE);
    ASSERT_TRUE(readTestFile.is_open());

    AlbaFileParameterReader reader(readTestFile);
    ASSERT_TRUE(readTestFile.good());
    ASSERT_FALSE(readTestFile.eof());
    EXPECT_EQ(12345u, reader.readData<unsigned int>());
    EXPECT_EQ(-12345, reader.readData<int>());
    EXPECT_EQ(1.2345, reader.readData<double>());
    EXPECT_EQ("12345", reader.readData<string>());
}

TEST(ReaderWriterParameterTest, VectorTest)
{
    ofstream writeTestFile(APRG_COMMON_TEST_FILE_TO_READ_WRITE);
    ASSERT_TRUE(writeTestFile.is_open());

    vector<unsigned int> vectorToSave{1,2,3,4,5};
    AlbaFileParameterWriter writer(writeTestFile);
    writer.writeData(vectorToSave);

    ifstream readTestFile(APRG_COMMON_TEST_FILE_TO_READ_WRITE);
    ASSERT_TRUE(readTestFile.is_open());

    vector<unsigned int> retrievedVector;
    AlbaFileParameterReader reader(readTestFile);
    ASSERT_TRUE(readTestFile.good());
    ASSERT_FALSE(readTestFile.eof());
    reader.readData(retrievedVector);
    ASSERT_EQ(5u, retrievedVector.size());
    EXPECT_EQ(1u, retrievedVector.at(0));
    EXPECT_EQ(2u, retrievedVector.at(1));
    EXPECT_EQ(3u, retrievedVector.at(2));
    EXPECT_EQ(4u, retrievedVector.at(3));
    EXPECT_EQ(5u, retrievedVector.at(4));
}

TEST(ReaderWriterParameterTest, MapTest)
{
    ofstream writeTestFile(APRG_COMMON_TEST_FILE_TO_READ_WRITE);
    ASSERT_TRUE(writeTestFile.is_open());

    map<unsigned int, string> mapToSave{{1, "one"}, {2, "two"}, {3, "three"}};
    AlbaFileParameterWriter writer(writeTestFile);
    writer.writeData(mapToSave);

    ifstream readTestFile(APRG_COMMON_TEST_FILE_TO_READ_WRITE);
    ASSERT_TRUE(readTestFile.is_open());

    map<unsigned int, string> retrievedmap;
    AlbaFileParameterReader reader(readTestFile);
    ASSERT_TRUE(readTestFile.good());
    ASSERT_FALSE(readTestFile.eof());
    reader.readData(retrievedmap);
    ASSERT_EQ(3u, retrievedmap.size());
    EXPECT_EQ("one", retrievedmap.at(1));
    EXPECT_EQ("two", retrievedmap.at(2));
    EXPECT_EQ("three", retrievedmap.at(3));
}
