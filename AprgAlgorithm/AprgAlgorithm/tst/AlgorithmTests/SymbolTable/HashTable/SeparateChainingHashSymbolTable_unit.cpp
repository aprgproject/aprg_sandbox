#include <Algorithm/SymbolTable/HashTable/SeparateChainingHashSymbolTable.hpp>
#include <AlgorithmTests/SymbolTable/Utilities/CommonTestsWithSymbolTable.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSymbolTable;
using namespace std;

namespace alba{

namespace algorithm
{

namespace
{
using SymbolTableForTest = SeparateChainingHashSymbolTable<unsigned int, char, 2>;
}

TEST(SeparateChainingHashSymbolTableTest, IsEmptyWorksWhenEmpty)
{
    testIsEmptyWhenEmptyWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(SeparateChainingHashSymbolTableTest, IsEmptyWorksWhenNotEmpty)
{
    testIsEmptyWhenNotEmptyWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(SeparateChainingHashSymbolTableTest, DoesContainWorks)
{
    testDoesContainWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(SeparateChainingHashSymbolTableTest, GetSizeWorksWhenEmpty)
{
    testGetSizeWhenEmptyWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(SeparateChainingHashSymbolTableTest, GetSizeWorksWhenNotEmpty)
{
    testGetSizeWhenNotEmptyWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(SeparateChainingHashSymbolTableTest, GetWorks)
{
    testGetWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(SeparateChainingHashSymbolTableTest, GetRankWorks)
{
    testGetRankWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(SeparateChainingHashSymbolTableTest, GetMinimumWorks)
{
    testGetMinimumWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(SeparateChainingHashSymbolTableTest, GetMaximumWorks)
{
    testGetMaximumWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(SeparateChainingHashSymbolTableTest, SelectAtWorks)
{
    testSelectAtWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(SeparateChainingHashSymbolTableTest, GetFloorWorks)
{
    testGetFloorWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(SeparateChainingHashSymbolTableTest, GetCeilingWorks)
{
    testGetCeilingWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(SeparateChainingHashSymbolTableTest, PutWorks)
{
    testPutWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(SeparateChainingHashSymbolTableTest, DeleteBasedOnKeyWorks)
{
    testDeleteBasedOnKeyWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(SeparateChainingHashSymbolTableTest, DeleteMinimumWorks)
{
    testDeleteMinimumWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(SeparateChainingHashSymbolTableTest, DeleteMaximumWorks)
{
    testDeleteMaximumWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(SeparateChainingHashSymbolTableTest, GetKeys)
{
    testGetKeysWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(SeparateChainingHashSymbolTableTest, GetKeysInRangeWorks)
{
    testGetKeysInRangeInclusiveWithUnsignedIntAndChar<SymbolTableForTest>();
}

}
}