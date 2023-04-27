#pragma once

#include <Common/Math/Matrix/AlbaMatrixDataTypes.hpp>

#include <functional>
#include <vector>

namespace alba {

namespace matrix {

// there shoulde be an implementation when used
template <typename DataType>
bool isEqualForMathMatrixDataType(DataType const& value1, DataType const& value2);

template <typename DataType>
bool isSquare(AlbaMatrix<DataType> const& matrix);
template <typename DataType>
bool isZeroMatrix(AlbaMatrix<DataType> const& matrix);
template <typename DataType>
bool isIdentityMatrix(AlbaMatrix<DataType> const& matrix);
template <typename DataType>
bool isSingular(AlbaMatrix<DataType> const& matrix);

template <typename DataType>
AlbaMatrix<DataType> getIdentityMatrix(size_t const sideSize);

template <typename DataType>
AlbaMatrix<DataType> doUnaryOperation(
    AlbaMatrix<DataType> const& inputMatrix, UnaryFunction<DataType> const& unaryFunction);

template <typename DataType>
AlbaMatrix<DataType> doBinaryOperationWithSameDimensions(
    AlbaMatrix<DataType> const& firstMatrix, AlbaMatrix<DataType> const& secondMatrix,
    BinaryFunction<DataType> const& binaryFunction);

template <typename DataType>
void doUnaryAssignmentOperation(AlbaMatrix<DataType>& inputOutputMatrix, UnaryFunction<DataType> const& unaryFunction);

template <typename DataType>
void doBinaryAssignmentOperationWithSameDimensions(
    AlbaMatrix<DataType>& firstMatrix, AlbaMatrix<DataType> const& secondMatrix,
    BinaryFunction<DataType> const& binaryFunction);

template <typename DataType>
AlbaMatrix<DataType> multiplyMatrices(AlbaMatrix<DataType> const& first, AlbaMatrix<DataType> const& second);

template <typename DataType>
AlbaMatrix<DataType> getMatrixRaiseToScalarPower(AlbaMatrix<DataType> const& base, size_t const scalarExponent);

template <typename DataType>
void interchangeRows(AlbaMatrix<DataType>& matrix, size_t const y1, size_t const y2);

template <typename DataType>
void addTwoRowsAndPutSumInAnotherRow(
    AlbaMatrix<DataType>& matrix, size_t const yInput1, size_t const yInput2, size_t const yOutput);

template <typename DataType>
DataType multiplyEachItemAndGetSum(AlbaMatrixData<DataType> const& first, AlbaMatrixData<DataType> const& second);

template <typename DataType>
void traverseWithUnaryOperationForDifferentRows(
    AlbaMatrix<DataType>& matrix, size_t const yInput, size_t const yOutput,
    UnaryFunction<DataType> const& unaryFunction);

template <typename DataType>
void traverseWithBinaryOperationForDifferentRows(
    AlbaMatrix<DataType>& matrix, size_t const yInput1, size_t const yInput2, size_t const yOutput,
    BinaryFunction<DataType> const& binaryFunction);

}  // namespace matrix

}  // namespace alba
