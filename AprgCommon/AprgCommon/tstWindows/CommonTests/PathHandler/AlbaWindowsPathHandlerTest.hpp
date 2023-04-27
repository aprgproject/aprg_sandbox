#include <gtest/gtest.h>

#include <string>

namespace alba {

struct AlbaWindowsPathHandlerTest : public testing::Test {
    AlbaWindowsPathHandlerTest();
    std::string convertToSimplestPath(std::string_view path);
    std::string getDriveOfAprgDir();
    std::string pathOfAprgDirectory;
};

}  // namespace alba
