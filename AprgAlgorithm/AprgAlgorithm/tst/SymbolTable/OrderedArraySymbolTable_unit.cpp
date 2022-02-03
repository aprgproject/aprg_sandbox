#include <SymbolTable/OrderedArraySymbolTable.hpp>
#include <SymbolTable/Utilities/CommonTestsWithBaseSymbolTable.hpp>

#include <gtest/gtest.h>

using namespace alba::CommonTestsWithBaseSymbolTable;
using namespace std;

namespace alba
{

namespace
{
using SymbolTableWithUnsignedIntToChar = OrderedArraySymbolTable<unsigned int, char>;
}

TEST(OrderedArraySymbolTableTest, IsEmptyWorksWhenEmpty)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performIsEmptyTestWhenEmpty(symbolTable);
}

TEST(OrderedArraySymbolTableTest, IsEmptyWorksWhenNotEmpty)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performIsEmptyTestWhenNotEmpty(symbolTable);
}

TEST(OrderedArraySymbolTableTest, DoesContainWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performDoesContainTest(symbolTable);
}

TEST(OrderedArraySymbolTableTest, GetSizeWorksWhenEmpty)
{
    SymbolTableWithUnsignedIntToChar symbolTable;    performGetSizeTestWhenEmpty(symbolTable);
}

TEST(OrderedArraySymbolTableTest, GetSizeWorksWhenNotEmpty){
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetSizeTestWhenNotEmpty(symbolTable);
}

TEST(OrderedArraySymbolTableTest, GetWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetTest(symbolTable);
}

TEST(OrderedArraySymbolTableTest, GetRankWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetRankTest(symbolTable);
}

TEST(OrderedArraySymbolTableTest, GetMinimumWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetMinimumTest(symbolTable);
}

TEST(OrderedArraySymbolTableTest, GetMaximumWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetMaximumTest(symbolTable);
}

TEST(OrderedArraySymbolTableTest, SelectAtWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performSelectAtTest(symbolTable);
}

TEST(OrderedArraySymbolTableTest, GetFloorWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetFloorTest(symbolTable);
}

TEST(OrderedArraySymbolTableTest, GetCeilingWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetCeilingTest(symbolTable);
}

TEST(OrderedArraySymbolTableTest, PutWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performPutTest(symbolTable);
}

TEST(OrderedArraySymbolTableTest, DeleteBasedOnKeyWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performDeleteBasedOnKeyTest(symbolTable);
}

TEST(OrderedArraySymbolTableTest, DeleteMinimumWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performDeleteMinimumTest(symbolTable);
}

TEST(OrderedArraySymbolTableTest, DeleteMaximumWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performDeleteMaximumTest(symbolTable);
}

TEST(OrderedArraySymbolTableTest, GetKeys)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetKeysTest(symbolTable);
}

TEST(OrderedArraySymbolTableTest, GetKeysInRangeWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetKeysInRangeInclusiveTest(symbolTable);
}

}
