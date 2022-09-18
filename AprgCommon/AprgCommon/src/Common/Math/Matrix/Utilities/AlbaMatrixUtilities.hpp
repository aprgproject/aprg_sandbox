#pragma once

#include "AlbaMatrixUtilitiesHeaders.hpp" // needs to be first

#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <algorithm>
#include <cassert>

namespace alba
{

namespace matrix
{

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
{
    unsigned int numberOfRows(matrix.getNumberOfRows());
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
    // Another method:
    // Matrix is invertible iff determinant is zero
    // But this is costly because of determinant.
    // Code:
    // return getDeterminant(matrix) != 0;

    AlbaMatrix<DataType> inverseOfInverse(matrix);
    inverseOfInverse.invert();
    inverseOfInverse.invert();
    return !(matrix == inverseOfInverse);
}

template <typename DataType>
AlbaMatrix<DataType> getIdentityMatrix(unsigned int const sideSize)
{
    AlbaMatrix<DataType> resultMatrix(sideSize, sideSize);
    for(unsigned int i=0; i<sideSize; i++)
    {
        resultMatrix.setEntry(i, i, 1);
    }
    return resultMatrix;
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
void doUnaryAssignmentOperation(
        AlbaMatrix<DataType> & inputOutputMatrix,
        UnaryFunction<DataType> const& unaryFunction)
{
    inputOutputMatrix.iterateAllThroughYAndThenX([&](unsigned int const x, unsigned int const y)
    {
        inputOutputMatrix.setEntry(x, y, unaryFunction(inputOutputMatrix.getEntry(x, y)));
    });
}

template <typename DataType>
void doBinaryAssignmentOperationWithSameDimensions(
        AlbaMatrix<DataType> & firstMatrix,
        AlbaMatrix<DataType> const& secondMatrix,
        BinaryFunction<DataType> const& binaryFunction)
{
    assert((firstMatrix.getNumberOfColumns() == secondMatrix.getNumberOfColumns()) &&
           (firstMatrix.getNumberOfRows() == secondMatrix.getNumberOfRows()));
    firstMatrix.iterateAllThroughYAndThenX([&](unsigned int const x, unsigned int const y)
    {
        firstMatrix.setEntry(x, y, binaryFunction(firstMatrix.getEntry(x, y), secondMatrix.getEntry(x, y)));
    });
}

template <typename DataType>
AlbaMatrix<DataType> multiplyMatrices(
        AlbaMatrix<DataType> const& first,
        AlbaMatrix<DataType> const& second)
{
    // Using a straightforward algorithm, we can calculate the product of two nxn matrices in O(n^3) time.
    // There are also more efficient algorithms for matrix multiplication,
    // but they are mostly of theoretical interest and such algorithms are not practical.

    assert(first.getNumberOfColumns() == second.getNumberOfRows());

    AlbaMatrix<DataType> result(first.getNumberOfRows(), second.getNumberOfColumns());
    ListOfAlbaMatrixData<DataType> rowsOfFirstMatrix, columnsOfSecondMatrix;
    first.retrieveRows(rowsOfFirstMatrix);
    second.retrieveColumns(columnsOfSecondMatrix);
    unsigned int y=0;
    for(AlbaMatrixData<DataType> const& rowOfFirstMatrix : rowsOfFirstMatrix)
    {
        unsigned int x=0;
        for(AlbaMatrixData<DataType> const& columnOfSecondMatrix : columnsOfSecondMatrix)
        {
            result.setEntry(x, y, multiplyEachItemAndGetSum(rowOfFirstMatrix, columnOfSecondMatrix));
            x++;
        }
        y++;
    }
    return result;
}

template <typename DataType>
AlbaMatrix<DataType> getMatrixRaiseToScalarPower(
        AlbaMatrix<DataType> const& base,
        unsigned int const scalarExponent)
{
    assert(base.getNumberOfColumns() == base.getNumberOfRows());

    AlbaMatrix<DataType> result(getIdentityMatrix<DataType>(base.getNumberOfColumns()));
    AlbaMatrix<DataType> newBase(base);
    unsigned int newExponent(scalarExponent);
    while(newExponent > 0)
    {
        if(mathHelper::isEven(newExponent))
        {
            newBase *= newBase;
            newExponent /= 2;
        }
        else
        {
            result *= newBase;
            newExponent--;
        }
    }
    return result;
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
DataType multiplyEachItemAndGetSum(
        AlbaMatrixData<DataType> const& first,
        AlbaMatrixData<DataType> const& second)
{
    DataType result{};
    unsigned int minSize = std::min(first.size(), second.size());
    for(unsigned int i=0; i<minSize; i++)
    {
        result+=first.at(i)*second.at(i);
    }
    return result;
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
