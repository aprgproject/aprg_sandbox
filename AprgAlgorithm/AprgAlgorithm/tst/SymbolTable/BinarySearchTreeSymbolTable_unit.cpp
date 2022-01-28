#include <SymbolTable/BinarySearchTreeSymbolTable.hpp>
#include <SymbolTable/Utilities/CommonTestsWithBaseSymbolTable.hpp>

#include <gtest/gtest.h>

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

}
