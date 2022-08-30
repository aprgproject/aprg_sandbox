#pragma once

#include <Common/Math/Number/AlbaNumberTypes.hpp>
#include <Common/Math/AlbaMathHelperTypes.hpp>

namespace alba
{

namespace mathHelper
{

//Constants
double getPi();
double getE();

//Conversion functions
double convertDegreesToRadians(double const valueInDegrees);
double convertRadiansToDegrees(double const valueInRadians);

//Precision related functions
template <typename NumberType> bool isAlmostEqual(NumberType const value1, NumberType const value2);
template <> bool isAlmostEqual<float>(float const value1, float const value2);
template <> bool isAlmostEqual<double>(double const value1, double const value2);
bool isAlmostEqual(double const value1, double const value2, double const differenceTolerance);
template <typename NumberType1, typename NumberType2> bool isAlmostAnInteger(NumberType1 const value);
bool isAlmostAnInteger(double const value, double const differenceTolerance);
template <typename NumberType> bool isValueBeyondLimits(double const value);
template <typename NumberType> NumberType getIntegerAfterRoundingADoubleValue(double const doubleValue);
template <typename NumberType> NumberType getIntegerAfterFloorOfDoubleValue(double const doubleValue);
template <typename NumberType> NumberType getIntegerAfterCeilingOfDoubleValue(double const doubleValue);
int getIntegerPartInDouble(double const doubleValue);
double getFractionalPartInDouble(double const doubleValue);
AlbaNumber convertIfInfinityToNearestFiniteValue(AlbaNumber const& value);

//Sign related functions
template <typename NumberType> NumberType getAbsoluteValue(NumberType const value);
template <> unsigned int getAbsoluteValue<unsigned int>(unsigned int const value);
AlbaNumber getAbsoluteValue(AlbaNumber const& value); // pass as const reference
template <typename NumberType> NumberType getSign(NumberType const value);
template <> unsigned int getSign<unsigned int>(unsigned int const);
AlbaNumber getSign(AlbaNumber const& value); // pass as const reference
template <typename NumberType> NumberType getPositiveDelta(NumberType const value1, NumberType const value2);
AlbaNumber getPositiveDelta(AlbaNumber const& value1, AlbaNumber const& value2); // pass as const reference
int convertToIntegerThenSubtract(unsigned int const number1, unsigned int const number2);

//Computation functions
template <typename NumberType> NumberType getAverage(NumberType const value1, NumberType const value2);
AlbaNumber getAverage(AlbaNumber const& value1, AlbaNumber const& value2);  // pass as const reference
template <typename NumberType> NumberType getAverage(NumberType const value1, NumberType const value2, NumberType const value3);
template <typename NumberType> NumberType getXSquaredPlusYSquared(NumberType const x, NumberType const y);
template <typename NumberType> NumberType getSquareRootOfXSquaredPlusYSquared(NumberType const x, NumberType const y);
template <typename NumberType> NumberType getSquareRootOfXSquaredPlusYSquaredPlusZSquared(NumberType const x, NumberType const y, NumberType const z);
double getLogarithm(double const base, double const inputForLogarithm);
unsigned int getIterativeLogarithm(double const base, double const inputForLogarithm);
int getSuperLogarithm(double const base, double const inputForLogarithm);
AlbaNumbers getQuadraticRoots(RootType const rootType, AlbaNumber const& a, AlbaNumber const& b, AlbaNumber const& c);

//Clamp functions
template <typename NumberType> NumberType clampLowerBound(NumberType const value, NumberType const limit);
template <typename NumberType> NumberType clampHigherBound(NumberType const value, NumberType const limit);

//Divisibility functions
template <typename NumberType> bool isDivisible(NumberType const dividend, NumberType const divisor);
template <typename NumberType> bool isEven(NumberType const number);
template <typename NumberType> bool isOdd(NumberType const number);

//Factor and multiple related functions
template <typename NumberType> bool isPrime(NumberType const number);
template <typename NumberType> NumberType getGreatestPowerOf2Factor(NumberType const number);
template <typename NumberType> NumberType getGreatestCommonFactor(NumberType const firstNumber, NumberType const secondNumber);
AlbaNumber getGreatestCommonFactor(AlbaNumber const& firstNumber, AlbaNumber const& secondNumber); // different implementation
template <typename NumberType> NumberType getLeastCommonMultiple(NumberType const firstNumber, NumberType const secondNumber);
AlbaNumber getLeastCommonMultiple(AlbaNumber const& firstNumber, AlbaNumber const& secondNumber); // different implementation
template <typename NumberType> double getLeastCommonMultipleInDouble(NumberType const firstNumber, NumberType const secondNumber);
template <typename NumberType> NumberType getNumberOfMultiplesInclusive(NumberType const multiple,  NumberType const number);
template <typename NumberType> NumberType getDifferenceFromGreaterMultiple(NumberType const multiple, NumberType const number);

//Fraction related functions
template <typename NumberType1, typename NumberType2>
FractionDetails getFractionDetailsInLowestForm(NumberType1 const numerator, NumberType2 const denominator);
FractionDetails getBestFractionDetailsForDoubleValue(double const doubleValue);

//Power related functions
template <typename NumberType> bool isPerfectNthPower(NumberType const value, NumberType const nthPower); // declare this first
template <typename NumberType> bool isPowerOfTwo(NumberType const value); // keep this template manually instantiated to remove dependency to bit utilities
template <typename NumberType> bool isPerfectSquare(NumberType const value);
template <typename NumberType> bool isPerfectCube(NumberType const value);
template <typename NumberType> bool isPerfectNthPower(NumberType const value, NumberType const nthPower);
bool isPerfectSquare(AlbaNumber const& value); // pass as const reference
bool isPerfectCube(AlbaNumber const& value); // pass as const reference
bool isPerfectNthPower(AlbaNumber const& number, unsigned int const nthPower); // different implementation
int getRaiseToPowerForIntegers(int const base, unsigned int exponent);

//Digit related functions
template <typename NumberType> unsigned int getNumberOfDigitsOnBase(NumberType const base, NumberType const value);
template <typename NumberType> unsigned int getNumberOfIntegerDigits(NumberType const value);
template <typename NumberType> bool areNumberOfDigitsOnTheIntegerLimit(unsigned int const digits);

//Combinatorics functions
template <typename NumberType> NumberType getFactorial(NumberType const number);
template <typename NumberType> NumberType getNumberOfPermutations(NumberType const n, NumberType const r);
template <typename NumberType> NumberType getNumberOfCombinations(NumberType const n, NumberType const r);
template <typename NumberType> NumberType getValueAtPascalTriangle(NumberType const rowIndex, NumberType const columnIndex);
int getStirlingNumberOfTheSecondKind(unsigned int const n, unsigned int const k);

//Statistics functions
double getCumulativeStandardDistributionApproximation(double const z);
double getInverseCumulativeStandardDistributionApproximation(double const p, unsigned int const numberOfIterations);

//Complex number related functions
AlbaComplexNumber<float> createComplexNumberFromData(AlbaNumber::ComplexNumberData const& data);
template <typename NumberType> AlbaNumber createNumberFromComplexNumber(AlbaComplexNumber<NumberType> const& number);
void saveToComplexNumberData(AlbaNumber::ComplexNumberData & data, AlbaComplexNumber<float> const& number);

}//namespace mathHelper

}//namespace alba
