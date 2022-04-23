#pragma once

#include <Common/Math/Number/AlbaNumber.hpp>
#include <Common/Math/Number/AlbaNumberTypes.hpp>

#include <algorithm>
#include <vector>

namespace alba{

namespace mathHelper
{
enum class RootType
{
    RealRootsOnly,
    RealAndImaginaryRoots,
};

using Integers=std::vector<int>;
using UnsignedIntegers=std::vector<unsigned int>;

struct FractionDetails
{
    int sign;
    unsigned int numerator;
    unsigned int denominator;
};


//Constants
double getPi();
double getE();


//Conversion functions
double convertDegreesToRadians(double const valueInDegrees);
double convertRadiansToDegrees(double const valueInRadians);


//Precision related functions
template <typename NumberType> bool isAlmostEqual(NumberType const value1, NumberType const value2)
{
    return value1==value2;
}
template <> bool isAlmostEqual<float>(float const value1, float const value2);
template <> bool isAlmostEqual<double>(double const value1, double const value2);
bool isAlmostEqual(double const value1, double const value2, double const differenceTolerance);
template <typename NumberType1, typename NumberType2> bool isAlmostAnInteger(NumberType1 const value)
{
    return isAlmostEqual(
                value,
                static_cast<NumberType1>(static_cast<NumberType2>(round(value))));
}
bool isAlmostAnInteger(double const value, double const differenceTolerance);
template <typename NumberType> bool isValueBeyondLimits(double const value);
template <typename NumberType> NumberType getIntegerAfterRoundingDoubleValue(double const doubleValue)
{
    return static_cast<NumberType>(round(doubleValue));
}
int getIntegerPartInDouble(double const doubleValue);
double getFractionalPartInDouble(double const doubleValue);
AlbaNumber convertIfInfinityToNearestFiniteValue(AlbaNumber const& value);

//Sign related functions
template <typename NumberType> NumberType getAbsoluteValue(NumberType const value)
{
    return (value<0) ? value*-1 : value;
}
template <> unsigned int getAbsoluteValue<unsigned int>(unsigned int const value);
template <typename NumberType> NumberType getSign(NumberType const value)
{
    return (value<0) ? -1 : 1;
}
template <> unsigned int getSign<unsigned int>(unsigned int const);
template <typename NumberType> NumberType getPositiveDelta(NumberType const value1, NumberType const value2)
{
    std::pair<NumberType, NumberType> minMaxPair = std::minmax(value1, value2);
    return minMaxPair.second-minMaxPair.first;
}
int convertToIntegerThenSubtract(unsigned int const number1, unsigned int const number2);
AlbaNumber getAbsoluteValueForAlbaNumber(AlbaNumber const& value);
AlbaNumber getSignForAlbaNumber(AlbaNumber const& value);AlbaNumber getPositiveDeltaForAlbaNumber(AlbaNumber const& value1, AlbaNumber const& value2);


//Computation functions
template <typename NumberType> NumberType getAverage(NumberType const value1, NumberType const value2)
{
    return (value1+value2)/2;
}
template <typename NumberType> NumberType getAverage(NumberType const value1, NumberType const value2, NumberType const value3)
{
    return (value1+value2+value3)/3;
}
template <typename NumberType> NumberType getXSquaredPlusYSquared(NumberType const x, NumberType const y)
{
    return static_cast<NumberType>(pow(x, 2)+pow(y, 2));
}
template <typename NumberType> NumberType getSquareRootOfXSquaredPlusYSquared(NumberType const x, NumberType const y)
{
    return static_cast<NumberType>(pow(pow(x, 2)+pow(y, 2), 0.5));
}
template <typename NumberType> NumberType getSquareRootOfXSquaredPlusYSquaredPlusZSquared(NumberType const x, NumberType const y, NumberType const z)
{
    return static_cast<NumberType>(pow(pow(x, 2)+pow(y, 2)+pow(z, 2), 0.5));
}
double getLogarithm(double const base, double const inputForLogarithm);
AlbaNumber getAverageForAlbaNumber(AlbaNumber const& value1, AlbaNumber const& value2);
AlbaNumbers getQuadraticRoots(RootType const rootType, AlbaNumber const& a, AlbaNumber const& b, AlbaNumber const& c);

//Combinatorics functions
unsigned int getFactorial(unsigned int const number);
unsigned int getNumberOfPermutations(unsigned int const n, unsigned int const r);unsigned int getNumberOfCombinations(unsigned int const n, unsigned int const r);
unsigned int getValueAtPascalTriangle(unsigned int const rowIndex, unsigned int const columnIndex);
int getStirlingNumberOfTheSecondKind(unsigned int const n, unsigned int const k);


//Statistics functions
double getCumulativeStandardDistributionApproximation(double const z);
double getInverseCumulativeStandardDistributionApproximation(double const p, unsigned int const numberOfIterations);


//Clamp functions
template <typename NumberType> NumberType clampLowerBound(NumberType const value, NumberType const limit)
{
    return (value<limit) ? limit : value;
}
template <typename NumberType> NumberType clampHigherBound(NumberType const value, NumberType const limit)
{
    return (value>limit) ? limit : value;
}


//Divisibility functionsbool isDivisible(unsigned int const dividend, unsigned int const divisor);
bool isEven(unsigned int const number);
bool isOdd(unsigned int const number);

//Factor and multiple related functions
bool isPrime(unsigned int const number);
unsigned int getGreatestCommonFactor(unsigned int const firstNumber, unsigned int const secondNumber);
unsigned int getLeastCommonMultiple(unsigned int const firstNumber, unsigned int const secondNumber);
double getLeastCommonMultipleInDouble(unsigned int const firstNumber, unsigned int const secondNumber);
unsigned int getDifferenceFromGreaterMultiple(unsigned int const multiple, unsigned int const number);
AlbaNumber getGreatestCommonFactorForAlbaNumber(AlbaNumber const& firstNumber, AlbaNumber const& secondNumber);
AlbaNumber getLeastCommonMultipleForAlbaNumber(AlbaNumber const& firstNumber, AlbaNumber const& secondNumber);


//Fraction related functions
template <typename NumberType1, typename NumberType2>
FractionDetails getFractionDetailsInLowestForm(NumberType1 const numerator, NumberType2 const denominator);
FractionDetails getBestFractionDetailsForDoubleValue(double const doubleValue);


//Power related functions
template <typename NumberType> bool isPerfectCube(NumberType const value);
template <typename NumberType> bool isPerfectSquare(NumberType const value);
bool isPerfectNthPower(unsigned int const valueToCheck, unsigned int const nthPower);
int getRaiseToPowerForIntegers(int const base, unsigned int exponent);
bool isPerfectCubeForAlbaNumber(AlbaNumber const& value);
bool isPerfectSquareForAlbaNumber(AlbaNumber const& value);
bool isPerfectNthPowerForAlbaNumber(AlbaNumber const& number, unsigned int const nthPower);


//Digit related functions
template <typename NumberType> unsigned int getNumberOfIntegerDigits(NumberType const value)
{
    unsigned int result(0);
    NumberType absoluteValue(getAbsoluteValue(value));
    if(absoluteValue >= 1)
    {
        result = static_cast<unsigned int>(log10(static_cast<double>(absoluteValue)))+1;
    }
    return result;
}
bool areNumberOfDigitsOnTheIntegerLimit(unsigned int const digits);

//Complex number related functions
AlbaComplexNumber<float> createComplexNumberFromData(AlbaNumber::ComplexNumberData const& data);
template <typename NumberType> AlbaNumber createNumberFromComplexNumber(AlbaComplexNumber<NumberType> const& number);void saveToComplexNumberData(AlbaNumber::ComplexNumberData & data, AlbaComplexNumber<float> const& number);

}//namespace mathHelper

}//namespace alba
