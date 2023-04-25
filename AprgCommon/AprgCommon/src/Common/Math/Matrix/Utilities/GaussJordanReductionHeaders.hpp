#pragma once

#include <Common/Math/Matrix/AlbaMatrixDataTypes.hpp>

namespace alba {

namespace matrix {

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
    AlbaMatrix<DataType>& matrix, DataType const& multiplierForInput, unsigned int const yInput,
    unsigned int const yOutput);

template <typename DataType>
void subtractRowsWithMultiplierPutDifferenceInAnotherRow(
    AlbaMatrix<DataType>& matrix, DataType const& multiplierForInput2, unsigned int const yInput1,
    unsigned int const yInput2, unsigned int const yOutput);

}  // namespace matrix

}  // namespace alba
