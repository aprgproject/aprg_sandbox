#pragma once

#include <Common/Math/Matrix/AlbaMatrixDataTypes.hpp>

#include <functional>
#include <vector>

namespace alba
{

namespace matrix
{

template <typename DataType> bool isSquare(AlbaMatrix<DataType> const& matrix);
template <typename DataType> bool isZeroMatrix(AlbaMatrix<DataType> const& matrix);
template <typename DataType> bool isIdentityMatrix(AlbaMatrix<DataType> const& matrix);
template <typename DataType> bool isSingular(AlbaMatrix<DataType> const& matrix);

template <typename DataType>
AlbaMatrix<DataType> doUnaryOperation(
        AlbaMatrix<DataType> const& inputMatrix,
        UnaryFunction<DataType> const& unaryFunction);

template <typename DataType>
AlbaMatrix<DataType> doBinaryOperationWithSameDimensions(
        AlbaMatrix<DataType> const& firstMatrix,
        AlbaMatrix<DataType> const& secondMatrix,
        BinaryFunction<DataType> const& binaryFunction);

template <typename DataType>
void interchangeRows(
        AlbaMatrix<DataType> & matrix,
        unsigned int const y1,        unsigned int const y2);

template <typename DataType>
void addTwoRowsAndPutSumInAnotherRow(        AlbaMatrix<DataType> & matrix,
        unsigned int const yInput1,
        unsigned int const yInput2,
        unsigned int const yOutput);

template <typename DataType>
void traverseWithUnaryOperationForDifferentRows(
        AlbaMatrix<DataType> & matrix,
        unsigned int const yInput,
        unsigned int const yOutput,
        UnaryFunction<DataType> const& unaryFunction);

template <typename DataType>
void traverseWithBinaryOperationForDifferentRows(
        AlbaMatrix<DataType> & matrix,
        unsigned int const yInput1,
        unsigned int const yInput2,
        unsigned int const yOutput,
        BinaryFunction<DataType> const& binaryFunction);

}

}//namespace alba
