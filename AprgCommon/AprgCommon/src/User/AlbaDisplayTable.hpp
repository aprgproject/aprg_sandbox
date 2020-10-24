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
    DisplayTableCell(unsigned int columnIndex);
    DisplayTableCell(unsigned int columnIndex, std::string const& text);

    std::string getText() const;
    DisplayTableCellMode getHorizontalMode() const;
    DisplayTableCellMode getVerticalMode() const;

    void setText(std::string const& text);
    void setHorizontalMode(DisplayTableCellMode const mode);
    void setVerticalMode(DisplayTableCellMode const mode);
private:
    int m_columnIndex;
    std::string m_textToDisplay;
    DisplayTableCellMode m_horizontalMode;
    DisplayTableCellMode m_verticalMode;
};

using Cells = std::vector<DisplayTableCell>;

class DisplayTableRow
{
public:    DisplayTableRow(unsigned int rowIndex);
    bool isAlign() const;
    unsigned int getNumberOfColumns() const;
    unsigned int getCharacters() const;

    Cells& getCellsReference();
    DisplayTableCell& getCellReference(unsigned int columnIndex);
    void addCell(std::string const& text);
private:
    int m_rowIndex;
    DisplayTableRowMode m_rowMode;
    Cells m_cells;
};

class DisplayTable{
public:
    DisplayTable();
    unsigned int getTotalRows() const;
    unsigned int getTotalColumns() const;
    unsigned int getMaxCharactersInOneRow() const;
    std::string getCellText(DisplayTableCell const& cell, unsigned int length) const;

    DisplayTableRow& getLastRow();
    DisplayTableRow& getRowReference(unsigned int rowIndex);
    DisplayTableCell& getCellReference(unsigned int rowIndex, unsigned int columnIndex);

    void addRow();
    void setBorders(std::string const& horizontalBorder, std::string const& verticalBorder);

    std::string drawOutput();
private:

    void calculateLengthPerColumn();
    unsigned int getTotalColumnLength() const;
    std::string getHorizontalBorderLine() const;
    std::string getVerticalBorderPoint() const;
    unsigned int getVerticalBorderLength() const;
    unsigned int getHorizontalBorderLength(unsigned int const totalColumnLength) const;

    std::string m_horizontalBorder;
    std::string m_verticalBorder;
    std::vector<DisplayTableRow> m_rows;
    std::vector<unsigned int> m_calculatedLengthPerColumn;
};


}//namespace alba