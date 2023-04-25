#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace mathHelper {

TEST(SignRelatedHelpersTest, GetAbsoluteValueWorksForPrimitiveTypes) {
    EXPECT_EQ(1, getAbsoluteValue(1));
    EXPECT_EQ(1, getAbsoluteValue(-1));
    EXPECT_EQ(0, getAbsoluteValue(0));
    EXPECT_EQ(0.5, getAbsoluteValue(0.5));
    EXPECT_EQ(0.5, getAbsoluteValue(-0.5));
}

TEST(SignRelatedHelpersTest, GetSignWorksForPrimitiveTypes) {
    EXPECT_EQ(-1, getSign(-10));
    EXPECT_EQ(1, getSign(0));
    EXPECT_EQ(1, getSign(10));
}

TEST(SignRelatedHelpersTest, GetPositiveDeltaWorksForPrimitiveTypes) {
    EXPECT_EQ(0U, getPositiveDelta(0U, 0U));
    EXPECT_EQ(0U, getPositiveDelta(5U, 5U));
    EXPECT_EQ(5U, getPositiveDelta(5U, 10U));
    EXPECT_EQ(5U, getPositiveDelta(10U, 5U));
    EXPECT_EQ(90, getPositiveDelta(-100, -10));
    EXPECT_EQ(20, getPositiveDelta(10, -10));
    EXPECT_EQ(20, getPositiveDelta(-10, 10));
    EXPECT_EQ(90, getPositiveDelta(10, 100));
}

TEST(SignRelatedHelpersTest, ConvertToSignedThenSubtractWorks) {
    EXPECT_EQ(0, convertToSignedThenSubtract(0U, 0U));
    EXPECT_EQ(0, convertToSignedThenSubtract(5U, 5U));
    EXPECT_EQ(4, convertToSignedThenSubtract(5U, 1U));
    EXPECT_EQ(-4, convertToSignedThenSubtract(1U, 5U));
}

TEST(SignRelatedHelpersTest, GetAbsoluteValueForAlbaNumberWorks) {
    EXPECT_EQ(AlbaNumber::createFraction(1, 3), getAbsoluteValue(AlbaNumber::createFraction(1, 3)));
    EXPECT_EQ(AlbaNumber::createFraction(1, 3), getAbsoluteValue(AlbaNumber::createFraction(-1, 3)));
}

TEST(SignRelatedHelpersTest, GetSignForAlbaNumberWorks) {
    EXPECT_EQ(AlbaNumber(1), getSign(AlbaNumber::createFraction(1, 3)));
    EXPECT_EQ(AlbaNumber(-1), getSign(AlbaNumber::createFraction(-1, 3)));
}

TEST(SignRelatedHelpersTest, GetPositiveDeltaForAlbaNumberWorks) {
    EXPECT_EQ(AlbaNumber(4.444), getPositiveDelta(AlbaNumber(1.234), AlbaNumber(5.678)));
    EXPECT_EQ(AlbaNumber(4.444), getPositiveDelta(AlbaNumber(5.678), AlbaNumber(1.234)));
}

}  // namespace mathHelper

}  // namespace alba
