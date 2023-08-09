#pragma once

#include <Container/AlbaUniqueVariant.hpp>

#include <ostream>
#include <string>

namespace alba
{

class AlbaNumber
{
public:
    enum class Value
    {
        PositiveInfinity,
        NegativeInfinity
    };
    enum class Type
    {
        Integer,
        Fraction,
        Double
    };
    struct FractionData
    {
        int numerator;
        unsigned int denominator;
    };
    union NumberUnionData
    {
        long long int intData;
        FractionData fractionData;
        double doubleData;
    };
    AlbaNumber();
    AlbaNumber(int const integerValue);
    AlbaNumber(unsigned int const integerValue);
    AlbaNumber(long long int const integerValue);
    AlbaNumber(int const numerator, int const denominator);
    AlbaNumber(int const numerator, unsigned int const denominator);
    AlbaNumber(double const doubleValue);
    AlbaNumber(Value const value);

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
    AlbaNumber operator+(int const integerValue) const;
    AlbaNumber operator-(int const integerValue) const;
    AlbaNumber operator*(int const integerValue) const;
    AlbaNumber operator/(int const integerValue) const;
    AlbaNumber operator^(int const integerValue) const;
    AlbaNumber operator+(unsigned int const integerValue) const;
    AlbaNumber operator-(unsigned int const integerValue) const;
    AlbaNumber operator*(unsigned int const integerValue) const;
    AlbaNumber operator/(unsigned int const integerValue) const;
    AlbaNumber operator^(unsigned int const integerValue) const;
    AlbaNumber operator+(long long int const integerValue) const;
    AlbaNumber operator-(long long int const integerValue) const;
    AlbaNumber operator*(long long int const integerValue) const;
    AlbaNumber operator/(long long int const integerValue) const;
    AlbaNumber operator^(long long int const integerValue) const;
    AlbaNumber operator+(double const doubleValue) const;
    AlbaNumber operator-(double const doubleValue) const;
    AlbaNumber operator*(double const doubleValue) const;
    AlbaNumber operator/(double const doubleValue) const;
    AlbaNumber operator^(double const doubleValue) const;

    bool isIntegerType() const;
    bool isFractionType() const;
    bool isDoubleType() const;
    bool isIntegerOrFractionType() const;
    bool isPositiveInfinity() const;
    bool isNegativeInfinity() const;

    Type getType() const;
    long long int getInteger() const;
    FractionData getFractionData() const;
    double getDouble() const;

    unsigned int getNumberDataSize() const;
    std::string getDisplayableString() const;

    void convertToInteger();
    void convertToFraction();

private:
    template <typename NumberType1, typename NumberType2>
    void constructFraction(NumberType1 const numerator, NumberType2 const denominator);

    void convertToIntegerIfNeeded();
    AlbaNumber addBothIntegersAndReturnNumber(
            bool & shouldBeConvertedToDouble,
            long long int const integerValue1,
            long long int const integerValue2) const;
    AlbaNumber addBothFractionsAndReturnNumber(
            bool & shouldBeConvertedToDouble,
            FractionData const& fractionData1,
            FractionData const& fractionData2) const;
    AlbaNumber addBothDoubleAndReturnNumber(double const doubleValue1, double const doubleValue2) const;
    AlbaNumber addIntegerAndFractionAndReturnNumber(
            bool & shouldBeConvertedToDouble,
            long long int const integerValue,
            FractionData const& fractionData) const;
    AlbaNumber addIntegerAndDoubleAndReturnNumber(
            long long int const integerValue,
            double const doubleValue) const;
    AlbaNumber addFractionAndDoubleAndReturnNumber(FractionData const& fractionData, double const doubleValue) const;
    AlbaNumber multiplyBothIntegersAndReturnNumber(
            bool & shouldBeConvertedToDouble,
            long long int const integerValue1,
            long long int const integerValue2) const;
    AlbaNumber multiplyBothFractionsAndReturnNumber(
            bool & shouldBeConvertedToDouble,
            FractionData const& fractionData1,
            FractionData const& fractionData2) const;
    AlbaNumber multiplyBothDoubleAndReturnNumber(double const doubleValue1, double const doubleValue2) const;
    AlbaNumber multiplyIntegerAndFractionAndReturnNumber(
            bool & shouldBeConvertedToDouble,
            long long int const integerValue,
            FractionData const& fractionData) const;
    AlbaNumber multiplyIntegerAndDoubleAndReturnNumber(
            long long int const integerValue,
            double const doubleValue) const;
    AlbaNumber multiplyFractionAndDoubleAndReturnNumber(FractionData const& fractionData, double const doubleValue) const;
    AlbaNumber divideBothIntegersAndReturnNumber(
            bool & shouldBeConvertedToDouble,
            long long int const dividend,
            long long int const divisor) const;
    AlbaNumber divideDividendsAndDivisorsAndReturnNumber(
            bool & shouldBeConvertedToDouble,
            long long int const dividendInteger,
            unsigned int const dividendUnsignedInteger,
            long long int const divisorInteger,
            unsigned int const divisorUnsignedInteger) const;
    AlbaNumber divideBothFractionsAndReturnNumber(
            bool & shouldBeConvertedToDouble,
            FractionData const& dividendFractionData,
            FractionData const& divisorFractionData) const;
    AlbaNumber raisePowerOfBothIntegersAndReturnNumber(
            bool & shouldBeConvertedToDouble,
            long long int const base,
            long long int const exponent) const;
    AlbaNumber raisePowerOfFractionsAndIntegerAndReturnNumber(
            bool & shouldBeConvertedToDouble,
            FractionData const& baseFractionData,
            long long int const exponent) const;

    Type m_type;
    NumberUnionData m_data;
};

std::ostream & operator<<(std::ostream & out, AlbaNumber const& number);

}
