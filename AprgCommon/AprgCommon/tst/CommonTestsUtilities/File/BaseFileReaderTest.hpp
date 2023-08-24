#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <gtest/gtest.h>

#include <fstream>
#include <string_view>

namespace alba {

struct BaseFileReaderTest : public testing::Test {
    BaseFileReaderTest(std::string_view testFilePath);

    void SetUp() override;
    void TearDown() override;
    void clearContentsOfTestFile();

    AlbaLocalPathHandler testFilePathHandler;
    std::ofstream testFileWriteStream;
};

}  // namespace alba
