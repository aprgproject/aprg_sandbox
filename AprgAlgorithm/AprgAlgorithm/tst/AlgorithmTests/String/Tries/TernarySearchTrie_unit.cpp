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
    testGetLongestPrefixOfWithUnsignedInt<TrieForTest>();
}

TEST(TernarySearchTrieTest, PutWorks)
{
    testPutWithUnsignedInt<TrieForTest>();
}

TEST(TernarySearchTrieTest, DeleteBasedOnKeyWorks)
{
    testDeleteBasedOnKeyWithUnsignedInt<TrieForTest>();
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

TEST(TernarySearchTrieTest, Example1Works)
{
    testExample1WithUnsignedInt<TrieForTest>();
}

TEST(TernarySearchTrieTest, GetNumberOfNodesWorksWhenEmpty)
{
    TrieForTest trie;
    EXPECT_EQ(0U, trie.getNumberOfNodes());
}
TEST(TernarySearchTrieTest, GetNumberOfNodesWorksWhenNotEmpty)
{
    TrieForTest trie;
    trie.put("she", 0U);
    trie.put("sells", 1U);
    trie.put("sea", 2U);

    EXPECT_EQ(8U, trie.getNumberOfNodes());
}

TEST(TernarySearchTrieTest, PutWorksWithNumberOfNodes)
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

TEST(TernarySearchTrieTest, PutWhenEmptyStringHasNoEffect)
{
    TrieForTest trie;

    trie.put("", 17U);

    EXPECT_EQ(0U, trie.getSize());
    EXPECT_EQ(0U, trie.getNumberOfNodes());
    EXPECT_EQ(0U, trie.get(""));
}

TEST(TernarySearchTrieTest, DeleteBasedOnKeyWorksWithNumberOfNodes)
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

TEST(TernarySearchTrieTest, DeleteBasedOnKeyWhenEmptyStringHasNoEffect)
{
    TrieForTest trie;
    trie.put("", 17U);

    trie.deleteBasedOnKey("");
    EXPECT_TRUE(trie.isEmpty());
    EXPECT_EQ(0U, trie.getNumberOfNodes());

    trie.deleteBasedOnKey("");
    EXPECT_TRUE(trie.isEmpty());
    EXPECT_EQ(0U, trie.getNumberOfNodes());
}

}

}
