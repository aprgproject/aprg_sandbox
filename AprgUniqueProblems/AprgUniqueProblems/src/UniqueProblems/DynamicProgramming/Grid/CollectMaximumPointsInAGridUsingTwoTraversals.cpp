#include "CollectMaximumPointsInAGridUsingTwoTraversals.hpp"

using namespace std;

namespace alba {

namespace {
vector<pair<int, int>> columnsOffsets{{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 0}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
}

CollectMaximumPointsInAGridUsingTwoTraversals::CollectMaximumPointsInAGridUsingTwoTraversals(ValueGrid const& inputGrid)
    : m_inputGrid(inputGrid) {}

CollectMaximumPointsInAGridUsingTwoTraversals::Value
CollectMaximumPointsInAGridUsingTwoTraversals::getMaximumPointsUsingNaiveRecursion() const {
    // Time Complexity: Exponential -> Since there are nine calls per iteration:  O(9^rows)
    // Auxiliary Space: Constant

    Value result(0);
    if (!m_inputGrid.isEmpty()) {
        result = getMaximumPointsUsingNaiveRecursion(0, 0, m_inputGrid.getNumberOfColumns() - 1);
    }
    return result;
}

CollectMaximumPointsInAGridUsingTwoTraversals::Value
CollectMaximumPointsInAGridUsingTwoTraversals::getMaximumPointsUsingMemoizationDP() const {
    // Time Complexity: Exponential -> Since there are nine calls per iteration:  O(9^rows)
    // Auxiliary Space: O(rows*columns*columns)

    Value result(0);
    if (!m_inputGrid.isEmpty()) {
        ValueGrid initialValueGrid(m_inputGrid.getNumberOfColumns(), m_inputGrid.getNumberOfColumns(), UNUSED_COUNT);
        ValueGrids valueGrids(m_inputGrid.getNumberOfRows(), initialValueGrid);
        result = getMaximumPointsUsingMemoizationDP(valueGrids, 0, 0, m_inputGrid.getNumberOfColumns() - 1);
    }
    return result;
}

CollectMaximumPointsInAGridUsingTwoTraversals::Value
CollectMaximumPointsInAGridUsingTwoTraversals::getMaximumPointsUsingIterativeDP() const {
    // Time Complexity: O(rows*columns*columns)
    // Auxiliary Space: O(rows*columns*columns)

    Value result(0);
    if (!m_inputGrid.isEmpty()) {
        ValueGrid initialValueGrid(m_inputGrid.getNumberOfColumns(), m_inputGrid.getNumberOfColumns(), INVALID_COUNT);
        ValueGrids valueGrids(m_inputGrid.getNumberOfRows(), initialValueGrid);

        {
            Index columnLeft(0);
            Index columnRight(m_inputGrid.getNumberOfColumns() - 1);
            Value firstEntryResult = (columnLeft == columnRight)
                                         ? m_inputGrid.getEntry(columnLeft, 0)
                                         : m_inputGrid.getEntry(columnLeft, 0) + m_inputGrid.getEntry(columnRight, 0);
            valueGrids[0].setEntry(columnLeft, columnRight, firstEntryResult);
        }

        for (Index row(1); row < static_cast<Index>(m_inputGrid.getNumberOfRows()); row++) {
            for (Index columnLeft(0); columnLeft < static_cast<Index>(m_inputGrid.getNumberOfColumns()); columnLeft++) {
                for (Index columnRight(0); columnRight < static_cast<Index>(m_inputGrid.getNumberOfColumns());
                     columnRight++) {
                    Value entryResult(INVALID_COUNT);
                    for (auto const& [leftOffset, rightOffset] : columnsOffsets) {
                        Index previousRow = row - 1;
                        Index previousColumnLeft = columnLeft + leftOffset;
                        Index previousColumnRight = columnRight + rightOffset;
                        if (m_inputGrid.isInside(previousColumnLeft, previousRow) &&
                            m_inputGrid.isInside(previousColumnRight, previousRow)) {
                            Value previousValue =
                                valueGrids[previousRow].getEntry(previousColumnLeft, previousColumnRight);
                            if (INVALID_COUNT != previousValue) {
                                entryResult =
                                    (entryResult == INVALID_COUNT) ? previousValue : max(entryResult, previousValue);
                            }
                        }
                    }
                    if (INVALID_COUNT != entryResult) {
                        entryResult += (columnLeft == columnRight) ? m_inputGrid.getEntry(columnLeft, row)
                                                                   : m_inputGrid.getEntry(columnLeft, row) +
                                                                         m_inputGrid.getEntry(columnRight, row);
                    }
                    valueGrids[row].setEntry(columnLeft, columnRight, entryResult);
                }
            }
        }
        result = valueGrids.back().getEntry(0, m_inputGrid.getNumberOfColumns() - 1);
    }
    return result;
}

CollectMaximumPointsInAGridUsingTwoTraversals::Value
CollectMaximumPointsInAGridUsingTwoTraversals::getMaximumPointsUsingNaiveRecursion(
    Index const row, Index const columnLeft, Index const columnRight) const {
    Value result(0);
    if (row == static_cast<Index>(m_inputGrid.getNumberOfRows()) - 1 &&
        !(columnLeft == 0 && columnRight == static_cast<Index>(m_inputGrid.getNumberOfColumns()) - 1)) {
        // if last row did not reach destination
        result = INVALID_COUNT;
    } else {
        for (auto const& [leftOffset, rightOffset] : columnsOffsets) {
            Index nextRow = row + 1;
            Index nextColumnLeft = columnLeft + leftOffset;
            Index nextColumnRight = columnRight + rightOffset;
            if (m_inputGrid.isInside(nextColumnLeft, nextRow) && m_inputGrid.isInside(nextColumnRight, nextRow)) {
                Value nextValue = getMaximumPointsUsingNaiveRecursion(nextRow, nextColumnLeft, nextColumnRight);
                if (INVALID_COUNT != nextValue) {
                    result = max(result, nextValue);
                }
            }
        }
        result += (columnLeft == columnRight)
                      ? m_inputGrid.getEntry(columnLeft, row)
                      : m_inputGrid.getEntry(columnLeft, row) + m_inputGrid.getEntry(columnRight, row);
    }
    return result;
}

CollectMaximumPointsInAGridUsingTwoTraversals::Value
CollectMaximumPointsInAGridUsingTwoTraversals::getMaximumPointsUsingMemoizationDP(
    ValueGrids& valueGrids, Index const row, Index const columnLeft, Index const columnRight) const {
    Value result(valueGrids[row].getEntry(columnLeft, columnRight));
    if (UNUSED_COUNT == result) {
        result = 0;
        if (row == static_cast<Index>(m_inputGrid.getNumberOfRows()) - 1 &&
            !(columnLeft == 0 && columnRight == static_cast<Index>(m_inputGrid.getNumberOfColumns()) - 1)) {
            // if last row did not reach destination
            result = INVALID_COUNT;
        } else {
            for (auto const& [leftOffset, rightOffset] : columnsOffsets) {
                Index nextRow = row + 1;
                Index nextColumnLeft = columnLeft + leftOffset;
                Index nextColumnRight = columnRight + rightOffset;
                if (m_inputGrid.isInside(nextColumnLeft, nextRow) && m_inputGrid.isInside(nextColumnRight, nextRow)) {
                    Value nextValue =
                        getMaximumPointsUsingMemoizationDP(valueGrids, nextRow, nextColumnLeft, nextColumnRight);
                    if (INVALID_COUNT != nextValue) {
                        result = max(result, nextValue);
                    }
                }
            }
            result += (columnLeft == columnRight)
                          ? m_inputGrid.getEntry(columnLeft, row)
                          : m_inputGrid.getEntry(columnLeft, row) + m_inputGrid.getEntry(columnRight, row);
        }
        valueGrids[row].setEntry(columnLeft, columnRight, result);
    }
    return result;
}

}  // namespace alba
