#pragma once

#include <Common/Math/Matrix/Utilities/Simplex.hpp>

namespace alba {

namespace algorithm {

template <typename Value>
class SimplexAlgorithm {
public:
    using Matrix = matrix::AlbaMatrix<Value>;
    using MatrixData = matrix::AlbaMatrixData<Value>;

    SimplexAlgorithm(
        Matrix const& constraintsCoefficients, MatrixData const& constraintsValues,
        MatrixData const& objectiveFunctionCoefficients)
        : m_simplexTable(matrix::constructSimplexTableWithLessThanConstraints(
              constraintsCoefficients, constraintsValues, objectiveFunctionCoefficients)) {
        matrix::solveSimplexTable(m_simplexTable);
    }

    bool isOptimized() const { return matrix::isOptimal(m_simplexTable); }

    Value getOptimizedObjectiveValue() const {
        return m_simplexTable.getEntry(m_simplexTable.getNumberOfColumns() - 1, m_simplexTable.getNumberOfRows() - 1) *
               -1;
    }

    Matrix getSolution() const {
        int numberOfRows = m_simplexTable.getNumberOfRows() - 1;
        int numberOfColumns = m_simplexTable.getNumberOfColumns() - numberOfRows;
        Matrix result(numberOfColumns, numberOfRows);
        int lastXInSimplex(m_simplexTable.getNumberOfColumns() - 1);
        int lastXInResult(result.getNumberOfColumns() - 1);
        result.iterateAllThroughYAndThenX([&](int const x, int const y) {
            if (x == lastXInResult) {
                result.setEntry(x, y, m_simplexTable.getEntry(lastXInSimplex, y));
            } else {
                result.setEntry(x, y, m_simplexTable.getEntry(x, y));
            }
        });
        return result;
    }

private:
    Matrix m_simplexTable;
};

}  // namespace algorithm

}  // namespace alba
