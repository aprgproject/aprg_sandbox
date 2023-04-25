#include <Algorithm/SetAndSymbolTable/Set/BinarySearchTree/BinarySearchTreeSet.hpp>
#include <AlgorithmTests/SetAndSymbolTable/Set/Utilities/CommonTestsWithSet.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSet;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using SetForTest = BinarySearchTreeSet<unsigned int>;
using NodeForTest = typename SetForTest::Node;
using KeysForTest = typename SetForTest::Keys;
}  // namespace

TEST(BinarySearchTreeSetTest, IsEmptyWorksWhenEmpty) { testIsEmptyWhenEmptyWithUnsignedIntAndChar<SetForTest>(); }

TEST(BinarySearchTreeSetTest, IsEmptyWorksWhenNotEmpty) { testIsEmptyWhenNotEmptyWithUnsignedIntAndChar<SetForTest>(); }

TEST(BinarySearchTreeSetTest, DoesContainWorks) { testDoesContainWithUnsignedIntAndChar<SetForTest>(); }

TEST(BinarySearchTreeSetTest, GetSizeWorksWhenEmpty) { testGetSizeWhenEmptyWithUnsignedIntAndChar<SetForTest>(); }

TEST(BinarySearchTreeSetTest, GetSizeWorksWhenNotEmpty) { testGetSizeWhenNotEmptyWithUnsignedIntAndChar<SetForTest>(); }

TEST(BinarySearchTreeSetTest, GetWorks) { testGetWithUnsignedIntAndChar<SetForTest>(); }

TEST(BinarySearchTreeSetTest, GetRankWorks) { testGetRankWithUnsignedIntAndChar<SetForTest>(); }

TEST(BinarySearchTreeSetTest, GetMinimumWorks) { testGetMinimumWithUnsignedIntAndChar<SetForTest>(); }

TEST(BinarySearchTreeSetTest, GetMaximumWorks) { testGetMaximumWithUnsignedIntAndChar<SetForTest>(); }

TEST(BinarySearchTreeSetTest, SelectAtWorks) { testSelectAtWithUnsignedIntAndChar<SetForTest>(); }

TEST(BinarySearchTreeSetTest, GetFloorWorks) { testGetFloorWithUnsignedIntAndChar<SetForTest>(); }

TEST(BinarySearchTreeSetTest, GetCeilingWorks) { testGetCeilingWithUnsignedIntAndChar<SetForTest>(); }

TEST(BinarySearchTreeSetTest, PutWorks) { testPutWithUnsignedIntAndChar<SetForTest>(); }

TEST(BinarySearchTreeSetTest, DeleteBasedOnKeyWorks) { testDeleteBasedOnKeyWithUnsignedIntAndChar<SetForTest>(); }

TEST(BinarySearchTreeSetTest, DeleteMinimumWorks) { testDeleteMinimumWithUnsignedIntAndChar<SetForTest>(); }

TEST(BinarySearchTreeSetTest, DeleteMaximumWorks) { testDeleteMaximumWithUnsignedIntAndChar<SetForTest>(); }

TEST(BinarySearchTreeSetTest, GetKeys) { testGetKeysWithUnsignedIntAndChar<SetForTest>(); }

TEST(BinarySearchTreeSetTest, GetKeysInRangeWorks) { testGetKeysInRangeInclusiveWithUnsignedIntAndChar<SetForTest>(); }

TEST(BinarySearchTreeSetTest, GetRootWorks) {
    SetForTest setObject;
    setObject.put(8U);

    auto const& expectedRoot(setObject.getRoot());

    NodeForTest node{8U, nullptr, nullptr, 1U};
    ASSERT_TRUE(expectedRoot);
    EXPECT_EQ(node.key, expectedRoot->key);
    EXPECT_EQ(node.left, expectedRoot->left);
    EXPECT_EQ(node.right, expectedRoot->right);
    EXPECT_EQ(node.numberOfNodesOnThisSubTree, expectedRoot->numberOfNodesOnThisSubTree);
}

TEST(BinarySearchTreeSetTest, TraverseByPreOrderWorks) {
    SetForTest setObject;
    setObject.put(3U);
    setObject.put(4U);
    setObject.put(5U);
    setObject.put(9U);
    setObject.put(8U);
    setObject.put(7U);

    KeysForTest keysToVerify;
    setObject.traverseByPreOrder([&keysToVerify](NodeForTest const& node) { keysToVerify.emplace_back(node.key); });

    KeysForTest expectedKeys{3U, 4U, 5U, 9U, 8U, 7U};  // not balanced
    EXPECT_EQ(expectedKeys, keysToVerify);
}

TEST(BinarySearchTreeSetTest, TraverseByInOrderWorks) {
    SetForTest setObject;
    setObject.put(3U);
    setObject.put(4U);
    setObject.put(5U);
    setObject.put(9U);
    setObject.put(8U);
    setObject.put(7U);

    KeysForTest keysToVerify;
    setObject.traverseByInOrder([&keysToVerify](NodeForTest const& node) { keysToVerify.emplace_back(node.key); });

    KeysForTest expectedKeys{3U, 4U, 5U, 7U, 8U, 9U};
    EXPECT_EQ(expectedKeys, keysToVerify);
}

TEST(BinarySearchTreeSetTest, TraverseByPostOrderWorks) {
    SetForTest setObject;
    setObject.put(3U);
    setObject.put(4U);
    setObject.put(5U);
    setObject.put(9U);
    setObject.put(8U);
    setObject.put(7U);

    KeysForTest keysToVerify;
    setObject.traverseByPostOrder([&keysToVerify](NodeForTest const& node) { keysToVerify.emplace_back(node.key); });

    KeysForTest expectedKeys{7U, 8U, 9U, 5U, 4U, 3U};  // not balanced
    EXPECT_EQ(expectedKeys, keysToVerify);
}

}  // namespace algorithm

}  // namespace alba
