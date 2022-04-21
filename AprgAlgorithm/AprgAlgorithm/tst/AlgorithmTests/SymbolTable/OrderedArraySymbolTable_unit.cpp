#include <Algorithm/SymbolTable/OrderedArraySymbolTable.hpp>
#include <AlgorithmTests/SymbolTable/Utilities/CommonTestsWithSymbolTable.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSymbolTable;
using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using SymbolTableForTest = OrderedArraySymbolTable<unsigned int, char>;
}

TEST(OrderedArraySymbolTableTest, IsEmptyWorksWhenEmpty)
{
    testIsEmptyWhenEmptyWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(OrderedArraySymbolTableTest, IsEmptyWorksWhenNotEmpty)
{
    testIsEmptyWhenNotEmptyWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(OrderedArraySymbolTableTest, DoesContainWorks)
{
    testDoesContainWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(OrderedArraySymbolTableTest, GetSizeWorksWhenEmpty)
{
    testGetSizeWhenEmptyWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(OrderedArraySymbolTableTest, GetSizeWorksWhenNotEmpty)
{
    testGetSizeWhenNotEmptyWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(OrderedArraySymbolTableTest, GetWorks)
{
    testGetWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(OrderedArraySymbolTableTest, GetRankWorks)
{
    testGetRankWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(OrderedArraySymbolTableTest, GetMinimumWorks)
{
    testGetMinimumWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(OrderedArraySymbolTableTest, GetMaximumWorks)
{
    testGetMaximumWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(OrderedArraySymbolTableTest, SelectAtWorks)
{
    testSelectAtWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(OrderedArraySymbolTableTest, GetFloorWorks)
{
    testGetFloorWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(OrderedArraySymbolTableTest, GetCeilingWorks)
{
    testGetCeilingWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(OrderedArraySymbolTableTest, PutWorks)
{
    testPutWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(OrderedArraySymbolTableTest, DeleteBasedOnKeyWorks)
{
    testDeleteBasedOnKeyWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(OrderedArraySymbolTableTest, DeleteMinimumWorks)
{
    testDeleteMinimumWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(OrderedArraySymbolTableTest, DeleteMaximumWorks)
{
    testDeleteMaximumWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(OrderedArraySymbolTableTest, GetKeys)
{
    testGetKeysWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(OrderedArraySymbolTableTest, GetKeysInRangeWorks)
{
    testGetKeysInRangeInclusiveWithUnsignedIntAndChar<SymbolTableForTest>();
}

}

}
