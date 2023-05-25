#include <Algorithm/String/Tries/TernarySearchTrie.hpp>
#include <AlgorithmTests/String/Tries/Utilities/CommonTestsWithTries.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithTries;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using TrieForTest = TernarySearchTrie<int>;
}

TEST(TernarySearchTrieTest, IsEmptyWorksWhenEmpty) { testIsEmptyWhenEmptyWithInt<TrieForTest>(); }

TEST(TernarySearchTrieTest, IsEmptyWorksWhenNotEmpty) { testIsEmptyWhenNotEmptyWithInt<TrieForTest>(); }

TEST(TernarySearchTrieTest, DoesContainWorks) { testDoesContainWithInt<TrieForTest>(); }

TEST(TernarySearchTrieTest, GetSizeWorksWhenEmpty) { testGetSizeWhenEmptyWithInt<TrieForTest>(); }

TEST(TernarySearchTrieTest, GetSizeWorksWhenNotEmpty) { testGetSizeWhenNotEmptyWithInt<TrieForTest>(); }

TEST(TernarySearchTrieTest, GetWorks) { testGetWithInt<TrieForTest>(); }

TEST(TernarySearchTrieTest, GetLongestPrefixWorks) { testGetLongestPrefixOfWithInt<TrieForTest>(); }

TEST(TernarySearchTrieTest, PutWorks) { testPutWithInt<TrieForTest>(); }

TEST(TernarySearchTrieTest, DeleteBasedOnKeyWorks) { testDeleteBasedOnKeyWithInt<TrieForTest>(); }

TEST(TernarySearchTrieTest, GetKeysWorks) { testGetKeysWithInt<TrieForTest>(); }

TEST(TernarySearchTrieTest, GetAllKeysWithPrefixWorks) { testGetAllKeysWithPrefixWithInt<TrieForTest>(); }

TEST(TernarySearchTrieTest, GetAllKeysThatMatchWorks) { testGetAllKeysThatMatchWithInt<TrieForTest>(); }

TEST(TernarySearchTrieTest, Example1Works) { testExample1WithInt<TrieForTest>(); }

TEST(TernarySearchTrieTest, GetNumberOfNodesWorksWhenEmpty) {
    TrieForTest trie;

    EXPECT_EQ(0, trie.getNumberOfNodes());
}

TEST(TernarySearchTrieTest, GetNumberOfNodesWorksWhenNotEmpty) {
    TrieForTest trie;
    trie.put("she", 0);
    trie.put("sells", 1);
    trie.put("sea", 2);

    EXPECT_EQ(8, trie.getNumberOfNodes());
}

TEST(TernarySearchTrieTest, PutWorksWithNumberOfNodes) {
    TrieForTest trie;

    trie.put("she", 0);
    trie.put("sells", 1);
    trie.put("sea", 2);

    EXPECT_EQ(3, trie.getSize());
    EXPECT_EQ(8, trie.getNumberOfNodes());
    EXPECT_EQ(0, trie.get("she"));
    EXPECT_EQ(1, trie.get("sells"));
    EXPECT_EQ(2, trie.get("sea"));
}

TEST(TernarySearchTrieTest, PutWhenEmptyStringHasNoEffect) {
    TrieForTest trie;

    trie.put("", 17);

    EXPECT_EQ(0, trie.getSize());
    EXPECT_EQ(0, trie.getNumberOfNodes());
    EXPECT_EQ(0, trie.get(""));
}

TEST(TernarySearchTrieTest, DeleteBasedOnKeyWorksWithNumberOfNodes) {
    TrieForTest trie;
    trie.put("she", 0);
    trie.put("sells", 1);
    trie.put("sea", 2);

    trie.deleteBasedOnKey("she");
    EXPECT_EQ(2, trie.getSize());
    EXPECT_EQ(6, trie.getNumberOfNodes());
    EXPECT_EQ(1, trie.get("sells"));
    EXPECT_EQ(2, trie.get("sea"));

    trie.deleteBasedOnKey("sells");
    EXPECT_EQ(1, trie.getSize());
    EXPECT_EQ(3, trie.getNumberOfNodes());
    EXPECT_EQ(2, trie.get("sea"));

    trie.deleteBasedOnKey("sea");
    EXPECT_TRUE(trie.isEmpty());
    EXPECT_EQ(0, trie.getNumberOfNodes());
}

TEST(TernarySearchTrieTest, DeleteBasedOnKeyWhenEmptyStringHasNoEffect) {
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
