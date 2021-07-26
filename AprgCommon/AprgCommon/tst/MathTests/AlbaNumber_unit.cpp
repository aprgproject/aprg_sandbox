#include <Math/AlbaNumber.hpp>

#include <gtest/gtest.h>

#include <ctgmath>

using namespace std;

namespace alba
{

TEST(AlbaNumberTest, SizeValueIsExpected)
{
    AlbaNumber number;

    EXPECT_EQ(16u, sizeof(number));
    EXPECT_EQ(8u, number.getNumberDataSize());
}

TEST(AlbaNumberTest, ConstructionWorksAsExpected)
{
    AlbaNumber number1;
    AlbaNumber number2(-81237);
    AlbaNumber number3(34095093u);
    AlbaNumber number4(-87408, -9802);
    AlbaNumber number5(-100, 10);
    AlbaNumber number6(-100, -10);
    AlbaNumber number7(4564.38794);
    AlbaNumber number8(AlbaNumber::Value::PositiveInfinity);
    AlbaNumber number9(AlbaNumber::Value::NegativeInfinity);
    AlbaNumber number10(AlbaNumber::Value::NotANumber);

    EXPECT_EQ(AlbaNumber::Type::Integer, number1.getType());
    EXPECT_EQ(0, number1.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number2.getType());
    EXPECT_EQ(-81237, number2.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number3.getType());
    EXPECT_EQ(34095093, number3.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Fraction, number4.getType());
    AlbaNumber::FractionData fractionData(number4.getFractionData());
    EXPECT_EQ(43704, fractionData.numerator);
    EXPECT_EQ(4901u, fractionData.denominator);
    EXPECT_EQ(AlbaNumber::Type::Integer, number5.getType());
    EXPECT_EQ(-10, number5.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number6.getType());
    EXPECT_EQ(10, number6.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Double, number7.getType());
    EXPECT_DOUBLE_EQ(4564.38794, number7.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number8.getType());
    EXPECT_DOUBLE_EQ(INFINITY, number8.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number9.getType());
    EXPECT_DOUBLE_EQ(-INFINITY, number9.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number10.getType());
    EXPECT_TRUE(isnan(number10.getDouble()));
}

TEST(AlbaNumberTest, IsIntegerTypeWorksAsExpected)
{
    AlbaNumber number1;
    AlbaNumber number2(-81237);
    AlbaNumber number3(34095093u);
    AlbaNumber number4(-87408, -9802);
    AlbaNumber number5(-100, 10);
    AlbaNumber number6(4564.38794);

    EXPECT_TRUE(number1.isIntegerType());
    EXPECT_TRUE(number2.isIntegerType());
    EXPECT_TRUE(number3.isIntegerType());
    EXPECT_FALSE(number4.isIntegerType());
    EXPECT_TRUE(number5.isIntegerType());
    EXPECT_FALSE(number6.isIntegerType());
}

TEST(AlbaNumberTest, IsFractionTypeWorksAsExpected)
{
    AlbaNumber number1;
    AlbaNumber number2(-81237);
    AlbaNumber number3(34095093u);
    AlbaNumber number4(-87408, -9802);
    AlbaNumber number5(-100, 10);
    AlbaNumber number6(4564.38794);

    EXPECT_FALSE(number1.isFractionType());
    EXPECT_FALSE(number2.isFractionType());
    EXPECT_FALSE(number3.isFractionType());
    EXPECT_TRUE(number4.isFractionType());
    EXPECT_FALSE(number5.isFractionType());
    EXPECT_FALSE(number6.isFractionType());
}

TEST(AlbaNumberTest, IsDoubleTypeWorksAsExpected)
{
    AlbaNumber number1;
    AlbaNumber number2(-81237);
    AlbaNumber number3(34095093u);
    AlbaNumber number4(-87408, -9802);
    AlbaNumber number5(-100, 10);
    AlbaNumber number6(4564.38794);

    EXPECT_FALSE(number1.isDoubleType());
    EXPECT_FALSE(number2.isDoubleType());
    EXPECT_FALSE(number3.isDoubleType());
    EXPECT_FALSE(number4.isDoubleType());
    EXPECT_FALSE(number5.isDoubleType());
    EXPECT_TRUE(number6.isDoubleType());
}

TEST(AlbaNumberTest, IsIntegerOrFractionTypeWorksAsExpected)
{
    AlbaNumber number1;
    AlbaNumber number2(-81237);
    AlbaNumber number3(34095093u);
    AlbaNumber number4(-87408, -9802);
    AlbaNumber number5(-100, 10);
    AlbaNumber number6(4564.38794);

    EXPECT_TRUE(number1.isIntegerOrFractionType());
    EXPECT_TRUE(number2.isIntegerOrFractionType());
    EXPECT_TRUE(number3.isIntegerOrFractionType());
    EXPECT_TRUE(number4.isIntegerOrFractionType());
    EXPECT_TRUE(number5.isIntegerOrFractionType());
    EXPECT_FALSE(number6.isIntegerOrFractionType());
}

TEST(AlbaNumberTest, IsPositiveInfinityWorksAsExpected)
{
    AlbaNumber number1;
    AlbaNumber number2(-81237);
    AlbaNumber number3(34095093u);
    AlbaNumber number4(-87408, -9802);
    AlbaNumber number5(-100, 10);
    AlbaNumber number6(4564.38794);
    AlbaNumber number7(AlbaNumber::Value::PositiveInfinity);
    AlbaNumber number8(AlbaNumber::Value::NegativeInfinity);
    AlbaNumber number9(100, 0);
    AlbaNumber number10(-100, 0);
    AlbaNumber number11(AlbaNumber::Value::NotANumber);

    EXPECT_FALSE(number1.isPositiveInfinity());
    EXPECT_FALSE(number2.isPositiveInfinity());
    EXPECT_FALSE(number3.isPositiveInfinity());
    EXPECT_FALSE(number4.isPositiveInfinity());
    EXPECT_FALSE(number5.isPositiveInfinity());
    EXPECT_FALSE(number6.isPositiveInfinity());
    EXPECT_TRUE(number7.isPositiveInfinity());
    EXPECT_FALSE(number8.isPositiveInfinity());
    EXPECT_TRUE(number9.isPositiveInfinity());
    EXPECT_FALSE(number10.isPositiveInfinity());
    EXPECT_FALSE(number11.isPositiveInfinity());
}

TEST(AlbaNumberTest, IsNegativeInfinityWorksAsExpected)
{
    AlbaNumber number1;
    AlbaNumber number2(-81237);
    AlbaNumber number3(34095093u);
    AlbaNumber number4(-87408, -9802);
    AlbaNumber number5(-100, 10);
    AlbaNumber number6(4564.38794);
    AlbaNumber number7(AlbaNumber::Value::PositiveInfinity);
    AlbaNumber number8(AlbaNumber::Value::NegativeInfinity);
    AlbaNumber number9(100, 0);
    AlbaNumber number10(-100, 0);
    AlbaNumber number11(AlbaNumber::Value::NotANumber);

    EXPECT_FALSE(number1.isNegativeInfinity());
    EXPECT_FALSE(number2.isNegativeInfinity());
    EXPECT_FALSE(number3.isNegativeInfinity());
    EXPECT_FALSE(number4.isNegativeInfinity());
    EXPECT_FALSE(number5.isNegativeInfinity());
    EXPECT_FALSE(number6.isNegativeInfinity());
    EXPECT_FALSE(number7.isNegativeInfinity());
    EXPECT_TRUE(number8.isNegativeInfinity());
    EXPECT_FALSE(number9.isNegativeInfinity());
    EXPECT_TRUE(number10.isNegativeInfinity());
    EXPECT_FALSE(number11.isNegativeInfinity());
}

TEST(AlbaNumberTest, IsNotANumberWorksAsExpected)
{
    AlbaNumber number1;
    AlbaNumber number2(-81237);
    AlbaNumber number3(34095093u);
    AlbaNumber number4(-87408, -9802);
    AlbaNumber number5(-100, 10);
    AlbaNumber number6(4564.38794);
    AlbaNumber number7(AlbaNumber::Value::PositiveInfinity);
    AlbaNumber number8(AlbaNumber::Value::NegativeInfinity);
    AlbaNumber number9(100, 0);
    AlbaNumber number10(-100, 0);
    AlbaNumber number11(AlbaNumber::Value::NotANumber);

    EXPECT_FALSE(number1.isNotANumber());
    EXPECT_FALSE(number2.isNotANumber());
    EXPECT_FALSE(number3.isNotANumber());
    EXPECT_FALSE(number4.isNotANumber());
    EXPECT_FALSE(number5.isNotANumber());
    EXPECT_FALSE(number6.isNotANumber());
    EXPECT_FALSE(number7.isNotANumber());
    EXPECT_FALSE(number8.isNotANumber());
    EXPECT_FALSE(number9.isNotANumber());
    EXPECT_FALSE(number10.isNotANumber());
    EXPECT_TRUE(number11.isNotANumber());
}

TEST(AlbaNumberTest, HasValidValueWorksAsExpected)
{
    AlbaNumber number1;
    AlbaNumber number2(-81237);
    AlbaNumber number3(34095093u);
    AlbaNumber number4(-87408, -9802);
    AlbaNumber number5(-100, 10);
    AlbaNumber number6(4564.38794);
    AlbaNumber number7(AlbaNumber::Value::PositiveInfinity);
    AlbaNumber number8(AlbaNumber::Value::NegativeInfinity);
    AlbaNumber number9(100, 0);
    AlbaNumber number10(-100, 0);
    AlbaNumber number11(AlbaNumber::Value::NotANumber);

    EXPECT_TRUE(number1.hasValidValue());
    EXPECT_TRUE(number2.hasValidValue());
    EXPECT_TRUE(number3.hasValidValue());
    EXPECT_TRUE(number4.hasValidValue());
    EXPECT_TRUE(number5.hasValidValue());
    EXPECT_TRUE(number6.hasValidValue());
    EXPECT_FALSE(number7.hasValidValue());
    EXPECT_FALSE(number8.hasValidValue());
    EXPECT_FALSE(number9.hasValidValue());
    EXPECT_FALSE(number10.hasValidValue());
    EXPECT_FALSE(number11.hasValidValue());
}

TEST(AlbaNumberTest, GetIntegerWorksAsExpected)
{
    AlbaNumber number1;
    AlbaNumber number2(-81237);
    AlbaNumber number3(34095093u);
    AlbaNumber number4(-87408, -9802);
    AlbaNumber number5(4564.38794);

    EXPECT_EQ(0, number1.getInteger());
    EXPECT_EQ(-81237, number2.getInteger());
    EXPECT_EQ(34095093, number3.getInteger());
    EXPECT_EQ(9, number4.getInteger());
    EXPECT_EQ(4564, number5.getInteger());
}

TEST(AlbaNumberTest, GetFractionDataWorksAsExpected)
{
    AlbaNumber number1;
    AlbaNumber number2(-81237);
    AlbaNumber number3(34095093u);
    AlbaNumber number4(-87408, -9802);
    AlbaNumber number5(4564.38794);

    AlbaNumber::FractionData fractionData1(number1.getFractionData());
    EXPECT_EQ(0, fractionData1.numerator);
    EXPECT_EQ(1u, fractionData1.denominator);
    AlbaNumber::FractionData fractionData2(number2.getFractionData());
    EXPECT_EQ(-81237, fractionData2.numerator);
    EXPECT_EQ(1u, fractionData2.denominator);
    AlbaNumber::FractionData fractionData3(number3.getFractionData());
    EXPECT_EQ(34095093, fractionData3.numerator);
    EXPECT_EQ(1u, fractionData3.denominator);
    AlbaNumber::FractionData fractionData4(number4.getFractionData());
    EXPECT_EQ(43704, fractionData4.numerator);
    EXPECT_EQ(4901u, fractionData4.denominator);
    AlbaNumber::FractionData fractionData5(number5.getFractionData());
    EXPECT_EQ(228219397, fractionData5.numerator);
    EXPECT_EQ(50000u, fractionData5.denominator);
}

TEST(AlbaNumberTest, GetDoubleWorksAsExpected)
{
    AlbaNumber number1;
    AlbaNumber number2(-81237);
    AlbaNumber number3(34095093u);
    AlbaNumber number4(-87408, -9802);
    AlbaNumber number5(4564.38794);

    EXPECT_DOUBLE_EQ(0, number1.getDouble());
    EXPECT_DOUBLE_EQ(-81237, number2.getDouble());
    EXPECT_DOUBLE_EQ(34095093, number3.getDouble());
    EXPECT_DOUBLE_EQ(8.9173638033054488, number4.getDouble());
    EXPECT_DOUBLE_EQ(4564.38794, number5.getDouble());
}

TEST(AlbaNumberTest, EqualityWorksAsExpected)
{
    AlbaNumber number1;
    AlbaNumber number2(-81237);
    AlbaNumber number3(-81237);
    AlbaNumber number4(static_cast<double>(1)/3);
    AlbaNumber number5(1, 3);
    AlbaNumber number6(AlbaNumber::Value::PositiveInfinity);
    AlbaNumber number7(AlbaNumber::Value::NegativeInfinity);

    EXPECT_TRUE(number1==number1);
    EXPECT_TRUE(number2==number2);
    EXPECT_TRUE(number3==number3);
    EXPECT_TRUE(number4==number4);
    EXPECT_TRUE(number5==number5);
    EXPECT_FALSE(number1==number2);
    EXPECT_TRUE(number2==number3);
    EXPECT_FALSE(number3==number4);
    EXPECT_TRUE(number4==number5);
    EXPECT_FALSE(number5==number6);
    EXPECT_TRUE(number6==number6);
    EXPECT_FALSE(number5==number7);
    EXPECT_TRUE(number7==number7);
    EXPECT_FALSE(number6==number7);
}

TEST(AlbaNumberTest, InequalityWorksAsExpected)
{
    AlbaNumber number1;
    AlbaNumber number2(-81237);
    AlbaNumber number3(-81237);
    AlbaNumber number4(static_cast<double>(1)/3);
    AlbaNumber number5(1, 3);

    EXPECT_FALSE(number1!=number1);
    EXPECT_FALSE(number2!=number2);
    EXPECT_FALSE(number3!=number3);
    EXPECT_FALSE(number4!=number4);
    EXPECT_FALSE(number5!=number5);
    EXPECT_TRUE(number1!=number2);
    EXPECT_FALSE(number2!=number3);
    EXPECT_TRUE(number3!=number4);
    EXPECT_FALSE(number4!=number5);
}

TEST(AlbaNumberTest, LessThanWorksAsExpected)
{
    AlbaNumber number1;
    AlbaNumber number2(1, 3);
    AlbaNumber number3(0.5);
    AlbaNumber number4(AlbaNumber::Value::PositiveInfinity);
    AlbaNumber number5(AlbaNumber::Value::NegativeInfinity);

    EXPECT_FALSE(number1<number1);
    EXPECT_FALSE(number2<number2);
    EXPECT_FALSE(number3<number3);
    EXPECT_TRUE(number1<number2);
    EXPECT_TRUE(number2<number3);
    EXPECT_FALSE(number2<number1);
    EXPECT_FALSE(number3<number2);
    EXPECT_TRUE(number3<number4);
    EXPECT_FALSE(number4<number4);
    EXPECT_FALSE(number3<number5);
    EXPECT_FALSE(number5<number5);
    EXPECT_FALSE(number4<number5);
}

TEST(AlbaNumberTest, LessThanOrEqualWorksAsExpected)
{
    AlbaNumber number1;
    AlbaNumber number2(1, 3);
    AlbaNumber number3(0.5);
    AlbaNumber number4(AlbaNumber::Value::PositiveInfinity);
    AlbaNumber number5(AlbaNumber::Value::NegativeInfinity);

    EXPECT_TRUE(number1<=number1);
    EXPECT_TRUE(number2<=number2);
    EXPECT_TRUE(number3<=number3);
    EXPECT_TRUE(number1<=number2);
    EXPECT_TRUE(number2<=number3);
    EXPECT_FALSE(number2<=number1);
    EXPECT_FALSE(number3<=number2);
    EXPECT_TRUE(number3<=number4);
    EXPECT_TRUE(number4<=number4);
    EXPECT_FALSE(number3<=number5);
    EXPECT_TRUE(number5<=number5);
    EXPECT_FALSE(number4<=number5);
}

TEST(AlbaNumberTest, GreaterThanWorksAsExpected)
{
    AlbaNumber number1;
    AlbaNumber number2(1, 3);
    AlbaNumber number3(0.5);
    AlbaNumber number4(AlbaNumber::Value::PositiveInfinity);
    AlbaNumber number5(AlbaNumber::Value::NegativeInfinity);

    EXPECT_FALSE(number1>number1);
    EXPECT_FALSE(number2>number2);
    EXPECT_FALSE(number3>number3);
    EXPECT_FALSE(number1>number2);
    EXPECT_FALSE(number2>number3);
    EXPECT_TRUE(number2>number1);
    EXPECT_TRUE(number3>number2);
    EXPECT_FALSE(number3>number4);
    EXPECT_FALSE(number4>number4);
    EXPECT_TRUE(number3>number5);
    EXPECT_FALSE(number5>number5);
    EXPECT_TRUE(number4>number5);
}

TEST(AlbaNumberTest, GreaterThanOrEqualWorksAsExpected)
{
    AlbaNumber number1;
    AlbaNumber number2(1, 3);
    AlbaNumber number3(0.5);
    AlbaNumber number4(AlbaNumber::Value::PositiveInfinity);
    AlbaNumber number5(AlbaNumber::Value::NegativeInfinity);

    EXPECT_TRUE(number1>=number1);
    EXPECT_TRUE(number2>=number2);
    EXPECT_TRUE(number3>=number3);
    EXPECT_FALSE(number1>=number2);
    EXPECT_FALSE(number2>=number3);
    EXPECT_TRUE(number2>=number1);
    EXPECT_TRUE(number3>=number2);
    EXPECT_FALSE(number3>=number4);
    EXPECT_TRUE(number4>=number4);
    EXPECT_TRUE(number3>=number5);
    EXPECT_TRUE(number5>=number5);
    EXPECT_TRUE(number4>=number5);
}

TEST(AlbaNumberTest, UnaryPlusWorksOnDifferentTypes)
{
    AlbaNumber number1 = +AlbaNumber();
    AlbaNumber number2 = +AlbaNumber(-81237);
    AlbaNumber number3 = +AlbaNumber(34095093u);
    AlbaNumber number4 = +AlbaNumber(-87408, -9802);
    AlbaNumber number5 = +AlbaNumber(4564.38794);

    EXPECT_EQ(AlbaNumber::Type::Integer, number1.getType());
    EXPECT_EQ(0, number1.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number2.getType());
    EXPECT_EQ(-81237, number2.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number3.getType());
    EXPECT_EQ(34095093, number3.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Fraction, number4.getType());
    AlbaNumber::FractionData fractionData(number4.getFractionData());
    EXPECT_EQ(43704, fractionData.numerator);
    EXPECT_EQ(4901u, fractionData.denominator);
    EXPECT_EQ(AlbaNumber::Type::Double, number5.getType());
    EXPECT_DOUBLE_EQ(4564.38794, number5.getDouble());
}

TEST(AlbaNumberTest, UnaryMinusWorksOnDifferentTypes)
{
    AlbaNumber number1 = -AlbaNumber();
    AlbaNumber number2 = -AlbaNumber(-81237);
    AlbaNumber number3 = -AlbaNumber(34095093u);
    AlbaNumber number4 = -AlbaNumber(-87408, -9802);
    AlbaNumber number5 = -AlbaNumber(4564.38794);

    EXPECT_EQ(AlbaNumber::Type::Integer, number1.getType());
    EXPECT_EQ(0, number1.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number2.getType());
    EXPECT_EQ(81237, number2.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number3.getType());
    EXPECT_EQ(-34095093, number3.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Fraction, number4.getType());
    AlbaNumber::FractionData fractionData(number4.getFractionData());
    EXPECT_EQ(-43704, fractionData.numerator);
    EXPECT_EQ(4901u, fractionData.denominator);
    EXPECT_EQ(AlbaNumber::Type::Double, number5.getType());
    EXPECT_DOUBLE_EQ(-4564.38794, number5.getDouble());
}

TEST(AlbaNumberTest, AdditionWorksOnTypesStartingFromInteger)
{
    AlbaNumber number1 = AlbaNumber() + AlbaNumber();
    AlbaNumber number2 = AlbaNumber(100) + 10;
    AlbaNumber number3 = AlbaNumber(100) + AlbaNumber(10, 3);
    AlbaNumber number4 = AlbaNumber(100) + 23.24897;
    AlbaNumber number5 = AlbaNumber(1234567891) + AlbaNumber(1234567891);
    AlbaNumber number6 = AlbaNumber(9223372036854775807) + AlbaNumber(9223372036854775807);

    EXPECT_EQ(AlbaNumber::Type::Integer, number1.getType());
    EXPECT_EQ(0, number1.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number2.getType());
    EXPECT_EQ(110, number2.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Fraction, number3.getType());
    AlbaNumber::FractionData fractionData(number3.getFractionData());
    EXPECT_EQ(310, fractionData.numerator);
    EXPECT_EQ(3u, fractionData.denominator);
    EXPECT_EQ(AlbaNumber::Type::Double, number4.getType());
    EXPECT_DOUBLE_EQ(123.24897, number4.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Integer, number5.getType());
    EXPECT_EQ(2469135782, number5.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Double, number6.getType());
    EXPECT_DOUBLE_EQ(1.8446744073709552e+019, number6.getDouble());
}

TEST(AlbaNumberTest, AdditionWorksOnTypesStartingFromFraction)
{
    AlbaNumber number1 = AlbaNumber(0, 1) + AlbaNumber(0, 1);
    AlbaNumber number2 = AlbaNumber(100, 6) + 5;
    AlbaNumber number3 = AlbaNumber(100, 6) + AlbaNumber(10, 7);
    AlbaNumber number4 = AlbaNumber(100, 6) + AlbaNumber(10, 3);
    AlbaNumber number5 = AlbaNumber(100, 6) + 23.24897;
    AlbaNumber number6 = AlbaNumber(1234567890, 1234567891) + AlbaNumber(1234567891);
    AlbaNumber number7 = AlbaNumber(1234567891) + AlbaNumber(1234567890, 1234567891);
    AlbaNumber number8 = AlbaNumber(1234567890, 1234567891) + AlbaNumber(1234567890, 1234567893);

    EXPECT_EQ(AlbaNumber::Type::Integer, number1.getType());
    EXPECT_EQ(0, number1.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Fraction, number2.getType());
    AlbaNumber::FractionData fractionData2(number2.getFractionData());
    EXPECT_EQ(65, fractionData2.numerator);
    EXPECT_EQ(3u, fractionData2.denominator);
    EXPECT_EQ(AlbaNumber::Type::Fraction, number3.getType());
    AlbaNumber::FractionData fractionData3(number3.getFractionData());
    EXPECT_EQ(380, fractionData3.numerator);
    EXPECT_EQ(21u, fractionData3.denominator);
    EXPECT_EQ(AlbaNumber::Type::Integer, number4.getType());
    EXPECT_EQ(20, number4.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Double, number5.getType());
    EXPECT_DOUBLE_EQ(39.915636666666664, number5.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Integer, number6.getType());
    EXPECT_DOUBLE_EQ(1234567892, number6.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number7.getType());
    EXPECT_DOUBLE_EQ(1234567892, number7.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Double, number8.getType());
    EXPECT_DOUBLE_EQ(1.9999999967600002, number8.getDouble());
}

TEST(AlbaNumberTest, AdditionWorksOnTypesStartingFromDouble)
{
    AlbaNumber number1 = AlbaNumber(0.1) + AlbaNumber(0);
    AlbaNumber number2 = AlbaNumber(10.5) + 5;
    AlbaNumber number3 = AlbaNumber(10.5) + AlbaNumber(10, 7);
    AlbaNumber number4 = AlbaNumber(10.5) + 23.24897;
    AlbaNumber number5 = AlbaNumber(1234567891.1) + AlbaNumber(1234567891);

    EXPECT_EQ(AlbaNumber::Type::Double, number1.getType());
    EXPECT_DOUBLE_EQ(0.1, number1.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number2.getType());
    EXPECT_DOUBLE_EQ(15.5, number2.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number3.getType());
    EXPECT_DOUBLE_EQ(11.928571428571429, number3.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number4.getType());
    EXPECT_DOUBLE_EQ(33.74897, number4.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number5.getType());
    EXPECT_DOUBLE_EQ(2469135782.0999999, number5.getDouble());
}

TEST(AlbaNumberTest, SubtractionWorksOnTypesStartingFromInteger)
{
    AlbaNumber number1 = AlbaNumber() - AlbaNumber();
    AlbaNumber number2 = AlbaNumber(100) - 10;
    AlbaNumber number3 = AlbaNumber(100) - AlbaNumber(10, 3);
    AlbaNumber number4 = AlbaNumber(100) - 23.24897;
    AlbaNumber number5 = AlbaNumber(1234567891) - AlbaNumber(1234567891);
    AlbaNumber number6 = AlbaNumber(9223372036854775807) - AlbaNumber(9223372036854775807);

    EXPECT_EQ(AlbaNumber::Type::Integer, number1.getType());
    EXPECT_EQ(0, number1.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number2.getType());
    EXPECT_EQ(90, number2.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Fraction, number3.getType());
    AlbaNumber::FractionData fractionData(number3.getFractionData());
    EXPECT_EQ(290, fractionData.numerator);
    EXPECT_EQ(3u, fractionData.denominator);
    EXPECT_EQ(AlbaNumber::Type::Double, number4.getType());
    EXPECT_DOUBLE_EQ(76.75103, number4.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Integer, number5.getType());
    EXPECT_EQ(0, number5.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number6.getType());
    EXPECT_EQ(0, number6.getInteger());
}

TEST(AlbaNumberTest, SubtractionWorksOnTypesStartingFromFraction)
{
    AlbaNumber number1 = AlbaNumber(0, 1) - AlbaNumber(0, 1);
    AlbaNumber number2 = AlbaNumber(100, 6) - 5;
    AlbaNumber number3 = AlbaNumber(100, 6) - AlbaNumber(10, 7);
    AlbaNumber number4 = AlbaNumber(100, 6) - AlbaNumber(10, 3);
    AlbaNumber number5 = AlbaNumber(100, 6) - 23.24897;
    AlbaNumber number6 = AlbaNumber(1234567890, 1234567891) - AlbaNumber(1234567891);
    AlbaNumber number7 = AlbaNumber(1234567891) - AlbaNumber(1234567890, 1234567891);
    AlbaNumber number8 = AlbaNumber(1234567890, 1234567891) - AlbaNumber(1234567890, 1234567893);
    AlbaNumber number9 = AlbaNumber(169, 65536) - AlbaNumber(1, 262144);

    EXPECT_EQ(AlbaNumber::Type::Integer, number1.getType());
    EXPECT_EQ(0, number1.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Fraction, number2.getType());
    AlbaNumber::FractionData fractionData2(number2.getFractionData());
    EXPECT_EQ(35, fractionData2.numerator);
    EXPECT_EQ(3u, fractionData2.denominator);
    EXPECT_EQ(AlbaNumber::Type::Fraction, number3.getType());
    AlbaNumber::FractionData fractionData3(number3.getFractionData());
    EXPECT_EQ(320, fractionData3.numerator);
    EXPECT_EQ(21u, fractionData3.denominator);
    EXPECT_EQ(AlbaNumber::Type::Fraction, number4.getType());
    AlbaNumber::FractionData fractionData4(number4.getFractionData());
    EXPECT_EQ(40, fractionData4.numerator);
    EXPECT_EQ(3u, fractionData4.denominator);
    EXPECT_EQ(AlbaNumber::Type::Double, number5.getType());
    EXPECT_DOUBLE_EQ(-6.582303333333333, number5.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Integer, number6.getType());
    EXPECT_DOUBLE_EQ(-1234567890, number6.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number7.getType());
    EXPECT_DOUBLE_EQ(1234567890, number7.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Double, number8.getType());
    EXPECT_DOUBLE_EQ(1.6200000230170986e-009, number8.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Fraction, number9.getType());
    AlbaNumber::FractionData fractionData9(number9.getFractionData());
    EXPECT_EQ(675, fractionData9.numerator);
    EXPECT_EQ(262144u, fractionData9.denominator);
}

TEST(AlbaNumberTest, SubtractionWorksOnTypesStartingFromDouble)
{
    AlbaNumber number1 = AlbaNumber(0.1) - AlbaNumber(0);
    AlbaNumber number2 = AlbaNumber(10.5) - 5;
    AlbaNumber number3 = AlbaNumber(10.5) - AlbaNumber(10, 7);
    AlbaNumber number4 = AlbaNumber(10.5) - 23.24897;
    AlbaNumber number5 = AlbaNumber(1234567891.1) - AlbaNumber(1234567891);

    EXPECT_EQ(AlbaNumber::Type::Double, number1.getType());
    EXPECT_DOUBLE_EQ(0.1, number1.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number2.getType());
    EXPECT_DOUBLE_EQ(5.5, number2.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number3.getType());
    EXPECT_DOUBLE_EQ(9.0714285714285712, number3.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number4.getType());
    EXPECT_DOUBLE_EQ(-12.74897, number4.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number5.getType());
    EXPECT_DOUBLE_EQ(0.099999904632568359, number5.getDouble());
}

TEST(AlbaNumberTest, MultiplyWorksOnTypesStartingFromInteger)
{
    AlbaNumber number1 = AlbaNumber() * AlbaNumber();
    AlbaNumber number2 = AlbaNumber(100) * 10;
    AlbaNumber number3 = AlbaNumber(100) * AlbaNumber(10, 3);
    AlbaNumber number4 = AlbaNumber(100) * 23.24897;
    AlbaNumber number5 = AlbaNumber(1234567891) * AlbaNumber(1234567891);
    AlbaNumber number6 = AlbaNumber(9223372036854775807) * AlbaNumber(9223372036854775807);

    EXPECT_EQ(AlbaNumber::Type::Integer, number1.getType());
    EXPECT_EQ(0, number1.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number2.getType());
    EXPECT_EQ(1000, number2.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Fraction, number3.getType());
    AlbaNumber::FractionData fractionData(number3.getFractionData());
    EXPECT_EQ(1000, fractionData.numerator);
    EXPECT_EQ(3u, fractionData.denominator);
    EXPECT_EQ(AlbaNumber::Type::Double, number4.getType());
    EXPECT_DOUBLE_EQ(2324.8969999999999, number4.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Integer, number5.getType());
    EXPECT_EQ(1524157877488187881, number5.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Double, number6.getType());
    EXPECT_DOUBLE_EQ(8.5070591730234616e+037, number6.getDouble());
}

TEST(AlbaNumberTest, MultiplyWorksOnTypesStartingFromFraction)
{
    AlbaNumber number1 = AlbaNumber(0, 1) * AlbaNumber(0, 1);
    AlbaNumber number2 = AlbaNumber(100, 6) * 5;
    AlbaNumber number3 = AlbaNumber(100, 6) * AlbaNumber(10, 7);
    AlbaNumber number4 = AlbaNumber(100, 6) * 23.24897;
    AlbaNumber number5 = AlbaNumber(-2005875, -79507) * AlbaNumber(-688, -27);
    AlbaNumber number6 = AlbaNumber(1234567890, 1234567891) * AlbaNumber(1234567891);
    AlbaNumber number7 = AlbaNumber(1234567891) * AlbaNumber(1234567890, 1234567891);
    AlbaNumber number8 = AlbaNumber(1234567890, 1234567891) * AlbaNumber(1234567890, 1234567893);

    EXPECT_EQ(AlbaNumber::Type::Integer, number1.getType());
    EXPECT_EQ(0, number1.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Fraction, number2.getType());
    AlbaNumber::FractionData fractionData2(number2.getFractionData());
    EXPECT_EQ(250, fractionData2.numerator);
    EXPECT_EQ(3u, fractionData2.denominator);
    EXPECT_EQ(AlbaNumber::Type::Fraction, number3.getType());
    AlbaNumber::FractionData fractionData3(number3.getFractionData());
    EXPECT_EQ(500, fractionData3.numerator);
    EXPECT_EQ(21u, fractionData3.denominator);
    EXPECT_EQ(AlbaNumber::Type::Double, number4.getType());
    EXPECT_DOUBLE_EQ(387.48283333333336, number4.getDouble());
    AlbaNumber::FractionData fractionData5(number5.getFractionData());
    EXPECT_EQ(3566000, fractionData5.numerator);
    EXPECT_EQ(5547u, fractionData5.denominator);
    EXPECT_EQ(AlbaNumber::Type::Integer, number6.getType());
    EXPECT_DOUBLE_EQ(1234567890, number6.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number7.getType());
    EXPECT_DOUBLE_EQ(1234567890, number7.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Double, number8.getType());
    EXPECT_DOUBLE_EQ(0.99999999676000006, number8.getDouble());
}

TEST(AlbaNumberTest, MultiplyWorksOnTypesStartingFromDouble)
{
    AlbaNumber number1 = AlbaNumber(0.1) * AlbaNumber(0);
    AlbaNumber number2 = AlbaNumber(10.5) * 5;
    AlbaNumber number3 = AlbaNumber(10.5) * AlbaNumber(10, 7);
    AlbaNumber number4 = AlbaNumber(10.5) * 23.24897;
    AlbaNumber number5 = AlbaNumber(1234567891.1) * AlbaNumber(1234567891);
    AlbaNumber number6 = AlbaNumber(-5878) * AlbaNumber(16769025);

    EXPECT_EQ(AlbaNumber::Type::Integer, number1.getType());
    EXPECT_EQ(0, number1.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Double, number2.getType());
    EXPECT_DOUBLE_EQ(52.5, number2.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Integer, number3.getType());
    EXPECT_EQ(15, number3.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Double, number4.getType());
    EXPECT_DOUBLE_EQ(244.11418499999999, number4.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Integer, number5.getType());
    EXPECT_EQ(1524157877611644672, number5.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number6.getType());
    EXPECT_EQ(-98568328950, number6.getInteger());
}

TEST(AlbaNumberTest, DivideWorksOnTypesStartingFromInteger)
{
    AlbaNumber number1 = AlbaNumber() / AlbaNumber(1);
    AlbaNumber number2 = AlbaNumber(100) / 10;
    AlbaNumber number3 = AlbaNumber(100) / AlbaNumber(11, 3);
    AlbaNumber number4 = AlbaNumber(100) / 23.24897;
    AlbaNumber number5 = AlbaNumber(1234567893) / AlbaNumber(1234567891);
    AlbaNumber number6 = AlbaNumber(-40)/AlbaNumber(800);
    AlbaNumber number7 = AlbaNumber(9223372036854775807) / AlbaNumber(9223372036854775807);

    EXPECT_EQ(AlbaNumber::Type::Integer, number1.getType());
    EXPECT_EQ(0, number1.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number2.getType());
    EXPECT_EQ(10, number2.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Fraction, number3.getType());
    AlbaNumber::FractionData fractionData(number3.getFractionData());
    EXPECT_EQ(300, fractionData.numerator);
    EXPECT_EQ(11u, fractionData.denominator);
    EXPECT_EQ(AlbaNumber::Type::Double, number4.getType());
    EXPECT_DOUBLE_EQ(4.3012658195180258, number4.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Fraction, number5.getType());
    AlbaNumber::FractionData fractionData1(number5.getFractionData());
    EXPECT_EQ(1234567893, fractionData1.numerator);
    EXPECT_EQ(1234567891u, fractionData1.denominator);
    AlbaNumber::FractionData fractionData2(number6.getFractionData());
    EXPECT_EQ(-1, fractionData2.numerator);
    EXPECT_EQ(20u, fractionData2.denominator);
    EXPECT_EQ(AlbaNumber::Type::Integer, number7.getType());
    EXPECT_EQ(1, number7.getInteger());
}

TEST(AlbaNumberTest, DivideWorksOnTypesStartingFromFraction)
{
    AlbaNumber number1 = AlbaNumber(0, 1) / AlbaNumber(1, 1);
    AlbaNumber number2 = AlbaNumber(100, 6) / 5;
    AlbaNumber number3 = AlbaNumber(100, 6) / AlbaNumber(10, 7);
    AlbaNumber number4 = AlbaNumber(100, 6) / 23.24897;
    AlbaNumber number5 = AlbaNumber(-946400, -2146689) / AlbaNumber(-3566000, -5547);
    AlbaNumber number6 = AlbaNumber(1234567890, 1234567891) / AlbaNumber(1234567891);
    AlbaNumber number7 = AlbaNumber(1234567891) / AlbaNumber(1234567890, 1234567893);
    AlbaNumber number8 = AlbaNumber(1234567890, 1234567891) / AlbaNumber(1234567890, 1234567893);

    EXPECT_EQ(AlbaNumber::Type::Integer, number1.getType());
    EXPECT_EQ(0, number1.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Fraction, number2.getType());
    AlbaNumber::FractionData fractionData2(number2.getFractionData());
    EXPECT_EQ(10, fractionData2.numerator);
    EXPECT_EQ(3u, fractionData2.denominator);
    EXPECT_EQ(AlbaNumber::Type::Fraction, number3.getType());
    AlbaNumber::FractionData fractionData3(number3.getFractionData());
    EXPECT_EQ(35, fractionData3.numerator);
    EXPECT_EQ(3u, fractionData3.denominator);
    EXPECT_EQ(AlbaNumber::Type::Double, number4.getType());
    EXPECT_DOUBLE_EQ(0.71687763658633763, number4.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number5.getType());
    EXPECT_DOUBLE_EQ(0.00068577622999879705, number5.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number6.getType());
    EXPECT_DOUBLE_EQ(8.1000000605880009e-010, number6.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Integer, number7.getType());
    EXPECT_DOUBLE_EQ(1234567894, number7.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Double, number8.getType());
    EXPECT_DOUBLE_EQ(1.0000000016200001, number8.getDouble());
}

TEST(AlbaNumberTest, DivideWorksOnTypesStartingFromDouble)
{
    AlbaNumber number1 = AlbaNumber(0.1) / AlbaNumber(1);
    AlbaNumber number2 = AlbaNumber(10.5) / 5;
    AlbaNumber number3 = AlbaNumber(10.5) / AlbaNumber(10, 7);
    AlbaNumber number4 = AlbaNumber(10.5) / 23.24897;
    AlbaNumber number5 = AlbaNumber(1234567891.1) / AlbaNumber(1234567891);

    EXPECT_EQ(AlbaNumber::Type::Double, number1.getType());
    EXPECT_DOUBLE_EQ(0.10000000000000001, number1.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number2.getType());
    EXPECT_DOUBLE_EQ(2.1000000000000001, number2.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number3.getType());
    EXPECT_DOUBLE_EQ(7.3499999999999996, number3.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number4.getType());
    EXPECT_DOUBLE_EQ(0.45163291104939274, number4.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number5.getType());
    EXPECT_DOUBLE_EQ(1.0000000000809999, number5.getDouble());
}

TEST(AlbaNumberTest, RaisePowerWorksOnTypesStartingFromInteger)
{
    AlbaNumber number1 = AlbaNumber() ^ AlbaNumber(1);
    AlbaNumber number2 = AlbaNumber(-10) ^ 5;
    AlbaNumber number3 = AlbaNumber(10) ^ AlbaNumber(11, 3);
    AlbaNumber number4 = AlbaNumber(10) ^ 2.324897;
    AlbaNumber number5 = AlbaNumber(1234567891) ^ AlbaNumber(3);
    AlbaNumber number6 = AlbaNumber(9223372036854775807) ^ AlbaNumber(5);
    AlbaNumber number7 = AlbaNumber(-256) ^ AlbaNumber(-256);

    EXPECT_EQ(AlbaNumber::Type::Integer, number1.getType());
    EXPECT_EQ(0, number1.getInteger());    EXPECT_EQ(AlbaNumber::Type::Integer, number2.getType());
    EXPECT_EQ(-100000, number2.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Double, number3.getType());
    EXPECT_DOUBLE_EQ(4641.5888336127773, number3.getDouble());    EXPECT_EQ(AlbaNumber::Type::Double, number4.getType());
    EXPECT_DOUBLE_EQ(211.29878509707362, number4.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number5.getType());
    EXPECT_DOUBLE_EQ(1.8816763763616284e+027, number5.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number6.getType());
    EXPECT_DOUBLE_EQ(6.674959487252844e+094, number6.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Integer, number7.getType());
    EXPECT_DOUBLE_EQ(0, number7.getDouble());
}

TEST(AlbaNumberTest, RaisePowerWorksOnTypesStartingFromFraction){
    AlbaNumber number1 = AlbaNumber(0, 1) ^ AlbaNumber(1, 1);
    AlbaNumber number2 = AlbaNumber(10, 6) ^ 5;
    AlbaNumber number3 = AlbaNumber(10, 6) ^ AlbaNumber(10, 7);    AlbaNumber number4 = AlbaNumber(10, 6) ^ 2.324897;
    AlbaNumber number5 = AlbaNumber(12345, 12346) ^ AlbaNumber(1234);
    AlbaNumber number6 = AlbaNumber(1234567890, 1234567891) ^ AlbaNumber(3);
    AlbaNumber number7 = AlbaNumber(1234567891) ^ AlbaNumber(1234567890, 1234567891);
    AlbaNumber number8 = AlbaNumber(1234567890, 1234567891) ^ AlbaNumber(1234567890, 1234567893);

    EXPECT_EQ(AlbaNumber::Type::Integer, number1.getType());
    EXPECT_EQ(0, number1.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Fraction, number2.getType());
    AlbaNumber::FractionData fractionData2(number2.getFractionData());
    EXPECT_EQ(3125, fractionData2.numerator);
    EXPECT_EQ(243u, fractionData2.denominator);
    EXPECT_EQ(AlbaNumber::Type::Double, number3.getType());
    EXPECT_DOUBLE_EQ(2.0745637509941224, number3.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number4.getType());
    EXPECT_DOUBLE_EQ(3.2792572881529063, number4.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number5.getType());
    EXPECT_DOUBLE_EQ(0.90487772997589355, number5.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number6.getType());
    EXPECT_DOUBLE_EQ(0.99999999757000013, number6.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number7.getType());
    EXPECT_DOUBLE_EQ(1234567870.0660145, number7.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number8.getType());
    EXPECT_DOUBLE_EQ(0.99999999919000004, number8.getDouble());
}

TEST(AlbaNumberTest, RaisePowerWorksOnTypesStartingFromDouble)
{
    AlbaNumber number1 = AlbaNumber(0.1) ^ AlbaNumber(1);
    AlbaNumber number2 = AlbaNumber(10.5) ^ 5;
    AlbaNumber number3 = AlbaNumber(10.5) ^ AlbaNumber(10, 7);
    AlbaNumber number4 = AlbaNumber(10.5) ^ 2.324897;
    AlbaNumber number5 = AlbaNumber(1234567891.1) ^ AlbaNumber(3);
    AlbaNumber number6 = AlbaNumber(256.000001) ^ AlbaNumber(256.000001);
    AlbaNumber number7 = AlbaNumber(-256.000001) ^ AlbaNumber(-256.000001);

    EXPECT_EQ(AlbaNumber::Type::Double, number1.getType());
    EXPECT_DOUBLE_EQ(0.10000000000000001, number1.getDouble());    EXPECT_EQ(AlbaNumber::Type::Double, number2.getType());
    EXPECT_DOUBLE_EQ(127628.15625, number2.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number3.getType());
    EXPECT_DOUBLE_EQ(28.763508283430014, number3.getDouble());    EXPECT_EQ(AlbaNumber::Type::Double, number4.getType());
    EXPECT_DOUBLE_EQ(236.67911563383956, number4.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number5.getType());
    EXPECT_DOUBLE_EQ(1.8816763768188754e+027, number5.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number6.getType());
    EXPECT_TRUE(number6.isPositiveInfinity());
    EXPECT_EQ(AlbaNumber::Type::Double, number7.getType());
    EXPECT_TRUE(number7.isNotANumber());
}

TEST(AlbaNumberTest, GetDisplayableStringWorks){
    AlbaNumber number1;
    AlbaNumber number2(3484);
    AlbaNumber number3(-1561);    AlbaNumber number4(-415, 41745);
    AlbaNumber number5(-85.45631);

    EXPECT_EQ("0", number1.getDisplayableString());
    EXPECT_EQ("3484", number2.getDisplayableString());
    EXPECT_EQ("-1561", number3.getDisplayableString());
    EXPECT_EQ("(-83/8349)", number4.getDisplayableString());
    EXPECT_EQ("-85.45631", number5.getDisplayableString());
}

TEST(AlbaNumberTest, ConvertToIntegerWorks)
{
    AlbaNumber number1(-1561);
    AlbaNumber number2(-415, 41);
    AlbaNumber number3(-3, 2);
    AlbaNumber number4(-85.25);
    AlbaNumber number5(-2.99999821186066);

    number1.convertToInteger();
    number2.convertToInteger();
    number3.convertToInteger();
    number4.convertToInteger();
    number5.convertToInteger();

    EXPECT_EQ(AlbaNumber::Type::Integer, number1.getType());
    EXPECT_EQ(-1561, number1.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number2.getType());
    EXPECT_EQ(-10, number2.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number3.getType());
    EXPECT_EQ(-2, number3.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number4.getType());
    EXPECT_EQ(-85, number4.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number5.getType());
    EXPECT_EQ(-3, number5.getInteger());
}

TEST(AlbaNumberTest, ConvertToFractionWorks)
{
    AlbaNumber number1(-1561);
    AlbaNumber number2(-415, 41);
    AlbaNumber number3(-85.25);

    number1.convertToFraction();
    number2.convertToFraction();
    number3.convertToFraction();

    EXPECT_EQ(AlbaNumber::Type::Integer, number1.getType());
    EXPECT_EQ(-1561, number1.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Fraction, number2.getType());
    AlbaNumber::FractionData fractionData2(number2.getFractionData());
    EXPECT_EQ(-415, fractionData2.numerator);
    EXPECT_EQ(41u, fractionData2.denominator);
    EXPECT_EQ(AlbaNumber::Type::Fraction, number3.getType());
    AlbaNumber::FractionData fractionData3(number3.getFractionData());
    EXPECT_EQ(-341, fractionData3.numerator);
    EXPECT_EQ(4u, fractionData3.denominator);
}

TEST(AlbaNumberTest, DivisionOfAValueByZeroWorksAsExpected)
{
    AlbaNumber number1(5);
    AlbaNumber number2(5, 0);
    AlbaNumber number3(1.25);

    number1 = number1/0;
    number3 = number3/0;
    EXPECT_EQ(AlbaNumber::Type::Double, number1.getType());
    EXPECT_DOUBLE_EQ(INFINITY, number1.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number2.getType());
    EXPECT_DOUBLE_EQ(INFINITY, number2.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number3.getType());
    EXPECT_DOUBLE_EQ(INFINITY, number3.getDouble());
}

TEST(AlbaNumberTest, DivisionOfZeroByZeroWorksAsExpected)
{
    AlbaNumber number1(0);
    AlbaNumber number2(0, 0);
    AlbaNumber number3(static_cast<double>(0));

    number1 = number1/0;
    number3 = number3/0;
    EXPECT_EQ(AlbaNumber::Type::Double, number1.getType());
    EXPECT_TRUE(isnan(number1.getDouble()));
    EXPECT_EQ(AlbaNumber::Type::Double, number2.getType());
    EXPECT_TRUE(isnan(number2.getDouble()));
    EXPECT_EQ(AlbaNumber::Type::Double, number3.getType());
    EXPECT_TRUE(isnan(number3.getDouble()));
}

TEST(AlbaNumberTest, SquareRootOfNegativeNumberWorksAsExpected)
{
    AlbaNumber base(-5);
    AlbaNumber exponent(1, 2);

    AlbaNumber numberToVerify = base^exponent;

    EXPECT_EQ(AlbaNumber::Type::Double, numberToVerify.getType());
    EXPECT_TRUE(isnan(numberToVerify.getDouble()));
}

}
