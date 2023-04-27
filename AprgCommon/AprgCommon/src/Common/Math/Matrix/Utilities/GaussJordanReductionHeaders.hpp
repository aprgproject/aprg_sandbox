#pragma once

#include <Common/Math/Matrix/AlbaMatrixDataTypes.hpp>

namespace alba::matrix {

template <typename DataType>
bool areRowsWithAllZerosInTheBottom(AlbaMatrix<DataType> const& matrix);
template <typename DataType>
bool areLeadingEntriesInReducedRowEchelonForm(AlbaMatrix<DataType> const& matrix);
template <typename DataType>
bool isReducedRowEchelonForm(AlbaMatrix<DataType> const& matrix);

template <typename DataType>
void transformToReducedEchelonFormUsingGaussJordanReduction(AlbaMatrix<DataType>& matrix);

template <typename DataType>
void multiplyValueInRowAndPutProductInAnotherRow(
    AlbaMatrix<DataType>& matrix, DataType const& multiplierForInput, size_t const yInput, size_t const yOutput);

template <typename DataType>
void subtractRowsWithMultiplierPutDifferenceInAnotherRow(
    AlbaMatrix<DataType>& matrix, DataType const& multiplierForInput2, size_t const yInput1, size_t const yInput2,
    size_t const yOutput);

}  // namespace alba::matrix
