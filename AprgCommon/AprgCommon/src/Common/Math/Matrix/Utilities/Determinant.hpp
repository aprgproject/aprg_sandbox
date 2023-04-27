#pragma once

#include "DeterminantHeaders.hpp"  // needs to be first
#include <Common/Math/Helpers/DivisibilityHelpers.hpp>
#include <Common/Math/Matrix/AlbaMatrix.hpp>

namespace alba {

namespace matrix {

template <typename DataType>
size_t getIndexWithHighestNumberOfZeros(ListOfAlbaMatrixData<DataType> const& rowsOrColumns) {
    BoolUnaryFunction<DataType> equalCondition = [](DataType const& entry) {
        return isEqualForMathMatrixDataType(entry, DataType{});
    };
    return getIndexWithHighestSatisfiedCount(rowsOrColumns, equalCondition);
}

template <typename DataType>
size_t getIndexWithHighestNumberOfNonZeros(ListOfAlbaMatrixData<DataType> const& rowsOrColumns) {
    BoolUnaryFunction<DataType> nonEqualCondition = [](DataType const& entry) {
        return !isEqualForMathMatrixDataType(entry, DataType{});
    };
    return getIndexWithHighestSatisfiedCount(rowsOrColumns, nonEqualCondition);
}

template <typename DataType>
DataType getDeterminant(AlbaMatrix<DataType> const& matrix) {
    size_t numberOfRows(matrix.getNumberOfRows());
    size_t numberOfColumns(matrix.getNumberOfColumns());
    assert(numberOfRows == numberOfColumns);
    DataType determinant{};
    if (numberOfColumns == 1) {
        determinant = matrix.getEntry(0, 0);
    } else if (numberOfColumns == 2) {
        determinant = matrix.getEntry(0, 0) * matrix.getEntry(1, 1) - matrix.getEntry(0, 1) * matrix.getEntry(1, 0);
    } else {
        determinant = getDeterminantWhenSideIsMoreThan2(matrix);
    }
    return determinant;
}

template <typename DataType>
DataType getValueUsingCramerRule(
    AlbaMatrix<DataType> const& matrix, size_t const columnIndex, AlbaMatrixData<DataType> const& newColumnValues) {
    size_t numberOfRows(matrix.getNumberOfRows());
    size_t numberOfColumns(matrix.getNumberOfColumns());
    assert(numberOfRows == numberOfColumns);
    AlbaMatrix<DataType> matrixWithNewColumn(matrix);
    matrixWithNewColumn.setColumn(columnIndex, newColumnValues);
    return getDeterminant(matrixWithNewColumn) / getDeterminant(matrix);
}

template <typename DataType>
DataType getValueFromCoFactorExpansion(AlbaMatrix<DataType> const& matrix, size_t x, size_t y) {
    DataType value{};
    DataType entry = matrix.getEntry(x, y);
    if (!isEqualForMathMatrixDataType(entry, 0)) {
        int sign = mathHelper::isEven(x + y) ? 1 : -1;
        DataType subDeterminant = getDeterminant(getMatrixWithOneColumnAndOneRowRemoved(matrix, x, y));
        value = entry * subDeterminant * sign;
    }
    return value;
}

template <typename DataType>
DataType getDeterminantWhenSideIsMoreThan2(AlbaMatrix<DataType> const& matrix) {
    DataType determinant{};

    typename AlbaMatrix<DataType>::ListOfMatrixData rowsAndColumns;
    matrix.retrieveRows(rowsAndColumns);
    matrix.retrieveColumns(rowsAndColumns);

    size_t numberOfRows(matrix.getNumberOfRows());
    size_t numberOfColumns(matrix.getNumberOfColumns());
    size_t bestIndex = getIndexWithHighestNumberOfZeros(rowsAndColumns);
    if (bestIndex < numberOfRows) {
        size_t y = bestIndex;
        for (size_t x = 0; x < numberOfColumns; x++) {
            determinant += getValueFromCoFactorExpansion(matrix, x, y);
        }
    } else {
        size_t x = bestIndex - numberOfRows;
        for (size_t y = 0; y < numberOfRows; y++) {
            determinant += getValueFromCoFactorExpansion(matrix, x, y);
        }
    }
    return determinant;
}

template <typename DataType>
AlbaMatrix<DataType> getMatrixWithOneColumnAndOneRowRemoved(
    AlbaMatrix<DataType> const& matrix, size_t const columnIndex, size_t const rowIndex) {
    size_t numberOfRows(matrix.getNumberOfRows());
    size_t numberOfColumns(matrix.getNumberOfColumns());
    assert((columnIndex < numberOfColumns) && (rowIndex < numberOfRows));
    AlbaMatrix<DataType> result(numberOfColumns - 1, numberOfRows - 1);
    matrix.iterateAllThroughYAndThenX([&](size_t const x, size_t const y) {
        if (columnIndex != x && rowIndex != y) {
            size_t newX = (x >= columnIndex) ? x - 1 : x;
            size_t newY = (y >= rowIndex) ? y - 1 : y;
            result.setEntry(newX, newY, matrix.getEntry(x, y));
        }
    });
    return result;
}

}  // namespace matrix

}  // namespace alba
