#include "MatrixMultiplicationOrder.hpp"

using namespace std;

namespace alba {

MatrixMultiplicationOrder::MatrixMultiplicationOrder(Dimensions const& dimensions) : m_dimensions(dimensions) {}

MatrixMultiplicationOrder::Count MatrixMultiplicationOrder::getMinimumNumberOfOperationsUsingNaiveRecursion() const {
    // Time Complexity: Exponential
    // Auxiliary Space: Constant

    Count result(0);
    if (!m_dimensions.empty()) {
        result = getMinimumNumberOfOperationsUsingNaiveRecursion(0, m_dimensions.size() - 1);
    }
    return result;
}

MatrixMultiplicationOrder::Count MatrixMultiplicationOrder::getMinimumNumberOfOperationsUsingMemoizationDP() const {
    // Time Complexity: O(n^3) (should be same as Iterative DP)
    // Auxiliary Space: O(n^2)

    Count result(0);
    if (!m_dimensions.empty()) {
        CountMatrix countMatrix(m_dimensions.size(), m_dimensions.size(), MAX_COUNT);
        result = getMinimumNumberOfOperationsUsingMemoizationDP(countMatrix, 0, m_dimensions.size() - 1);
    }
    return result;
}

MatrixMultiplicationOrder::Count MatrixMultiplicationOrder::getMinimumNumberOfOperationsUsingIterativeDP() const {
    // Time Complexity: O(n^3)
    // Auxiliary Space: O(n^2)

    Count result(0);
    if (!m_dimensions.empty()) {
        CountMatrix countMatrix(m_dimensions.size(), m_dimensions.size(), 0);

        for (Index length = 3; length <= static_cast<Index>(m_dimensions.size()); length++) {
            for (Index leftParenthesis = 0;
                 leftParenthesis + length <= static_cast<Index>(countMatrix.getNumberOfColumns()); leftParenthesis++) {
                Index rightParenthesis = leftParenthesis + length - 1;
                Count minimumCount(MAX_COUNT);
                for (Index inBetween = leftParenthesis + 1; inBetween < rightParenthesis; inBetween++) {
                    Count currentCount =
                        countMatrix.getEntry(leftParenthesis, inBetween) +
                        countMatrix.getEntry(inBetween, rightParenthesis) +
                        m_dimensions[leftParenthesis] * m_dimensions[inBetween] * m_dimensions[rightParenthesis];
                    minimumCount = min(minimumCount, currentCount);
                }
                countMatrix.setEntry(leftParenthesis, rightParenthesis, minimumCount);
            }
        }
        result = countMatrix.getEntry(0, countMatrix.getNumberOfRows() - 1);
    }
    return result;
}

MatrixMultiplicationOrder::Count MatrixMultiplicationOrder::getMinimumNumberOfOperationsUsingNaiveRecursion(
    Index const leftParenthesis, Index const rightParenthesis) const {
    Count result(0);
    if (leftParenthesis + 2 <= rightParenthesis) {
        // distance should be two for at least three elements
        result = MAX_COUNT;
        for (Index inBetween = leftParenthesis + 1; inBetween < rightParenthesis; inBetween++) {
            Count currentCount =
                getMinimumNumberOfOperationsUsingNaiveRecursion(leftParenthesis, inBetween) +
                getMinimumNumberOfOperationsUsingNaiveRecursion(inBetween, rightParenthesis) +
                m_dimensions[leftParenthesis] * m_dimensions[inBetween] * m_dimensions[rightParenthesis];
            result = min(result, currentCount);
        }
    }
    return result;
}

MatrixMultiplicationOrder::Count MatrixMultiplicationOrder::getMinimumNumberOfOperationsUsingMemoizationDP(
    CountMatrix& countMatrix, Index const leftParenthesis, Index const rightParenthesis) const {
    Count result(countMatrix.getEntry(leftParenthesis, rightParenthesis));
    if (MAX_COUNT == result) {
        if (leftParenthesis + 2 <= rightParenthesis)  // distance should be two for at least three elements
        {
            // result is already set to MAX_COUNT so we can proceed on using min
            for (Index inBetween = leftParenthesis + 1; inBetween < rightParenthesis; inBetween++) {
                Count currentCount =
                    getMinimumNumberOfOperationsUsingMemoizationDP(countMatrix, leftParenthesis, inBetween) +
                    getMinimumNumberOfOperationsUsingMemoizationDP(countMatrix, inBetween, rightParenthesis) +
                    m_dimensions[leftParenthesis] * m_dimensions[inBetween] * m_dimensions[rightParenthesis];
                result = min(result, currentCount);
            }
        } else {
            result = 0;
        }
        countMatrix.setEntry(leftParenthesis, rightParenthesis, result);
    }
    return result;
}

}  // namespace alba
