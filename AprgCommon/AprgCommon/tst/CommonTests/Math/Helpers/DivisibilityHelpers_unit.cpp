#include <Common/Math/Helpers/DivisibilityHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace mathHelper {

TEST(DivisibilityHelpersTest, IsDivisibleWorks) {
    EXPECT_FALSE(isDivisible(0U, 0U));
    EXPECT_TRUE(isDivisible(0U, 1U));
    EXPECT_TRUE(isDivisible(1U, 1U));
    EXPECT_FALSE(isDivisible(1U, 5U));
    EXPECT_TRUE(isDivisible(5U, 1U));
    EXPECT_TRUE(isDivisible(256U, 16U));
    EXPECT_FALSE(isDivisible(256U, 17U));
}

TEST(DivisibilityHelpersTest, IsEvenWorks) {
    EXPECT_TRUE(isEven(0U));
    EXPECT_FALSE(isEven(1U));
    EXPECT_TRUE(isEven(256U));
    EXPECT_FALSE(isEven(255U));
}

TEST(DivisibilityHelpersTest, IsOddWorks) {
    EXPECT_FALSE(isOdd(0U));
    EXPECT_TRUE(isOdd(1U));
    EXPECT_FALSE(isOdd(256U));
    EXPECT_TRUE(isOdd(255U));
}

}  // namespace mathHelper

}  // namespace alba
