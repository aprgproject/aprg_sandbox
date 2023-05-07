#include "DisplayTable.hpp"

#include <Common/String/AlbaStringHelper.hpp>

#include <algorithm>
#include <numeric>

using namespace alba::stringHelper;
using namespace std;

namespace alba {

DisplayTableCell::DisplayTableCell() : m_displayText(), m_horizontalMode(DisplayTableCellMode::center) {}

DisplayTableCell::DisplayTableCell(string_view displayText)
    : m_displayText(displayText), m_horizontalMode(DisplayTableCellMode::center) {}

DisplayTableCell::DisplayTableCell(string_view displayText, DisplayTableCellMode const horizontalMode)
    : m_displayText(displayText), m_horizontalMode(horizontalMode) {}

string DisplayTableCell::getText() const { return m_displayText; }

DisplayTableCellMode DisplayTableCell::getHorizontalMode() const { return m_horizontalMode; }

string& DisplayTableCell::getTextReference() { return m_displayText; }

void DisplayTableCell::setText(string_view text) { m_displayText = text; }

void DisplayTableCell::setHorizontalMode(DisplayTableCellMode const mode) { m_horizontalMode = mode; }

DisplayTableRow::DisplayTableRow(size_t const numberOfCells) : m_cells(numberOfCells) {}

size_t DisplayTableRow::getNumberOfColumns() const { return m_cells.size(); }

size_t DisplayTableRow::getCharacters() const {
    return accumulate(m_cells.cbegin(), m_cells.cend(), 0U, [](size_t partialSum, DisplayTableCell const& cell) {
        partialSum += cell.getText().size();
        return partialSum;
    });
}

Cells const& DisplayTableRow::getCells() const { return m_cells; }

DisplayTableCell const& DisplayTableRow::getCellAt(size_t const columnIndex) const { return m_cells.at(columnIndex); }

Cells& DisplayTableRow::getCellsReference() { return m_cells; }

DisplayTableCell& DisplayTableRow::getCellReferenceAt(size_t const columnIndex) { return m_cells[columnIndex]; }

void DisplayTableRow::addCell(string_view text) { m_cells.emplace_back(text); }

void DisplayTableRow::addCell(string_view text, DisplayTableCellMode const horizontalMode) {
    m_cells.emplace_back(text, horizontalMode);
}

DisplayTable::DisplayTable(size_t const numberOfColumns, size_t const numberOfRows)
    : m_rows(numberOfRows, numberOfColumns) {}

size_t DisplayTable::getTotalRows() const { return m_rows.size(); }

size_t DisplayTable::getTotalColumns() const {
    size_t maxColumns = 0;
    for (DisplayTableRow const& row : m_rows) {
        maxColumns = max(maxColumns, row.getNumberOfColumns());
    }
    return maxColumns;
}

size_t DisplayTable::getMaxCharactersInOneRow() const {
    size_t maxCharacters = 0;
    for (DisplayTableRow const& row : m_rows) {
        maxCharacters = max(maxCharacters, row.getCharacters());
    }
    return maxCharacters;
}

DisplayTableCell const& DisplayTable::getCellAt(size_t const columnIndex, size_t const rowIndex) const {
    return m_rows.at(rowIndex).getCellAt(columnIndex);
}

DisplayTableRow& DisplayTable::getLastRow() { return m_rows.back(); }

DisplayTableRow& DisplayTable::getRowReferenceAt(size_t const rowIndex) { return m_rows[rowIndex]; }

DisplayTableCell& DisplayTable::getCellReferenceAt(size_t const columnIndex, size_t const rowIndex) {
    return m_rows[rowIndex].getCellReferenceAt(columnIndex);
}

void DisplayTable::addRow() { m_rows.emplace_back(); }

void DisplayTable::setBorders(string_view horizontalBorder, string_view verticalBorder) {
    m_horizontalBorder = horizontalBorder;
    m_verticalBorder = verticalBorder;
}

void DisplayTable::setHorizontalBorder(std::string_view horizontalBorder) { m_horizontalBorder = horizontalBorder; }

void DisplayTable::setVerticalBorder(std::string_view verticalBorder) { m_verticalBorder = verticalBorder; }

string DisplayTable::getCellTextWithDesiredLength(DisplayTableCell const& cell, size_t const desiredLength) const {
    DisplayTableCellMode mode = cell.getHorizontalMode();
    string result;
    switch (mode) {
        case DisplayTableCellMode::justify:
            result = getStringWithJustifyAlignment(cell.getText(), desiredLength);
            break;
        case DisplayTableCellMode::center:
            result = getStringWithCenterAlignment(cell.getText(), desiredLength);
            break;
        case DisplayTableCellMode::right:
            result = getStringWithRightAlignment(cell.getText(), desiredLength);
            break;
        case DisplayTableCellMode::left:
            result = getStringWithLeftAlignment(cell.getText(), desiredLength);
            break;
    }
    return result;
}

string DisplayTable::getHorizontalBorderLine(size_t const totalColumnLength) const {
    string result;
    if (!m_horizontalBorder.empty()) {
        result =
            getStringByRepeatingUntilDesiredLength(m_horizontalBorder, getHorizontalBorderLength(totalColumnLength)) +
            "\n";
    }
    return result;
}

string DisplayTable::getVerticalBorderPoint() const { return m_verticalBorder; }

size_t DisplayTable::getVerticalBorderLength() const { return m_verticalBorder.length(); }

size_t DisplayTable::getHorizontalBorderLength(size_t const totalColumnLength) const {
    return ((getTotalColumns() + 1) * getVerticalBorderLength()) + totalColumnLength;
}

ostream& operator<<(ostream& out, DisplayTable const& displayTable) {
    vector<size_t> calculatedLengthPerColumn(displayTable.getTotalColumns(), 0);
    for (DisplayTableRow const& row : displayTable.m_rows) {
        size_t column = 0;
        for (DisplayTableCell const& cell : row.getCells()) {
            calculatedLengthPerColumn[column] =
                max(calculatedLengthPerColumn[column], static_cast<size_t>(cell.getText().size()));
            column++;
        }
    }

    size_t totalColumnLength = accumulate(
        calculatedLengthPerColumn.cbegin(), calculatedLengthPerColumn.cend(), 0U,
        [](size_t partialSum, size_t const lengthPerColumn) {
            partialSum += lengthPerColumn;
            return partialSum;
        });

    string horizontalLine(displayTable.getHorizontalBorderLine(totalColumnLength));
    string verticalBorderPoint(displayTable.getVerticalBorderPoint());
    out << horizontalLine;
    for (DisplayTableRow const& row : displayTable.m_rows) {
        out << verticalBorderPoint;
        size_t column = 0;
        for (DisplayTableCell const& cell : row.getCells()) {
            out << displayTable.getCellTextWithDesiredLength(cell, calculatedLengthPerColumn[column]);
            column++;
            out << verticalBorderPoint;
        }
        out << "\n";
        out << horizontalLine;
    }
    return out;
}

}  // namespace alba
