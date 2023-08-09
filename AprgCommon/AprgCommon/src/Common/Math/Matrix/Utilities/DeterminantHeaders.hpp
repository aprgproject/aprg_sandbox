#pragma once

#include <Common/Math/Matrix/AlbaMatrixDataTypes.hpp>

namespace alba
{

namespace matrix
{
template <typename DataType> unsigned int getBestIndexForCoFactorExpansion(ListOfAlbaMatrixData<DataType> const& rowsAndColumns);

template <typename DataType> DataType getDeterminant(AlbaMatrix<DataType> const& matrix);

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

}

}//namespace alba
