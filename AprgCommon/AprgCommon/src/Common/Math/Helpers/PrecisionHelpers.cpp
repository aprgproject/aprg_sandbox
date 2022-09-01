#include "PrecisionHelpers.hpp"

#include <limits>

using namespace std;

namespace alba
{

namespace mathHelper
{

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

}//namespace mathHelper

}//namespace alba
