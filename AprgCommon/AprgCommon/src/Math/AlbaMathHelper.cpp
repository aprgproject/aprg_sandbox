#include "AlbaMathHelper.hpp"

#include <algorithm>
#include <cmath>

using namespace std;

namespace alba
{

namespace mathHelper
{


//internal functions

unsigned int getNumberOfMultiplesInclusive(unsigned int const multiple, unsigned int const number)
{
    unsigned int result(0);
    if(multiple>0)
    {
        result = ((number+multiple-1)/multiple);
    }
    return result;
}

//end of internal functions


//isAlmostEqual
template <typename NumberType>
bool isAlmostEqual(NumberType const value1, NumberType const value2){
    constexpr double differenceTolerance(1E-12);
    return getAbsoluteValue(value1-value2) <= differenceTolerance;
}
//Commented out: This implementation is not practical when value is equal to zero
/*
template <typename NumberType>
bool isAlmostEqual(NumberType const value1, NumberType const value2)
{
    constexpr double absoluteScaledDifferenceTolerance(1E-12);
    double absoluteMaxValue = max(getAbsoluteValue(value1), getAbsoluteValue(value2));
    double difference = getAbsoluteValue(value1-value2);
    return difference <= absoluteMaxValue*absoluteScaledDifferenceTolerance;
}
*/

template bool isAlmostEqual<double>(double const value1, double const value2);

template <>
bool isAlmostEqual<int>(int const value1, int const value2)
{
    return value1==value2;
}

template <>
bool isAlmostEqual<unsigned int>(unsigned int const value1, unsigned int const value2)
{
    return value1==value2;
}


//getDistance
template <typename NumberType>
NumberType getDistance(NumberType const value1, NumberType const value2)
{
    std::pair<NumberType, NumberType> minMaxPair = std::minmax(value1, value2);
    return minMaxPair.second-minMaxPair.first;
}
template unsigned int getDistance<unsigned int>(unsigned int const value1, unsigned int const value2);
template int getDistance<int>(int const value1, int const value2);


//getAverage 2 parameters
template <typename NumberType>
NumberType getAverage(NumberType const value1, NumberType const value2)
{
    return (value1+value2)/2;
}
template unsigned int getAverage<unsigned int>(unsigned int const value1, unsigned int const value2);
template int getAverage<int>(int const value1, int const value2);
template double getAverage<double>(double const value1, double const value2);

//getAverage 3 parameters
template <typename NumberType>
NumberType getAverage(NumberType const value1, NumberType const value2, NumberType const value3)
{
    return (value1+value2+value3)/3;
}
template unsigned int getAverage<unsigned int>(unsigned int const value1, unsigned int const value2, unsigned int const value3);
template int getAverage<int>(int const value1, int const value2, int const value3);
template double getAverage<double>(double const value1, double const value2, double const value3);


//getAbsoluteValue
template <typename NumberType>
NumberType getAbsoluteValue(NumberType const value)
{
    return (value<0) ? value*-1 : value;
}
template int getAbsoluteValue<int>(int const value);
template double getAbsoluteValue<double>(double const value);

template <>
unsigned int getAbsoluteValue<unsigned int>(unsigned int const value)
{
    return value;
}


//getXSquaredPlusYSquared
template <typename NumberType>
NumberType getXSquaredPlusYSquared(NumberType const x, NumberType const y)
{
    return static_cast<NumberType>(pow(x, 2)+pow(y, 2));
}
template int getXSquaredPlusYSquared<int>(int const x, int const y);
template double getXSquaredPlusYSquared<double>(double const x, double const y);


//getSquareRootOfXSquaredPlusYSquared
template <typename NumberType>
NumberType getSquareRootOfXSquaredPlusYSquared(NumberType const x, NumberType const y)
{
    return static_cast<NumberType>(pow(pow(x, 2)+pow(y, 2), 0.5));
}
template int getSquareRootOfXSquaredPlusYSquared<int>(int const x, int const y);
template double getSquareRootOfXSquaredPlusYSquared<double>(double const x, double const y);


//getSquareRootOfXSquaredPlusYSquaredPlusZSquared
template <typename NumberType>
NumberType getSquareRootOfXSquaredPlusYSquaredPlusZSquared(NumberType const x, NumberType const y, NumberType const z)
{
    return static_cast<NumberType>(pow(pow(x, 2)+pow(y, 2)+pow(z, 2), 0.5));
}
template int getSquareRootOfXSquaredPlusYSquaredPlusZSquared<int>(int const x, int const y, int const z);
template double getSquareRootOfXSquaredPlusYSquaredPlusZSquared<double>(double const x, double const y, double const z);


//getSign
template <typename NumberType>
NumberType getSign(NumberType const value)
{
    return (value<0) ? -1 : 1;
}
template int getSign<int>(int const value);
template double getSign<double>(double const value);


//clampLowerBound
template <typename NumberType>
NumberType clampLowerBound(NumberType const value, NumberType const limit)
{
    return (value<limit) ? limit : value;
}
template int clampLowerBound<int>(int const value, int const limit);
template double clampLowerBound<double>(double const value, double const limit);


//clampHigherBound
template <typename NumberType>
NumberType clampHigherBound(NumberType const value, NumberType const limit)
{
    return (value>limit) ? limit : value;
}
template int clampHigherBound<int>(int const value, int const limit);
template double clampHigherBound<double>(double const value, double const limit);



bool isDivisible(unsigned int const dividend, unsigned int const divisor)
{
    bool result(false);
    if(divisor != 0)
    {
        result = (dividend % divisor)==0;
    }
    return result;
}

double getPi()
{
    return 3.14159265358979323846;
}

double getE()
{
    return 2.7182818284590452354;
}

int getRaiseToPowerForIntegers(int const base, unsigned int exponent)
{
    return static_cast<int>(ceil(pow(base, exponent)));
}

FractionDetails getFractionDetailsInLowestForm(int const numerator, int const denominator)
{
    FractionDetails result{0, 0, 0};    unsigned int unsignedNumerator = mathHelper::getAbsoluteValue(numerator);
    unsigned int unsignedDenominator = mathHelper::getAbsoluteValue(denominator);
    unsigned int greatestCommonFactor = mathHelper::getGreatestCommonFactor(unsignedNumerator, unsignedDenominator);
    if(greatestCommonFactor==0)    {
        result.sign = mathHelper::getSign(numerator*denominator);
        result.numerator = unsignedNumerator;
        result.denominator = unsignedDenominator;
    }
    else
    {
        result.sign = mathHelper::getSign(numerator*denominator);
        result.numerator = unsignedNumerator/greatestCommonFactor;
        result.denominator = unsignedDenominator/greatestCommonFactor;
    }
    return result;
}

FractionDetails getBestFractionDetailsForDoubleValue(double const doubleValue)
{
    static unsigned int numberOfIterations=0; //numberOfIterations dictates the accuracy of fraction
    numberOfIterations++;
    constexpr double tolerance(1E-3);
    FractionDetails result;
    result.sign = getSign(doubleValue);    double absoluteValueOfDouble = getAbsoluteValue(doubleValue);
    result.numerator = static_cast<int>(absoluteValueOfDouble);
    result.denominator = 1;
    double fractionalPart = getFractionalPartInDouble(absoluteValueOfDouble);
    if(fractionalPart>tolerance && numberOfIterations<=10)
    {
        double nextDoubleValueInIteration = 1/fractionalPart;
        FractionDetails partialResult = getBestFractionDetailsForDoubleValue(nextDoubleValueInIteration);        result.numerator = (result.numerator * partialResult.numerator) + (partialResult.denominator);
        result.denominator = partialResult.numerator;
    }
    else
    {
        numberOfIterations=0;
    }
    return result;
}
unsigned int getGreatestCommonFactor(unsigned int const firstNumber, unsigned int const secondNumber)
{
    unsigned int result(0);    if(firstNumber==0)
    {
        result = secondNumber;
    }
    else if(secondNumber==0)
    {
        result = firstNumber;
    }
    else if(firstNumber==secondNumber)
    {
        result = firstNumber;
    }
    else if(firstNumber>secondNumber)
    {
        result = getGreatestCommonFactor(firstNumber-secondNumber, secondNumber);
    }
    else
    {
        result = getGreatestCommonFactor(secondNumber, secondNumber-firstNumber);
    }
    return result;
}

unsigned int getLeastCommonMultiple(unsigned int const firstNumber, unsigned int const secondNumber)
{
    unsigned int result(0);
    if(firstNumber!=0 && secondNumber!=0)
    {
        result = firstNumber*secondNumber/getGreatestCommonFactor(firstNumber, secondNumber);
    }
    return result;
}

unsigned int getDifferenceFromGreaterMultiple(unsigned int const multiple, unsigned int const number)
{
    unsigned result(0);
    if(multiple>0)
    {
        unsigned int numberOfMultiples(getNumberOfMultiplesInclusive(multiple, number));
        result = (numberOfMultiples*multiple) - number;
    }
    return result;
}

int getIntegerPartInDouble(double const doubleValue)
{
    return static_cast<int>(doubleValue);
}

double getFractionalPartInDouble(double const doubleValue)
{
    return doubleValue-getIntegerPartInDouble(doubleValue);
}

double calculateCumulativeStandardDistributionApproximation(double const z)
{
    return 0.5 * erfc(-z * pow(0.5, 0.5));
}

double calculateInverseCumulativeStandardDistributionApproximation(double const probability, unsigned int const numberOfIterations)
{
    double lowestZ=-10, highestZ=10, z(0);
    for(unsigned int iterationCount=0; iterationCount<numberOfIterations; iterationCount++)
    {
        double middleZ = getAverage<double>(lowestZ, highestZ);
        double probabilityLowest = calculateCumulativeStandardDistributionApproximation(lowestZ);
        double probabilityMiddle = calculateCumulativeStandardDistributionApproximation(middleZ);
        double probabilityHighest = calculateCumulativeStandardDistributionApproximation(highestZ);
        if(isAlmostEqual(probability, probabilityLowest))
        {
            z=lowestZ;
            break;
        }
        else if(isAlmostEqual(probability, probabilityMiddle))
        {
            z=middleZ;
            break;
        }
        else if(isAlmostEqual(probability, probabilityHighest))
        {
            z=highestZ;
            break;
        }
        else if(probability>probabilityLowest && probability<probabilityMiddle)
        {
            highestZ=middleZ;
            z=getAverage<double>(lowestZ, middleZ);
        }
        else if(probability>probabilityMiddle && probability<probabilityHighest)
        {
            lowestZ=middleZ;
            z=getAverage<double>(middleZ, highestZ);
        }
    }
    return z;
}

double convertDegreesToRadians(double const valueInDegrees)
{
    return valueInDegrees/180*getPi();
}

double convertRadiansToDegrees(double const valueInRadians)
{
    return valueInRadians/getPi()*180;
}

}//namespace mathHelper

}//namespace alba