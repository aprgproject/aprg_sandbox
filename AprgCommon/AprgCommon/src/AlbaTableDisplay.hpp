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

class DisplayTableRow
{
public:
    DisplayTableRow(unsigned int rowIndex);
    bool isAlign() const;
    unsigned int getNumberOfColumns() const;
    unsigned int getCharacters();
    std::vector<DisplayTableCell>& getCells();
    DisplayTableCell& getCellReference(unsigned int columnIndex);
    void addCell(std::string const& text);

private:
    int m_rowIndex;
    DisplayTableRowMode m_rowMode;
    std::vector<DisplayTableCell> m_cells;
};

class DisplayTable
{
public:
    DisplayTable();
    std::string drawOutput();

    DisplayTableRow& getLastRow();
    DisplayTableRow& getRowReference(unsigned int rowIndex);
    DisplayTableCell& getCellReference(unsigned int rowIndex, unsigned int columnIndex);
    void addRow();
    unsigned int getTotalRows();
    unsigned int getTotalColumns();
    unsigned int getMaxCharactersInOneRow();
    void setBorders(char horizontalBorder, char verticalBorder);
    std::string getCellText(DisplayTableCell const& cell, unsigned int length);

private:
    char m_horizontalBorder;
    char m_verticalBorder;
    std::vector<DisplayTableRow> m_rows;
};



}//namespace alba
