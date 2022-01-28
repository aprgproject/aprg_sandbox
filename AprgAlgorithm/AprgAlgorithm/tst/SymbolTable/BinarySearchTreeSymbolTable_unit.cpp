#include <SymbolTable/BinarySearchTreeSymbolTable.hpp>
#include <SymbolTable/Utilities/CommonTestsWithBaseSymbolTable.hpp>

#include <gtest/gtest.h>

#include <vector>

using namespace alba::CommonTestsWithBaseSymbolTable;
using namespace std;

namespace alba
{

namespace
{
using SymbolTableWithUnsignedIntToChar = BinarySearchTreeSymbolTable<unsigned int, char>;
}

TEST(BinarySearchTreeSymbolTableTest, IsEmptyWorksWhenEmpty)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performIsEmptyTestWhenEmpty(symbolTable);
}

TEST(BinarySearchTreeSymbolTableTest, IsEmptyWorksWhenNotEmpty)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performIsEmptyTestWhenNotEmpty(symbolTable);
}

TEST(BinarySearchTreeSymbolTableTest, GetSizeWorksWhenEmpty)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetSizeTestWhenEmpty(symbolTable);
}

TEST(BinarySearchTreeSymbolTableTest, GetSizeWorksWhenNotEmpty)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetSizeTestWhenNotEmpty(symbolTable);
}

TEST(BinarySearchTreeSymbolTableTest, GetWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetTest(symbolTable);
}

TEST(BinarySearchTreeSymbolTableTest, GetRankWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetRankTest(symbolTable);
}

TEST(BinarySearchTreeSymbolTableTest, GetMinimumWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetMinimumTest(symbolTable);
}

TEST(BinarySearchTreeSymbolTableTest, GetMaximumWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetMaximumTest(symbolTable);
}

TEST(BinarySearchTreeSymbolTableTest, SelectAtWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performSelectAtTest(symbolTable);
}

TEST(BinarySearchTreeSymbolTableTest, GetFloorWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetFloorTest(symbolTable);
}

TEST(BinarySearchTreeSymbolTableTest, GetCeilingWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetCeilingTest(symbolTable);
}

TEST(BinarySearchTreeSymbolTableTest, PutWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performPutTest(symbolTable);
}

TEST(BinarySearchTreeSymbolTableTest, DeleteBasedOnKeyWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performDeleteBasedOnKeyTest(symbolTable);
}

TEST(BinarySearchTreeSymbolTableTest, DeleteMinimumWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performDeleteMinimumTest(symbolTable);
}

TEST(BinarySearchTreeSymbolTableTest, DeleteMaximumWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performDeleteMaximumTest(symbolTable);
}

TEST(BinarySearchTreeSymbolTableTest, RetrieveKeysInRangeWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    vector<unsigned int> keys;
    symbolTable.put(8U, 'H');
    symbolTable.put(9U, 'I');
    symbolTable.put(5U, 'E');
    symbolTable.put(4U, 'D');
    symbolTable.put(7U, 'G');
    symbolTable.put(3U, 'C');

    symbolTable.retrieveKeysInRangeInclusive(keys, 5U, 8U);

    vector<unsigned int> expectedKeys{5U, 7U, 8U};
    EXPECT_EQ(expectedKeys, keys);
}


}
