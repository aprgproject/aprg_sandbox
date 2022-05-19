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

TEST(TrieSymbolTableTest, DeleteBasedOnKeyWorks)
{
    testDeleteBasedOnKeyWithUnsignedInt<TrieForTest>();
}

TEST(TrieSymbolTableTest, GetKeysWorks)
{
    testGetKeysWithUnsignedInt<TrieForTest>();}

TEST(TrieSymbolTableTest, GetAllKeysWithPrefixWorks)
{
    testGetAllKeysWithPrefixWithUnsignedInt<TrieForTest>();
}

TEST(TrieSymbolTableTest, GetAllKeysThatMatchWorks)
{
    testGetAllKeysThatMatchWithUnsignedInt<TrieForTest>();
}

TEST(TrieSymbolTableTest, GetNumberOfNodesWorksWhenEmpty)
{
    TrieForTest trie;

    EXPECT_EQ(0U, trie.getNumberOfNodes());
}

TEST(TrieSymbolTableTest, GetNumberOfNodesWorksWhenNotEmpty)
{
    TrieForTest trie;
    trie.put("she", 0U);
    trie.put("sells", 1U);
    trie.put("sea", 2U);

    EXPECT_EQ(8U, trie.getNumberOfNodes());
}

TEST(TrieSymbolTableTest, PutWorksWithNumberOfNodes)
{
    TrieForTest trie;
    trie.put("she", 0U);
    trie.put("sells", 1U);
    trie.put("sea", 2U);

    EXPECT_EQ(3U, trie.getSize());
    EXPECT_EQ(8U, trie.getNumberOfNodes());
    EXPECT_EQ(0U, trie.get("she"));
    EXPECT_EQ(1U, trie.get("sells"));
    EXPECT_EQ(2U, trie.get("sea"));
}

TEST(TrieSymbolTableTest, PutWhenEmptyStringWorks)
{
    TrieForTest trie;
    trie.put("", 17U);

    EXPECT_EQ(1U, trie.getSize());
    EXPECT_EQ(1U, trie.getNumberOfNodes());
    EXPECT_EQ(17U, trie.get(""));
}

TEST(TrieSymbolTableTest, DeleteBasedOnKeyWorksWithNumberOfNodes)
{
    TrieForTest trie;
    trie.put("she", 0U);
    trie.put("sells", 1U);
    trie.put("sea", 2U);

    trie.deleteBasedOnKey("she");
    EXPECT_EQ(2U, trie.getSize());
    EXPECT_EQ(6U, trie.getNumberOfNodes());
    EXPECT_EQ(1U, trie.get("sells"));
    EXPECT_EQ(2U, trie.get("sea"));

    trie.deleteBasedOnKey("sells");
    EXPECT_EQ(1U, trie.getSize());
    EXPECT_EQ(3U, trie.getNumberOfNodes());
    EXPECT_EQ(2U, trie.get("sea"));

    trie.deleteBasedOnKey("sea");
    EXPECT_TRUE(trie.isEmpty());
    EXPECT_EQ(0U, trie.getNumberOfNodes());
}

TEST(TrieSymbolTableTest, DeleteBasedOnKeyWhenEmptyStringWorks)
{
    TrieForTest trie;
    trie.put("", 017U);

    trie.deleteBasedOnKey("");
    EXPECT_TRUE(trie.isEmpty());
    EXPECT_EQ(0U, trie.getNumberOfNodes());

    trie.deleteBasedOnKey("");
    EXPECT_TRUE(trie.isEmpty());
    EXPECT_EQ(0U, trie.getNumberOfNodes());
}

}

}