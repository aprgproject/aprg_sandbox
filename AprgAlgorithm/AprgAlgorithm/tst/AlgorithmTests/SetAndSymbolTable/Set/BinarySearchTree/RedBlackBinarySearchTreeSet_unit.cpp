#include <Algorithm/SetAndSymbolTable/Set/BinarySearchTree/RedBlackBinarySearchTreeSet.hpp>
#include <AlgorithmTests/SetAndSymbolTable/Set/Utilities/CommonTestsWithSet.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSet;
using namespace std;


namespace alba
{

namespace algorithm
{

namespace
{
using SetForTest = RedBlackBinarySearchTreeSet<unsigned int>;
using NodeForTest = typename SetForTest::Node;
using KeysForTest = typename SetForTest::Keys;
}

TEST(RedBlackBinarySearchTreeSetTest, IsEmptyWorksWhenEmpty)
{
    testIsEmptyWhenEmptyWithUnsignedIntAndChar<SetForTest>();
}

TEST(RedBlackBinarySearchTreeSetTest, IsEmptyWorksWhenNotEmpty)
{
    testIsEmptyWhenNotEmptyWithUnsignedIntAndChar<SetForTest>();
}

TEST(RedBlackBinarySearchTreeSetTest, DoesContainWorks)
{
    testDoesContainWithUnsignedIntAndChar<SetForTest>();
}

TEST(RedBlackBinarySearchTreeSetTest, GetSizeWorksWhenEmpty)
{
    testGetSizeWhenEmptyWithUnsignedIntAndChar<SetForTest>();
}

TEST(RedBlackBinarySearchTreeSetTest, GetSizeWorksWhenNotEmpty)
{
    testGetSizeWhenNotEmptyWithUnsignedIntAndChar<SetForTest>();
}

TEST(RedBlackBinarySearchTreeSetTest, GetWorks)
{
    testGetWithUnsignedIntAndChar<SetForTest>();
}

TEST(RedBlackBinarySearchTreeSetTest, GetRankWorks)
{
    testGetRankWithUnsignedIntAndChar<SetForTest>();
}

TEST(RedBlackBinarySearchTreeSetTest, GetMinimumWorks)
{
    testGetMinimumWithUnsignedIntAndChar<SetForTest>();
}

TEST(RedBlackBinarySearchTreeSetTest, GetMaximumWorks)
{
    testGetMaximumWithUnsignedIntAndChar<SetForTest>();
}

TEST(RedBlackBinarySearchTreeSetTest, SelectAtWorks)
{
    testSelectAtWithUnsignedIntAndChar<SetForTest>();
}

TEST(RedBlackBinarySearchTreeSetTest, GetFloorWorks)
{
    testGetFloorWithUnsignedIntAndChar<SetForTest>();
}

TEST(RedBlackBinarySearchTreeSetTest, GetCeilingWorks)
{
    testGetCeilingWithUnsignedIntAndChar<SetForTest>();
}

TEST(RedBlackBinarySearchTreeSetTest, PutWorks)
{
    testPutWithUnsignedIntAndChar<SetForTest>();
}

TEST(RedBlackBinarySearchTreeSetTest, DeleteBasedOnKeyWorks)
{
    testDeleteBasedOnKeyWithUnsignedIntAndChar<SetForTest>();
}

TEST(RedBlackBinarySearchTreeSetTest, DeleteMinimumWorks)
{
    testDeleteMinimumWithUnsignedIntAndChar<SetForTest>();
}

TEST(RedBlackBinarySearchTreeSetTest, DeleteMaximumWorks)
{
    testDeleteMaximumWithUnsignedIntAndChar<SetForTest>();
}

TEST(RedBlackBinarySearchTreeSetTest, GetKeys)
{
    testGetKeysWithUnsignedIntAndChar<SetForTest>();
}

TEST(RedBlackBinarySearchTreeSetTest, GetKeysInRangeWorks)
{
    testGetKeysInRangeInclusiveWithUnsignedIntAndChar<SetForTest>();
}

TEST(RedBlackBinarySearchTreeSetTest, TraverseByPreOrderWorks)
{
    SetForTest setObject;
    setObject.put(3U);
    setObject.put(4U);
    setObject.put(5U);
    setObject.put(9U);
    setObject.put(8U);
    setObject.put(7U);

    KeysForTest keysToVerify;
    setObject.traverseByPreOrder([&keysToVerify](NodeForTest const& node)
    {
        keysToVerify.emplace_back(node.key);
    });

    KeysForTest expectedKeys{8U, 4U, 3U, 7U, 5U, 9U}; // balanced search tree
    EXPECT_EQ(expectedKeys, keysToVerify);
}

TEST(RedBlackBinarySearchTreeSetTest, TraverseByInOrderWorks)
{
    SetForTest setObject;
    setObject.put(3U);
    setObject.put(4U);
    setObject.put(5U);
    setObject.put(9U);
    setObject.put(8U);
    setObject.put(7U);

    KeysForTest keysToVerify;
    setObject.traverseByInOrder([&keysToVerify](NodeForTest const& node)
    {
        keysToVerify.emplace_back(node.key);
    });

    KeysForTest expectedKeys{3U, 4U, 5U, 7U, 8U, 9U};
    EXPECT_EQ(expectedKeys, keysToVerify);
}

TEST(RedBlackBinarySearchTreeSetTest, TraverseByPostOrderWorks)
{
    SetForTest setObject;
    setObject.put(3U);
    setObject.put(4U);
    setObject.put(5U);
    setObject.put(9U);
    setObject.put(8U);
    setObject.put(7U);

    KeysForTest keysToVerify;
    setObject.traverseByPostOrder([&keysToVerify](NodeForTest const& node)
    {
        keysToVerify.emplace_back(node.key);
    });

    KeysForTest expectedKeys{3U, 5U, 7U, 4U, 9U, 8U}; // balanced
    EXPECT_EQ(expectedKeys, keysToVerify);
}

}

}
