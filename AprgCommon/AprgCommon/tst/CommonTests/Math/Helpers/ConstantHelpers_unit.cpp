#include <Common/Math/Helpers/ConstantHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace mathHelper {

TEST(ConstantHelpersTest, GetPiWorks) { EXPECT_DOUBLE_EQ(3.14159265358979323846, getPi()); }

TEST(ConstantHelpersTest, GetEWorks) { EXPECT_DOUBLE_EQ(2.7182818284590452354, getE()); }

}  // namespace mathHelper

}  // namespace alba
