#pragma once

#include <Container/AlbaSingleton.hpp>
#include <Math/Number/AlbaComplexNumber.hpp>

#include <ostream>
#include <string>

namespace alba
{

class AlbaNumber
{
public:
    static constexpr double ADJUSTMENT_FLOAT_TOLERANCE = 1E-15;

    enum class Value
    {
        PositiveInfinity,
        NegativeInfinity,
        NotANumber
    };
    enum class Type
    {
        Integer,
        Double,
        Fraction,
        ComplexNumber
    };
    struct FractionData
    {
        int numerator;
        unsigned int denominator;
    };
    struct ComplexNumberData
    {
        float realPart;
        float imaginaryPart;
    };
    union NumberUnionData
    {
        long long int intData;
        FractionData fractionData;
        double doubleData;
        ComplexNumberData complexNumberData;
    };

    struct ConfigurationDetails
    {
        double comparisonTolerance;
        double floatAdjustmentTolerance;
    };

    class Configuration : public AlbaSingleton<Configuration>
    {
    public:
        Configuration();
        ConfigurationDetails const& getConfigurationDetails();
        double getComparisonTolerance() const;
        double getFloatAdjustmentTolerance() const;

        void setConfigurationDetails(ConfigurationDetails const& configurationDetails);
        void setConfigurationToDefault();
        void setConfigurationTolerancesToZero();
        void setComparisonTolerance(double const comparisonTolerance);
        void setFloatAdjustmentTolerance(double const comparisonTolerance);
    private:
        ConfigurationDetails m_configurationDetails;
    };

    class ScopeObject
    {
    public:
        ScopeObject();
        ~ScopeObject();
        void setInThisScopeConfiguration(ConfigurationDetails const& configurationDetails) const;
        void setInThisScopeTheTolerancesToZero() const;
    private:
        void setInThisScopeTheValuesBack() const;
        ConfigurationDetails m_savedConfigurationDetails;
    };

    AlbaNumber();
    AlbaNumber(int const integerValue);
    AlbaNumber(unsigned int const integerValue);
    AlbaNumber(long long int const integerValue);
    AlbaNumber(double const doubleValue);
    AlbaNumber(Value const value);

    static AlbaNumber createFraction(int const numerator, int const denominator);
    static AlbaNumber createFraction(int const numerator, unsigned int const denominator);
    static AlbaNumber createComplexNumber(int const realPart, int const imaginaryPart);
    static AlbaNumber createComplexNumber(double const realPart, double const imaginaryPart);

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

    AlbaNumber& operator+=(AlbaNumber const& second);
    AlbaNumber& operator-=(AlbaNumber const& second);
    AlbaNumber& operator*=(AlbaNumber const& second);
    AlbaNumber& operator/=(AlbaNumber const& second);
    AlbaNumber operator+=(int const integerValue);
    AlbaNumber operator-=(int const integerValue);
    AlbaNumber operator*=(int const integerValue);
    AlbaNumber operator/=(int const integerValue);
    AlbaNumber operator+=(unsigned int const integerValue);
    AlbaNumber operator-=(unsigned int const integerValue);
    AlbaNumber operator*=(unsigned int const integerValue);
    AlbaNumber operator/=(unsigned int const integerValue);
    AlbaNumber operator+=(long long int const integerValue);
    AlbaNumber operator-=(long long int const integerValue);
    AlbaNumber operator*=(long long int const integerValue);
    AlbaNumber operator/=(long long int const integerValue);
    AlbaNumber operator+=(double const doubleValue);
    AlbaNumber operator-=(double const doubleValue);
    AlbaNumber operator*=(double const doubleValue);
    AlbaNumber operator/=(double const doubleValue);

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
    long long int getInteger() const;
    double getDouble() const;
    FractionData getFractionData() const;
    ComplexNumberData getComplexNumberData() const;

    unsigned int getNumberDataSize() const;
    std::string getDisplayableString() const;

    void convertToInteger();
    void convertToFraction();

private:
    template <typename NumberType1, typename NumberType2>
    void constructBasedFromFractionDetails(NumberType1 const numerator, NumberType2 const denominator);
    template <typename NumberType1, typename NumberType2>
    void constructBasedFromComplexNumberDetails(NumberType1 const realPart, NumberType2 const imaginaryPart);
    void convertFromDoubleToIntegerIfNeeded();

    double adjustFloatValue(float const value) const;

    AlbaNumber addBothIntegersAndReturnNumber(
            bool & shouldBeConvertedToDouble,
            long long int const integerValue1,
            long long int const integerValue2) const;
    AlbaNumber addBothDoubleAndReturnNumber(double const doubleValue1, double const doubleValue2) const;
    AlbaNumber addBothFractionsAndReturnNumber(
            bool & shouldBeConvertedToDouble,
            FractionData const& fractionData1,
            FractionData const& fractionData2) const;
    AlbaNumber addIntegerAndDoubleAndReturnNumber(
            long long int const integerValue,
            double const doubleValue) const;
    AlbaNumber addIntegerAndFractionAndReturnNumber(
            bool & shouldBeConvertedToDouble,
            long long int const integerValue,
            FractionData const& fractionData) const;
    AlbaNumber addFractionAndDoubleAndReturnNumber(FractionData const& fractionData, double const doubleValue) const;
    AlbaNumber multiplyBothIntegersAndReturnNumber(
            bool & shouldBeConvertedToDouble,
            long long int const integerValue1,
            long long int const integerValue2) const;
    AlbaNumber multiplyBothDoubleAndReturnNumber(double const doubleValue1, double const doubleValue2) const;
    AlbaNumber multiplyBothFractionsAndReturnNumber(
            bool & shouldBeConvertedToDouble,
            FractionData const& fractionData1,
            FractionData const& fractionData2) const;
    AlbaNumber multiplyIntegerAndDoubleAndReturnNumber(
            long long int const integerValue,
            double const doubleValue) const;
    AlbaNumber multiplyIntegerAndFractionAndReturnNumber(
            bool & shouldBeConvertedToDouble,
            long long int const integerValue,
            FractionData const& fractionData) const;
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
