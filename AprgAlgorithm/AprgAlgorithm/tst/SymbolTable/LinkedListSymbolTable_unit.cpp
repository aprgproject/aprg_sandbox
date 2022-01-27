#include <SymbolTable/LinkedListSymbolTable.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace
{
using SymbolTableForTest = LinkedListSymbolTable<unsigned int, char>;
}

TEST(LinkedListSymbolTableTest, IsEmptyWorks)
{
    SymbolTableForTest symbolTable1;
    SymbolTableForTest symbolTable2;
    symbolTable2.put(5U, 'E');

    EXPECT_TRUE(symbolTable1.isEmpty());
    EXPECT_FALSE(symbolTable2.isEmpty());
}

TEST(LinkedListSymbolTableTest, GetSizeWorks)
{
    SymbolTableForTest symbolTable1;
    SymbolTableForTest symbolTable2;
    symbolTable2.put(5U, 'E');
    symbolTable2.put(6U, 'F');
    symbolTable2.put(7U, 'G');

    EXPECT_EQ(0U, symbolTable1.getSize());
    EXPECT_EQ(3U, symbolTable2.getSize());
}

TEST(LinkedListSymbolTableTest, GetWorks)
{
    SymbolTableForTest symbolTable;
    symbolTable.put(5U, 'E');
    symbolTable.put(6U, 'F');
    symbolTable.put(7U, 'G');

    EXPECT_EQ('E', symbolTable.get(5U));
    EXPECT_EQ('F', symbolTable.get(6U));
    EXPECT_EQ('G', symbolTable.get(7U));
    EXPECT_EQ('\0', symbolTable.get(8U));
}

TEST(LinkedListSymbolTableTest, PutWorks)
{
    SymbolTableForTest symbolTable;

    symbolTable.put(5U, 'E');
    symbolTable.put(6U, 'F');
    symbolTable.put(7U, 'G');

    EXPECT_EQ(3U, symbolTable.getSize());
    EXPECT_EQ('E', symbolTable.get(5U));
    EXPECT_EQ('F', symbolTable.get(6U));
    EXPECT_EQ('G', symbolTable.get(7U));
}

}
