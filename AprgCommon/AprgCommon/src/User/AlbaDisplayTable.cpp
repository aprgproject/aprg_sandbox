#include "AlbaDisplayTable.hpp"

#include <String/AlbaStringHelper.hpp>

#include <algorithm>

using namespace std;

namespace alba
{

DisplayTableCell::DisplayTableCell()
    : m_textToDisplay("")
    , m_horizontalMode(DisplayTableCellMode::center)
    , m_verticalMode(DisplayTableCellMode::center)
{}

DisplayTableCell::DisplayTableCell(string const& text)
    : m_textToDisplay(text)
    , m_horizontalMode(DisplayTableCellMode::center)
    , m_verticalMode(DisplayTableCellMode::center)
{}

DisplayTableCell::DisplayTableCell(string const& text, DisplayTableCellMode const horizontalMode, DisplayTableCellMode const verticalMode)
    : m_textToDisplay(text)
    , m_horizontalMode(horizontalMode)
    , m_verticalMode(verticalMode)
{}
string DisplayTableCell::getText() const
{
    return m_textToDisplay;
}

DisplayTableCellMode DisplayTableCell::getHorizontalMode() const
{
    return m_horizontalMode;
}

DisplayTableCellMode DisplayTableCell::getVerticalMode() const
{
    return m_verticalMode;
}

void DisplayTableCell::setText(string const& text)
{
    m_textToDisplay = text;
}

void DisplayTableCell::setHorizontalMode(DisplayTableCellMode const mode)
{
    m_horizontalMode = mode;
}

void DisplayTableCell::setVerticalMode(DisplayTableCellMode const mode)
{
    m_verticalMode = mode;
}

DisplayTableRow::DisplayTableRow()
    : m_rowMode(DisplayTableRowMode::align)
{}

bool DisplayTableRow::isAlign() const{
    return DisplayTableRowMode::align == m_rowMode;
}

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

Cells& DisplayTableRow::getCellsReference()
{
    return m_cells;
}

DisplayTableCell& DisplayTableRow::getCellReference(unsigned int columnIndex)
{
    return m_cells[columnIndex];
}

DisplayTableCell const& DisplayTableRow::getCellConstReference(unsigned int columnIndex) const
{
    return m_cells[columnIndex];
}

void DisplayTableRow::addCell(string const & text)
{
    m_cells.emplace_back(text);
}

void DisplayTableRow::addCell(string const & text, DisplayTableCellMode const horizontalMode, DisplayTableCellMode const verticalMode)
{
    m_cells.emplace_back(text, horizontalMode, verticalMode);
}

DisplayTable::DisplayTable(){}

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

DisplayTableRow& DisplayTable::getLastRow()
{
    return m_rows.back();
}

DisplayTableRow& DisplayTable::getRowReference(unsigned int rowIndex)
{
    return m_rows[rowIndex];
}

DisplayTableCell& DisplayTable::getCellReference(unsigned int rowIndex, unsigned int columnIndex)
{
    return m_rows[rowIndex].getCellReference(columnIndex);
}

DisplayTableCell const& DisplayTable::getCellConstReference(unsigned int rowIndex, unsigned int columnIndex) const
{
    return m_rows[rowIndex].getCellConstReference(columnIndex);
}

void DisplayTable::addRow()
{
    m_rows.emplace_back();
}

void DisplayTable::setBorders(string const& horizontalBorder, string const& verticalBorder){
    m_horizontalBorder = horizontalBorder;
    m_verticalBorder = verticalBorder;
}

std::string DisplayTable::getCellText(DisplayTableCell const& cell, unsigned int length) const
{
    DisplayTableCellMode mode = cell.getHorizontalMode();
    string result;
    switch(mode)
    {
    case DisplayTableCellMode::justify:
        result = stringHelper::getStringWithJustifyAlignment(cell.getText(), length);
        break;
    case DisplayTableCellMode::center:
        result = stringHelper::getStringWithCenterAlignment(cell.getText(), length);
        break;
    case DisplayTableCellMode::right:
        result = stringHelper::getStringWithRightAlignment(cell.getText(), length);
        break;
    case DisplayTableCellMode::left:
        result = stringHelper::getStringWithLeftAlignment(cell.getText(), length);
        break;
    }
    return result;
}

void DisplayTable::calculateLengthPerColumn()
{
    unsigned int totalColumns = getTotalColumns();
    m_calculatedLengthPerColumn.resize(totalColumns);
    for(unsigned int i=0; i<totalColumns; i++)
    {
        m_calculatedLengthPerColumn[i]=0;
    }
    for(DisplayTableRow & row : m_rows)
    {
        unsigned int column=0;
        for(DisplayTableCell & cell : row.getCellsReference())
        {
            if(row.isAlign())
            {
                m_calculatedLengthPerColumn[column] = std::max(m_calculatedLengthPerColumn[column], static_cast<unsigned int>(cell.getText().size()));
            }
            column++;
        }
    }
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
        result = stringHelper::getStringByRepeatingUntilDesiredLength(m_horizontalBorder, getHorizontalBorderLength(getTotalColumnLength()))+"\n";
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

string DisplayTable::drawOutput()
{
    calculateLengthPerColumn();
    string horizontalLine(getHorizontalBorderLine());
    string buffer(horizontalLine);
    for(DisplayTableRow & row : m_rows)
    {
        string line(getVerticalBorderPoint());
        unsigned int column=0;
        for(DisplayTableCell & cell : row.getCellsReference())
        {
            if(row.isAlign())
            {
                line+=getCellText(cell, m_calculatedLengthPerColumn[column]);
            }
            column++;
            line+=getVerticalBorderPoint();
        }
        buffer+=line+"\n";
        buffer+=horizontalLine;
    }
    return buffer;
}


}//namespace alba
