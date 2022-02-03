#include <SymbolTable/BinarySearchTree/RedBlackBinarySearchTreeSymbolTable.hpp>
#include <SymbolTable/Utilities/CommonTestsWithBaseSymbolTable.hpp>

#include <gtest/gtest.h>

#include <vector>

using namespace alba::CommonTestsWithBaseSymbolTable;
using namespace std;


namespace alba
{

namespace
{
using SymbolTableWithUnsignedIntToChar = RedBlackBinarySearchTreeSymbolTable<unsigned int, char>;
}

TEST(RedBlackBinarySearchTreeSymbolTableTest, IsEmptyWorksWhenEmpty)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performIsEmptyTestWhenEmpty(symbolTable);
}

TEST(RedBlackBinarySearchTreeSymbolTableTest, IsEmptyWorksWhenNotEmpty)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performIsEmptyTestWhenNotEmpty(symbolTable);
}

TEST(RedBlackBinarySearchTreeSymbolTableTest, GetSizeWorksWhenEmpty)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetSizeTestWhenEmpty(symbolTable);
}

TEST(RedBlackBinarySearchTreeSymbolTableTest, GetSizeWorksWhenNotEmpty)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetSizeTestWhenNotEmpty(symbolTable);
}

TEST(RedBlackBinarySearchTreeSymbolTableTest, GetWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetTest(symbolTable);
}

TEST(RedBlackBinarySearchTreeSymbolTableTest, GetRankWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetRankTest(symbolTable);
}

TEST(RedBlackBinarySearchTreeSymbolTableTest, GetMinimumWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetMinimumTest(symbolTable);
}

TEST(RedBlackBinarySearchTreeSymbolTableTest, GetMaximumWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetMaximumTest(symbolTable);
}

TEST(RedBlackBinarySearchTreeSymbolTableTest, SelectAtWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performSelectAtTest(symbolTable);
}

TEST(RedBlackBinarySearchTreeSymbolTableTest, GetFloorWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetFloorTest(symbolTable);
}

TEST(RedBlackBinarySearchTreeSymbolTableTest, GetCeilingWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetCeilingTest(symbolTable);
}

TEST(RedBlackBinarySearchTreeSymbolTableTest, PutWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performPutTest(symbolTable);
}

TEST(RedBlackBinarySearchTreeSymbolTableTest, DeleteBasedOnKeyWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performDeleteBasedOnKeyTest(symbolTable);
}

TEST(RedBlackBinarySearchTreeSymbolTableTest, DeleteMinimumWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performDeleteMinimumTest(symbolTable);
}

TEST(RedBlackBinarySearchTreeSymbolTableTest, DeleteMaximumWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performDeleteMaximumTest(symbolTable);
}

TEST(RedBlackBinarySearchTreeSymbolTableTest, GetKeys)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetKeysTest(symbolTable);
}

TEST(RedBlackBinarySearchTreeSymbolTableTest, GetKeysInRangeWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetKeysInRangeInclusiveTest(symbolTable);
}



}
