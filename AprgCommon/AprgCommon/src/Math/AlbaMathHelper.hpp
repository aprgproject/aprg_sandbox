#pragma once

#include <Math/AlbaNumber.hpp>
#include <Math/AlbaNumberTypes.hpp>

#include <vector>
namespace alba
{
namespace mathHelper
{

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
template <typename NumberType> bool isAlmostEqual(NumberType const value1, NumberType const value2);
bool isAlmostEqual(AlbaNumber const& number1, AlbaNumber const& number2);
bool isAlmostEqual(double const value1, double const value2, double const differenceTolerance);
template <typename NumberType> bool isAlmostAnInteger(double const value);
bool isAlmostAnInteger(double const value, double const differenceTolerance);template <typename NumberType> bool isValueBeyondLimits(double const value);
template <> bool isValueBeyondLimits<int>(double const value);
template <> bool isValueBeyondLimits<unsigned int>(double const value);
template <> bool isValueBeyondLimits<short int>(double const value);
template <> bool isValueBeyondLimits<long int>(double const value);
template <> bool isValueBeyondLimits<unsigned long int>(double const value);
template <> bool isValueBeyondLimits<long long int>(double const value);
template <> bool isValueBeyondLimits<unsigned long long int>(double const value);
template <typename NumberType> NumberType getIntegerAfterRoundingDoubleValue(double const doubleValue);
int getIntegerPartInDouble(double const doubleValue);
double getFractionalPartInDouble(double const doubleValue);


//Sign related functions
template <typename NumberType> NumberType getAbsoluteValue(NumberType const value);
AlbaNumber getAbsoluteValue(AlbaNumber const& value);
template <typename NumberType> NumberType getSign(NumberType const value);
AlbaNumber getSign(AlbaNumber const& value);
template <typename NumberType> NumberType getPositiveDelta(NumberType const value1, NumberType const value2);
AlbaNumber getPositiveDelta(AlbaNumber const& value1, AlbaNumber const& value2);
int convertToIntegerThenSubtract(unsigned int const number1, unsigned int const number2);


//Computation functions
template <typename NumberType> NumberType getAverage(NumberType const value1, NumberType const value2);
AlbaNumber getAverage(AlbaNumber const& value1, AlbaNumber const& value2);
template <typename NumberType> NumberType getAverage(NumberType const value1, NumberType const value2, NumberType const value3);
template <typename NumberType> NumberType getXSquaredPlusYSquared(NumberType const x, NumberType const y);
template <typename NumberType> NumberType getSquareRootOfXSquaredPlusYSquared(NumberType const x, NumberType const y);
template <typename NumberType> NumberType getSquareRootOfXSquaredPlusYSquaredPlusZSquared(NumberType const x, NumberType const y, NumberType const z);
double calculateCumulativeStandardDistributionApproximation(double const value);
double calculateInverseCumulativeStandardDistributionApproximation(double const p, unsigned int const numberOfIterations);
AlbaNumbers calculateQuadraticRoots(AlbaNumber const& a, AlbaNumber const& b, AlbaNumber const& c);


//Clamp functionstemplate <typename NumberType> NumberType clampLowerBound(NumberType const value, NumberType const limit);
template <typename NumberType> NumberType clampHigherBound(NumberType const value, NumberType const limit);

//Divisibility functions
bool isDivisible(unsigned int const dividend, unsigned int const divisor);
bool isEven(unsigned int const number);
bool isOdd(unsigned int const number);


//Factor and multiple related functions
unsigned int getGreatestCommonFactor(unsigned int const firstNumber, unsigned int const secondNumber);
AlbaNumber getGreatestCommonFactor(AlbaNumber const& firstNumber, AlbaNumber const& secondNumber);
unsigned int getLeastCommonMultiple(unsigned int const firstNumber, unsigned int const secondNumber);
AlbaNumber getLeastCommonMultiple(AlbaNumber const& firstNumber, AlbaNumber const& secondNumber);
double getLeastCommonMultipleInDouble(unsigned int const firstNumber, unsigned int const secondNumber);
unsigned int getDifferenceFromGreaterMultiple(unsigned int const multiple, unsigned int const number);


//Fraction related functions
template <typename NumberType1, typename NumberType2>
FractionDetails getFractionDetailsInLowestForm(NumberType1 const numerator, NumberType2 const denominator);
FractionDetails getBestFractionDetailsForDoubleValue(double const doubleValue);


//Power related functions
template <typename NumberType> bool isPerfectCube(NumberType const value);
bool isPerfectCube(AlbaNumber const& value);
template <typename NumberType> bool isPerfectSquare(NumberType const value);
bool isPerfectSquare(AlbaNumber const& value);
bool isPerfectNthPower(unsigned int const valueToCheck, unsigned int const nthPower);
bool isPerfectNthPower(AlbaNumber const& number, unsigned int const nthPower);
int getRaiseToPowerForIntegers(int const base, unsigned int exponent);


//Digit related functions
template <typename NumberType> unsigned int getNumberOfIntegerDigits(NumberType const value);
bool areNumberOfDigitsOnTheIntegerLimit(unsigned int const digits);



}//namespace mathHelper

}//namespace alba
