#include <Common/User/DisplayTable.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(DisplayTableTest, TableCanOutputProvideText)
{
    DisplayTable table;

    table.addRow();
    table.getLastRow().addCell("Test");

    EXPECT_EQ("Test\n", table.drawOutput());
}

TEST(DisplayTableTest, TableCanOutputTextWithBorders)
{
    DisplayTable table;

    table.setBorders("X","X");
    table.addRow();
    table.getLastRow().addCell("Test");

    EXPECT_EQ("XXXXXX\nXTestX\nXXXXXX\n", table.drawOutput());
}

TEST(DisplayTableTest, TableCanOutputTextFor3by3Table)
{
    DisplayTable table;

    table.setBorders("-","|");
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

    EXPECT_EQ("----------------\n|1000|2|   3   |\n----------------\n|4.1 |5| 6.55  |\n----------------\n| 7  |8|9000000|\n----------------\n",
              table.drawOutput());
}

TEST(DisplayTableTest, CellWithAlignmentCanBeAdded)
{
    DisplayTable table;

    table.addRow();
    table.getLastRow().addCell("12345");
    table.addRow();
    table.getLastRow().addCell("C", DisplayTableCellMode::center);
    table.addRow();
    table.getLastRow().addCell("L", DisplayTableCellMode::left);
    table.addRow();
    table.getLastRow().addCell("R", DisplayTableCellMode::right);
    table.addRow();
    table.getLastRow().addCell("J", DisplayTableCellMode::justify);

    EXPECT_EQ("12345\n  C  \nL    \n    R\n  J  \n", table.drawOutput());
}

TEST(DisplayTableTest, CanBeConstructedWithNumberOfColumnsAndRows)
{
    DisplayTable table(2U, 3U);

    table.setBorders("-","|");
    table.getCellReferenceAt(0U, 0U).setText("(0,0)");
    table.getCellReferenceAt(0U, 1U).setText("(0,1)");
    table.getCellReferenceAt(0U, 2U).setText("(0,2)");
    table.getCellReferenceAt(1U, 0U).setText("(1,0)");
    table.getCellReferenceAt(1U, 1U).setText("(1,1)");
    table.getCellReferenceAt(1U, 2U).setText("(1,2)");

    EXPECT_EQ("-------------\n|(0,0)|(1,0)|\n-------------\n|(0,1)|(1,1)|\n-------------\n|(0,2)|(1,2)|\n-------------\n",
              table.drawOutput());
}

}
