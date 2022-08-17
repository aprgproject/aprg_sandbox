#pragma once

#include <Common/Bit/AlbaBitValueUtilities.hpp>
#include <Common/Math/AlbaMathConstants.hpp>
#include <Common/Math/Number/AlbaNumber.hpp>
#include <Common/Math/Number/AlbaNumberTypes.hpp>
#include <algorithm>
#include <vector>
namespace alba
{

namespace mathHelper
{

enum class RootType
{
    RealRootsOnly,
    RealAndImaginaryRoots,
};

struct FractionDetails
{
    int sign;
    unsigned int numerator;
    unsigned int denominator;
};

// Some functions are inline because they are short


//Constants
inline double getPi()
{
    return PI_DOUBLE_VALUE;
}

inline double getE()
{
    return E_DOUBLE_VALUE;
}

//Conversion functions
inline double convertDegreesToRadians(double const valueInDegrees)
{
    return valueInDegrees / 180 * getPi();
}

inline double convertRadiansToDegrees(double const valueInRadians)
{
    return valueInRadians / getPi() * 180;
}

//Precision related functions
template <typename NumberType> inline NumberType getAbsoluteValue(NumberType const value);
template <typename NumberType> inline bool isAlmostEqual(NumberType const value1, NumberType const value2)
{
    return value1==value2;
}
template <> inline bool isAlmostEqual<float>(float const value1, float const value2)
{
    return value1 == value2 || getAbsoluteValue(value1-value2) < COMPARISON_TOLERANCE_FOR_FLOAT;
}
template <> inline bool isAlmostEqual<double>(double const value1, double const value2)
{
    return value1 == value2 || getAbsoluteValue(value1-value2) < COMPARISON_TOLERANCE_FOR_DOUBLE;
}
inline bool isAlmostEqual(double const value1, double const value2, double const differenceTolerance)
{
    return value1 == value2 || getAbsoluteValue(value1-value2) <= differenceTolerance;
}
template <typename NumberType1, typename NumberType2> inline bool isAlmostAnInteger(NumberType1 const value)
{
    return isAlmostEqual(
                value,
                static_cast<NumberType1>(static_cast<NumberType2>(round(value))));
}
inline bool isAlmostAnInteger(double const value, double const differenceTolerance)
{
    return isAlmostEqual(value, round(value), differenceTolerance);
}
template <typename NumberType> bool isValueBeyondLimits(double const value);
template <typename NumberType> NumberType getIntegerAfterRoundingADoubleValue(double const doubleValue)
{
    return static_cast<NumberType>(round(doubleValue));
}
template <typename NumberType> NumberType getIntegerAfterFloorOfDoubleValue(double const doubleValue)
{
    return static_cast<NumberType>(floor(doubleValue));
}
template <typename NumberType> NumberType getIntegerAfterCeilingOfDoubleValue(double const doubleValue)
{
    return static_cast<NumberType>(ceil(doubleValue));
}
int getIntegerPartInDouble(double const doubleValue);
double getFractionalPartInDouble(double const doubleValue);
AlbaNumber convertIfInfinityToNearestFiniteValue(AlbaNumber const& value);


//Sign related functions
template <typename NumberType> inline NumberType getAbsoluteValue(NumberType const value)
{
    return (value<0) ? value*-1 : value;
}
template <> inline unsigned int getAbsoluteValue<unsigned int>(unsigned int const value)
{
    return value;
}
inline AlbaNumber getAbsoluteValue(AlbaNumber const& value) // pass as const reference
{
    return (value<0) ? value*-1 : value;
}
template <typename NumberType> inline NumberType getSign(NumberType const value)
{
    return (value<0) ? -1 : 1;
}
template <> inline unsigned int getSign<unsigned int>(unsigned int const)
{
    return 1;
}
inline AlbaNumber getSign(AlbaNumber const& value) // pass as const reference
{
    return (value<0) ? -1 : 1;
}
template <typename NumberType> NumberType getPositiveDelta(NumberType const value1, NumberType const value2)
{
    std::pair<NumberType, NumberType> minMaxPair = std::minmax(value1, value2);
    return minMaxPair.second-minMaxPair.first;
}
inline AlbaNumber getPositiveDelta(AlbaNumber const& value1, AlbaNumber const& value2) // pass as const reference
{
    std::pair<AlbaNumber, AlbaNumber> minMaxPair = std::minmax(value1, value2);
    return minMaxPair.second-minMaxPair.first;
}
inline int convertToIntegerThenSubtract(unsigned int const number1, unsigned int const number2)
{
    return static_cast<int>(number1)-static_cast<int>(number2);
}


//Computation functions
template <typename NumberType> inline NumberType getAverage(NumberType const value1, NumberType const value2)
{
    return (value1+value2)/2;
}
inline AlbaNumber getAverage(AlbaNumber const& value1, AlbaNumber const& value2)  // pass as const reference
{
    return (value1+value2)/2;
}
template <typename NumberType> inline NumberType getAverage(NumberType const value1, NumberType const value2, NumberType const value3)
{
    return (value1+value2+value3)/3;
}
template <typename NumberType> inline NumberType getXSquaredPlusYSquared(NumberType const x, NumberType const y)
{
    return static_cast<NumberType>(pow(x, 2)+pow(y, 2));
}
template <typename NumberType> inline NumberType getSquareRootOfXSquaredPlusYSquared(NumberType const x, NumberType const y)
{
    return static_cast<NumberType>(pow(pow(x, 2)+pow(y, 2), 0.5));
}
template <typename NumberType> inline NumberType getSquareRootOfXSquaredPlusYSquaredPlusZSquared(NumberType const x, NumberType const y, NumberType const z)
{
    return static_cast<NumberType>(pow(pow(x, 2)+pow(y, 2)+pow(z, 2), 0.5));
}
double getLogarithm(double const base, double const inputForLogarithm);
unsigned int getIterativeLogarithm(double const base, double const inputForLogarithm);
int getSuperLogarithm(double const base, double const inputForLogarithm);
AlbaNumbers getQuadraticRoots(RootType const rootType, AlbaNumber const& a, AlbaNumber const& b, AlbaNumber const& c);


//Combinatorics functions

template <typename NumberType> NumberType getFactorial(NumberType const number)
{
    NumberType result(1);
    for(NumberType currentNumber=number; currentNumber>1; currentNumber--)
    {
        result *= currentNumber;
    }
    return result;
}

template <typename NumberType> NumberType getNumberOfPermutations(NumberType const n, NumberType const r)
{
    NumberType result(0);
    if(n >= r)
    {
        result = 1;
        for(NumberType currentNumber=n; currentNumber>n-r; currentNumber--)
        {
            result *= currentNumber;
        }
    }
    return result;
}

template <typename NumberType> NumberType getNumberOfCombinations(NumberType const n, NumberType const r)
{
    NumberType result(0);
    if(n >= r)
    {
        result = 1;
        for(NumberType currentNumber=n; currentNumber>n-r; currentNumber--)
        {
            result *= currentNumber;
        }
        for(NumberType currentNumber=r; currentNumber>1; currentNumber--)
        {
            result /= currentNumber;
        }
    }
    return result;
}

template <typename NumberType> NumberType getFibonacci(NumberType const number)
{
    // Binets formula:
    double sqrtOf5 = sqrt(5);
    double fibonacciInDouble = (pow(1+sqrtOf5, number)-pow(1-sqrtOf5, number)) / (pow(2, number)*sqrtOf5);
    return getIntegerAfterRoundingADoubleValue<NumberType>(fibonacciInDouble);
}

template <typename NumberType> NumberType getValueAtPascalTriangle(NumberType const rowIndex, NumberType const columnIndex)
{
    return getNumberOfCombinations(rowIndex, columnIndex);
}

int getStirlingNumberOfTheSecondKind(unsigned int const n, unsigned int const k);

//Statistics functions
double getCumulativeStandardDistributionApproximation(double const z);double getInverseCumulativeStandardDistributionApproximation(double const p, unsigned int const numberOfIterations);


//Clamp functions
template <typename NumberType> inline NumberType clampLowerBound(NumberType const value, NumberType const limit)
{
    return (value<limit) ? limit : value;
}
template <typename NumberType> inline NumberType clampHigherBound(NumberType const value, NumberType const limit)
{
    return (value>limit) ? limit : value;
}

//Divisibility functions
template <typename NumberType> bool isDivisible(NumberType const dividend, NumberType const divisor)
{
    bool result(false);
    if(divisor != 0)
    {
        result = (dividend % divisor)==0;
    }
    return result;
}
template <typename NumberType> bool isEven(NumberType const number)
{
    return isDivisible(number, 2U);
}
template <typename NumberType> bool isOdd(NumberType const number)
{
    return !isDivisible(number, 2U);
}



//Factor and multiple related functions

template <typename NumberType> bool isPrime(NumberType const number)
{
    // Non prime would have: a * b = nonPrimeNumber, where a and b are integers
    // To have less iterations:
    // When a = b, then we can test if divisible until nonPrimeNumber^0.5
    // When a > b, then we can test if divisible until b. Since b < nonPrimeNumber^0.5, then we can test until nonPrimeNumber^0.5.
    // When a < b, then we can test if divisible until a. Since a < nonPrimeNumber^0.5, then we can test until nonPrimeNumber^0.5.
    bool result(number>=2);
    NumberType limit(pow(number, 0.5));
    for(NumberType i=2; i<=limit; i++)
    {
        if(isDivisible(number, i))
        {
            result = false;
            break;
        }
    }
    return result;
}

template <typename NumberType> NumberType getGreatestPowerOf2Factor(NumberType const number)
{
    return AlbaBitValueUtilities<NumberType>::getGreatestPowerOf2Factor(number);
}

template <typename NumberType> NumberType getGreatestCommonFactor(NumberType const firstNumber, NumberType const secondNumber)
{
    NumberType result(0);
    NumberType temporaryFirstNumber(firstNumber);
    NumberType temporarySecondNumber(secondNumber);
    while(true)
    {
        if(temporaryFirstNumber==0)
        {
            result = temporarySecondNumber;
            break;
        }
        else if(temporarySecondNumber==0)
        {
            result = temporaryFirstNumber;
            break;
        }
        else if(temporaryFirstNumber>temporarySecondNumber)
        {
            temporaryFirstNumber = temporaryFirstNumber%temporarySecondNumber;
        }
        else
        {
            temporarySecondNumber = temporarySecondNumber%temporaryFirstNumber;
        }
    }
    return result;
}

AlbaNumber getGreatestCommonFactor(AlbaNumber const& firstNumber, AlbaNumber const& secondNumber); // different implementation

template <typename NumberType> NumberType getLeastCommonMultiple(NumberType const firstNumber, NumberType const secondNumber)
{
    NumberType result(0);
    if(firstNumber!=0 && secondNumber!=0)
    {
        result = firstNumber/getGreatestCommonFactor(firstNumber, secondNumber)*secondNumber;
    }
    return result;
}

AlbaNumber getLeastCommonMultiple(AlbaNumber const& firstNumber, AlbaNumber const& secondNumber); // different implementation

template <typename NumberType> double getLeastCommonMultipleInDouble(NumberType const firstNumber, NumberType const secondNumber)
{
    double result(0);
    if(firstNumber!=0 && secondNumber!=0)
    {
        result = static_cast<double>(firstNumber)/getGreatestCommonFactor(firstNumber, secondNumber)*secondNumber;
    }
    return result;
}

template <typename NumberType> NumberType getNumberOfMultiplesInclusive(
        NumberType const multiple,
        NumberType const number)
{
    NumberType result(0);
    if(multiple>0)
    {
        result = ((number+multiple-1)/multiple);
    }
    return result;
}

template <typename NumberType> NumberType getDifferenceFromGreaterMultiple(NumberType const multiple, NumberType const number)
{
    unsigned result(0);
    if(multiple>0)
    {
        NumberType numberOfMultiples(getNumberOfMultiplesInclusive(multiple, number));
        result = (numberOfMultiples*multiple) - number;
    }
    return result;
}



//Fraction related functions
template <typename NumberType1, typename NumberType2>
FractionDetails getFractionDetailsInLowestForm(NumberType1 const numerator, NumberType2 const denominator);FractionDetails getBestFractionDetailsForDoubleValue(double const doubleValue);


//Power related functionstemplate <typename NumberType> bool isPerfectNthPower(NumberType const value, NumberType const nthPower); // declare this first
template <typename NumberType> bool isPowerOfTwo(NumberType const value); // keep this template manually instantiated to remove dependency to bit utilities
template <typename NumberType> bool isPerfectSquare(NumberType const value)
{
    return isPerfectNthPower(value, static_cast<NumberType>(2));
}
template <typename NumberType> bool isPerfectCube(NumberType const value)
{
    return isPerfectNthPower(value, static_cast<NumberType>(3));
}
template <typename NumberType> bool isPerfectNthPower(NumberType const value, NumberType const nthPower)
{
    return isAlmostAnInteger<double, NumberType>(pow(value, static_cast<double>(1)/nthPower));
}
bool isPerfectSquare(AlbaNumber const& value); // pass as const reference
bool isPerfectCube(AlbaNumber const& value); // pass as const reference
bool isPerfectNthPower(AlbaNumber const& number, unsigned int const nthPower); // different implementation
int getRaiseToPowerForIntegers(int const base, unsigned int exponent);


//Digit related functions
template <typename NumberType> unsigned int getNumberOfDigitsOnBase(NumberType const base, NumberType const value)
{
    unsigned int result(0);
    NumberType absoluteValue(getAbsoluteValue(value));
    if(absoluteValue >= 1)
    {
        result = static_cast<NumberType>(getLogarithm(base, absoluteValue)) + 1;
    }
    return result;
}

template <typename NumberType> unsigned int getNumberOfIntegerDigits(NumberType const value)
{
    return getNumberOfDigitsOnBase<NumberType>(10, value);
}

template <typename NumberType> inline bool areNumberOfDigitsOnTheIntegerLimit(unsigned int const digits)
{
    return digits >= std::numeric_limits<NumberType>::digits10;
}


//Complex number related functions
AlbaComplexNumber<float> createComplexNumberFromData(AlbaNumber::ComplexNumberData const& data);
template <typename NumberType> AlbaNumber createNumberFromComplexNumber(AlbaComplexNumber<NumberType> const& number);
void saveToComplexNumberData(AlbaNumber::ComplexNumberData & data, AlbaComplexNumber<float> const& number);

}//namespace mathHelper

}//namespace alba
