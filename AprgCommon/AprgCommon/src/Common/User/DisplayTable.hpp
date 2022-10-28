#pragma once

#include <string>
#include <vector>

namespace alba
{

enum class DisplayTableCellMode
{
    justify,
    center,
    right,
    left
};

enum class DisplayTableRowMode
{
    align,
    justify
};


class DisplayTableCell
{
public:
    DisplayTableCell();
    DisplayTableCell(std::string const& displayText);
    DisplayTableCell(std::string const& displayText, DisplayTableCellMode const horizontalMode);

    std::string getText() const;
    DisplayTableCellMode getHorizontalMode() const;

    void setText(std::string const& text);
    void setHorizontalMode(DisplayTableCellMode const mode);
private:
    std::string m_displayText;
    DisplayTableCellMode m_horizontalMode;
};

using Cells = std::vector<DisplayTableCell>;
class DisplayTableRow
{
public:
    DisplayTableRow();

    unsigned int getNumberOfColumns() const;
    unsigned int getCharacters() const;
    Cells const& getCells() const;
    DisplayTableCell const& getCellAt(unsigned int columnIndex) const;

    Cells& getCellsReference();
    DisplayTableCell& getCellReferenceAt(unsigned int columnIndex);
    void addCell(std::string const& text);
    void addCell(std::string const & text, DisplayTableCellMode const horizontalMode);

private:
    Cells m_cells;
};
class DisplayTable
{
public:
    DisplayTable() = default;

    unsigned int getTotalRows() const;
    unsigned int getTotalColumns() const;
    unsigned int getMaxCharactersInOneRow() const;
    DisplayTableCell const& getCellAt(unsigned int rowIndex, unsigned int columnIndex) const;

    DisplayTableRow& getLastRow();
    DisplayTableRow& getRowReferenceAt(unsigned int rowIndex);
    DisplayTableCell& getCellReferenceAt(unsigned int rowIndex, unsigned int columnIndex);
    void addRow();
    void setBorders(std::string const& horizontalBorder, std::string const& verticalBorder);
    std::string drawOutput();
private:

    void calculateLengthPerColumn();
    std::string getCellTextWithDesiredLength(DisplayTableCell const& cell, unsigned int const desiredLength) const;
    unsigned int getTotalColumnLength() const;
    std::string getHorizontalBorderLine() const;
    std::string getVerticalBorderPoint() const;    unsigned int getVerticalBorderLength() const;
    unsigned int getHorizontalBorderLength(unsigned int const totalColumnLength) const;

    std::string m_horizontalBorder;    std::string m_verticalBorder;
    std::vector<DisplayTableRow> m_rows;
    std::vector<unsigned int> m_calculatedLengthPerColumn;
};



}//namespace alba
