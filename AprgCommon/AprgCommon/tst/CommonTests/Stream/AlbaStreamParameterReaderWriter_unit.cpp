#include <Common/Stream/AlbaStreamParameterReader.hpp>
#include <Common/Stream/AlbaStreamParameterWriter.hpp>
#include <CommonTestsUtilities/DirectoryConstants.hpp>
#include <CommonTestsUtilities/File/BaseFileReaderTest.hpp>

#include <gtest/gtest.h>

#include <fstream>
#include <string>

using namespace std;

namespace alba {

struct AlbaStreamParameterReaderTest : public BaseFileReaderTest {
    AlbaStreamParameterReaderTest() : BaseFileReaderTest(APRG_COMMON_TEST_FILE_TO_WRITE) {}
};

TEST_F(AlbaStreamParameterReaderTest, EmptyFileTest) {
    clearContentsOfTestFile();

    ifstream testFileReadStream(testFilePathHandler.getFullPath());
    ASSERT_TRUE(testFileReadStream.is_open());
    AlbaStreamParameterReader reader(testFileReadStream);
    ASSERT_TRUE(testFileReadStream.good());
    ASSERT_FALSE(testFileReadStream.eof());

    EXPECT_EQ(0U, reader.readData<unsigned int>());
    EXPECT_EQ(0, reader.readData<int>());
    EXPECT_EQ(0, reader.readData<double>());
    EXPECT_TRUE(reader.readData<string>().empty());
}

TEST_F(AlbaStreamParameterReaderTest, SingleParameterTest) {
    AlbaStreamParameterWriter writer(testFileWriteStream);
    writer.writeData(12345U);
    writer.writeData(-12345);
    writer.writeData(1.2345);
    writer.writeData<string>("12345");
    writer.flush();
    testFileWriteStream.close();

    ifstream testFileReadStream(testFilePathHandler.getFullPath());
    ASSERT_TRUE(testFileReadStream.is_open());
    AlbaStreamParameterReader reader(testFileReadStream);
    ASSERT_TRUE(testFileReadStream.good());
    ASSERT_FALSE(testFileReadStream.eof());

    EXPECT_EQ(12345U, reader.readData<unsigned int>());
    EXPECT_EQ(-12345, reader.readData<int>());
    EXPECT_EQ(1.2345, reader.readData<double>());
    EXPECT_EQ("12345", reader.readData<string>());
}

TEST_F(AlbaStreamParameterReaderTest, VectorTest) {
    vector<int> sampleVector{1, 2, 3, 4, 5};
    AlbaStreamParameterWriter writer(testFileWriteStream);
    writer.writeVectorData(sampleVector);
    writer.flush();
    testFileWriteStream.close();

    ifstream testFileReadStream(testFilePathHandler.getFullPath());
    ASSERT_TRUE(testFileReadStream.is_open());
    AlbaStreamParameterReader reader(testFileReadStream);
    ASSERT_TRUE(testFileReadStream.good());
    ASSERT_FALSE(testFileReadStream.eof());

    vector<int> retrievedVector;
    reader.readVectorData(retrievedVector);
    EXPECT_EQ(sampleVector, retrievedVector);
}

TEST_F(AlbaStreamParameterReaderTest, MapTest) {
    map<int, string> sampleMap{{1, "one"}, {2, "two"}, {3, "three"}};
    AlbaStreamParameterWriter writer(testFileWriteStream);
    writer.writeMapData(sampleMap);
    writer.flush();
    testFileWriteStream.close();

    ifstream testFileReadStream(testFilePathHandler.getFullPath());
    ASSERT_TRUE(testFileReadStream.is_open());
    AlbaStreamParameterReader reader(testFileReadStream);
    ASSERT_TRUE(testFileReadStream.good());
    ASSERT_FALSE(testFileReadStream.eof());

    map<int, string> retrievedmap;
    reader.readMapData(retrievedmap);
    EXPECT_EQ(sampleMap, retrievedmap);
}

}  // namespace alba
