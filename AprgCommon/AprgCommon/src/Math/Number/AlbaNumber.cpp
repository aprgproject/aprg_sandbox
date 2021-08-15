#include "AlbaNumber.hpp"

#include <Math/AlbaMathHelper.hpp>
#include <Math/Number/AlbaComplexNumber.hpp>

#include <cmath>
#include <sstream>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

using ComplexFloat = AlbaComplexNumber<float>;

AlbaNumber::AlbaNumber()
    : m_type(Type::Integer)
{
    m_data.intData = 0;
}

AlbaNumber::AlbaNumber(int const integerValue)
    : m_type(Type::Integer)
{
    m_data.intData = integerValue;
}

AlbaNumber::AlbaNumber(unsigned int const integerValue)
    : m_type(Type::Integer)
{
    m_data.intData = integerValue;
}

AlbaNumber::AlbaNumber(long long int const integerValue)
    : m_type(Type::Integer)
{
    m_data.intData = integerValue;
}

AlbaNumber::AlbaNumber(double const doubleValue)
    : m_type(Type::Double)
{
    m_data.doubleData = doubleValue;
    convertFromDoubleToIntegerIfNeeded();
}

AlbaNumber::AlbaNumber(Value const value)
    : m_type(Type::Double)
{
    switch(value)
    {
    case Value::PositiveInfinity:
        m_data.doubleData = INFINITY;
        break;
    case Value::NegativeInfinity:
        m_data.doubleData = -INFINITY;
        break;
    case Value::NotANumber:
        m_data.doubleData = NAN;
        break;
    }
}

AlbaNumber AlbaNumber::createFraction(int const numerator, int const denominator)
{
    AlbaNumber result;
    result.constructBasedFromFractionDetails(numerator, denominator);
    return result;
}

AlbaNumber AlbaNumber::createFraction(int const numerator, unsigned int const denominator)
{
    AlbaNumber result;
    result.constructBasedFromFractionDetails(numerator, denominator);
    return result;
}

AlbaNumber AlbaNumber::createComplexNumber(int const realPart, int const imaginaryPart)
{
    AlbaNumber result;
    result.constructBasedFromComplexNumberDetails(realPart, imaginaryPart);
    return result;
}

AlbaNumber AlbaNumber::createComplexNumber(double const realPart, double const imaginaryPart)
{
    AlbaNumber result;
    result.constructBasedFromComplexNumberDetails(
                static_cast<float>(realPart),
                static_cast<float>(imaginaryPart));
    return result;
}

bool AlbaNumber::operator==(AlbaNumber const& second) const
{
    bool result(false);
    if(!isComplexNumberType() && !second.isComplexNumberType())
    {
        result = isAlmostEqual(getDouble(), second.getDouble());
    }
    else if(isComplexNumberType() && second.isComplexNumberType())
    {
        result = createComplexNumberFromData(m_data.complexNumberData)
                == createComplexNumberFromData(second.m_data.complexNumberData);
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
        result.m_data.intData=-result.m_data.intData;
    }
    else if(result.m_type == Type::Double)
    {
        result.m_data.doubleData = -result.m_data.doubleData;
    }
    else if(result.m_type == Type::Fraction)
    {
        result.m_data.fractionData.numerator=-result.m_data.fractionData.numerator;
    }
    else if(result.m_type == Type::ComplexNumber)
    {
        saveToComplexNumberData(
                    result.m_data.complexNumberData,
                    -createComplexNumberFromData(result.m_data.complexNumberData));
    }
    return result;
}

AlbaNumber AlbaNumber::operator+(AlbaNumber const& value) const
{
    AlbaNumber const& first(*this);
    AlbaNumber const& second(value);

    AlbaNumber result;
    bool shouldBeConvertedToDouble(false);
    if(first.m_type == Type::Integer && second.m_type == Type::Integer)
    {
        result = addBothIntegersAndReturnNumber(shouldBeConvertedToDouble, first.m_data.intData, second.m_data.intData);
    }
    else if(first.m_type == Type::Integer && second.m_type == Type::Double)
    {
        result = addIntegerAndDoubleAndReturnNumber(first.m_data.intData, second.m_data.doubleData);
    }
    else if(first.m_type == Type::Integer && second.m_type == Type::Fraction)
    {
        result = addIntegerAndFractionAndReturnNumber(shouldBeConvertedToDouble, first.m_data.intData, second.m_data.fractionData);
    }
    else if(first.m_type == Type::Integer && second.m_type == Type::ComplexNumber)
    {
        ComplexFloat resultComplex(
                    ComplexFloat(first.m_data.intData, 0)
                    + createComplexNumberFromData(second.m_data.complexNumberData));
        result = createComplexNumber(resultComplex.getRealPart(), resultComplex.getImaginaryPart());
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
        ComplexFloat resultComplex(
                    ComplexFloat(first.m_data.doubleData, 0)
                    + createComplexNumberFromData(second.m_data.complexNumberData));
        result = createComplexNumber(resultComplex.getRealPart(), resultComplex.getImaginaryPart());
    }
    else if(first.m_type == Type::Fraction && second.m_type == Type::Integer)
    {
        result = addIntegerAndFractionAndReturnNumber(shouldBeConvertedToDouble, second.m_data.intData, first.m_data.fractionData);
    }
    else if(first.m_type == Type::Fraction && second.m_type == Type::Double)
    {
        result = addFractionAndDoubleAndReturnNumber(first.m_data.fractionData, second.m_data.doubleData);
    }
    else if(first.m_type == Type::Fraction && second.m_type == Type::Fraction)
    {
        result = addBothFractionsAndReturnNumber(shouldBeConvertedToDouble, first.m_data.fractionData, second.m_data.fractionData);
    }
    else if(first.m_type == Type::Fraction && second.m_type == Type::ComplexNumber)
    {
        ComplexFloat resultComplex(
                    ComplexFloat(first.getDouble(), 0)
                    + createComplexNumberFromData(second.m_data.complexNumberData));
        result = createComplexNumber(resultComplex.getRealPart(), resultComplex.getImaginaryPart());
    }
    else if(first.m_type == Type::ComplexNumber && second.m_type == Type::Integer)
    {
        ComplexFloat resultComplex(
                    createComplexNumberFromData(first.m_data.complexNumberData)
                    + ComplexFloat(second.m_data.intData, 0));
        result = createComplexNumber(resultComplex.getRealPart(), resultComplex.getImaginaryPart());
    }
    else if(first.m_type == Type::ComplexNumber && second.m_type == Type::Double)
    {
        ComplexFloat resultComplex(
                    createComplexNumberFromData(first.m_data.complexNumberData)
                    + ComplexFloat(second.m_data.doubleData, 0));
        result = createComplexNumber(resultComplex.getRealPart(), resultComplex.getImaginaryPart());
    }
    else if(first.m_type == Type::ComplexNumber && second.m_type == Type::Fraction)
    {
        ComplexFloat resultComplex(
                    createComplexNumberFromData(first.m_data.complexNumberData)
                    + ComplexFloat(second.getDouble(), 0));
        result = createComplexNumber(resultComplex.getRealPart(), resultComplex.getImaginaryPart());
    }
    else if(first.m_type == Type::ComplexNumber && second.m_type == Type::ComplexNumber)
    {
        ComplexFloat resultComplex(
                    createComplexNumberFromData(first.m_data.complexNumberData)
                    + createComplexNumberFromData(second.m_data.complexNumberData));
        result = createComplexNumber(resultComplex.getRealPart(), resultComplex.getImaginaryPart());
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
    AlbaNumber const& first(*this);
    AlbaNumber const& second(value);

    AlbaNumber result(*this);
    bool shouldBeConvertedToDouble(false);
    if(first.m_type == Type::Integer && second.m_type == Type::Integer)
    {
        result = multiplyBothIntegersAndReturnNumber(shouldBeConvertedToDouble, first.m_data.intData, second.m_data.intData);
    }
    else if(first.m_type == Type::Integer && second.m_type == Type::Double)
    {
        result = multiplyIntegerAndDoubleAndReturnNumber(first.m_data.intData, second.m_data.doubleData);
    }
    else if(first.m_type == Type::Integer && second.m_type == Type::Fraction)
    {
        result = multiplyIntegerAndFractionAndReturnNumber(shouldBeConvertedToDouble, first.m_data.intData, second.m_data.fractionData);
    }
    else if(first.m_type == Type::Integer && second.m_type == Type::ComplexNumber)
    {
        ComplexFloat resultComplex(
                    ComplexFloat(first.m_data.intData, 0)
                    * createComplexNumberFromData(second.m_data.complexNumberData));
        result = createComplexNumber(resultComplex.getRealPart(), resultComplex.getImaginaryPart());
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
        ComplexFloat resultComplex(
                    ComplexFloat(first.m_data.doubleData, 0)
                    * createComplexNumberFromData(second.m_data.complexNumberData));
        result = createComplexNumber(resultComplex.getRealPart(), resultComplex.getImaginaryPart());
    }
    else if(first.m_type == Type::Fraction && second.m_type == Type::Integer)
    {
        result = multiplyIntegerAndFractionAndReturnNumber(shouldBeConvertedToDouble, second.m_data.intData, first.m_data.fractionData);
    }
    else if(first.m_type == Type::Fraction && second.m_type == Type::Double)
    {
        result = multiplyFractionAndDoubleAndReturnNumber(first.m_data.fractionData, second.m_data.doubleData);
    }
    else if(first.m_type == Type::Fraction && second.m_type == Type::Fraction)
    {
        result = multiplyBothFractionsAndReturnNumber(shouldBeConvertedToDouble, first.m_data.fractionData, second.m_data.fractionData);
    }
    else if(first.m_type == Type::Fraction && second.m_type == Type::ComplexNumber)
    {
        ComplexFloat resultComplex(
                    ComplexFloat(first.getDouble(), 0)
                    * createComplexNumberFromData(second.m_data.complexNumberData));
        result = createComplexNumber(resultComplex.getRealPart(), resultComplex.getImaginaryPart());
    }
    else if(first.m_type == Type::ComplexNumber && second.m_type == Type::Integer)
    {
        ComplexFloat resultComplex(
                    createComplexNumberFromData(first.m_data.complexNumberData)
                    * ComplexFloat(second.m_data.intData, 0));
        result = createComplexNumber(resultComplex.getRealPart(), resultComplex.getImaginaryPart());
    }
    else if(first.m_type == Type::ComplexNumber && second.m_type == Type::Double)
    {
        ComplexFloat resultComplex(
                    createComplexNumberFromData(first.m_data.complexNumberData)
                    * ComplexFloat(second.m_data.doubleData, 0));
        result = createComplexNumber(resultComplex.getRealPart(), resultComplex.getImaginaryPart());
    }
    else if(first.m_type == Type::ComplexNumber && second.m_type == Type::Fraction)
    {
        ComplexFloat resultComplex(
                    createComplexNumberFromData(first.m_data.complexNumberData)
                    * ComplexFloat(second.getDouble(), 0));
        result = createComplexNumber(resultComplex.getRealPart(), resultComplex.getImaginaryPart());
    }
    else if(first.m_type == Type::ComplexNumber && second.m_type == Type::ComplexNumber)
    {
        ComplexFloat resultComplex(
                    createComplexNumberFromData(first.m_data.complexNumberData)
                    * createComplexNumberFromData(second.m_data.complexNumberData));
        result = createComplexNumber(resultComplex.getRealPart(), resultComplex.getImaginaryPart());
    }
    if(shouldBeConvertedToDouble)
    {
        result = multiplyBothDoubleAndReturnNumber(first.getDouble(), second.getDouble());
    }
    return result;
}

AlbaNumber AlbaNumber::operator/(AlbaNumber const& value) const
{
    AlbaNumber const& first(*this);
    AlbaNumber const& second(value);

    AlbaNumber result(*this);
    bool shouldBeConvertedToDouble(false);
    if(first.m_type == Type::Integer && second.m_type == Type::Integer)
    {
        result = divideBothIntegersAndReturnNumber(shouldBeConvertedToDouble, first.m_data.intData, second.m_data.intData);
    }
    else if(first.m_type == Type::Integer && second.m_type == Type::Double)
    {
        result = AlbaNumber(static_cast<double>(first.m_data.intData) / second.m_data.doubleData);
    }
    else if(first.m_type == Type::Integer && second.m_type == Type::Fraction)
    {
        result = divideDividendsAndDivisorsAndReturnNumber(
                    shouldBeConvertedToDouble,
                    first.m_data.intData,
                    second.m_data.fractionData.denominator,
                    static_cast<long long int>(second.m_data.fractionData.numerator),
                    1);
    }
    else if(first.m_type == Type::Integer && second.m_type == Type::ComplexNumber)
    {
        ComplexFloat resultComplex(
                    ComplexFloat(first.m_data.intData, 0)
                    / createComplexNumberFromData(second.m_data.complexNumberData));
        result = createComplexNumber(resultComplex.getRealPart(), resultComplex.getImaginaryPart());
    }
    else if(first.m_type == Type::Double && second.m_type == Type::Integer)
    {
        result = AlbaNumber(first.m_data.doubleData / second.m_data.intData);
    }
    else if(first.m_type == Type::Double && second.m_type == Type::Double)
    {
        result = AlbaNumber(first.m_data.doubleData / second.m_data.doubleData);
    }
    else if(first.m_type == Type::Double && second.m_type == Type::Fraction)
    {
        result = AlbaNumber(
                    first.m_data.doubleData
                    * second.m_data.fractionData.denominator
                    / second.m_data.fractionData.numerator);
    }
    else if(first.m_type == Type::Double && second.m_type == Type::ComplexNumber)
    {
        ComplexFloat resultComplex(
                    ComplexFloat(first.m_data.doubleData, 0)
                    / createComplexNumberFromData(second.m_data.complexNumberData));
        result = createComplexNumber(resultComplex.getRealPart(), resultComplex.getImaginaryPart());
    }
    else if(first.m_type == Type::Fraction && second.m_type == Type::Integer)
    {
        result = divideDividendsAndDivisorsAndReturnNumber(
                    shouldBeConvertedToDouble,
                    static_cast<long long int>(first.m_data.fractionData.numerator),
                    1,
                    second.m_data.intData,
                    first.m_data.fractionData.denominator);
    }
    else if(first.m_type == Type::Fraction && second.m_type == Type::Double)
    {
        result = AlbaNumber(
                    static_cast<double>(first.m_data.fractionData.numerator)
                    / first.m_data.fractionData.denominator
                    / second.m_data.doubleData);
    }
    else if(first.m_type == Type::Fraction && second.m_type == Type::Fraction)
    {
        result = divideBothFractionsAndReturnNumber(shouldBeConvertedToDouble, first.m_data.fractionData, second.m_data.fractionData);
    }
    else if(first.m_type == Type::Fraction && second.m_type == Type::ComplexNumber)
    {
        ComplexFloat resultComplex(
                    ComplexFloat(first.getDouble(), 0)
                    / createComplexNumberFromData(second.m_data.complexNumberData));
        result = createComplexNumber(resultComplex.getRealPart(), resultComplex.getImaginaryPart());
    }
    else if(first.m_type == Type::ComplexNumber && second.m_type == Type::Integer)
    {
        ComplexFloat resultComplex(
                    createComplexNumberFromData(first.m_data.complexNumberData)
                    / ComplexFloat(second.m_data.intData, 0));
        result = createComplexNumber(resultComplex.getRealPart(), resultComplex.getImaginaryPart());
    }
    else if(first.m_type == Type::ComplexNumber && second.m_type == Type::Double)
    {
        ComplexFloat resultComplex(
                    createComplexNumberFromData(first.m_data.complexNumberData)
                    / ComplexFloat(second.m_data.doubleData, 0));
        result = createComplexNumber(resultComplex.getRealPart(), resultComplex.getImaginaryPart());
    }
    else if(first.m_type == Type::ComplexNumber && second.m_type == Type::Fraction)
    {
        ComplexFloat resultComplex(
                    createComplexNumberFromData(first.m_data.complexNumberData)
                    / ComplexFloat(second.getDouble(), 0));
        result = createComplexNumber(resultComplex.getRealPart(), resultComplex.getImaginaryPart());
    }
    else if(first.m_type == Type::ComplexNumber && second.m_type == Type::ComplexNumber)
    {
        ComplexFloat resultComplex(
                    createComplexNumberFromData(first.m_data.complexNumberData)
                    / createComplexNumberFromData(second.m_data.complexNumberData));
        result = createComplexNumber(resultComplex.getRealPart(), resultComplex.getImaginaryPart());
    }
    if(shouldBeConvertedToDouble)
    {
        result = AlbaNumber(first.getDouble() / second.getDouble());
    }
    return result;
}

AlbaNumber AlbaNumber::operator^(AlbaNumber const& value) const
{
    AlbaNumber const& first(*this);
    AlbaNumber const& second(value);

    AlbaNumber result(*this);
    bool shouldBeConvertedToDouble(false);

    double firstInDouble(first.getDouble());
    double secondInDouble(second.getDouble());
    if(!isnan(firstInDouble) && !isnan(secondInDouble) && isnan(pow(firstInDouble, secondInDouble)))
    {
        ComplexFloat resultComplex(ComplexFloat(firstInDouble, 0) ^ secondInDouble);
        result = createComplexNumber(resultComplex.getRealPart(), resultComplex.getImaginaryPart());
    }
    else
    {
        if(first.m_type == Type::Integer && second.m_type == Type::Integer)
        {
            result = raisePowerOfBothIntegersAndReturnNumber(shouldBeConvertedToDouble, first.m_data.intData, second.m_data.intData);
        }
        else if(first.m_type == Type::Integer && second.m_type == Type::Double)
        {
            result = AlbaNumber(pow(firstInDouble, secondInDouble));
        }
        else if(first.m_type == Type::Integer && second.m_type == Type::Fraction)
        {
            result = AlbaNumber(pow(firstInDouble, secondInDouble));
        }
        else if(first.m_type == Type::Integer && second.m_type == Type::ComplexNumber)
        {
            result = AlbaNumber(pow(firstInDouble, secondInDouble));
        }
        else if(first.m_type == Type::Double && second.m_type == Type::Integer)
        {
            result = AlbaNumber(pow(firstInDouble, secondInDouble));
        }
        else if(first.m_type == Type::Double && second.m_type == Type::Double)
        {
            result = AlbaNumber(pow(firstInDouble, secondInDouble));
        }
        else if(first.m_type == Type::Double && second.m_type == Type::Fraction)
        {
            result = AlbaNumber(pow(firstInDouble, secondInDouble));
        }
        else if(first.m_type == Type::Double && second.m_type == Type::ComplexNumber)
        {
            result = AlbaNumber(pow(firstInDouble, secondInDouble));
        }
        else if(first.m_type == Type::Fraction && second.m_type == Type::Integer)
        {
            result = raisePowerOfFractionsAndIntegerAndReturnNumber(shouldBeConvertedToDouble, first.m_data.fractionData, second.m_data.intData);
        }
        else if(first.m_type == Type::Fraction && second.m_type == Type::Double)
        {
            result = AlbaNumber(pow(firstInDouble, secondInDouble));
        }
        else if(first.m_type == Type::Fraction && second.m_type == Type::Fraction)
        {
            result = AlbaNumber(pow(firstInDouble, secondInDouble));
        }
        else if(first.m_type == Type::Fraction && second.m_type == Type::ComplexNumber)
        {
            result = AlbaNumber(pow(firstInDouble, secondInDouble));
        }
        else if(first.m_type == Type::ComplexNumber)
        {
            ComplexFloat resultComplex(
                        createComplexNumberFromData(first.m_data.complexNumberData)
                        ^ secondInDouble);
            result = createComplexNumber(resultComplex.getRealPart(), resultComplex.getImaginaryPart());
        }
        else if(first.m_type == Type::ComplexNumber && second.m_type == Type::Double)
        {
            ComplexFloat resultComplex(
                        createComplexNumberFromData(first.m_data.complexNumberData)
                        ^ secondInDouble);
            result = createComplexNumber(resultComplex.getRealPart(), resultComplex.getImaginaryPart());
        }
        else if(first.m_type == Type::ComplexNumber && second.m_type == Type::Fraction)
        {
            ComplexFloat resultComplex(
                        createComplexNumberFromData(first.m_data.complexNumberData)
                        ^ secondInDouble);
            result = createComplexNumber(resultComplex.getRealPart(), resultComplex.getImaginaryPart());
        }
        else if(first.m_type == Type::ComplexNumber && second.m_type == Type::ComplexNumber)
        {
            ComplexFloat resultComplex(
                        createComplexNumberFromData(first.m_data.complexNumberData)
                        ^ secondInDouble);
            result = createComplexNumber(resultComplex.getRealPart(), resultComplex.getImaginaryPart());
        }
    }
    if(shouldBeConvertedToDouble)
    {
        result = AlbaNumber(pow(firstInDouble, secondInDouble));
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
    return operator+=(AlbaNumber(integerValue));
}

AlbaNumber AlbaNumber::operator-=(int const integerValue)
{
    return operator-=(AlbaNumber(integerValue));
}

AlbaNumber AlbaNumber::operator*=(int const integerValue)
{
    return operator*=(AlbaNumber(integerValue));
}

AlbaNumber AlbaNumber::operator/=(int const integerValue)
{
    return operator/=(AlbaNumber(integerValue));
}

AlbaNumber AlbaNumber::operator+=(unsigned int const integerValue)
{
    return operator+=(AlbaNumber(integerValue));
}

AlbaNumber AlbaNumber::operator-=(unsigned int const integerValue)
{
    return operator-=(AlbaNumber(integerValue));
}

AlbaNumber AlbaNumber::operator*=(unsigned int const integerValue)
{
    return operator*=(AlbaNumber(integerValue));
}

AlbaNumber AlbaNumber::operator/=(unsigned int const integerValue)
{
    return operator/=(AlbaNumber(integerValue));
}

AlbaNumber AlbaNumber::operator+=(long long int const integerValue)
{
    return operator+=(AlbaNumber(integerValue));
}

AlbaNumber AlbaNumber::operator-=(long long int const integerValue)
{
    return operator-=(AlbaNumber(integerValue));
}

AlbaNumber AlbaNumber::operator*=(long long int const integerValue)
{
    return operator*=(AlbaNumber(integerValue));
}

AlbaNumber AlbaNumber::operator/=(long long int const integerValue)
{
    return operator/=(AlbaNumber(integerValue));
}

AlbaNumber AlbaNumber::operator+=(double const doubleValue)
{
    return operator+=(AlbaNumber(doubleValue));
}

AlbaNumber AlbaNumber::operator-=(double const doubleValue)
{
    return operator-=(AlbaNumber(doubleValue));
}

AlbaNumber AlbaNumber::operator*=(double const doubleValue)
{
    return operator*=(AlbaNumber(doubleValue));
}

AlbaNumber AlbaNumber::operator/=(double const doubleValue)
{
    return operator/=(AlbaNumber(doubleValue));
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

bool AlbaNumber::isAFiniteValue() const
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
        result = m_data.intData;
    }
    else if(m_type==Type::Double)
    {
        result = getIntegerAfterRoundingDoubleValue<long long int>(m_data.doubleData);
    }
    else if(m_type==Type::Fraction)
    {
        result = getIntegerAfterRoundingDoubleValue<long long int>(
                    static_cast<double>(m_data.fractionData.numerator)/m_data.fractionData.denominator);
    }
    else if(m_type==Type::ComplexNumber)
    {
        result = getIntegerAfterRoundingDoubleValue<long long int>(
                    createComplexNumberFromData(m_data.complexNumberData).getModulusWithSignOfRealPart());
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
        result = createComplexNumberFromData(m_data.complexNumberData).getModulusWithSignOfRealPart();
    }
    return result;
}

AlbaNumber::FractionData AlbaNumber::getFractionData() const
{
    FractionData result{0, 0};
    if(m_type==Type::Integer)
    {
        result.numerator = static_cast<int>(m_data.intData);
        result.denominator = 1u;
    }
    else if(m_type==Type::Double)
    {
        //this is costly avoid this
        FractionDetails bestFractionDetails(getBestFractionDetailsForDoubleValue(m_data.doubleData));
        result.denominator = bestFractionDetails.denominator;
        result.numerator = bestFractionDetails.sign * bestFractionDetails.numerator;
    }
    else if(m_type==Type::Fraction)
    {
        result = m_data.fractionData;
    }
    else if(m_type==Type::ComplexNumber)
    {
        double doubleValue = createComplexNumberFromData(m_data.complexNumberData).getModulusWithSignOfRealPart();
        FractionDetails bestFractionDetails(getBestFractionDetailsForDoubleValue(doubleValue));
        result.denominator = bestFractionDetails.denominator;
        result.numerator = bestFractionDetails.sign * bestFractionDetails.numerator;
    }
    return result;
}

AlbaNumber::ComplexNumberData AlbaNumber::getComplexNumberData() const
{
    ComplexNumberData result{0, 0};
    if(m_type==Type::Integer)
    {
        result.realPart = static_cast<float>(m_data.intData);
        result.imaginaryPart = 0u;
    }
    else if(m_type==Type::Double)
    {
        result.realPart = static_cast<float>(m_data.doubleData);
        result.imaginaryPart = 0u;
    }
    else if(m_type==Type::Fraction)
    {
        result.realPart = static_cast<float>(m_data.fractionData.numerator) / m_data.fractionData.denominator;
        result.imaginaryPart = 0u;
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

string AlbaNumber::getDisplayableString() const
{
    stringstream result;
    if(m_type==Type::Integer)
    {
        result << m_data.intData;
    }
    else if(m_type==Type::Double)
    {
        result.precision(15);
        result << m_data.doubleData;
    }
    else if(m_type==Type::Fraction)
    {
        result << "(" << m_data.fractionData.numerator << "/" << m_data.fractionData.denominator << ")";
    }
    else if(m_type==Type::ComplexNumber)
    {
        result << ComplexFloat(m_data.complexNumberData.realPart, m_data.complexNumberData.imaginaryPart).getDisplayableString();
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
    *this = AlbaNumber::createFraction(fractionData.numerator, fractionData.denominator);
}


template <typename NumberType1, typename NumberType2>
void AlbaNumber::constructBasedFromFractionDetails(NumberType1 const numerator, NumberType2 const denominator)
{
    if(denominator==0)
    {
        *this = AlbaNumber(static_cast<double>(numerator)/denominator);
    }
    else if(isDivisible(
                static_cast<unsigned int>(getAbsoluteValue(numerator)),
                static_cast<unsigned int>(getAbsoluteValue(denominator))))
    {
        *this = AlbaNumber(
                    getIntegerAfterRoundingDoubleValue<long long int>(
                        static_cast<double>(numerator) / denominator));
    }
    else
    {
        m_type = AlbaNumber::Type::Fraction;
        FractionDetails fractionDetails(getFractionDetailsInLowestForm(numerator, denominator));
        FractionData& fractionDataReference(m_data.fractionData);
        fractionDataReference.numerator = fractionDetails.sign * fractionDetails.numerator;
        fractionDataReference.denominator = fractionDetails.denominator;
    }
}
template void AlbaNumber::constructBasedFromFractionDetails<int, int>(int const numerator, int const denominator);
template void AlbaNumber::constructBasedFromFractionDetails<int, unsigned int>(int const numerator, unsigned int const denominator);


template <typename NumberType1, typename NumberType2>
void AlbaNumber::constructBasedFromComplexNumberDetails(NumberType1 const realPart, NumberType2 const imaginaryPart)
{
    double adjustedRealPart = adjustFloatValue(realPart);
    double adjustedImaginaryPart = adjustFloatValue(imaginaryPart);
    if(isAlmostEqual(adjustedImaginaryPart, 0.0) || INFINITY == adjustedRealPart|| -INFINITY == adjustedRealPart || isnan(adjustedRealPart))
    {
        *this = AlbaNumber(static_cast<double>(adjustedRealPart));
    }
    else
    {
        m_type = AlbaNumber::Type::ComplexNumber;
        ComplexNumberData& complexReference(m_data.complexNumberData);
        complexReference.realPart = static_cast<float>(adjustedRealPart);
        complexReference.imaginaryPart = static_cast<float>(adjustedImaginaryPart);
    }
}
template void AlbaNumber::constructBasedFromComplexNumberDetails<int, int>(int const numerator, int const denominator);
template void AlbaNumber::constructBasedFromComplexNumberDetails<float, float>(float const numerator, float const denominator);


void AlbaNumber::convertFromDoubleToIntegerIfNeeded()
{
    double realValue(getDouble());
    if(!isValueBeyondLimits<long long int>(realValue) && isAlmostAnInteger<double, long long int>(realValue))
    {
        *this = AlbaNumber(getIntegerAfterRoundingDoubleValue<long long int>(realValue));
    }
}

double AlbaNumber::adjustFloatValue(float const value) const
{
    double result(value);
    if(isAlmostAnInteger<float, long long int>(value))
    {
        result=round(value);
    }
    return result;
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

AlbaNumber AlbaNumber::addBothDoubleAndReturnNumber(
        double const doubleValue1,
        double const doubleValue2) const
{
    return AlbaNumber(doubleValue1 + doubleValue2);
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
    return AlbaNumber::createFraction(
                getIntegerAfterRoundingDoubleValue<int>(numeratorResult),
                getIntegerAfterRoundingDoubleValue<unsigned int>(lcm));
}

AlbaNumber AlbaNumber::addIntegerAndDoubleAndReturnNumber(
        long long int const integerValue,
        double const doubleValue) const
{
    return AlbaNumber(static_cast<double>(integerValue + doubleValue));
}

AlbaNumber AlbaNumber::addIntegerAndFractionAndReturnNumber(
        bool & shouldBeConvertedToDouble,
        long long int const integerValue,
        FractionData const& fractionData) const
{
    double numerator((static_cast<double>(fractionData.denominator)*integerValue) + fractionData.numerator);
    shouldBeConvertedToDouble = isValueBeyondLimits<int>(numerator);
    return AlbaNumber::createFraction(getIntegerAfterRoundingDoubleValue<int>(numerator), fractionData.denominator);
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

AlbaNumber AlbaNumber::multiplyBothDoubleAndReturnNumber(double const doubleValue1, double const doubleValue2) const
{
    return AlbaNumber(doubleValue1 * doubleValue2);
}

AlbaNumber AlbaNumber::multiplyBothFractionsAndReturnNumber(
        bool & shouldBeConvertedToDouble,
        AlbaNumber::FractionData const& fractionData1,
        AlbaNumber::FractionData const& fractionData2) const
{
    double numerator(static_cast<double>(fractionData1.numerator) * fractionData2.numerator);
    double denominator(static_cast<double>(fractionData1.denominator) * fractionData2.denominator);
    shouldBeConvertedToDouble = isValueBeyondLimits<int>(numerator) || isValueBeyondLimits<unsigned int>(denominator);
    return AlbaNumber::createFraction(
                getIntegerAfterRoundingDoubleValue<int>(numerator),
                getIntegerAfterRoundingDoubleValue<unsigned int>(denominator));
}

AlbaNumber AlbaNumber::multiplyIntegerAndDoubleAndReturnNumber(
        long long int const integerValue,
        double const doubleValue) const
{
    return AlbaNumber(static_cast<double>(integerValue) * doubleValue);
}

AlbaNumber AlbaNumber::multiplyIntegerAndFractionAndReturnNumber(
        bool & shouldBeConvertedToDouble,
        long long int const integerValue,
        FractionData const& fractionData) const
{
    double numerator(static_cast<double>(integerValue) * fractionData.numerator);
    shouldBeConvertedToDouble = isValueBeyondLimits<int>(numerator);
    return AlbaNumber::createFraction(getIntegerAfterRoundingDoubleValue<int>(numerator), fractionData.denominator);
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
    return AlbaNumber::createFraction(static_cast<int>(fractionDetails.sign * fractionDetails.numerator), fractionDetails.denominator);
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
    return AlbaNumber::createFraction(
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
    return AlbaNumber::createFraction(
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
        result = AlbaNumber::createFraction(1, getIntegerAfterRoundingDoubleValue<int>(baseRaiseToExponent));
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
        result = AlbaNumber::createFraction(
                    getIntegerAfterRoundingDoubleValue<int>(numerator),
                    getIntegerAfterRoundingDoubleValue<unsigned int>(denominator));
    }
    else
    {
        double numerator(previousNumeratorRaiseToExponent);
        double denominator(previousDenominatorRaiseToExponent);
        shouldBeConvertedToDouble = isValueBeyondLimits<int>(numerator) || isValueBeyondLimits<unsigned int>(denominator);
        result = AlbaNumber::createFraction(
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
