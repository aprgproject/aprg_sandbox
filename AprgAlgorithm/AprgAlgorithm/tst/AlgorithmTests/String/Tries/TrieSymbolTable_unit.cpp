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

TEST(TrieSymbolTableTest, GetWhenEmptyStringWorks)
{
    TrieForTest trie;

    EXPECT_EQ(0U, trie.get(""));

    trie.put("", 17U);
    EXPECT_EQ(17U, trie.get(""));
}

TEST(TrieSymbolTableTest, GetLongestPrefixWorks)
{
    testGetLongestPrefixOfWithUnsignedInt<TrieForTest>();
}

TEST(TrieSymbolTableTest, PutWorks)
{
    testPutWithUnsignedInt<TrieForTest>();
}

TEST(TrieSymbolTableTest, PutWhenEmptyStringWorks)
{
    TrieForTest trie;
    trie.put("", 17U);

    ASSERT_EQ(1U, trie.getSize());
    EXPECT_EQ(17U, trie.get(""));
}

TEST(TrieSymbolTableTest, DeleteBasedOnKeyWorks)
{
    testDeleteBasedOnKeyWithUnsignedInt<TrieForTest>();
}

TEST(TrieSymbolTableTest, DeleteBasedOnKeyWhenEmptyStringWorks)
{
    testDeleteBasedOnKeyWhenEmptyStringWithUnsignedInt<TrieForTest>();
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
