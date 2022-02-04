#include <SymbolTable/UnorderedLinkedListSymbolTable.hpp>
#include <SymbolTable/Utilities/CommonTestsWithBaseSymbolTable.hpp>

#include <gtest/gtest.h>

using namespace alba::CommonTestsWithBaseSymbolTable;
using namespace std;


namespace alba
{

namespace
{
using SymbolTableWithUnsignedIntToChar = UnorderedLinkedListSymbolTable<unsigned int, char>;
}

TEST(UnorderedLinkedListSymbolTableTest, IsEmptyWorksWhenEmpty)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performIsEmptyTestWhenEmpty(symbolTable);
}

TEST(UnorderedLinkedListSymbolTableTest, IsEmptyWorksWhenNotEmpty)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performIsEmptyTestWhenNotEmpty(symbolTable);
}

TEST(UnorderedLinkedListSymbolTableTest, DoesContainWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performDoesContainTest(symbolTable);
}

TEST(UnorderedLinkedListSymbolTableTest, GetSizeWorksWhenEmpty)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetSizeTestWhenEmpty(symbolTable);
}

TEST(UnorderedLinkedListSymbolTableTest, GetSizeWorksWhenNotEmpty)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetSizeTestWhenNotEmpty(symbolTable);
}

TEST(UnorderedLinkedListSymbolTableTest, GetWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetTest(symbolTable);
}

TEST(UnorderedLinkedListSymbolTableTest, GetRankWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetRankTest(symbolTable);
}

TEST(UnorderedLinkedListSymbolTableTest, GetMinimumWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetMinimumTest(symbolTable);
}

TEST(UnorderedLinkedListSymbolTableTest, GetMaximumWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetMaximumTest(symbolTable);
}

TEST(UnorderedLinkedListSymbolTableTest, SelectAtWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performSelectAtTest(symbolTable);
}

TEST(UnorderedLinkedListSymbolTableTest, GetFloorWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetFloorTest(symbolTable);
}

TEST(UnorderedLinkedListSymbolTableTest, GetCeilingWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetCeilingTest(symbolTable);
}

TEST(UnorderedLinkedListSymbolTableTest, PutWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performPutTest(symbolTable);
}

TEST(UnorderedLinkedListSymbolTableTest, DeleteBasedOnKeyWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performDeleteBasedOnKeyTest(symbolTable);
}

TEST(UnorderedLinkedListSymbolTableTest, DeleteMinimumWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performDeleteMinimumTest(symbolTable);
}

TEST(UnorderedLinkedListSymbolTableTest, DeleteMaximumWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performDeleteMaximumTest(symbolTable);
}

TEST(UnorderedLinkedListSymbolTableTest, GetKeys)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetKeysTest(symbolTable);
}

TEST(UnorderedLinkedListSymbolTableTest, GetKeysInRangeWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetKeysInRangeInclusiveTest(symbolTable);
}

}
