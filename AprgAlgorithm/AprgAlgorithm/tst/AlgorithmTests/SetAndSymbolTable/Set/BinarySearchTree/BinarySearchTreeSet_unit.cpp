#include <Algorithm/SetAndSymbolTable/Set/BinarySearchTree/BinarySearchTreeSet.hpp>
#include <AlgorithmTests/SetAndSymbolTable/Set/Utilities/CommonTestsWithSet.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSet;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using SetForTest = BinarySearchTreeSet<int>;
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
    setObject.put(8);

    auto const& expectedRoot(setObject.getRoot());

    NodeForTest node{8, nullptr, nullptr, 1};
    ASSERT_TRUE(expectedRoot);
    EXPECT_EQ(node.key, expectedRoot->key);
    EXPECT_EQ(node.left, expectedRoot->left);
    EXPECT_EQ(node.right, expectedRoot->right);
    EXPECT_EQ(node.sizeOfThisSubTree, expectedRoot->sizeOfThisSubTree);
}

TEST(BinarySearchTreeSetTest, TraverseByPreOrderWorks) {
    SetForTest setObject;
    setObject.put(3);
    setObject.put(4);
    setObject.put(5);
    setObject.put(9);
    setObject.put(8);
    setObject.put(7);

    KeysForTest keysToVerify;
    setObject.traverseByPreOrder([&keysToVerify](NodeForTest const& node) { keysToVerify.emplace_back(node.key); });

    KeysForTest expectedKeys{3, 4, 5, 9, 8, 7};  // not balanced
    EXPECT_EQ(expectedKeys, keysToVerify);
}

TEST(BinarySearchTreeSetTest, TraverseByInOrderWorks) {
    SetForTest setObject;
    setObject.put(3);
    setObject.put(4);
    setObject.put(5);
    setObject.put(9);
    setObject.put(8);
    setObject.put(7);

    KeysForTest keysToVerify;
    setObject.traverseByInOrder([&keysToVerify](NodeForTest const& node) { keysToVerify.emplace_back(node.key); });

    KeysForTest expectedKeys{3, 4, 5, 7, 8, 9};
    EXPECT_EQ(expectedKeys, keysToVerify);
}

TEST(BinarySearchTreeSetTest, TraverseByPostOrderWorks) {
    SetForTest setObject;
    setObject.put(3);
    setObject.put(4);
    setObject.put(5);
    setObject.put(9);
    setObject.put(8);
    setObject.put(7);

    KeysForTest keysToVerify;
    setObject.traverseByPostOrder([&keysToVerify](NodeForTest const& node) { keysToVerify.emplace_back(node.key); });

    KeysForTest expectedKeys{7, 8, 9, 5, 4, 3};  // not balanced
    EXPECT_EQ(expectedKeys, keysToVerify);
}

TEST(BinarySearchTreeSetTest, HibbardDeletionWorks) {
    SetForTest setObject;
    setObject.put(8);
    setObject.put(4);
    setObject.put(9);
    setObject.put(3);
    setObject.put(7);
    setObject.put(5);

    KeysForTest actualBeforeDelete;
    KeysForTest actualAfterDelete;
    setObject.traverseByPreOrder(
        [&actualBeforeDelete](NodeForTest const& node) { actualBeforeDelete.emplace_back(node.key); });
    setObject.deleteBasedOnKey(7);
    setObject.deleteBasedOnKey(4);
    setObject.deleteBasedOnKey(3);
    setObject.traverseByPreOrder(
        [&actualAfterDelete](NodeForTest const& node) { actualAfterDelete.emplace_back(node.key); });

    KeysForTest expectedBeforeDelete{8, 4, 3, 7, 5, 9};
    KeysForTest expectedAfterDelete{8, 5, 9};
    EXPECT_EQ(expectedBeforeDelete, actualBeforeDelete);
    EXPECT_EQ(expectedAfterDelete, actualAfterDelete);
}

}  // namespace algorithm

}  // namespace alba
