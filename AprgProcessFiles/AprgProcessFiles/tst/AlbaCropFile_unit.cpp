#include <DirectoryConstants.hpp>
#include <CropFile/AlbaCropFile.hpp>
#include <File/AlbaFileReader.hpp>

#include <gtest/gtest.h>

#include <fstream>
#include <string>

using namespace std;

namespace alba
{

TEST(AlbaCropFileTest, NoOutputIsWrittenWhenInputIsNonExisting)
{
    AlbaCropFile cropFile("[.]", 100);
    EXPECT_FALSE(cropFile.isOutputFileWritten());
    cropFile.processFile(APRG_PROCESS_FILES_NON_EXISTING_FILE, APRG_PROCESS_FILES_TEST_FILE1_TO_READ);
    EXPECT_FALSE(cropFile.isOutputFileWritten());
}

TEST(AlbaCropFileTest, CropUpdatesWorksAsExpected)
{
    ofstream testFile(APRG_PROCESS_FILES_TEST_FILE1_TO_READ);
    ASSERT_TRUE(testFile.is_open());
    for(unsigned int i = 0; i<100; i++)
    {
        testFile << i << endl;
    }
    testFile.close();

    double capturedPercentage=0;
    AlbaCropFile cropFile("[50]", 50, [&](double percentage)->void
    {
        capturedPercentage = percentage;
    });
    EXPECT_FALSE(cropFile.isOutputFileWritten());
    cropFile.processFile(APRG_PROCESS_FILES_TEST_FILE1_TO_READ, APRG_PROCESS_FILES_TEST_FILE2_TO_READ);
    EXPECT_TRUE(cropFile.isOutputFileWritten());
    EXPECT_DOUBLE_EQ(100, capturedPercentage);
}

TEST(AlbaCropFileTest, CropWorksAsExpectedWhenCropSizeIsHalfOfTheWholeDocument) // windows handling is problematic
{
    ofstream testFile(APRG_PROCESS_FILES_TEST_FILE1_TO_READ);
    ASSERT_TRUE(testFile.is_open());
    for(unsigned int i = 0; i<10; i++)
    {
        testFile << i << endl;
    }
    testFile.close();

    ifstream testFileToRead(APRG_PROCESS_FILES_TEST_FILE1_TO_READ);
    AlbaFileReader testFileReader(testFileToRead);

    AlbaCropFile cropFile("[4]", testFileReader.getFileSize()/2);
    EXPECT_FALSE(cropFile.isOutputFileWritten());
    cropFile.processFile(APRG_PROCESS_FILES_TEST_FILE1_TO_READ, APRG_PROCESS_FILES_TEST_FILE2_TO_READ);
    EXPECT_TRUE(cropFile.isOutputFileWritten());

    ifstream outputTestFile(APRG_PROCESS_FILES_TEST_FILE2_TO_READ);
    ASSERT_TRUE(outputTestFile.is_open());

    AlbaFileReader fileReader(outputTestFile);
    ASSERT_TRUE(outputTestFile.good());
    ASSERT_FALSE(outputTestFile.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(R"(4)", fileReader.getLine());
    EXPECT_EQ(R"(5)", fileReader.getLine());
    EXPECT_EQ(R"(6)", fileReader.getLine());
    EXPECT_EQ(R"(7)", fileReader.getLine());
    EXPECT_EQ("", fileReader.getLine());
    EXPECT_FALSE(fileReader.isNotFinished());
}

TEST(AlbaCropFileTest, CropWorksAsExpectedWhenCropSizeIsTwiceOfTheWholeDocument) // windows handling is problematic
{
    ofstream testFile(APRG_PROCESS_FILES_TEST_FILE1_TO_READ);
    ASSERT_TRUE(testFile.is_open());
    for(unsigned int i = 0; i<10; i++)
    {
        testFile << i << endl;
    }
    testFile.close();

    ifstream testFileToRead(APRG_PROCESS_FILES_TEST_FILE1_TO_READ);
    AlbaFileReader testFileReader(testFileToRead);

    AlbaCropFile cropFile("[4]", testFileReader.getFileSize()*2);
    EXPECT_FALSE(cropFile.isOutputFileWritten());
    cropFile.processFile(APRG_PROCESS_FILES_TEST_FILE1_TO_READ, APRG_PROCESS_FILES_TEST_FILE2_TO_READ);
    EXPECT_TRUE(cropFile.isOutputFileWritten());

    ifstream outputTestFile(APRG_PROCESS_FILES_TEST_FILE2_TO_READ);
    ASSERT_TRUE(outputTestFile.is_open());

    AlbaFileReader fileReader(outputTestFile);
    ASSERT_TRUE(outputTestFile.good());
    ASSERT_FALSE(outputTestFile.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(R"(0)", fileReader.getLine());
    EXPECT_EQ(R"(1)", fileReader.getLine());
    EXPECT_EQ(R"(2)", fileReader.getLine());
    EXPECT_EQ(R"(3)", fileReader.getLine());
    EXPECT_EQ(R"(4)", fileReader.getLine());
    EXPECT_EQ(R"(5)", fileReader.getLine());
    EXPECT_EQ(R"(6)", fileReader.getLine());
    EXPECT_EQ(R"(7)", fileReader.getLine());
    EXPECT_EQ(R"(8)", fileReader.getLine());
    EXPECT_EQ(R"(9)", fileReader.getLine());
    EXPECT_EQ("", fileReader.getLine());
    EXPECT_FALSE(fileReader.isNotFinished());
}

TEST(AlbaCropFileTest, CropWorksAsExpectedWhenCropSizeIsHalfOfTheWholeDocumentAtTheStart) // windows handling is problematic
{
    ofstream testFile(APRG_PROCESS_FILES_TEST_FILE1_TO_READ);
    ASSERT_TRUE(testFile.is_open());
    for(unsigned int i = 0; i<10; i++)
    {
        testFile << i << endl;
    }
    testFile.close();

    ifstream testFileToRead(APRG_PROCESS_FILES_TEST_FILE1_TO_READ);
    AlbaFileReader testFileReader(testFileToRead);

    AlbaCropFile cropFile("[0]", testFileReader.getFileSize()/2);
    EXPECT_FALSE(cropFile.isOutputFileWritten());
    cropFile.processFile(APRG_PROCESS_FILES_TEST_FILE1_TO_READ, APRG_PROCESS_FILES_TEST_FILE2_TO_READ);
    EXPECT_TRUE(cropFile.isOutputFileWritten());

    ifstream outputTestFile(APRG_PROCESS_FILES_TEST_FILE2_TO_READ);
    ASSERT_TRUE(outputTestFile.is_open());

    AlbaFileReader fileReader(outputTestFile);
    ASSERT_TRUE(outputTestFile.good());
    ASSERT_FALSE(outputTestFile.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(R"(0)", fileReader.getLine());
    EXPECT_EQ(R"(1)", fileReader.getLine());
    EXPECT_EQ(R"(2)", fileReader.getLine());
    EXPECT_EQ("", fileReader.getLine());
    EXPECT_FALSE(fileReader.isNotFinished());
}

TEST(AlbaCropFileTest, CropWorksAsExpectedWhenCropSizeIsHalfOfTheWholeDocumentAtTheEnd) // windows handling is problematic
{
    ofstream testFile(APRG_PROCESS_FILES_TEST_FILE1_TO_READ);
    ASSERT_TRUE(testFile.is_open());
    for(unsigned int i = 0; i<10; i++)
    {
        testFile << i << endl;
    }
    testFile.close();

    ifstream testFileToRead(APRG_PROCESS_FILES_TEST_FILE1_TO_READ);
    AlbaFileReader testFileReader(testFileToRead);

    AlbaCropFile cropFile("[9]", testFileReader.getFileSize()/2);
    EXPECT_FALSE(cropFile.isOutputFileWritten());
    cropFile.processFile(APRG_PROCESS_FILES_TEST_FILE1_TO_READ, APRG_PROCESS_FILES_TEST_FILE2_TO_READ);
    EXPECT_TRUE(cropFile.isOutputFileWritten());

    ifstream outputTestFile(APRG_PROCESS_FILES_TEST_FILE2_TO_READ);
    ASSERT_TRUE(outputTestFile.is_open());

    AlbaFileReader fileReader(outputTestFile);
    ASSERT_TRUE(outputTestFile.good());
    ASSERT_FALSE(outputTestFile.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(R"(5)", fileReader.getLine());
    EXPECT_EQ(R"(6)", fileReader.getLine());
    EXPECT_EQ(R"(7)", fileReader.getLine());
    EXPECT_EQ(R"(8)", fileReader.getLine());
    EXPECT_EQ(R"(9)", fileReader.getLine());
    EXPECT_EQ("", fileReader.getLine());
    EXPECT_FALSE(fileReader.isNotFinished());
}

}
