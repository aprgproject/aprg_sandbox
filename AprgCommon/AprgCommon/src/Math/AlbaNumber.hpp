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
        int intData;
        FractionData fractionData;
        double doubleData;
    };
    AlbaNumber();
    AlbaNumber(int const signedValue);
    AlbaNumber(unsigned int const unsignedValue);
    AlbaNumber(int const numerator, int const denominator);
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
    AlbaNumber operator+(int const signedValue) const;
    AlbaNumber operator-(int const signedValue) const;
    AlbaNumber operator*(int const signedValue) const;
    AlbaNumber operator/(int const signedValue) const;
    AlbaNumber operator^(int const signedValue) const;
    AlbaNumber operator+(unsigned int const unsignedValue) const;
    AlbaNumber operator-(unsigned int const unsignedValue) const;
    AlbaNumber operator*(unsigned int const unsignedValue) const;
    AlbaNumber operator/(unsigned int const unsignedValue) const;
    AlbaNumber operator^(unsigned int const unsignedValue) const;
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
    int getInteger() const;
    FractionData getFractionData() const;
    double getDouble() const;

    unsigned int getNumberDataSize() const;
    std::string getDisplayableString() const;

    void convertToInteger();    void convertToFraction();

private:
    void convertToIntegerIfNeeded();    AlbaNumber addBothIntegersAndReturnNumber(
            bool & shouldBeConvertedToDouble,
            int const signedValue1,
            int const signedValue2) const;
    AlbaNumber addBothFractionsAndReturnNumber(
            bool & shouldBeConvertedToDouble,
            FractionData const& fractionData1,
            FractionData const& fractionData2) const;
    AlbaNumber addBothDoubleAndReturnNumber(double const doubleValue1, double const doubleValue2) const;
    AlbaNumber addIntegerAndFractionAndReturnNumber(
            bool & shouldBeConvertedToDouble,
            int const signedValue,
            FractionData const& fractionData) const;
    AlbaNumber addIntegerAndDoubleAndReturnNumber(int const signedValue, double const doubleValue) const;
    AlbaNumber addFractionAndDoubleAndReturnNumber(FractionData const& fractionData, double const doubleValue) const;
    AlbaNumber multiplyBothIntegersAndReturnNumber(
            bool & shouldBeConvertedToDouble,
            int const signedValue1,
            int const signedValue2) const;
    AlbaNumber multiplyBothFractionsAndReturnNumber(
            bool & shouldBeConvertedToDouble,
            FractionData const& fractionData1,
            FractionData const& fractionData2) const;
    AlbaNumber multiplyBothDoubleAndReturnNumber(double const doubleValue1, double const doubleValue2) const;
    AlbaNumber multiplyIntegerAndFractionAndReturnNumber(
            bool & shouldBeConvertedToDouble,
            int const signedValue,
            FractionData const& fractionData) const;
    AlbaNumber multiplyIntegerAndDoubleAndReturnNumber(int const signedValue, double const doubleValue) const;
    AlbaNumber multiplyFractionAndDoubleAndReturnNumber(FractionData const& fractionData, double const doubleValue) const;
    AlbaNumber divideBothIntegersAndReturnNumber(
            bool & shouldBeConvertedToDouble,
            int const dividend,
            int const divisor) const;
    AlbaNumber divideDividendsAndDivisorsAndReturnNumber(
            bool & shouldBeConvertedToDouble,
            int const dividendInteger,
            unsigned int const dividendUnsignedInteger,
            int const divisorInteger,
            unsigned int const divisorUnsignedInteger) const;
    AlbaNumber divideBothFractionsAndReturnNumber(
            bool & shouldBeConvertedToDouble,
            FractionData const& dividendFractionData,
            FractionData const& divisorFractionData) const;
    AlbaNumber raisePowerOfBothIntegersAndReturnNumber(
            bool & shouldBeConvertedToDouble,
            int const base,
            int const exponent) const;
    AlbaNumber raisePowerOfFractionsAndIntegerAndReturnNumber(
            bool & shouldBeConvertedToDouble,
            FractionData const& baseFractionData,
            int const exponent) const;

    Type m_type;
    NumberUnionData m_data;
};

std::ostream & operator<<(std::ostream & out, AlbaNumber const& number);

}
