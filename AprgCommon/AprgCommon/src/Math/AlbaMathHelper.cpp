#include "AlbaMathHelper.hpp"

#include <Math/AlbaMathConstants.hpp>

#include <algorithm>
#include <limits>
#include <cmath>

using namespace std;

namespace alba
{

namespace mathHelper
{

namespace
{
//internal functions

unsigned int getNumberOfMultiplesInclusive(
        unsigned int const multiple,
        unsigned int const number)
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
    double numerator(0), denominator(0);
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
    return PI_DOUBLE_VALUE;
}

double getE()
{
    return E_DOUBLE_VALUE;
}

double convertDegreesToRadians(double const valueInDegrees)
{
    return valueInDegrees / 180 * getPi();
}

double convertRadiansToDegrees(double const valueInRadians)
{
    return valueInRadians / getPi() * 180;
}


//isAlmostEqual
template <typename NumberType>
bool isAlmostEqual(NumberType const value1, NumberType const value2)
{
    return value1==value2;
}
template bool isAlmostEqual<unsigned int>(unsigned int const value1, unsigned int const value2);
template bool isAlmostEqual<int>(int const value1, int const value2);
template <> bool isAlmostEqual<float>(float const value1, float const value2)
{
    return value1 == value2 || getAbsoluteValue(value1-value2) < COMPARISON_TOLERANCE_FOR_FLOAT;
}
template <> bool isAlmostEqual<double>(double const value1, double const value2)
{
    return value1 == value2 || getAbsoluteValue(value1-value2) < COMPARISON_TOLERANCE_FOR_DOUBLE;
}
//Commented out: This implementation is not practical when value is equal to zero
//template <> bool isAlmostEqual<double>(double const value1, double const value2)
//{
//    constexpr double absoluteScaledDifferenceTolerance(1E-12);
//    double absoluteMaxValue = max(getAbsoluteValue(value1), getAbsoluteValue(value2));
//    double difference = getAbsoluteValue(value1-value2);
//    return difference <= absoluteMaxValue*absoluteScaledDifferenceTolerance;
//}


bool isAlmostEqual(AlbaNumber const& value1, AlbaNumber const& value2)
{
    return value1 == value2;
}


bool isAlmostEqual(double const value1, double const value2, double const differenceTolerance)
{
    return value1 == value2 || getAbsoluteValue(value1-value2) <= differenceTolerance;
}


//isAlmostAnInteger
template <typename NumberType1, typename NumberType2>
bool isAlmostAnInteger(NumberType1 const value)
{
    return isAlmostEqual(
                value,
                static_cast<NumberType1>(static_cast<NumberType2>(round(value))));
}
template bool isAlmostAnInteger<float, int>(float const value);
template bool isAlmostAnInteger<float, unsigned int>(float const value);
template bool isAlmostAnInteger<float, long long int>(float const value);
template bool isAlmostAnInteger<double, int>(double const value);
template bool isAlmostAnInteger<double, unsigned int>(double const value);
template bool isAlmostAnInteger<double, long long int>(double const value);


bool isAlmostAnInteger(double const value, double const differenceTolerance)
{
    return isAlmostEqual(value, round(value), differenceTolerance);
}


//isValueBeyondLimits
template <typename NumberType>
bool isValueBeyondLimits(double const value)
{
    return value < numeric_limits<NumberType>::min()
            || value > numeric_limits<NumberType>::max();
}
template bool isValueBeyondLimits<int>(double const value);
template bool isValueBeyondLimits<unsigned int>(double const value);
template bool isValueBeyondLimits<short int>(double const value);
template bool isValueBeyondLimits<long int>(double const value);
template bool isValueBeyondLimits<unsigned long int>(double const value);
template bool isValueBeyondLimits<long long int>(double const value);
template bool isValueBeyondLimits<unsigned long long int>(double const value);


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

AlbaNumber convertIfInfinityToNearestFiniteValue(AlbaNumber const& value)
{
    AlbaNumber result(value);
    if(value.isPositiveInfinity())
    {
        result = AlbaNumber(numeric_limits<double>::max());
    }
    else if(value.isNegativeInfinity())
    {
        result = AlbaNumber(-numeric_limits<double>::max());
    }
    return result;
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


//getSign
template <typename NumberType>
NumberType getSign(NumberType const value)
{
    return (value<0) ? -1 : 1;
}
template int getSign<int>(int const value);
template float getSign<float>(float const value);
template double getSign<double>(double const value);
template <> unsigned int getSign<unsigned int>(unsigned int const)
{
    return 1;
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

int convertToIntegerThenSubtract(unsigned int const number1, unsigned int const number2)
{
    return static_cast<int>(number1)-static_cast<int>(number2);
}

AlbaNumber getAbsoluteValueForAlbaNumber(AlbaNumber const& value)
{
    return (value<0) ? value*-1 : value;
}

AlbaNumber getSignForAlbaNumber(AlbaNumber const& value)
{
    return (value<0) ? -1 : 1;
}

AlbaNumber getPositiveDeltaForAlbaNumber(AlbaNumber const& value1, AlbaNumber const& value2)
{
    pair<AlbaNumber, AlbaNumber> minMaxPair = minmax(value1, value2);
    return minMaxPair.second-minMaxPair.first;
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
template float getXSquaredPlusYSquared<float>(float const x, float const y);
template double getXSquaredPlusYSquared<double>(double const x, double const y);


//getSquareRootOfXSquaredPlusYSquared
template <typename NumberType>
NumberType getSquareRootOfXSquaredPlusYSquared(NumberType const x, NumberType const y)
{
    return static_cast<NumberType>(pow(pow(x, 2)+pow(y, 2), 0.5));
}
template int getSquareRootOfXSquaredPlusYSquared<int>(int const x, int const y);
template float getSquareRootOfXSquaredPlusYSquared<float>(float const x, float const y);
template double getSquareRootOfXSquaredPlusYSquared<double>(double const x, double const y);


//getSquareRootOfXSquaredPlusYSquaredPlusZSquared
template <typename NumberType>
NumberType getSquareRootOfXSquaredPlusYSquaredPlusZSquared(NumberType const x, NumberType const y, NumberType const z)
{
    return static_cast<NumberType>(pow(pow(x, 2)+pow(y, 2)+pow(z, 2), 0.5));
}
template int getSquareRootOfXSquaredPlusYSquaredPlusZSquared<int>(int const x, int const y, int const z);
template double getSquareRootOfXSquaredPlusYSquaredPlusZSquared<double>(double const x, double const y, double const z);


double getLogarithm(double const base, double const inputForLogarithm)
{
    // change of base formula
    // log a(b) = C
    // -> b = a^C
    // -> log10(b) = log10(a^C)
    // -> log10(b) = C*log10(a)
    // -> C = log10(b)/log10(a)

    // log a(b) = log10(b) / log10(a)
    return log10(inputForLogarithm)/log10(base);
}

AlbaNumber getAverageForAlbaNumber(AlbaNumber const& value1, AlbaNumber const& value2){
    return (value1+value2)/2;
}
AlbaNumbers getQuadraticRealRoots(
        AlbaNumber const& a,
        AlbaNumber const& b,
        AlbaNumber const& c)
{
    AlbaNumbers result;
    AlbaNumber twoA = a*2;
    AlbaNumber firstPart((-b)/twoA);
    AlbaNumber discriminant((b^2)-(a*c*4));
    if(discriminant >= 0)
    {
        AlbaNumber discriminantSquaredRoot
                = discriminant^(AlbaNumber::createFraction(1, 2));
        AlbaNumber secondPart(discriminantSquaredRoot/twoA);
        result.emplace_back(firstPart + secondPart);
        result.emplace_back(firstPart - secondPart);
    }
    return result;
}

AlbaNumbers getQuadraticRoots(
        RootType const rootType,
        AlbaNumber const& a,
        AlbaNumber const& b,
        AlbaNumber const& c)
{
    AlbaNumbers result;
    AlbaNumber twoA = a*2;
    AlbaNumber firstPart((-b)/twoA);
    AlbaNumber discriminant((b^2)-(a*c*4));
    if(discriminant >= 0)
    {
        AlbaNumber discriminantSquaredRoot
                = discriminant^(AlbaNumber::createFraction(1, 2));
        AlbaNumber secondPart(discriminantSquaredRoot/twoA);
        result.emplace_back(firstPart + secondPart);
        result.emplace_back(firstPart - secondPart);
    }
    else if(RootType::RealAndImaginaryRoots == rootType)
    {
        AlbaComplexNumber<double> discriminantComplex(discriminant.getDouble(), 0.0);
        result.emplace_back(firstPart + createNumberFromComplexNumber(discriminantComplex.getNthRoot(0, 2))/twoA);
        result.emplace_back(firstPart + createNumberFromComplexNumber(discriminantComplex.getNthRoot(1, 2))/twoA);
    }
    return result;
}

unsigned int getFactorial(unsigned int const number)
{
    unsigned int result(1);
    for(unsigned int currentNumber=number; currentNumber>1; currentNumber--)
    {
        result *= currentNumber;
    }
    return result;
}

unsigned int getNumberOfPermutations(unsigned int const n, unsigned int const r)
{
    unsigned int result(0);
    if(n >= r)
    {
        result = 1;
        for(unsigned int currentNumber=n; currentNumber>n-r; currentNumber--)
        {
            result *= currentNumber;
        }
    }
    return result;
}

unsigned int getNumberOfCombinations(unsigned int const n, unsigned int const r)
{
    unsigned int result(0);
    if(n >= r)
    {
        result = 1;
        for(unsigned int currentNumber=n; currentNumber>n-r; currentNumber--)
        {
            result *= currentNumber;
        }
        for(unsigned int currentNumber=r; currentNumber>1; currentNumber--)
        {
            result /= currentNumber;
        }
    }
    return result;
}

unsigned int getValueAtPascalTriangle(unsigned int const rowIndex, unsigned int const columnIndex)
{
    return getNumberOfCombinations(rowIndex, columnIndex);
}

int getStirlingNumberOfTheSecondKind(unsigned int const n, unsigned int const k)
{
    //In mathematics, particularly in combinatorics, a Stirling number of the second kind (or Stirling partition number) is the number of ways to partition a set of n objects into k non-empty subsets
    // Stirling numbers of the second kind occur in the field of mathematics called combinatorics and the study of partitions.
    int sum=0;
    for(unsigned int i=0; i<=k; i++)
    {
        int sign = isDivisible(i, 2) ? 1 : -1;
        sum += sign * getNumberOfCombinations(k, i) * static_cast<unsigned int>(pow(k-i, n));
    }
    return sum / getFactorial(k);
}

double getCumulativeStandardDistributionApproximation(double const z)
{
    return 0.5 * erfc(-z * pow(0.5, 0.5));
}

double getInverseCumulativeStandardDistributionApproximation(double const probability, unsigned int const numberOfIterations)
{
    double lowestZ=-10, highestZ=10, z(0);
    for(unsigned int iterationCount=0; iterationCount<numberOfIterations; iterationCount++)
    {
        double middleZ = getAverage<double>(lowestZ, highestZ);
        double probabilityLowest = getCumulativeStandardDistributionApproximation(lowestZ);
        double probabilityMiddle = getCumulativeStandardDistributionApproximation(middleZ);
        double probabilityHighest = getCumulativeStandardDistributionApproximation(highestZ);
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
    return isDivisible(number, 2U);
}

bool isOdd(unsigned int const number)
{
    return !isDivisible(number, 2U);
}

unsigned int getGreatestCommonFactor(unsigned int const firstNumber, unsigned int const secondNumber)
{
    unsigned int result(0);
    unsigned int temporaryFirstValue(firstNumber);
    unsigned int temporarySecondValue(secondNumber);
    while(true)
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

unsigned int getLeastCommonMultiple(unsigned int const firstNumber, unsigned int const secondNumber)
{
    unsigned int result(0);
    if(firstNumber!=0 && secondNumber!=0)
    {
        result = firstNumber/getGreatestCommonFactor(firstNumber, secondNumber)*secondNumber;
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

AlbaNumber getGreatestCommonFactorForAlbaNumber(AlbaNumber const& firstNumber, AlbaNumber const& secondNumber)
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

AlbaNumber getLeastCommonMultipleForAlbaNumber(AlbaNumber const& firstNumber, AlbaNumber const& secondNumber)
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


//isPerfectSquare
template <typename NumberType>
bool isPerfectSquare(NumberType const value)
{
    return isPerfectNthPower(value, 2);
}
template bool isPerfectSquare<unsigned int>(unsigned int const value);


bool isPerfectNthPower(
        unsigned int const value,
        unsigned int const nthPower)
{
    double valueRaiseToTheReciprocal = pow(value, static_cast<double>(1)/nthPower);
    return isAlmostAnInteger<double, unsigned int>(valueRaiseToTheReciprocal);
}

int getRaiseToPowerForIntegers(int const base, unsigned int exponent)
{
    return static_cast<int>(ceil(pow(base, exponent)));
}

bool isPerfectCubeForAlbaNumber(AlbaNumber const& value)
{
    return isPerfectNthPowerForAlbaNumber(value, 3);
}

bool isPerfectSquareForAlbaNumber(AlbaNumber const& value)
{
    return isPerfectNthPowerForAlbaNumber(value, 2);
}

bool isPerfectNthPowerForAlbaNumber(
        AlbaNumber const& number,
        unsigned int const nthPower)
{
    bool result(false);
    if(number.isIntegerType())
    {
        int integerValue(static_cast<int>(number.getInteger()));
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

AlbaComplexNumber<float> createComplexNumberFromData(AlbaNumber::ComplexNumberData const& data)
{
    return AlbaComplexNumber<float>(data.realPart, data.imaginaryPart);
}


template <typename NumberType>
AlbaNumber createNumberFromComplexNumber(AlbaComplexNumber<NumberType> const& complexNumber)
{
    return AlbaNumber::createComplexNumber(complexNumber.getRealPart(), complexNumber.getImaginaryPart());
}
template AlbaNumber createNumberFromComplexNumber<double>(AlbaComplexNumber<double> const& value);


void saveToComplexNumberData(AlbaNumber::ComplexNumberData & data, AlbaComplexNumber<float> const& number)
{
    data.realPart = number.getRealPart();
    data.imaginaryPart = number.getImaginaryPart();
}

}//namespace mathHelper

}//namespace alba
