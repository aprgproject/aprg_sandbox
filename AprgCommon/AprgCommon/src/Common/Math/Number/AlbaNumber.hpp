#pragma once

#include <Common/Container/AlbaConfigurationHolder.hpp>
#include <Common/Math/AlbaMathConstants.hpp>
#include <Common/Math/Number/AlbaComplexNumber.hpp>
#include <Common/Types/AlbaTypeHelper.hpp>

#include <cmath>
#include <cstdint>
#include <ostream>

namespace alba
{

class AlbaNumber // This is value type.
{
public:

    using ComplexFloat = AlbaComplexNumber<float>;
    static constexpr double ADJUSTMENT_FLOAT_TOLERANCE = 1E-15;

    enum class Type
    {
        Integer,
        Double,
        Fraction,
        ComplexNumber
    };
    struct FractionData
    {
        int32_t numerator;
        uint32_t denominator;
    };
    struct ComplexNumberData
    {
        float realPart;
        float imaginaryPart;
    };
    union NumberUnionData
    {
        constexpr NumberUnionData()
            : intData{}
        {}
        constexpr NumberUnionData(int64_t const integer)
            : intData(integer)
        {}
        constexpr NumberUnionData(double const doubleValue)
            : doubleData(doubleValue)
        {}
        constexpr NumberUnionData(FractionData const& fractionData)
            : fractionData(fractionData)
        {}
        constexpr NumberUnionData(ComplexNumberData const& complexNumberData)
            : complexNumberData(complexNumberData)
        {}
        int64_t intData;
        double doubleData;
        FractionData fractionData;
        ComplexNumberData complexNumberData;
    };

    struct ConfigurationDetails
    {
        double comparisonTolerance;
        double floatAdjustmentTolerance;
    };
    class Configuration
            : public AlbaConfigurationHolder<ConfigurationDetails>
    {
    public:
        using BaseConfigurationHolder=AlbaConfigurationHolder<ConfigurationDetails>;
        static ConfigurationDetails getConfigurationDetailsWithZeroTolerance();

        void setConfigurationTolerancesToZero();
        void setComparisonTolerance(double const comparisonTolerance);
        void setFloatAdjustmentTolerance(double const comparisonTolerance);
    };
    class ScopeConfigurationObject : public AlbaConfigurationScopeObject<ConfigurationDetails>
    {
    public:
        void setInThisScopeTheTolerancesToZero() const;
    };

    // static functions

    static AlbaNumber createNumberFromDoubleAndRoundIfNeeded(double const doubleValue);
    static AlbaNumber createFraction(int32_t const numerator, int32_t const denominator);
    static AlbaNumber createFraction(int32_t const numerator, uint32_t const denominator);
    template <typename NumberType> static AlbaNumber createComplexNumber(NumberType const realPart, NumberType const imaginaryPart);
    static AlbaNumber createComplexNumber(ComplexFloat const& complexNumber);


    // constexpr functions

    template <typename ArithmeticType>
    void constexpr checkArithmeticType()
    {
        static_assert(sizeof(ArithmeticType)<=8, "Maximum size is 8 bytes/64 bits.");
        static_assert(!(sizeof(ArithmeticType)==8 && typeHelper::isUnsignedType<ArithmeticType>()), "Unsigned integer with 8 bytes/64 bits are not supported.");
    }

    template <typename ArithmeticType>
    Type constexpr getTypeBasedFromArithmeticType()
    {
        return typeHelper::isIntegralType<ArithmeticType>() ? Type::Integer : Type::Double;
    }


    // no need to be explicit in the constructors (allow implicit conversions)

    constexpr AlbaNumber()
        : m_type(Type::Integer)
        , m_data()
    {}

    template< typename ArithmeticType, typename = std::enable_if_t<typeHelper::isArithmeticType<ArithmeticType>()>> // enabled via a type template parameter
    constexpr AlbaNumber(ArithmeticType const value)
        : m_type(getTypeBasedFromArithmeticType<ArithmeticType>())
        , m_data(static_cast<typeHelper::ConditionalType<typeHelper::isIntegralType<ArithmeticType>(), int64_t, double>>(value))
    {
        checkArithmeticType<ArithmeticType>();
    }

    constexpr AlbaNumber(FractionData const& fractionData)
        : m_type(Type::Fraction)
        , m_data(fractionData)
    {}

    constexpr AlbaNumber(ComplexNumberData const& complexNumberData)
        : m_type(Type::ComplexNumber)
        , m_data(complexNumberData)
    {}

    AlbaNumber(char const character) = delete; // remove character to integer conversion (delete any functions is a C++11 feature)

    // This should be constexpr as well but a lot of coding is needed
    bool operator==(AlbaNumber const& second) const;
    bool operator!=(AlbaNumber const& second) const;
    bool operator<=(AlbaNumber const& second) const;
    bool operator>=(AlbaNumber const& second) const;
    bool operator<(AlbaNumber const& second) const;
    bool operator>(AlbaNumber const& second) const;
    AlbaNumber operator+() const;
    AlbaNumber operator-() const;
    AlbaNumber operator+(AlbaNumber const& second) const;
    AlbaNumber operator-(AlbaNumber const& second) const;
    AlbaNumber operator*(AlbaNumber const& second) const;
    AlbaNumber operator/(AlbaNumber const& second) const;
    AlbaNumber operator^(AlbaNumber const& second) const;
    AlbaNumber& operator+=(AlbaNumber const& second);
    AlbaNumber& operator-=(AlbaNumber const& second);
    AlbaNumber& operator*=(AlbaNumber const& second);
    AlbaNumber& operator/=(AlbaNumber const& second);

    bool isIntegerType() const;
    bool isDoubleType() const;
    bool isFractionType() const;
    bool isComplexNumberType() const;
    bool isIntegerOrFractionType() const;
    bool isPositiveInfinity() const;
    bool isNegativeInfinity() const;
    bool isPositiveOrNegativeInfinity() const;
    bool isNotANumber() const;
    bool isAFiniteValue() const;
    bool isARealFiniteValue() const;

    Type getType() const;
    int64_t getInteger() const;
    double getDouble() const;
    FractionData getFractionData() const;
    ComplexNumberData getComplexNumberData() const;

    void convertToInteger();
    void convertToFraction();

private:

    // static functions
    static double getComparisonTolerance();
    static double getFloatAdjustmentTolerance();

    static double adjustFloatValue(float const value);
    static ComplexFloat createComplexFloat(ComplexNumberData const& data);
    static void correctPowerResult(double & powerResult, double const base, double const exponent);

    template <typename NumberType1, typename NumberType2>
    void constructBasedFromComplexNumberDetails(NumberType1 const realPart, NumberType2 const imaginaryPart);

    AlbaNumber addBothIntegersAndReturnNumber(
            int64_t const integerValue1,
            int64_t const integerValue2) const;
    AlbaNumber addBothDoubleAndReturnNumber(double const doubleValue1, double const doubleValue2) const;
    AlbaNumber addBothFractionsAndReturnNumber(
            FractionData const& fractionData1,
            FractionData const& fractionData2) const;
    AlbaNumber addIntegerAndDoubleAndReturnNumber(
            int64_t const integerValue,
            double const doubleValue) const;
    AlbaNumber addIntegerAndFractionAndReturnNumber(
            int64_t const integerValue,
            FractionData const& fractionData) const;
    AlbaNumber addFractionAndDoubleAndReturnNumber(FractionData const& fractionData, double const doubleValue) const;
    AlbaNumber multiplyBothIntegersAndReturnNumber(
            int64_t const integerValue1,
            int64_t const integerValue2) const;
    AlbaNumber multiplyBothDoubleAndReturnNumber(double const doubleValue1, double const doubleValue2) const;
    AlbaNumber multiplyBothFractionsAndReturnNumber(
            FractionData const& fractionData1,
            FractionData const& fractionData2) const;
    AlbaNumber multiplyIntegerAndDoubleAndReturnNumber(
            int64_t const integerValue,
            double const doubleValue) const;
    AlbaNumber multiplyIntegerAndFractionAndReturnNumber(
            int64_t const integerValue,
            FractionData const& fractionData) const;
    AlbaNumber multiplyFractionAndDoubleAndReturnNumber(FractionData const& fractionData, double const doubleValue) const;
    AlbaNumber divideBothIntegersAndReturnNumber(
            int64_t const dividend,
            int64_t const divisor) const;
    AlbaNumber divideDividendsAndDivisorsAndReturnNumber(
            int64_t const dividendInteger,
            uint32_t const dividendUnsignedInteger,
            int64_t const divisorInteger,
            uint32_t const divisorUnsignedInteger) const;
    AlbaNumber divideBothFractionsAndReturnNumber(
            FractionData const& dividendFractionData,
            FractionData const& divisorFractionData) const;
    AlbaNumber raisePowerOfBothIntegersAndReturnNumber(
            int64_t const base,
            int64_t const exponent) const;
    AlbaNumber raisePowerOfFractionsAndIntegerAndReturnNumber(
            FractionData const& baseFractionData,
            int64_t const exponent) const;

    friend std::ostream & operator<<(std::ostream & out, AlbaNumber const& number);

    Type m_type; // Hotness: Type is much hotter.
    NumberUnionData m_data; // use std variant instead? Nah, I dont wanna deal with getting the "index" to know the "type".

    static_assert(sizeof(m_type) == 4, "The size of AlbaNumber type should be 4 bytes/32 bits.");
    static_assert(sizeof(m_data) == 8, "The size of AlbaNumber data should be 8 bytes/64 bits.");
};

static_assert(sizeof(AlbaNumber) == 16, "The size of AlbaNumber should be 16 bytes/128 bits.");

// Source: https://en.cppreference.com/w/cpp/language/user_literal
// NOTE: The string needs to have a underscore '_' prefix because all letters as prefix are reserved according to the standard.
constexpr AlbaNumber operator "" _AS_ALBA_NUMBER(unsigned long long int const value)
{
    return AlbaNumber(static_cast<int64_t>(value));
}
constexpr AlbaNumber operator "" _AS_ALBA_NUMBER(long double const value)
{
    return AlbaNumber(static_cast<double>(value));
}
// AlbaNumber operator "" _AS_ALBA_NUMBER(char const value) = delete; // not needed to delete because there is no implicit conversion

template <> AlbaNumber::ConfigurationDetails getDefaultConfigurationDetails<AlbaNumber::ConfigurationDetails>();

}
