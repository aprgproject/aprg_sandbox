#pragma once

#include <Common/Math/Matrix/AlbaMatrixDataTypes.hpp>

namespace alba
{

namespace matrix
{

template <typename DataType> unsigned int getIndexWithHighestNumberOfZeros(
        ListOfAlbaMatrixData<DataType> const& rowsAndColumns);

template <typename DataType> unsigned int getIndexWithHighestNumberOfNonZeros(
        ListOfAlbaMatrixData<DataType> const& rowsAndColumns);

template <typename DataType> DataType getDeterminant(
        AlbaMatrix<DataType> const& matrix);

template <typename DataType>
DataType getValueUsingCramerRule(
        AlbaMatrix<DataType> const& matrix,
        unsigned int const columnIndex,
        AlbaMatrixData<DataType> const& newColumnValues);

template <typename DataType>
DataType getValueFromCoFactorExpansion(
        AlbaMatrix<DataType> const& matrix,
        unsigned int x,
        unsigned int y);

template <typename DataType>
DataType getDeterminantWhenSideIsMoreThan2(
        AlbaMatrix<DataType> const& matrix);

template <typename DataType>
AlbaMatrix<DataType> getMatrixWithOneColumnAndOneRowRemoved(
        AlbaMatrix<DataType> const& matrix,
        unsigned int const columnIndex,
        unsigned int const rowIndex);

}

}//namespace alba
