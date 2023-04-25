#include <gtest/gtest.h>

#include <string>

namespace alba {

struct AlbaLinuxPathHandlerTest : public testing::Test {
    AlbaLinuxPathHandlerTest() = default;
    std::string convertToSimplestPath(std::string const& path);
};

}  // namespace alba
