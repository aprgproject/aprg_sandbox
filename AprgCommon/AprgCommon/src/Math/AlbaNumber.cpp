#include "AlbaNumber.hpp"

#include <Math/AlbaMathHelper.hpp>

#include <cmath>
#include <sstream>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

AlbaNumber::AlbaNumber()
    : m_type(Type::Integer)
{
    int& intDataReference(m_data.intData);
    intDataReference = 0;
}

AlbaNumber::AlbaNumber(int const signedValue)
    : m_type(Type::Integer)
{
    int& intDataReference(m_data.intData);
    intDataReference = signedValue;
}

AlbaNumber::AlbaNumber(unsigned int const unsignedValue)
    : m_type(Type::Integer)
{
    int& intDataReference(m_data.intData);
    intDataReference = static_cast<int>(unsignedValue);
}

AlbaNumber::AlbaNumber(int const numerator, int const denominator)
    : m_type(Type::Fraction)
{
    if(denominator==0)    {
        *this = AlbaNumber(static_cast<double>(numerator)/denominator);
    }
    else    {
        FractionDetails fractionDetails(getFractionDetailsInLowestForm(numerator, denominator));
        FractionData& fractionDataReference(m_data.fractionData);
        fractionDataReference.numerator = fractionDetails.sign*fractionDetails.numerator;
        fractionDataReference.denominator = fractionDetails.denominator;
        convertToIntegerIfNeeded();
    }
}
AlbaNumber::AlbaNumber(double const doubleValue)
    : m_type(Type::Double)
{    double& doubleDataReference(m_data.doubleData);
    doubleDataReference = doubleValue;
    convertToIntegerIfNeeded();
}

bool AlbaNumber::operator==(AlbaNumber const& second) const
{
    return isAlmostEqual(getDouble(), second.getDouble());
}

bool AlbaNumber::operator!=(AlbaNumber const& second) const
{
    AlbaNumber const& first(*this);
    return !(first==second);
}

bool AlbaNumber::operator<=(AlbaNumber const& second) const
{
    return getDouble() <= second.getDouble();
}

bool AlbaNumber::operator>=(AlbaNumber const& second) const
{
    return getDouble() >= second.getDouble();
}

bool AlbaNumber::operator<(AlbaNumber const& second) const
{
    return getDouble() < second.getDouble();
}

bool AlbaNumber::operator>(AlbaNumber const& second) const
{
    return getDouble() > second.getDouble();
}

AlbaNumber AlbaNumber::operator+() const
{
    return *this;
}

AlbaNumber AlbaNumber::operator-() const
{
    AlbaNumber result(*this);
    if(result.m_type == Type::Integer)
    {
        int& intDataReference(result.m_data.intData);
        intDataReference=-intDataReference;
    }
    else if(result.m_type == Type::Fraction)
    {
        FractionData& fractionDataReference(result.m_data.fractionData);
        fractionDataReference.numerator=-fractionDataReference.numerator;
    }
    else if(result.m_type == Type::Double)
    {
        double& doubleDataReference(result.m_data.doubleData);
        doubleDataReference = -doubleDataReference;
    }
    return result;
}

AlbaNumber AlbaNumber::operator+(AlbaNumber const& value) const
{
    AlbaNumber first(*this);
    AlbaNumber second(value);

    AlbaNumber result;
    bool shouldBeConvertedToDouble(false);
    if(first.m_type == Type::Integer && second.m_type == Type::Integer)
    {
        int const& intDataReference1(first.m_data.intData);
        int const& intDataReference2(second.m_data.intData);
        result = addBothIntegersAndReturnNumber(shouldBeConvertedToDouble, intDataReference1, intDataReference2);
    }
    else if(first.m_type == Type::Integer && second.m_type == Type::Fraction)
    {
        int const& intDataReference1(first.m_data.intData);
        FractionData const& fractionDataReference2(second.m_data.fractionData);
        result = addIntegerAndFractionAndReturnNumber(shouldBeConvertedToDouble, intDataReference1, fractionDataReference2);
    }
    else if(first.m_type == Type::Integer && second.m_type == Type::Double)
    {        int const& intDataReference1(first.m_data.intData);
        double const& doubleDataReference2(second.m_data.doubleData);
        result = addIntegerAndDoubleAndReturnNumber(intDataReference1, doubleDataReference2);
    }    else if(first.m_type == Type::Fraction && second.m_type == Type::Integer)
    {
        FractionData const& fractionDataReference1(first.m_data.fractionData);
        int const& intDataReference2(second.m_data.intData);
        result = addIntegerAndFractionAndReturnNumber(shouldBeConvertedToDouble, intDataReference2, fractionDataReference1);
    }
    else if(first.m_type == Type::Fraction && second.m_type == Type::Fraction)
    {
        FractionData const& fractionDataReference1(first.m_data.fractionData);
        FractionData const& fractionDataReference2(second.m_data.fractionData);
        result = addBothFractionsAndReturnNumber(shouldBeConvertedToDouble, fractionDataReference1, fractionDataReference2);
    }
    else if(first.m_type == Type::Fraction && second.m_type == Type::Double)
    {        FractionData const& fractionDataReference1(first.m_data.fractionData);
        double const& doubleDataReference2(second.m_data.doubleData);
        result = addFractionAndDoubleAndReturnNumber(fractionDataReference1, doubleDataReference2);
    }    else if(first.m_type == Type::Double && second.m_type == Type::Integer)
    {
        double const& doubleDataReference1(first.m_data.doubleData);
        int const& intDataReference2(second.m_data.intData);
        result = addIntegerAndDoubleAndReturnNumber(intDataReference2, doubleDataReference1);
    }
    else if(first.m_type == Type::Double && second.m_type == Type::Fraction)
    {
        double const& doubleDataReference1(first.m_data.doubleData);
        FractionData const& fractionDataReference2(second.m_data.fractionData);
        result = addFractionAndDoubleAndReturnNumber(fractionDataReference2, doubleDataReference1);
    }
    else if(first.m_type == Type::Double && second.m_type == Type::Double)
    {
        double const& doubleDataReference1(first.m_data.doubleData);
        double const& doubleDataReference2(second.m_data.doubleData);
        result = addBothDoubleAndReturnNumber(doubleDataReference1, doubleDataReference2);
    }
    if(shouldBeConvertedToDouble)
    {
        result = addBothDoubleAndReturnNumber(first.getDouble(), second.getDouble());
    }
    return result;
}
AlbaNumber AlbaNumber::operator-(AlbaNumber const& second) const
{
    return operator+(-second);}

AlbaNumber AlbaNumber::operator*(AlbaNumber const& value) const
{
    AlbaNumber first(*this);
    AlbaNumber second(value);

    AlbaNumber result(*this);
    bool shouldBeConvertedToDouble(false);
    if(first.m_type == Type::Integer && second.m_type == Type::Integer)
    {
        int const& intDataReference1(first.m_data.intData);
        int const& intDataReference2(second.m_data.intData);
        result = multiplyBothIntegersAndReturnNumber(shouldBeConvertedToDouble, intDataReference1, intDataReference2);
    }
    else if(first.m_type == Type::Integer && second.m_type == Type::Fraction)
    {
        int const& intDataReference1(first.m_data.intData);
        FractionData const& fractionDataReference2(second.m_data.fractionData);
        result = multiplyIntegerAndFractionAndReturnNumber(shouldBeConvertedToDouble, intDataReference1, fractionDataReference2);
    }
    else if(first.m_type == Type::Integer && second.m_type == Type::Double)
    {        int const& intDataReference1(first.m_data.intData);
        double const& doubleDataReference2(second.m_data.doubleData);
        result = multiplyIntegerAndDoubleAndReturnNumber(intDataReference1, doubleDataReference2);
    }    else if(first.m_type == Type::Fraction && second.m_type == Type::Integer)
    {
        FractionData const& fractionDataReference1(first.m_data.fractionData);
        int const& intDataReference2(second.m_data.intData);
        result = multiplyIntegerAndFractionAndReturnNumber(shouldBeConvertedToDouble, intDataReference2, fractionDataReference1);
    }
    else if(first.m_type == Type::Fraction && second.m_type == Type::Fraction)
    {
        FractionData const& fractionDataReference1(first.m_data.fractionData);
        FractionData const& fractionDataReference2(second.m_data.fractionData);
        result = multiplyBothFractionsAndReturnNumber(shouldBeConvertedToDouble, fractionDataReference1, fractionDataReference2);
    }
    else if(first.m_type == Type::Fraction && second.m_type == Type::Double)
    {        FractionData const& fractionDataReference1(first.m_data.fractionData);
        double const& doubleDataReference2(second.m_data.doubleData);
        result = multiplyFractionAndDoubleAndReturnNumber(fractionDataReference1, doubleDataReference2);
    }    else if(first.m_type == Type::Double && second.m_type == Type::Integer)
    {
        double const& doubleDataReference1(first.m_data.doubleData);
        int const& intDataReference2(second.m_data.intData);
        result = multiplyIntegerAndDoubleAndReturnNumber(intDataReference2, doubleDataReference1);
    }
    else if(first.m_type == Type::Double && second.m_type == Type::Fraction)
    {
        double const& doubleDataReference1(first.m_data.doubleData);
        FractionData const& fractionDataReference2(second.m_data.fractionData);
        result = multiplyFractionAndDoubleAndReturnNumber(fractionDataReference2, doubleDataReference1);
    }
    else if(first.m_type == Type::Double && second.m_type == Type::Double)
    {
        double const& doubleDataReference1(first.m_data.doubleData);
        double const& doubleDataReference2(second.m_data.doubleData);
        result = multiplyBothDoubleAndReturnNumber(doubleDataReference1, doubleDataReference2);
    }
    if(shouldBeConvertedToDouble)
    {
        result = multiplyBothDoubleAndReturnNumber(first.getDouble(), second.getDouble());
    }
    return result;
}
AlbaNumber AlbaNumber::operator/(AlbaNumber const& value) const
{
    AlbaNumber first(*this);
    AlbaNumber second(value);

    AlbaNumber result(*this);
    bool shouldBeConvertedToDouble(false);
    if(first.m_type == Type::Integer && second.m_type == Type::Integer)
    {
        int const& intDataReference1(first.m_data.intData);
        int const& intDataReference2(second.m_data.intData);
        result = divideBothIntegersAndReturnNumber(shouldBeConvertedToDouble, intDataReference1, intDataReference2);
    }
    else if(first.m_type == Type::Integer && second.m_type == Type::Fraction)
    {
        int const& intDataReference1(first.m_data.intData);
        FractionData const& fractionDataReference2(second.m_data.fractionData);
        result = divideDividendsAndDivisorsAndReturnNumber(
                    shouldBeConvertedToDouble,
                    intDataReference1,
                    fractionDataReference2.denominator,
                    fractionDataReference2.numerator,
                    1);
    }
    else if(first.m_type == Type::Integer && second.m_type == Type::Double)
    {        int const& intDataReference1(first.m_data.intData);
        double const& doubleDataReference2(second.m_data.doubleData);
        result = AlbaNumber(static_cast<double>(intDataReference1) / doubleDataReference2);
    }    else if(first.m_type == Type::Fraction && second.m_type == Type::Integer)
    {
        FractionData const& fractionDataReference1(first.m_data.fractionData);
        int const& intDataReference2(second.m_data.intData);
        result = divideDividendsAndDivisorsAndReturnNumber(
                    shouldBeConvertedToDouble,
                    fractionDataReference1.numerator,
                    1,
                    intDataReference2,
                    fractionDataReference1.denominator);
    }
    else if(first.m_type == Type::Fraction && second.m_type == Type::Fraction)
    {
        FractionData const& fractionDataReference1(first.m_data.fractionData);
        FractionData const& fractionDataReference2(second.m_data.fractionData);
        result = divideBothFractionsAndReturnNumber(shouldBeConvertedToDouble, fractionDataReference1, fractionDataReference2);
    }
    else if(first.m_type == Type::Fraction && second.m_type == Type::Double)
    {        FractionData const& fractionDataReference1(first.m_data.fractionData);
        double const& doubleDataReference2(second.m_data.doubleData);
        result = AlbaNumber(
                    static_cast<double>(fractionDataReference1.numerator) /                    fractionDataReference1.denominator /
                    doubleDataReference2);
    }
    else if(first.m_type == Type::Double && second.m_type == Type::Integer)
    {
        double const& doubleDataReference1(first.m_data.doubleData);
        int const& intDataReference2(second.m_data.intData);
        result = AlbaNumber(doubleDataReference1 / intDataReference2);
    }
    else if(first.m_type == Type::Double && second.m_type == Type::Fraction)
    {
        double const& doubleDataReference1(first.m_data.doubleData);
        FractionData const& fractionDataReference2(second.m_data.fractionData);
        result = AlbaNumber(
                    doubleDataReference1 *
                    fractionDataReference2.denominator /
                    fractionDataReference2.numerator);
    }
    else if(first.m_type == Type::Double && second.m_type == Type::Double)
    {
        double const& doubleDataReference1(first.m_data.doubleData);
        double const& doubleDataReference2(second.m_data.doubleData);
        result = AlbaNumber(doubleDataReference1 / doubleDataReference2);
    }
    if(shouldBeConvertedToDouble)
    {
        result = AlbaNumber(first.getDouble() / second.getDouble());
    }
    return result;
}
AlbaNumber AlbaNumber::operator^(AlbaNumber const& value) const
{
    AlbaNumber first(*this);
    AlbaNumber second(value);

    AlbaNumber result(*this);
    bool shouldBeConvertedToDouble(false);
    if(first.m_type == Type::Integer && second.m_type == Type::Integer)
    {
        int const& intDataReference1(first.m_data.intData);
        int const& intDataReference2(second.m_data.intData);
        result = raisePowerOfBothIntegersAndReturnNumber(shouldBeConvertedToDouble, intDataReference1, intDataReference2);
    }
    else if(first.m_type == Type::Integer && second.m_type == Type::Fraction)
    {        result = AlbaNumber(pow(getDouble(), second.getDouble()));
    }
    else if(first.m_type == Type::Integer && second.m_type == Type::Double)
    {        result = AlbaNumber(pow(getDouble(), second.getDouble()));
    }
    else if(first.m_type == Type::Fraction && second.m_type == Type::Integer)
    {
        FractionData const& fractionDataReference1(first.m_data.fractionData);
        int const& intDataReference2(second.m_data.intData);
        result = raisePowerOfFractionsAndIntegerAndReturnNumber(shouldBeConvertedToDouble, fractionDataReference1, intDataReference2);
    }
    else if(first.m_type == Type::Fraction && second.m_type == Type::Fraction)
    {        result = AlbaNumber(pow(getDouble(), second.getDouble()));
    }
    else if(first.m_type == Type::Fraction && second.m_type == Type::Double)
    {        result = AlbaNumber(pow(getDouble(), second.getDouble()));
    }
    else if(first.m_type == Type::Double && second.m_type == Type::Integer)
    {
        result = AlbaNumber(pow(getDouble(), second.getDouble()));
    }
    else if(first.m_type == Type::Double && second.m_type == Type::Fraction)
    {
        result = AlbaNumber(pow(getDouble(), second.getDouble()));
    }
    else if(first.m_type == Type::Double && second.m_type == Type::Double)
    {
        result = AlbaNumber(pow(getDouble(), second.getDouble()));
    }
    if(shouldBeConvertedToDouble)
    {
        result = AlbaNumber(pow(getDouble(), second.getDouble()));
    }
    return result;
}
AlbaNumber AlbaNumber::operator+(int const signedValue) const
{
    return operator+(AlbaNumber(signedValue));}

AlbaNumber AlbaNumber::operator-(int const signedValue) const
{
    return operator-(AlbaNumber(signedValue));
}

AlbaNumber AlbaNumber::operator*(int const signedValue) const
{
    return operator*(AlbaNumber(signedValue));
}

AlbaNumber AlbaNumber::operator/(int const signedValue) const
{
    return operator/(AlbaNumber(signedValue));
}

AlbaNumber AlbaNumber::operator^(int const signedValue) const
{
    return operator^(AlbaNumber(signedValue));
}

AlbaNumber AlbaNumber::operator+(unsigned int const unsignedValue) const
{
    return operator+(AlbaNumber(unsignedValue));
}

AlbaNumber AlbaNumber::operator-(unsigned int const unsignedValue) const
{
    return operator-(AlbaNumber(unsignedValue));
}

AlbaNumber AlbaNumber::operator*(unsigned int const unsignedValue) const
{
    return operator*(AlbaNumber(unsignedValue));
}

AlbaNumber AlbaNumber::operator/(unsigned int const unsignedValue) const
{
    return operator/(AlbaNumber(unsignedValue));
}

AlbaNumber AlbaNumber::operator^(unsigned int const unsignedValue) const
{
    return operator^(AlbaNumber(unsignedValue));
}

AlbaNumber AlbaNumber::operator+(double const doubleValue) const
{
    return operator+(AlbaNumber(doubleValue));
}

AlbaNumber AlbaNumber::operator-(double const doubleValue) const
{
    return operator-(AlbaNumber(doubleValue));
}

AlbaNumber AlbaNumber::operator*(double const doubleValue) const
{
    return operator*(AlbaNumber(doubleValue));
}

AlbaNumber AlbaNumber::operator/(double const doubleValue) const
{
    return operator/(AlbaNumber(doubleValue));
}

AlbaNumber AlbaNumber::operator^(double const doubleValue) const
{
    return operator^(AlbaNumber(doubleValue));
}

bool AlbaNumber::isIntegerType() const
{
    return m_type==Type::Integer;
}

bool AlbaNumber::isFractionType() const
{
    return m_type==Type::Fraction;
}

bool AlbaNumber::isDoubleType() const
{
    return m_type==Type::Double;
}

bool AlbaNumber::isIntegerOrFractionType() const
{
    return isIntegerType() || isFractionType();
}

AlbaNumber::Type AlbaNumber::getType() const
{
    return m_type;
}

int AlbaNumber::getInteger() const
{
    int result(0);
    if(m_type==Type::Integer)
    {
        int const& dataReference(m_data.intData);
        result = dataReference;
    }
    else if(m_type==Type::Fraction)
    {
        FractionData const& dataReference(m_data.fractionData);
        result = getIntegerAfterRoundingDoubleValue(static_cast<double>(dataReference.numerator)/dataReference.denominator);
    }
    else if(m_type==Type::Double)
    {
        double const& dataReference(m_data.doubleData);
        result = getIntegerAfterRoundingDoubleValue(dataReference);
    }
    return result;
}

AlbaNumber::FractionData AlbaNumber::getFractionData() const
{
    FractionData result{0, 0};
    if(m_type==Type::Integer)
    {
        int const& dataReference(m_data.intData);
        result.numerator = dataReference;
        result.denominator = 1u;
    }
    else if(m_type==Type::Fraction)
    {
        FractionData const& dataReference(m_data.fractionData);
        result = dataReference;
    }
    else if(m_type==Type::Double)
    {
        //this is costly avoid this
        double const& dataReference(m_data.doubleData);
        FractionDetails bestFractionDetails(getBestFractionDetailsForDoubleValue(dataReference));
        result.denominator = bestFractionDetails.denominator;
        result.numerator = bestFractionDetails.sign * bestFractionDetails.numerator;
    }
    return result;
}

double AlbaNumber::getDouble() const
{
    double result(0);
    if(m_type==Type::Integer)
    {
        int const& dataReference(m_data.intData);
        result = static_cast<double>(dataReference);
    }
    else if(m_type==Type::Fraction)
    {
        FractionData const& dataReference(m_data.fractionData);
        result = static_cast<double>(static_cast<double>(dataReference.numerator)/dataReference.denominator);
    }
    else if(m_type==Type::Double)
    {
        double const& dataReference(m_data.doubleData);
        result = dataReference;
    }
    return result;
}

string AlbaNumber::getDisplayableString() const
{
    stringstream result;
    if(m_type==Type::Integer)
    {
        result << getInteger();
    }
    else if(m_type==Type::Fraction)
    {
        FractionData fractionData(getFractionData());
        result << "(" << fractionData.numerator << "/" << fractionData.denominator << ")";
    }
    else if(m_type==Type::Double)
    {
        result.precision(15);
        result << getDouble();
    }
    return result.str();
}

void AlbaNumber::convertToInteger()
{
    *this = AlbaNumber(getInteger());
}

void AlbaNumber::convertToFraction()
{
    FractionData fractionData(getFractionData());
    *this = AlbaNumber(fractionData.numerator, fractionData.denominator);
}

void AlbaNumber::convertToIntegerIfNeeded()
{
    if(m_type == Type::Fraction)    {
        FractionData const& fractionDataReference(m_data.fractionData);
        if(isDivisible(getAbsoluteValue(fractionDataReference.numerator), fractionDataReference.denominator))
        {            *this = AlbaNumber(static_cast<int>(fractionDataReference.numerator/fractionDataReference.denominator));
        }
    }
    else if(m_type == Type::Double)
    {
        double realValue(getDouble());
        if(!isValueBeyondIntegerLimits(realValue) && isAlmostAnInteger(realValue))
        {
            *this = AlbaNumber(getIntegerAfterRoundingDoubleValue(realValue));
        }    }
}

AlbaNumber AlbaNumber::addBothIntegersAndReturnNumber(
        bool & shouldBeConvertedToDouble,
        int const signedValue1,
        int const signedValue2) const
{
    double numberValue = static_cast<double>(signedValue1) + signedValue2;
    shouldBeConvertedToDouble = isValueBeyondIntegerLimits(numberValue);
    return AlbaNumber(getIntegerAfterRoundingDoubleValue(numberValue));
}

AlbaNumber AlbaNumber::addBothFractionsAndReturnNumber(
        bool & shouldBeConvertedToDouble,
        AlbaNumber::FractionData const& fractionData1,
        AlbaNumber::FractionData const& fractionData2) const
{
    double lcm(getLeastCommonMultipleInDouble(fractionData1.denominator, fractionData2.denominator));
    double numeratorResult =
            ((lcm/fractionData1.denominator)*fractionData1.numerator) +
            ((lcm/fractionData2.denominator)*fractionData2.numerator);
    shouldBeConvertedToDouble = isValueBeyondIntegerLimits(numeratorResult) || isValueBeyondIntegerLimits(lcm);
    return AlbaNumber(getIntegerAfterRoundingDoubleValue(numeratorResult), getIntegerAfterRoundingDoubleValue(lcm));
}

AlbaNumber AlbaNumber::addBothDoubleAndReturnNumber(
        double const doubleValue1,
        double const doubleValue2) const
{
    return AlbaNumber(doubleValue1 + doubleValue2);
}

AlbaNumber AlbaNumber::addIntegerAndFractionAndReturnNumber(
        bool & shouldBeConvertedToDouble,
        int const signedValue,
        FractionData const& fractionData) const
{
    double numerator(fractionData.numerator + (static_cast<double>(fractionData.denominator)*signedValue));
    shouldBeConvertedToDouble = isValueBeyondIntegerLimits(numerator);
    return AlbaNumber(getIntegerAfterRoundingDoubleValue(numerator), fractionData.denominator);
}

AlbaNumber AlbaNumber::addIntegerAndDoubleAndReturnNumber(int const signedValue, double const doubleValue) const{
    return AlbaNumber(static_cast<double>(signedValue + doubleValue));
}
AlbaNumber AlbaNumber::addFractionAndDoubleAndReturnNumber(FractionData const& fractionData, double const doubleValue) const
{
    return AlbaNumber(
                static_cast<double>(
                    static_cast<double>(fractionData.numerator)/fractionData.denominator +
                    doubleValue));
}

AlbaNumber AlbaNumber::multiplyBothIntegersAndReturnNumber(
        bool & shouldBeConvertedToDouble,
        int const signedValue1,
        int const signedValue2) const
{
    double numberValue = static_cast<double>(signedValue1) * signedValue2;
    shouldBeConvertedToDouble = isValueBeyondIntegerLimits(numberValue);
    return AlbaNumber(getIntegerAfterRoundingDoubleValue(numberValue));
}

AlbaNumber AlbaNumber::multiplyBothFractionsAndReturnNumber(
        bool & shouldBeConvertedToDouble,
        AlbaNumber::FractionData const& fractionData1,
        AlbaNumber::FractionData const& fractionData2) const
{
    double numerator(static_cast<double>(fractionData1.numerator) * fractionData2.numerator);
    double denominator(static_cast<double>(fractionData1.denominator) * fractionData2.denominator);
    shouldBeConvertedToDouble = isValueBeyondIntegerLimits(numerator) || isValueBeyondIntegerLimits(denominator);
    return AlbaNumber(getIntegerAfterRoundingDoubleValue(numerator), getIntegerAfterRoundingDoubleValue(denominator));
}

AlbaNumber AlbaNumber::multiplyBothDoubleAndReturnNumber(double const doubleValue1, double const doubleValue2) const{
    return AlbaNumber(doubleValue1 * doubleValue2);
}

AlbaNumber AlbaNumber::multiplyIntegerAndFractionAndReturnNumber(
        bool & shouldBeConvertedToDouble,
        int const signedValue,
        FractionData const& fractionData) const
{
    double numerator(static_cast<double>(signedValue) * fractionData.numerator);
    shouldBeConvertedToDouble = isValueBeyondIntegerLimits(numerator);
    return AlbaNumber(getIntegerAfterRoundingDoubleValue(numerator), fractionData.denominator);
}

AlbaNumber AlbaNumber::multiplyIntegerAndDoubleAndReturnNumber(int const signedValue, double const doubleValue) const{
    return AlbaNumber(static_cast<double>(signedValue) * doubleValue);
}
AlbaNumber AlbaNumber::multiplyFractionAndDoubleAndReturnNumber(FractionData const& fractionData, double const doubleValue) const
{
    return AlbaNumber(
                static_cast<double>(
                    static_cast<double>(fractionData.numerator)/fractionData.denominator *
                    doubleValue));
}

AlbaNumber AlbaNumber::divideBothIntegersAndReturnNumber(
        bool & shouldBeConvertedToDouble,
        int const dividend,
        int const divisor) const
{
    FractionDetails fractionDetails(getFractionDetailsInLowestForm(dividend, divisor));
    double numerator(fractionDetails.sign*fractionDetails.numerator);
    shouldBeConvertedToDouble = isValueBeyondIntegerLimits(numerator);
    return AlbaNumber(getIntegerAfterRoundingDoubleValue(numerator), fractionDetails.denominator);
}

AlbaNumber AlbaNumber::divideDividendsAndDivisorsAndReturnNumber(
        bool & shouldBeConvertedToDouble,
        int const dividendInteger,
        unsigned int const dividendUnsignedInteger,
        int const divisorInteger,
        unsigned int const divisorUnsignedInteger) const
{
    double numerator(static_cast<double>(dividendInteger) * dividendUnsignedInteger);
    double denominator(static_cast<double>(divisorInteger) * divisorUnsignedInteger);
    shouldBeConvertedToDouble = isValueBeyondIntegerLimits(numerator) || isValueBeyondIntegerLimits(denominator);
    return AlbaNumber(getIntegerAfterRoundingDoubleValue(numerator), getIntegerAfterRoundingDoubleValue(denominator));
}

AlbaNumber AlbaNumber::divideBothFractionsAndReturnNumber(
        bool & shouldBeConvertedToDouble,
        AlbaNumber::FractionData const& dividendFractionData,
        AlbaNumber::FractionData const& divisorFractionData) const
{
    double denominator(static_cast<double>(dividendFractionData.denominator) * divisorFractionData.numerator);
    double numerator(static_cast<double>(dividendFractionData.numerator) * divisorFractionData.denominator * getSign(denominator));
    denominator = getAbsoluteValue(denominator);
    shouldBeConvertedToDouble = isValueBeyondIntegerLimits(numerator) || isValueBeyondIntegerLimits(denominator);
    return AlbaNumber(getIntegerAfterRoundingDoubleValue(numerator), getIntegerAfterRoundingDoubleValue(denominator));
}

AlbaNumber AlbaNumber::raisePowerOfBothIntegersAndReturnNumber(
        bool & shouldBeConvertedToDouble,
        int const base,
        int const exponent) const
{
    AlbaNumber result;
    double baseRaiseToExponent(pow(base, getAbsoluteValue(exponent)));
    if(exponent<0)
    {
        shouldBeConvertedToDouble = isValueBeyondIntegerLimits(baseRaiseToExponent);
        result = AlbaNumber(1, getIntegerAfterRoundingDoubleValue(baseRaiseToExponent));
    }
    else
    {
        shouldBeConvertedToDouble = isValueBeyondIntegerLimits(baseRaiseToExponent);
        result = AlbaNumber(getIntegerAfterRoundingDoubleValue(baseRaiseToExponent));
    }
    return result;
}

AlbaNumber AlbaNumber::raisePowerOfFractionsAndIntegerAndReturnNumber(
        bool & shouldBeConvertedToDouble,
        AlbaNumber::FractionData const& baseFractionData,
        int const exponent) const
{
    AlbaNumber result;
    unsigned int absoluteValueOfExponent(static_cast<unsigned int>(getAbsoluteValue(exponent)));
    double previousNumeratorRaiseToExponent(pow(baseFractionData.numerator, absoluteValueOfExponent));
    double previousDenominatorRaiseToExponent(pow(baseFractionData.denominator, absoluteValueOfExponent));
    if(exponent<0)
    {
        double numerator(previousDenominatorRaiseToExponent * getSign(previousNumeratorRaiseToExponent));
        double denominator(getAbsoluteValue(previousNumeratorRaiseToExponent));
        shouldBeConvertedToDouble = isValueBeyondIntegerLimits(numerator) || isValueBeyondIntegerLimits(denominator);
        result = AlbaNumber(getIntegerAfterRoundingDoubleValue(numerator), getIntegerAfterRoundingDoubleValue(denominator));
    }
    else
    {
        double numerator(previousNumeratorRaiseToExponent);
        double denominator(previousDenominatorRaiseToExponent);
        shouldBeConvertedToDouble = isValueBeyondIntegerLimits(numerator) || isValueBeyondIntegerLimits(denominator);
        result = AlbaNumber(getIntegerAfterRoundingDoubleValue(numerator), getIntegerAfterRoundingDoubleValue(denominator));
    }
    return result;
}
ostream & operator<<(std::ostream & out, AlbaNumber const& number)
{
    out << number.getDisplayableString();    return out;
}


}
