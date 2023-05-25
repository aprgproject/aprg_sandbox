#include <Common/Math/Helpers/DigitRelatedHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::mathHelper {

TEST(DigitRelatedHelpersTest, GetNumberOfDigitsOnBaseWorks) {
    EXPECT_EQ(4U, getNumberOfDigitsOnBase<int>(10, 1000));
    EXPECT_EQ(10U, getNumberOfDigitsOnBase<int>(2, 1000));
    EXPECT_EQ(4U, getNumberOfDigitsOnBase<int>(8, 1000));
    EXPECT_EQ(3U, getNumberOfDigitsOnBase<int>(16, 1000));
    EXPECT_EQ(2U, getNumberOfDigitsOnBase<int>(32, 1000));
}

TEST(DigitRelatedHelpersTest, GetNumberOfBase10DigitsWorks) {
    EXPECT_EQ(0U, getNumberOfBase10Digits<int>(0));
    EXPECT_EQ(1U, getNumberOfBase10Digits<int>(1));
    EXPECT_EQ(2U, getNumberOfBase10Digits<int>(54));
    EXPECT_EQ(4U, getNumberOfBase10Digits<int>(1000));
    EXPECT_EQ(0U, getNumberOfBase10Digits<int>(0));
    EXPECT_EQ(1U, getNumberOfBase10Digits<int>(-1));
    EXPECT_EQ(2U, getNumberOfBase10Digits<int>(-54));
    EXPECT_EQ(4U, getNumberOfBase10Digits<int>(-1000));
}

TEST(DigitRelatedHelpersTest, AreNumberOfDigitsOnTheIntegerLimitWorks) {
    EXPECT_FALSE(areNumberOfDigitsOnTheIntegerLimit<int>(0));
    EXPECT_FALSE(areNumberOfDigitsOnTheIntegerLimit<int>(1));
    EXPECT_TRUE(areNumberOfDigitsOnTheIntegerLimit<int>(9));
    EXPECT_TRUE(areNumberOfDigitsOnTheIntegerLimit<int>(10));
    EXPECT_TRUE(areNumberOfDigitsOnTheIntegerLimit<int>(11));
}

}  // namespace alba::mathHelper
