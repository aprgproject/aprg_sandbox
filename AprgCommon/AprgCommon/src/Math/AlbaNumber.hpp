#pragma once

#include <Container/AlbaUniqueVariant.hpp>

namespace alba
{

class AlbaNumber
{
public:
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
    AlbaNumber(int const numerator, unsigned int const denominator);
    AlbaNumber(double const doubleValue);

    Type getType() const;
    int getInteger() const;
    FractionData getFractionData() const;
    double getDouble() const;

    AlbaNumber operator+() const;
    AlbaNumber operator-() const;
    AlbaNumber operator+(AlbaNumber const& second) const;
    AlbaNumber operator-(AlbaNumber const& second) const;
    AlbaNumber operator*(AlbaNumber const& second) const;
    AlbaNumber operator/(AlbaNumber const& second) const;
    AlbaNumber operator+(int const signedValue) const;
    AlbaNumber operator-(int const signedValue) const;
    AlbaNumber operator*(int const signedValue) const;
    AlbaNumber operator/(int const signedValue) const;
    AlbaNumber operator+(unsigned int const unsignedValue) const;
    AlbaNumber operator-(unsigned int const unsignedValue) const;
    AlbaNumber operator*(unsigned int const unsignedValue) const;
    AlbaNumber operator/(unsigned int const unsignedValue) const;
    AlbaNumber operator+(double const doubleValue) const;
    AlbaNumber operator-(double const doubleValue) const;
    AlbaNumber operator*(double const doubleValue) const;
    AlbaNumber operator/(double const doubleValue) const;

private:
    void convertToIntegerIfNeeded();
    AlbaNumber addBothIntegersAndReturnNumber(int const signedValue1, int const signedValue2) const;
    AlbaNumber addBothFractionsAndReturnNumber(FractionData const& fractionData1, FractionData const& fractionData2) const;
    AlbaNumber addBothDoubleAndReturnNumber(double const doubleValue1, double const doubleValue2) const;
    AlbaNumber addIntegerAndFractionAndReturnNumber(int const signedValue, FractionData const& fractionData) const;
    AlbaNumber addIntegerAndDoubleAndReturnNumber(int const signedValue, double const doubleValue) const;
    AlbaNumber addFractionAndDoubleAndReturnNumber(FractionData const& fractionData, double const doubleValue) const;
    AlbaNumber multiplyBothIntegersAndReturnNumber(int const signedValue1, int const signedValue2) const;
    AlbaNumber multiplyBothFractionsAndReturnNumber(FractionData const& fractionData1, FractionData const& fractionData2) const;
    AlbaNumber multiplyBothDoubleAndReturnNumber(double const doubleValue1, double const doubleValue2) const;
    AlbaNumber multiplyIntegerAndFractionAndReturnNumber(int const signedValue, FractionData const& fractionData) const;
    AlbaNumber multiplyIntegerAndDoubleAndReturnNumber(int const signedValue, double const doubleValue) const;
    AlbaNumber multiplyFractionAndDoubleAndReturnNumber(FractionData const& fractionData, double const doubleValue) const;
    AlbaNumber divideBothIntegersAndReturnNumber(int const signedValue1, int const signedValue2) const;
    AlbaNumber divideBothFractionsAndReturnNumber(FractionData const& fractionData1, FractionData const& fractionData2) const;

    Type m_type;
    NumberUnionData m_data;
};

}