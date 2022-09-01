#include "FractionHelpers.hpp"

#include <Common/Math/Helpers/FactorAndMulitplesHelpers.hpp>
#include <Common/Math/Helpers/PrecisionHelpers.hpp>

#include <type_traits>

using namespace std;

namespace alba
{

namespace mathHelper
{

namespace
{
//internal functions

using Integers=vector<int>;
using UnsignedIntegers=vector<unsigned int>;

unsigned int getPartialNumerator(
        double const doubleValue,
        double & fractionalPart,
        double & doubleValueForNextIteration)
{
    double absoluteValueOfDouble = getAbsoluteValue(doubleValue);
    fractionalPart = getFractionalPartInDouble(absoluteValueOfDouble);
    doubleValueForNextIteration = 1/fractionalPart;
    return static_cast<unsigned int>(absoluteValueOfDouble);
}

FractionDetails getFractionFromPartialNumerators(
        UnsignedIntegers const& calculatedPartialNumerators,
        bool & isBeyondUnsignedIntegerLimits)
{
    double numerator(0), denominator(0);
    if(!calculatedPartialNumerators.empty())
    {
        numerator = calculatedPartialNumerators.at(calculatedPartialNumerators.size()-1);
        denominator = 1;
        for(int i=calculatedPartialNumerators.size()-2; i>=0; i--)
        {
            double previousNumerator = numerator;
            numerator = (calculatedPartialNumerators.at(i) * numerator) + denominator;
            denominator = previousNumerator;
            isBeyondUnsignedIntegerLimits =
                    isValueBeyondLimits<unsigned int>(numerator) || isValueBeyondLimits<unsigned int>(denominator);
            if(isBeyondUnsignedIntegerLimits) { break; }
        }
    }
    return FractionDetails{
        1,
        getIntegerAfterRoundingADoubleValue<unsigned int>(numerator),
                getIntegerAfterRoundingADoubleValue<unsigned int>(denominator)};
}

//end of internal functions
}

//getFractionDetailsInLowestForm
template <typename NumberType1, typename NumberType2>
FractionDetails getFractionDetailsInLowestForm(NumberType1 const numerator, NumberType2 const denominator)
{
    static_assert(std::is_integral<NumberType1>::value, "Number type 1 must be an integer");
    static_assert(std::is_integral<NumberType2>::value, "Number type 2 must be an integer");

    FractionDetails result{0, 0, 0};
    unsigned int unsignedNumerator = mathHelper::getAbsoluteValue(numerator);
    unsigned int unsignedDenominator = mathHelper::getAbsoluteValue(denominator);
    unsigned int greatestCommonFactor = mathHelper::getGreatestCommonFactor(unsignedNumerator, unsignedDenominator);
    if(greatestCommonFactor==0)
    {
        result.sign = mathHelper::getSign(numerator)*mathHelper::getSign(denominator);
        result.numerator = unsignedNumerator;
        result.denominator = unsignedDenominator;
    }
    else
    {
        result.sign = mathHelper::getSign(numerator)*mathHelper::getSign(denominator);
        result.numerator = unsignedNumerator/greatestCommonFactor;
        result.denominator = unsignedDenominator/greatestCommonFactor;
    }
    return result;
}
template FractionDetails getFractionDetailsInLowestForm<int, int>(int const numerator, int const denominator);
template FractionDetails getFractionDetailsInLowestForm<int, unsigned int>(int const numerator, unsigned int const denominator);


FractionDetails getBestFractionDetailsForDoubleValue(
        double const doubleValue)
{
    constexpr double tolerance(1E-12);
    FractionDetails result{1, 0, 1};

    UnsignedIntegers partialNumerators;
    double fractionalPart(getAbsoluteValue(doubleValue)), doubleValueForNextIteration(doubleValue);
    bool isBeyondUnsignedIntegerLimits(false);
    while(fractionalPart>tolerance && !isBeyondUnsignedIntegerLimits)
    {
        partialNumerators.emplace_back(
                    getPartialNumerator(doubleValueForNextIteration, fractionalPart, doubleValueForNextIteration));
        result = getFractionFromPartialNumerators(partialNumerators, isBeyondUnsignedIntegerLimits);
    }
    if(isBeyondUnsignedIntegerLimits)
    {
        partialNumerators.pop_back();
        result = getFractionFromPartialNumerators(partialNumerators, isBeyondUnsignedIntegerLimits);
    }
    result.sign = getSign(doubleValue);
    return result;
}

}//namespace mathHelper

}//namespace alba
