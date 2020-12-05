#pragma once

namespace alba
{

namespace mathHelper
{
template <typename NumberType> NumberType getAverage(NumberType const value1, NumberType const value2);
template <typename NumberType> NumberType getAbsoluteValue(NumberType const value);
template <typename NumberType> NumberType getSign(NumberType const value);
template <typename NumberType> NumberType clampLowerBound(NumberType const value, NumberType const limit);
template <typename NumberType> NumberType clampHigherBound(NumberType const value, NumberType const limit);
unsigned int getDifferenceFromGreaterMultiple(unsigned int const multiple, unsigned int const number);
unsigned int getNumberOfMultiplesInclusive(unsigned int const multiple, unsigned int const number);
double calculateCumulativeStandardDistributionApproximation(double const value);
double calculateInverseCumulativeStandardDistributionApproximation(double const p, unsigned int const numberOfIterations);
double getPi();
double getE();
}

}//namespace alba
