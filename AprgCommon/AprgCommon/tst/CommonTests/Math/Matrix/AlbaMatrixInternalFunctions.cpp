#include "AlbaMatrixInternalFunctions.hpp"

#include <Common/Math/Helpers/PrecisionHelpers.hpp>

namespace alba
{

namespace matrix
{

template <>
bool isEqualForMathMatrixDataType(unsigned int const& value1, unsigned int const& value2)
{
    return mathHelper::isAlmostEqual<unsigned int>(value1, value2);
}

template <>
bool isEqualForMathMatrixDataType(int const& value1, int const& value2)
{
    return mathHelper::isAlmostEqual<int>(value1, value2);
}

template <>
bool isEqualForMathMatrixDataType(double const& value1, double const& value2)
{
    return mathHelper::isAlmostEqual<double>(value1, value2);
}

}
}