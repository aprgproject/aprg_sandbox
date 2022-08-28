#include "AlbaMathHelper.hpp"

#include <cmath>
#include <limits>

using namespace std;

namespace alba
{

namespace mathHelper
{

namespace
{
//internal functions

using Integers=vector<int>;
using UnsignedIntegers=vector<unsigned int>;

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
    if(!calculatedPartialNumerators.empty())
    {
        numerator = calculatedPartialNumerators.at(calculatedPartialNumerators.size()-1);
        denominator = 1;
        for(int i=calculatedPartialNumerators.size()-2; i>=0; i--)
        {
            double previousNumerator = numerator;
            numerator = (calculatedPartialNumerators.at(i) * numerator) + denominator;
            denominator = previousNumerator;
            isBeyondUnsignedIntegerLimits =
                    isValueBeyondLimits<unsigned int>(numerator) || isValueBeyondLimits<unsigned int>(denominator);
            if(isBeyondUnsignedIntegerLimits) { break; }
        }
    }
    return FractionDetails{
        1,
        getIntegerAfterRoundingADoubleValue<unsigned int>(numerator),
                getIntegerAfterRoundingADoubleValue<unsigned int>(denominator)};
}

//end of internal functions
}


//isAlmostEqual
//Commented out: This implementation is not practical when value is equal to zero
//template <> bool isAlmostEqual<double>(double const value1, double const value2)
//{
//    constexpr double absoluteScaledDifferenceTolerance(1E-12);
//    double absoluteMaxValue = max(getAbsoluteValue(value1), getAbsoluteValue(value2));
//    double difference = getAbsoluteValue(value1-value2);
//    return difference <= absoluteMaxValue*absoluteScaledDifferenceTolerance;
//}


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

unsigned int getIterativeLogarithm(double const base, double const inputForLogarithm)
{
    // The iterated logarithm of n, written log* n (usually read "log star"),
    // is the number of times the logarithm function must be iteratively applied before the result is less than or equal to 1.
    unsigned int count(0);
    double currentLogarithm = getLogarithm(base, inputForLogarithm);
    while(currentLogarithm >= 0 && !isAlmostEqual(currentLogarithm, 1.0) )
    {
        count++;
        currentLogarithm = getLogarithm(base, currentLogarithm);
    }
    return count;
}

int getSuperLogarithm(double const base, double const inputForLogarithm)
{
    // In mathematics, the super-logarithm is one of the two inverse functions of tetration.
    // On the positive real numbers, the continuous super-logarithm (inverse tetration) is essentially equivalent
    // However, on the negative real numbers, log-star is 0, whereas the superlogarithm = -1
    int result(0);
    if(inputForLogarithm >= 0)
    {
        result = static_cast<int>(getIterativeLogarithm(base, inputForLogarithm));
    }
    else
    {
        result = -1;
    }
    return result;
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



//Combinatorics functions

int getStirlingNumberOfTheSecondKind(unsigned int const n, unsigned int const k)
{
    // In mathematics, particularly in combinatorics, a Stirling number of the second kind (or Stirling partition number)
    // is the number of ways to partition a set of n objects into k non-empty subsets

    // Stirling numbers of the second kind occur in the field of mathematics called combinatorics and the study of partitions.

    AlbaNumber sum(0);
    for(unsigned int i=0; i<=k; i++)
    {
        int sign = isDivisible(i, 2U) ? 1 : -1;
        sum += AlbaNumber(sign) * getNumberOfCombinations(k, i) * pow(k-i, n);
    }
    sum /= getFactorial(k);
    return static_cast<int>(sum.getInteger());
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
        result = AlbaNumber::createFraction(static_cast<int>(gcfNumerator), lcmDenominator);
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



template <typename NumberType>
bool isPowerOfTwo(NumberType const value)
{
    return AlbaBitValueUtilities<NumberType>::isPowerOfTwo(value);
}
template bool isPowerOfTwo<unsigned int>(unsigned int const value);

bool isPerfectCube(AlbaNumber const& value)
{
    return isPerfectNthPower(value, 3);
}

bool isPerfectSquare(AlbaNumber const& value)
{
    return isPerfectNthPower(value, 2);
}

bool isPerfectNthPower(
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

int getRaiseToPowerForIntegers(int const base, unsigned int exponent)
{
    return static_cast<int>(ceil(pow(base, exponent)));
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
