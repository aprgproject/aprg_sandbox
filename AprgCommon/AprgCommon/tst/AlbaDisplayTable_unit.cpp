#include <User/AlbaDisplayTable.hpp>
#include <gtest/gtest.h>
#include <windows.h>

using namespace alba;
using namespace std;

TEST(AlbaTableDisplay, TableCanOutputProvideText)
{
    DisplayTable table;
    table.addRow();
    table.getLastRow().addCell("Test");
    EXPECT_EQ("Test\n", table.drawOutput());
    cout<<table.drawOutput();
}

TEST(AlbaTableDisplay, TableCanOutputTextWithBorders){
    DisplayTable table;
    table.addRow();
    table.getLastRow().addCell("Test");
    table.setBorders("X","X");
    EXPECT_EQ("XXXXXX\nXTestX\nXXXXXX\n", table.drawOutput());
    cout<<table.drawOutput();
}

TEST(AlbaTableDisplay, TableCanOutputTextFor3by3Table){
    DisplayTable table;
    table.addRow();
    table.getLastRow().addCell("1000");    table.getLastRow().addCell("2");
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