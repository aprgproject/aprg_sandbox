#pragma once

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

template <typename NumberType1, typename NumberType2>
FractionDetails getFractionDetailsInLowestForm(NumberType1 const numerator, NumberType2 const denominator);
FractionDetails getBestFractionDetailsForDoubleValue(double const doubleValue);

}//namespace mathHelper

}//namespace alba
