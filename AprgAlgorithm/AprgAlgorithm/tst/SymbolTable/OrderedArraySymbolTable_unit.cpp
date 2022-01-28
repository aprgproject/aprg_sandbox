#include <SymbolTable/OrderedArraySymbolTable.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace
{
using SymbolTableForTest = OrderedArraySymbolTable<unsigned int, char>;
}

TEST(OrderedArraySymbolTableTest, IsEmptyWorks)
{
    SymbolTableForTest symbolTable1;
    SymbolTableForTest symbolTable2;
    symbolTable2.put(5U, 'E');

    EXPECT_TRUE(symbolTable1.isEmpty());
    EXPECT_FALSE(symbolTable2.isEmpty());
}

TEST(OrderedArraySymbolTableTest, GetSizeWorks)
{
    SymbolTableForTest symbolTable1;
    SymbolTableForTest symbolTable2;
    symbolTable2.put(5U, 'E');
    symbolTable2.put(6U, 'F');
    symbolTable2.put(7U, 'G');

    EXPECT_EQ(0U, symbolTable1.getSize());
    EXPECT_EQ(3U, symbolTable2.getSize());
}

TEST(OrderedArraySymbolTableTest, GetWorks)
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

TEST(OrderedArraySymbolTableTest, GetRankWorks)
{
    SymbolTableForTest symbolTable;
    symbolTable.put(4U, 'D');
    symbolTable.put(5U, 'E');
    symbolTable.put(7U, 'G');
    symbolTable.put(8U, 'H');

    EXPECT_EQ(0U, symbolTable.getRank(3U));
    EXPECT_EQ(0U, symbolTable.getRank(4U));
    EXPECT_EQ(1U, symbolTable.getRank(5U));
    EXPECT_EQ(2U, symbolTable.getRank(6U));
    EXPECT_EQ(2U, symbolTable.getRank(7U));
    EXPECT_EQ(3U, symbolTable.getRank(8U));
    EXPECT_EQ(4U, symbolTable.getRank(9U));
}

TEST(OrderedArraySymbolTableTest, GetMinimumWorks)
{
    SymbolTableForTest symbolTable;
    symbolTable.put(4U, 'D');
    symbolTable.put(5U, 'E');
    symbolTable.put(7U, 'G');
    symbolTable.put(8U, 'H');

    EXPECT_EQ(4U, symbolTable.getMinimum());
}

TEST(OrderedArraySymbolTableTest, GetMaximumWorks)
{
    SymbolTableForTest symbolTable;
    symbolTable.put(4U, 'D');
    symbolTable.put(5U, 'E');
    symbolTable.put(7U, 'G');
    symbolTable.put(8U, 'H');

    EXPECT_EQ(8U, symbolTable.getMaximum());
}

TEST(OrderedArraySymbolTableTest, SelectAtWorks)
{
    SymbolTableForTest symbolTable;
    symbolTable.put(4U, 'D');
    symbolTable.put(5U, 'E');
    symbolTable.put(7U, 'G');
    symbolTable.put(8U, 'H');

    EXPECT_EQ(4U, symbolTable.selectAt(0U));
    EXPECT_EQ(5U, symbolTable.selectAt(1U));
    EXPECT_EQ(7U, symbolTable.selectAt(2U));
    EXPECT_EQ(8U, symbolTable.selectAt(3U));
}

TEST(OrderedArraySymbolTableTest, GetFloorWorks)
{
    SymbolTableForTest symbolTable;
    symbolTable.put(4U, 'D');
    symbolTable.put(5U, 'E');
    symbolTable.put(7U, 'G');
    symbolTable.put(8U, 'H');

    EXPECT_EQ(0U, symbolTable.getFloor(3U));
    EXPECT_EQ(4U, symbolTable.getFloor(4U));
    EXPECT_EQ(5U, symbolTable.getFloor(5U));
    EXPECT_EQ(5U, symbolTable.getFloor(6U));
    EXPECT_EQ(7U, symbolTable.getFloor(7U));
    EXPECT_EQ(8U, symbolTable.getFloor(8U));
    EXPECT_EQ(8U, symbolTable.getFloor(9U));
}

TEST(OrderedArraySymbolTableTest, GetCeilingWorks)
{
    SymbolTableForTest symbolTable;
    symbolTable.put(4U, 'D');
    symbolTable.put(5U, 'E');
    symbolTable.put(7U, 'G');
    symbolTable.put(8U, 'H');

    EXPECT_EQ(4U, symbolTable.getCeiling(3U));
    EXPECT_EQ(4U, symbolTable.getCeiling(4U));
    EXPECT_EQ(5U, symbolTable.getCeiling(5U));
    EXPECT_EQ(7U, symbolTable.getCeiling(6U));
    EXPECT_EQ(7U, symbolTable.getCeiling(7U));
    EXPECT_EQ(8U, symbolTable.getCeiling(8U));
    EXPECT_EQ(0U, symbolTable.getCeiling(9U));
}

TEST(OrderedArraySymbolTableTest, PutWorks)
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

TEST(OrderedArraySymbolTableTest, DeleteBasedOnKeyWorks)
{
    SymbolTableForTest symbolTable;
    symbolTable.put(5U, 'E');
    symbolTable.put(6U, 'F');
    symbolTable.put(7U, 'G');

    symbolTable.deleteBasedOnKey(5U);
    EXPECT_EQ(2U, symbolTable.getSize());
    EXPECT_EQ('F', symbolTable.get(6U));
    EXPECT_EQ('G', symbolTable.get(7U));

    symbolTable.deleteBasedOnKey(6U);
    EXPECT_EQ(1U, symbolTable.getSize());
    EXPECT_EQ('G', symbolTable.get(7U));

    symbolTable.deleteBasedOnKey(7U);
    EXPECT_TRUE(symbolTable.isEmpty());
}

}
