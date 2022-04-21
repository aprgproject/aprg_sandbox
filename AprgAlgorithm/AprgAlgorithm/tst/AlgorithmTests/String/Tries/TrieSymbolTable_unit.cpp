#include <Algorithm/String/Tries/TrieSymbolTable.hpp>
#include <AlgorithmTests/String/Tries/Utilities/CommonTestsWithTries.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithTries;
using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using TrieForTest = TrieSymbolTable<unsigned int>;
}

TEST(TrieSymbolTableTest, IsEmptyWorksWhenEmpty)
{
    testIsEmptyWhenEmptyWithUnsignedInt<TrieForTest>();
}

TEST(TrieSymbolTableTest, IsEmptyWorksWhenNotEmpty)
{
    testIsEmptyWhenNotEmptyWithUnsignedInt<TrieForTest>();
}

TEST(TrieSymbolTableTest, DoesContainWorks)
{
    testDoesContainWithUnsignedInt<TrieForTest>();
}

TEST(TrieSymbolTableTest, GetSizeWorksWhenEmpty)
{
    testGetSizeWhenEmptyWithUnsignedInt<TrieForTest>();
}

TEST(TrieSymbolTableTest, GetSizeWorksWhenNotEmpty)
{
    testGetSizeWhenNotEmptyWithUnsignedInt<TrieForTest>();
}

TEST(TrieSymbolTableTest, GetWorks)
{
    testGetWithUnsignedInt<TrieForTest>();
}

TEST(TrieSymbolTableTest, GetLongestPrefixWorks)
{
    testGetLongestPrefixOfWithUnsignedInt<TrieForTest>();
}

TEST(TrieSymbolTableTest, PutWorks)
{
    testPutWithUnsignedInt<TrieForTest>();
}

TEST(TrieSymbolTableTest, DeleteBasedOnKeyWorks)
{
    testDeleteBasedOnKeyWithUnsignedInt<TrieForTest>();
}

TEST(TrieSymbolTableTest, GetKeysWorks)
{
    testGetKeysWithUnsignedInt<TrieForTest>();
}

TEST(TrieSymbolTableTest, GetAllKeysWithPrefixWorks)
{
    testGetAllKeysWithPrefixWithUnsignedInt<TrieForTest>();
}

TEST(TrieSymbolTableTest, GetAllKeysThatMatchWorks)
{
    testGetAllKeysThatMatchWithUnsignedInt<TrieForTest>();
}

}

}
