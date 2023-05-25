#include <Algorithm/String/Tries/RWayTrieUsingLinkedArrays.hpp>
#include <AlgorithmTests/String/Tries/Utilities/CommonTestsWithTries.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithTries;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using TrieForTest = RWayTrieUsingLinkedArrays<int>;
}

TEST(RWayTrieUsingLinkedArraysTest, IsEmptyWorksWhenEmpty) { testIsEmptyWhenEmptyWithInt<TrieForTest>(); }

TEST(RWayTrieUsingLinkedArraysTest, IsEmptyWorksWhenNotEmpty) { testIsEmptyWhenNotEmptyWithInt<TrieForTest>(); }

TEST(RWayTrieUsingLinkedArraysTest, DoesContainWorks) { testDoesContainWithInt<TrieForTest>(); }

TEST(RWayTrieUsingLinkedArraysTest, GetSizeWorksWhenEmpty) { testGetSizeWhenEmptyWithInt<TrieForTest>(); }

TEST(RWayTrieUsingLinkedArraysTest, GetSizeWorksWhenNotEmpty) { testGetSizeWhenNotEmptyWithInt<TrieForTest>(); }

TEST(RWayTrieUsingLinkedArraysTest, GetWorks) { testGetWithInt<TrieForTest>(); }

TEST(RWayTrieUsingLinkedArraysTest, GetLongestPrefixWorks) { testGetLongestPrefixOfWithInt<TrieForTest>(); }

TEST(RWayTrieUsingLinkedArraysTest, PutWorks) { testPutWithInt<TrieForTest>(); }

TEST(RWayTrieUsingLinkedArraysTest, DeleteBasedOnKeyWorks) { testDeleteBasedOnKeyWithInt<TrieForTest>(); }

TEST(RWayTrieUsingLinkedArraysTest, GetKeysWorks) { testGetKeysWithInt<TrieForTest>(); }

TEST(RWayTrieUsingLinkedArraysTest, GetAllKeysWithPrefixWorks) { testGetAllKeysWithPrefixWithInt<TrieForTest>(); }

TEST(RWayTrieUsingLinkedArraysTest, GetAllKeysThatMatchWorks) { testGetAllKeysThatMatchWithInt<TrieForTest>(); }

TEST(RWayTrieUsingLinkedArraysTest, Example1Works) { testExample1WithInt<TrieForTest>(); }

TEST(RWayTrieUsingLinkedArraysTest, GetWhenEmptyStringWorks) {
    TrieForTest trie;

    EXPECT_EQ(0, trie.get(""));

    trie.put("", 17);
    EXPECT_EQ(17, trie.get(""));
}

TEST(RWayTrieUsingLinkedArraysTest, GetNumberOfNodesWorksWhenEmpty) {
    TrieForTest trie;

    EXPECT_EQ(0, trie.getNumberOfNodes());
}

TEST(RWayTrieUsingLinkedArraysTest, GetNumberOfNodesWorksWhenNotEmpty) {
    TrieForTest trie;
    trie.put("she", 0);
    trie.put("sells", 1);
    trie.put("sea", 2);

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
    EXPECT_EQ(9, trie.getNumberOfNodes());
}

TEST(RWayTrieUsingLinkedArraysTest, PutWorksWithNumberOfNodes) {
    TrieForTest trie;

    trie.put("she", 0);
    trie.put("sells", 1);
    trie.put("sea", 2);

    EXPECT_EQ(3, trie.getSize());
    EXPECT_EQ(9, trie.getNumberOfNodes());
    EXPECT_EQ(0, trie.get("she"));
    EXPECT_EQ(1, trie.get("sells"));
    EXPECT_EQ(2, trie.get("sea"));
}

TEST(RWayTrieUsingLinkedArraysTest, PutWhenEmptyStringWorks) {
    TrieForTest trie;

    trie.put("", 17);

    EXPECT_EQ(1, trie.getSize());
    EXPECT_EQ(1, trie.getNumberOfNodes());
    EXPECT_EQ(17, trie.get(""));
}

TEST(RWayTrieUsingLinkedArraysTest, DeleteBasedOnKeyWorksWithNumberOfNodes) {
    TrieForTest trie;
    trie.put("she", 0);
    trie.put("sells", 1);
    trie.put("sea", 2);

    trie.deleteBasedOnKey("she");
    EXPECT_EQ(2, trie.getSize());
    EXPECT_EQ(7, trie.getNumberOfNodes());
    EXPECT_EQ(1, trie.get("sells"));
    EXPECT_EQ(2, trie.get("sea"));

    trie.deleteBasedOnKey("sells");
    EXPECT_EQ(1, trie.getSize());
    EXPECT_EQ(4, trie.getNumberOfNodes());
    EXPECT_EQ(2, trie.get("sea"));

    trie.deleteBasedOnKey("sea");
    EXPECT_TRUE(trie.isEmpty());
    EXPECT_EQ(0, trie.getNumberOfNodes());
}

TEST(RWayTrieUsingLinkedArraysTest, DeleteBasedOnKeyWhenEmptyStringWorks) {
    TrieForTest trie;
    trie.put("", 17);

    trie.deleteBasedOnKey("");
    EXPECT_TRUE(trie.isEmpty());
    EXPECT_EQ(0, trie.getNumberOfNodes());

    trie.deleteBasedOnKey("");
    EXPECT_TRUE(trie.isEmpty());
    EXPECT_EQ(0, trie.getNumberOfNodes());
}

}  // namespace algorithm

}  // namespace alba
