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
    long long int& intDataReference(m_data.intData);
    intDataReference = 0;
}

AlbaNumber::AlbaNumber(int const integerValue)
    : m_type(Type::Integer)
{
    long long int& intDataReference(m_data.intData);
    intDataReference = integerValue;
}

AlbaNumber::AlbaNumber(unsigned int const integerValue)
    : m_type(Type::Integer)
{
    long long int& intDataReference(m_data.intData);
    intDataReference = integerValue;
}

AlbaNumber::AlbaNumber(long long int const integerValue)
    : m_type(Type::Integer)
{
    long long int& intDataReference(m_data.intData);
    intDataReference = integerValue;
}

AlbaNumber::AlbaNumber(int const numerator, int const denominator)
    : m_type(Type::Fraction)
{
    constructFraction(numerator, denominator);
}

AlbaNumber::AlbaNumber(int const numerator, unsigned int const denominator)
    : m_type(Type::Fraction)
{
    constructFraction(numerator, denominator);
}

AlbaNumber::AlbaNumber(double const doubleValue)
    : m_type(Type::Double)
{
    double& doubleDataReference(m_data.doubleData);
    doubleDataReference = doubleValue;
    convertToIntegerIfNeeded();
}

AlbaNumber::AlbaNumber(Value const value)
    : m_type(Type::Double)
{
    double& doubleDataReference(m_data.doubleData);
    switch(value)
    {
    case Value::PositiveInfinity:
        doubleDataReference = INFINITY;
        break;
    case Value::NegativeInfinity:
        doubleDataReference = -INFINITY;
        break;
    case Value::NotANumber:
        doubleDataReference = NAN;
        break;
    }
}

bool AlbaNumber::operator==(AlbaNumber const& second) const
{
    return isAlmostEqual(getDouble(), second.getDouble());
}

bool AlbaNumber::operator!=(AlbaNumber const& second) const
{
    return !operator==(second);
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
        long long int& intDataReference(result.m_data.intData);
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
        long long int const& intDataReference1(first.m_data.intData);
        long long int const& intDataReference2(second.m_data.intData);
        result = addBothIntegersAndReturnNumber(shouldBeConvertedToDouble, intDataReference1, intDataReference2);
    }
    else if(first.m_type == Type::Integer && second.m_type == Type::Fraction)
    {
        long long int const& intDataReference1(first.m_data.intData);
        FractionData const& fractionDataReference2(second.m_data.fractionData);
        result = addIntegerAndFractionAndReturnNumber(shouldBeConvertedToDouble, intDataReference1, fractionDataReference2);
    }
    else if(first.m_type == Type::Integer && second.m_type == Type::Double)
    {
        long long int const& intDataReference1(first.m_data.intData);
        double const& doubleDataReference2(second.m_data.doubleData);
        result = addIntegerAndDoubleAndReturnNumber(intDataReference1, doubleDataReference2);
    }
    else if(first.m_type == Type::Fraction && second.m_type == Type::Integer)
    {
        FractionData const& fractionDataReference1(first.m_data.fractionData);
        long long int const& intDataReference2(second.m_data.intData);
        result = addIntegerAndFractionAndReturnNumber(shouldBeConvertedToDouble, intDataReference2, fractionDataReference1);
    }
    else if(first.m_type == Type::Fraction && second.m_type == Type::Fraction)
    {
        FractionData const& fractionDataReference1(first.m_data.fractionData);
        FractionData const& fractionDataReference2(second.m_data.fractionData);
        result = addBothFractionsAndReturnNumber(shouldBeConvertedToDouble, fractionDataReference1, fractionDataReference2);
    }
    else if(first.m_type == Type::Fraction && second.m_type == Type::Double)
    {
        FractionData const& fractionDataReference1(first.m_data.fractionData);
        double const& doubleDataReference2(second.m_data.doubleData);
        result = addFractionAndDoubleAndReturnNumber(fractionDataReference1, doubleDataReference2);
    }
    else if(first.m_type == Type::Double && second.m_type == Type::Integer)
    {
        double const& doubleDataReference1(first.m_data.doubleData);
        long long int const& intDataReference2(second.m_data.intData);
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
    return operator+(-second);
}

AlbaNumber AlbaNumber::operator*(AlbaNumber const& value) const
{
    AlbaNumber first(*this);
    AlbaNumber second(value);

    AlbaNumber result(*this);
    bool shouldBeConvertedToDouble(false);
    if(first.m_type == Type::Integer && second.m_type == Type::Integer)
    {
        long long int const& intDataReference1(first.m_data.intData);
        long long int const& intDataReference2(second.m_data.intData);
        result = multiplyBothIntegersAndReturnNumber(shouldBeConvertedToDouble, intDataReference1, intDataReference2);
    }
    else if(first.m_type == Type::Integer && second.m_type == Type::Fraction)
    {
        long long int const& intDataReference1(first.m_data.intData);
        FractionData const& fractionDataReference2(second.m_data.fractionData);
        result = multiplyIntegerAndFractionAndReturnNumber(shouldBeConvertedToDouble, intDataReference1, fractionDataReference2);
    }
    else if(first.m_type == Type::Integer && second.m_type == Type::Double)
    {
        long long int const& intDataReference1(first.m_data.intData);
        double const& doubleDataReference2(second.m_data.doubleData);
        result = multiplyIntegerAndDoubleAndReturnNumber(intDataReference1, doubleDataReference2);
    }
    else if(first.m_type == Type::Fraction && second.m_type == Type::Integer)
    {
        FractionData const& fractionDataReference1(first.m_data.fractionData);
        long long int const& intDataReference2(second.m_data.intData);
        result = multiplyIntegerAndFractionAndReturnNumber(shouldBeConvertedToDouble, intDataReference2, fractionDataReference1);
    }
    else if(first.m_type == Type::Fraction && second.m_type == Type::Fraction)
    {
        FractionData const& fractionDataReference1(first.m_data.fractionData);
        FractionData const& fractionDataReference2(second.m_data.fractionData);
        result = multiplyBothFractionsAndReturnNumber(shouldBeConvertedToDouble, fractionDataReference1, fractionDataReference2);
    }
    else if(first.m_type == Type::Fraction && second.m_type == Type::Double)
    {
        FractionData const& fractionDataReference1(first.m_data.fractionData);
        double const& doubleDataReference2(second.m_data.doubleData);
        result = multiplyFractionAndDoubleAndReturnNumber(fractionDataReference1, doubleDataReference2);
    }
    else if(first.m_type == Type::Double && second.m_type == Type::Integer)
    {
        double const& doubleDataReference1(first.m_data.doubleData);
        long long int const& intDataReference2(second.m_data.intData);
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
        long long int const& intDataReference1(first.m_data.intData);
        long long int const& intDataReference2(second.m_data.intData);
        result = divideBothIntegersAndReturnNumber(shouldBeConvertedToDouble, intDataReference1, intDataReference2);
    }
    else if(first.m_type == Type::Integer && second.m_type == Type::Fraction)
    {
        long long int const& intDataReference1(first.m_data.intData);
        FractionData const& fractionDataReference2(second.m_data.fractionData);
        result = divideDividendsAndDivisorsAndReturnNumber(
                    shouldBeConvertedToDouble,
                    intDataReference1,
                    fractionDataReference2.denominator,
                    static_cast<long long int>(fractionDataReference2.numerator),
                    1);
    }
    else if(first.m_type == Type::Integer && second.m_type == Type::Double)
    {
        long long int const& intDataReference1(first.m_data.intData);
        double const& doubleDataReference2(second.m_data.doubleData);
        result = AlbaNumber(static_cast<double>(intDataReference1) / doubleDataReference2);
    }
    else if(first.m_type == Type::Fraction && second.m_type == Type::Integer)
    {
        FractionData const& fractionDataReference1(first.m_data.fractionData);
        long long int const& intDataReference2(second.m_data.intData);
        result = divideDividendsAndDivisorsAndReturnNumber(
                    shouldBeConvertedToDouble,
                    static_cast<long long int>(fractionDataReference1.numerator),
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
    {
        FractionData const& fractionDataReference1(first.m_data.fractionData);
        double const& doubleDataReference2(second.m_data.doubleData);
        result = AlbaNumber(
                    static_cast<double>(fractionDataReference1.numerator) /
                    fractionDataReference1.denominator /
                    doubleDataReference2);
    }
    else if(first.m_type == Type::Double && second.m_type == Type::Integer)
    {
        double const& doubleDataReference1(first.m_data.doubleData);
        long long int const& intDataReference2(second.m_data.intData);
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
        long long int const& intDataReference1(first.m_data.intData);
        long long int const& intDataReference2(second.m_data.intData);
        result = raisePowerOfBothIntegersAndReturnNumber(shouldBeConvertedToDouble, intDataReference1, intDataReference2);
    }
    else if(first.m_type == Type::Integer && second.m_type == Type::Fraction)
    {
        result = AlbaNumber(pow(getDouble(), second.getDouble()));
    }
    else if(first.m_type == Type::Integer && second.m_type == Type::Double)
    {
        result = AlbaNumber(pow(getDouble(), second.getDouble()));
    }
    else if(first.m_type == Type::Fraction && second.m_type == Type::Integer)
    {
        FractionData const& fractionDataReference1(first.m_data.fractionData);
        long long int const& intDataReference2(second.m_data.intData);
        result = raisePowerOfFractionsAndIntegerAndReturnNumber(shouldBeConvertedToDouble, fractionDataReference1, intDataReference2);
    }
    else if(first.m_type == Type::Fraction && second.m_type == Type::Fraction)
    {
        result = AlbaNumber(pow(getDouble(), second.getDouble()));
    }
    else if(first.m_type == Type::Fraction && second.m_type == Type::Double)
    {
        result = AlbaNumber(pow(getDouble(), second.getDouble()));
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

AlbaNumber AlbaNumber::operator+(int const integerValue) const
{
    return operator+(AlbaNumber(integerValue));
}

AlbaNumber AlbaNumber::operator-(int const integerValue) const
{
    return operator-(AlbaNumber(integerValue));
}

AlbaNumber AlbaNumber::operator*(int const integerValue) const
{
    return operator*(AlbaNumber(integerValue));
}

AlbaNumber AlbaNumber::operator/(int const integerValue) const
{
    return operator/(AlbaNumber(integerValue));
}

AlbaNumber AlbaNumber::operator^(int const integerValue) const
{
    return operator^(AlbaNumber(integerValue));
}

AlbaNumber AlbaNumber::operator+(unsigned int const integerValue) const
{
    return operator+(AlbaNumber(integerValue));
}

AlbaNumber AlbaNumber::operator-(unsigned int const integerValue) const
{
    return operator-(AlbaNumber(integerValue));
}

AlbaNumber AlbaNumber::operator*(unsigned int const integerValue) const
{
    return operator*(AlbaNumber(integerValue));
}

AlbaNumber AlbaNumber::operator/(unsigned int const integerValue) const
{
    return operator/(AlbaNumber(integerValue));
}

AlbaNumber AlbaNumber::operator^(unsigned int const integerValue) const
{
    return operator^(AlbaNumber(integerValue));
}

AlbaNumber AlbaNumber::operator+(long long int const integerValue) const
{
    return operator+(AlbaNumber(integerValue));
}

AlbaNumber AlbaNumber::operator-(long long int const integerValue) const
{
    return operator-(AlbaNumber(integerValue));
}

AlbaNumber AlbaNumber::operator*(long long int const integerValue) const
{
    return operator*(AlbaNumber(integerValue));
}

AlbaNumber AlbaNumber::operator/(long long int const integerValue) const
{
    return operator/(AlbaNumber(integerValue));
}

AlbaNumber AlbaNumber::operator^(long long int const integerValue) const
{
    return operator^(AlbaNumber(integerValue));
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

bool AlbaNumber::isPositiveInfinity() const
{
    return getDouble() == INFINITY;
}

bool AlbaNumber::isNegativeInfinity() const
{
    return getDouble() == -INFINITY;
}

bool AlbaNumber::isNotANumber() const
{
    return isnan(getDouble());
}

bool AlbaNumber::hasValidValue() const
{
    return !isPositiveInfinity() && !isNegativeInfinity() && !isNotANumber();
}

AlbaNumber::Type AlbaNumber::getType() const
{
    return m_type;
}

long long int AlbaNumber::getInteger() const
{
    long long int result(0);
    if(m_type==Type::Integer)
    {
        long long int const& dataReference(m_data.intData);
        result = dataReference;
    }
    else if(m_type==Type::Fraction)
    {
        FractionData const& dataReference(m_data.fractionData);
        result = getIntegerAfterRoundingDoubleValue<long long int>(
                    static_cast<double>(dataReference.numerator)/dataReference.denominator);
    }
    else if(m_type==Type::Double)
    {
        double const& dataReference(m_data.doubleData);
        result = getIntegerAfterRoundingDoubleValue<long long int>(dataReference);
    }
    return result;
}

AlbaNumber::FractionData AlbaNumber::getFractionData() const
{
    FractionData result{0, 0};
    if(m_type==Type::Integer)
    {
        long long int const& dataReference(m_data.intData);
        result.numerator = static_cast<int>(dataReference);
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
        long long int const& dataReference(m_data.intData);
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

unsigned int AlbaNumber::getNumberDataSize() const
{
    return sizeof(m_data);
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

template <typename NumberType1, typename NumberType2>
void AlbaNumber::constructFraction(NumberType1 const numerator, NumberType2 const denominator)
{
    if(denominator==0)
    {
        *this = AlbaNumber(static_cast<double>(numerator)/denominator);
    }
    else
    {
        FractionDetails fractionDetails(getFractionDetailsInLowestForm(numerator, denominator));
        FractionData& fractionDataReference(m_data.fractionData);
        fractionDataReference.numerator = fractionDetails.sign * fractionDetails.numerator;
        fractionDataReference.denominator = fractionDetails.denominator;
        convertToIntegerIfNeeded();
    }
}
template void AlbaNumber::constructFraction<int, int>(int const numerator, int const denominator);
template void AlbaNumber::constructFraction<int, unsigned int>(int const numerator, unsigned int const denominator);

void AlbaNumber::convertToIntegerIfNeeded()
{
    if(m_type == Type::Fraction)
    {
        FractionData const& fractionDataReference(m_data.fractionData);
        if(isDivisible(
                    static_cast<unsigned int>(getAbsoluteValue(fractionDataReference.numerator)),
                    fractionDataReference.denominator))
        {
            *this = AlbaNumber(
                        getIntegerAfterRoundingDoubleValue<long long int>(
                            static_cast<double>(fractionDataReference.numerator)/fractionDataReference.denominator));
        }
    }
    else if(m_type == Type::Double)
    {
        double realValue(getDouble());
        if(!isValueBeyondLimits<long long int>(realValue) && isAlmostAnInteger<long long int>(realValue))
        {
            *this = AlbaNumber(getIntegerAfterRoundingDoubleValue<long long int>(realValue));
        }
    }
}

AlbaNumber AlbaNumber::addBothIntegersAndReturnNumber(
        bool & shouldBeConvertedToDouble,
        long long int const integerValue1,
        long long int const integerValue2) const
{
    shouldBeConvertedToDouble
            = isValueBeyondLimits<long long int>(static_cast<double>(integerValue1) + integerValue2);
    return AlbaNumber(integerValue1 + integerValue2);
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
    shouldBeConvertedToDouble = isValueBeyondLimits<int>(numeratorResult) || isValueBeyondLimits<unsigned int>(lcm);
    return AlbaNumber(
                getIntegerAfterRoundingDoubleValue<int>(numeratorResult),
                getIntegerAfterRoundingDoubleValue<unsigned int>(lcm));
}

AlbaNumber AlbaNumber::addBothDoubleAndReturnNumber(
        double const doubleValue1,
        double const doubleValue2) const
{
    return AlbaNumber(doubleValue1 + doubleValue2);
}

AlbaNumber AlbaNumber::addIntegerAndFractionAndReturnNumber(
        bool & shouldBeConvertedToDouble,
        long long int const integerValue,
        FractionData const& fractionData) const
{
    double numerator((static_cast<double>(fractionData.denominator)*integerValue) + fractionData.numerator);
    shouldBeConvertedToDouble = isValueBeyondLimits<int>(numerator);
    return AlbaNumber(getIntegerAfterRoundingDoubleValue<int>(numerator), fractionData.denominator);
}

AlbaNumber AlbaNumber::addIntegerAndDoubleAndReturnNumber(
        long long int const integerValue,
        double const doubleValue) const
{
    return AlbaNumber(static_cast<double>(integerValue + doubleValue));
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
        long long int const integerValue1,
        long long int const integerValue2) const
{
    shouldBeConvertedToDouble
            = isValueBeyondLimits<long long int>(static_cast<double>(integerValue1) * integerValue2);
    return AlbaNumber(integerValue1 * integerValue2);
}

AlbaNumber AlbaNumber::multiplyBothFractionsAndReturnNumber(
        bool & shouldBeConvertedToDouble,
        AlbaNumber::FractionData const& fractionData1,
        AlbaNumber::FractionData const& fractionData2) const
{
    double numerator(static_cast<double>(fractionData1.numerator) * fractionData2.numerator);
    double denominator(static_cast<double>(fractionData1.denominator) * fractionData2.denominator);
    shouldBeConvertedToDouble = isValueBeyondLimits<int>(numerator) || isValueBeyondLimits<unsigned int>(denominator);
    return AlbaNumber(
                getIntegerAfterRoundingDoubleValue<int>(numerator),
                getIntegerAfterRoundingDoubleValue<unsigned int>(denominator));
}

AlbaNumber AlbaNumber::multiplyBothDoubleAndReturnNumber(double const doubleValue1, double const doubleValue2) const
{
    return AlbaNumber(doubleValue1 * doubleValue2);
}

AlbaNumber AlbaNumber::multiplyIntegerAndFractionAndReturnNumber(
        bool & shouldBeConvertedToDouble,
        long long int const integerValue,
        FractionData const& fractionData) const
{
    double numerator(static_cast<double>(integerValue) * fractionData.numerator);
    shouldBeConvertedToDouble = isValueBeyondLimits<int>(numerator);
    return AlbaNumber(getIntegerAfterRoundingDoubleValue<int>(numerator), fractionData.denominator);
}

AlbaNumber AlbaNumber::multiplyIntegerAndDoubleAndReturnNumber(
        long long int const integerValue,
        double const doubleValue) const
{
    return AlbaNumber(static_cast<double>(integerValue) * doubleValue);
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
        long long int const dividend,
        long long int const divisor) const
{
    shouldBeConvertedToDouble
            = isValueBeyondLimits<int>(static_cast<double>(dividend))
            || isValueBeyondLimits<int>(static_cast<double>(divisor));
    FractionDetails fractionDetails(
                getFractionDetailsInLowestForm(
                    static_cast<int>(dividend),
                    static_cast<int>(divisor)));
    return AlbaNumber(fractionDetails.sign * fractionDetails.numerator, fractionDetails.denominator);
}

AlbaNumber AlbaNumber::divideDividendsAndDivisorsAndReturnNumber(
        bool & shouldBeConvertedToDouble,
        long long int const dividendInteger,
        unsigned int const dividendUnsignedInteger,
        long long int const divisorInteger,
        unsigned int const divisorUnsignedInteger) const
{
    double numerator(static_cast<double>(dividendInteger) * dividendUnsignedInteger);
    double denominator(static_cast<double>(divisorInteger) * divisorUnsignedInteger);
    shouldBeConvertedToDouble = isValueBeyondLimits<int>(numerator) || isValueBeyondLimits<int>(denominator);
    return AlbaNumber(
                getIntegerAfterRoundingDoubleValue<int>(numerator),
                getIntegerAfterRoundingDoubleValue<int>(denominator));
}

AlbaNumber AlbaNumber::divideBothFractionsAndReturnNumber(
        bool & shouldBeConvertedToDouble,
        AlbaNumber::FractionData const& dividendFractionData,
        AlbaNumber::FractionData const& divisorFractionData) const
{
    double denominator(static_cast<double>(dividendFractionData.denominator) * divisorFractionData.numerator);
    double numerator(static_cast<double>(dividendFractionData.numerator) * divisorFractionData.denominator * getSign(denominator));
    denominator = getAbsoluteValue(denominator);
    shouldBeConvertedToDouble = isValueBeyondLimits<int>(numerator) || isValueBeyondLimits<int>(denominator);
    return AlbaNumber(
                getIntegerAfterRoundingDoubleValue<int>(numerator),
                getIntegerAfterRoundingDoubleValue<int>(denominator));
}

AlbaNumber AlbaNumber::raisePowerOfBothIntegersAndReturnNumber(
        bool & shouldBeConvertedToDouble,
        long long int const base,
        long long int const exponent) const
{
    AlbaNumber result;
    double baseRaiseToExponent(pow(base, getAbsoluteValue(exponent)));
    if(exponent<0)
    {
        shouldBeConvertedToDouble = isValueBeyondLimits<int>(baseRaiseToExponent);
        result = AlbaNumber(1, getIntegerAfterRoundingDoubleValue<int>(baseRaiseToExponent));
    }
    else
    {
        shouldBeConvertedToDouble = isValueBeyondLimits<long long int>(baseRaiseToExponent);
        result = AlbaNumber(getIntegerAfterRoundingDoubleValue<long long int>(baseRaiseToExponent));
    }
    return result;
}

AlbaNumber AlbaNumber::raisePowerOfFractionsAndIntegerAndReturnNumber(
        bool & shouldBeConvertedToDouble,
        AlbaNumber::FractionData const& baseFractionData,
        long long int const exponent) const
{
    AlbaNumber result;
    unsigned long long int absoluteValueOfExponent(static_cast<unsigned long long int>(getAbsoluteValue(exponent)));
    double previousNumeratorRaiseToExponent(pow(baseFractionData.numerator, absoluteValueOfExponent));
    double previousDenominatorRaiseToExponent(pow(baseFractionData.denominator, absoluteValueOfExponent));
    if(exponent<0)
    {
        double numerator(previousDenominatorRaiseToExponent * getSign(previousNumeratorRaiseToExponent));
        double denominator(getAbsoluteValue(previousNumeratorRaiseToExponent));
        shouldBeConvertedToDouble = isValueBeyondLimits<int>(numerator) || isValueBeyondLimits<unsigned int>(denominator);
        result = AlbaNumber(
                    getIntegerAfterRoundingDoubleValue<int>(numerator),
                    getIntegerAfterRoundingDoubleValue<unsigned int>(denominator));
    }
    else
    {
        double numerator(previousNumeratorRaiseToExponent);
        double denominator(previousDenominatorRaiseToExponent);
        shouldBeConvertedToDouble = isValueBeyondLimits<int>(numerator) || isValueBeyondLimits<unsigned int>(denominator);
        result = AlbaNumber(
                    getIntegerAfterRoundingDoubleValue<int>(numerator),
                    getIntegerAfterRoundingDoubleValue<unsigned int>(denominator));
    }
    return result;
}

ostream & operator<<(ostream & out, AlbaNumber const& number)
{
    out << number.getDisplayableString();
    return out;
}


}
