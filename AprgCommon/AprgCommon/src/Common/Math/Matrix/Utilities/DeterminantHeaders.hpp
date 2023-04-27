#pragma once

#include <Common/Math/Matrix/AlbaMatrixDataTypes.hpp>

namespace alba::matrix {

template <typename DataType>
size_t getIndexWithHighestNumberOfZeros(ListOfAlbaMatrixData<DataType> const& rowsAndColumns);

template <typename DataType>
size_t getIndexWithHighestNumberOfNonZeros(ListOfAlbaMatrixData<DataType> const& rowsAndColumns);

template <typename DataType>
DataType getDeterminant(AlbaMatrix<DataType> const& matrix);

template <typename DataType>
DataType getValueUsingCramerRule(
    AlbaMatrix<DataType> const& matrix, size_t const columnIndex, AlbaMatrixData<DataType> const& newColumnValues);

template <typename DataType>
DataType getValueFromCoFactorExpansion(AlbaMatrix<DataType> const& matrix, size_t x, size_t y);

template <typename DataType>
DataType getDeterminantWhenSideIsMoreThan2(AlbaMatrix<DataType> const& matrix);

template <typename DataType>
AlbaMatrix<DataType> getMatrixWithOneColumnAndOneRowRemoved(
    AlbaMatrix<DataType> const& matrix, size_t const columnIndex, size_t const rowIndex);

}  // namespace alba::matrix
