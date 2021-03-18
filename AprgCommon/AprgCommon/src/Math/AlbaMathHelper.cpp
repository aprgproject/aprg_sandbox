#include "AlbaMathHelper.hpp"

#include <algorithm>
#include <cmath>

using namespace std;

namespace alba
{

namespace mathHelper
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

//end of internal functions



//isConsideredEqual
template <typename NumberType>
bool isConsideredEqual(NumberType const value1, NumberType const value2)
{
    constexpr double tolerance(0.00000000001);
    double absoluteMinValue = min(getAbsoluteValue(value1), getAbsoluteValue(value2));
    double scale = absoluteMinValue < tolerance ? 1 : absoluteMinValue;
    double scaledDifference(getAbsoluteValue(value1 - value2)/scale);
    return scaledDifference < tolerance;
}
template bool isConsideredEqual<double>(double const value1, double const value2);

template <>
bool isConsideredEqual<int>(int const value1, int const value2)
{
    return value1==value2;
}

template <>
bool isConsideredEqual<unsigned int>(unsigned int const value1, unsigned int const value2)
{
    return value1==value2;
}


//getDistance
template <typename NumberType>
NumberType getDistance(NumberType const value1, NumberType const value2)
{
    std::pair<NumberType, NumberType> minMaxPair = std::minmax(value1, value2);
    return minMaxPair.second-minMaxPair.first;
}
template unsigned int getDistance<unsigned int>(unsigned int const value1, unsigned int const value2);
template int getDistance<int>(int const value1, int const value2);


//getAverage
template <typename NumberType>
NumberType getAverage(NumberType const value1, NumberType const value2)
{
    return (value1+value2)/2;
}
template unsigned int getAverage<unsigned int>(unsigned int const value1, unsigned int const value2);
template int getAverage<int>(int const value1, int const value2);
template double getAverage<double>(double const value1, double const value2);


//getAbsoluteValue
template <typename NumberType>
NumberType getAbsoluteValue(NumberType const value)
{
    return (value<0) ? value*-1 : value;
}
template int getAbsoluteValue<int>(int const value);
template double getAbsoluteValue<double>(double const value);


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


//getSign
template <typename NumberType>
NumberType getSign(NumberType const value)
{
    return (value<0) ? -1 : 1;
}
template int getSign<int>(int const value);
template double getSign<double>(double const value);


//clampLowerBound
template <typename NumberType>
NumberType clampLowerBound(NumberType const value, NumberType const limit)
{
    return (value<limit) ? limit : value;
}
template int clampLowerBound<int>(int const value, int const limit);
template double clampLowerBound<double>(double const value, double const limit);


//clampHigherBound
template <typename NumberType>
NumberType clampHigherBound(NumberType const value, NumberType const limit)
{
    return (value>limit) ? limit : value;
}
template int clampHigherBound<int>(int const value, int const limit);
template double clampHigherBound<double>(double const value, double const limit);


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
        if(isConsideredEqual(probability, probabilityLowest))
        {
            z=lowestZ;
            break;
        }
        else if(isConsideredEqual(probability, probabilityMiddle))
        {
            z=middleZ;
            break;
        }
        else if(isConsideredEqual(probability, probabilityHighest))
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

double getPi()
{
    return 3.14159265358979323846;
}

double getE()
{
    return 2.7182818284590452354;
}

}//namespace mathHelper

}//namespace alba
