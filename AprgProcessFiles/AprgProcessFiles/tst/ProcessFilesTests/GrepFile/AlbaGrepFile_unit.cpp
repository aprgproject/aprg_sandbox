#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <ProcessFiles/GrepFile/AlbaGrepFile.hpp>
#include <ProcessFilesTests/DirectoryConstants.hpp>

#include <gtest/gtest.h>

#include <fstream>
#include <string>

using namespace std;

namespace alba {

TEST(AlbaGrepFileTest, NoOutputIsWrittenWhenInputIsNonExisting) {
    AlbaLocalPathHandler file1ToReadPathHandler(APRG_PROCESS_FILES_TEST_FILE1_TO_READ);
    AlbaGrepFile grepFile("[.]");
    EXPECT_FALSE(grepFile.isOutputFileWritten());
    grepFile.processFile(APRG_PROCESS_FILES_NON_EXISTING_FILE, file1ToReadPathHandler.getFullPath());
    EXPECT_FALSE(grepFile.isOutputFileWritten());
}

TEST(AlbaGrepFileTest, GrepUpdatesWorks) {
    AlbaLocalPathHandler file1ToReadPathHandler(APRG_PROCESS_FILES_TEST_FILE1_TO_READ);
    AlbaLocalPathHandler file2ToReadPathHandler(APRG_PROCESS_FILES_TEST_FILE2_TO_READ);
    ofstream testFile(file1ToReadPathHandler.getFullPath());
    ASSERT_TRUE(testFile.is_open());
    for (int i = 0; i < 100; i++) {
        testFile << i << "\n";
    }
    testFile.close();

    double capturedPercentage = 0;
    AlbaGrepFile grepFile("[0]", [&](double percentage) -> void { capturedPercentage = percentage; });
    EXPECT_FALSE(grepFile.isOutputFileWritten());
    grepFile.processFile(file1ToReadPathHandler.getFullPath(), file2ToReadPathHandler.getFullPath());
    EXPECT_TRUE(grepFile.isOutputFileWritten());
    EXPECT_DOUBLE_EQ(100, capturedPercentage);
}

TEST(AlbaGrepFileTest, GrepWorks) {
    AlbaLocalPathHandler file1ToReadPathHandler(APRG_PROCESS_FILES_TEST_FILE1_TO_READ);
    AlbaLocalPathHandler file2ToReadPathHandler(APRG_PROCESS_FILES_TEST_FILE2_TO_READ);
    ofstream testFile(file1ToReadPathHandler.getFullPath());
    ASSERT_TRUE(testFile.is_open());
    testFile << R"(As a person, I think that Mark is so cool)"
             << "\n";
    testFile << R"(As a designer, I know that Mark Earvin is so cool)"
             << "\n";
    testFile << R"(As a programmer, I know that Earvin is so cool)"
             << "\n";
    testFile << R"(As a coder, I know that MARKalba is so cool)"
             << "\n";
    testFile.close();

    AlbaGrepFile grepFile("[mark]");
    EXPECT_FALSE(grepFile.isOutputFileWritten());
    grepFile.processFile(file1ToReadPathHandler.getFullPath(), file2ToReadPathHandler.getFullPath());
    EXPECT_TRUE(grepFile.isOutputFileWritten());

    ifstream outputTestFile(file2ToReadPathHandler.getFullPath());
    ASSERT_TRUE(outputTestFile.is_open());

    AlbaFileReader fileReader(outputTestFile);
    ASSERT_TRUE(outputTestFile.good());
    ASSERT_FALSE(outputTestFile.eof());
    EXPECT_TRUE(fileReader.isNotFinished());
    EXPECT_EQ(R"(As a person, I think that Mark is so cool)", fileReader.getLine());
    EXPECT_EQ(R"(As a designer, I know that Mark Earvin is so cool)", fileReader.getLine());
    EXPECT_EQ(R"(As a coder, I know that MARKalba is so cool)", fileReader.getLine());
    EXPECT_TRUE(fileReader.getLine().empty());
    EXPECT_FALSE(fileReader.isNotFinished());
}

}  // namespace alba
