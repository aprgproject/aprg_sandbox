#include <Algorithm/String/Tries/TernarySearchTrie.hpp>
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
using TrieForTest = TernarySearchTrie<unsigned int>;
}

TEST(TernarySearchTrieTest, IsEmptyWorksWhenEmpty)
{
    testIsEmptyWhenEmptyWithUnsignedInt<TrieForTest>();
}

TEST(TernarySearchTrieTest, IsEmptyWorksWhenNotEmpty)
{
    testIsEmptyWhenNotEmptyWithUnsignedInt<TrieForTest>();
}

TEST(TernarySearchTrieTest, DoesContainWorks)
{
    testDoesContainWithUnsignedInt<TrieForTest>();
}

TEST(TernarySearchTrieTest, GetSizeWorksWhenEmpty)
{
    testGetSizeWhenEmptyWithUnsignedInt<TrieForTest>();
}

TEST(TernarySearchTrieTest, GetSizeWorksWhenNotEmpty)
{
    testGetSizeWhenNotEmptyWithUnsignedInt<TrieForTest>();
}

TEST(TernarySearchTrieTest, GetWorks)
{
    testGetWithUnsignedInt<TrieForTest>();
}

TEST(TernarySearchTrieTest, GetLongestPrefixWorks)
{
    TrieForTest trie;

    EXPECT_EQ(0U, trie.get(""));

    trie.put("", 17U);
    EXPECT_EQ(0U, trie.get(""));
}

TEST(TernarySearchTrieTest, PutWorks)
{
    testPutWithUnsignedInt<TrieForTest>();
}

TEST(TernarySearchTrieTest, PutWhenEmptyStringWorks)
{
    TrieForTest trie;
    trie.put("", 17U);

    EXPECT_EQ(0U, trie.getSize());
    EXPECT_EQ(0U, trie.get(""));
}

TEST(TernarySearchTrieTest, DeleteBasedOnKeyWorks)
{
    testDeleteBasedOnKeyWithUnsignedInt<TrieForTest>();
}

TEST(TernarySearchTrieTest, DeleteBasedOnKeyWhenEmptyStringWorks)
{
    testDeleteBasedOnKeyWhenEmptyStringWithUnsignedInt<TrieForTest>();
}

TEST(TernarySearchTrieTest, GetKeysWorks)
{
    testGetKeysWithUnsignedInt<TrieForTest>();
}

TEST(TernarySearchTrieTest, GetAllKeysWithPrefixWorks)
{
    testGetAllKeysWithPrefixWithUnsignedInt<TrieForTest>();
}

TEST(TernarySearchTrieTest, GetAllKeysThatMatchWorks)
{
    testGetAllKeysThatMatchWithUnsignedInt<TrieForTest>();
}

}

}
