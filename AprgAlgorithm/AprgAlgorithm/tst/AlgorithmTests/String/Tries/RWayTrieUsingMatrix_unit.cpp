#include <Algorithm/String/Tries/RWayTrieUsingMatrix.hpp>
#include <AlgorithmTests/String/Tries/Utilities/CommonTestsWithTries.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithTries;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using TrieForTest = RWayTrieUsingMatrix<int, 50>;
}

TEST(RWayTrieUsingMatrixTest, IsEmptyWorksWhenEmpty) { testIsEmptyWhenEmptyWithInt<TrieForTest>(); }

TEST(RWayTrieUsingMatrixTest, IsEmptyWorksWhenNotEmpty) { testIsEmptyWhenNotEmptyWithInt<TrieForTest>(); }

TEST(RWayTrieUsingMatrixTest, DoesContainWorks) { testDoesContainWithInt<TrieForTest>(); }

TEST(RWayTrieUsingMatrixTest, GetSizeWorksWhenEmpty) { testGetSizeWhenEmptyWithInt<TrieForTest>(); }

TEST(RWayTrieUsingMatrixTest, GetSizeWorksWhenNotEmpty) { testGetSizeWhenNotEmptyWithInt<TrieForTest>(); }

TEST(RWayTrieUsingMatrixTest, GetWorks) { testGetWithInt<TrieForTest>(); }

TEST(RWayTrieUsingMatrixTest, GetLongestPrefixWorks) { testGetLongestPrefixOfWithInt<TrieForTest>(); }

TEST(RWayTrieUsingMatrixTest, PutWorks) { testPutWithInt<TrieForTest>(); }

TEST(RWayTrieUsingMatrixTest, DeleteBasedOnKeyWorks) { testDeleteBasedOnKeyWithInt<TrieForTest>(); }

TEST(RWayTrieUsingMatrixTest, GetKeysWorks) { testGetKeysWithInt<TrieForTest>(); }

TEST(RWayTrieUsingMatrixTest, GetAllKeysWithPrefixWorks) { testGetAllKeysWithPrefixWithInt<TrieForTest>(); }

TEST(RWayTrieUsingMatrixTest, GetAllKeysThatMatchWorks) { testGetAllKeysThatMatchWithInt<TrieForTest>(); }

TEST(RWayTrieUsingMatrixTest, Example1Works) { testExample1WithInt<TrieForTest>(); }

TEST(RWayTrieUsingMatrixTest, PutWhenEmptyStringHasNoEffect) {
    TrieForTest trie;

    trie.put("", 17);

    EXPECT_EQ(0, trie.getSize());
    EXPECT_EQ(0, trie.get(""));
}

TEST(RWayTrieUsingMatrixTest, DeleteBasedOnKeyWhenEmptyStringWorks) {
    TrieForTest trie;
    trie.put("", 17);

    trie.deleteBasedOnKey("");
    EXPECT_TRUE(trie.isEmpty());

    trie.deleteBasedOnKey("");
    EXPECT_TRUE(trie.isEmpty());
}

TEST(RWayTrieUsingMatrixTest, PutDeleteAlternatelyWorks) {
    TrieForTest trie;
    trie.put("she", 0);

    trie.put("sells", 1);
    trie.put("sea", 2);

    trie.deleteBasedOnKey("she");
    EXPECT_EQ((TrieForTest::SetOfNodeIds{2}), trie.getUnusedNodeIds());

    trie.deleteBasedOnKey("sells");
    EXPECT_EQ((TrieForTest::SetOfNodeIds{2, 4, 5}), trie.getUnusedNodeIds());

    trie.deleteBasedOnKey("sea");
    EXPECT_EQ((TrieForTest::SetOfNodeIds{0, 1, 2, 3, 4, 5}), trie.getUnusedNodeIds());
}

TEST(RWayTrieUsingMatrixTest, GetUnusedNodeIdsWorks) {
    TrieForTest trie;

    EXPECT_EQ(0, trie.getSize());

    trie.put("she", 1);
    ASSERT_EQ(1, trie.getSize());
    EXPECT_EQ(1, trie.get("she"));
    EXPECT_EQ(0, trie.get("sells"));
    EXPECT_EQ(0, trie.get("sea"));

    trie.put("sells", 2);
    ASSERT_EQ(2, trie.getSize());
    EXPECT_EQ(1, trie.get("she"));
    EXPECT_EQ(2, trie.get("sells"));
    EXPECT_EQ(0, trie.get("sea"));

    trie.put("sea", 3);
    ASSERT_EQ(3, trie.getSize());
    EXPECT_EQ(1, trie.get("she"));
    EXPECT_EQ(2, trie.get("sells"));
    EXPECT_EQ(3, trie.get("sea"));

    trie.deleteBasedOnKey("she");
    EXPECT_EQ((TrieForTest::SetOfNodeIds{2}), trie.getUnusedNodeIds());
    ASSERT_EQ(2, trie.getSize());
    EXPECT_EQ(0, trie.get("she"));
    EXPECT_EQ(2, trie.get("sells"));
    EXPECT_EQ(3, trie.get("sea"));

    trie.deleteBasedOnKey("sells");
    EXPECT_EQ((TrieForTest::SetOfNodeIds{2, 4, 5}), trie.getUnusedNodeIds());
    ASSERT_EQ(1, trie.getSize());
    EXPECT_EQ(0, trie.get("she"));
    EXPECT_EQ(0, trie.get("sells"));
    EXPECT_EQ(3, trie.get("sea"));

    trie.put("she", 4);
    EXPECT_EQ((TrieForTest::SetOfNodeIds{4, 5}), trie.getUnusedNodeIds());
    ASSERT_EQ(2, trie.getSize());
    EXPECT_EQ(4, trie.get("she"));
    EXPECT_EQ(0, trie.get("sells"));
    EXPECT_EQ(3, trie.get("sea"));

    trie.deleteBasedOnKey("sea");
    EXPECT_EQ((TrieForTest::SetOfNodeIds{3, 4, 5}), trie.getUnusedNodeIds());
    ASSERT_EQ(1, trie.getSize());
    EXPECT_EQ(4, trie.get("she"));
    EXPECT_EQ(0, trie.get("sells"));
    EXPECT_EQ(0, trie.get("sea"));

    trie.put("sells", 5);
    EXPECT_EQ((TrieForTest::SetOfNodeIds{}), trie.getUnusedNodeIds());
    ASSERT_EQ(2, trie.getSize());
    EXPECT_EQ(4, trie.get("she"));
    EXPECT_EQ(5, trie.get("sells"));
    EXPECT_EQ(0, trie.get("sea"));

    trie.put("sea", 6);
    EXPECT_EQ((TrieForTest::SetOfNodeIds{}), trie.getUnusedNodeIds());
    ASSERT_EQ(3, trie.getSize());
    EXPECT_EQ(4, trie.get("she"));
    EXPECT_EQ(5, trie.get("sells"));
    EXPECT_EQ(6, trie.get("sea"));
}

// disabled because it takes too long
TEST(RWayTrieUsingMatrixTest, DISABLED_AssertionWorksWhenNodeIdsReachesMaximumSize) {
    RWayTrieUsingMatrix<int, 1> trie;

    EXPECT_DEATH(trie.put("se", 100), "Assertion failed!");
}

}  // namespace algorithm

}  // namespace alba
