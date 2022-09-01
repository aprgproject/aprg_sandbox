#include <Common/Math/AlbaMathConstants.hpp>
#include <Common/Math/Helpers/FractionHelpers.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace mathHelper
{

TEST(AlbaMathHelperTest, GetFractionDetailsInLowestFormWorks)
{
    FractionDetails fractionDetails1(getFractionDetailsInLowestForm(0, 0));
    EXPECT_EQ(1, fractionDetails1.sign);
    EXPECT_EQ(0U, fractionDetails1.numerator);
    EXPECT_EQ(0U, fractionDetails1.denominator);

    FractionDetails fractionDetails2(getFractionDetailsInLowestForm(1, 1));
    EXPECT_EQ(1, fractionDetails2.sign);
    EXPECT_EQ(1U, fractionDetails2.numerator);
    EXPECT_EQ(1U, fractionDetails2.denominator);

    FractionDetails fractionDetails3(getFractionDetailsInLowestForm(16, -32));
    EXPECT_EQ(-1, fractionDetails3.sign);
    EXPECT_EQ(1U, fractionDetails3.numerator);
    EXPECT_EQ(2U, fractionDetails3.denominator);

    FractionDetails fractionDetails4(getFractionDetailsInLowestForm(-98, 56));
    EXPECT_EQ(-1, fractionDetails4.sign);
    EXPECT_EQ(7U, fractionDetails4.numerator);
    EXPECT_EQ(4U, fractionDetails4.denominator);

    FractionDetails fractionDetails5(getFractionDetailsInLowestForm(-15, -20));
    EXPECT_EQ(1, fractionDetails5.sign);
    EXPECT_EQ(3U, fractionDetails5.numerator);
    EXPECT_EQ(4U, fractionDetails5.denominator);

    FractionDetails fractionDetails6(getFractionDetailsInLowestForm(1234567891, -1234567892));
    EXPECT_EQ(-1, fractionDetails6.sign);
    EXPECT_EQ(1234567891U, fractionDetails6.numerator);
    EXPECT_EQ(1234567892U, fractionDetails6.denominator);
}

TEST(AlbaMathHelperTest, GetBestFractionDetailsForDoubleValueWorks)
{
    FractionDetails fractionDetails1(getBestFractionDetailsForDoubleValue(0));
    EXPECT_EQ(1, fractionDetails1.sign);
    EXPECT_EQ(0U, fractionDetails1.numerator);
    EXPECT_EQ(1U, fractionDetails1.denominator);

    FractionDetails fractionDetails2(getBestFractionDetailsForDoubleValue(1));
    EXPECT_EQ(1, fractionDetails2.sign);
    EXPECT_EQ(1U, fractionDetails2.numerator);
    EXPECT_EQ(1U, fractionDetails2.denominator);

    FractionDetails fractionDetails3(getBestFractionDetailsForDoubleValue(-1));
    EXPECT_EQ(-1, fractionDetails3.sign);
    EXPECT_EQ(1U, fractionDetails3.numerator);
    EXPECT_EQ(1U, fractionDetails3.denominator);

    FractionDetails fractionDetails4(getBestFractionDetailsForDoubleValue(-234));
    EXPECT_EQ(-1, fractionDetails4.sign);
    EXPECT_EQ(234U, fractionDetails4.numerator);
    EXPECT_EQ(1U, fractionDetails4.denominator);

    FractionDetails fractionDetails5(getBestFractionDetailsForDoubleValue(0.3333333333333333333));
    EXPECT_EQ(1, fractionDetails5.sign);
    EXPECT_EQ(1U, fractionDetails5.numerator);
    EXPECT_EQ(3U, fractionDetails5.denominator);

    FractionDetails fractionDetails6(getBestFractionDetailsForDoubleValue(-78.787878787878787878));
    EXPECT_EQ(-1, fractionDetails6.sign);
    EXPECT_EQ(2600U, fractionDetails6.numerator);
    EXPECT_EQ(33U, fractionDetails6.denominator);

    FractionDetails fractionDetails7(getBestFractionDetailsForDoubleValue(2.236067977499789696409));
    EXPECT_EQ(1, fractionDetails7.sign);
    EXPECT_EQ(2446376235U, fractionDetails7.numerator);
    EXPECT_EQ(1094052712U, fractionDetails7.denominator);

    FractionDetails fractionDetails8(getBestFractionDetailsForDoubleValue(POSITIVE_INFINITY_DOUBLE_VALUE));
    EXPECT_EQ(1, fractionDetails8.sign);
    EXPECT_EQ(1U, fractionDetails8.numerator);
    EXPECT_EQ(0U, fractionDetails8.denominator);

    FractionDetails fractionDetails9(getBestFractionDetailsForDoubleValue(NEGATIVE_INFINITY_DOUBLE_VALUE));
    EXPECT_EQ(-1, fractionDetails9.sign);
    EXPECT_EQ(1U, fractionDetails9.numerator);
    EXPECT_EQ(0U, fractionDetails9.denominator);

    FractionDetails fractionDetails10(getBestFractionDetailsForDoubleValue(NAN_DOUBLE_VALUE));
    EXPECT_EQ(1, fractionDetails10.sign);
    EXPECT_EQ(0U, fractionDetails10.numerator);
    EXPECT_EQ(1U, fractionDetails10.denominator);
}

}

}
