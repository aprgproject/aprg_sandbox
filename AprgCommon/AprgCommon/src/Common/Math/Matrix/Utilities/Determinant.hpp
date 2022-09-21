#pragma once

#include "DeterminantHeaders.hpp" // needs to be first

#include <Common/Math/Helpers/DivisibilityHelpers.hpp>
#include <Common/Math/Matrix/AlbaMatrix.hpp>

namespace alba
{

namespace matrix
{

template <typename DataType>
unsigned int getIndexWithHighestNumberOfZeros(
        ListOfAlbaMatrixData<DataType> const& rowsOrColumns)
{
    BoolUnaryFunction<DataType> equalCondition = [](DataType const& entry)
    {
        return isEqualForMathMatrixDataType(entry, DataType{});
    };
    return getIndexWithHighestSatisfiedCount(rowsOrColumns, equalCondition);
}

template <typename DataType>
unsigned int getIndexWithHighestNumberOfNonZeros(
        ListOfAlbaMatrixData<DataType> const& rowsOrColumns)
{
    BoolUnaryFunction<DataType> nonEqualCondition = [](DataType const& entry)
    {
        return !isEqualForMathMatrixDataType(entry, DataType{});
    };
    return getIndexWithHighestSatisfiedCount(rowsOrColumns, nonEqualCondition);
}

template <typename DataType>
DataType getDeterminant(
        AlbaMatrix<DataType> const& matrix)
{
    unsigned int numberOfRows(matrix.getNumberOfRows());
    unsigned int numberOfColumns(matrix.getNumberOfColumns());
    assert(numberOfRows == numberOfColumns);
    DataType determinant{};
    if(numberOfColumns==1)
    {
        determinant = matrix.getEntry(0,0);
    }
    else if(numberOfColumns==2)
    {
        determinant = matrix.getEntry(0,0)*matrix.getEntry(1,1) - matrix.getEntry(0,1)*matrix.getEntry(1,0);
    }
    else
    {
        determinant = getDeterminantWhenSideIsMoreThan2(matrix);
    }
    return determinant;
}

template <typename DataType>
DataType getValueUsingCramerRule(
        AlbaMatrix<DataType> const& matrix,
        unsigned int const columnIndex,
        AlbaMatrixData<DataType> const& newColumnValues)
{
    unsigned int numberOfRows(matrix.getNumberOfRows());
    unsigned int numberOfColumns(matrix.getNumberOfColumns());
    assert(numberOfRows == numberOfColumns);
    AlbaMatrix<DataType> matrixWithNewColumn(matrix);
    matrixWithNewColumn.setColumn(columnIndex, newColumnValues);
    return getDeterminant(matrixWithNewColumn) / getDeterminant(matrix);
}

template <typename DataType>
DataType getValueFromCoFactorExpansion(
        AlbaMatrix<DataType> const& matrix,
        unsigned int x,
        unsigned int y)
{
    DataType value{};
    DataType entry = matrix.getEntry(x,y);
    if(!isEqualForMathMatrixDataType(entry, 0))
    {
        int sign = mathHelper::isEven(x+y) ? 1 : -1;
        DataType subDeterminant = getDeterminant(getMatrixWithOneColumnAndOneRowRemoved(matrix, x, y));
        value = entry * subDeterminant * sign;
    }
    return value;
}

template <typename DataType>
DataType getDeterminantWhenSideIsMoreThan2(
        AlbaMatrix<DataType> const& matrix)
{
    DataType determinant{};

    typename AlbaMatrix<DataType>::ListOfMatrixData rowsAndColumns;
    matrix.retrieveRows(rowsAndColumns);
    matrix.retrieveColumns(rowsAndColumns);

    unsigned int numberOfRows(matrix.getNumberOfRows());
    unsigned int numberOfColumns(matrix.getNumberOfColumns());
    unsigned int bestIndex = getIndexWithHighestNumberOfZeros(rowsAndColumns);
    if(bestIndex < numberOfRows)
    {
        unsigned int y = bestIndex;
        for(unsigned int x=0; x<numberOfColumns; x++)
        {
            determinant += getValueFromCoFactorExpansion(matrix, x, y);
        }
    }
    else
    {
        unsigned int x = bestIndex-numberOfRows;
        for(unsigned int y=0; y<numberOfRows; y++)
        {
            determinant += getValueFromCoFactorExpansion(matrix, x, y);
        }
    }
    return determinant;
}

template <typename DataType>
AlbaMatrix<DataType> getMatrixWithOneColumnAndOneRowRemoved(
        AlbaMatrix<DataType> const& matrix,
        unsigned int const columnIndex,
        unsigned int const rowIndex)
{
    unsigned int numberOfRows(matrix.getNumberOfRows());
    unsigned int numberOfColumns(matrix.getNumberOfColumns());
    assert((columnIndex < numberOfColumns) && (rowIndex < numberOfRows));
    AlbaMatrix<DataType> result(numberOfColumns-1, numberOfRows-1);
    matrix.iterateAllThroughYAndThenX([&](unsigned int const x, unsigned int const y)
    {
        if(columnIndex != x && rowIndex != y)
        {
            unsigned int newX = (x >= columnIndex) ? x-1 : x;
            unsigned int newY = (y >= rowIndex) ? y-1 : y;
            result.setEntry(newX, newY, matrix.getEntry(x , y));
        }
    });
    return result;
}

}

}//namespace alba
