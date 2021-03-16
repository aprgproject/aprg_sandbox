#include "AlbaMathHelper.hpp"

#include <algorithm>
#include <cmath>

using namespace std;

namespace alba
{

template <typename NumberType>
bool mathHelper::isConsideredEqual(NumberType const value1, NumberType const value2)
{
    constexpr double tolerance(0.00000000001);
    double scaledDifference(getAbsoluteValue(value1 - value2)/max(value1, value2));
    return scaledDifference < tolerance;
}

template <typename NumberType>
NumberType mathHelper::getDistance(NumberType const value1, NumberType const value2)
{
    std::pair<NumberType, NumberType> minMaxPair = std::minmax(value1, value2);
    return minMaxPair.second-minMaxPair.first;
}
template unsigned int mathHelper::getDistance<unsigned int>(unsigned int const value1, unsigned int const value2);

template <typename NumberType>
NumberType mathHelper::getAverage(NumberType const value1, NumberType const value2)
{
    return (value1+value2)/2;
}
template unsigned int mathHelper::getAverage<unsigned int>(unsigned int const value1, unsigned int const value2);
template int mathHelper::getAverage<int>(int const value1, int const value2);
template double mathHelper::getAverage<double>(double const value1, double const value2);


template <typename NumberType>
NumberType mathHelper::getAbsoluteValue(NumberType const value)
{
    return (value<0) ? value*-1 : value;
}
template int mathHelper::getAbsoluteValue<int>(int const value);
template double mathHelper::getAbsoluteValue<double>(double const value);


template <typename NumberType>
NumberType mathHelper::getSquareRootOfXSquaredPlusYSquared(NumberType const x, NumberType const y)
{
    return pow(pow(x, 2)+pow(y, 2), 0.5);
}
template double mathHelper::getSquareRootOfXSquaredPlusYSquared<double>(double const x, double const y);


template <typename NumberType>
NumberType mathHelper::getSquareRootOfXSquaredPlusYSquaredPlusZSquared(NumberType const x, NumberType const y, NumberType const z)
{
    return pow(pow(x, 2)+pow(y, 2)+pow(z, 2), 0.5);
}
template double mathHelper::getSquareRootOfXSquaredPlusYSquaredPlusZSquared<double>(double const x, double const y, double const z);


template <typename NumberType>
NumberType mathHelper::getSign(NumberType const value)
{
    return (value<0) ? -1 : 1;
}
template int mathHelper::getSign<int>(int const value);
template double mathHelper::getSign<double>(double const value);


template <typename NumberType>
NumberType mathHelper::clampLowerBound(NumberType const value, NumberType const limit)
{
    return (value<limit) ? limit : value;
}
template int mathHelper::clampLowerBound<int>(int const value, int const limit);
template double mathHelper::clampLowerBound<double>(double const value, double const limit);


template <typename NumberType>
NumberType mathHelper::clampHigherBound(NumberType const value, NumberType const limit)
{
    return (value>limit) ? limit : value;
}
template int mathHelper::clampHigherBound<int>(int const value, int const limit);
template double mathHelper::clampHigherBound<double>(double const value, double const limit);


unsigned int mathHelper::getDifferenceFromGreaterMultiple(unsigned int const multiple, unsigned int const number)
{
    unsigned result(0);
    if(multiple>0)
    {
        unsigned int numberOfMultiples(getNumberOfMultiplesInclusive(multiple, number));
        result = (numberOfMultiples*multiple) - number;
    }
    return result;
}

unsigned int mathHelper::getNumberOfMultiplesInclusive(unsigned int const multiple, unsigned int const number)
{
    unsigned int result(0);
    if(multiple>0)
    {
        result = ((number+multiple-1)/multiple);
    }
    return result;
}

double mathHelper::calculateCumulativeStandardDistributionApproximation(double const z)
{
    return 0.5 * erfc(-z * pow(0.5, 0.5));
}

double mathHelper::calculateInverseCumulativeStandardDistributionApproximation(double const probability, unsigned int const numberOfIterations)
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

double mathHelper::getPi()
{
    return 3.14159265358979323846;
}

double mathHelper::getE()
{
    return 2.7182818284590452354;
}

}//namespace alba
