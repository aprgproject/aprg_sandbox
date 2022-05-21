#pragma once

#include <Common/Math/Matrix/AlbaMatrixDataTypes.hpp>

namespace alba
{

namespace matrix
{

template <typename DataType>
AlbaMatrix<DataType> constructSimplexTableWithLessThanConstraints(
        AlbaMatrix<DataType> const& constraintsCoefficients,
        AlbaMatrixData<DataType> const& constraintsValues,
        AlbaMatrixData<DataType> const& objectiveFunctionCoefficients);

template <typename DataType>
void solveSimplexTable(AlbaMatrix<DataType> & simplexTable);

template <typename DataType>
bool isOptimal(AlbaMatrix<DataType> const& simplexTable);

template <typename DataType>
unsigned int getPivotingColumnUsingBlandsRule(AlbaMatrix<DataType> const& simplexTable);

template <typename DataType>
unsigned int getPivotingRowUsingMinRatioRule(AlbaMatrix<DataType> const& simplexTable, unsigned int const pivotingColumn);

template <typename DataType>
void pivotAt(AlbaMatrix<DataType> & simplexTable, unsigned int const pivotingColumn, unsigned int const pivotingRow);

}

}//namespace alba
