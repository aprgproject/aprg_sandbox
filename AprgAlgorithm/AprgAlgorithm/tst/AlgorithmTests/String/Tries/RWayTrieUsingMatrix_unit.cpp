#include <Algorithm/String/Tries/RWayTrieUsingMatrix.hpp>
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
using TrieForTest = RWayTrieUsingMatrix<unsigned int, 50U>;
}

TEST(RWayTrieUsingMatrixTest, IsEmptyWorksWhenEmpty)
{
    testIsEmptyWhenEmptyWithUnsignedInt<TrieForTest>();
}

TEST(RWayTrieUsingMatrixTest, IsEmptyWorksWhenNotEmpty)
{
    testIsEmptyWhenNotEmptyWithUnsignedInt<TrieForTest>();
}

TEST(RWayTrieUsingMatrixTest, DoesContainWorks)
{
    testDoesContainWithUnsignedInt<TrieForTest>();
}

TEST(RWayTrieUsingMatrixTest, GetSizeWorksWhenEmpty)
{
    testGetSizeWhenEmptyWithUnsignedInt<TrieForTest>();
}

TEST(RWayTrieUsingMatrixTest, GetSizeWorksWhenNotEmpty)
{
    testGetSizeWhenNotEmptyWithUnsignedInt<TrieForTest>();
}

TEST(RWayTrieUsingMatrixTest, GetWorks)
{
    testGetWithUnsignedInt<TrieForTest>();
}

TEST(RWayTrieUsingMatrixTest, GetLongestPrefixWorks)
{
    testGetLongestPrefixOfWithUnsignedInt<TrieForTest>();
}

TEST(RWayTrieUsingMatrixTest, PutWorks)
{
    testPutWithUnsignedInt<TrieForTest>();
}

TEST(RWayTrieUsingMatrixTest, DeleteBasedOnKeyWorks)
{
    testDeleteBasedOnKeyWithUnsignedInt<TrieForTest>();
}

TEST(RWayTrieUsingMatrixTest, GetKeysWorks)
{
    testGetKeysWithUnsignedInt<TrieForTest>();
}

TEST(RWayTrieUsingMatrixTest, GetAllKeysWithPrefixWorks)
{
    testGetAllKeysWithPrefixWithUnsignedInt<TrieForTest>();
}

TEST(RWayTrieUsingMatrixTest, GetAllKeysThatMatchWorks)
{
    testGetAllKeysThatMatchWithUnsignedInt<TrieForTest>();
}

TEST(RWayTrieUsingMatrixTest, Example1Works)
{
    testExample1WithUnsignedInt<TrieForTest>();
}

TEST(RWayTrieUsingMatrixTest, PutWhenEmptyStringHasNoEffect)
{
    TrieForTest trie;
    trie.put("", 17U);

    EXPECT_EQ(0U, trie.getSize());    EXPECT_EQ(0U, trie.get(""));
}

TEST(RWayTrieUsingMatrixTest, DeleteBasedOnKeyWhenEmptyStringWorks)
{
    TrieForTest trie;
    trie.put("", 17U);

    trie.deleteBasedOnKey("");
    EXPECT_TRUE(trie.isEmpty());

    trie.deleteBasedOnKey("");
    EXPECT_TRUE(trie.isEmpty());
}

TEST(RWayTrieUsingMatrixTest, PutDeleteAlternatelyWorks)
{
    TrieForTest trie;
    trie.put("she", 0U);

    trie.put("sells", 1U);
    trie.put("sea", 2U);

    trie.deleteBasedOnKey("she");
    EXPECT_EQ((TrieForTest::SetOfNodeIds{2U}), trie.getUnusedNodeIds());

    trie.deleteBasedOnKey("sells");
    EXPECT_EQ((TrieForTest::SetOfNodeIds{2U, 4U, 5U}), trie.getUnusedNodeIds());

    trie.deleteBasedOnKey("sea");
    EXPECT_EQ((TrieForTest::SetOfNodeIds{0U, 1U, 2U, 3U, 4U, 5U}), trie.getUnusedNodeIds());
}

TEST(RWayTrieUsingMatrixTest, GetUnusedNodeIdsWorks)
{
    TrieForTest trie;

    EXPECT_EQ(0U, trie.getSize());

    trie.put("she", 1U);
    ASSERT_EQ(1U, trie.getSize());
    EXPECT_EQ(1U, trie.get("she"));
    EXPECT_EQ(0U, trie.get("sells"));
    EXPECT_EQ(0U, trie.get("sea"));

    trie.put("sells", 2U);
    ASSERT_EQ(2U, trie.getSize());
    EXPECT_EQ(1U, trie.get("she"));
    EXPECT_EQ(2U, trie.get("sells"));
    EXPECT_EQ(0U, trie.get("sea"));

    trie.put("sea", 3U);
    ASSERT_EQ(3U, trie.getSize());
    EXPECT_EQ(1U, trie.get("she"));
    EXPECT_EQ(2U, trie.get("sells"));
    EXPECT_EQ(3U, trie.get("sea"));

    trie.deleteBasedOnKey("she");
    EXPECT_EQ((TrieForTest::SetOfNodeIds{2U}), trie.getUnusedNodeIds());
    ASSERT_EQ(2U, trie.getSize());
    EXPECT_EQ(0U, trie.get("she"));
    EXPECT_EQ(2U, trie.get("sells"));
    EXPECT_EQ(3U, trie.get("sea"));

    trie.deleteBasedOnKey("sells");
    EXPECT_EQ((TrieForTest::SetOfNodeIds{2U, 4U, 5U}), trie.getUnusedNodeIds());
    ASSERT_EQ(1U, trie.getSize());
    EXPECT_EQ(0U, trie.get("she"));
    EXPECT_EQ(0U, trie.get("sells"));
    EXPECT_EQ(3U, trie.get("sea"));

    trie.put("she", 4U);
    EXPECT_EQ((TrieForTest::SetOfNodeIds{4U, 5U}), trie.getUnusedNodeIds());
    ASSERT_EQ(2U, trie.getSize());
    EXPECT_EQ(4U, trie.get("she"));
    EXPECT_EQ(0U, trie.get("sells"));
    EXPECT_EQ(3U, trie.get("sea"));

    trie.deleteBasedOnKey("sea");
    EXPECT_EQ((TrieForTest::SetOfNodeIds{3U, 4U, 5U}), trie.getUnusedNodeIds());
    ASSERT_EQ(1U, trie.getSize());
    EXPECT_EQ(4U, trie.get("she"));
    EXPECT_EQ(0U, trie.get("sells"));
    EXPECT_EQ(0U, trie.get("sea"));

    trie.put("sells", 5U);
    EXPECT_EQ((TrieForTest::SetOfNodeIds{}), trie.getUnusedNodeIds());
    ASSERT_EQ(2U, trie.getSize());
    EXPECT_EQ(4U, trie.get("she"));
    EXPECT_EQ(5U, trie.get("sells"));
    EXPECT_EQ(0U, trie.get("sea"));

    trie.put("sea", 6U);
    EXPECT_EQ((TrieForTest::SetOfNodeIds{}), trie.getUnusedNodeIds());
    ASSERT_EQ(3U, trie.getSize());
    EXPECT_EQ(4U, trie.get("she"));
    EXPECT_EQ(5U, trie.get("sells"));
    EXPECT_EQ(6U, trie.get("sea"));
}

TEST(RWayTrieUsingMatrixTest, DISABLED_AssertionWorksWhenNodeIdsReachesMaximumSize) //disabled because it takes too long
{
    RWayTrieUsingMatrix<unsigned int, 1U> trie;

    EXPECT_DEATH(trie.put("se", 100U), "Assertion failed!");
}

}

}