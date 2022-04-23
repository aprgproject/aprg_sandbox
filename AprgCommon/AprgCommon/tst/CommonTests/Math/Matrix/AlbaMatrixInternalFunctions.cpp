#include "AlbaMatrixInternalFunctions.hpp"

#include <Common/Math/AlbaMathHelper.hpp>

namespace alba
{

namespace matrix
{

template<>
bool isEqualForMathMatrixDataType(unsigned int const& value1, unsigned int const& value2)
{
    return mathHelper::isAlmostEqual(value1, value2);
}

template<>
bool isEqualForMathMatrixDataType(int const& value1, int const& value2)
{
    return mathHelper::isAlmostEqual(value1, value2);
}

template<>
bool isEqualForMathMatrixDataType(double const& value1, double const& value2)
{
    return mathHelper::isAlmostEqual(value1, value2);
}

}

}
