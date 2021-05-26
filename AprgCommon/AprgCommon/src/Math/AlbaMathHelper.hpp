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

bool isDivisible(unsigned int const largerValue, unsigned int const smallerValue);
template <typename NumberType> bool isAlmostEqual(NumberType const value1, NumberType const value2);
template <typename NumberType> NumberType getDistance(NumberType const value1, NumberType const value2);
template <typename NumberType> NumberType getAverage(NumberType const value1, NumberType const value2);template <typename NumberType> NumberType getAverage(NumberType const value1, NumberType const value2, NumberType const value3);
template <typename NumberType> NumberType getAbsoluteValue(NumberType const value);
template <typename NumberType> NumberType getXSquaredPlusYSquared(NumberType const x, NumberType const y);
template <typename NumberType> NumberType getSquareRootOfXSquaredPlusYSquared(NumberType const x, NumberType const y);template <typename NumberType> NumberType getSquareRootOfXSquaredPlusYSquaredPlusZSquared(NumberType const x, NumberType const y, NumberType const z);
template <typename NumberType> NumberType getSign(NumberType const value);
template <typename NumberType> NumberType clampLowerBound(NumberType const value, NumberType const limit);
template <typename NumberType> NumberType clampHigherBound(NumberType const value, NumberType const limit);
FractionDetails getFractionDetailsInLowestForm(int const numerator, int const denominator);
unsigned int getGreatestCommonFactor(unsigned int const firstNumber, unsigned int const secondNumber);
unsigned int getLeastCommonMultiple(unsigned int const firstNumber, unsigned int const secondNumber);
unsigned int getDifferenceFromGreaterMultiple(unsigned int const multiple, unsigned int const number);
double calculateCumulativeStandardDistributionApproximation(double const value);
double calculateInverseCumulativeStandardDistributionApproximation(double const p, unsigned int const numberOfIterations);double getPi();
double getE();
double convertDegreesToRadians(double const valueInDegrees);
double convertRadiansToDegrees(double const valueInRadians);
}//namespace mathHelper

}//namespace alba
