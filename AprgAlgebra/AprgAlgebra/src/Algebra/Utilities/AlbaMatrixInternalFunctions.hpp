#pragma once

#include <Common/Math/Number/AlbaNumber.hpp>

namespace alba
{

namespace matrix
{

// Template declaration

template <typename DataType>
bool isEqualForMathMatrixDataType(DataType const& value1, DataType const& value2);


// Template specialization

template<>
bool isEqualForMathMatrixDataType(AlbaNumber const& value1, AlbaNumber const& value2);

}

}
