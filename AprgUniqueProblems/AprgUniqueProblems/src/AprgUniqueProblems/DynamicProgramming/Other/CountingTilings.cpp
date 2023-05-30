#include "CountingTilings.hpp"

#include <stack>

using namespace std;

namespace alba {

CountingTilings::CountingTilings(Count const numberOfColumns, Count const numberOfRows)
    : m_numberOfColumns(numberOfColumns),
      m_numberOfRows(numberOfRows),
      m_numberOfCells(m_numberOfColumns * m_numberOfRows),
      m_numberFilledCells(0),
      m_numberOfSolutions(0),
      m_grid()  // just initialize this when searching
{}

CountingTilings::Count CountingTilings::getNumberOfSolutionsUsingDynamicProgramming() {
    // lets make the column the smaller dimension
    if (m_numberOfColumns > m_numberOfRows) {
        swap(m_numberOfColumns, m_numberOfRows);
    }

    m_numberOfSolutions = 0;

    Row currentRow(getEmptyRow(m_numberOfColumns));
    searchNextRow(0, currentRow);

    return m_numberOfSolutions;
}

CountingTilings::Count CountingTilings::getNumberOfSolutionsUsingCompleteSearch() {
    // This is not exactly DP but "complete search".
    startCompleteSearch();
    return m_numberOfSolutions;
}

CountingTilings::Row CountingTilings::getEmptyRow(Count const length) const { return Row(length, ' '); }

void CountingTilings::searchNextRow(Count const rowIndex, Row const& currentRow) {
    if (rowIndex < m_numberOfRows - 1) {
        for (Row const& nextRow : getNextRows(currentRow)) {
            searchNextRow(rowIndex + 1, nextRow);
        }
    } else if (rowIndex == m_numberOfRows - 1) {
        Row emptyRow(getEmptyRow(currentRow.length()));
        for (Row const& nextRow : getNextRows(currentRow)) {
            if (emptyRow == nextRow) {
                m_numberOfSolutions++;
            }
        }
    }
}

CountingTilings::Rows const& CountingTilings::getNextRows(Row const& currentRow) {
    auto it = m_currentRowToNextRows.find(currentRow);
    if (it != m_currentRowToNextRows.cend()) {
        return it->second;
    } else {
        m_currentRowToNextRows[currentRow] = calculateNextRows(currentRow);
        return m_currentRowToNextRows.at(currentRow);
    }
}

CountingTilings::Rows CountingTilings::calculateNextRows(Row const& currentRow) {
    // This is not exactly DP but "complete search".

    struct NextDetail {
        Row nextRow;
        Count nextIndex;
    };

    Rows result;
    stack<NextDetail> possibleNextDetails;
    possibleNextDetails.emplace(NextDetail{getEmptyRow(currentRow.length()), 0});
    while (!possibleNextDetails.empty()) {
        NextDetail const& nextDetail(possibleNextDetails.top());
        Row nextRow(nextDetail.nextRow);
        Count nextIndex(nextDetail.nextIndex);
        possibleNextDetails.pop();
        if (nextIndex >= static_cast<Count>(currentRow.length())) {
            result.emplace_back(nextRow);
        } else if (currentRow.at(nextIndex) == ' ') {
            if (nextIndex + 1 < static_cast<Count>(currentRow.length()) && currentRow.at(nextIndex + 1) == ' ') {
                possibleNextDetails.emplace(NextDetail{nextRow, nextIndex + 2});
            }
            nextRow[nextIndex] = 'V';
            possibleNextDetails.emplace(NextDetail{nextRow, nextIndex + 1});
        } else {
            possibleNextDetails.emplace(NextDetail{nextRow, nextIndex + 1});
        }
    }
    return result;
}

void CountingTilings::startCompleteSearch() {
    // This is not exactly DP but "complete search".

    m_numberOfSolutions = 0;
    m_numberFilledCells = 0;
    m_grid.clearAndResize(m_numberOfColumns, m_numberOfRows);

    doCompleteSearchAt(0);
}

void CountingTilings::doCompleteSearchAt(Count const gridIndex) {
    // This is not exactly DP but "complete search".

    if (m_numberFilledCells == m_numberOfCells) {
        m_numberOfSolutions++;
    } else if (gridIndex < m_numberOfCells) {
        size_t x, y;
        m_grid.retrieveXAndYFromIndex(x, y, gridIndex);
        if (m_grid.getEntry(x, y) == '\0') {
            if (m_grid.isInside(x + 1, y) && m_grid.getEntry(x + 1, y) == '\0') {
                m_grid.setEntry(x, y, 'H');
                m_grid.setEntry(x + 1, y, 'H');
                m_numberFilledCells += 2;
                doCompleteSearchAt(gridIndex + 2);
                m_grid.setEntry(x, y, '\0');
                m_grid.setEntry(x + 1, y, '\0');
                m_numberFilledCells -= 2;
            }
            if (m_grid.isInside(x, y + 1) && m_grid.getEntry(x, y + 1) == '\0') {
                m_grid.setEntry(x, y, 'V');
                m_grid.setEntry(x, y + 1, 'V');
                m_numberFilledCells += 2;
                doCompleteSearchAt(gridIndex + 1);
                m_grid.setEntry(x, y, '\0');
                m_grid.setEntry(x, y + 1, '\0');
                m_numberFilledCells -= 2;
            }
        } else {
            doCompleteSearchAt(gridIndex + 1);
        }
    }
}

}  // namespace alba
