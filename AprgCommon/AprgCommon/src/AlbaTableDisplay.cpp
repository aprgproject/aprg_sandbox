#include <AlbaTableDisplay.hpp>

#include <AlbaStringHelper.hpp>

using namespace std;

namespace alba
{

DisplayTableCell::DisplayTableCell(unsigned int columnIndex)
    : m_columnIndex(columnIndex)
    , m_textToDisplay("")
    , m_horizontalMode(DisplayTableCellMode::center)
    , m_verticalMode(DisplayTableCellMode::center)
{}

DisplayTableCell::DisplayTableCell(unsigned int columnIndex, string const& text)
    : m_columnIndex(columnIndex)
    , m_textToDisplay(text)
    , m_horizontalMode(DisplayTableCellMode::center)
    , m_verticalMode(DisplayTableCellMode::center)
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

DisplayTableRow::DisplayTableRow(unsigned int rowIndex)
    : m_rowIndex(rowIndex)
    , m_rowMode(DisplayTableRowMode::align)
{}

unsigned int DisplayTableRow::getNumberOfColumns() const
{
    return m_cells.size();
}

bool DisplayTableRow::isAlign() const
{
    return DisplayTableRowMode::align == m_rowMode;
}

unsigned int DisplayTableRow::getCharacters()
{
    unsigned int numberOfCharacters(0);
    for(DisplayTableCell & cell : getCells())
    {
        numberOfCharacters+=cell.getText().size();
    }
    return numberOfCharacters;
}

vector<DisplayTableCell>& DisplayTableRow::getCells()
{
    return m_cells;
}

DisplayTableCell& DisplayTableRow::getCellReference(unsigned int columnIndex)
{
    return m_cells[columnIndex];
}

void DisplayTableRow::addCell(string const & text)
{
    m_cells.emplace_back(getNumberOfColumns(), text);
}

DisplayTable::DisplayTable()
    : m_horizontalBorder(' ')
    , m_verticalBorder(' ')
{}

string DisplayTable::drawOutput()
{
    vector <unsigned int> determinedLengthPerColumn(getTotalColumns(), 0);
    for(DisplayTableRow & row : m_rows)
    {
        int column=0;
        for(DisplayTableCell & cell : row.getCells())
        {
            if(row.isAlign())
            {
                determinedLengthPerColumn[column] = std::max(determinedLengthPerColumn[column], cell.getText().size());
                column++;
            }
        }
    }
    int totalColumnLength=0;
    for(unsigned int & lengthPerColumn : determinedLengthPerColumn)
    {
        totalColumnLength+=lengthPerColumn;
    }
    string horizontalLine(getTotalColumns()+totalColumnLength+1, m_horizontalBorder);
    string buffer(horizontalLine);
    buffer+="\n";
    for(DisplayTableRow & row : m_rows)
    {
        string line;
        line+=m_verticalBorder;
        int column=0;
        for(DisplayTableCell & cell : row.getCells())
        {
            if(row.isAlign())
            {
                line+=getCellText(cell, determinedLengthPerColumn[column++]);
            }
            line+=m_verticalBorder;
        }
        buffer+=line;
        buffer+="\n";
    }
    buffer+=horizontalLine;
    buffer+="\n";
    return buffer;
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

void DisplayTable::addRow()
{
    m_rows.emplace_back(getTotalRows());
}

unsigned int DisplayTable::getTotalRows()
{
    return m_rows.size();
}

unsigned int DisplayTable::getTotalColumns()
{
    unsigned int maxColumns=0;
    for(DisplayTableRow const& row : m_rows)
    {
        maxColumns = max(maxColumns, row.getNumberOfColumns());
    }
    return maxColumns;
}

unsigned int DisplayTable::getMaxCharactersInOneRow()
{
    unsigned int maxCharacters=0;
    for(DisplayTableRow& row : m_rows)
    {
        maxCharacters = max(maxCharacters, row.getCharacters());
    }
    return maxCharacters;
}

void DisplayTable::setBorders(char horizontalBorder, char verticalBorder)
{
    m_horizontalBorder = horizontalBorder;
    m_verticalBorder = verticalBorder;
}

std::string DisplayTable::getCellText(DisplayTableCell const& cell, unsigned int length)
{
    DisplayTableCellMode mode = cell.getHorizontalMode();
    string result;
    switch(mode)
    {
    case DisplayTableCellMode::justify:
        result = stringHelper::getStringUsingJustifyAlignment(cell.getText(), length);
        break;
    case DisplayTableCellMode::center:
        result = stringHelper::getStringUsingCenterAlignment(cell.getText(), length);
        break;
    case DisplayTableCellMode::right:
        result = stringHelper::getStringUsingRightAlignment(cell.getText(), length);
        break;
    case DisplayTableCellMode::left:
        result = stringHelper::getStringUsingLeftAlignment(cell.getText(), length);
        break;
    }
    return result;
}


}//namespace alba
