#include <Math/AlbaNumber.hpp>

#include <gtest/gtest.h>

namespace alba
{

TEST(AlbaNumberTest, ConstructionWorkAsExpected)
{
    AlbaNumber number1;
    AlbaNumber number2(-81237);
    AlbaNumber number3(34095093u);
    AlbaNumber number4(-87408, -9802);
    AlbaNumber number5(4.38794);

    EXPECT_EQ(AlbaNumber::Type::Integer, number1.getType());
    EXPECT_EQ(0, number1.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number2.getType());
    EXPECT_EQ(-81237, number2.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number3.getType());
    EXPECT_EQ(34095093, number3.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Fraction, number4.getType());
    AlbaNumber::FractionData fractionData(number4.getFractionData());
    EXPECT_EQ(43704, fractionData.numerator);
    EXPECT_EQ(4901, fractionData.denominator);
    EXPECT_EQ(AlbaNumber::Type::Double, number5.getType());
    EXPECT_DOUBLE_EQ(4.38794, number5.getDouble());
}

}
