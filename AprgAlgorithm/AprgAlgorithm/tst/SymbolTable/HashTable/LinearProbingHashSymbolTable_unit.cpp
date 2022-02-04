#include <SymbolTable/HashTable/LinearProbingHashSymbolTable.hpp>
#include <SymbolTable/Utilities/CommonTestsWithBaseSymbolTable.hpp>

#include <gtest/gtest.h>

using namespace alba::CommonTestsWithBaseSymbolTable;
using namespace std;

namespace alba
{

namespace
{
using SymbolTableWithUnsignedIntToChar = LinearProbingHashSymbolTable<unsigned int, char>;
}

TEST(LinearProbingHashSymbolTableTest, IsEmptyWorksWhenEmpty)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performIsEmptyTestWhenEmpty(symbolTable);
}

TEST(LinearProbingHashSymbolTableTest, IsEmptyWorksWhenNotEmpty)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performIsEmptyTestWhenNotEmpty(symbolTable);
}

TEST(LinearProbingHashSymbolTableTest, DoesContainWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performDoesContainTest(symbolTable);
}

TEST(LinearProbingHashSymbolTableTest, GetSizeWorksWhenEmpty)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetSizeTestWhenEmpty(symbolTable);
}

TEST(LinearProbingHashSymbolTableTest, GetSizeWorksWhenNotEmpty)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetSizeTestWhenNotEmpty(symbolTable);
}

TEST(LinearProbingHashSymbolTableTest, GetWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetTest(symbolTable);
}

TEST(LinearProbingHashSymbolTableTest, GetRankWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetRankTest(symbolTable);
}

TEST(LinearProbingHashSymbolTableTest, GetMinimumWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetMinimumTest(symbolTable);
}

TEST(LinearProbingHashSymbolTableTest, GetMaximumWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetMaximumTest(symbolTable);
}

TEST(LinearProbingHashSymbolTableTest, SelectAtWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performSelectAtTest(symbolTable);
}

TEST(LinearProbingHashSymbolTableTest, GetFloorWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetFloorTest(symbolTable);
}

TEST(LinearProbingHashSymbolTableTest, GetCeilingWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetCeilingTest(symbolTable);
}

TEST(LinearProbingHashSymbolTableTest, PutWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performPutTest(symbolTable);
}

TEST(LinearProbingHashSymbolTableTest, DeleteBasedOnKeyWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performDeleteBasedOnKeyTest(symbolTable);
}

TEST(LinearProbingHashSymbolTableTest, DeleteMinimumWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performDeleteMinimumTest(symbolTable);
}

TEST(LinearProbingHashSymbolTableTest, DeleteMaximumWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performDeleteMaximumTest(symbolTable);
}

TEST(LinearProbingHashSymbolTableTest, GetKeys)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetKeysTest(symbolTable);
}

TEST(LinearProbingHashSymbolTableTest, GetKeysInRangeWorks)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    performGetKeysInRangeInclusiveTest(symbolTable);
}

TEST(LinearProbingHashSymbolTableTest, PutWorksWithDoublingHashTableSize)
{
    SymbolTableWithUnsignedIntToChar symbolTable;

    EXPECT_EQ(1U, symbolTable.getHashTableSize());

    symbolTable.put(8U, 'H');
    symbolTable.put(9U, 'I');
    EXPECT_EQ(4U, symbolTable.getHashTableSize());

    symbolTable.put(5U, 'E');
    EXPECT_EQ(8U, symbolTable.getHashTableSize());

    symbolTable.put(4U, 'D');
    symbolTable.put(7U, 'G');
    EXPECT_EQ(16U, symbolTable.getHashTableSize());

    symbolTable.put(3U, 'C');
    EXPECT_EQ(16U, symbolTable.getHashTableSize());
}

TEST(LinearProbingHashSymbolTableTest, DeleteBasedOnKeyWorksWithHalvingHashTableSize)
{
    SymbolTableWithUnsignedIntToChar symbolTable;
    symbolTable.put(8U, 'H');
    symbolTable.put(9U, 'I');
    symbolTable.put(5U, 'E');
    symbolTable.put(4U, 'D');
    symbolTable.put(7U, 'G');
    symbolTable.put(3U, 'C');

    EXPECT_EQ(16U, symbolTable.getHashTableSize());

    symbolTable.deleteBasedOnKey(3U);
    symbolTable.deleteBasedOnKey(4U);
    symbolTable.deleteBasedOnKey(5U);
    symbolTable.deleteBasedOnKey(7U);
    EXPECT_EQ(8U, symbolTable.getHashTableSize());

    symbolTable.deleteBasedOnKey(8U);
    EXPECT_EQ(4U, symbolTable.getHashTableSize());

    symbolTable.deleteBasedOnKey(9U);
    EXPECT_EQ(4U, symbolTable.getHashTableSize());

}

}
