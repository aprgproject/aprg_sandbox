#pragma once

#include <Common/Math/Matrix/AlbaMatrixDataTypes.hpp>

namespace alba {

namespace matrix {

template <typename DataType>
AlbaMatrix<DataType> constructSimplexTableWithLessThanConstraints(
    AlbaMatrix<DataType> const& constraintsCoefficients, AlbaMatrixData<DataType> const& constraintsValues,
    AlbaMatrixData<DataType> const& objectiveFunctionCoefficients);

template <typename DataType>
void solveSimplexTable(AlbaMatrix<DataType>& simplexTable);

template <typename DataType>
bool isOptimal(AlbaMatrix<DataType> const& simplexTable);

template <typename DataType>
size_t getPivotingColumnUsingBlandsRule(AlbaMatrix<DataType> const& simplexTable);

template <typename DataType>
size_t getPivotingRowUsingMinRatioRule(AlbaMatrix<DataType> const& simplexTable, size_t const pivotingColumn);

template <typename DataType>
void pivotAt(AlbaMatrix<DataType>& simplexTable, size_t const pivotingColumn, size_t const pivotingRow);

}  // namespace matrix

}  // namespace alba
