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
    AlbaNumber number5(-100, 10);
    AlbaNumber number6(4564.38794);

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
    EXPECT_EQ(AlbaNumber::Type::Integer, number5.getType());
    EXPECT_EQ(-10, number5.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Double, number6.getType());
    EXPECT_DOUBLE_EQ(4564.38794, number6.getDouble());
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
    EXPECT_EQ(8, number4.getInteger());
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
    EXPECT_EQ(1, fractionData1.denominator);
    AlbaNumber::FractionData fractionData2(number2.getFractionData());
    EXPECT_EQ(-81237, fractionData2.numerator);
    EXPECT_EQ(1, fractionData2.denominator);
    AlbaNumber::FractionData fractionData3(number3.getFractionData());
    EXPECT_EQ(34095093, fractionData3.numerator);
    EXPECT_EQ(1, fractionData3.denominator);
    AlbaNumber::FractionData fractionData4(number4.getFractionData());
    EXPECT_EQ(43704, fractionData4.numerator);
    EXPECT_EQ(4901, fractionData4.denominator);
    AlbaNumber::FractionData fractionData5(number5.getFractionData());
    EXPECT_EQ(228219397, fractionData5.numerator);
    EXPECT_EQ(50000, fractionData5.denominator);
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
    EXPECT_EQ(4901, fractionData.denominator);
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
    EXPECT_EQ(4901, fractionData.denominator);
    EXPECT_EQ(AlbaNumber::Type::Double, number5.getType());
    EXPECT_DOUBLE_EQ(-4564.38794, number5.getDouble());
}

TEST(AlbaNumberTest, AdditionWorksOnTypesStartingFromInteger)
{
    AlbaNumber number1 = AlbaNumber() + AlbaNumber();
    AlbaNumber number2 = AlbaNumber(100) + 10;
    AlbaNumber number3 = AlbaNumber(100) + AlbaNumber(10, 3);
    AlbaNumber number4 = AlbaNumber(100) + 23.24897;

    EXPECT_EQ(AlbaNumber::Type::Integer, number1.getType());
    EXPECT_EQ(0, number1.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number2.getType());
    EXPECT_EQ(110, number2.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Fraction, number3.getType());
    AlbaNumber::FractionData fractionData(number3.getFractionData());
    EXPECT_EQ(310, fractionData.numerator);
    EXPECT_EQ(3, fractionData.denominator);
    EXPECT_EQ(AlbaNumber::Type::Double, number4.getType());
    EXPECT_DOUBLE_EQ(123.24897, number4.getDouble());
}

TEST(AlbaNumberTest, AdditionWorksOnTypesStartingFromFraction)
{
    AlbaNumber number1 = AlbaNumber(0, 1) + AlbaNumber(0, 1);
    AlbaNumber number2 = AlbaNumber(100, 6) + 5;
    AlbaNumber number3 = AlbaNumber(100, 6) + AlbaNumber(10, 7);
    AlbaNumber number4 = AlbaNumber(100, 6) + AlbaNumber(10, 3);
    AlbaNumber number5 = AlbaNumber(100, 6) + 23.24897;

    EXPECT_EQ(AlbaNumber::Type::Integer, number1.getType());
    EXPECT_EQ(0, number1.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Fraction, number2.getType());
    AlbaNumber::FractionData fractionData2(number2.getFractionData());
    EXPECT_EQ(65, fractionData2.numerator);
    EXPECT_EQ(3, fractionData2.denominator);
    EXPECT_EQ(AlbaNumber::Type::Fraction, number3.getType());
    AlbaNumber::FractionData fractionData3(number3.getFractionData());
    EXPECT_EQ(380, fractionData3.numerator);
    EXPECT_EQ(21, fractionData3.denominator);
    EXPECT_EQ(AlbaNumber::Type::Integer, number4.getType());
    EXPECT_EQ(20, number4.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Double, number5.getType());
    EXPECT_DOUBLE_EQ(39.915636666666664, number5.getDouble());
}

TEST(AlbaNumberTest, AdditionWorksOnTypesStartingFromDouble)
{
    AlbaNumber number1 = AlbaNumber(0.1) + AlbaNumber(0);
    AlbaNumber number2 = AlbaNumber(10.5) + 5;
    AlbaNumber number3 = AlbaNumber(10.5) + AlbaNumber(10, 7);
    AlbaNumber number4 = AlbaNumber(10.5) + 23.24897;

    EXPECT_EQ(AlbaNumber::Type::Double, number1.getType());
    EXPECT_DOUBLE_EQ(0.1, number1.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number2.getType());
    EXPECT_DOUBLE_EQ(15.5, number2.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number3.getType());
    EXPECT_DOUBLE_EQ(11.928571428571429, number3.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number4.getType());
    EXPECT_DOUBLE_EQ(33.74897, number4.getDouble());
}

TEST(AlbaNumberTest, SubtractionWorksOnTypesStartingFromInteger)
{
    AlbaNumber number1 = AlbaNumber() - AlbaNumber();
    AlbaNumber number2 = AlbaNumber(100) - 10;
    AlbaNumber number3 = AlbaNumber(100) - AlbaNumber(10, 3);
    AlbaNumber number4 = AlbaNumber(100) - 23.24897;

    EXPECT_EQ(AlbaNumber::Type::Integer, number1.getType());
    EXPECT_EQ(0, number1.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number2.getType());
    EXPECT_EQ(90, number2.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Fraction, number3.getType());
    AlbaNumber::FractionData fractionData(number3.getFractionData());
    EXPECT_EQ(290, fractionData.numerator);
    EXPECT_EQ(3, fractionData.denominator);
    EXPECT_EQ(AlbaNumber::Type::Double, number4.getType());
    EXPECT_DOUBLE_EQ(76.75103, number4.getDouble());
}

TEST(AlbaNumberTest, SubtractionWorksOnTypesStartingFromFraction)
{
    AlbaNumber number1 = AlbaNumber(0, 1) - AlbaNumber(0, 1);
    AlbaNumber number2 = AlbaNumber(100, 6) - 5;
    AlbaNumber number3 = AlbaNumber(100, 6) - AlbaNumber(10, 7);
    AlbaNumber number4 = AlbaNumber(100, 6) - 23.24897;

    EXPECT_EQ(AlbaNumber::Type::Integer, number1.getType());
    EXPECT_EQ(0, number1.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Fraction, number2.getType());
    AlbaNumber::FractionData fractionData2(number2.getFractionData());
    EXPECT_EQ(35, fractionData2.numerator);
    EXPECT_EQ(3, fractionData2.denominator);
    EXPECT_EQ(AlbaNumber::Type::Fraction, number3.getType());
    AlbaNumber::FractionData fractionData3(number3.getFractionData());
    EXPECT_EQ(320, fractionData3.numerator);
    EXPECT_EQ(21, fractionData3.denominator);
    EXPECT_EQ(AlbaNumber::Type::Double, number4.getType());
    EXPECT_DOUBLE_EQ(-6.582303333333333, number4.getDouble());
}

TEST(AlbaNumberTest, SubtractionWorksOnTypesStartingFromDouble)
{
    AlbaNumber number1 = AlbaNumber(0.1) - AlbaNumber(0);
    AlbaNumber number2 = AlbaNumber(10.5) - 5;
    AlbaNumber number3 = AlbaNumber(10.5) - AlbaNumber(10, 7);
    AlbaNumber number4 = AlbaNumber(10.5) - 23.24897;

    EXPECT_EQ(AlbaNumber::Type::Double, number1.getType());
    EXPECT_DOUBLE_EQ(0.1, number1.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number2.getType());
    EXPECT_DOUBLE_EQ(5.5, number2.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number3.getType());
    EXPECT_DOUBLE_EQ(9.0714285714285712, number3.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number4.getType());
    EXPECT_DOUBLE_EQ(-12.74897, number4.getDouble());
}

TEST(AlbaNumberTest, MultiplyWorksOnTypesStartingFromInteger)
{
    AlbaNumber number1 = AlbaNumber() * AlbaNumber();
    AlbaNumber number2 = AlbaNumber(100) * 10;
    AlbaNumber number3 = AlbaNumber(100) * AlbaNumber(10, 3);
    AlbaNumber number4 = AlbaNumber(100) * 23.24897;

    EXPECT_EQ(AlbaNumber::Type::Integer, number1.getType());
    EXPECT_EQ(0, number1.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number2.getType());
    EXPECT_EQ(1000, number2.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Fraction, number3.getType());
    AlbaNumber::FractionData fractionData(number3.getFractionData());
    EXPECT_EQ(1000, fractionData.numerator);
    EXPECT_EQ(3, fractionData.denominator);
    EXPECT_EQ(AlbaNumber::Type::Double, number4.getType());
    EXPECT_DOUBLE_EQ(2324.8969999999999, number4.getDouble());
}

TEST(AlbaNumberTest, MultiplyWorksOnTypesStartingFromFraction)
{
    AlbaNumber number1 = AlbaNumber(0, 1) * AlbaNumber(0, 1);
    AlbaNumber number2 = AlbaNumber(100, 6) * 5;
    AlbaNumber number3 = AlbaNumber(100, 6) * AlbaNumber(10, 7);
    AlbaNumber number4 = AlbaNumber(100, 6) * 23.24897;

    EXPECT_EQ(AlbaNumber::Type::Integer, number1.getType());
    EXPECT_EQ(0, number1.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Fraction, number2.getType());
    AlbaNumber::FractionData fractionData2(number2.getFractionData());
    EXPECT_EQ(250, fractionData2.numerator);
    EXPECT_EQ(3, fractionData2.denominator);
    EXPECT_EQ(AlbaNumber::Type::Fraction, number3.getType());
    AlbaNumber::FractionData fractionData3(number3.getFractionData());
    EXPECT_EQ(500, fractionData3.numerator);
    EXPECT_EQ(21, fractionData3.denominator);
    EXPECT_EQ(AlbaNumber::Type::Double, number4.getType());
    EXPECT_DOUBLE_EQ(387.48283333333336, number4.getDouble());
}

TEST(AlbaNumberTest, MultiplyWorksOnTypesStartingFromDouble)
{
    AlbaNumber number1 = AlbaNumber(0.1) * AlbaNumber(0);
    AlbaNumber number2 = AlbaNumber(10.5) * 5;
    AlbaNumber number3 = AlbaNumber(10.5) * AlbaNumber(10, 7);
    AlbaNumber number4 = AlbaNumber(10.5) * 23.24897;

    EXPECT_EQ(AlbaNumber::Type::Double, number1.getType());
    EXPECT_DOUBLE_EQ(0, number1.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number2.getType());
    EXPECT_DOUBLE_EQ(52.5, number2.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number3.getType());
    EXPECT_DOUBLE_EQ(15, number3.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number4.getType());
    EXPECT_DOUBLE_EQ(244.11418499999999, number4.getDouble());
}

TEST(AlbaNumberTest, DivideWorksOnTypesStartingFromInteger)
{
    AlbaNumber number1 = AlbaNumber() / AlbaNumber(1);
    AlbaNumber number2 = AlbaNumber(100) / 10;
    AlbaNumber number3 = AlbaNumber(100) / AlbaNumber(11, 3);
    AlbaNumber number4 = AlbaNumber(100) / 23.24897;

    EXPECT_EQ(AlbaNumber::Type::Integer, number1.getType());
    EXPECT_EQ(0, number1.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number2.getType());
    EXPECT_EQ(10, number2.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Fraction, number3.getType());
    AlbaNumber::FractionData fractionData(number3.getFractionData());
    EXPECT_EQ(300, fractionData.numerator);
    EXPECT_EQ(11, fractionData.denominator);
    EXPECT_EQ(AlbaNumber::Type::Double, number4.getType());
    EXPECT_DOUBLE_EQ(4.3012658195180258, number4.getDouble());
}

TEST(AlbaNumberTest, DivideWorksOnTypesStartingFromFraction)
{
    AlbaNumber number1 = AlbaNumber(0, 1) / AlbaNumber(1, 1);
    AlbaNumber number2 = AlbaNumber(100, 6) / 5;
    AlbaNumber number3 = AlbaNumber(100, 6) / AlbaNumber(10, 7);
    AlbaNumber number4 = AlbaNumber(100, 6) / 23.24897;

    EXPECT_EQ(AlbaNumber::Type::Integer, number1.getType());
    EXPECT_EQ(0, number1.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Fraction, number2.getType());
    AlbaNumber::FractionData fractionData2(number2.getFractionData());
    EXPECT_EQ(10, fractionData2.numerator);
    EXPECT_EQ(3, fractionData2.denominator);
    EXPECT_EQ(AlbaNumber::Type::Fraction, number3.getType());
    AlbaNumber::FractionData fractionData3(number3.getFractionData());
    EXPECT_EQ(35, fractionData3.numerator);
    EXPECT_EQ(3, fractionData3.denominator);
    EXPECT_EQ(AlbaNumber::Type::Double, number4.getType());
    EXPECT_DOUBLE_EQ(0.71687763658633763, number4.getDouble());
}

TEST(AlbaNumberTest, DivideWorksOnTypesStartingFromDouble)
{
    AlbaNumber number1 = AlbaNumber(0.1) / AlbaNumber(1);
    AlbaNumber number2 = AlbaNumber(10.5) / 5;
    AlbaNumber number3 = AlbaNumber(10.5) / AlbaNumber(10, 7);
    AlbaNumber number4 = AlbaNumber(10.5) / 23.24897;

    EXPECT_EQ(AlbaNumber::Type::Double, number1.getType());
    EXPECT_DOUBLE_EQ(0.10000000000000001, number1.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number2.getType());
    EXPECT_DOUBLE_EQ(2.1000000000000001, number2.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number3.getType());
    EXPECT_DOUBLE_EQ(7.3499999999999996, number3.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number4.getType());
    EXPECT_DOUBLE_EQ(0.45163291104939274, number4.getDouble());
}

}
