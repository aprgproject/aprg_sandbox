#include "PrecisionHelpers.hpp"

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
