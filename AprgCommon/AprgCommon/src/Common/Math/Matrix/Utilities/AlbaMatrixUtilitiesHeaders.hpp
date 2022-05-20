#pragma once

#include <Common/Math/Matrix/AlbaMatrixDataTypes.hpp>

#include <functional>
#include <vector>

namespace alba
{

namespace matrix
{

template <typename DataType> using UnaryFunction = std::function<DataType(DataType const&)>;
template <typename DataType> using BinaryFunction = std::function<DataType(DataType const&, DataType const&)>;
template <typename DataType> class AlbaMatrix;

template <typename DataType> bool areRowsWithAllZerosInTheBottom(AlbaMatrix<DataType> const& matrix);
template <typename DataType> bool areLeadingEntriesInReducedRowEchelonForm(AlbaMatrix<DataType> const& matrix);
template <typename DataType> bool isSquare(AlbaMatrix<DataType> const& matrix);
template <typename DataType> bool isZeroMatrix(AlbaMatrix<DataType> const& matrix);
template <typename DataType> bool isIdentityMatrix(AlbaMatrix<DataType> const& matrix);
template <typename DataType> bool isSingular(AlbaMatrix<DataType> const& matrix);
template <typename DataType> bool isReducedRowEchelonForm(AlbaMatrix<DataType> const& matrix);
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
AlbaMatrix<DataType> getMatrixWithOneColumnAndOneRowRemoved(
        AlbaMatrix<DataType> const& matrix,
        unsigned int const columnIndex,
        unsigned int const rowIndex);

template <typename DataType>
void transformToReducedEchelonFormUsingGaussJordanReduction(
        AlbaMatrix<DataType> & matrix);

template <typename DataType>
void interchangeRows(
        AlbaMatrix<DataType> & matrix,
        unsigned int const y1,
        unsigned int const y2);

template <typename DataType>
void addTwoRowsAndPutSumInAnotherRow(
        AlbaMatrix<DataType> & matrix,
        unsigned int const yInput1,
        unsigned int const yInput2,
        unsigned int const yOutput);

template <typename DataType>
void multiplyValueInRowAndPutProductInAnotherRow(
        AlbaMatrix<DataType> & matrix,
        DataType const& multiplierForInput,
        unsigned int const yInput,
        unsigned int const yOutput);

template <typename DataType>
void subtractRowsWithMultiplierPutDifferenceInAnotherRow(
        AlbaMatrix<DataType> & matrix,
        DataType const& multiplierForInput2,
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
