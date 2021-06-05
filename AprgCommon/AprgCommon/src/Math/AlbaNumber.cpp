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
{    int& intDataReference(m_data.intData);
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

AlbaNumber::AlbaNumber(int const numerator, unsigned int const denominator)
    : m_type(Type::Fraction)
{
    FractionDetails fractionDetails(getFractionDetailsInLowestForm(numerator, denominator));
    FractionData& fractionDataReference(m_data.fractionData);
    fractionDataReference.numerator = fractionDetails.sign*fractionDetails.numerator;
    fractionDataReference.denominator = static_cast<int>(fractionDetails.denominator);
    convertToIntegerIfNeeded();
}

AlbaNumber::AlbaNumber(double const doubleValue)
    : m_type(Type::Double)
{
    double& doubleDataReference(m_data.doubleData);
    doubleDataReference = doubleValue;
}

bool AlbaNumber::operator==(AlbaNumber const& second) const
{
    return isAlmostEqual(getDouble(), second.getDouble());}

bool AlbaNumber::operator!=(AlbaNumber const& second) const
{    AlbaNumber const& first(*this);
    return !(first==second);
}

bool AlbaNumber::operator<(AlbaNumber const& second) const
{
    return getDouble() < second.getDouble();
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

AlbaNumber AlbaNumber::operator+(AlbaNumber const& second) const
{
    AlbaNumber result;
    if(m_type == Type::Integer && second.m_type == Type::Integer)
    {
        int const& intDataReference1(m_data.intData);
        int const& intDataReference2(second.m_data.intData);
        result = addBothIntegersAndReturnNumber(intDataReference1, intDataReference2);
    }
    else if(m_type == Type::Integer && second.m_type == Type::Fraction)
    {
        int const& intDataReference1(m_data.intData);
        FractionData const& fractionDataReference2(second.m_data.fractionData);
        result = addIntegerAndFractionAndReturnNumber(intDataReference1, fractionDataReference2);
    }
    else if(m_type == Type::Integer && second.m_type == Type::Double)
    {
        int const& intDataReference1(m_data.intData);
        double const& doubleDataReference2(second.m_data.doubleData);
        result = addIntegerAndDoubleAndReturnNumber(intDataReference1, doubleDataReference2);
    }
    else if(m_type == Type::Fraction && second.m_type == Type::Integer)
    {
        FractionData const& fractionDataReference1(m_data.fractionData);
        int const& intDataReference2(second.m_data.intData);
        result = addIntegerAndFractionAndReturnNumber(intDataReference2, fractionDataReference1);
    }
    else if(m_type == Type::Fraction && second.m_type == Type::Fraction)
    {
        FractionData const& fractionDataReference1(m_data.fractionData);
        FractionData const& fractionDataReference2(second.m_data.fractionData);
        result = addBothFractionsAndReturnNumber(fractionDataReference1, fractionDataReference2);
    }
    else if(m_type == Type::Fraction && second.m_type == Type::Double)
    {
        FractionData const& fractionDataReference1(m_data.fractionData);
        double const& doubleDataReference2(second.m_data.doubleData);
        result = addFractionAndDoubleAndReturnNumber(fractionDataReference1, doubleDataReference2);
    }
    else if(m_type == Type::Double && second.m_type == Type::Integer)
    {
        double const& doubleDataReference1(m_data.doubleData);
        int const& intDataReference2(second.m_data.intData);
        result = addIntegerAndDoubleAndReturnNumber(intDataReference2, doubleDataReference1);
    }
    else if(m_type == Type::Double && second.m_type == Type::Fraction)
    {
        double const& doubleDataReference1(m_data.doubleData);
        FractionData const& fractionDataReference2(second.m_data.fractionData);
        result = addFractionAndDoubleAndReturnNumber(fractionDataReference2, doubleDataReference1);
    }
    else if(m_type == Type::Double && second.m_type == Type::Double)
    {
        double const& doubleDataReference1(m_data.doubleData);
        double const& doubleDataReference2(second.m_data.doubleData);
        result = addBothDoubleAndReturnNumber(doubleDataReference1, doubleDataReference2);
    }
    return result;
}

AlbaNumber AlbaNumber::operator-(AlbaNumber const& second) const
{
    return operator+(-second);
}

AlbaNumber AlbaNumber::operator*(AlbaNumber const& second) const
{
    AlbaNumber result(*this);
    if(m_type == Type::Integer && second.m_type == Type::Integer)
    {
        int const& intDataReference1(m_data.intData);
        int const& intDataReference2(second.m_data.intData);
        result = multiplyBothIntegersAndReturnNumber(intDataReference1, intDataReference2);
    }
    else if(m_type == Type::Integer && second.m_type == Type::Fraction)
    {
        int const& intDataReference1(m_data.intData);
        FractionData const& fractionDataReference2(second.m_data.fractionData);
        result = multiplyIntegerAndFractionAndReturnNumber(intDataReference1, fractionDataReference2);
    }
    else if(m_type == Type::Integer && second.m_type == Type::Double)
    {
        int const& intDataReference1(m_data.intData);
        double const& doubleDataReference2(second.m_data.doubleData);
        result = multiplyIntegerAndDoubleAndReturnNumber(intDataReference1, doubleDataReference2);
    }
    else if(m_type == Type::Fraction && second.m_type == Type::Integer)
    {
        FractionData const& fractionDataReference1(m_data.fractionData);
        int const& intDataReference2(second.m_data.intData);
        result = multiplyIntegerAndFractionAndReturnNumber(intDataReference2, fractionDataReference1);
    }
    else if(m_type == Type::Fraction && second.m_type == Type::Fraction)
    {
        FractionData const& fractionDataReference1(m_data.fractionData);
        FractionData const& fractionDataReference2(second.m_data.fractionData);
        result = multiplyBothFractionsAndReturnNumber(fractionDataReference1, fractionDataReference2);
    }
    else if(m_type == Type::Fraction && second.m_type == Type::Double)
    {
        FractionData const& fractionDataReference1(m_data.fractionData);
        double const& doubleDataReference2(second.m_data.doubleData);
        result = multiplyFractionAndDoubleAndReturnNumber(fractionDataReference1, doubleDataReference2);
    }
    else if(m_type == Type::Double && second.m_type == Type::Integer)
    {
        double const& doubleDataReference1(m_data.doubleData);
        int const& intDataReference2(second.m_data.intData);
        result = multiplyIntegerAndDoubleAndReturnNumber(intDataReference2, doubleDataReference1);
    }
    else if(m_type == Type::Double && second.m_type == Type::Fraction)
    {
        double const& doubleDataReference1(m_data.doubleData);
        FractionData const& fractionDataReference2(second.m_data.fractionData);
        result = multiplyFractionAndDoubleAndReturnNumber(fractionDataReference2, doubleDataReference1);
    }
    else if(m_type == Type::Double && second.m_type == Type::Double)
    {
        double const& doubleDataReference1(m_data.doubleData);
        double const& doubleDataReference2(second.m_data.doubleData);
        result = multiplyBothDoubleAndReturnNumber(doubleDataReference1, doubleDataReference2);
    }
    return result;
}

AlbaNumber AlbaNumber::operator/(AlbaNumber const& second) const
{
    AlbaNumber result(*this);
    if(m_type == Type::Integer && second.m_type == Type::Integer)
    {
        int const& intDataReference1(m_data.intData);
        int const& intDataReference2(second.m_data.intData);
        result = divideBothIntegersAndReturnNumber(intDataReference1, intDataReference2);
    }
    else if(m_type == Type::Integer && second.m_type == Type::Fraction)
    {
        int const& intDataReference1(m_data.intData);
        FractionData const& fractionDataReference2(second.m_data.fractionData);
        result = divideBothIntegersAndReturnNumber(
                    intDataReference1 * static_cast<int>(fractionDataReference2.denominator),
                    fractionDataReference2.numerator);
    }
    else if(m_type == Type::Integer && second.m_type == Type::Double)
    {
        int const& intDataReference1(m_data.intData);
        double const& doubleDataReference2(second.m_data.doubleData);
        result = AlbaNumber(static_cast<double>(intDataReference1) / doubleDataReference2);
    }
    else if(m_type == Type::Fraction && second.m_type == Type::Integer)
    {
        FractionData const& fractionDataReference1(m_data.fractionData);
        int const& intDataReference2(second.m_data.intData);
        result = divideBothIntegersAndReturnNumber(
                    fractionDataReference1.numerator,
                    intDataReference2 * static_cast<int>(fractionDataReference1.denominator));
    }
    else if(m_type == Type::Fraction && second.m_type == Type::Fraction)
    {
        FractionData const& fractionDataReference1(m_data.fractionData);
        FractionData const& fractionDataReference2(second.m_data.fractionData);
        result = divideBothFractionsAndReturnNumber(fractionDataReference1, fractionDataReference2);
    }
    else if(m_type == Type::Fraction && second.m_type == Type::Double)
    {
        FractionData const& fractionDataReference1(m_data.fractionData);
        double const& doubleDataReference2(second.m_data.doubleData);
        result = AlbaNumber(
                    static_cast<double>(fractionDataReference1.numerator) /
                    fractionDataReference1.denominator /
                    doubleDataReference2);
    }
    else if(m_type == Type::Double && second.m_type == Type::Integer)
    {
        double const& doubleDataReference1(m_data.doubleData);
        int const& intDataReference2(second.m_data.intData);
        result = AlbaNumber(doubleDataReference1 / intDataReference2);
    }
    else if(m_type == Type::Double && second.m_type == Type::Fraction)
    {
        double const& doubleDataReference1(m_data.doubleData);
        FractionData const& fractionDataReference2(second.m_data.fractionData);
        result = AlbaNumber(
                    doubleDataReference1 *
                    fractionDataReference2.denominator /
                    fractionDataReference2.numerator);
    }
    else if(m_type == Type::Double && second.m_type == Type::Double)
    {
        double const& doubleDataReference1(m_data.doubleData);
        double const& doubleDataReference2(second.m_data.doubleData);
        result = AlbaNumber(doubleDataReference1 / doubleDataReference2);
    }
    return result;
}

AlbaNumber AlbaNumber::operator^(AlbaNumber const& second) const
{
    AlbaNumber result(*this);
    if(m_type == Type::Integer && second.m_type == Type::Integer)
    {
        int const& intDataReference1(m_data.intData);
        int const& intDataReference2(second.m_data.intData);
        result = raisePowerOfBothIntegersAndReturnNumber(intDataReference1, intDataReference2);
    }
    else if(m_type == Type::Integer && second.m_type == Type::Fraction)
    {
        result = AlbaNumber(pow(getDouble(), second.getDouble()));
    }
    else if(m_type == Type::Integer && second.m_type == Type::Double)
    {
        result = AlbaNumber(pow(getDouble(), second.getDouble()));
    }
    else if(m_type == Type::Fraction && second.m_type == Type::Integer)
    {
        FractionData const& fractionDataReference1(m_data.fractionData);
        int const& intDataReference2(second.m_data.intData);
        result = raisePowerOfFractionsAndIntegerAndReturnNumber(fractionDataReference1, intDataReference2);
    }
    else if(m_type == Type::Fraction && second.m_type == Type::Fraction)
    {
        result = AlbaNumber(pow(getDouble(), second.getDouble()));
    }
    else if(m_type == Type::Fraction && second.m_type == Type::Double)
    {
        result = AlbaNumber(pow(getDouble(), second.getDouble()));
    }
    else if(m_type == Type::Double && second.m_type == Type::Integer)
    {
        result = AlbaNumber(pow(getDouble(), second.getDouble()));
    }
    else if(m_type == Type::Double && second.m_type == Type::Fraction)
    {
        result = AlbaNumber(pow(getDouble(), second.getDouble()));
    }
    else if(m_type == Type::Double && second.m_type == Type::Double)
    {
        result = AlbaNumber(pow(getDouble(), second.getDouble()));
    }
    return result;
}

AlbaNumber AlbaNumber::operator+(int const signedValue) const
{
    return operator+(AlbaNumber(signedValue));
}

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
        result = static_cast<int>(dataReference.numerator/dataReference.denominator);
    }
    else if(m_type==Type::Double)
    {
        double const& dataReference(m_data.doubleData);
        result = static_cast<int>(dataReference);
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

std::string AlbaNumber::getDisplayableString() const
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
        result.precision(10);
        result << getDouble();
    }
    return result.str();
}

void AlbaNumber::convertToIntegerIfNeeded()
{
    if(m_type == Type::Fraction)    {
        FractionData& fractionDataReference(m_data.fractionData);
        if(isDivisible(getAbsoluteValue(fractionDataReference.numerator), fractionDataReference.denominator))
        {            *this = AlbaNumber(static_cast<int>(fractionDataReference.numerator/fractionDataReference.denominator));
        }
    }
}

AlbaNumber AlbaNumber::addBothIntegersAndReturnNumber(int const signedValue1, int const signedValue2) const
{
    return AlbaNumber(signedValue1 + signedValue2);
}

AlbaNumber AlbaNumber::addBothFractionsAndReturnNumber(AlbaNumber::FractionData const& fractionData1, AlbaNumber::FractionData const& fractionData2) const
{
    unsigned int lcm(getLeastCommonMultiple(fractionData1.denominator, fractionData2.denominator));
    int numeratorResult =
            ((lcm/fractionData1.denominator)*fractionData1.numerator) +
            ((lcm/fractionData2.denominator)*fractionData2.numerator);
    return AlbaNumber(numeratorResult, lcm);
}

AlbaNumber AlbaNumber::addBothDoubleAndReturnNumber(double const doubleValue1, double const doubleValue2) const
{
    return AlbaNumber(doubleValue1 + doubleValue2);
}

AlbaNumber AlbaNumber::addIntegerAndFractionAndReturnNumber(int const signedValue, FractionData const& fractionData) const
{
    unsigned int denominator(fractionData.denominator);
    int numerator(fractionData.numerator + (fractionData.denominator*signedValue));
    return AlbaNumber(numerator, denominator);
}

AlbaNumber AlbaNumber::addIntegerAndDoubleAndReturnNumber(int const signedValue, double const doubleValue) const
{
    return AlbaNumber(static_cast<double>(signedValue + doubleValue));
}

AlbaNumber AlbaNumber::addFractionAndDoubleAndReturnNumber(FractionData const& fractionData, double const doubleValue) const
{
    return AlbaNumber(
                static_cast<double>(
                    static_cast<double>(fractionData.numerator)/fractionData.denominator +
                    doubleValue));
}

AlbaNumber AlbaNumber::multiplyBothIntegersAndReturnNumber(int const signedValue1, int const signedValue2) const
{
    return AlbaNumber(signedValue1 * signedValue2);
}

AlbaNumber AlbaNumber::multiplyBothFractionsAndReturnNumber(AlbaNumber::FractionData const& fractionData1, AlbaNumber::FractionData const& fractionData2) const
{
    return AlbaNumber((fractionData1.numerator * fractionData2.numerator),
                      (fractionData1.denominator * fractionData2.denominator));
}

AlbaNumber AlbaNumber::multiplyBothDoubleAndReturnNumber(double const doubleValue1, double const doubleValue2) const
{
    return AlbaNumber(doubleValue1 * doubleValue2);
}

AlbaNumber AlbaNumber::multiplyIntegerAndFractionAndReturnNumber(int const signedValue, FractionData const& fractionData) const
{
    return AlbaNumber((signedValue * fractionData.numerator),
                      (fractionData.denominator));
}

AlbaNumber AlbaNumber::multiplyIntegerAndDoubleAndReturnNumber(int const signedValue, double const doubleValue) const
{
    return AlbaNumber(static_cast<double>(signedValue * doubleValue));
}

AlbaNumber AlbaNumber::multiplyFractionAndDoubleAndReturnNumber(FractionData const& fractionData, double const doubleValue) const
{
    return AlbaNumber(
                static_cast<double>(
                    static_cast<double>(fractionData.numerator)/fractionData.denominator *
                    doubleValue));
}

AlbaNumber AlbaNumber::divideBothIntegersAndReturnNumber(int const dividend, int const divisor) const
{
    FractionDetails fractionDetails(getFractionDetailsInLowestForm(dividend, divisor));
    return AlbaNumber(
                fractionDetails.sign*fractionDetails.numerator,
                fractionDetails.denominator);
}

AlbaNumber AlbaNumber::divideBothFractionsAndReturnNumber(
        AlbaNumber::FractionData const& dividendFractionData,
        AlbaNumber::FractionData const& divisorFractionData) const
{
    return AlbaNumber((dividendFractionData.numerator * divisorFractionData.denominator),
                      (dividendFractionData.denominator * divisorFractionData.numerator));
}

AlbaNumber AlbaNumber::raisePowerOfBothIntegersAndReturnNumber(int const base, int const exponent) const
{
    AlbaNumber result;
    if(exponent<0)
    {
        result = AlbaNumber(1, getRaiseToPowerForIntegers(base, static_cast<unsigned int>(getAbsoluteValue(exponent))));
    }
    else
    {
        result = AlbaNumber(getRaiseToPowerForIntegers(base, static_cast<unsigned int>(exponent)));
    }
    return result;
}

AlbaNumber AlbaNumber::raisePowerOfFractionsAndIntegerAndReturnNumber(AlbaNumber::FractionData const& baseFractionData, int const exponent) const
{
    AlbaNumber result;
    if(exponent<0)
    {
        unsigned int absoluteValueOfExponent(static_cast<unsigned int>(getAbsoluteValue(exponent)));
        int sign(getSign(baseFractionData.numerator));
        result = AlbaNumber(
                    getRaiseToPowerForIntegers((sign*baseFractionData.denominator), absoluteValueOfExponent),
                    getRaiseToPowerForIntegers(getAbsoluteValue(baseFractionData.numerator), absoluteValueOfExponent));
    }
    else
    {
        result = AlbaNumber(
                    getRaiseToPowerForIntegers(baseFractionData.numerator, static_cast<unsigned int>(exponent)),
                    getRaiseToPowerForIntegers(baseFractionData.denominator, static_cast<unsigned int>(exponent)));
    }
    return result;
}


}
