#pragma once

#include <Math/AlbaNumber.hpp>

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

template <typename NumberType> bool isAlmostEqual(NumberType const value1, NumberType const value2);
template <typename NumberType> NumberType getDistance(NumberType const value1, NumberType const value2);
template <typename NumberType> NumberType getAverage(NumberType const value1, NumberType const value2);
template <typename NumberType> NumberType getAverage(NumberType const value1, NumberType const value2, NumberType const value3);
template <typename NumberType> NumberType getAbsoluteValue(NumberType const& value);
template <typename NumberType> unsigned int getNumberOfIntegerDigits(NumberType const value);
template <typename NumberType> NumberType getXSquaredPlusYSquared(NumberType const x, NumberType const y);
template <typename NumberType> NumberType getSquareRootOfXSquaredPlusYSquared(NumberType const x, NumberType const y);
template <typename NumberType> NumberType getSquareRootOfXSquaredPlusYSquaredPlusZSquared(NumberType const x, NumberType const y, NumberType const z);
template <typename NumberType> NumberType getSign(NumberType const& value);
template <typename NumberType> NumberType clampLowerBound(NumberType const value, NumberType const limit);
template <typename NumberType> NumberType clampHigherBound(NumberType const value, NumberType const limit);
template <typename NumberType> bool isPerfectSquare(NumberType const& value);
template <typename NumberType> bool isPerfectCube(NumberType const& value);

bool isDivisible(unsigned int const dividend, unsigned int const divisor);
bool isEven(unsigned int const number);
bool isOdd(unsigned int const number);
bool isPerfectNthPower(unsigned int const valueToCheck, unsigned int const nthPower);
bool isPerfectNthPower(AlbaNumber const& number, unsigned int const nthPower);
bool isAlmostEqual(double const value1, double const value2, double const differenceTolerance);
bool canConvertedToInteger(double const realValue);
bool canConvertedToInteger(double const realValue, double const differenceTolerance);
bool areNumberOfDigitsOnTheIntegerLimit(unsigned int const digits);
double getPi();
double getE();
int getRaiseToPowerForIntegers(int const base, unsigned int exponent);
FractionDetails getFractionDetailsInLowestForm(int const numerator, int const denominator);
FractionDetails getBestFractionDetailsForDoubleValue(double const doubleValue);
unsigned int getGreatestCommonFactor(unsigned int const firstNumber, unsigned int const secondNumber);
AlbaNumber getGreatestCommonFactor(AlbaNumber const& firstNumber, AlbaNumber const& secondNumber);
unsigned int getLeastCommonMultiple(unsigned int const firstNumber, unsigned int const secondNumber);
AlbaNumber getLeastCommonMultiple(AlbaNumber const& firstNumber, AlbaNumber const& secondNumber);
unsigned int getDifferenceFromGreaterMultiple(unsigned int const multiple, unsigned int const number);
int getIntegerAfterRoundingDoubleValue(double const doubleValue);
int getIntegerPartInDouble(double const doubleValue);
double getFractionalPartInDouble(double const doubleValue);
double calculateCumulativeStandardDistributionApproximation(double const value);
double calculateInverseCumulativeStandardDistributionApproximation(double const p, unsigned int const numberOfIterations);
double convertDegreesToRadians(double const valueInDegrees);
double convertRadiansToDegrees(double const valueInRadians);

}//namespace mathHelper

}//namespace alba
