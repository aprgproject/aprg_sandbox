#include <SymbolTable/LinkedListSymbolTable.hpp>
#include <SymbolTable/Utilities/CommonTestsWithBaseSymbolTable.hpp>

#include <gtest/gtest.h>

using namespace alba::CommonTestsWithBaseSymbolTable;
using namespace std;


namespace alba
{

namespace
{
using SymbolTableWithUnsignedIntToChar = LinkedListSymbolTable<unsigned int, char>;
}

TEST(LinkedListSymbolTableTest, IsEmptyWorksWhenEmpty)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performIsEmptyTestWhenEmpty(symbolTable);
}

TEST(LinkedListSymbolTableTest, IsEmptyWorksWhenNotEmpty)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performIsEmptyTestWhenNotEmpty(symbolTable);
}

TEST(LinkedListSymbolTableTest, GetSizeWorksWhenEmpty)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetSizeTestWhenEmpty(symbolTable);
}

TEST(LinkedListSymbolTableTest, GetSizeWorksWhenNotEmpty)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetSizeTestWhenNotEmpty(symbolTable);
}

TEST(LinkedListSymbolTableTest, GetWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetTest(symbolTable);
}

TEST(LinkedListSymbolTableTest, GetRankWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetRankTest(symbolTable);
}

TEST(LinkedListSymbolTableTest, GetMinimumWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetMinimumTest(symbolTable);
}

TEST(LinkedListSymbolTableTest, GetMaximumWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetMaximumTest(symbolTable);
}

TEST(LinkedListSymbolTableTest, SelectAtWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performSelectAtTest(symbolTable);
}

TEST(LinkedListSymbolTableTest, GetFloorWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetFloorTest(symbolTable);
}

TEST(LinkedListSymbolTableTest, GetCeilingWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetCeilingTest(symbolTable);
}

TEST(LinkedListSymbolTableTest, PutWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performPutTest(symbolTable);
}

}
