#include <Common/Math/Helpers/DivisibilityHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::mathHelper {

TEST(DivisibilityHelpersTest, IsDivisibleWorks) {
    EXPECT_FALSE(isDivisible(0U, 0U));
    EXPECT_TRUE(isDivisible(0U, 1U));
    EXPECT_TRUE(isDivisible(1U, 1U));
    EXPECT_FALSE(isDivisible(1U, 5U));
    EXPECT_TRUE(isDivisible(5U, 1U));
    EXPECT_TRUE(isDivisible(256U, 16U));
    EXPECT_FALSE(isDivisible(256U, 17U));
    EXPECT_TRUE(isDivisible(-256, -16));
    EXPECT_FALSE(isDivisible(-256, -17));
}

TEST(DivisibilityHelpersTest, IsEvenWorks) {
    EXPECT_TRUE(isEven(0U));
    EXPECT_FALSE(isEven(1U));
    EXPECT_TRUE(isEven(256U));
    EXPECT_FALSE(isEven(255U));
    EXPECT_TRUE(isEven(-256));
    EXPECT_FALSE(isEven(-255));
}

TEST(DivisibilityHelpersTest, IsOddWorks) {
    EXPECT_FALSE(isOdd(0U));
    EXPECT_TRUE(isOdd(1U));
    EXPECT_FALSE(isOdd(256U));
    EXPECT_TRUE(isOdd(255U));
    EXPECT_FALSE(isOdd(-256));
    EXPECT_TRUE(isOdd(-255));
}

TEST(DivisibilityHelpersTest, IsDivisibleByThreeWorks) {
    EXPECT_TRUE(isDivisibleByThree(0U));
    EXPECT_FALSE(isDivisibleByThree(1U));
    EXPECT_FALSE(isDivisibleByThree(157U));
    EXPECT_TRUE(isDivisibleByThree(156U));
    EXPECT_FALSE(isDivisibleByThree(-157));
    EXPECT_TRUE(isDivisibleByThree(-156));
}

TEST(DivisibilityHelpersTest, IsDivisibleByNineWorks) {
    EXPECT_TRUE(isDivisibleByNine(0U));
    EXPECT_FALSE(isDivisibleByNine(1U));
    EXPECT_FALSE(isDivisibleByNine(154U));
    EXPECT_TRUE(isDivisibleByNine(153U));
    EXPECT_FALSE(isDivisibleByNine(-154));
    EXPECT_TRUE(isDivisibleByNine(-153));
}

}  // namespace alba::mathHelper
