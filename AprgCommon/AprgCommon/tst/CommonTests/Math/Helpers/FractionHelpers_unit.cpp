#include <Common/Math/AlbaMathConstants.hpp>
#include <Common/Math/Helpers/FractionHelpers.hpp>

#include <gtest/gtest.h>

using namespace alba::AlbaMathConstants;
using namespace std;

namespace alba::mathHelper {

TEST(FractionHelpersTest, ChangeFractionToSimplestFormWorksWithIntAndUnsignedInt) {
    int32_t numerator1 = 0;
    uint32_t denominator1 = 0;
    changeFractionToSimplestForm<int32_t, uint32_t, int64_t>(numerator1, denominator1);
    EXPECT_EQ(0, numerator1);
    EXPECT_EQ(0U, denominator1);

    int32_t numerator2 = 1;
    uint32_t denominator2 = 1;
    changeFractionToSimplestForm<int32_t, uint32_t, int64_t>(numerator2, denominator2);
    EXPECT_EQ(1, numerator2);
    EXPECT_EQ(1U, denominator2);

    int32_t numerator3 = 98;
    uint32_t denominator3 = 56;
    changeFractionToSimplestForm<int32_t, uint32_t, int64_t>(numerator3, denominator3);
    EXPECT_EQ(7, numerator3);
    EXPECT_EQ(4U, denominator3);

    int32_t numerator4 = -98;
    uint32_t denominator4 = 56;
    changeFractionToSimplestForm<int32_t, uint32_t, int64_t>(numerator4, denominator4);
    EXPECT_EQ(-7, numerator4);
    EXPECT_EQ(4U, denominator4);

    int32_t numerator5 = -2147483646;
    uint32_t denominator5 = 4294967294;
    changeFractionToSimplestForm<int32_t, uint32_t, int64_t>(numerator5, denominator5);
    EXPECT_EQ(-1073741823, numerator5);
    EXPECT_EQ(2147483647U, denominator5);
}

TEST(FractionHelpersTest, ChangeFractionToSimplestFormForUnsignedWorks) {
    unsigned int numerator1 = 0;
    unsigned int denominator1 = 0;
    changeFractionToSimplestFormForUnsigned(numerator1, denominator1);
    EXPECT_EQ(0U, numerator1);
    EXPECT_EQ(0U, denominator1);

    unsigned int numerator2 = 1;
    unsigned int denominator2 = 1;
    changeFractionToSimplestFormForUnsigned(numerator2, denominator2);
    EXPECT_EQ(1U, numerator2);
    EXPECT_EQ(1U, denominator2);

    unsigned int numerator3 = 98;
    unsigned int denominator3 = 56;
    changeFractionToSimplestFormForUnsigned(numerator3, denominator3);
    EXPECT_EQ(7U, numerator3);
    EXPECT_EQ(4U, denominator3);

    unsigned int numerator4 = 4294967292;
    unsigned int denominator4 = 4294967294;
    changeFractionToSimplestFormForUnsigned(numerator4, denominator4);
    EXPECT_EQ(2147483646U, numerator4);
    EXPECT_EQ(2147483647U, denominator4);
}

TEST(FractionHelpersTest, ChangeFractionToSimplestFormForSignedWorks) {
    int numerator1 = 0;
    int denominator1 = 0;
    changeFractionToSimplestFormForSigned(numerator1, denominator1);
    EXPECT_EQ(0, numerator1);
    EXPECT_EQ(0, denominator1);

    int numerator2 = 1;
    int denominator2 = 1;
    changeFractionToSimplestFormForSigned(numerator2, denominator2);
    EXPECT_EQ(1, numerator2);
    EXPECT_EQ(1, denominator2);

    int numerator3 = 98;
    int denominator3 = 56;
    changeFractionToSimplestFormForSigned(numerator3, denominator3);
    EXPECT_EQ(7, numerator3);
    EXPECT_EQ(4, denominator3);

    int numerator4 = 98;
    int denominator4 = -56;
    changeFractionToSimplestFormForSigned(numerator4, denominator4);
    EXPECT_EQ(-7, numerator4);
    EXPECT_EQ(4, denominator4);

    int numerator5 = -98;
    int denominator5 = 56;
    changeFractionToSimplestFormForSigned(numerator5, denominator5);
    EXPECT_EQ(-7, numerator5);
    EXPECT_EQ(4, denominator5);

    int numerator6 = -98;
    int denominator6 = -56;
    changeFractionToSimplestFormForSigned(numerator6, denominator6);
    EXPECT_EQ(7, numerator6);
    EXPECT_EQ(4, denominator6);

    int numerator7 = -2147483644;
    int denominator7 = 2147483646;
    changeFractionToSimplestFormForSigned(numerator7, denominator7);
    EXPECT_EQ(-1073741822, numerator7);
    EXPECT_EQ(1073741823, denominator7);
}

TEST(FractionHelpersTest, GetBestFractionDetailsForDoubleValueWorks) {
    auto fractionDetails1(getBestFractionDetailsForDoubleValue<unsigned int>(0));
    EXPECT_EQ(1, fractionDetails1.sign);
    EXPECT_EQ(0U, fractionDetails1.numerator);
    EXPECT_EQ(1U, fractionDetails1.denominator);

    auto fractionDetails2(getBestFractionDetailsForDoubleValue<unsigned int>(1));
    EXPECT_EQ(1, fractionDetails2.sign);
    EXPECT_EQ(1U, fractionDetails2.numerator);
    EXPECT_EQ(1U, fractionDetails2.denominator);

    auto fractionDetails3(getBestFractionDetailsForDoubleValue<unsigned int>(-1));
    EXPECT_EQ(-1, fractionDetails3.sign);
    EXPECT_EQ(1U, fractionDetails3.numerator);
    EXPECT_EQ(1U, fractionDetails3.denominator);

    auto fractionDetails4(getBestFractionDetailsForDoubleValue<unsigned int>(-234));
    EXPECT_EQ(-1, fractionDetails4.sign);
    EXPECT_EQ(234U, fractionDetails4.numerator);
    EXPECT_EQ(1U, fractionDetails4.denominator);

    auto fractionDetails5(getBestFractionDetailsForDoubleValue<unsigned int>(0.3333333333333333333));
    EXPECT_EQ(1, fractionDetails5.sign);
    EXPECT_EQ(1U, fractionDetails5.numerator);
    EXPECT_EQ(3U, fractionDetails5.denominator);

    auto fractionDetails6(getBestFractionDetailsForDoubleValue<unsigned int>(-78.787878787878787878));
    EXPECT_EQ(-1, fractionDetails6.sign);
    EXPECT_EQ(2600U, fractionDetails6.numerator);
    EXPECT_EQ(33U, fractionDetails6.denominator);

    auto fractionDetails7(getBestFractionDetailsForDoubleValue<unsigned int>(2.236067977499789696409));
    EXPECT_EQ(1, fractionDetails7.sign);
    EXPECT_EQ(2446376235U, fractionDetails7.numerator);
    EXPECT_EQ(1094052712U, fractionDetails7.denominator);

    auto fractionDetails8(getBestFractionDetailsForDoubleValue<unsigned int>(POSITIVE_INFINITY_DOUBLE_VALUE));
    EXPECT_EQ(1, fractionDetails8.sign);
    EXPECT_EQ(1U, fractionDetails8.numerator);
    EXPECT_EQ(0U, fractionDetails8.denominator);

    auto fractionDetails9(getBestFractionDetailsForDoubleValue<unsigned int>(NEGATIVE_INFINITY_DOUBLE_VALUE));
    EXPECT_EQ(-1, fractionDetails9.sign);
    EXPECT_EQ(1U, fractionDetails9.numerator);
    EXPECT_EQ(0U, fractionDetails9.denominator);

    auto fractionDetails10(getBestFractionDetailsForDoubleValue<unsigned int>(NAN_DOUBLE_VALUE));
    EXPECT_EQ(1, fractionDetails10.sign);
    EXPECT_EQ(0U, fractionDetails10.numerator);
    EXPECT_EQ(1U, fractionDetails10.denominator);
}

}  // namespace alba::mathHelper
