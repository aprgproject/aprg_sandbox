#include "FractionHelpers.hpp"

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


template <typename NumberType1, typename NumberType2, typename GcfType>
void changeFractionToSimplestForm(NumberType1 & numerator, NumberType2 & denominator)
{
    static_assert(std::is_integral<NumberType1>::value, "Number type 1 must be an integer");
    static_assert(std::is_integral<NumberType2>::value, "Number type 2 must be an integer");

    GcfType gcf = getGreatestCommonFactor<GcfType>(numerator, denominator);
    if(gcf!=0)
    {
        numerator = static_cast<NumberType1>(numerator/gcf);
        denominator = static_cast<NumberType2>(denominator/gcf);
        numerator = getAbsoluteValue(numerator) * getSign(numerator) * getSign(denominator);
        denominator = getAbsoluteValue(denominator);
    }
}

// instantiation should fit on long long int
template void changeFractionToSimplestForm<int, unsigned int, long long int>(int & numerator, unsigned int & denominator);

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
