#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <ProcessFiles/CropFile/AlbaCropFile.hpp>
#include <ProcessFilesTests/DirectoryConstants.hpp>

#include <gtest/gtest.h>

#include <fstream>
#include <string>

using namespace std;

namespace alba {

TEST(AlbaCropFileTest, NoOutputIsWrittenWhenInputIsNonExisting) {
    AlbaLocalPathHandler file1ToReadPathHandler(APRG_PROCESS_FILES_TEST_FILE1_TO_READ);
    AlbaCropFile cropFile("[.]", 100);

    EXPECT_FALSE(cropFile.isOutputFileWritten());
    cropFile.processFile(APRG_PROCESS_FILES_NON_EXISTING_FILE, file1ToReadPathHandler.getFullPath());
    EXPECT_FALSE(cropFile.isOutputFileWritten());
}

TEST(AlbaCropFileTest, CropUpdatesWorks) {
    AlbaLocalPathHandler file1ToReadPathHandler(APRG_PROCESS_FILES_TEST_FILE1_TO_READ);
    AlbaLocalPathHandler file2ToReadPathHandler(APRG_PROCESS_FILES_TEST_FILE2_TO_READ);
    ofstream testFile(file1ToReadPathHandler.getFullPath());
    ASSERT_TRUE(testFile.is_open());
    for (int i = 0; i < 100; i++) {
        testFile << i << "\n";
    }
    testFile.close();
    double capturedPercentage = 0;
    AlbaCropFile cropFile("[50]", 50, [&](double percentage) -> void { capturedPercentage = percentage; });
    EXPECT_FALSE(cropFile.isOutputFileWritten());    cropFile.processFile(file1ToReadPathHandler.getFullPath(), file2ToReadPathHandler.getFullPath());
    EXPECT_TRUE(cropFile.isOutputFileWritten());
    EXPECT_DOUBLE_EQ(100, capturedPercentage);
}

TEST(AlbaCropFileTest, CropWorksWhenCropSizeIsHalfOfTheWholeDocument) {
    AlbaLocalPathHandler file1ToReadPathHandler(APRG_PROCESS_FILES_TEST_FILE1_TO_READ);
    AlbaLocalPathHandler file2ToReadPathHandler(APRG_PROCESS_FILES_TEST_FILE2_TO_READ);
    ofstream testFile(file1ToReadPathHandler.getFullPath());
    ASSERT_TRUE(testFile.is_open());
    for (int i = 0; i < 10; i++) {
        testFile << i << "\n";
    }
    testFile.close();
    ifstream testFileToRead(file1ToReadPathHandler.getFullPath());
    AlbaFileReader testFileReader(testFileToRead);
    AlbaCropFile cropFile("[4]", testFileReader.getFileSize() / 2);
    EXPECT_FALSE(cropFile.isOutputFileWritten());
    cropFile.processFile(file1ToReadPathHandler.getFullPath(), file2ToReadPathHandler.getFullPath());
    EXPECT_TRUE(cropFile.isOutputFileWritten());

    ifstream outputTestFile(file2ToReadPathHandler.getFullPath());
    ASSERT_TRUE(outputTestFile.is_open());

    AlbaFileReader fileReader(outputTestFile);
    ASSERT_TRUE(outputTestFile.good());
    ASSERT_FALSE(outputTestFile.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
#ifdef OS_WINDOWS
    // windows handling is problematic, tellg on windows works on mysterious ways
    EXPECT_EQ(R"(4)", fileReader.getLine());
    EXPECT_EQ(R"(5)", fileReader.getLine());
    EXPECT_EQ(R"(6)", fileReader.getLine());
    EXPECT_EQ(R"(7)", fileReader.getLine());
#endif
#ifdef OS_LINUX
    EXPECT_EQ(R"(2)", fileReader.getLine());
    EXPECT_EQ(R"(3)", fileReader.getLine());
    EXPECT_EQ(R"(4)", fileReader.getLine());
    EXPECT_EQ(R"(5)", fileReader.getLine());
    EXPECT_EQ(R"(6)", fileReader.getLine());
#endif
    EXPECT_TRUE(fileReader.getLine().empty());
    EXPECT_FALSE(fileReader.isNotFinished());
}

TEST(AlbaCropFileTest, CropWorksWhenCropSizeIsTwiceOfTheWholeDocument) {
    AlbaLocalPathHandler file1ToReadPathHandler(APRG_PROCESS_FILES_TEST_FILE1_TO_READ);
    AlbaLocalPathHandler file2ToReadPathHandler(APRG_PROCESS_FILES_TEST_FILE2_TO_READ);
    ofstream testFile(file1ToReadPathHandler.getFullPath());
    ASSERT_TRUE(testFile.is_open());
    for (int i = 0; i < 10; i++) {
        testFile << i << "\n";
    }
    testFile.close();
    ifstream testFileToRead(file1ToReadPathHandler.getFullPath());
    AlbaFileReader testFileReader(testFileToRead);
    AlbaCropFile cropFile("[4]", testFileReader.getFileSize() * 2);
    EXPECT_FALSE(cropFile.isOutputFileWritten());
    cropFile.processFile(file1ToReadPathHandler.getFullPath(), file2ToReadPathHandler.getFullPath());
    EXPECT_TRUE(cropFile.isOutputFileWritten());

    ifstream outputTestFile(file2ToReadPathHandler.getFullPath());
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
    EXPECT_TRUE(fileReader.getLine().empty());
    EXPECT_FALSE(fileReader.isNotFinished());
}

TEST(AlbaCropFileTest, CropWorksWhenCropSizeIsHalfOfTheWholeDocumentAtTheStart) {
    AlbaLocalPathHandler file1ToReadPathHandler(APRG_PROCESS_FILES_TEST_FILE1_TO_READ);
    AlbaLocalPathHandler file2ToReadPathHandler(APRG_PROCESS_FILES_TEST_FILE2_TO_READ);
    ofstream testFile(file1ToReadPathHandler.getFullPath());
    ASSERT_TRUE(testFile.is_open());
    for (int i = 0; i < 10; i++) {
        testFile << i << "\n";
    }
    testFile.close();
    ifstream testFileToRead(file1ToReadPathHandler.getFullPath());
    AlbaFileReader testFileReader(testFileToRead);
    AlbaCropFile cropFile("[0]", testFileReader.getFileSize() / 2);
    EXPECT_FALSE(cropFile.isOutputFileWritten());
    cropFile.processFile(file1ToReadPathHandler.getFullPath(), file2ToReadPathHandler.getFullPath());
    EXPECT_TRUE(cropFile.isOutputFileWritten());

    ifstream outputTestFile(file2ToReadPathHandler.getFullPath());
    ASSERT_TRUE(outputTestFile.is_open());

    AlbaFileReader fileReader(outputTestFile);
    ASSERT_TRUE(outputTestFile.good());
    ASSERT_FALSE(outputTestFile.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
#ifdef OS_WINDOWS
    // windows handling is problematic, tellg on windows works on mysterious ways
    EXPECT_EQ(R"(0)", fileReader.getLine());
    EXPECT_EQ(R"(1)", fileReader.getLine());
    EXPECT_EQ(R"(2)", fileReader.getLine());
#endif
#ifdef OS_LINUX
    EXPECT_EQ(R"(0)", fileReader.getLine());
    EXPECT_EQ(R"(1)", fileReader.getLine());
    EXPECT_EQ(R"(2)", fileReader.getLine());
    EXPECT_EQ(R"(3)", fileReader.getLine());
    EXPECT_EQ(R"(4)", fileReader.getLine());
#endif
    EXPECT_TRUE(fileReader.getLine().empty());
    EXPECT_FALSE(fileReader.isNotFinished());
}

TEST(AlbaCropFileTest, CropWorksWhenCropSizeIsHalfOfTheWholeDocumentAtTheEnd) {
    AlbaLocalPathHandler file1ToReadPathHandler(APRG_PROCESS_FILES_TEST_FILE1_TO_READ);
    AlbaLocalPathHandler file2ToReadPathHandler(APRG_PROCESS_FILES_TEST_FILE2_TO_READ);
    ofstream testFile(file1ToReadPathHandler.getFullPath());
    ASSERT_TRUE(testFile.is_open());
    for (int i = 0; i < 10; i++) {
        testFile << i << "\n";
    }
    testFile.close();
    ifstream testFileToRead(file1ToReadPathHandler.getFullPath());
    AlbaFileReader testFileReader(testFileToRead);
    AlbaCropFile cropFile("[9]", testFileReader.getFileSize() / 2);
    EXPECT_FALSE(cropFile.isOutputFileWritten());
    cropFile.processFile(file1ToReadPathHandler.getFullPath(), file2ToReadPathHandler.getFullPath());
    EXPECT_TRUE(cropFile.isOutputFileWritten());

    ifstream outputTestFile(file2ToReadPathHandler.getFullPath());
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
    EXPECT_TRUE(fileReader.getLine().empty());
    EXPECT_FALSE(fileReader.isNotFinished());
}

}  // namespace alba
