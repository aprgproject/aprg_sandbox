#include "FactorAndMulitplesHelpers.hpp"

using namespace std;

namespace alba
{

namespace mathHelper
{

AlbaNumber getGreatestCommonFactor(AlbaNumber const& firstNumber, AlbaNumber const& secondNumber)
{
    AlbaNumber result(0);
    if(firstNumber.isDoubleType() || secondNumber.isDoubleType())
    {
        result=1;
    }
    else
    {
        AlbaNumber::FractionData firstFractionData(firstNumber.getFractionData());
        AlbaNumber::FractionData secondFractionData(secondNumber.getFractionData());
        unsigned int lcmDenominator = getLeastCommonMultiple(firstFractionData.denominator, secondFractionData.denominator);
        unsigned int firstNumerator = static_cast<unsigned int>(getAbsoluteValue(firstFractionData.numerator))*lcmDenominator/firstFractionData.denominator;
        unsigned int secondNumerator = static_cast<unsigned int>(getAbsoluteValue(secondFractionData.numerator))*lcmDenominator/secondFractionData.denominator;
        unsigned int gcfNumerator = getGreatestCommonFactor(firstNumerator, secondNumerator);
        result = AlbaNumber::createFraction(static_cast<int>(gcfNumerator), lcmDenominator);
    }
    return result;
}

AlbaNumber getLeastCommonMultiple(AlbaNumber const& firstNumber, AlbaNumber const& secondNumber)
{
    AlbaNumber result(0);
    if(firstNumber.isDoubleType() || secondNumber.isDoubleType())
    {
        result=1;
    }
    else
    {
        AlbaNumber::FractionData firstFractionData(firstNumber.getFractionData());
        AlbaNumber::FractionData secondFractionData(secondNumber.getFractionData());
        unsigned int lcmDenominator = getLeastCommonMultiple(firstFractionData.denominator, secondFractionData.denominator);
        unsigned int firstNumerator = static_cast<unsigned int>(getAbsoluteValue(firstFractionData.numerator))*lcmDenominator/firstFractionData.denominator;
        unsigned int secondNumerator = static_cast<unsigned int>(getAbsoluteValue(secondFractionData.numerator))*lcmDenominator/secondFractionData.denominator;
        unsigned int lcmNumerator = getLeastCommonMultiple(firstNumerator, secondNumerator);
        result = AlbaNumber::createFraction(static_cast<int>(lcmNumerator), lcmDenominator);
    }
    return result;
}

}//namespace mathHelper

}//namespace alba
