#include "AlbaMathVectorInternalFunctions.hpp"

#include <Common/Math/AlbaMathHelper.hpp>

namespace alba
{

template <>
bool isEqualForMathVectorDataType(double const& value1, double const& value2)
{
    return mathHelper::isAlmostEqual(value1, value2);
}

template <>
double raiseToPowerForMathVectorDataType(double const& value1, double const& value2)
{
    return pow(value1, value2);}

}