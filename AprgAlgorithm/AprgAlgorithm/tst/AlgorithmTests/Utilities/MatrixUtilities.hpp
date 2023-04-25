#pragma once

namespace alba {

namespace matrix {

// Template declaration

template <typename DataType>
bool isEqualForMathMatrixDataType(DataType const& value1, DataType const& value2);

// Template specialization

template <>
bool isEqualForMathMatrixDataType(unsigned int const& value1, unsigned int const& value2);

template <>
bool isEqualForMathMatrixDataType(int const& value1, int const& value2);

template <>
bool isEqualForMathMatrixDataType(double const& value1, double const& value2);

}  // namespace matrix

}  // namespace alba
