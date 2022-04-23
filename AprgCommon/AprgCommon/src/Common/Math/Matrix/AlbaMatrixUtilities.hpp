#pragma once

#include <Common/Math/Matrix/AlbaMatrixUtilitiesHeaders.hpp>
#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <algorithm>
#include <cassert>

namespace alba
{

namespace matrix
{

template <typename DataType>
bool isEqualForMathMatrixDataType(DataType const& value1, DataType const& value2);

template <typename DataType>
bool areRowsWithAllZerosInTheBottom(
        AlbaMatrix<DataType> const& matrix)
{    unsigned int numberOfRows(matrix.getNumberOfRows());
    unsigned int numberOfColumns(matrix.getNumberOfColumns());
    bool isRowWithNonZeroEncountered(false);
    for(unsigned int yPlusOne=numberOfRows; yPlusOne>0; yPlusOne--)    {
        unsigned int y(yPlusOne-1);
        bool isRowWithAllZero(true);
        for(unsigned int x=0; x<numberOfColumns; x++)
        {
            if(isRowWithAllZero && !isEqualForMathMatrixDataType(matrix.getEntry(x, y), DataType(0)))
            {
                isRowWithAllZero = false;
                break;            }
        }
        if(!isRowWithNonZeroEncountered)
        {            isRowWithNonZeroEncountered = !isRowWithAllZero;
        }
        if(isRowWithNonZeroEncountered && isRowWithAllZero)
        {
            //1. All rows consisting entirely of zeros, if any, are at the bottom of the matrix.
            return false;
        }
    }
    return true;
}

template <typename DataType>
bool areLeadingEntriesInReducedRowEchelonForm(
        AlbaMatrix<DataType> const& matrix)
{
    unsigned int numberOfRows(matrix.getNumberOfRows());
    unsigned int numberOfColumns(matrix.getNumberOfColumns());
    int currentLeadingEntryColumn(-1);
    for(unsigned int y=0; y<numberOfRows; y++)
    {
        for(unsigned int x=0; x<numberOfColumns; x++)
        {
            if(isEqualForMathMatrixDataType(matrix.getEntry(x, y), DataType(0))) {}
            else if(isEqualForMathMatrixDataType(matrix.getEntry(x, y), DataType(1)))
            {
                if(currentLeadingEntryColumn < static_cast<int>(x))
                {
                    for(unsigned int yZeroCheck=0; yZeroCheck<numberOfRows; yZeroCheck++)
                    {
                        if(yZeroCheck!=y && !isEqualForMathMatrixDataType(matrix.getEntry(x, yZeroCheck), DataType(0)))
                        {
                            //4. If a column contains a leading entry of some row, then all other entries in that column are zero
                            return false;                        }
                    }
                }
                else                {
                    //3. If rows i and i+1 are two successive rows that do not consist entirely of zeros, then the leading entry of row i+1 is to the right of the leading entry of row i.
                    return false;
                }
                currentLeadingEntryColumn = static_cast<int>(x);
                break;
            }
            else
            {
                //2. By reading from left to right, the first nonzero entry in each row that does not consist entirely of zeros is a 1, called the leading entry of its row.
                return false;
            }
        }
    }
    return true;
}

template <typename DataType>
bool isSquare(AlbaMatrix<DataType> const& matrix)
{
    return matrix.getNumberOfRows() == matrix.getNumberOfColumns();
}

template <typename DataType>
bool isZeroMatrix(AlbaMatrix<DataType> const& matrix)
{
    auto const& matrixData(matrix.getMatrixData());
    return std::all_of(matrixData.cbegin(), matrixData.cend(), [](DataType const& data)
    {
        return isEqualForMathMatrixDataType(data, DataType(0));
    });
}
template <typename DataType>
bool isIdentityMatrix(AlbaMatrix<DataType> const& matrix)
{    unsigned int numberOfRows(matrix.getNumberOfRows());
    unsigned int numberOfColumns(matrix.getNumberOfColumns());
    bool isIdentityMatrix(numberOfRows == numberOfColumns);
    for(unsigned int y=0; isIdentityMatrix && y<numberOfRows; y++)
    {
        for(unsigned int x=0; isIdentityMatrix && x<numberOfColumns; x++)
        {
            if(x==y)
            {
                isIdentityMatrix = isIdentityMatrix && matrix.getEntry(x, y) == 1;
            }
            else
            {
                isIdentityMatrix = isIdentityMatrix && matrix.getEntry(x, y) == 0;
            }
        }
    }
    return isIdentityMatrix;
}

template <typename DataType>
bool isSingular(AlbaMatrix<DataType> const& matrix) // means the its non invertible
{
    AlbaMatrix<DataType> inverseOfInverse(matrix);
    inverseOfInverse.invert();
    inverseOfInverse.invert();
    return !(matrix == inverseOfInverse);
}

template <typename DataType>
bool isReducedRowEchelonForm(
        AlbaMatrix<DataType> const& matrix)
{
    return areRowsWithAllZerosInTheBottom(matrix) && areLeadingEntriesInReducedRowEchelonForm(matrix);
}

template <typename DataType>
unsigned int getBestIndexForCoFactorExpansion(
        ListOfAlbaMatrixData<DataType> const& rowsAndColumns)
{
    unsigned int i=0;
    unsigned int bestIndex=0;
    unsigned int highestNumberOfZeros=0;
    for(auto const& rowOrColumn : rowsAndColumns)
    {
        unsigned int numberOfZeros = std::count_if(rowOrColumn.cbegin(), rowOrColumn.cend(),[](DataType const& value)
        {return isEqualForMathMatrixDataType(value, DataType(0));});
        if(highestNumberOfZeros < numberOfZeros)
        {
            highestNumberOfZeros = numberOfZeros;            bestIndex = i;
        }
        i++;
    }
    return bestIndex;
}

template <typename DataType>
DataType getDeterminant(
        AlbaMatrix<DataType> const& matrix)
{
    unsigned int numberOfRows(matrix.getNumberOfRows());
    unsigned int numberOfColumns(matrix.getNumberOfColumns());
    assert(numberOfRows == numberOfColumns);
    DataType determinant(0);
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
    DataType value(0);
    DataType entry = matrix.getEntry(x,y);
    if(!isEqualForMathMatrixDataType(entry, 0))
    {
        int sign = mathHelper::isEven(x+y) ? 1 : -1;
        DataType subDeterminant = getDeterminant(getMatrixWithOneColumnAndOneRowRemoved(matrix, x, y));        value = entry * subDeterminant * sign;
    }
    return value;
}
template <typename DataType>
DataType getDeterminantWhenSideIsMoreThan2(
        AlbaMatrix<DataType> const& matrix)
{
    DataType determinant(0);

    typename AlbaMatrix<DataType>::ListOfMatrixData rowsAndColumns;
    matrix.retrieveRows(rowsAndColumns);
    matrix.retrieveColumns(rowsAndColumns);

    unsigned int numberOfRows(matrix.getNumberOfRows());
    unsigned int numberOfColumns(matrix.getNumberOfColumns());
    unsigned int bestIndex(getBestIndexForCoFactorExpansion(rowsAndColumns));
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
AlbaMatrix<DataType> doUnaryOperation(
        AlbaMatrix<DataType> const& inputMatrix,
        UnaryFunction<DataType> const& unaryFunction)
{
    AlbaMatrix<DataType> resultMatrix(inputMatrix.getNumberOfColumns(), inputMatrix.getNumberOfRows());
    inputMatrix.iterateAllThroughYAndThenX([&](unsigned int const x, unsigned int const y)
    {
        resultMatrix.setEntry(x, y, unaryFunction(inputMatrix.getEntry(x, y)));
    });
    return resultMatrix;
}

template <typename DataType>
AlbaMatrix<DataType> doBinaryOperationWithSameDimensions(
        AlbaMatrix<DataType> const& firstMatrix,
        AlbaMatrix<DataType> const& secondMatrix,
        BinaryFunction<DataType> const& binaryFunction)
{
    assert((firstMatrix.getNumberOfColumns() == secondMatrix.getNumberOfColumns()) &&
           (firstMatrix.getNumberOfRows() == secondMatrix.getNumberOfRows()));
    AlbaMatrix<DataType> resultMatrix(firstMatrix.getNumberOfColumns(), firstMatrix.getNumberOfRows());
    firstMatrix.iterateAllThroughYAndThenX([&](unsigned int const x, unsigned int const y)
    {
        resultMatrix.setEntry(x, y, binaryFunction(firstMatrix.getEntry(x, y), secondMatrix.getEntry(x, y)));
    });
    return resultMatrix;
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

template <typename DataType>
void transformToReducedEchelonFormUsingGaussJordanReduction(
        AlbaMatrix<DataType> & matrix)
{
    unsigned int numberOfRows(matrix.getNumberOfRows());
    unsigned int numberOfColumns(matrix.getNumberOfColumns());
    unsigned int yWithLeadingEntry = 0;
    for(unsigned int x=0; x<numberOfColumns; x++)
    {
        for(unsigned int y=yWithLeadingEntry; y<numberOfRows; y++)
        {
            if(!isEqualForMathMatrixDataType(matrix.getEntry(x, y), DataType(0)))
            {
                interchangeRows(matrix, y, yWithLeadingEntry);
                multiplyValueInRowAndPutProductInAnotherRow(                            matrix,
                            static_cast<DataType>(1)/matrix.getEntry(x, yWithLeadingEntry),
                            yWithLeadingEntry,
                            yWithLeadingEntry);
                for(unsigned int yToZero=0; yToZero<numberOfRows; yToZero++)
                {
                    if(yToZero != yWithLeadingEntry
                            && !isEqualForMathMatrixDataType(matrix.getEntry(x, yToZero), DataType(0)))
                    {
                        subtractRowsWithMultiplierPutDifferenceInAnotherRow(
                                    matrix,                                    matrix.getEntry(x, yToZero) / matrix.getEntry(x, yWithLeadingEntry),
                                    yToZero,
                                    yWithLeadingEntry,
                                    yToZero);                    }
                }
                yWithLeadingEntry++;
                break;
            }
        }
    }
}

template <typename DataType>
void interchangeRows(
        AlbaMatrix<DataType> & matrix,
        unsigned int const y1,
        unsigned int const y2)
{
    unsigned int numberOfRows(matrix.getNumberOfRows());
    unsigned int numberOfColumns(matrix.getNumberOfColumns());
    assert((y1 < numberOfRows) && (y2 < numberOfRows));
    for(unsigned int x=0; x<numberOfColumns; x++)
    {
        std::swap(matrix.getEntryReference(x, y1), matrix.getEntryReference(x, y2));
    }
}

template <typename DataType>
void addTwoRowsAndPutSumInAnotherRow(
        AlbaMatrix<DataType> & matrix,
        unsigned int const yInput1,
        unsigned int const yInput2,
        unsigned int const yOutput)
{
    unsigned int numberOfRows(matrix.getNumberOfRows());
    assert((yInput1 < numberOfRows) && (yInput2 < numberOfRows) && (yOutput < numberOfRows));
    traverseWithBinaryOperationForDifferentRows(
                matrix, yInput1, yInput2, yOutput, BinaryFunction<DataType>(std::plus<DataType>()));
}

template <typename DataType>
void multiplyValueInRowAndPutProductInAnotherRow(
        AlbaMatrix<DataType> & matrix,
        DataType const& multiplierForInput,
        unsigned int const yInput,
        unsigned int const yOutput)
{
    unsigned int numberOfRows(matrix.getNumberOfRows());
    assert((yInput < numberOfRows) && (yOutput < numberOfRows));
    traverseWithUnaryOperationForDifferentRows(
                matrix, yInput, yOutput, UnaryFunction<DataType>([&](DataType const& input)
    {
        return input*multiplierForInput;
    }));
}

template <typename DataType>
void subtractRowsWithMultiplierPutDifferenceInAnotherRow(
        AlbaMatrix<DataType> & matrix,
        DataType const& multiplierForInput2,
        unsigned int const yInput1,
        unsigned int const yInput2,
        unsigned int const yOutput)
{
    unsigned int numberOfRows(matrix.getNumberOfRows());
    assert((yInput1 < numberOfRows) && (yInput2 < numberOfRows) && (yOutput < numberOfRows));
    traverseWithBinaryOperationForDifferentRows(
                matrix, yInput1, yInput2, yOutput, BinaryFunction<DataType>([&](DataType const& input1, DataType const& input2)
    {
        return input1 - (input2*multiplierForInput2);
    }));
}

template <typename DataType>
void traverseWithUnaryOperationForDifferentRows(
        AlbaMatrix<DataType> & matrix,
        unsigned int const yInput,
        unsigned int const yOutput,
        UnaryFunction<DataType> const& unaryFunction)
{
    unsigned int numberOfRows(matrix.getNumberOfRows());
    unsigned int numberOfColumns(matrix.getNumberOfColumns());
    assert((yInput < numberOfRows) && (yOutput < numberOfRows));
    for(unsigned int x=0; x<numberOfColumns; x++)
    {
        matrix.setEntry(x, yOutput, unaryFunction(matrix.getEntry(x, yInput)));
    }
}

template <typename DataType>
void traverseWithBinaryOperationForDifferentRows(
        AlbaMatrix<DataType> & matrix,
        unsigned int const yInput1,
        unsigned int const yInput2,
        unsigned int const yOutput,
        BinaryFunction<DataType> const& binaryFunction)
{
    unsigned int numberOfRows(matrix.getNumberOfRows());
    unsigned int numberOfColumns(matrix.getNumberOfColumns());
    assert((yInput1 < numberOfRows) && (yInput2 < numberOfRows) && (yOutput < numberOfRows));
    for(unsigned int x=0; x<numberOfColumns; x++)
    {
        matrix.setEntry(x, yOutput, binaryFunction(matrix.getEntry(x, yInput1), matrix.getEntry(x, yInput2)));
    }
}

}

}//namespace alba
