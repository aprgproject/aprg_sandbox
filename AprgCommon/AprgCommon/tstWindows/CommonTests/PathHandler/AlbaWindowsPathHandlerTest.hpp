#include <gtest/gtest.h>

#include <string>

namespace alba
{

struct AlbaWindowsPathHandlerTest : public testing::Test
{
    AlbaWindowsPathHandlerTest();
    std::string convertToSimplestPath(std::string const& path);
    std::string getDriveOfAprgDir();
    std::string pathOfAprgDirectory;
};

}
