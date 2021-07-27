#include "AlbaMathHelper.hpp"

#include <algorithm>
#include <cmath>
#include <climits>

using namespace std;

namespace alba
{

namespace mathHelper
{

constexpr double DOUBLE_DIFFERENCE_TOLERANCE=1E-12;


namespace
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
    double numerator, denominator;
    bool isFirst(true);
    for(UnsignedIntegers::const_reverse_iterator it=calculatedPartialNumerators.crbegin();
        it!=calculatedPartialNumerators.crend();
        it++)
    {
        unsigned int calculatedNumerator(*it);
        if(isFirst)
        {
            numerator = calculatedNumerator;
            denominator = 1;
            isFirst = false;
        }
        else
        {
            double previousNumerator = numerator;
            numerator = (calculatedNumerator * numerator) + denominator;
            denominator = previousNumerator;
        }
        isBeyondUnsignedIntegerLimits =
                isValueBeyondLimits<unsigned int>(numerator) || isValueBeyondLimits<unsigned int>(denominator);
        if(isBeyondUnsignedIntegerLimits) { break; }
    }
    return FractionDetails{
        1,
        getIntegerAfterRoundingDoubleValue<unsigned int>(numerator),
                getIntegerAfterRoundingDoubleValue<unsigned int>(denominator)};
}

//end of internal functions
}


double getPi()
{
    return 3.14159265358979323846;
}

double getE()
{
    return 2.7182818284590452354;
}

double convertDegreesToRadians(double const valueInDegrees)
{
    return valueInDegrees/180*getPi();
}

double convertRadiansToDegrees(double const valueInRadians)
{
    return valueInRadians/getPi()*180;
}


//isAlmostEqual
template <typename NumberType>
bool isAlmostEqual(NumberType const value1, NumberType const value2)
{
    return value1==value2;
}
template bool isAlmostEqual<unsigned int>(unsigned int const value1, unsigned int const value2);
template bool isAlmostEqual<int>(int const value1, int const value2);
template <> bool isAlmostEqual<double>(double const value1, double const value2)
{
    return value1 == value2 || getAbsoluteValue(value1-value2) < DOUBLE_DIFFERENCE_TOLERANCE;
}
//Commented out: This implementation is not practical when value is equal to zero
//template <> bool isAlmostEqual<double>(double const value1, double const value2)
//{
//    constexpr double absoluteScaledDifferenceTolerance(1E-12);
//    double absoluteMaxValue = max(getAbsoluteValue(value1), getAbsoluteValue(value2));
//    double difference = getAbsoluteValue(value1-value2);
//    return difference <= absoluteMaxValue*absoluteScaledDifferenceTolerance;
//}


bool isAlmostEqual(double const value1, double const value2, double const differenceTolerance)
{
    return value1 == value2 || getAbsoluteValue(value1-value2) <= differenceTolerance;
}


//isAlmostAnInteger
template <typename NumberType>
bool isAlmostAnInteger(double const value)
{
    return isAlmostEqual(
                value,
                static_cast<double>(static_cast<NumberType>(round(value))));
}
template bool isAlmostAnInteger<int>(double const value);
template bool isAlmostAnInteger<unsigned int>(double const value);
template bool isAlmostAnInteger<long long int>(double const value);


bool isAlmostAnInteger(double const value, double const differenceTolerance)
{
    return isAlmostEqual(
                value,
                static_cast<double>(static_cast<int>(round(value))),
                differenceTolerance);
}


//isValueBeyondLimits
template <> bool isValueBeyondLimits<int>(double const value)
{
    return value<INT_MIN || value>INT_MAX;
}
template <> bool isValueBeyondLimits<unsigned int>(double const value)
{
    return value<0 || value>UINT_MAX;
}
template <> bool isValueBeyondLimits<short int>(double const value)
{
    return value<SHRT_MIN || value>SHRT_MAX;
}
template <> bool isValueBeyondLimits<long int>(double const value)
{
    return value<LONG_MIN || value>LONG_MAX;
}
template <> bool isValueBeyondLimits<unsigned long int>(double const value)
{
    return value<0 || value>ULONG_MAX;
}
template <> bool isValueBeyondLimits<long long int>(double const value)
{
    return value<LLONG_MIN || value>LLONG_MAX;
}
template <> bool isValueBeyondLimits<unsigned long long int>(double const value)
{
    return value<0 || value>ULLONG_MAX;
}


//getIntegerAfterRoundingDoubleValue
template <typename NumberType>
NumberType getIntegerAfterRoundingDoubleValue(double const doubleValue)
{
    return static_cast<NumberType>(round(doubleValue));
}
template int getIntegerAfterRoundingDoubleValue<int>(double const doubleValue);
template unsigned int getIntegerAfterRoundingDoubleValue<unsigned int>(double const doubleValue);
template long long int getIntegerAfterRoundingDoubleValue<long long int>(double const doubleValue);


int getIntegerPartInDouble(double const doubleValue)
{
    return static_cast<int>(doubleValue);
}

double getFractionalPartInDouble(double const doubleValue)
{
    return doubleValue-getIntegerPartInDouble(doubleValue);
}


//getAbsoluteValue
template <typename NumberType>
NumberType getAbsoluteValue(NumberType const value)
{
    return (value<0) ? value*-1 : value;
}
template int getAbsoluteValue<int>(int const value);
template long long int getAbsoluteValue<long long int>(long long int const value);
template double getAbsoluteValue<double>(double const value);
template <> unsigned int getAbsoluteValue<unsigned int>(unsigned int const value)
{
    return value;
}
AlbaNumber getAbsoluteValue(AlbaNumber const& value)
{
    return (value<0) ? value*-1 : value;
}


//getSign
template <typename NumberType>
NumberType getSign(NumberType const value)
{
    return (value<0) ? -1 : 1;
}
template int getSign<int>(int const value);
template double getSign<double>(double const value);
template <> unsigned int getSign<unsigned int>(unsigned int const)
{
    return 1;
}
AlbaNumber getSign(AlbaNumber const& value)
{
    return (value<0) ? -1 : 1;
}


//getPositiveDelta
template <typename NumberType>
NumberType getPositiveDelta(NumberType const value1, NumberType const value2)
{
    pair<NumberType, NumberType> minMaxPair = minmax(value1, value2);
    return minMaxPair.second-minMaxPair.first;
}
template unsigned int getPositiveDelta<unsigned int>(unsigned int const value1, unsigned int const value2);
template int getPositiveDelta<int>(int const value1, int const value2);
template double getPositiveDelta<double>(double const value1, double const value2);
AlbaNumber getPositiveDelta(AlbaNumber const& value1, AlbaNumber const& value2)
{
    pair<AlbaNumber, AlbaNumber> minMaxPair = minmax(value1, value2);
    return minMaxPair.second-minMaxPair.first;
}


int convertToIntegerThenSubtract(unsigned int const number1, unsigned int const number2)
{
    return static_cast<int>(number1)-static_cast<int>(number2);
}


//getAverage 2 parameters
template <typename NumberType>
NumberType getAverage(NumberType const value1, NumberType const value2)
{
    return (value1+value2)/2;
}
template unsigned int getAverage<unsigned int>(unsigned int const value1, unsigned int const value2);
template int getAverage<int>(int const value1, int const value2);
template double getAverage<double>(double const value1, double const value2);
AlbaNumber getAverage(AlbaNumber const& value1, AlbaNumber const& value2)
{
    return (value1+value2)/2;
}


//getAverage 3 parameters
template <typename NumberType>
NumberType getAverage(NumberType const value1, NumberType const value2, NumberType const value3)
{
    return (value1+value2+value3)/3;
}
template unsigned int getAverage<unsigned int>(unsigned int const value1, unsigned int const value2, unsigned int const value3);
template int getAverage<int>(int const value1, int const value2, int const value3);
template double getAverage<double>(double const value1, double const value2, double const value3);


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


//clampLowerBound
template <typename NumberType>
NumberType clampLowerBound(NumberType const value, NumberType const limit)
{
    return (value<limit) ? limit : value;
}
template unsigned int clampLowerBound<unsigned int>(unsigned int const value, unsigned int const limit);
template int clampLowerBound<int>(int const value, int const limit);
template double clampLowerBound<double>(double const value, double const limit);


//clampHigherBound
template <typename NumberType>
NumberType clampHigherBound(NumberType const value, NumberType const limit)
{
    return (value>limit) ? limit : value;
}
template unsigned int clampHigherBound<unsigned int>(unsigned int const value, unsigned int const limit);
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

bool isEven(unsigned int const number)
{
    return isDivisible(number, 2u);
}

bool isOdd(unsigned int const number)
{
    return !isDivisible(number, 2u);
}

unsigned int getGreatestCommonFactor(unsigned int const firstNumber, unsigned int const secondNumber)
{
    unsigned int result(0);
    unsigned int temporaryFirstValue(firstNumber);
    unsigned int temporarySecondValue(secondNumber);
    while(1)
    {
        if(temporaryFirstValue==0)
        {
            result = temporarySecondValue;
            break;
        }
        else if(temporarySecondValue==0)
        {
            result = temporaryFirstValue;
            break;
        }
        else if(temporaryFirstValue==1 || temporarySecondValue==1)
        {
            result = 1;
            break;
        }
        else if(temporaryFirstValue==temporarySecondValue)
        {
            result = temporaryFirstValue;
            break;
        }
        else if(temporaryFirstValue>temporarySecondValue)
        {
            temporaryFirstValue = temporaryFirstValue%temporarySecondValue;
        }
        else
        {
            temporarySecondValue = temporarySecondValue%temporaryFirstValue;
        }
    }
    return result;
}

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
        result = AlbaNumber(gcfNumerator, lcmDenominator);
    }
    return result;
}

unsigned int getLeastCommonMultiple(unsigned int const firstNumber, unsigned int const secondNumber)
{
    unsigned int result(0);
    if(firstNumber!=0 && secondNumber!=0)
    {
        result = firstNumber/getGreatestCommonFactor(firstNumber, secondNumber)*secondNumber;
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
        result = AlbaNumber(lcmNumerator, lcmDenominator);
    }
    return result;
}

double getLeastCommonMultipleInDouble(unsigned int const firstNumber, unsigned int const secondNumber)
{
    double result(0);
    if(firstNumber!=0 && secondNumber!=0)
    {
        result = static_cast<double>(firstNumber)/getGreatestCommonFactor(firstNumber, secondNumber)*secondNumber;
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

//getFractionDetailsInLowestForm
template <typename NumberType1, typename NumberType2>
FractionDetails getFractionDetailsInLowestForm(NumberType1 const numerator, NumberType2 const denominator)
{
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


//isPerfectCube
template <typename NumberType>
bool isPerfectCube(NumberType const value)
{
    return isPerfectNthPower(value, 3);
}
template bool isPerfectCube<unsigned int>(unsigned int const value);
bool isPerfectCube(AlbaNumber const& value)
{
    return isPerfectNthPower(value, 3);
}


//isPerfectSquare
template <typename NumberType>
bool isPerfectSquare(NumberType const value)
{
    return isPerfectNthPower(value, 2);
}
template bool isPerfectSquare<unsigned int>(unsigned int const value);
bool isPerfectSquare(AlbaNumber const& value)
{
    return isPerfectNthPower(value, 2);
}


bool isPerfectNthPower(
        unsigned int const value,
        unsigned int const nthPower)
{
    double valueRaiseToTheReciprocal = pow(value, static_cast<double>(1)/nthPower);
    return isAlmostAnInteger<unsigned int>(valueRaiseToTheReciprocal);
}

bool isPerfectNthPower(
        AlbaNumber const& number,
        unsigned int const nthPower)
{
    bool result(false);
    if(number.isIntegerType())
    {
        int integerValue(number.getInteger());
        result = integerValue >= 0 && isPerfectNthPower(static_cast<unsigned int>(integerValue), nthPower);
    }
    else if(number.isFractionType())
    {
        AlbaNumber::FractionData fractionData(number.getFractionData());
        result = fractionData.numerator >= 0
                && isPerfectNthPower(static_cast<unsigned int>(getAbsoluteValue(fractionData.numerator)), nthPower)
                && isPerfectNthPower(fractionData.denominator, nthPower);
    }
    return result;
}

int getRaiseToPowerForIntegers(int const base, unsigned int exponent)
{
    return static_cast<int>(ceil(pow(base, exponent)));
}


template <typename NumberType>
unsigned int getNumberOfIntegerDigits(NumberType const value)
{
    unsigned int result(0);
    NumberType absoluteValue(getAbsoluteValue(value));
    if(absoluteValue >= 1)
    {
        result = static_cast<unsigned int>(log10(static_cast<double>(absoluteValue)))+1;
    }
    return result;
}
template unsigned int getNumberOfIntegerDigits<unsigned int>(unsigned int const value);
template unsigned int getNumberOfIntegerDigits<int>(int const value);
template unsigned int getNumberOfIntegerDigits<double>(double const value);


bool areNumberOfDigitsOnTheIntegerLimit(unsigned int const digits)
{
    return digits>=10;
}

}//namespace mathHelper

}//namespace alba
