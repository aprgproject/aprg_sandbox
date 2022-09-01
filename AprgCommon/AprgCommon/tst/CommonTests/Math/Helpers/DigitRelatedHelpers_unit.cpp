#include <Common/Math/Helpers/DigitRelatedHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace mathHelper
{

TEST(DigitRelatedHelpersTest, GetNumberOfDigitsOnBaseWorks)
{
    EXPECT_EQ(4U, getNumberOfDigitsOnBase<unsigned int>(10, 1000));
    EXPECT_EQ(10U, getNumberOfDigitsOnBase<unsigned int>(2, 1000));    EXPECT_EQ(4U, getNumberOfDigitsOnBase<unsigned int>(8, 1000));
    EXPECT_EQ(3U, getNumberOfDigitsOnBase<unsigned int>(16, 1000));
    EXPECT_EQ(2U, getNumberOfDigitsOnBase<unsigned int>(32, 1000));
}

TEST(DigitRelatedHelpersTest, GetNumberOfIntegerDigitsWorks)
{
    EXPECT_EQ(0U, getNumberOfIntegerDigits<unsigned int>(0));
    EXPECT_EQ(1U, getNumberOfIntegerDigits<unsigned int>(1));    EXPECT_EQ(2U, getNumberOfIntegerDigits<unsigned int>(54));
    EXPECT_EQ(4U, getNumberOfIntegerDigits<unsigned int>(1000));
    EXPECT_EQ(0U, getNumberOfIntegerDigits<int>(0));
    EXPECT_EQ(1U, getNumberOfIntegerDigits<int>(-1));    EXPECT_EQ(2U, getNumberOfIntegerDigits<int>(-54));
    EXPECT_EQ(4U, getNumberOfIntegerDigits<int>(-1000));
    EXPECT_EQ(0U, getNumberOfIntegerDigits<double>(0));
    EXPECT_EQ(1U, getNumberOfIntegerDigits<double>(1.1));
    EXPECT_EQ(2U, getNumberOfIntegerDigits<double>(-54.123));
    EXPECT_EQ(4U, getNumberOfIntegerDigits<double>(1000.12345));
}

TEST(DigitRelatedHelpersTest, AreNumberOfDigitsOnTheIntegerLimitWorks)
{
    EXPECT_FALSE(areNumberOfDigitsOnTheIntegerLimit<int>(0));
    EXPECT_FALSE(areNumberOfDigitsOnTheIntegerLimit<int>(1));    EXPECT_TRUE(areNumberOfDigitsOnTheIntegerLimit<int>(9));
    EXPECT_TRUE(areNumberOfDigitsOnTheIntegerLimit<int>(10));
    EXPECT_TRUE(areNumberOfDigitsOnTheIntegerLimit<int>(11));
}
}

}
