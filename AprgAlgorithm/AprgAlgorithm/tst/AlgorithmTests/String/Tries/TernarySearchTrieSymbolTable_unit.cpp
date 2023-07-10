#include <Algorithm/String/Tries/TernarySearchTrieSymbolTable.hpp>
#include <AlgorithmTests/String/Tries/Utilities/CommonTestsWithTries.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithTries;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using TrieForTest = TernarySearchTrieSymbolTable<int>;
}

TEST(TernarySearchTrieSymbolTableTest, IsEmptyWorksWhenEmpty) { testIsEmptyWhenEmptyWithInt<TrieForTest>(); }

TEST(TernarySearchTrieSymbolTableTest, IsEmptyWorksWhenNotEmpty) { testIsEmptyWhenNotEmptyWithInt<TrieForTest>(); }

TEST(TernarySearchTrieSymbolTableTest, DoesContainWorks) { testDoesContainWithInt<TrieForTest>(); }

TEST(TernarySearchTrieSymbolTableTest, GetSizeWorksWhenEmpty) { testGetSizeWhenEmptyWithInt<TrieForTest>(); }

TEST(TernarySearchTrieSymbolTableTest, GetSizeWorksWhenNotEmpty) { testGetSizeWhenNotEmptyWithInt<TrieForTest>(); }

TEST(TernarySearchTrieSymbolTableTest, GetWorks) { testGetWithInt<TrieForTest>(); }

TEST(TernarySearchTrieSymbolTableTest, GetLongestPrefixWorks) { testGetLongestPrefixOfWithInt<TrieForTest>(); }

TEST(TernarySearchTrieSymbolTableTest, PutWorks) { testPutWithInt<TrieForTest>(); }

TEST(TernarySearchTrieSymbolTableTest, DeleteBasedOnKeyWorks) { testDeleteBasedOnKeyWithInt<TrieForTest>(); }

TEST(TernarySearchTrieSymbolTableTest, GetKeysWorks) { testGetKeysWithInt<TrieForTest>(); }

TEST(TernarySearchTrieSymbolTableTest, GetAllKeysWithPrefixWorks) { testGetAllKeysWithPrefixWithInt<TrieForTest>(); }

TEST(TernarySearchTrieSymbolTableTest, GetAllKeysThatMatchWorks) { testGetAllKeysThatMatchWithInt<TrieForTest>(); }

TEST(TernarySearchTrieSymbolTableTest, Example1Works) { testExample1WithInt<TrieForTest>(); }

TEST(TernarySearchTrieSymbolTableTest, GetNumberOfNodesWorksWhenEmpty) {
    TrieForTest trie;

    EXPECT_EQ(0, trie.getNumberOfNodes());
}

TEST(TernarySearchTrieSymbolTableTest, GetNumberOfNodesWorksWhenNotEmpty) {
    TrieForTest trie;
    trie.put("she", 0);
    trie.put("sells", 1);
    trie.put("sea", 2);

    EXPECT_EQ(8, trie.getNumberOfNodes());
}

TEST(TernarySearchTrieSymbolTableTest, PutWorksWithNumberOfNodes) {
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

TEST(TernarySearchTrieSymbolTableTest, PutWhenEmptyStringHasNoEffect) {
    TrieForTest trie;

    trie.put("", 17);

    EXPECT_EQ(0, trie.getSize());
    EXPECT_EQ(0, trie.getNumberOfNodes());
    EXPECT_EQ(0, trie.get(""));
}

TEST(TernarySearchTrieSymbolTableTest, DeleteBasedOnKeyWorksWithNumberOfNodes) {
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

TEST(TernarySearchTrieSymbolTableTest, DeleteBasedOnKeyWhenEmptyStringHasNoEffect) {
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
