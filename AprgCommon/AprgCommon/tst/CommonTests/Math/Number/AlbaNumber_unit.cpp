#include <Common/Math/AlbaMathConstants.hpp>
#include <Common/Math/Helpers/PrecisionHelpers.hpp>
#include <Common/Math/Number/AlbaNumber.hpp>
#include <Common/Math/Number/AlbaNumberConstants.hpp>

#include <gtest/gtest.h>

#include <ctgmath>

using namespace alba::AlbaMathConstants;
using namespace alba::AlbaNumberConstants;
using namespace alba::mathHelper;
using namespace std;

namespace alba{

TEST(AlbaNumberTest, SizeValueIsExpected)
{    AlbaNumber number;

    EXPECT_EQ(16U, sizeof(number));
    EXPECT_EQ(8U, number.getNumberDataSize());
}

TEST(AlbaNumberTest, GetDefaultConfigurationDetailsWorks)
{
    AlbaNumber::ConfigurationDetails configurationDetails(
                getDefaultConfigurationDetails<AlbaNumber::ConfigurationDetails>());

    EXPECT_DOUBLE_EQ(COMPARISON_TOLERANCE_FOR_DOUBLE, configurationDetails.comparisonTolerance);
    EXPECT_DOUBLE_EQ(AlbaNumber::ADJUSTMENT_FLOAT_TOLERANCE, configurationDetails.floatAdjustmentTolerance);
}

TEST(AlbaNumberConfigurationTest, GetConfigurationDetailsWorksAtDefault)
{
    AlbaNumber::ConfigurationDetails const& configurationDetails(
                AlbaNumber::Configuration::getInstance().getConfigurationDetails());

    EXPECT_DOUBLE_EQ(COMPARISON_TOLERANCE_FOR_DOUBLE, configurationDetails.comparisonTolerance);
    EXPECT_DOUBLE_EQ(AlbaNumber::ADJUSTMENT_FLOAT_TOLERANCE, configurationDetails.floatAdjustmentTolerance);
}

TEST(AlbaNumberConfigurationTest, ComparisonToleranceIsCorrectlyAtDefault)
{
    EXPECT_DOUBLE_EQ(
                COMPARISON_TOLERANCE_FOR_DOUBLE,
                AlbaNumber::Configuration::getInstance().getConfigurationDetails().comparisonTolerance);
}

TEST(AlbaNumberConfigurationTest, FloatAdjustmentToleranceIsCorrectlyAtDefault)
{
    EXPECT_DOUBLE_EQ(
                AlbaNumber::ADJUSTMENT_FLOAT_TOLERANCE,
                AlbaNumber::Configuration::getInstance().getConfigurationDetails().floatAdjustmentTolerance);
}

TEST(AlbaNumberTest, SettingTolerancesReflectsInAlbaNumber)
{
    AlbaNumber number1(AlbaNumber::createNumberFromDoubleAndRoundIfNeeded(3.01));
    AlbaNumber number2(AlbaNumber::createNumberFromDoubleAndRoundIfNeeded(3.0000000000001));
    EXPECT_TRUE(number1.isDoubleType());
    EXPECT_DOUBLE_EQ(3.01, number1.getDouble());
    EXPECT_TRUE(number2.isIntegerType());    EXPECT_EQ(3, number2.getInteger());

    AlbaNumber::Configuration::getInstance().setConfigurationDetails
            (AlbaNumber::Configuration::getConfigurationDetailsWithZeroTolerance());

    AlbaNumber number3(AlbaNumber::createNumberFromDoubleAndRoundIfNeeded(3.01));
    AlbaNumber number4(AlbaNumber::createNumberFromDoubleAndRoundIfNeeded(3.0000000000001));
    EXPECT_TRUE(number3.isDoubleType());
    EXPECT_DOUBLE_EQ(3.01, number3.getDouble());
    EXPECT_TRUE(number4.isDoubleType());    EXPECT_DOUBLE_EQ(3.0000000000001, number4.getDouble());

    AlbaNumber::Configuration::getInstance().setConfigurationToDefault();

    AlbaNumber number5(AlbaNumber::createNumberFromDoubleAndRoundIfNeeded(3.01));
    AlbaNumber number6(AlbaNumber::createNumberFromDoubleAndRoundIfNeeded(3.0000000000001));
    EXPECT_TRUE(number5.isDoubleType());
    EXPECT_DOUBLE_EQ(3.01, number5.getDouble());
    EXPECT_TRUE(number6.isIntegerType());    EXPECT_EQ(3, number6.getInteger());
}

TEST(AlbaNumberScopeObjectTest, SetInThisScopeThisConfigurationWorksAtDefaultValuesAndValuesAreSetBack)
{
    AlbaNumber number1(AlbaNumber::createNumberFromDoubleAndRoundIfNeeded(3.01));
    AlbaNumber number2(AlbaNumber::createNumberFromDoubleAndRoundIfNeeded(3.0000000000001));
    EXPECT_TRUE(number1.isDoubleType());
    EXPECT_DOUBLE_EQ(3.01, number1.getDouble());
    EXPECT_TRUE(number2.isIntegerType());
    EXPECT_EQ(3, number2.getInteger());

    {
        AlbaNumber::ScopeConfigurationObject scopeConfigurationObject;
        scopeConfigurationObject.setInThisScopeThisConfiguration(AlbaNumber::ConfigurationDetails{0.1, 0.1});

        AlbaNumber number3(AlbaNumber::createNumberFromDoubleAndRoundIfNeeded(3.01));
        AlbaNumber number4(AlbaNumber::createNumberFromDoubleAndRoundIfNeeded(3.0000000000001));
        EXPECT_TRUE(number3.isIntegerType());
        EXPECT_EQ(3, number3.getInteger());
        EXPECT_TRUE(number4.isIntegerType());
        EXPECT_EQ(3, number4.getInteger());
    }

    AlbaNumber number5(AlbaNumber::createNumberFromDoubleAndRoundIfNeeded(3.01));
    AlbaNumber number6(AlbaNumber::createNumberFromDoubleAndRoundIfNeeded(3.0000000000001));
    EXPECT_TRUE(number5.isDoubleType());
    EXPECT_DOUBLE_EQ(3.01, number5.getDouble());
    EXPECT_TRUE(number6.isIntegerType());    EXPECT_EQ(3, number6.getInteger());
}

TEST(AlbaNumberScopeObjectTest, SetInThisScopeTheTolerancesToZeroWorksAtDefaultValuesAndValuesAreSetBack)
{
    AlbaNumber number1(AlbaNumber::createNumberFromDoubleAndRoundIfNeeded(3.01));
    AlbaNumber number2(AlbaNumber::createNumberFromDoubleAndRoundIfNeeded(3.0000000000001));
    EXPECT_TRUE(number1.isDoubleType());
    EXPECT_DOUBLE_EQ(3.01, number1.getDouble());
    EXPECT_TRUE(number2.isIntegerType());
    EXPECT_EQ(3, number2.getInteger());

    {
        AlbaNumber::ScopeConfigurationObject scopeConfigurationObject;
        scopeConfigurationObject.setInThisScopeTheTolerancesToZero();

        AlbaNumber number3(AlbaNumber::createNumberFromDoubleAndRoundIfNeeded(3.01));
        AlbaNumber number4(AlbaNumber::createNumberFromDoubleAndRoundIfNeeded(3.0000000000001));
        EXPECT_TRUE(number3.isDoubleType());
        EXPECT_DOUBLE_EQ(3.01, number3.getDouble());
        EXPECT_TRUE(number4.isDoubleType());
        EXPECT_DOUBLE_EQ(3.0000000000001, number4.getDouble());
    }

    AlbaNumber number5(AlbaNumber::createNumberFromDoubleAndRoundIfNeeded(3.01));
    AlbaNumber number6(AlbaNumber::createNumberFromDoubleAndRoundIfNeeded(3.0000000000001));
    EXPECT_TRUE(number5.isDoubleType());
    EXPECT_DOUBLE_EQ(3.01, number5.getDouble());
    EXPECT_TRUE(number6.isIntegerType());    EXPECT_EQ(3, number6.getInteger());
}

TEST(AlbaNumberScopeObjectTest, SetInThisScopeTheTolerancesToZeroWorksWhenValuesAreChangedAndValuesAreSetBack){
    AlbaNumber::ConfigurationDetails configurationDetailsInThisOutsideScope(
                getDefaultConfigurationDetails<AlbaNumber::ConfigurationDetails>());
    configurationDetailsInThisOutsideScope.comparisonTolerance = 1E-1;
    AlbaNumber::Configuration::getInstance().setConfigurationDetails(configurationDetailsInThisOutsideScope);

    AlbaNumber number1(AlbaNumber::createNumberFromDoubleAndRoundIfNeeded(3.01));
    AlbaNumber number2(AlbaNumber::createNumberFromDoubleAndRoundIfNeeded(3.0000000000001));
    EXPECT_TRUE(number1.isIntegerType());
    EXPECT_EQ(3, number1.getInteger());
    EXPECT_TRUE(number2.isIntegerType());
    EXPECT_EQ(3, number2.getInteger());

    {
        AlbaNumber::ScopeConfigurationObject scopeConfigurationObject;
        scopeConfigurationObject.setInThisScopeTheTolerancesToZero();

        AlbaNumber number3(AlbaNumber::createNumberFromDoubleAndRoundIfNeeded(3.01));
        AlbaNumber number4(AlbaNumber::createNumberFromDoubleAndRoundIfNeeded(3.0000000000001));
        EXPECT_TRUE(number3.isDoubleType());
        EXPECT_DOUBLE_EQ(3.01, number3.getDouble());
        EXPECT_TRUE(number4.isDoubleType());
        EXPECT_DOUBLE_EQ(3.0000000000001, number4.getDouble());
    }

    AlbaNumber number5(AlbaNumber::createNumberFromDoubleAndRoundIfNeeded(3.01));
    AlbaNumber number6(AlbaNumber::createNumberFromDoubleAndRoundIfNeeded(3.0000000000001));
    EXPECT_TRUE(number5.isIntegerType());
    EXPECT_EQ(3, number5.getInteger());
    EXPECT_TRUE(number6.isIntegerType());    EXPECT_EQ(3, number6.getInteger());

    AlbaNumber::Configuration::getInstance().setConfigurationToDefault(); //Ensure set the static values back for other tests
}
TEST(AlbaNumberTest, ConstructionWorksWithDefaultConstructor)
{
    AlbaNumber number1;

    EXPECT_EQ(AlbaNumber::Type::Integer, number1.getType());
    EXPECT_EQ(0, number1.getInteger());
}

TEST(AlbaNumberTest, ConstructionWorksWithValue)
{
    AlbaNumber number1;
    AlbaNumber number2(ALBA_NUMBER_POSITIVE_INFINITY);
    AlbaNumber number3(ALBA_NUMBER_NEGATIVE_INFINITY);
    AlbaNumber number4(ALBA_NUMBER_NOT_A_NUMBER);
    AlbaNumber number5(ALBA_NUMBER_PI);
    AlbaNumber number6(ALBA_NUMBER_E);

    EXPECT_EQ(AlbaNumber::Type::Integer, number1.getType());
    EXPECT_DOUBLE_EQ(0, number1.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Double, number2.getType());
    EXPECT_DOUBLE_EQ(INFINITY, number2.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number3.getType());
    EXPECT_DOUBLE_EQ(-INFINITY, number3.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number4.getType());
    EXPECT_TRUE(isnan(number4.getDouble()));
    EXPECT_EQ(AlbaNumber::Type::Double, number5.getType());
    EXPECT_DOUBLE_EQ(3.14159265358979323846, number5.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number6.getType());
    EXPECT_DOUBLE_EQ(2.7182818284590452354, number6.getDouble());
}

TEST(AlbaNumberTest, CreateIntegerWorks)
{
    AlbaNumber number1(AlbaNumber::createInteger(-81237));
    AlbaNumber number2(AlbaNumber::createInteger(34095093U));
    AlbaNumber number3(AlbaNumber::createInteger(1000000000000000000LL));

    EXPECT_EQ(AlbaNumber::Type::Integer, number1.getType());
    EXPECT_EQ(-81237, number1.getInteger());    EXPECT_EQ(AlbaNumber::Type::Integer, number2.getType());
    EXPECT_EQ(34095093, number2.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number3.getType());
    EXPECT_EQ(1000000000000000000LL, number3.getInteger());
}

TEST(AlbaNumberTest, CreateDoubleWorks)
{
    AlbaNumber number1(AlbaNumber::createDouble(3.01));
    AlbaNumber number2(AlbaNumber::createDouble(3.0000000000001));
    AlbaNumber number3(AlbaNumber::createDouble(POSITIVE_INFINITY_DOUBLE_VALUE));
    AlbaNumber number4(AlbaNumber::createDouble(NEGATIVE_INFINITY_DOUBLE_VALUE));
    AlbaNumber number5(AlbaNumber::createDouble(NAN_DOUBLE_VALUE));

    EXPECT_EQ(AlbaNumber::Type::Double, number1.getType());
    EXPECT_EQ(3.01, number1.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number2.getType());
    EXPECT_EQ(3.0000000000001, number2.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number3.getType());
    EXPECT_TRUE(number3.isPositiveInfinity());
    EXPECT_EQ(AlbaNumber::Type::Double, number4.getType());
    EXPECT_TRUE(number4.isNegativeInfinity());
    EXPECT_EQ(AlbaNumber::Type::Double, number5.getType());
    EXPECT_TRUE(number5.isNotANumber());
}

TEST(AlbaNumberTest, CreateNumberFromDoubleAndRoundIfNeededWorks)
{
    AlbaNumber number1(AlbaNumber::createNumberFromDoubleAndRoundIfNeeded(3.01));
    AlbaNumber number2(AlbaNumber::createNumberFromDoubleAndRoundIfNeeded(3.0000000000001));
    AlbaNumber number3(AlbaNumber::createNumberFromDoubleAndRoundIfNeeded(POSITIVE_INFINITY_DOUBLE_VALUE));
    AlbaNumber number4(AlbaNumber::createNumberFromDoubleAndRoundIfNeeded(NEGATIVE_INFINITY_DOUBLE_VALUE));
    AlbaNumber number5(AlbaNumber::createNumberFromDoubleAndRoundIfNeeded(NAN_DOUBLE_VALUE));

    EXPECT_EQ(AlbaNumber::Type::Double, number1.getType());
    EXPECT_EQ(3.01, number1.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Integer, number2.getType());
    EXPECT_EQ(3, number2.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Double, number3.getType());
    EXPECT_TRUE(number3.isPositiveInfinity());
    EXPECT_EQ(AlbaNumber::Type::Double, number4.getType());
    EXPECT_TRUE(number4.isNegativeInfinity());
    EXPECT_EQ(AlbaNumber::Type::Double, number5.getType());
    EXPECT_TRUE(number5.isNotANumber());
}

TEST(AlbaNumberTest, CreateFractionWorks)
{
    AlbaNumber number1(AlbaNumber::createFraction(-87408, -9802));
    AlbaNumber number2(AlbaNumber::createFraction(-100, 10));    AlbaNumber number3(AlbaNumber::createFraction(-100, -10));

    EXPECT_EQ(AlbaNumber::Type::Fraction, number1.getType());
    AlbaNumber::FractionData fractionData(number1.getFractionData());    EXPECT_EQ(43704, fractionData.numerator);
    EXPECT_EQ(4901U, fractionData.denominator);
    EXPECT_EQ(AlbaNumber::Type::Integer, number2.getType());
    EXPECT_EQ(-10, number2.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number3.getType());
    EXPECT_EQ(10, number3.getInteger());
}

TEST(AlbaNumberTest, CreateComplexNumberWorks)
{
    AlbaNumber number1(AlbaNumber::createComplexNumber(-4, 3));
    AlbaNumber number2(AlbaNumber::createComplexNumber(-4.5, 3.5));    AlbaNumber number3(AlbaNumber::createComplexNumber(-4.0, 0.0));
    AlbaNumber number4(AlbaNumber::createComplexNumber(-4.5, 0.0));

    EXPECT_EQ(AlbaNumber::Type::ComplexNumber, number1.getType());    AlbaNumber::ComplexNumberData complexNumberData1(number1.getComplexNumberData());
    EXPECT_FLOAT_EQ(-4, complexNumberData1.realPart);
    EXPECT_FLOAT_EQ(3, complexNumberData1.imaginaryPart);
    EXPECT_EQ(AlbaNumber::Type::ComplexNumber, number2.getType());
    AlbaNumber::ComplexNumberData complexNumberData2(number2.getComplexNumberData());
    EXPECT_FLOAT_EQ(-4.5, complexNumberData2.realPart);
    EXPECT_FLOAT_EQ(3.5, complexNumberData2.imaginaryPart);
    EXPECT_EQ(AlbaNumber::Type::Integer, number3.getType());
    EXPECT_EQ(-4, number3.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Double, number4.getType());
    EXPECT_DOUBLE_EQ(-4.5, number4.getDouble());
}

TEST(AlbaNumberTest, ConstructionWorks)
{
    AlbaNumber number6(ALBA_NUMBER_POSITIVE_INFINITY);
    AlbaNumber number7(ALBA_NUMBER_NEGATIVE_INFINITY);
    AlbaNumber number8(ALBA_NUMBER_NOT_A_NUMBER);
    AlbaNumber number9(AlbaNumber::createFraction(-87408, -9802));
    AlbaNumber number10(AlbaNumber::createFraction(-100, 10));
    AlbaNumber number11(AlbaNumber::createFraction(-100, -10));    AlbaNumber number12(AlbaNumber::createComplexNumber(-4, 3));
    AlbaNumber number13(AlbaNumber::createComplexNumber(-4.5, 3.5));
    AlbaNumber number14(AlbaNumber::createComplexNumber(-4.0, 0.0));
    AlbaNumber number15(AlbaNumber::createComplexNumber(-4.5, 0.0));
    EXPECT_EQ(AlbaNumber::Type::Double, number6.getType());
    EXPECT_DOUBLE_EQ(INFINITY, number6.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number7.getType());
    EXPECT_DOUBLE_EQ(-INFINITY, number7.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number8.getType());
    EXPECT_TRUE(isnan(number8.getDouble()));
    EXPECT_EQ(AlbaNumber::Type::Fraction, number9.getType());
    AlbaNumber::FractionData fractionData(number9.getFractionData());
    EXPECT_EQ(43704, fractionData.numerator);
    EXPECT_EQ(4901U, fractionData.denominator);
    EXPECT_EQ(AlbaNumber::Type::Integer, number10.getType());
    EXPECT_EQ(-10, number10.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number11.getType());
    EXPECT_EQ(10, number11.getInteger());
    EXPECT_EQ(AlbaNumber::Type::ComplexNumber, number12.getType());
    AlbaNumber::ComplexNumberData complexNumberData1(number12.getComplexNumberData());
    EXPECT_FLOAT_EQ(-4, complexNumberData1.realPart);
    EXPECT_FLOAT_EQ(3, complexNumberData1.imaginaryPart);
    EXPECT_EQ(AlbaNumber::Type::ComplexNumber, number13.getType());
    AlbaNumber::ComplexNumberData complexNumberData2(number13.getComplexNumberData());
    EXPECT_FLOAT_EQ(-4.5, complexNumberData2.realPart);
    EXPECT_FLOAT_EQ(3.5, complexNumberData2.imaginaryPart);
    EXPECT_EQ(AlbaNumber::Type::Integer, number14.getType());
    EXPECT_EQ(-4, number14.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Double, number15.getType());
    EXPECT_DOUBLE_EQ(-4.5, number15.getDouble());
}

TEST(AlbaNumberTest, EqualityWorks)
{
    AlbaNumber number1;
    AlbaNumber number2(-81237);
    AlbaNumber number3(-81237);
    AlbaNumber number4(static_cast<double>(1)/3);
    AlbaNumber number5(ALBA_NUMBER_POSITIVE_INFINITY);
    AlbaNumber number6(ALBA_NUMBER_NEGATIVE_INFINITY);
    AlbaNumber number7(AlbaNumber::createFraction(1, 3));
    AlbaNumber number8(AlbaNumber::createComplexNumber(static_cast<double>(1)/3, 0.0));
    AlbaNumber number9(AlbaNumber::createComplexNumber(-81237, -81237));
    EXPECT_TRUE(number1==number1);
    EXPECT_TRUE(number2==number2);
    EXPECT_TRUE(number3==number3);    EXPECT_TRUE(number4==number4);
    EXPECT_TRUE(number5==number5);
    EXPECT_TRUE(number6==number6);
    EXPECT_TRUE(number7==number7);
    EXPECT_TRUE(number8==number8);
    EXPECT_TRUE(number9==number9);
    EXPECT_FALSE(number1==number2);
    EXPECT_TRUE(number2==number3);
    EXPECT_FALSE(number2==number9);
    EXPECT_FALSE(number3==number4);
    EXPECT_TRUE(number4==number7);
    EXPECT_FALSE(number4==number8);
    EXPECT_FALSE(number5==number6);
    EXPECT_FALSE(number5==number7);
    EXPECT_FALSE(number6==number7);
    EXPECT_FALSE(number7==number8);
    EXPECT_FALSE(number1==number9);
}

TEST(AlbaNumberTest, InequalityWorks)
{
    AlbaNumber number1;
    AlbaNumber number2(-81237);
    AlbaNumber number3(-81237);
    AlbaNumber number4(static_cast<double>(1)/3);
    AlbaNumber number5(ALBA_NUMBER_POSITIVE_INFINITY);
    AlbaNumber number6(ALBA_NUMBER_NEGATIVE_INFINITY);
    AlbaNumber number7(AlbaNumber::createFraction(1, 3));
    AlbaNumber number8(AlbaNumber::createComplexNumber(static_cast<double>(1)/3, 0.0));
    AlbaNumber number9(AlbaNumber::createComplexNumber(-81237, -81237));
    EXPECT_FALSE(number1!=number1);
    EXPECT_FALSE(number2!=number2);
    EXPECT_FALSE(number3!=number3);    EXPECT_FALSE(number4!=number4);
    EXPECT_FALSE(number5!=number5);
    EXPECT_FALSE(number6!=number6);
    EXPECT_FALSE(number7!=number7);
    EXPECT_FALSE(number8!=number8);
    EXPECT_FALSE(number9!=number9);
    EXPECT_TRUE(number1!=number2);
    EXPECT_FALSE(number2!=number3);
    EXPECT_TRUE(number2!=number9);
    EXPECT_TRUE(number3!=number4);
    EXPECT_FALSE(number4!=number7);
    EXPECT_TRUE(number4!=number8);
    EXPECT_TRUE(number5!=number6);
    EXPECT_TRUE(number5!=number7);
    EXPECT_TRUE(number6!=number7);
    EXPECT_TRUE(number7!=number8);
    EXPECT_TRUE(number1!=number9);
}

TEST(AlbaNumberTest, LessThanWorks)
{
    AlbaNumber number1;
    AlbaNumber number2(AlbaNumber::createFraction(1, 3));
    AlbaNumber number3(AlbaNumber::createComplexNumber(0.25, 0.25));
    AlbaNumber number4(0.5);
    AlbaNumber number5(ALBA_NUMBER_POSITIVE_INFINITY);
    AlbaNumber number6(ALBA_NUMBER_NEGATIVE_INFINITY);

    EXPECT_FALSE(number1<number1);
    EXPECT_FALSE(number2<number2);    EXPECT_FALSE(number3<number3);
    EXPECT_FALSE(number4<number4);
    EXPECT_FALSE(number5<number5);
    EXPECT_FALSE(number6<number6);    EXPECT_TRUE(number1<number2);
    EXPECT_TRUE(number2<number4);
    EXPECT_FALSE(number2<number1);
    EXPECT_FALSE(number4<number2);
    EXPECT_TRUE(number1<number3);
    EXPECT_TRUE(number3<number4);
    EXPECT_FALSE(number3<number1);
    EXPECT_FALSE(number4<number3);
    EXPECT_TRUE(number4<number5);
    EXPECT_FALSE(number4<number6);
    EXPECT_FALSE(number5<number6);
}

TEST(AlbaNumberTest, LessThanOrEqualWorks)
{
    AlbaNumber number1;
    AlbaNumber number2(AlbaNumber::createFraction(1, 3));
    AlbaNumber number3(AlbaNumber::createComplexNumber(0.25, 0.25));
    AlbaNumber number4(0.5);
    AlbaNumber number5(ALBA_NUMBER_POSITIVE_INFINITY);
    AlbaNumber number6(ALBA_NUMBER_NEGATIVE_INFINITY);

    EXPECT_TRUE(number1<=number1);
    EXPECT_TRUE(number2<=number2);    EXPECT_TRUE(number3<=number3);
    EXPECT_TRUE(number4<=number4);
    EXPECT_TRUE(number5<=number5);
    EXPECT_TRUE(number6<=number6);    EXPECT_TRUE(number1<=number2);
    EXPECT_TRUE(number2<=number4);
    EXPECT_FALSE(number2<=number1);
    EXPECT_FALSE(number4<=number2);
    EXPECT_TRUE(number1<=number3);
    EXPECT_TRUE(number3<=number4);
    EXPECT_FALSE(number3<=number1);
    EXPECT_FALSE(number4<=number3);
    EXPECT_TRUE(number4<=number5);
    EXPECT_FALSE(number4<=number6);
    EXPECT_FALSE(number5<=number6);
}

TEST(AlbaNumberTest, GreaterThanWorks)
{
    AlbaNumber number1;
    AlbaNumber number2(AlbaNumber::createFraction(1, 3));
    AlbaNumber number3(AlbaNumber::createComplexNumber(0.25, 0.25));
    AlbaNumber number4(0.5);
    AlbaNumber number5(ALBA_NUMBER_POSITIVE_INFINITY);
    AlbaNumber number6(ALBA_NUMBER_NEGATIVE_INFINITY);

    EXPECT_FALSE(number1>number1);
    EXPECT_FALSE(number2>number2);    EXPECT_FALSE(number3>number3);
    EXPECT_FALSE(number4>number4);
    EXPECT_FALSE(number5>number5);
    EXPECT_FALSE(number6>number6);    EXPECT_FALSE(number1>number2);
    EXPECT_FALSE(number2>number4);
    EXPECT_TRUE(number2>number1);
    EXPECT_TRUE(number4>number2);
    EXPECT_FALSE(number1>number3);
    EXPECT_FALSE(number3>number4);
    EXPECT_TRUE(number3>number1);
    EXPECT_TRUE(number4>number3);
    EXPECT_FALSE(number4>number5);
    EXPECT_TRUE(number4>number6);
    EXPECT_TRUE(number5>number6);
}

TEST(AlbaNumberTest, GreaterThanOrEqualWorks)
{
    AlbaNumber number1;
    AlbaNumber number2(AlbaNumber::createFraction(1, 3));
    AlbaNumber number3(AlbaNumber::createComplexNumber(0.25, 0.25));
    AlbaNumber number4(0.5);
    AlbaNumber number5(ALBA_NUMBER_POSITIVE_INFINITY);
    AlbaNumber number6(ALBA_NUMBER_NEGATIVE_INFINITY);

    EXPECT_TRUE(number1>=number1);
    EXPECT_TRUE(number2>=number2);    EXPECT_TRUE(number3>=number3);
    EXPECT_TRUE(number4>=number4);
    EXPECT_TRUE(number5>=number5);
    EXPECT_TRUE(number6>=number6);    EXPECT_FALSE(number1>=number2);
    EXPECT_FALSE(number2>=number4);
    EXPECT_TRUE(number2>=number1);
    EXPECT_TRUE(number4>=number2);
    EXPECT_FALSE(number1>=number3);
    EXPECT_FALSE(number3>=number4);
    EXPECT_TRUE(number3>=number1);
    EXPECT_TRUE(number4>=number3);
    EXPECT_FALSE(number4>=number5);
    EXPECT_TRUE(number4>=number6);
    EXPECT_TRUE(number5>=number6);
}

TEST(AlbaNumberTest, UnaryPlusWorksOnDifferentTypes)
{
    AlbaNumber number1 = +AlbaNumber();
    AlbaNumber number2 = +AlbaNumber(-81237);
    AlbaNumber number3 = +AlbaNumber(34095093U);
    AlbaNumber number4 = +AlbaNumber(4564.38794);
    AlbaNumber number5 = +AlbaNumber::createFraction(-87408, -9802);
    AlbaNumber number6 = +AlbaNumber::createComplexNumber(-4.5, -3.5);

    EXPECT_EQ(AlbaNumber::Type::Integer, number1.getType());
    EXPECT_EQ(0, number1.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number2.getType());
    EXPECT_EQ(-81237, number2.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number3.getType());
    EXPECT_EQ(34095093, number3.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Double, number4.getType());
    EXPECT_DOUBLE_EQ(4564.38794, number4.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Fraction, number5.getType());
    AlbaNumber::FractionData fractionData(number5.getFractionData());
    EXPECT_EQ(43704, fractionData.numerator);
    EXPECT_EQ(4901U, fractionData.denominator);
    EXPECT_EQ(AlbaNumber::Type::ComplexNumber, number6.getType());
    AlbaNumber::ComplexNumberData complexNumberData(number6.getComplexNumberData());
    EXPECT_FLOAT_EQ(-4.5, complexNumberData.realPart);
    EXPECT_FLOAT_EQ(-3.5, complexNumberData.imaginaryPart);
}

TEST(AlbaNumberTest, UnaryMinusWorksOnDifferentTypes)
{
    AlbaNumber number1 = -AlbaNumber();
    AlbaNumber number2 = -AlbaNumber(-81237);
    AlbaNumber number3 = -AlbaNumber(34095093U);
    AlbaNumber number4 = -AlbaNumber(4564.38794);
    AlbaNumber number5 = -AlbaNumber::createFraction(-87408, -9802);
    AlbaNumber number6 = -AlbaNumber::createComplexNumber(-4.5, -3.5);

    EXPECT_EQ(AlbaNumber::Type::Integer, number1.getType());
    EXPECT_EQ(0, number1.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number2.getType());
    EXPECT_EQ(81237, number2.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number3.getType());
    EXPECT_EQ(-34095093, number3.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Double, number4.getType());
    EXPECT_DOUBLE_EQ(-4564.38794, number4.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Fraction, number5.getType());
    AlbaNumber::FractionData fractionData(number5.getFractionData());
    EXPECT_EQ(-43704, fractionData.numerator);
    EXPECT_EQ(4901U, fractionData.denominator);
    EXPECT_EQ(AlbaNumber::Type::ComplexNumber, number6.getType());
    AlbaNumber::ComplexNumberData complexNumberData(number6.getComplexNumberData());
    EXPECT_FLOAT_EQ(4.5, complexNumberData.realPart);
    EXPECT_FLOAT_EQ(3.5, complexNumberData.imaginaryPart);
}

TEST(AlbaNumberTest, AdditionWorksOnTypesStartingFromInteger)
{
    AlbaNumber number1 = AlbaNumber() + AlbaNumber();
    AlbaNumber number2 = AlbaNumber(100) + 10;
    AlbaNumber number3 = AlbaNumber(100) + 23.24897;
    AlbaNumber number4 = AlbaNumber(1234567891) + AlbaNumber(1234567891);
    AlbaNumber number5 = AlbaNumber(9223372036854775807LL) + AlbaNumber(9223372036854775807LL);
    AlbaNumber number6 = AlbaNumber(100) + AlbaNumber::createFraction(10, 3);
    AlbaNumber number7 = AlbaNumber(100) + AlbaNumber::createComplexNumber(-4.5, -3.5);

    EXPECT_EQ(AlbaNumber::Type::Integer, number1.getType());
    EXPECT_EQ(0, number1.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number2.getType());
    EXPECT_EQ(110, number2.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Double, number3.getType());
    EXPECT_DOUBLE_EQ(123.24897, number3.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Integer, number4.getType());
    EXPECT_EQ(2469135782, number4.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Double, number5.getType());
    EXPECT_DOUBLE_EQ(1.8446744073709552e+019, number5.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Fraction, number6.getType());
    AlbaNumber::FractionData fractionData(number6.getFractionData());
    EXPECT_EQ(310, fractionData.numerator);
    EXPECT_EQ(3U, fractionData.denominator);
    EXPECT_EQ(AlbaNumber::Type::ComplexNumber, number7.getType());
    AlbaNumber::ComplexNumberData complexNumberData(number7.getComplexNumberData());
    EXPECT_FLOAT_EQ(95.5, complexNumberData.realPart);
    EXPECT_FLOAT_EQ(-3.5, complexNumberData.imaginaryPart);
}

TEST(AlbaNumberTest, AdditionWorksOnTypesStartingFromDouble)
{
    AlbaNumber number1 = AlbaNumber(0.1) + AlbaNumber(0);
    AlbaNumber number2 = AlbaNumber(10.5) + 5;
    AlbaNumber number3 = AlbaNumber(10.5) + 23.24897;
    AlbaNumber number4 = AlbaNumber(1234567891.1) + AlbaNumber(1234567891);
    AlbaNumber number5 = AlbaNumber(10.5) + AlbaNumber::createFraction(10, 7);
    AlbaNumber number6 = AlbaNumber(10.5) + AlbaNumber::createComplexNumber(-4.5, -3.5);

    EXPECT_EQ(AlbaNumber::Type::Double, number1.getType());
    EXPECT_DOUBLE_EQ(0.1, number1.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number2.getType());
    EXPECT_DOUBLE_EQ(15.5, number2.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number3.getType());
    EXPECT_DOUBLE_EQ(33.74897, number3.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number4.getType());
    EXPECT_DOUBLE_EQ(2469135782.0999999, number4.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number5.getType());
    EXPECT_DOUBLE_EQ(11.928571428571429, number5.getDouble());
    EXPECT_EQ(AlbaNumber::Type::ComplexNumber, number6.getType());
    AlbaNumber::ComplexNumberData complexNumberData(number6.getComplexNumberData());
    EXPECT_FLOAT_EQ(6.0, complexNumberData.realPart);
    EXPECT_FLOAT_EQ(-3.5, complexNumberData.imaginaryPart);
}

TEST(AlbaNumberTest, AdditionWorksOnTypesStartingFromFraction)
{
    AlbaNumber number1 = AlbaNumber::createFraction(0, 1) + AlbaNumber::createFraction(0, 1);
    AlbaNumber number2 = AlbaNumber::createFraction(100, 6) + 5;
    AlbaNumber number3 = AlbaNumber::createFraction(100, 6) + AlbaNumber::createFraction(10, 7);
    AlbaNumber number4 = AlbaNumber::createFraction(100, 6) + AlbaNumber::createFraction(10, 3);
    AlbaNumber number5 = AlbaNumber::createFraction(100, 6) + 23.24897;
    AlbaNumber number6 = AlbaNumber::createFraction(1234567890, 1234567891) + AlbaNumber(1234567891);
    AlbaNumber number7 = AlbaNumber(1234567891) + AlbaNumber::createFraction(1234567890, 1234567891);
    AlbaNumber number8 = AlbaNumber::createFraction(1234567890, 1234567891) + AlbaNumber::createFraction(1234567890, 1234567893);
    AlbaNumber number9 = AlbaNumber::createFraction(23, 4) + AlbaNumber::createComplexNumber(-4.5, -3.5);

    EXPECT_EQ(AlbaNumber::Type::Integer, number1.getType());
    EXPECT_EQ(0, number1.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Fraction, number2.getType());
    AlbaNumber::FractionData fractionData2(number2.getFractionData());
    EXPECT_EQ(65, fractionData2.numerator);
    EXPECT_EQ(3U, fractionData2.denominator);
    EXPECT_EQ(AlbaNumber::Type::Fraction, number3.getType());
    AlbaNumber::FractionData fractionData3(number3.getFractionData());
    EXPECT_EQ(380, fractionData3.numerator);
    EXPECT_EQ(21U, fractionData3.denominator);
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
    EXPECT_EQ(AlbaNumber::Type::ComplexNumber, number9.getType());
    AlbaNumber::ComplexNumberData complexNumberData(number9.getComplexNumberData());
    EXPECT_FLOAT_EQ(1.25, complexNumberData.realPart);
    EXPECT_FLOAT_EQ(-3.5, complexNumberData.imaginaryPart);
}

TEST(AlbaNumberTest, AdditionWorksOnTypesStartingFromComplexNumber)
{
    AlbaNumber number1 = AlbaNumber::createComplexNumber(8.5, 9.5) + 5;
    AlbaNumber number2 = AlbaNumber::createComplexNumber(8.5, 9.5) + 23.24897;
    AlbaNumber number3 = AlbaNumber::createComplexNumber(8.5, 9.5) + AlbaNumber::createFraction(63, 4);
    AlbaNumber number4 = AlbaNumber::createComplexNumber(8.5, 9.5) + AlbaNumber::createComplexNumber(-4.5, -3.5);

    EXPECT_EQ(AlbaNumber::Type::ComplexNumber, number1.getType());
    AlbaNumber::ComplexNumberData complexNumberData1(number1.getComplexNumberData());
    EXPECT_FLOAT_EQ(13.5, complexNumberData1.realPart);
    EXPECT_FLOAT_EQ(9.5, complexNumberData1.imaginaryPart);
    EXPECT_EQ(AlbaNumber::Type::ComplexNumber, number2.getType());
    AlbaNumber::ComplexNumberData complexNumberData2(number2.getComplexNumberData());
    EXPECT_FLOAT_EQ(31.74897, complexNumberData2.realPart);
    EXPECT_FLOAT_EQ(9.5, complexNumberData2.imaginaryPart);
    EXPECT_EQ(AlbaNumber::Type::ComplexNumber, number3.getType());
    AlbaNumber::ComplexNumberData complexNumberData3(number3.getComplexNumberData());
    EXPECT_FLOAT_EQ(24.25, complexNumberData3.realPart);
    EXPECT_FLOAT_EQ(9.5, complexNumberData3.imaginaryPart);
    EXPECT_EQ(AlbaNumber::Type::ComplexNumber, number4.getType());
    AlbaNumber::ComplexNumberData complexNumberData4(number4.getComplexNumberData());
    EXPECT_FLOAT_EQ(4, complexNumberData4.realPart);
    EXPECT_FLOAT_EQ(6, complexNumberData4.imaginaryPart);
}

TEST(AlbaNumberTest, SubtractionWorksOnTypesStartingFromInteger)
{
    AlbaNumber number1 = AlbaNumber() - AlbaNumber();
    AlbaNumber number2 = AlbaNumber(100) - 10;
    AlbaNumber number3 = AlbaNumber(100) - 23.24897;
    AlbaNumber number4 = AlbaNumber(1234567891) - AlbaNumber(1234567891);
    AlbaNumber number5 = AlbaNumber(9223372036854775807LL) - AlbaNumber(9223372036854775807LL);
    AlbaNumber number6 = AlbaNumber(100) - AlbaNumber::createFraction(10, 3);
    AlbaNumber number7 = AlbaNumber(100) - AlbaNumber::createComplexNumber(-4.5, -3.5);

    EXPECT_EQ(AlbaNumber::Type::Integer, number1.getType());
    EXPECT_EQ(0, number1.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number2.getType());
    EXPECT_EQ(90, number2.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Double, number3.getType());
    EXPECT_DOUBLE_EQ(76.75103, number3.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Integer, number4.getType());
    EXPECT_EQ(0, number4.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number5.getType());
    EXPECT_EQ(0, number5.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Fraction, number6.getType());
    AlbaNumber::FractionData fractionData(number6.getFractionData());
    EXPECT_EQ(290, fractionData.numerator);
    EXPECT_EQ(3U, fractionData.denominator);
    EXPECT_EQ(AlbaNumber::Type::ComplexNumber, number7.getType());
    AlbaNumber::ComplexNumberData complexNumberData(number7.getComplexNumberData());
    EXPECT_FLOAT_EQ(104.5, complexNumberData.realPart);
    EXPECT_FLOAT_EQ(3.5, complexNumberData.imaginaryPart);
}

TEST(AlbaNumberTest, SubtractionWorksOnTypesStartingFromDouble)
{
    AlbaNumber number1 = AlbaNumber(0.1) - AlbaNumber(0);
    AlbaNumber number2 = AlbaNumber(10.5) - 5;
    AlbaNumber number3 = AlbaNumber(10.5) - 23.24897;
    AlbaNumber number4 = AlbaNumber(1234567891.1) - AlbaNumber(1234567891);
    AlbaNumber number5 = AlbaNumber(10.5) - AlbaNumber::createFraction(10, 7);
    AlbaNumber number6 = AlbaNumber(10.5) - AlbaNumber::createComplexNumber(-4.5, -3.5);

    EXPECT_EQ(AlbaNumber::Type::Double, number1.getType());
    EXPECT_DOUBLE_EQ(0.1, number1.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number2.getType());
    EXPECT_DOUBLE_EQ(5.5, number2.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number3.getType());
    EXPECT_DOUBLE_EQ(-12.74897, number3.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number4.getType());
    EXPECT_DOUBLE_EQ(0.099999904632568359, number4.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number5.getType());
    EXPECT_DOUBLE_EQ(9.0714285714285712, number5.getDouble());
    EXPECT_EQ(AlbaNumber::Type::ComplexNumber, number6.getType());
    AlbaNumber::ComplexNumberData complexNumberData(number6.getComplexNumberData());
    EXPECT_FLOAT_EQ(15.0, complexNumberData.realPart);
    EXPECT_FLOAT_EQ(3.5, complexNumberData.imaginaryPart);
}

TEST(AlbaNumberTest, SubtractionWorksOnTypesStartingFromFraction)
{
    AlbaNumber number1 = AlbaNumber::createFraction(0, 1) - AlbaNumber::createFraction(0, 1);
    AlbaNumber number2 = AlbaNumber::createFraction(100, 6) - 5;
    AlbaNumber number3 = AlbaNumber::createFraction(100, 6) - AlbaNumber::createFraction(10, 7);
    AlbaNumber number4 = AlbaNumber::createFraction(100, 6) - AlbaNumber::createFraction(10, 3);
    AlbaNumber number5 = AlbaNumber::createFraction(100, 6) - 23.24897;
    AlbaNumber number6 = AlbaNumber::createFraction(1234567890, 1234567891) - AlbaNumber(1234567891);
    AlbaNumber number7 = AlbaNumber(1234567891) - AlbaNumber::createFraction(1234567890, 1234567891);
    AlbaNumber number8 = AlbaNumber::createFraction(1234567890, 1234567891) - AlbaNumber::createFraction(1234567890, 1234567893);
    AlbaNumber number9 = AlbaNumber::createFraction(169, 65536) - AlbaNumber::createFraction(1, 262144);
    AlbaNumber number10 = AlbaNumber::createFraction(23, 4) - AlbaNumber::createComplexNumber(-4.5, -3.5);

    EXPECT_EQ(AlbaNumber::Type::Integer, number1.getType());
    EXPECT_EQ(0, number1.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Fraction, number2.getType());
    AlbaNumber::FractionData fractionData2(number2.getFractionData());
    EXPECT_EQ(35, fractionData2.numerator);
    EXPECT_EQ(3U, fractionData2.denominator);
    EXPECT_EQ(AlbaNumber::Type::Fraction, number3.getType());
    AlbaNumber::FractionData fractionData3(number3.getFractionData());
    EXPECT_EQ(320, fractionData3.numerator);
    EXPECT_EQ(21U, fractionData3.denominator);
    EXPECT_EQ(AlbaNumber::Type::Fraction, number4.getType());
    AlbaNumber::FractionData fractionData4(number4.getFractionData());
    EXPECT_EQ(40, fractionData4.numerator);
    EXPECT_EQ(3U, fractionData4.denominator);
    EXPECT_EQ(AlbaNumber::Type::Double, number5.getType());
    EXPECT_DOUBLE_EQ(-6.582303333333333, number5.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Integer, number6.getType());
    EXPECT_DOUBLE_EQ(-1234567890, number6.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number7.getType());
    EXPECT_DOUBLE_EQ(1234567890, number7.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Double, number8.getType());
    EXPECT_DOUBLE_EQ(1.6200000094932001e-009, number8.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Fraction, number9.getType());
    AlbaNumber::FractionData fractionData9(number9.getFractionData());
    EXPECT_EQ(675, fractionData9.numerator);
    EXPECT_EQ(262144U, fractionData9.denominator);
    EXPECT_EQ(AlbaNumber::Type::ComplexNumber, number10.getType());
    AlbaNumber::ComplexNumberData complexNumberData(number10.getComplexNumberData());
    EXPECT_FLOAT_EQ(10.25, complexNumberData.realPart);
    EXPECT_FLOAT_EQ(3.5, complexNumberData.imaginaryPart);
}

TEST(AlbaNumberTest, SubtractionWorksOnTypesStartingFromComplexNumber)
{
    AlbaNumber number1 = AlbaNumber::createComplexNumber(8.5, 9.5) - 5;
    AlbaNumber number2 = AlbaNumber::createComplexNumber(8.5, 9.5) - 23.24897;
    AlbaNumber number3 = AlbaNumber::createComplexNumber(8.5, 9.5) - AlbaNumber::createFraction(63, 4);
    AlbaNumber number4 = AlbaNumber::createComplexNumber(8.5, 9.5) - AlbaNumber::createComplexNumber(-4.5, -3.5);

    EXPECT_EQ(AlbaNumber::Type::ComplexNumber, number1.getType());
    AlbaNumber::ComplexNumberData complexNumberData1(number1.getComplexNumberData());
    EXPECT_FLOAT_EQ(3.5, complexNumberData1.realPart);
    EXPECT_FLOAT_EQ(9.5, complexNumberData1.imaginaryPart);
    EXPECT_EQ(AlbaNumber::Type::ComplexNumber, number2.getType());
    AlbaNumber::ComplexNumberData complexNumberData2(number2.getComplexNumberData());
    EXPECT_FLOAT_EQ(-14.74897, complexNumberData2.realPart);
    EXPECT_FLOAT_EQ(9.5, complexNumberData2.imaginaryPart);
    EXPECT_EQ(AlbaNumber::Type::ComplexNumber, number3.getType());
    AlbaNumber::ComplexNumberData complexNumberData3(number3.getComplexNumberData());
    EXPECT_FLOAT_EQ(-7.25, complexNumberData3.realPart);
    EXPECT_FLOAT_EQ(9.5, complexNumberData3.imaginaryPart);
    EXPECT_EQ(AlbaNumber::Type::ComplexNumber, number4.getType());
    AlbaNumber::ComplexNumberData complexNumberData4(number4.getComplexNumberData());
    EXPECT_FLOAT_EQ(13, complexNumberData4.realPart);
    EXPECT_FLOAT_EQ(13, complexNumberData4.imaginaryPart);
}

TEST(AlbaNumberTest, MultiplyWorksOnTypesStartingFromInteger)
{
    AlbaNumber number1 = AlbaNumber() * AlbaNumber();
    AlbaNumber number2 = AlbaNumber(100) * 10;
    AlbaNumber number3 = AlbaNumber(100) * 23.24897;
    AlbaNumber number4 = AlbaNumber(1234567891) * AlbaNumber(1234567891);
    AlbaNumber number5 = AlbaNumber(9223372036854775807LL) * AlbaNumber(9223372036854775807LL);
    AlbaNumber number6 = AlbaNumber(100) * AlbaNumber::createFraction(10, 3);
    AlbaNumber number7 = AlbaNumber(100) * AlbaNumber::createComplexNumber(-4.5, -3.5);

    EXPECT_EQ(AlbaNumber::Type::Integer, number1.getType());
    EXPECT_EQ(0, number1.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number2.getType());
    EXPECT_EQ(1000, number2.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Double, number3.getType());
    EXPECT_DOUBLE_EQ(2324.8969999999999, number3.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Integer, number4.getType());
    EXPECT_EQ(1524157877488187881, number4.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Double, number5.getType());
    EXPECT_DOUBLE_EQ(8.5070591730234616e+037, number5.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Fraction, number6.getType());
    AlbaNumber::FractionData fractionData(number6.getFractionData());
    EXPECT_EQ(1000, fractionData.numerator);
    EXPECT_EQ(3U, fractionData.denominator);
    EXPECT_EQ(AlbaNumber::Type::ComplexNumber, number7.getType());
    AlbaNumber::ComplexNumberData complexNumberData(number7.getComplexNumberData());
    EXPECT_FLOAT_EQ(-450, complexNumberData.realPart);
    EXPECT_FLOAT_EQ(-350, complexNumberData.imaginaryPart);
}

TEST(AlbaNumberTest, MultiplyWorksOnTypesStartingFromDouble)
{
    AlbaNumber number1 = AlbaNumber(0.1) * AlbaNumber(0);
    AlbaNumber number2 = AlbaNumber(10.5) * 5;
    AlbaNumber number3 = AlbaNumber(10.5) * AlbaNumber::createFraction(10, 7);
    AlbaNumber number4 = AlbaNumber(10.5) * 23.24897;
    AlbaNumber number5 = AlbaNumber(1234567891.1) * AlbaNumber(1234567891);
    AlbaNumber number6 = AlbaNumber(-5878) * AlbaNumber(16769025);
    AlbaNumber number7 = AlbaNumber(10.5) * AlbaNumber::createComplexNumber(-4.5, -3.5);

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
    EXPECT_EQ(AlbaNumber::Type::ComplexNumber, number7.getType());
    AlbaNumber::ComplexNumberData complexNumberData(number7.getComplexNumberData());
    EXPECT_FLOAT_EQ(-47.25, complexNumberData.realPart);
    EXPECT_FLOAT_EQ(-36.75, complexNumberData.imaginaryPart);
}

TEST(AlbaNumberTest, MultiplyWorksOnTypesStartingFromFraction)
{
    AlbaNumber number1 = AlbaNumber::createFraction(0, 1) * AlbaNumber::createFraction(0, 1);
    AlbaNumber number2 = AlbaNumber::createFraction(100, 6) * 5;
    AlbaNumber number3 = AlbaNumber::createFraction(100, 6) * AlbaNumber::createFraction(10, 7);
    AlbaNumber number4 = AlbaNumber::createFraction(100, 6) * 23.24897;
    AlbaNumber number5 = AlbaNumber::createFraction(-2005875, -79507) * AlbaNumber::createFraction(-688, -27);
    AlbaNumber number6 = AlbaNumber::createFraction(1234567890, 1234567891) * AlbaNumber(1234567891);
    AlbaNumber number7 = AlbaNumber(1234567891) * AlbaNumber::createFraction(1234567890, 1234567891);
    AlbaNumber number8 = AlbaNumber::createFraction(1234567890, 1234567891) * AlbaNumber::createFraction(1234567890, 1234567893);
    AlbaNumber number9 = AlbaNumber::createFraction(23, 4) * AlbaNumber::createComplexNumber(-4.5, -3.5);

    EXPECT_EQ(AlbaNumber::Type::Integer, number1.getType());
    EXPECT_EQ(0, number1.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Fraction, number2.getType());
    AlbaNumber::FractionData fractionData2(number2.getFractionData());
    EXPECT_EQ(250, fractionData2.numerator);
    EXPECT_EQ(3U, fractionData2.denominator);
    EXPECT_EQ(AlbaNumber::Type::Fraction, number3.getType());
    AlbaNumber::FractionData fractionData3(number3.getFractionData());
    EXPECT_EQ(500, fractionData3.numerator);
    EXPECT_EQ(21U, fractionData3.denominator);
    EXPECT_EQ(AlbaNumber::Type::Double, number4.getType());
    EXPECT_DOUBLE_EQ(387.48283333333336, number4.getDouble());
    AlbaNumber::FractionData fractionData5(number5.getFractionData());
    EXPECT_EQ(3566000, fractionData5.numerator);
    EXPECT_EQ(5547U, fractionData5.denominator);
    EXPECT_EQ(AlbaNumber::Type::Integer, number6.getType());
    EXPECT_DOUBLE_EQ(1234567890, number6.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number7.getType());
    EXPECT_DOUBLE_EQ(1234567890, number7.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Double, number8.getType());
    EXPECT_DOUBLE_EQ(0.99999999676000006, number8.getDouble());
    EXPECT_EQ(AlbaNumber::Type::ComplexNumber, number9.getType());
    AlbaNumber::ComplexNumberData complexNumberData(number9.getComplexNumberData());
    EXPECT_FLOAT_EQ(-25.875, complexNumberData.realPart);
    EXPECT_FLOAT_EQ(-20.125, complexNumberData.imaginaryPart);
}

TEST(AlbaNumberTest, MultiplyWorksOnTypesStartingFromComplexNumber)
{
    AlbaNumber number1 = AlbaNumber::createComplexNumber(8.5, 9.5) * 5;
    AlbaNumber number2 = AlbaNumber::createComplexNumber(8.5, 9.5) * 23.24897;
    AlbaNumber number3 = AlbaNumber::createComplexNumber(8.5, 9.5) * AlbaNumber::createFraction(63, 4);
    AlbaNumber number4 = AlbaNumber::createComplexNumber(8.5, 9.5) * AlbaNumber::createComplexNumber(-4.5, -3.5);

    EXPECT_EQ(AlbaNumber::Type::ComplexNumber, number1.getType());
    AlbaNumber::ComplexNumberData complexNumberData1(number1.getComplexNumberData());
    EXPECT_FLOAT_EQ(42.5, complexNumberData1.realPart);
    EXPECT_FLOAT_EQ(47.5, complexNumberData1.imaginaryPart);
    EXPECT_EQ(AlbaNumber::Type::ComplexNumber, number2.getType());
    AlbaNumber::ComplexNumberData complexNumberData2(number2.getComplexNumberData());
    EXPECT_FLOAT_EQ(197.61624, complexNumberData2.realPart);
    EXPECT_FLOAT_EQ(220.86522, complexNumberData2.imaginaryPart);
    EXPECT_EQ(AlbaNumber::Type::ComplexNumber, number3.getType());
    AlbaNumber::ComplexNumberData complexNumberData3(number3.getComplexNumberData());
    EXPECT_FLOAT_EQ(133.875, complexNumberData3.realPart);
    EXPECT_FLOAT_EQ(149.625, complexNumberData3.imaginaryPart);
    EXPECT_EQ(AlbaNumber::Type::ComplexNumber, number4.getType());
    AlbaNumber::ComplexNumberData complexNumberData4(number4.getComplexNumberData());
    EXPECT_FLOAT_EQ(-5, complexNumberData4.realPart);
    EXPECT_FLOAT_EQ(-72.5, complexNumberData4.imaginaryPart);
}

TEST(AlbaNumberTest, DivideWorksOnTypesStartingFromInteger)
{
    AlbaNumber number1 = AlbaNumber() / AlbaNumber(1);
    AlbaNumber number2 = AlbaNumber(100) / 10;
    AlbaNumber number3 = AlbaNumber(100) / 23.24897;
    AlbaNumber number4 = AlbaNumber(1234567893) / AlbaNumber(1234567891);
    AlbaNumber number5 = AlbaNumber(-40)/AlbaNumber(800);
    AlbaNumber number6 = AlbaNumber(9223372036854775807LL) / AlbaNumber(9223372036854775807LL);
    AlbaNumber number7 = AlbaNumber(100) / AlbaNumber::createFraction(11, 3);
    AlbaNumber number8 = AlbaNumber(100) / AlbaNumber::createComplexNumber(-4.5, -3.5);

    EXPECT_EQ(AlbaNumber::Type::Integer, number1.getType());
    EXPECT_EQ(0, number1.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number2.getType());
    EXPECT_EQ(10, number2.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Double, number3.getType());
    EXPECT_DOUBLE_EQ(4.3012658195180258, number3.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Fraction, number4.getType());
    AlbaNumber::FractionData fractionData1(number4.getFractionData());
    EXPECT_EQ(1234567893, fractionData1.numerator);
    EXPECT_EQ(1234567891U, fractionData1.denominator);
    AlbaNumber::FractionData fractionData2(number5.getFractionData());
    EXPECT_EQ(-1, fractionData2.numerator);
    EXPECT_EQ(20U, fractionData2.denominator);
    EXPECT_EQ(AlbaNumber::Type::Integer, number6.getType());
    EXPECT_EQ(1, number6.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Fraction, number7.getType());
    AlbaNumber::FractionData fractionData(number7.getFractionData());
    EXPECT_EQ(300, fractionData.numerator);
    EXPECT_EQ(11U, fractionData.denominator);
    EXPECT_EQ(AlbaNumber::Type::ComplexNumber, number8.getType());
    AlbaNumber::ComplexNumberData complexNumberData(number8.getComplexNumberData());
    EXPECT_FLOAT_EQ(-13.846154, complexNumberData.realPart);
    EXPECT_FLOAT_EQ(10.769231, complexNumberData.imaginaryPart);
}

TEST(AlbaNumberTest, DivideWorksOnTypesStartingFromDouble)
{
    AlbaNumber number1 = AlbaNumber(0.1) / AlbaNumber(1);
    AlbaNumber number2 = AlbaNumber(10.5) / 5;
    AlbaNumber number3 = AlbaNumber(10.5) / 23.24897;
    AlbaNumber number4 = AlbaNumber(1234567891.1) / AlbaNumber(1234567891);
    AlbaNumber number5 = AlbaNumber(10.5) / AlbaNumber::createFraction(10, 7);
    AlbaNumber number6 = AlbaNumber(10.5) / AlbaNumber::createComplexNumber(-4.5, -3.5);

    EXPECT_EQ(AlbaNumber::Type::Double, number1.getType());
    EXPECT_DOUBLE_EQ(0.10000000000000001, number1.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number2.getType());
    EXPECT_DOUBLE_EQ(2.1000000000000001, number2.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number3.getType());
    EXPECT_DOUBLE_EQ(0.45163291104939274, number3.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number4.getType());
    EXPECT_DOUBLE_EQ(1.0000000000809999, number4.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number5.getType());
    EXPECT_DOUBLE_EQ(7.3499999999999996, number5.getDouble());
    EXPECT_EQ(AlbaNumber::Type::ComplexNumber, number6.getType());
    AlbaNumber::ComplexNumberData complexNumberData(number6.getComplexNumberData());
    EXPECT_FLOAT_EQ(-1.4538461, complexNumberData.realPart);
    EXPECT_FLOAT_EQ(1.1307693, complexNumberData.imaginaryPart);
}

TEST(AlbaNumberTest, DivideWorksOnTypesStartingFromFraction)
{
    AlbaNumber number1 = AlbaNumber::createFraction(0, 1) / AlbaNumber::createFraction(1, 1);
    AlbaNumber number2 = AlbaNumber::createFraction(100, 6) / 5;
    AlbaNumber number3 = AlbaNumber::createFraction(100, 6) / AlbaNumber::createFraction(10, 7);
    AlbaNumber number4 = AlbaNumber::createFraction(100, 6) / 23.24897;
    AlbaNumber number5 = AlbaNumber::createFraction(-946400, -2146689) / AlbaNumber::createFraction(-3566000, -5547);
    AlbaNumber number6 = AlbaNumber::createFraction(1234567890, 1234567891) / AlbaNumber(1234567891);
    AlbaNumber number7 = AlbaNumber(1234567891) / AlbaNumber::createFraction(1234567890, 1234567893);
    AlbaNumber number8 = AlbaNumber::createFraction(1234567890, 1234567891) / AlbaNumber::createFraction(1234567890, 1234567893);
    AlbaNumber number9 = AlbaNumber::createFraction(2147483647, 4294967295U) / AlbaNumber::createFraction(2147483646, 4294967294U);
    AlbaNumber number10 = AlbaNumber::createFraction(23, 4) / AlbaNumber::createComplexNumber(-4.5, -3.5);

    EXPECT_EQ(AlbaNumber::Type::Integer, number1.getType());
    EXPECT_EQ(0, number1.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Fraction, number2.getType());
    AlbaNumber::FractionData fractionData2(number2.getFractionData());
    EXPECT_EQ(10, fractionData2.numerator);
    EXPECT_EQ(3U, fractionData2.denominator);
    EXPECT_EQ(AlbaNumber::Type::Fraction, number3.getType());
    AlbaNumber::FractionData fractionData3(number3.getFractionData());
    EXPECT_EQ(35, fractionData3.numerator);
    EXPECT_EQ(3U, fractionData3.denominator);
    EXPECT_EQ(AlbaNumber::Type::Double, number4.getType());
    EXPECT_DOUBLE_EQ(0.71687763658633763, number4.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Fraction, number5.getType());
    AlbaNumber::FractionData fractionData5(number5.getFractionData());
    EXPECT_EQ(2366, fractionData5.numerator);
    EXPECT_EQ(3450105U, fractionData5.denominator);
    EXPECT_EQ(AlbaNumber::Type::Double, number6.getType());
    EXPECT_DOUBLE_EQ(8.1000000605880009e-010, number6.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Integer, number7.getType());
    EXPECT_DOUBLE_EQ(1234567894, number7.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Fraction, number8.getType());
    AlbaNumber::FractionData fractionData8(number8.getFractionData());
    EXPECT_EQ(1234567893, fractionData8.numerator);
    EXPECT_EQ(1234567891U, fractionData8.denominator);
    EXPECT_EQ(AlbaNumber::Type::Double, number9.getType());
    EXPECT_DOUBLE_EQ(1.0000000002328306, number9.getDouble());
    EXPECT_EQ(AlbaNumber::Type::ComplexNumber, number10.getType());
    AlbaNumber::ComplexNumberData complexNumberData(number10.getComplexNumberData());
    EXPECT_FLOAT_EQ(-0.79615384, complexNumberData.realPart);
    EXPECT_FLOAT_EQ(0.61923075, complexNumberData.imaginaryPart);
}

TEST(AlbaNumberTest, DivideWorksOnTypesStartingFromComplexNumber)
{
    AlbaNumber number1 = AlbaNumber::createComplexNumber(8.5, 9.5) / 5;
    AlbaNumber number2 = AlbaNumber::createComplexNumber(8.5, 9.5) / 23.24897;
    AlbaNumber number3 = AlbaNumber::createComplexNumber(8.5, 9.5) / AlbaNumber::createFraction(63, 4);
    AlbaNumber number4 = AlbaNumber::createComplexNumber(8.5, 9.5) / AlbaNumber::createComplexNumber(-4.5, -3.5);

    EXPECT_EQ(AlbaNumber::Type::ComplexNumber, number1.getType());
    AlbaNumber::ComplexNumberData complexNumberData1(number1.getComplexNumberData());
    EXPECT_FLOAT_EQ(1.7, complexNumberData1.realPart);
    EXPECT_FLOAT_EQ(1.9, complexNumberData1.imaginaryPart);
    EXPECT_EQ(AlbaNumber::Type::ComplexNumber, number2.getType());
    AlbaNumber::ComplexNumberData complexNumberData2(number2.getComplexNumberData());
    EXPECT_FLOAT_EQ(0.36560762, complexNumberData2.realPart);
    EXPECT_FLOAT_EQ(0.40862027, complexNumberData2.imaginaryPart);
    EXPECT_EQ(AlbaNumber::Type::ComplexNumber, number3.getType());
    AlbaNumber::ComplexNumberData complexNumberData3(number3.getComplexNumberData());
    EXPECT_FLOAT_EQ(0.53968257, complexNumberData3.realPart);
    EXPECT_FLOAT_EQ(0.60317463, complexNumberData3.imaginaryPart);
    EXPECT_EQ(AlbaNumber::Type::ComplexNumber, number4.getType());
    AlbaNumber::ComplexNumberData complexNumberData4(number4.getComplexNumberData());
    EXPECT_FLOAT_EQ(-2.2, complexNumberData4.realPart);
    EXPECT_FLOAT_EQ(-0.40000001, complexNumberData4.imaginaryPart);
}

TEST(AlbaNumberTest, RaisePowerWorksOnTypesStartingFromInteger)
{
    AlbaNumber number1 = AlbaNumber() ^ AlbaNumber(1);
    AlbaNumber number2 = AlbaNumber(-10) ^ 5;
    AlbaNumber number3 = AlbaNumber(10) ^ 2.324897;
    AlbaNumber number4 = AlbaNumber(1234567891) ^ AlbaNumber(3);
    AlbaNumber number5 = AlbaNumber(9223372036854775807LL) ^ AlbaNumber(5);
    AlbaNumber number6 = AlbaNumber(-256) ^ AlbaNumber(-256);
    AlbaNumber number7 = AlbaNumber(10) ^ AlbaNumber::createFraction(11, 3);
    AlbaNumber number8 = AlbaNumber(10) ^ AlbaNumber::createComplexNumber(-4.5, -3.5); //This is wrong
    AlbaNumber number9 = AlbaNumber(-1) ^ ALBA_NUMBER_POSITIVE_INFINITY;

    EXPECT_EQ(AlbaNumber::Type::Integer, number1.getType());
    EXPECT_EQ(0, number1.getInteger());    EXPECT_EQ(AlbaNumber::Type::Integer, number2.getType());
    EXPECT_EQ(-100000, number2.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Double, number3.getType());
    EXPECT_DOUBLE_EQ(211.29878509707362, number3.getDouble());    EXPECT_EQ(AlbaNumber::Type::Double, number4.getType());
    EXPECT_DOUBLE_EQ(1.8816763763616284e+027, number4.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number5.getType());
    EXPECT_DOUBLE_EQ(6.674959487252844e+094, number5.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Integer, number6.getType());
    EXPECT_DOUBLE_EQ(0, number6.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number7.getType());
    EXPECT_DOUBLE_EQ(4641.5888336127773, number7.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number8.getType());
    EXPECT_DOUBLE_EQ(1.9912363438073718e-006, number8.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number9.getType());
    EXPECT_TRUE(number9.isNotANumber());
}

TEST(AlbaNumberTest, RaisePowerWorksOnTypesStartingFromDouble)
{
    AlbaNumber number1 = AlbaNumber(0.1) ^ AlbaNumber(1);
    AlbaNumber number2 = AlbaNumber(10.5) ^ 5;
    AlbaNumber number3 = AlbaNumber(10.5) ^ 2.324897;
    AlbaNumber number4 = AlbaNumber(1234567891.1) ^ AlbaNumber(3);
    AlbaNumber number5 = AlbaNumber(256.000001) ^ AlbaNumber(256.000001);
    AlbaNumber number6 = AlbaNumber(-256.000001) ^ AlbaNumber(-256.000001);
    AlbaNumber number7 = AlbaNumber(10.5) ^ AlbaNumber::createFraction(10, 7);
    AlbaNumber number8 = AlbaNumber(100.5) ^ AlbaNumber::createComplexNumber(-4.5, -3.5);
    AlbaNumber number9 = AlbaNumber(-100.5) ^ ALBA_NUMBER_POSITIVE_INFINITY;

    EXPECT_EQ(AlbaNumber::Type::Double, number1.getType());
    EXPECT_DOUBLE_EQ(0.10000000000000001, number1.getDouble());    EXPECT_EQ(AlbaNumber::Type::Double, number2.getType());
    EXPECT_DOUBLE_EQ(127628.15625, number2.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number3.getType());
    EXPECT_DOUBLE_EQ(236.67911563383956, number3.getDouble());    EXPECT_EQ(AlbaNumber::Type::Double, number4.getType());
    EXPECT_DOUBLE_EQ(1.8816763768188754e+027, number4.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number5.getType());
    EXPECT_TRUE(number5.isPositiveInfinity());
    EXPECT_EQ(AlbaNumber::Type::Integer, number6.getType());
    EXPECT_EQ(0, number6.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Double, number7.getType());
    EXPECT_DOUBLE_EQ(28.763508283430014, number7.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number8.getType());
    EXPECT_DOUBLE_EQ(3.8538709571806662e-012, number8.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number9.getType());
    EXPECT_TRUE(number9.isNotANumber());
}

TEST(AlbaNumberTest, RaisePowerWorksOnTypesStartingFromFraction)
{
    AlbaNumber number1 = AlbaNumber::createFraction(0, 1) ^ AlbaNumber::createFraction(1, 1);
    AlbaNumber number2 = AlbaNumber::createFraction(10, 6) ^ 5;
    AlbaNumber number3 = AlbaNumber::createFraction(10, 6) ^ AlbaNumber::createFraction(10, 7);
    AlbaNumber number4 = AlbaNumber::createFraction(10, 6) ^ 2.324897;
    AlbaNumber number5 = AlbaNumber::createFraction(12345, 12346) ^ AlbaNumber(1234);
    AlbaNumber number6 = AlbaNumber::createFraction(1234567890, 1234567891) ^ AlbaNumber(3);
    AlbaNumber number7 = AlbaNumber(1234567891) ^ AlbaNumber::createFraction(1234567890, 1234567891);
    AlbaNumber number8 = AlbaNumber::createFraction(1234567890, 1234567891) ^ AlbaNumber::createFraction(1234567890, 1234567893);
    AlbaNumber number9 = AlbaNumber::createFraction(23, 4) ^ AlbaNumber::createComplexNumber(-4.5, -3.5);
    AlbaNumber number10 = AlbaNumber::createFraction(23, 4) ^ ALBA_NUMBER_POSITIVE_INFINITY;

    EXPECT_EQ(AlbaNumber::Type::Integer, number1.getType());
    EXPECT_EQ(0, number1.getInteger());    EXPECT_EQ(AlbaNumber::Type::Fraction, number2.getType());
    AlbaNumber::FractionData fractionData2(number2.getFractionData());
    EXPECT_EQ(3125, fractionData2.numerator);
    EXPECT_EQ(243U, fractionData2.denominator);    EXPECT_EQ(AlbaNumber::Type::Double, number3.getType());
    EXPECT_DOUBLE_EQ(2.0745637509941224, number3.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number4.getType());
    EXPECT_DOUBLE_EQ(3.2792572881529063, number4.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number5.getType());
    EXPECT_TRUE(isAlmostEqual(0.90487772997585858, number5.getDouble(), 1E-13));
    EXPECT_EQ(AlbaNumber::Type::Double, number6.getType());
    EXPECT_DOUBLE_EQ(0.99999999757000013, number6.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number7.getType());    EXPECT_DOUBLE_EQ(1234567870.0660145, number7.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number8.getType());
    EXPECT_DOUBLE_EQ(0.99999999919000004, number8.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number9.getType());    EXPECT_DOUBLE_EQ(4.6690326671664561e-005, number9.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number10.getType());
    EXPECT_DOUBLE_EQ(INFINITY, number10.getDouble());
}

TEST(AlbaNumberTest, RaisePowerWorksOnTypesStartingFromComplexNumber)
{
    AlbaNumber number1 = AlbaNumber::createComplexNumber(8.5, 9.5) ^ 5;
    AlbaNumber number2 = AlbaNumber::createComplexNumber(8.5, 9.5) ^ 23.24897;
    AlbaNumber number3 = AlbaNumber::createComplexNumber(8.5, 9.5) ^ AlbaNumber::createFraction(63, 4);
    AlbaNumber number4 = AlbaNumber::createComplexNumber(8.5, 9.5) ^ AlbaNumber::createComplexNumber(-4.5, -3.5);
    AlbaNumber number5 = AlbaNumber::createComplexNumber(8.5, 9.5) ^ ALBA_NUMBER_POSITIVE_INFINITY;

    EXPECT_EQ(AlbaNumber::Type::ComplexNumber, number1.getType());
    AlbaNumber::ComplexNumberData complexNumberData1(number1.getComplexNumberData());    EXPECT_FLOAT_EQ(-163712.14, complexNumberData1.realPart);
    EXPECT_FLOAT_EQ(-294122.41, complexNumberData1.imaginaryPart);
    EXPECT_EQ(AlbaNumber::Type::ComplexNumber, number2.getType());
    AlbaNumber::ComplexNumberData complexNumberData2(number2.getComplexNumberData());    EXPECT_FLOAT_EQ(-5.0012564e+025, complexNumberData2.realPart);
    EXPECT_FLOAT_EQ(-3.3166986e+024, complexNumberData2.imaginaryPart);
    EXPECT_EQ(AlbaNumber::Type::ComplexNumber, number3.getType());
    AlbaNumber::ComplexNumberData complexNumberData3(number3.getComplexNumberData());
    EXPECT_FLOAT_EQ(-2.0044679e+017, complexNumberData3.realPart);
    EXPECT_FLOAT_EQ(-1.6134964e+017, complexNumberData3.imaginaryPart);
    EXPECT_EQ(AlbaNumber::Type::ComplexNumber, number4.getType());
    AlbaNumber::ComplexNumberData complexNumberData4(number4.getComplexNumberData());
    EXPECT_FLOAT_EQ(-4.9898603e-007, complexNumberData4.realPart);
    EXPECT_FLOAT_EQ(-3.3563614e-009, complexNumberData4.imaginaryPart);
    EXPECT_EQ(AlbaNumber::Type::Double, number5.getType());
    EXPECT_DOUBLE_EQ(INFINITY, number5.getDouble());
}

TEST(AlbaNumberTest, OperatorAdditionAssignmentWorks)
{
    AlbaNumber number1(4506);
    AlbaNumber number2(4506);
    AlbaNumber number3(4506);
    AlbaNumber number4(4506);
    AlbaNumber number5(4506);

    number1 += AlbaNumber(2);
    number2 += -2;
    number3 += 3U;
    number4 += 1000000000000000000LL;
    number5 += 2.2;

    EXPECT_EQ(AlbaNumber::Type::Integer, number1.getType());
    EXPECT_EQ(4508, number1.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number2.getType());
    EXPECT_EQ(4504, number2.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number3.getType());
    EXPECT_EQ(4509, number3.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number4.getType());
    EXPECT_EQ(1000000000000004506, number4.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Double, number5.getType());
    EXPECT_DOUBLE_EQ(4508.2, number5.getDouble());
}

TEST(AlbaNumberTest, OperatorSubtractionAssignmentWorks)
{
    AlbaNumber number1(4506);
    AlbaNumber number2(4506);
    AlbaNumber number3(4506);
    AlbaNumber number4(4506);
    AlbaNumber number5(4506);

    number1 -= AlbaNumber(2);
    number2 -= -2;
    number3 -= 3U;
    number4 -= 10000LL;
    number5 -= 2.2;

    EXPECT_EQ(AlbaNumber::Type::Integer, number1.getType());
    EXPECT_EQ(4504, number1.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number2.getType());
    EXPECT_EQ(4508, number2.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number3.getType());
    EXPECT_EQ(4503, number3.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number4.getType());
    EXPECT_EQ(-5494, number4.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Double, number5.getType());
    EXPECT_DOUBLE_EQ(4503.8, number5.getDouble());
}

TEST(AlbaNumberTest, OperatorMultiplicationAssignmentWorks)
{
    AlbaNumber number1(4506);
    AlbaNumber number2(4506);
    AlbaNumber number3(4506);
    AlbaNumber number4(4506);
    AlbaNumber number5(4506);

    number1 *= AlbaNumber(2);
    number2 *= -2;
    number3 *= 3U;
    number4 *= 10000LL;
    number5 *= 2.2;

    EXPECT_EQ(AlbaNumber::Type::Integer, number1.getType());
    EXPECT_EQ(9012, number1.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number2.getType());
    EXPECT_EQ(-9012, number2.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number3.getType());
    EXPECT_EQ(13518, number3.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number4.getType());
    EXPECT_EQ(45060000, number4.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Double, number5.getType());
    EXPECT_DOUBLE_EQ(9913.2, number5.getDouble());
}

TEST(AlbaNumberTest, OperatorDivisionAssignmentWorks)
{
    AlbaNumber number1(4506);
    AlbaNumber number2(4506);
    AlbaNumber number3(4506);
    AlbaNumber number4(4506);
    AlbaNumber number5(4506);

    number1 /= AlbaNumber(2);
    number2 /= -2;
    number3 /= 3U;
    number4 /= 10000LL;
    number5 /= 2.2;

    EXPECT_EQ(AlbaNumber::Type::Integer, number1.getType());
    EXPECT_EQ(2253, number1.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number2.getType());
    EXPECT_EQ(-2253, number2.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number3.getType());
    EXPECT_EQ(1502, number3.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Fraction, number4.getType());
    AlbaNumber::FractionData fractionData(number4.getFractionData());
    EXPECT_EQ(2253, fractionData.numerator);
    EXPECT_EQ(5000U, fractionData.denominator);
    EXPECT_EQ(AlbaNumber::Type::Double, number5.getType());
    EXPECT_DOUBLE_EQ(2048.181818181818, number5.getDouble());
}

TEST(AlbaNumberTest, IsIntegerTypeWorks)
{
    AlbaNumber number1;
    AlbaNumber number2(-81237);
    AlbaNumber number3(34095093U);
    AlbaNumber number4(1000000000000000000LL);
    AlbaNumber number5(4564.38794);
    AlbaNumber number6(ALBA_NUMBER_POSITIVE_INFINITY);
    AlbaNumber number7(AlbaNumber::createFraction(-87408, -9802));
    AlbaNumber number8(AlbaNumber::createFraction(-100, 10));
    AlbaNumber number9(AlbaNumber::createComplexNumber(-4.5, 3.5));
    EXPECT_TRUE(number1.isIntegerType());
    EXPECT_TRUE(number2.isIntegerType());
    EXPECT_TRUE(number3.isIntegerType());    EXPECT_TRUE(number4.isIntegerType());
    EXPECT_FALSE(number5.isIntegerType());
    EXPECT_FALSE(number6.isIntegerType());
    EXPECT_FALSE(number7.isIntegerType());
    EXPECT_TRUE(number8.isIntegerType());
    EXPECT_FALSE(number9.isIntegerType());
}

TEST(AlbaNumberTest, IsDoubleTypeWorks)
{
    AlbaNumber number1;
    AlbaNumber number2(-81237);
    AlbaNumber number3(34095093U);
    AlbaNumber number4(1000000000000000000LL);
    AlbaNumber number5(4564.38794);
    AlbaNumber number6(ALBA_NUMBER_POSITIVE_INFINITY);
    AlbaNumber number7(AlbaNumber::createFraction(-87408, -9802));
    AlbaNumber number8(AlbaNumber::createFraction(-100, 10));
    AlbaNumber number9(AlbaNumber::createComplexNumber(-4.5, 3.5));
    EXPECT_FALSE(number1.isDoubleType());
    EXPECT_FALSE(number2.isDoubleType());
    EXPECT_FALSE(number3.isDoubleType());    EXPECT_FALSE(number4.isDoubleType());
    EXPECT_TRUE(number5.isDoubleType());
    EXPECT_TRUE(number6.isDoubleType());
    EXPECT_FALSE(number7.isDoubleType());
    EXPECT_FALSE(number8.isDoubleType());
    EXPECT_FALSE(number9.isDoubleType());
}

TEST(AlbaNumberTest, IsFractionTypeWorks)
{
    AlbaNumber number1;
    AlbaNumber number2(-81237);
    AlbaNumber number3(34095093U);
    AlbaNumber number4(1000000000000000000LL);
    AlbaNumber number5(4564.38794);
    AlbaNumber number6(ALBA_NUMBER_POSITIVE_INFINITY);
    AlbaNumber number7(AlbaNumber::createFraction(-87408, -9802));
    AlbaNumber number8(AlbaNumber::createFraction(-100, 10));
    AlbaNumber number9(AlbaNumber::createComplexNumber(-4.5, 3.5));
    EXPECT_FALSE(number1.isFractionType());
    EXPECT_FALSE(number2.isFractionType());
    EXPECT_FALSE(number3.isFractionType());    EXPECT_FALSE(number4.isFractionType());
    EXPECT_FALSE(number5.isFractionType());
    EXPECT_FALSE(number6.isFractionType());
    EXPECT_TRUE(number7.isFractionType());
    EXPECT_FALSE(number8.isFractionType());
    EXPECT_FALSE(number9.isFractionType());
}

TEST(AlbaNumberTest, IsComplexNumberTypeWorks)
{
    AlbaNumber number1;
    AlbaNumber number2(-81237);
    AlbaNumber number3(34095093U);
    AlbaNumber number4(1000000000000000000LL);
    AlbaNumber number5(4564.38794);
    AlbaNumber number6(ALBA_NUMBER_POSITIVE_INFINITY);
    AlbaNumber number7(AlbaNumber::createFraction(-87408, -9802));
    AlbaNumber number8(AlbaNumber::createFraction(-100, 10));
    AlbaNumber number9(AlbaNumber::createComplexNumber(-4.5, 3.5));
    EXPECT_FALSE(number1.isComplexNumberType());
    EXPECT_FALSE(number2.isComplexNumberType());
    EXPECT_FALSE(number3.isComplexNumberType());    EXPECT_FALSE(number4.isComplexNumberType());
    EXPECT_FALSE(number5.isComplexNumberType());
    EXPECT_FALSE(number6.isComplexNumberType());
    EXPECT_FALSE(number7.isComplexNumberType());
    EXPECT_FALSE(number8.isComplexNumberType());
    EXPECT_TRUE(number9.isComplexNumberType());
}

TEST(AlbaNumberTest, IsIntegerOrFractionTypeWorks)
{
    AlbaNumber number1;
    AlbaNumber number2(-81237);
    AlbaNumber number3(34095093U);
    AlbaNumber number4(1000000000000000000LL);
    AlbaNumber number5(4564.38794);
    AlbaNumber number6(ALBA_NUMBER_POSITIVE_INFINITY);
    AlbaNumber number7(AlbaNumber::createFraction(-87408, -9802));
    AlbaNumber number8(AlbaNumber::createFraction(-100, 10));
    AlbaNumber number9(AlbaNumber::createComplexNumber(-4.5, 3.5));
    EXPECT_TRUE(number1.isIntegerOrFractionType());
    EXPECT_TRUE(number2.isIntegerOrFractionType());
    EXPECT_TRUE(number3.isIntegerOrFractionType());    EXPECT_TRUE(number4.isIntegerOrFractionType());
    EXPECT_FALSE(number5.isIntegerOrFractionType());
    EXPECT_FALSE(number6.isIntegerOrFractionType());
    EXPECT_TRUE(number7.isIntegerOrFractionType());
    EXPECT_TRUE(number8.isIntegerOrFractionType());
    EXPECT_FALSE(number9.isIntegerOrFractionType());
}

TEST(AlbaNumberTest, IsPositiveInfinityWorks)
{
    AlbaNumber number1;
    AlbaNumber number2(-81237);
    AlbaNumber number3(34095093U);
    AlbaNumber number4(1000000000000000000LL);
    AlbaNumber number5(4564.38794);
    AlbaNumber number6(AlbaNumber::createFraction(-87408, -9802));
    AlbaNumber number7(AlbaNumber::createFraction(-100, 10));
    AlbaNumber number8(AlbaNumber::createComplexNumber(-4.5, 3.5));
    AlbaNumber number9(ALBA_NUMBER_POSITIVE_INFINITY);
    AlbaNumber number10(ALBA_NUMBER_NEGATIVE_INFINITY);
    AlbaNumber number11(AlbaNumber::createFraction(100, 0));
    AlbaNumber number12(AlbaNumber::createFraction(-100, 0));
    AlbaNumber number13(ALBA_NUMBER_NOT_A_NUMBER);

    EXPECT_FALSE(number1.isPositiveInfinity());
    EXPECT_FALSE(number2.isPositiveInfinity());    EXPECT_FALSE(number3.isPositiveInfinity());
    EXPECT_FALSE(number4.isPositiveInfinity());
    EXPECT_FALSE(number5.isPositiveInfinity());
    EXPECT_FALSE(number6.isPositiveInfinity());    EXPECT_FALSE(number7.isPositiveInfinity());
    EXPECT_FALSE(number8.isPositiveInfinity());
    EXPECT_TRUE(number9.isPositiveInfinity());
    EXPECT_FALSE(number10.isPositiveInfinity());
    EXPECT_TRUE(number11.isPositiveInfinity());
    EXPECT_FALSE(number12.isPositiveInfinity());
    EXPECT_FALSE(number13.isPositiveInfinity());
}

TEST(AlbaNumberTest, IsNegativeInfinityWorks)
{
    AlbaNumber number1;
    AlbaNumber number2(-81237);
    AlbaNumber number3(34095093U);
    AlbaNumber number4(1000000000000000000LL);
    AlbaNumber number5(4564.38794);
    AlbaNumber number6(AlbaNumber::createFraction(-87408, -9802));
    AlbaNumber number7(AlbaNumber::createFraction(-100, 10));
    AlbaNumber number8(AlbaNumber::createComplexNumber(-4.5, 3.5));
    AlbaNumber number9(ALBA_NUMBER_POSITIVE_INFINITY);
    AlbaNumber number10(ALBA_NUMBER_NEGATIVE_INFINITY);
    AlbaNumber number11(AlbaNumber::createFraction(100, 0));
    AlbaNumber number12(AlbaNumber::createFraction(-100, 0));
    AlbaNumber number13(ALBA_NUMBER_NOT_A_NUMBER);

    EXPECT_FALSE(number1.isNegativeInfinity());
    EXPECT_FALSE(number2.isNegativeInfinity());    EXPECT_FALSE(number3.isNegativeInfinity());
    EXPECT_FALSE(number4.isNegativeInfinity());
    EXPECT_FALSE(number5.isNegativeInfinity());
    EXPECT_FALSE(number6.isNegativeInfinity());    EXPECT_FALSE(number7.isNegativeInfinity());
    EXPECT_FALSE(number8.isNegativeInfinity());
    EXPECT_FALSE(number9.isNegativeInfinity());
    EXPECT_TRUE(number10.isNegativeInfinity());
    EXPECT_FALSE(number11.isNegativeInfinity());
    EXPECT_TRUE(number12.isNegativeInfinity());
    EXPECT_FALSE(number13.isNegativeInfinity());
}

TEST(AlbaNumberTest, IsPositiveOrNegativeInfinityWorks)
{
    AlbaNumber number1;
    AlbaNumber number2(-81237);
    AlbaNumber number3(34095093U);
    AlbaNumber number4(1000000000000000000LL);
    AlbaNumber number5(4564.38794);
    AlbaNumber number6(AlbaNumber::createFraction(-87408, -9802));
    AlbaNumber number7(AlbaNumber::createFraction(-100, 10));
    AlbaNumber number8(AlbaNumber::createComplexNumber(-4.5, 3.5));
    AlbaNumber number9(ALBA_NUMBER_POSITIVE_INFINITY);
    AlbaNumber number10(ALBA_NUMBER_NEGATIVE_INFINITY);
    AlbaNumber number11(AlbaNumber::createFraction(100, 0));
    AlbaNumber number12(AlbaNumber::createFraction(-100, 0));
    AlbaNumber number13(ALBA_NUMBER_NOT_A_NUMBER);

    EXPECT_FALSE(number1.isPositiveOrNegativeInfinity());
    EXPECT_FALSE(number2.isPositiveOrNegativeInfinity());    EXPECT_FALSE(number3.isPositiveOrNegativeInfinity());
    EXPECT_FALSE(number4.isPositiveOrNegativeInfinity());
    EXPECT_FALSE(number5.isPositiveOrNegativeInfinity());
    EXPECT_FALSE(number6.isPositiveOrNegativeInfinity());    EXPECT_FALSE(number7.isPositiveOrNegativeInfinity());
    EXPECT_FALSE(number8.isPositiveOrNegativeInfinity());
    EXPECT_TRUE(number9.isPositiveOrNegativeInfinity());
    EXPECT_TRUE(number10.isPositiveOrNegativeInfinity());
    EXPECT_TRUE(number11.isPositiveOrNegativeInfinity());
    EXPECT_TRUE(number12.isPositiveOrNegativeInfinity());
    EXPECT_FALSE(number13.isPositiveOrNegativeInfinity());
}

TEST(AlbaNumberTest, IsNotANumberWorks)
{
    AlbaNumber number1;
    AlbaNumber number2(-81237);
    AlbaNumber number3(34095093U);
    AlbaNumber number4(1000000000000000000LL);
    AlbaNumber number5(4564.38794);
    AlbaNumber number6(AlbaNumber::createFraction(-87408, -9802));
    AlbaNumber number7(AlbaNumber::createFraction(-100, 10));
    AlbaNumber number8(AlbaNumber::createComplexNumber(-4.5, 3.5));
    AlbaNumber number9(ALBA_NUMBER_POSITIVE_INFINITY);
    AlbaNumber number10(ALBA_NUMBER_NEGATIVE_INFINITY);
    AlbaNumber number11(AlbaNumber::createFraction(100, 0));
    AlbaNumber number12(AlbaNumber::createFraction(-100, 0));
    AlbaNumber number13(ALBA_NUMBER_NOT_A_NUMBER);

    EXPECT_FALSE(number1.isNotANumber());
    EXPECT_FALSE(number2.isNotANumber());    EXPECT_FALSE(number3.isNotANumber());
    EXPECT_FALSE(number4.isNotANumber());
    EXPECT_FALSE(number5.isNotANumber());
    EXPECT_FALSE(number6.isNotANumber());    EXPECT_FALSE(number7.isNotANumber());
    EXPECT_FALSE(number8.isNotANumber());
    EXPECT_FALSE(number9.isNotANumber());
    EXPECT_FALSE(number10.isNotANumber());
    EXPECT_FALSE(number11.isNotANumber());
    EXPECT_FALSE(number12.isNotANumber());
    EXPECT_TRUE(number13.isNotANumber());
}

TEST(AlbaNumberTest, IsAFiniteValueWorks)
{
    AlbaNumber number1;
    AlbaNumber number2(-81237);
    AlbaNumber number3(34095093U);
    AlbaNumber number4(1000000000000000000LL);
    AlbaNumber number5(4564.38794);
    AlbaNumber number6(AlbaNumber::createFraction(-87408, -9802));
    AlbaNumber number7(AlbaNumber::createFraction(-100, 10));
    AlbaNumber number8(AlbaNumber::createComplexNumber(-4.5, 3.5));
    AlbaNumber number9(ALBA_NUMBER_POSITIVE_INFINITY);
    AlbaNumber number10(ALBA_NUMBER_NEGATIVE_INFINITY);
    AlbaNumber number11(AlbaNumber::createFraction(100, 0));
    AlbaNumber number12(AlbaNumber::createFraction(-100, 0));
    AlbaNumber number13(ALBA_NUMBER_NOT_A_NUMBER);

    EXPECT_TRUE(number1.isAFiniteValue());
    EXPECT_TRUE(number2.isAFiniteValue());    EXPECT_TRUE(number3.isAFiniteValue());
    EXPECT_TRUE(number4.isAFiniteValue());
    EXPECT_TRUE(number5.isAFiniteValue());
    EXPECT_TRUE(number6.isAFiniteValue());    EXPECT_TRUE(number7.isAFiniteValue());
    EXPECT_TRUE(number8.isAFiniteValue());
    EXPECT_FALSE(number9.isAFiniteValue());
    EXPECT_FALSE(number10.isAFiniteValue());
    EXPECT_FALSE(number11.isAFiniteValue());
    EXPECT_FALSE(number12.isAFiniteValue());
    EXPECT_FALSE(number13.isAFiniteValue());
}

TEST(AlbaNumberTest, GetIntegerWorks)
{
    AlbaNumber number1;
    AlbaNumber number2(-81237);
    AlbaNumber number3(34095093U);
    AlbaNumber number4(1000000000000000000LL);
    AlbaNumber number5(4564.38794);
    AlbaNumber number6(ALBA_NUMBER_POSITIVE_INFINITY);
    AlbaNumber number7(ALBA_NUMBER_NEGATIVE_INFINITY);
    AlbaNumber number8(ALBA_NUMBER_NOT_A_NUMBER);
    AlbaNumber number9(AlbaNumber::createFraction(-87408, -9802));
    AlbaNumber number10(AlbaNumber::createComplexNumber(-4.5, 3.5));
    EXPECT_EQ(0, number1.getInteger());
    EXPECT_EQ(-81237, number2.getInteger());
    EXPECT_EQ(34095093, number3.getInteger());    EXPECT_EQ(1000000000000000000, number4.getInteger());
    EXPECT_EQ(4564, number5.getInteger());
    EXPECT_EQ(static_cast<long long int>(-9223372036854775808U), number6.getInteger());
    EXPECT_EQ(static_cast<long long int>(-9223372036854775808U), number7.getInteger());
    EXPECT_EQ(static_cast<long long int>(-9223372036854775808U), number8.getInteger());
    EXPECT_EQ(9, number9.getInteger());
    EXPECT_EQ(-6, number10.getInteger());
}

TEST(AlbaNumberTest, GetDoubleWorks)
{
    AlbaNumber number1;
    AlbaNumber number2(-81237);
    AlbaNumber number3(34095093U);
    AlbaNumber number4(1000000000000000000LL);
    AlbaNumber number5(4564.38794);
    AlbaNumber number6(ALBA_NUMBER_POSITIVE_INFINITY);
    AlbaNumber number7(ALBA_NUMBER_NEGATIVE_INFINITY);
    AlbaNumber number8(ALBA_NUMBER_NOT_A_NUMBER);
    AlbaNumber number9(AlbaNumber::createFraction(-87408, -9802));
    AlbaNumber number10(AlbaNumber::createComplexNumber(-4.5, 3.5));
    EXPECT_DOUBLE_EQ(0, number1.getDouble());
    EXPECT_DOUBLE_EQ(-81237, number2.getDouble());
    EXPECT_DOUBLE_EQ(34095093, number3.getDouble());    EXPECT_DOUBLE_EQ(1000000000000000000, number4.getDouble());
    EXPECT_DOUBLE_EQ(4564.38794, number5.getDouble());
    EXPECT_DOUBLE_EQ(INFINITY, number6.getDouble());
    EXPECT_DOUBLE_EQ(-INFINITY, number7.getDouble());
    EXPECT_TRUE(isnan(number8.getDouble()));
    EXPECT_DOUBLE_EQ(8.9173638033054488, number9.getDouble());
    EXPECT_DOUBLE_EQ(-5.7008771896362305, number10.getDouble());
}

TEST(AlbaNumberTest, GetFractionDataWorks)
{
    AlbaNumber number1;    AlbaNumber number2(-81237);
    AlbaNumber number3(34095093U);
    AlbaNumber number4(1000000000000000000LL);
    AlbaNumber number5(4564.38794);
    AlbaNumber number6(ALBA_NUMBER_POSITIVE_INFINITY);
    AlbaNumber number7(ALBA_NUMBER_NEGATIVE_INFINITY);
    AlbaNumber number8(ALBA_NUMBER_NOT_A_NUMBER);
    AlbaNumber number9(AlbaNumber::createFraction(-87408, -9802));
    AlbaNumber number10(AlbaNumber::createComplexNumber(-4.5, 3.5));
    AlbaNumber::FractionData fractionData1(number1.getFractionData());
    EXPECT_EQ(0, fractionData1.numerator);
    EXPECT_EQ(1U, fractionData1.denominator);    AlbaNumber::FractionData fractionData2(number2.getFractionData());
    EXPECT_EQ(-81237, fractionData2.numerator);
    EXPECT_EQ(1U, fractionData2.denominator);
    AlbaNumber::FractionData fractionData3(number3.getFractionData());
    EXPECT_EQ(34095093, fractionData3.numerator);
    EXPECT_EQ(1U, fractionData3.denominator);
    AlbaNumber::FractionData fractionData4(number4.getFractionData());
    EXPECT_EQ(-1486618624, fractionData4.numerator);
    EXPECT_EQ(1U, fractionData4.denominator);
    AlbaNumber::FractionData fractionData5(number5.getFractionData());
    EXPECT_EQ(228219397, fractionData5.numerator);
    EXPECT_EQ(50000U, fractionData5.denominator);
    AlbaNumber::FractionData fractionData6(number6.getFractionData());
    EXPECT_EQ(1, fractionData6.numerator);
    EXPECT_EQ(0U, fractionData6.denominator);
    AlbaNumber::FractionData fractionData7(number7.getFractionData());
    EXPECT_EQ(-1, fractionData7.numerator);
    EXPECT_EQ(0U, fractionData7.denominator);
    AlbaNumber::FractionData fractionData8(number8.getFractionData());
    EXPECT_EQ(0, fractionData8.numerator);
    EXPECT_EQ(1U, fractionData8.denominator);
    AlbaNumber::FractionData fractionData9(number9.getFractionData());
    EXPECT_EQ(43704, fractionData9.numerator);
    EXPECT_EQ(4901U, fractionData9.denominator);
    AlbaNumber::FractionData fractionData10(number10.getFractionData());
    EXPECT_EQ(-5977803, fractionData10.numerator);
    EXPECT_EQ(1048576U, fractionData10.denominator);
}

TEST(AlbaNumberTest, GetComplexNumberDataWorks)
{
    AlbaNumber number1;
    AlbaNumber number2(-81237);
    AlbaNumber number3(34095093U);
    AlbaNumber number4(1000000000000000000LL);
    AlbaNumber number5(4564.38794);
    AlbaNumber number6(ALBA_NUMBER_POSITIVE_INFINITY);
    AlbaNumber number7(ALBA_NUMBER_NEGATIVE_INFINITY);
    AlbaNumber number8(ALBA_NUMBER_NOT_A_NUMBER);
    AlbaNumber number9(AlbaNumber::createFraction(-87408, -9802));
    AlbaNumber number10(AlbaNumber::createComplexNumber(-4.5, 3.5));
    AlbaNumber::ComplexNumberData complexNumberData1(number1.getComplexNumberData());
    EXPECT_FLOAT_EQ(0, complexNumberData1.realPart);
    EXPECT_FLOAT_EQ(0, complexNumberData1.imaginaryPart);    AlbaNumber::ComplexNumberData complexNumberData2(number2.getComplexNumberData());
    EXPECT_FLOAT_EQ(-81237, complexNumberData2.realPart);
    EXPECT_FLOAT_EQ(0, complexNumberData2.imaginaryPart);
    AlbaNumber::ComplexNumberData complexNumberData3(number3.getComplexNumberData());
    EXPECT_FLOAT_EQ(34095092, complexNumberData3.realPart);
    EXPECT_FLOAT_EQ(0, complexNumberData3.imaginaryPart);
    AlbaNumber::ComplexNumberData complexNumberData4(number4.getComplexNumberData());
    EXPECT_FLOAT_EQ(9.9999998e+017, complexNumberData4.realPart);    EXPECT_FLOAT_EQ(0, complexNumberData4.imaginaryPart);
    AlbaNumber::ComplexNumberData complexNumberData5(number5.getComplexNumberData());
    EXPECT_FLOAT_EQ(4564.3882, complexNumberData5.realPart);
    EXPECT_FLOAT_EQ(0, complexNumberData5.imaginaryPart);    AlbaNumber::ComplexNumberData complexNumberData6(number6.getComplexNumberData());
    EXPECT_FLOAT_EQ(INFINITY, complexNumberData6.realPart);
    EXPECT_FLOAT_EQ(0, complexNumberData6.imaginaryPart);
    AlbaNumber::ComplexNumberData complexNumberData7(number7.getComplexNumberData());
    EXPECT_FLOAT_EQ(-INFINITY, complexNumberData7.realPart);
    EXPECT_FLOAT_EQ(0, complexNumberData7.imaginaryPart);
    AlbaNumber::ComplexNumberData complexNumberData8(number8.getComplexNumberData());
    EXPECT_TRUE(isnan(complexNumberData8.realPart));
    EXPECT_FLOAT_EQ(0, complexNumberData8.imaginaryPart);
    AlbaNumber::ComplexNumberData complexNumberData9(number9.getComplexNumberData());
    EXPECT_FLOAT_EQ(8.9173641, complexNumberData9.realPart);
    EXPECT_FLOAT_EQ(0, complexNumberData9.imaginaryPart);
    AlbaNumber::ComplexNumberData complexNumberData10(number10.getComplexNumberData());
    EXPECT_FLOAT_EQ(-4.5, complexNumberData10.realPart);
    EXPECT_FLOAT_EQ(3.5, complexNumberData10.imaginaryPart);
}

TEST(AlbaNumberTest, ConvertToIntegerWorks)
{
    AlbaNumber number1(-1561);
    AlbaNumber number2(-85.25);
    AlbaNumber number3(-2.99999821186066);
    AlbaNumber number4(AlbaNumber::createFraction(-415, 41));
    AlbaNumber number5(AlbaNumber::createFraction(-3, 2));
    AlbaNumber number6(AlbaNumber::createComplexNumber(8.9, 7.8));

    number1.convertToInteger();
    number2.convertToInteger();
    number3.convertToInteger();
    number4.convertToInteger();
    number5.convertToInteger();
    number6.convertToInteger();

    EXPECT_EQ(AlbaNumber::Type::Integer, number1.getType());
    EXPECT_EQ(-1561, number1.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number2.getType());
    EXPECT_EQ(-85, number2.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number3.getType());
    EXPECT_EQ(-3, number3.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number4.getType());
    EXPECT_EQ(-10, number4.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number5.getType());
    EXPECT_EQ(-2, number5.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Integer, number6.getType());
    EXPECT_EQ(12, number6.getInteger());
}

TEST(AlbaNumberTest, ConvertToFractionWorks)
{
    AlbaNumber number1(-1561);
    AlbaNumber number2(-85.25);
    AlbaNumber number3(AlbaNumber::createFraction(-415, 41));
    AlbaNumber number4(AlbaNumber::createComplexNumber(8.9, 7.8));

    number1.convertToFraction();
    number2.convertToFraction();
    number3.convertToFraction();
    number4.convertToFraction();

    EXPECT_EQ(AlbaNumber::Type::Integer, number1.getType());
    EXPECT_EQ(-1561, number1.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Fraction, number2.getType());
    AlbaNumber::FractionData fractionData2(number2.getFractionData());
    EXPECT_EQ(-341, fractionData2.numerator);
    EXPECT_EQ(4U, fractionData2.denominator);
    EXPECT_EQ(AlbaNumber::Type::Fraction, number3.getType());
    AlbaNumber::FractionData fractionData3(number3.getFractionData());
    EXPECT_EQ(-415, fractionData3.numerator);
    EXPECT_EQ(41U, fractionData3.denominator);
    EXPECT_EQ(AlbaNumber::Type::Fraction, number4.getType());
    AlbaNumber::FractionData fractionData4(number4.getFractionData());
    EXPECT_EQ(12409133, fractionData4.numerator);
    EXPECT_EQ(1048576U, fractionData4.denominator);
}

TEST(AlbaNumberTest, DivisionOfAValueByZeroWorks){
    AlbaNumber number1(5);
    AlbaNumber number2(1.25);
    AlbaNumber number3(AlbaNumber::createFraction(5, 0));    AlbaNumber number4(AlbaNumber::createComplexNumber(8.9, 7.8));

    number1 = number1/0;
    number2 = number2/0;
    number4 = number4/0;

    EXPECT_EQ(AlbaNumber::Type::Double, number1.getType());
    EXPECT_DOUBLE_EQ(INFINITY, number1.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number2.getType());
    EXPECT_DOUBLE_EQ(INFINITY, number2.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number3.getType());
    EXPECT_DOUBLE_EQ(INFINITY, number3.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Double, number4.getType());
    EXPECT_TRUE(isnan(number4.getDouble()));
}

TEST(AlbaNumberTest, DivisionOfZeroByZeroWorks)
{
    AlbaNumber number1(0);
    AlbaNumber number2(static_cast<double>(0));
    AlbaNumber number3(AlbaNumber::createFraction(0, 0));
    AlbaNumber number4(AlbaNumber::createComplexNumber(8.9, 7.8));

    number1 = number1/0;
    number2 = number2/0;
    number4 = number4/0;

    EXPECT_EQ(AlbaNumber::Type::Double, number1.getType());
    EXPECT_TRUE(isnan(number1.getDouble()));
    EXPECT_EQ(AlbaNumber::Type::Double, number2.getType());
    EXPECT_TRUE(isnan(number2.getDouble()));
    EXPECT_EQ(AlbaNumber::Type::Double, number3.getType());
    EXPECT_TRUE(isnan(number3.getDouble()));
    EXPECT_EQ(AlbaNumber::Type::Double, number4.getType());
    EXPECT_TRUE(isnan(number4.getDouble()));
}

TEST(AlbaNumberTest, SquareRootOfNegativeNumberWorks)
{
    AlbaNumber numberToVerify1 = AlbaNumber(-8) ^ AlbaNumber::createFraction(1, 3);
    AlbaNumber numberToVerify2 = AlbaNumber(-1) ^ AlbaNumber::createFraction(1, 2);
    AlbaNumber numberToVerify3 = AlbaNumber(-5) ^ AlbaNumber::createFraction(1, 2);

    EXPECT_EQ(AlbaNumber::Type::Integer, numberToVerify1.getType());
    EXPECT_DOUBLE_EQ(-2, numberToVerify1.getInteger());
    EXPECT_EQ(AlbaNumber::Type::ComplexNumber, numberToVerify2.getType());
    AlbaNumber::ComplexNumberData complexNumberData2(numberToVerify2.getComplexNumberData());
    EXPECT_FLOAT_EQ(0, complexNumberData2.realPart);
    EXPECT_FLOAT_EQ(1, complexNumberData2.imaginaryPart);
    EXPECT_EQ(AlbaNumber::Type::ComplexNumber, numberToVerify3.getType());
    AlbaNumber::ComplexNumberData complexNumberData3(numberToVerify3.getComplexNumberData());
    EXPECT_FLOAT_EQ(0, complexNumberData3.realPart);
    EXPECT_FLOAT_EQ(2.236068, complexNumberData3.imaginaryPart);
}

TEST(AlbaNumberTest, PrecisionWorksOnSquareRootAndPolynomialCalculation)
{
    AlbaNumber valueToTest(3.99999999999636202119290828705);

    AlbaNumber numerator = (valueToTest ^ AlbaNumber::createFraction(1,2)) - 2;
    AlbaNumber denominator = valueToTest - 4;
    AlbaNumber numberToVerify = numerator/denominator;

    EXPECT_EQ(AlbaNumber::Type::Integer, numerator.getType());
    EXPECT_EQ(0, numerator.getInteger());
    EXPECT_EQ(AlbaNumber::Type::Double, denominator.getType());
    EXPECT_DOUBLE_EQ(-3.637978807091713e-012, denominator.getDouble());
    EXPECT_EQ(AlbaNumber::Type::Integer, numberToVerify.getType());
    EXPECT_EQ(0, numberToVerify.getInteger());
}

TEST(AlbaNumberTest, OutputStreamOperatorWorks)
{
    stringstream ss;
    AlbaNumber number1;
    AlbaNumber number2(3484);
    AlbaNumber number3(-1561);
    AlbaNumber number4(-85.45631);
    AlbaNumber number5(ALBA_NUMBER_PI);
    AlbaNumber number6(ALBA_NUMBER_E);
    AlbaNumber number7(AlbaNumber::createFraction(-415, 41745));
    AlbaNumber number8(AlbaNumber::createComplexNumber(8.9, 7.8));
    ss << number1 << "," << number2 << "," << number3 << "," << number4 << "," << number5 << "," << number6 << "," << number7 << "," << number8;

    EXPECT_EQ("0,3484,-1561,-85.4563,(pi),(e),(-83/8349),(8.9 + 7.8i)", ss.str());}

}
