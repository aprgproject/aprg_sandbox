#include "AlbaNumber.hpp"

#include <Common/Math/Helpers/ComplexNumberHelpers.hpp>
#include <Common/Math/Helpers/DivisibilityHelpers.hpp>
#include <Common/Math/Helpers/FactorAndMulitplesHelpers.hpp>
#include <Common/Math/Helpers/FractionHelpers.hpp>
#include <Common/Math/Helpers/PowerHelpers.hpp>
#include <Common/Math/Number/AlbaComplexNumber.hpp>

#include <cmath>

using namespace alba::AlbaMathConstants;
using namespace alba::mathHelper;
using namespace std;

namespace alba
{

AlbaNumber::ConfigurationDetails AlbaNumber::Configuration::getConfigurationDetailsWithZeroTolerance()
{
    return ConfigurationDetails{0.0, 0.0};
}

void AlbaNumber::Configuration::setConfigurationTolerancesToZero()
{
    setConfigurationDetails(getConfigurationDetailsWithZeroTolerance());
}

void AlbaNumber::Configuration::setComparisonTolerance(double const comparisonTolerance)
{
    m_configurationDetails.comparisonTolerance = comparisonTolerance;
}

void AlbaNumber::Configuration::setFloatAdjustmentTolerance(double const comparisonTolerance)
{
    m_configurationDetails.floatAdjustmentTolerance = comparisonTolerance;
}

void AlbaNumber::ScopeConfigurationObject::setInThisScopeTheTolerancesToZero() const
{
    Configuration::getInstance().setConfigurationDetails(Configuration::getConfigurationDetailsWithZeroTolerance());
}

inline AlbaNumber AlbaNumber::createInteger(long long int const integer)
{
    return AlbaNumber(integer);
}

inline AlbaNumber AlbaNumber::createDouble(double const doubleValue)
{
    return AlbaNumber(doubleValue);
}

AlbaNumber AlbaNumber::createNumberFromDoubleAndRoundIfNeeded(double const doubleValue)
{
    if(isValueWithinLimits<long long int>(doubleValue)
            && isAlmostAnInteger(doubleValue, getComparisonTolerance()))
    {
        return createInteger(getIntegerAfterRoundingADoubleValue<long long int>(doubleValue));
    }
    else
    {
        return createDouble(doubleValue);
    }
}

AlbaNumber AlbaNumber::createFraction(int const numerator, int const denominator)
{
    if(denominator==0)
    {
        return createNumberFromDoubleAndRoundIfNeeded(static_cast<double>(numerator)/denominator);
    }
    else if(isDivisible(numerator, denominator))
    {
        return createInteger(static_cast<long long int>(numerator)/denominator);
    }
    else
    {
        int newNumerator = numerator, newDenominator = denominator;
        changeFractionToSimplestFormForSigned(newNumerator, newDenominator);
        return AlbaNumber(FractionData{newNumerator, static_cast<unsigned int>(newDenominator)});
    }
}

AlbaNumber AlbaNumber::createFraction(int const numerator, unsigned int const denominator)
{
    if(denominator==0)
    {
        return createNumberFromDoubleAndRoundIfNeeded(static_cast<double>(numerator)/denominator);
    }
    else if(isDivisible(static_cast<unsigned int>(getAbsoluteValue(numerator)), denominator))
    {
        return createInteger(static_cast<long long int>(numerator)/denominator);
    }
    else
    {
        int newNumerator = numerator; unsigned int newDenominator = denominator;
        changeFractionToSimplestForm<int, unsigned int, long long int>(newNumerator, newDenominator);
        return AlbaNumber(FractionData{newNumerator, newDenominator});
    }
}


template <typename NumberType>
AlbaNumber AlbaNumber::createComplexNumber(NumberType const realPart, NumberType const imaginaryPart)
{
    double adjustedRealPart = adjustFloatValue(realPart);
    double adjustedImaginaryPart = adjustFloatValue(imaginaryPart);
    if(isinf(adjustedRealPart)
            || isnan(adjustedRealPart)
            || isAlmostEqual(adjustedImaginaryPart, 0.0, getComparisonTolerance()))
    {
        return createNumberFromDoubleAndRoundIfNeeded(static_cast<double>(adjustedRealPart));
    }
    else
    {
        return AlbaNumber(ComplexNumberData{static_cast<float>(adjustedRealPart), static_cast<float>(adjustedImaginaryPart)});
    }
}
template AlbaNumber AlbaNumber::createComplexNumber<int>(int const realPart, int const imaginaryPart);
template AlbaNumber AlbaNumber::createComplexNumber<float>(float const realPart, float const imaginaryPart);
template AlbaNumber AlbaNumber::createComplexNumber<double>(double const realPart, double const imaginaryPart);


AlbaNumber AlbaNumber::createComplexNumber(ComplexFloat const& complexNumber)
{
    return createComplexNumber(complexNumber.getRealPart(), complexNumber.getImaginaryPart());
}

bool AlbaNumber::operator==(AlbaNumber const& second) const
{
    bool result(false);
    if(!isComplexNumberType() && !second.isComplexNumberType())
    {
        result = isAlmostEqual(getDouble(), second.getDouble(), getComparisonTolerance());
    }
    else if(isComplexNumberType() && second.isComplexNumberType())
    {
        result = createComplexFloat(m_data.complexNumberData)
                == createComplexFloat(second.m_data.complexNumberData);
    }
    return result;
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
        result.m_data.intData = -result.m_data.intData;
    }
    else if(result.m_type == Type::Double)
    {
        result.m_data.doubleData = -result.m_data.doubleData;
    }
    else if(result.m_type == Type::Fraction)
    {
        result.m_data.fractionData.numerator = -result.m_data.fractionData.numerator;
    }
    else if(result.m_type == Type::ComplexNumber)
    {
        saveToComplexNumberData(
                    result.m_data.complexNumberData,
                    -createComplexFloat(result.m_data.complexNumberData));
    }
    return result;
}

AlbaNumber AlbaNumber::operator+(AlbaNumber const& second) const
{
    AlbaNumber const& first(*this);

    AlbaNumber result;
    if(first.m_type == Type::Integer && second.m_type == Type::Integer)
    {
        result = addBothIntegersAndReturnNumber(first.m_data.intData, second.m_data.intData);
    }
    else if(first.m_type == Type::Integer && second.m_type == Type::Double)
    {
        result = addIntegerAndDoubleAndReturnNumber(first.m_data.intData, second.m_data.doubleData);
    }
    else if(first.m_type == Type::Integer && second.m_type == Type::Fraction)
    {
        result = addIntegerAndFractionAndReturnNumber(first.m_data.intData, second.m_data.fractionData);
    }
    else if(first.m_type == Type::Integer && second.m_type == Type::ComplexNumber)
    {
        result = createComplexNumber(ComplexFloat(first.m_data.intData, 0) + createComplexFloat(second.m_data.complexNumberData));
    }
    else if(first.m_type == Type::Double && second.m_type == Type::Integer)
    {
        result = addIntegerAndDoubleAndReturnNumber(second.m_data.intData, first.m_data.doubleData);
    }
    else if(first.m_type == Type::Double && second.m_type == Type::Double)
    {
        result = addBothDoubleAndReturnNumber(first.m_data.doubleData, second.m_data.doubleData);
    }
    else if(first.m_type == Type::Double && second.m_type == Type::Fraction)
    {
        result = addFractionAndDoubleAndReturnNumber(second.m_data.fractionData, first.m_data.doubleData);
    }
    else if(first.m_type == Type::Double && second.m_type == Type::ComplexNumber)
    {
        result = createComplexNumber(ComplexFloat(first.m_data.doubleData, 0) + createComplexFloat(second.m_data.complexNumberData));
    }
    else if(first.m_type == Type::Fraction && second.m_type == Type::Integer)
    {
        result = addIntegerAndFractionAndReturnNumber(second.m_data.intData, first.m_data.fractionData);
    }
    else if(first.m_type == Type::Fraction && second.m_type == Type::Double)
    {
        result = addFractionAndDoubleAndReturnNumber(first.m_data.fractionData, second.m_data.doubleData);
    }
    else if(first.m_type == Type::Fraction && second.m_type == Type::Fraction)
    {
        result = addBothFractionsAndReturnNumber(first.m_data.fractionData, second.m_data.fractionData);
    }
    else if(first.m_type == Type::Fraction && second.m_type == Type::ComplexNumber)
    {
        result = createComplexNumber(ComplexFloat(first.getDouble(), 0) + createComplexFloat(second.m_data.complexNumberData));
    }
    else if(first.m_type == Type::ComplexNumber && second.m_type == Type::Integer)
    {
        result = createComplexNumber(createComplexFloat(first.m_data.complexNumberData) + ComplexFloat(second.m_data.intData, 0));
    }
    else if(first.m_type == Type::ComplexNumber && second.m_type == Type::Double)
    {
        result = createComplexNumber(createComplexFloat(first.m_data.complexNumberData) + ComplexFloat(second.m_data.doubleData, 0));
    }
    else if(first.m_type == Type::ComplexNumber && second.m_type == Type::Fraction)
    {
        result = createComplexNumber(createComplexFloat(first.m_data.complexNumberData) + ComplexFloat(second.getDouble(), 0));
    }
    else if(first.m_type == Type::ComplexNumber && second.m_type == Type::ComplexNumber)
    {
        result = createComplexNumber(createComplexFloat(first.m_data.complexNumberData) + createComplexFloat(second.m_data.complexNumberData));
    }
    return result;
}

AlbaNumber AlbaNumber::operator-(AlbaNumber const& second) const
{
    return operator+(-second);
}

AlbaNumber AlbaNumber::operator*(AlbaNumber const& second) const
{
    AlbaNumber const& first(*this);

    AlbaNumber result;
    if(first.m_type == Type::Integer && second.m_type == Type::Integer)
    {
        result = multiplyBothIntegersAndReturnNumber(first.m_data.intData, second.m_data.intData);
    }
    else if(first.m_type == Type::Integer && second.m_type == Type::Double)
    {
        result = multiplyIntegerAndDoubleAndReturnNumber(first.m_data.intData, second.m_data.doubleData);
    }
    else if(first.m_type == Type::Integer && second.m_type == Type::Fraction)
    {
        result = multiplyIntegerAndFractionAndReturnNumber(first.m_data.intData, second.m_data.fractionData);
    }
    else if(first.m_type == Type::Integer && second.m_type == Type::ComplexNumber)
    {
        result = createComplexNumber(ComplexFloat(first.m_data.intData, 0) * createComplexFloat(second.m_data.complexNumberData));
    }
    else if(first.m_type == Type::Double && second.m_type == Type::Integer)
    {
        result = multiplyIntegerAndDoubleAndReturnNumber(second.m_data.intData, first.m_data.doubleData);
    }
    else if(first.m_type == Type::Double && second.m_type == Type::Double)
    {
        result = multiplyBothDoubleAndReturnNumber(first.m_data.doubleData, second.m_data.doubleData);
    }
    else if(first.m_type == Type::Double && second.m_type == Type::Fraction)
    {
        result = multiplyFractionAndDoubleAndReturnNumber(second.m_data.fractionData, first.m_data.doubleData);
    }
    else if(first.m_type == Type::Double && second.m_type == Type::ComplexNumber)
    {
        result = createComplexNumber(ComplexFloat(first.m_data.doubleData, 0) * createComplexFloat(second.m_data.complexNumberData));
    }
    else if(first.m_type == Type::Fraction && second.m_type == Type::Integer)
    {
        result = multiplyIntegerAndFractionAndReturnNumber(second.m_data.intData, first.m_data.fractionData);
    }
    else if(first.m_type == Type::Fraction && second.m_type == Type::Double)
    {
        result = multiplyFractionAndDoubleAndReturnNumber(first.m_data.fractionData, second.m_data.doubleData);
    }
    else if(first.m_type == Type::Fraction && second.m_type == Type::Fraction)
    {
        result = multiplyBothFractionsAndReturnNumber(first.m_data.fractionData, second.m_data.fractionData);
    }
    else if(first.m_type == Type::Fraction && second.m_type == Type::ComplexNumber)
    {
        result = createComplexNumber(ComplexFloat(first.getDouble(), 0) * createComplexFloat(second.m_data.complexNumberData));
    }
    else if(first.m_type == Type::ComplexNumber && second.m_type == Type::Integer)
    {
        result = createComplexNumber(createComplexFloat(first.m_data.complexNumberData) * ComplexFloat(second.m_data.intData, 0));
    }
    else if(first.m_type == Type::ComplexNumber && second.m_type == Type::Double)
    {
        result = createComplexNumber(createComplexFloat(first.m_data.complexNumberData) * ComplexFloat(second.m_data.doubleData, 0));
    }
    else if(first.m_type == Type::ComplexNumber && second.m_type == Type::Fraction)
    {
        result = createComplexNumber(createComplexFloat(first.m_data.complexNumberData) * ComplexFloat(second.getDouble(), 0));
    }
    else if(first.m_type == Type::ComplexNumber && second.m_type == Type::ComplexNumber)
    {
        result = createComplexNumber(createComplexFloat(first.m_data.complexNumberData) * createComplexFloat(second.m_data.complexNumberData));
    }
    return result;
}

AlbaNumber AlbaNumber::operator/(AlbaNumber const& second) const
{
    AlbaNumber const& first(*this);

    AlbaNumber result;
    if(first.m_type == Type::Integer && second.m_type == Type::Integer)
    {
        result = divideBothIntegersAndReturnNumber(first.m_data.intData, second.m_data.intData);
    }
    else if(first.m_type == Type::Integer && second.m_type == Type::Double)
    {
        result = createNumberFromDoubleAndRoundIfNeeded(static_cast<double>(first.m_data.intData) / second.m_data.doubleData);
    }
    else if(first.m_type == Type::Integer && second.m_type == Type::Fraction)
    {
        result = divideDividendsAndDivisorsAndReturnNumber(
                    first.m_data.intData,
                    second.m_data.fractionData.denominator,
                    static_cast<long long int>(second.m_data.fractionData.numerator),
                    1);
    }
    else if(first.m_type == Type::Integer && second.m_type == Type::ComplexNumber)
    {
        result = createComplexNumber(ComplexFloat(first.m_data.intData, 0) / createComplexFloat(second.m_data.complexNumberData));
    }
    else if(first.m_type == Type::Double && second.m_type == Type::Integer)
    {
        result = createNumberFromDoubleAndRoundIfNeeded(first.m_data.doubleData / static_cast<double>(second.m_data.intData));
    }
    else if(first.m_type == Type::Double && second.m_type == Type::Double)
    {
        result = createNumberFromDoubleAndRoundIfNeeded(first.m_data.doubleData / second.m_data.doubleData);
    }
    else if(first.m_type == Type::Double && second.m_type == Type::Fraction)
    {
        result = createNumberFromDoubleAndRoundIfNeeded(
                    first.m_data.doubleData
                    * second.m_data.fractionData.denominator
                    / second.m_data.fractionData.numerator);
    }
    else if(first.m_type == Type::Double && second.m_type == Type::ComplexNumber)
    {
        result = createComplexNumber(ComplexFloat(first.m_data.doubleData, 0) / createComplexFloat(second.m_data.complexNumberData));
    }
    else if(first.m_type == Type::Fraction && second.m_type == Type::Integer)
    {
        result = divideDividendsAndDivisorsAndReturnNumber(
                    static_cast<long long int>(first.m_data.fractionData.numerator),
                    1,
                    second.m_data.intData,
                    first.m_data.fractionData.denominator);
    }
    else if(first.m_type == Type::Fraction && second.m_type == Type::Double)
    {
        result = createNumberFromDoubleAndRoundIfNeeded(
                    static_cast<double>(first.m_data.fractionData.numerator)
                    / first.m_data.fractionData.denominator
                    / second.m_data.doubleData);
    }
    else if(first.m_type == Type::Fraction && second.m_type == Type::Fraction)
    {
        result = divideBothFractionsAndReturnNumber(first.m_data.fractionData, second.m_data.fractionData);
    }
    else if(first.m_type == Type::Fraction && second.m_type == Type::ComplexNumber)
    {
        result = createComplexNumber(ComplexFloat(first.getDouble(), 0) / createComplexFloat(second.m_data.complexNumberData));
    }
    else if(first.m_type == Type::ComplexNumber && second.m_type == Type::Integer)
    {
        result = createComplexNumber(createComplexFloat(first.m_data.complexNumberData) / ComplexFloat(second.m_data.intData, 0));
    }
    else if(first.m_type == Type::ComplexNumber && second.m_type == Type::Double)
    {
        result = createComplexNumber(createComplexFloat(first.m_data.complexNumberData) / ComplexFloat(second.m_data.doubleData, 0));
    }
    else if(first.m_type == Type::ComplexNumber && second.m_type == Type::Fraction)
    {
        result = createComplexNumber(createComplexFloat(first.m_data.complexNumberData) / ComplexFloat(second.getDouble(), 0));
    }
    else if(first.m_type == Type::ComplexNumber && second.m_type == Type::ComplexNumber)
    {
        result = createComplexNumber(createComplexFloat(first.m_data.complexNumberData) / createComplexFloat(second.m_data.complexNumberData));
    }
    return result;
}

AlbaNumber AlbaNumber::operator^(AlbaNumber const& second) const
{
    AlbaNumber const& first(*this);

    AlbaNumber result;

    double baseInDouble(first.getDouble());
    double exponentInDouble(second.getDouble());
    double powerResultInDouble(pow(baseInDouble, exponentInDouble));
    if(!isnan(baseInDouble) && !isnan(exponentInDouble) && isnan(powerResultInDouble)) // should convert to complex
    {
        result = createComplexNumber(ComplexFloat(baseInDouble, 0) ^ exponentInDouble);
    }
    else
    {
        if(first.m_type == Type::Integer && second.m_type == Type::Integer)
        {
            result = raisePowerOfBothIntegersAndReturnNumber(first.m_data.intData, second.m_data.intData);
        }
        else if(first.m_type == Type::Fraction && second.m_type == Type::Integer)
        {
            result = raisePowerOfFractionsAndIntegerAndReturnNumber(first.m_data.fractionData, second.m_data.intData);
        }
        else if(first.m_type == Type::ComplexNumber)
        {
            result = createComplexNumber(createComplexFloat(first.m_data.complexNumberData) ^ exponentInDouble);
        }
        else // if(first.m_type != Type::ComplexNumber)
        {
            correctPowerResult(powerResultInDouble, baseInDouble, exponentInDouble);
            result = createNumberFromDoubleAndRoundIfNeeded(powerResultInDouble);
        }
    }
    return result;
}

AlbaNumber AlbaNumber::operator+(int const integerValue) const
{
    return operator+(createInteger(integerValue));
}

AlbaNumber AlbaNumber::operator-(int const integerValue) const
{
    return operator-(createInteger(integerValue));
}

AlbaNumber AlbaNumber::operator*(int const integerValue) const
{
    return operator*(createInteger(integerValue));
}

AlbaNumber AlbaNumber::operator/(int const integerValue) const
{
    return operator/(createInteger(integerValue));
}

AlbaNumber AlbaNumber::operator^(int const integerValue) const
{
    return operator^(createInteger(integerValue));
}

AlbaNumber AlbaNumber::operator+(unsigned int const integerValue) const
{
    return operator+(createInteger(integerValue));
}

AlbaNumber AlbaNumber::operator-(unsigned int const integerValue) const
{
    return operator-(createInteger(integerValue));
}

AlbaNumber AlbaNumber::operator*(unsigned int const integerValue) const
{
    return operator*(createInteger(integerValue));
}

AlbaNumber AlbaNumber::operator/(unsigned int const integerValue) const
{
    return operator/(createInteger(integerValue));
}

AlbaNumber AlbaNumber::operator^(unsigned int const integerValue) const
{
    return operator^(createInteger(integerValue));
}

AlbaNumber AlbaNumber::operator+(long long int const integerValue) const
{
    return operator+(createInteger(integerValue));
}

AlbaNumber AlbaNumber::operator-(long long int const integerValue) const
{
    return operator-(createInteger(integerValue));
}

AlbaNumber AlbaNumber::operator*(long long int const integerValue) const
{
    return operator*(createInteger(integerValue));
}

AlbaNumber AlbaNumber::operator/(long long int const integerValue) const
{
    return operator/(createInteger(integerValue));
}

AlbaNumber AlbaNumber::operator^(long long int const integerValue) const
{
    return operator^(createInteger(integerValue));
}

AlbaNumber AlbaNumber::operator+(double const doubleValue) const
{
    return operator+(createNumberFromDoubleAndRoundIfNeeded(doubleValue));
}

AlbaNumber AlbaNumber::operator-(double const doubleValue) const
{
    return operator-(createNumberFromDoubleAndRoundIfNeeded(doubleValue));
}

AlbaNumber AlbaNumber::operator*(double const doubleValue) const
{
    return operator*(createNumberFromDoubleAndRoundIfNeeded(doubleValue));
}

AlbaNumber AlbaNumber::operator/(double const doubleValue) const
{
    return operator/(createNumberFromDoubleAndRoundIfNeeded(doubleValue));
}

AlbaNumber AlbaNumber::operator^(double const doubleValue) const
{
    return operator^(createNumberFromDoubleAndRoundIfNeeded(doubleValue));
}

AlbaNumber& AlbaNumber::operator+=(AlbaNumber const& second)
{
    AlbaNumber & thisReference(*this);
    thisReference = thisReference + second;
    return thisReference;
}

AlbaNumber& AlbaNumber::operator-=(AlbaNumber const& second)
{
    AlbaNumber & thisReference(*this);
    thisReference = thisReference - second;
    return thisReference;
}

AlbaNumber& AlbaNumber::operator*=(AlbaNumber const& second)
{
    AlbaNumber & thisReference(*this);
    thisReference = thisReference * second;
    return thisReference;
}

AlbaNumber& AlbaNumber::operator/=(AlbaNumber const& second)
{
    AlbaNumber & thisReference(*this);
    thisReference = thisReference / second;
    return thisReference;
}

AlbaNumber AlbaNumber::operator+=(int const integerValue)
{
    return operator+=(createInteger(integerValue));
}

AlbaNumber AlbaNumber::operator-=(int const integerValue)
{
    return operator-=(createInteger(integerValue));
}

AlbaNumber AlbaNumber::operator*=(int const integerValue)
{
    return operator*=(createInteger(integerValue));
}

AlbaNumber AlbaNumber::operator/=(int const integerValue)
{
    return operator/=(createInteger(integerValue));
}

AlbaNumber AlbaNumber::operator+=(unsigned int const integerValue)
{
    return operator+=(createInteger(integerValue));
}

AlbaNumber AlbaNumber::operator-=(unsigned int const integerValue)
{
    return operator-=(createInteger(integerValue));
}

AlbaNumber AlbaNumber::operator*=(unsigned int const integerValue)
{
    return operator*=(createInteger(integerValue));
}

AlbaNumber AlbaNumber::operator/=(unsigned int const integerValue)
{
    return operator/=(createInteger(integerValue));
}

AlbaNumber AlbaNumber::operator+=(long long int const integerValue)
{
    return operator+=(createInteger(integerValue));
}

AlbaNumber AlbaNumber::operator-=(long long int const integerValue)
{
    return operator-=(createInteger(integerValue));
}

AlbaNumber AlbaNumber::operator*=(long long int const integerValue)
{
    return operator*=(createInteger(integerValue));
}

AlbaNumber AlbaNumber::operator/=(long long int const integerValue)
{
    return operator/=(createInteger(integerValue));
}

AlbaNumber AlbaNumber::operator+=(double const doubleValue)
{
    return operator+=(createNumberFromDoubleAndRoundIfNeeded(doubleValue));
}

AlbaNumber AlbaNumber::operator-=(double const doubleValue)
{
    return operator-=(createNumberFromDoubleAndRoundIfNeeded(doubleValue));
}

AlbaNumber AlbaNumber::operator*=(double const doubleValue)
{
    return operator*=(createNumberFromDoubleAndRoundIfNeeded(doubleValue));
}

AlbaNumber AlbaNumber::operator/=(double const doubleValue)
{
    return operator/=(createNumberFromDoubleAndRoundIfNeeded(doubleValue));
}

bool AlbaNumber::isIntegerType() const
{
    return m_type==Type::Integer;
}

bool AlbaNumber::isDoubleType() const
{
    return m_type==Type::Double;
}

bool AlbaNumber::isFractionType() const
{
    return m_type==Type::Fraction;
}

bool AlbaNumber::isComplexNumberType() const
{
    return m_type==Type::ComplexNumber;
}

bool AlbaNumber::isIntegerOrFractionType() const
{
    return isIntegerType() || isFractionType();
}

bool AlbaNumber::isPositiveInfinity() const
{
    return getDouble() == POSITIVE_INFINITY_DOUBLE_VALUE;
}

bool AlbaNumber::isNegativeInfinity() const
{
    return getDouble() == NEGATIVE_INFINITY_DOUBLE_VALUE;
}

bool AlbaNumber::isPositiveOrNegativeInfinity() const
{
    return isinf(getDouble());
}

bool AlbaNumber::isNotANumber() const
{
    return isnan(getDouble());
}

bool AlbaNumber::isAFiniteValue() const
{
    return isfinite(getDouble());
}

bool AlbaNumber::isARealFiniteValue() const
{
    return isAFiniteValue() && !isComplexNumberType();
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
        result = m_data.intData;
    }
    else if(m_type==Type::Double)
    {
        result = getIntegerAfterRoundingADoubleValue<long long int>(m_data.doubleData);
    }
    else if(m_type==Type::Fraction)
    {
        result = getIntegerAfterRoundingADoubleValue<long long int>(
                    static_cast<double>(m_data.fractionData.numerator)/m_data.fractionData.denominator);
    }
    else if(m_type==Type::ComplexNumber)
    {
        result = getIntegerAfterRoundingADoubleValue<long long int>(
                    createComplexFloat(m_data.complexNumberData).getModulusWithSignOfRealPart());
    }
    return result;
}

double AlbaNumber::getDouble() const
{
    double result(0);
    if(m_type==Type::Integer)
    {
        result = static_cast<double>(m_data.intData);
    }
    else if(m_type==Type::Double)
    {
        result = m_data.doubleData;
    }
    else if(m_type==Type::Fraction)
    {
        result = static_cast<double>(static_cast<double>(m_data.fractionData.numerator)/m_data.fractionData.denominator);
    }
    else if(m_type==Type::ComplexNumber)
    {
        result = createComplexFloat(m_data.complexNumberData).getModulusWithSignOfRealPart();
    }
    return result;
}

AlbaNumber::FractionData AlbaNumber::getFractionData() const
{
    FractionData result{0, 0};
    if(m_type==Type::Integer)
    {
        result.numerator = static_cast<int>(m_data.intData);
        result.denominator = 1U;
    }
    else if(m_type==Type::Double)
    {
        //this is costly avoid this
        FractionDetails bestFractionDetails(getBestFractionDetailsForDoubleValue(m_data.doubleData));
        result.denominator = bestFractionDetails.denominator;
        result.numerator = bestFractionDetails.sign * static_cast<int>(bestFractionDetails.numerator);
    }
    else if(m_type==Type::Fraction)
    {
        result = m_data.fractionData;
    }
    else if(m_type==Type::ComplexNumber)
    {
        double doubleValue = createComplexFloat(m_data.complexNumberData).getModulusWithSignOfRealPart();
        FractionDetails bestFractionDetails(getBestFractionDetailsForDoubleValue(doubleValue));
        result.denominator = bestFractionDetails.denominator;
        result.numerator = bestFractionDetails.sign * static_cast<int>(bestFractionDetails.numerator);
    }
    return result;
}

AlbaNumber::ComplexNumberData AlbaNumber::getComplexNumberData() const
{
    ComplexNumberData result{0, 0};
    if(m_type==Type::Integer)
    {
        result.realPart = static_cast<float>(m_data.intData);
        result.imaginaryPart = 0U;
    }
    else if(m_type==Type::Double)
    {
        result.realPart = static_cast<float>(m_data.doubleData);
        result.imaginaryPart = 0U;
    }
    else if(m_type==Type::Fraction)
    {
        result.realPart = static_cast<float>(m_data.fractionData.numerator)
                / static_cast<float>(m_data.fractionData.denominator);
        result.imaginaryPart = 0U;
    }
    else if(m_type==Type::ComplexNumber)
    {
        result = m_data.complexNumberData;
    }
    return result;
}

unsigned int AlbaNumber::getNumberDataSize() const
{
    return sizeof(m_data);
}

void AlbaNumber::convertToInteger()
{
    *this = createInteger(getInteger());
}

void AlbaNumber::convertToFraction()
{
    FractionData fractionData(getFractionData());
    *this = AlbaNumber::createFraction(fractionData.numerator, fractionData.denominator);
}

inline double AlbaNumber::getComparisonTolerance()
{
    return Configuration::getInstance().getConfigurationDetails().comparisonTolerance;
}

inline double AlbaNumber::getFloatAdjustmentTolerance()
{
    return Configuration::getInstance().getConfigurationDetails().floatAdjustmentTolerance;
}

double AlbaNumber::adjustFloatValue(float const value)
{
    double result(value);
    if(isAlmostAnInteger(value, getFloatAdjustmentTolerance()))
    {
        result=round(value);
    }
    return result;
}

AlbaNumber::ComplexFloat AlbaNumber::createComplexFloat(ComplexNumberData const& data)
{
    return ComplexFloat(data.realPart, data.imaginaryPart);
}

void AlbaNumber::correctPowerResult(double & powerResult, double const base, double const exponent)
{
    if(base < 0 && exponent == POSITIVE_INFINITY_DOUBLE_VALUE)
    {
        powerResult = NAN;
    }
}

AlbaNumber AlbaNumber::addBothIntegersAndReturnNumber(
        long long int const integerValue1,
        long long int const integerValue2) const
{
    double doubleValue = static_cast<double>(integerValue1) + static_cast<double>(integerValue2);
    if(isValueWithinLimits<long long int>(doubleValue))
    {
        return createInteger(integerValue1 + integerValue2);
    }
    else
    {
        return createNumberFromDoubleAndRoundIfNeeded(doubleValue);
    }
}

AlbaNumber AlbaNumber::addBothDoubleAndReturnNumber(
        double const doubleValue1,
        double const doubleValue2) const
{
    return createNumberFromDoubleAndRoundIfNeeded(doubleValue1 + doubleValue2);
}

AlbaNumber AlbaNumber::addBothFractionsAndReturnNumber(
        AlbaNumber::FractionData const& fractionData1,
        AlbaNumber::FractionData const& fractionData2) const
{
    unsigned long long int lcd = getLeastCommonMultiple<unsigned long long int>(fractionData1.denominator, fractionData2.denominator);
    long long int newNumerator =
            static_cast<long long int>(lcd/fractionData1.denominator)*fractionData1.numerator
            + static_cast<long long int>(lcd/fractionData2.denominator)*fractionData2.numerator;
    if(isValueWithinLimits<int>(static_cast<double>(newNumerator)) && isValueWithinLimits<unsigned int>(static_cast<double>(lcd)))
    {
        return AlbaNumber::createFraction(static_cast<int>(newNumerator), static_cast<unsigned int>(lcd));
    }
    else
    {
        return createNumberFromDoubleAndRoundIfNeeded(static_cast<double>(newNumerator)/static_cast<double>(lcd));
    }
}

AlbaNumber AlbaNumber::addIntegerAndDoubleAndReturnNumber(
        long long int const integerValue,
        double const doubleValue) const
{
    return createNumberFromDoubleAndRoundIfNeeded(static_cast<double>(integerValue) + doubleValue);
}

AlbaNumber AlbaNumber::addIntegerAndFractionAndReturnNumber(
        long long int const integerValue,
        FractionData const& fractionData) const
{
    double doubleNumerator = static_cast<double>(integerValue) * fractionData.denominator + fractionData.numerator;
    if(isValueWithinLimits<int>(doubleNumerator))
    {
        int integerNumerator = static_cast<int>(integerValue * fractionData.denominator + fractionData.numerator);
        return AlbaNumber::createFraction(integerNumerator, fractionData.denominator);
    }
    else
    {
        return createNumberFromDoubleAndRoundIfNeeded(doubleNumerator/fractionData.denominator);
    }
}

AlbaNumber AlbaNumber::addFractionAndDoubleAndReturnNumber(FractionData const& fractionData, double const doubleValue) const
{
    return createNumberFromDoubleAndRoundIfNeeded(
                static_cast<double>(
                    static_cast<double>(fractionData.numerator) / static_cast<double>(fractionData.denominator)
                    + doubleValue));
}

AlbaNumber AlbaNumber::multiplyBothIntegersAndReturnNumber(
        long long int const integerValue1,
        long long int const integerValue2) const
{
    double doubleValue = static_cast<double>(integerValue1) * static_cast<double>(integerValue2);
    if(isValueWithinLimits<long long int>(doubleValue))
    {
        return createInteger(integerValue1 * integerValue2);
    }
    else
    {
        return createNumberFromDoubleAndRoundIfNeeded(doubleValue);
    }
}

AlbaNumber AlbaNumber::multiplyBothDoubleAndReturnNumber(double const doubleValue1, double const doubleValue2) const
{
    return createNumberFromDoubleAndRoundIfNeeded(doubleValue1 * doubleValue2);
}

AlbaNumber AlbaNumber::multiplyBothFractionsAndReturnNumber(
        AlbaNumber::FractionData const& fractionData1,
        AlbaNumber::FractionData const& fractionData2) const
{
    long long int newNumerator = static_cast<long long int>(fractionData1.numerator) * fractionData2.numerator;
    unsigned long long int newDenominator = static_cast<unsigned long long int>(fractionData1.denominator) * fractionData2.denominator;
    if(isValueWithinLimits<int>(static_cast<double>(newNumerator)) && isValueWithinLimits<unsigned int>(static_cast<double>(newDenominator)))
    {
        return AlbaNumber::createFraction(static_cast<int>(newNumerator), static_cast<unsigned int>(newDenominator));
    }
    else
    {
        return createNumberFromDoubleAndRoundIfNeeded(static_cast<double>(newNumerator)/static_cast<double>(newDenominator));
    }
}

AlbaNumber AlbaNumber::multiplyIntegerAndDoubleAndReturnNumber(
        long long int const integerValue,
        double const doubleValue) const
{
    return createNumberFromDoubleAndRoundIfNeeded(static_cast<double>(integerValue) * doubleValue);
}

AlbaNumber AlbaNumber::multiplyIntegerAndFractionAndReturnNumber(
        long long int const integerValue,
        FractionData const& fractionData) const
{
    double doubleNumerator = static_cast<double>(integerValue) * fractionData.numerator;
    if(isValueWithinLimits<int>(doubleNumerator))
    {
        return AlbaNumber::createFraction(static_cast<int>(integerValue * fractionData.numerator), fractionData.denominator);
    }
    else
    {
        return createNumberFromDoubleAndRoundIfNeeded(doubleNumerator/fractionData.denominator);
    }
}

AlbaNumber AlbaNumber::multiplyFractionAndDoubleAndReturnNumber(FractionData const& fractionData, double const doubleValue) const
{
    return createNumberFromDoubleAndRoundIfNeeded(
                static_cast<double>(
                    static_cast<double>(fractionData.numerator)/fractionData.denominator *
                    doubleValue));
}

AlbaNumber AlbaNumber::divideBothIntegersAndReturnNumber(
        long long int const dividend,
        long long int const divisor) const
{
    long long int newDividend(dividend), newDivisor(divisor);
    changeFractionToSimplestFormForSigned(newDividend, newDivisor);
    if(isValueWithinLimits<int>(static_cast<double>(newDividend)) && isValueWithinLimits<unsigned int>(static_cast<double>(newDivisor)))
    {
        return AlbaNumber::createFraction(static_cast<int>(newDividend), static_cast<unsigned int>(newDivisor));
    }
    else
    {
        return createNumberFromDoubleAndRoundIfNeeded(static_cast<double>(newDividend)/static_cast<double>(newDivisor));
    }
}

AlbaNumber AlbaNumber::divideDividendsAndDivisorsAndReturnNumber(
        long long int const dividendInteger,
        unsigned int const dividendUnsignedInteger,
        long long int const divisorInteger,
        unsigned int const divisorUnsignedInteger) const
{
    double doubleNumerator = static_cast<double>(dividendInteger) * dividendUnsignedInteger;
    double doubleDenominator = static_cast<double>(divisorInteger) * divisorUnsignedInteger;
    if(isValueWithinLimits<long long int>(doubleNumerator) && isValueWithinLimits<long long int>(doubleDenominator))
    {
        return divideBothIntegersAndReturnNumber(dividendInteger*dividendUnsignedInteger, divisorInteger*divisorUnsignedInteger);
    }
    else
    {
        return createNumberFromDoubleAndRoundIfNeeded(doubleNumerator/doubleDenominator);
    }
}

AlbaNumber AlbaNumber::divideBothFractionsAndReturnNumber(
        AlbaNumber::FractionData const& dividendFractionData,
        AlbaNumber::FractionData const& divisorFractionData) const
{
    double doubleNumerator = static_cast<double>(dividendFractionData.numerator) * divisorFractionData.denominator;
    double doubleDenominator = static_cast<double>(dividendFractionData.denominator) * divisorFractionData.numerator;
    if(isValueWithinLimits<long long int>(doubleNumerator) && isValueWithinLimits<long long int>(doubleDenominator))
    {
        long long int integerNumerator = static_cast<long long int>(dividendFractionData.numerator) * divisorFractionData.denominator;
        long long int integerDenominator = static_cast<long long int>(dividendFractionData.denominator) * divisorFractionData.numerator;
        return divideBothIntegersAndReturnNumber(integerNumerator, integerDenominator);
    }
    else
    {
        return createNumberFromDoubleAndRoundIfNeeded(doubleNumerator/doubleDenominator);
    }
}

AlbaNumber AlbaNumber::raisePowerOfBothIntegersAndReturnNumber(
        long long int const base,
        long long int const exponent) const
{
    int signOfBase = static_cast<int>(getSign(base));
    double powerUsingPositiveValues = pow(getAbsoluteValue(base), getAbsoluteValue(exponent));
    if(exponent>=0)
    {
        if(isValueWithinLimits<long long int>(powerUsingPositiveValues * signOfBase))
        {
            return createInteger(getRaiseToPowerForIntegers<long long int>(base, exponent));
        }
        else
        {
            return createNumberFromDoubleAndRoundIfNeeded(powerUsingPositiveValues * signOfBase);
        }
    }
    else
    {
        if(isValueWithinLimits<unsigned int>(powerUsingPositiveValues))
        {
            return AlbaNumber::createFraction(
                        signOfBase, static_cast<unsigned int>(getRaiseToPowerForIntegers(getAbsoluteValue(base), getAbsoluteValue(exponent))));
        }
        else
        {
            return createNumberFromDoubleAndRoundIfNeeded(pow(base, exponent));
        }
    }
}

AlbaNumber AlbaNumber::raisePowerOfFractionsAndIntegerAndReturnNumber(
        AlbaNumber::FractionData const& baseFractionData,
        long long int const exponent) const
{
    double numeratorRaiseToExponent(pow(baseFractionData.numerator, getAbsoluteValue(exponent)));
    double denominatorRaiseToExponent(pow(baseFractionData.denominator, getAbsoluteValue(exponent)));
    if(isValueWithinLimits<long long int>(numeratorRaiseToExponent) && isValueWithinLimits<long long int>(denominatorRaiseToExponent))
    {
        long long int integerNumerator = getRaiseToPowerForIntegers<long long int>(baseFractionData.numerator, getAbsoluteValue(exponent));
        long long int integerDenominator = getRaiseToPowerForIntegers<long long int>(baseFractionData.denominator, getAbsoluteValue(exponent));
        if(exponent<0)
        {
            swap(integerNumerator, integerDenominator);
        }
        return divideBothIntegersAndReturnNumber(integerNumerator, integerDenominator);
    }
    else
    {
        return createNumberFromDoubleAndRoundIfNeeded(pow(static_cast<double>(baseFractionData.numerator)/baseFractionData.denominator, exponent));
    }
}

ostream & operator<<(ostream & out, AlbaNumber const& number)
{
    if(number.m_type == AlbaNumber::Type::Integer)
    {
        out << number.m_data.intData;
    }
    else if(number.m_type == AlbaNumber::Type::Double)
    {
        double doubleValue = number.m_data.doubleData;
        if(isnan(doubleValue))
        {
            out << "(nan)";
        }
        else if(isinf(doubleValue))
        {
            if(doubleValue>0)
            {
                out << "(+infinity)";
            }
            else
            {
                out << "(-infinity)";
            }
        }
        else if(PI_DOUBLE_VALUE == doubleValue)
        {
            out << "(pi)";
        }
        else if(E_DOUBLE_VALUE == doubleValue)
        {
            out << "(e)";
        }
        else
        {
            out << doubleValue;
        }
    }
    else if(number.m_type == AlbaNumber::Type::Fraction)
    {
        out << "(" << number.m_data.fractionData.numerator << "/" << number.m_data.fractionData.denominator << ")";
    }
    else if(number.m_type == AlbaNumber::Type::ComplexNumber)
    {
        out << AlbaNumber::ComplexFloat(number.m_data.complexNumberData.realPart, number.m_data.complexNumberData.imaginaryPart);
    }
    return out;
}

template <>
AlbaNumber::ConfigurationDetails getDefaultConfigurationDetails<AlbaNumber::ConfigurationDetails>()
{
    return AlbaNumber::ConfigurationDetails{COMPARISON_TOLERANCE_FOR_DOUBLE, AlbaNumber::ADJUSTMENT_FLOAT_TOLERANCE};
}


}
