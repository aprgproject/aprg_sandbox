#pragma once

#include <Common/Math/Helpers/FactorAndMulitplesHelpers.hpp>
#include <Common/Math/Helpers/PrecisionHelpers.hpp>

#include <type_traits>

namespace alba
{
namespace mathHelper
{
struct FractionDetails
{
    int sign;
    unsigned int numerator;
    unsigned int denominator;
};

template <typename NumberType1, typename NumberType2, typename GcfType>
void changeFractionToSimplestForm(NumberType1 & numerator, NumberType2 & denominator);

template <typename NumberType>
void changeFractionToSimplestFormForUnsigned(NumberType & numerator, NumberType & denominator)
{
    static_assert(std::is_integral<NumberType>::value, "Number type must be an integer");
    static_assert(std::is_unsigned<NumberType>::value, "Number type must be unsigned");

    NumberType gcf = getGreatestCommonFactor(numerator, denominator);
    if(gcf!=0)
    {
        numerator /= gcf;
        denominator /= gcf;
    }
}

template <typename NumberType>
void changeFractionToSimplestFormForSigned(NumberType & numerator, NumberType & denominator)
{
    static_assert(std::is_integral<NumberType>::value, "Number type must be an integer");
    static_assert(std::is_signed<NumberType>::value, "Number type must be signed");

    NumberType gcf = getGreatestCommonFactor(numerator, denominator);
    if(gcf!=0)
    {
        numerator /= gcf;
        denominator /= gcf;
        numerator = getAbsoluteValue(numerator) * getSign(numerator) * getSign(denominator);
        denominator = getAbsoluteValue(denominator);
    }
}

FractionDetails getBestFractionDetailsForDoubleValue(double const doubleValue);

}//namespace mathHelper
}//namespace alba