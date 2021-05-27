#include <DirectoryConstants.hpp>
#include <GrepFile/AlbaGrepFile.hpp>
#include <File/AlbaFileReader.hpp>

#include <gtest/gtest.h>

#include <fstream>
#include <string>

using namespace std;

namespace alba
{

TEST(AlbaGrepFileTest, NoOutputIsWrittenWhenInputIsNonExisting)
{
    AlbaGrepFile grepFile("[.]");    EXPECT_FALSE(grepFile.isOutputFileWritten());
    grepFile.processFile(APRG_PROCESS_FILES_NON_EXISTING_FILE, APRG_PROCESS_FILES_TEST_FILE1_TO_READ);
    EXPECT_FALSE(grepFile.isOutputFileWritten());
}
TEST(AlbaGrepFileTest, GrepUpdatesWorksAsExpected)
{
    ofstream testFile(APRG_PROCESS_FILES_TEST_FILE1_TO_READ);
    ASSERT_TRUE(testFile.is_open());
    for(unsigned int i = 0; i<100; i++)
    {
        testFile << i << endl;
    }
    testFile.close();

    double capturedPercentage=0;
    AlbaGrepFile grepFile("[0]", [&](double percentage)->void
    {
        capturedPercentage = percentage;
    });
    EXPECT_FALSE(grepFile.isOutputFileWritten());
    grepFile.processFile(APRG_PROCESS_FILES_TEST_FILE1_TO_READ, APRG_PROCESS_FILES_TEST_FILE2_TO_READ);
    EXPECT_TRUE(grepFile.isOutputFileWritten());
    EXPECT_DOUBLE_EQ(100, capturedPercentage);
}

TEST(AlbaGrepFileTest, GrepWorksAsExpected)
{
    ofstream testFile(APRG_PROCESS_FILES_TEST_FILE1_TO_READ);
    ASSERT_TRUE(testFile.is_open());
    testFile << R"(As a person, I think that Mark is so cool)" << endl;
    testFile << R"(As a designer, I know that Mark Earvin is so cool)" << endl;
    testFile << R"(As a programmer, I know that Earvin is so cool)" << endl;
    testFile << R"(As a coder, I know that MARKalba is so cool)" << endl;
    testFile.close();

    AlbaGrepFile grepFile("[mark]");
    EXPECT_FALSE(grepFile.isOutputFileWritten());
    grepFile.processFile(APRG_PROCESS_FILES_TEST_FILE1_TO_READ, APRG_PROCESS_FILES_TEST_FILE2_TO_READ);
    EXPECT_TRUE(grepFile.isOutputFileWritten());

    ifstream outputTestFile(APRG_PROCESS_FILES_TEST_FILE2_TO_READ);
    ASSERT_TRUE(outputTestFile.is_open());

    AlbaFileReader fileReader(outputTestFile);
    ASSERT_TRUE(outputTestFile.good());
    ASSERT_FALSE(outputTestFile.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(R"(As a person, I think that Mark is so cool)", fileReader.getLine());
    EXPECT_EQ(R"(As a designer, I know that Mark Earvin is so cool)", fileReader.getLine());
    EXPECT_EQ(R"(As a coder, I know that MARKalba is so cool)", fileReader.getLine());
    EXPECT_EQ("", fileReader.getLine());
    EXPECT_FALSE(fileReader.isNotFinished());
}

}