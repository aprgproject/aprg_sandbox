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

TEST(RWayTrieUsingMatrixTest, PutWhenEmptyStringHasNoEffect)
{
    TrieForTest trie;

    trie.put("", 17U);

    EXPECT_EQ(0U, trie.getSize());
    EXPECT_EQ(0U, trie.get(""));
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

}

}
