#include <User/DisplayTable.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(DisplayTable, TableCanOutputProvideText)
{
    DisplayTable table;
    table.addRow();
    table.getLastRow().addCell("Test");
    EXPECT_EQ("Test\n", table.drawOutput());
    cout<<table.drawOutput();
}

TEST(DisplayTable, TableCanOutputTextWithBorders)
{
    DisplayTable table;
    table.addRow();
    table.getLastRow().addCell("Test");
    table.setBorders("X","X");
    EXPECT_EQ("XXXXXX\nXTestX\nXXXXXX\n", table.drawOutput());
    cout<<table.drawOutput();
}

TEST(DisplayTable, TableCanOutputTextFor3by3Table)
{
    DisplayTable table;
    table.addRow();
    table.getLastRow().addCell("1000");
    table.getLastRow().addCell("2");
    table.getLastRow().addCell("3");
    table.addRow();
    table.getLastRow().addCell("4.1");
    table.getLastRow().addCell("5");
    table.getLastRow().addCell("6.55");
    table.addRow();
    table.getLastRow().addCell("7");
    table.getLastRow().addCell("8");
    table.getLastRow().addCell("9000000");
    table.setBorders("-","|");
    EXPECT_EQ("----------------\n|1000|2|   3   |\n----------------\n|4.1 |5| 6.55  |\n----------------\n| 7  |8|9000000|\n----------------\n", table.drawOutput());
    cout<<table.drawOutput();
}

TEST(DisplayTable, CellWithAlignmentCanBeAdded)
{
    DisplayTable table;
    table.addRow();
    table.getLastRow().addCell("12345");
    table.addRow();
    table.getLastRow().addCell("C", DisplayTableCellMode::center, DisplayTableCellMode::center);
    table.addRow();
    table.getLastRow().addCell("L", DisplayTableCellMode::left, DisplayTableCellMode::center);
    table.addRow();
    table.getLastRow().addCell("R", DisplayTableCellMode::right, DisplayTableCellMode::center);
    table.addRow();
    table.getLastRow().addCell("J", DisplayTableCellMode::justify, DisplayTableCellMode::center);
    EXPECT_EQ("12345\n  C  \nL    \n    R\n  J  \n", table.drawOutput());
    cout<<table.drawOutput();
}

}
