#pragma once

namespace alba
{

// Template declaration

template <typename DataType>
bool isEqualForMathVectorDataType(DataType const& value1, DataType const& value2);

template <typename DataType>
DataType raiseToPowerForMathVectorDataType(DataType const& value1, DataType const& value2);


// Template specialization

template <>
bool isEqualForMathVectorDataType(double const& value1, double const& value2);

template <>
double raiseToPowerForMathVectorDataType(double const& value1, double const& value2);

}