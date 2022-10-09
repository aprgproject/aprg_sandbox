#include <Algorithm/String/Tries/RWayTrieUsingLinkedArrays.hpp>
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
using TrieForTest = RWayTrieUsingLinkedArrays<unsigned int>;
}

TEST(RWayTrieUsingLinkedArraysTest, IsEmptyWorksWhenEmpty)
{
    testIsEmptyWhenEmptyWithUnsignedInt<TrieForTest>();
}

TEST(RWayTrieUsingLinkedArraysTest, IsEmptyWorksWhenNotEmpty)
{
    testIsEmptyWhenNotEmptyWithUnsignedInt<TrieForTest>();
}

TEST(RWayTrieUsingLinkedArraysTest, DoesContainWorks)
{
    testDoesContainWithUnsignedInt<TrieForTest>();
}

TEST(RWayTrieUsingLinkedArraysTest, GetSizeWorksWhenEmpty)
{
    testGetSizeWhenEmptyWithUnsignedInt<TrieForTest>();
}

TEST(RWayTrieUsingLinkedArraysTest, GetSizeWorksWhenNotEmpty)
{
    testGetSizeWhenNotEmptyWithUnsignedInt<TrieForTest>();
}

TEST(RWayTrieUsingLinkedArraysTest, GetWorks)
{
    testGetWithUnsignedInt<TrieForTest>();
}

TEST(RWayTrieUsingLinkedArraysTest, GetLongestPrefixWorks)
{
    testGetLongestPrefixOfWithUnsignedInt<TrieForTest>();
}

TEST(RWayTrieUsingLinkedArraysTest, PutWorks)
{
    testPutWithUnsignedInt<TrieForTest>();
}

TEST(RWayTrieUsingLinkedArraysTest, DeleteBasedOnKeyWorks)
{
    testDeleteBasedOnKeyWithUnsignedInt<TrieForTest>();
}

TEST(RWayTrieUsingLinkedArraysTest, GetKeysWorks)
{
    testGetKeysWithUnsignedInt<TrieForTest>();
}

TEST(RWayTrieUsingLinkedArraysTest, GetAllKeysWithPrefixWorks)
{
    testGetAllKeysWithPrefixWithUnsignedInt<TrieForTest>();
}

TEST(RWayTrieUsingLinkedArraysTest, GetAllKeysThatMatchWorks)
{
    testGetAllKeysThatMatchWithUnsignedInt<TrieForTest>();
}

TEST(RWayTrieUsingLinkedArraysTest, Example1Works)
{
    testExample1WithUnsignedInt<TrieForTest>();
}

TEST(RWayTrieUsingLinkedArraysTest, GetWhenEmptyStringWorks)
{
    TrieForTest trie;
    EXPECT_EQ(0U, trie.get(""));

    trie.put("", 17U);    EXPECT_EQ(17U, trie.get(""));
}

TEST(RWayTrieUsingLinkedArraysTest, GetNumberOfNodesWorksWhenEmpty)
{
    TrieForTest trie;

    EXPECT_EQ(0U, trie.getNumberOfNodes());
}

TEST(RWayTrieUsingLinkedArraysTest, GetNumberOfNodesWorksWhenNotEmpty)
{
    TrieForTest trie;
    trie.put("she", 0U);
    trie.put("sells", 1U);
    trie.put("sea", 2U);

    // 9 nodes:
    // 1) s
    // 2) eh (child of s)
    // 3) e (child of h)
    // 4) al (child of first e)
    // 5) l (child of first l)
    // 6) s (child of second l)
    // 7) 0-value (child of "she" path)
    // 8) 1-value (child of "sells" path)
    // 9) 2-value (child of "sea" path)
    EXPECT_EQ(9U, trie.getNumberOfNodes());
}

TEST(RWayTrieUsingLinkedArraysTest, PutWorksWithNumberOfNodes)
{
    TrieForTest trie;

    trie.put("she", 0U);
    trie.put("sells", 1U);
    trie.put("sea", 2U);

    EXPECT_EQ(3U, trie.getSize());
    EXPECT_EQ(9U, trie.getNumberOfNodes());
    EXPECT_EQ(0U, trie.get("she"));
    EXPECT_EQ(1U, trie.get("sells"));
    EXPECT_EQ(2U, trie.get("sea"));
}

TEST(RWayTrieUsingLinkedArraysTest, PutWhenEmptyStringWorks)
{
    TrieForTest trie;

    trie.put("", 17U);

    EXPECT_EQ(1U, trie.getSize());
    EXPECT_EQ(1U, trie.getNumberOfNodes());
    EXPECT_EQ(17U, trie.get(""));
}

TEST(RWayTrieUsingLinkedArraysTest, DeleteBasedOnKeyWorksWithNumberOfNodes)
{
    TrieForTest trie;
    trie.put("she", 0U);
    trie.put("sells", 1U);
    trie.put("sea", 2U);

    trie.deleteBasedOnKey("she");
    EXPECT_EQ(2U, trie.getSize());
    EXPECT_EQ(7U, trie.getNumberOfNodes());
    EXPECT_EQ(1U, trie.get("sells"));
    EXPECT_EQ(2U, trie.get("sea"));

    trie.deleteBasedOnKey("sells");
    EXPECT_EQ(1U, trie.getSize());
    EXPECT_EQ(4U, trie.getNumberOfNodes());
    EXPECT_EQ(2U, trie.get("sea"));

    trie.deleteBasedOnKey("sea");
    EXPECT_TRUE(trie.isEmpty());
    EXPECT_EQ(0U, trie.getNumberOfNodes());
}

TEST(RWayTrieUsingLinkedArraysTest, DeleteBasedOnKeyWhenEmptyStringWorks)
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
