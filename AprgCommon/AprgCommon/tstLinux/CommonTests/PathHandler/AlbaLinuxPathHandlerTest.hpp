#include <gtest/gtest.h>

#include <string>

namespace alba {

struct AlbaLinuxPathHandlerTest : public testing::Test {
    AlbaLinuxPathHandlerTest() = default;
    std::string convertToSimplestPath(std::string_view path);
};

}  // namespace alba
