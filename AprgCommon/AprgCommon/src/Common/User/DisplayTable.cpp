#include "DisplayTable.hpp"

#include <Common/String/AlbaStringHelper.hpp>

#include <algorithm>

using namespace alba::stringHelper;
using namespace std;

namespace alba
{

DisplayTableCell::DisplayTableCell()
    : m_displayText()
    , m_horizontalMode(DisplayTableCellMode::center)
{}

DisplayTableCell::DisplayTableCell(string const& displayText)
    : m_displayText(displayText)
    , m_horizontalMode(DisplayTableCellMode::center)
{}

DisplayTableCell::DisplayTableCell(string const& displayText, DisplayTableCellMode const horizontalMode)
    : m_displayText(displayText)
    , m_horizontalMode(horizontalMode)
{}

string DisplayTableCell::getText() const
{
    return m_displayText;
}

DisplayTableCellMode DisplayTableCell::getHorizontalMode() const
{
    return m_horizontalMode;
}

string& DisplayTableCell::getTextReference()
{
    return m_displayText;
}

void DisplayTableCell::setText(string const& text)
{
    m_displayText = text;
}

void DisplayTableCell::setHorizontalMode(DisplayTableCellMode const mode)
{
    m_horizontalMode = mode;
}

DisplayTableRow::DisplayTableRow(unsigned int const numberOfCells)
    : m_cells(numberOfCells)
{}

unsigned int DisplayTableRow::getNumberOfColumns() const
{
    return m_cells.size();
}

unsigned int DisplayTableRow::getCharacters() const
{
    unsigned int numberOfCharacters(0);
    for(DisplayTableCell const & cell : m_cells)
    {
        numberOfCharacters+=cell.getText().size();
    }
    return numberOfCharacters;
}

Cells const& DisplayTableRow::getCells() const
{
    return m_cells;
}

DisplayTableCell const& DisplayTableRow::getCellAt(unsigned int const columnIndex) const
{
    return m_cells.at(columnIndex);
}

Cells& DisplayTableRow::getCellsReference()
{
    return m_cells;
}

DisplayTableCell& DisplayTableRow::getCellReferenceAt(unsigned int const columnIndex)
{
    return m_cells[columnIndex];
}

void DisplayTableRow::addCell(string const & text)
{
    m_cells.emplace_back(text);
}

void DisplayTableRow::addCell(string const & text, DisplayTableCellMode const horizontalMode)
{
    m_cells.emplace_back(text, horizontalMode);
}

DisplayTable::DisplayTable(
        unsigned int const numberOfColumns,
        unsigned int const numberOfRows)
    : m_rows(numberOfRows, numberOfColumns)
{}

unsigned int DisplayTable::getTotalRows() const
{
    return m_rows.size();
}

unsigned int DisplayTable::getTotalColumns() const
{
    unsigned int maxColumns=0;
    for(DisplayTableRow const& row : m_rows)
    {
        maxColumns = max(maxColumns, row.getNumberOfColumns());
    }
    return maxColumns;
}

unsigned int DisplayTable::getMaxCharactersInOneRow() const
{
    unsigned int maxCharacters=0;
    for(DisplayTableRow const& row : m_rows)
    {
        maxCharacters = max(maxCharacters, row.getCharacters());
    }
    return maxCharacters;
}

DisplayTableCell const& DisplayTable::getCellAt(unsigned int const columnIndex, unsigned int const rowIndex) const
{
    return m_rows.at(rowIndex).getCellAt(columnIndex);
}

DisplayTableRow& DisplayTable::getLastRow()
{
    return m_rows.back();
}

DisplayTableRow& DisplayTable::getRowReferenceAt(unsigned int const rowIndex)
{
    return m_rows[rowIndex];
}

DisplayTableCell& DisplayTable::getCellReferenceAt(unsigned int const columnIndex,unsigned int const rowIndex)
{
    return m_rows[rowIndex].getCellReferenceAt(columnIndex);
}

void DisplayTable::addRow()
{
    m_rows.emplace_back();
}

void DisplayTable::setBorders(string const& horizontalBorder, string const& verticalBorder)
{
    m_horizontalBorder = horizontalBorder;
    m_verticalBorder = verticalBorder;
}

string DisplayTable::drawOutput()
{
    calculateLengthPerColumn();
    string horizontalLine(getHorizontalBorderLine());
    string buffer(horizontalLine);
    for(DisplayTableRow const& row : m_rows)
    {
        string line(getVerticalBorderPoint());
        unsigned int column=0;
        for(DisplayTableCell const& cell : row.getCells())
        {
            line+=getCellTextWithDesiredLength(cell, m_calculatedLengthPerColumn[column]);
            column++;
            line+=getVerticalBorderPoint();
        }
        buffer+=line+"\n";
        buffer+=horizontalLine;
    }
    return buffer;
}

void DisplayTable::calculateLengthPerColumn()
{
    unsigned int totalColumns = getTotalColumns();
    m_calculatedLengthPerColumn.resize(totalColumns, 0);
    for(DisplayTableRow & row : m_rows)
    {
        unsigned int column=0;
        for(DisplayTableCell & cell : row.getCellsReference())
        {
            m_calculatedLengthPerColumn[column] = max(m_calculatedLengthPerColumn[column], static_cast<unsigned int>(cell.getText().size()));
            column++;
        }
    }
}

string DisplayTable::getCellTextWithDesiredLength(DisplayTableCell const& cell, unsigned int const desiredLength) const
{
    DisplayTableCellMode mode = cell.getHorizontalMode();
    string result;
    switch(mode)
    {
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

unsigned int DisplayTable::getTotalColumnLength() const
{
    unsigned int totalColumnLength=0;
    for(unsigned int lengthPerColumn : m_calculatedLengthPerColumn)
    {
        totalColumnLength+=lengthPerColumn;
    }
    return totalColumnLength;
}

string DisplayTable::getHorizontalBorderLine() const
{
    string result;
    if(!m_horizontalBorder.empty())
    {
        result = getStringByRepeatingUntilDesiredLength(m_horizontalBorder, getHorizontalBorderLength(getTotalColumnLength()))+"\n";
    }
    return result;
}

string DisplayTable::getVerticalBorderPoint() const
{
    return m_verticalBorder;
}

unsigned int DisplayTable::getVerticalBorderLength() const
{
    return m_verticalBorder.length();
}

unsigned int DisplayTable::getHorizontalBorderLength(unsigned int const totalColumnLength) const
{
    return ((getTotalColumns()+1)*getVerticalBorderLength())+totalColumnLength;
}


}//namespace alba
