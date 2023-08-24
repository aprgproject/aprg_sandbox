#include "BaseFileReaderTest.hpp"

#include <Common/String/AlbaStringHelper.hpp>
#include <CommonTestsUtilities/File/FileUtilities.hpp>

using namespace alba::stringHelper;
using namespace std;

namespace alba {

BaseFileReaderTest::BaseFileReaderTest(std::string_view testFilePath)
    : testFilePathHandler(testFilePath), testFileWriteStream(testFilePathHandler.getFullPath()) {}

void BaseFileReaderTest::SetUp() { ASSERT_TRUE(testFileWriteStream.is_open()); }

void BaseFileReaderTest::TearDown() { clearContentsOfTestFile(); }

void BaseFileReaderTest::clearContentsOfTestFile() { clearContentsOfFile(testFilePathHandler.getFullPath()); }

}  // namespace alba
