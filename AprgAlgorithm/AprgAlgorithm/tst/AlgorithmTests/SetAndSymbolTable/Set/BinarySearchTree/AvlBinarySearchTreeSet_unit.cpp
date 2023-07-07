#include <Algorithm/SetAndSymbolTable/Set/BinarySearchTree/AvlBinarySearchTreeSet.hpp>
#include <AlgorithmTests/SetAndSymbolTable/Set/Utilities/CommonTestsWithSet.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSet;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using SetForTest = AvlBinarySearchTreeSet<int>;
using NodeForTest = typename SetForTest::Node;
using KeysForTest = typename SetForTest::Keys;
}  // namespace

TEST(AvlBinarySearchTreeSetTest, IsEmptyWorksWhenEmpty) { testIsEmptyWhenEmptyWithUnsignedIntAndChar<SetForTest>(); }

TEST(AvlBinarySearchTreeSetTest, IsEmptyWorksWhenNotEmpty) {
    testIsEmptyWhenNotEmptyWithUnsignedIntAndChar<SetForTest>();
}

TEST(AvlBinarySearchTreeSetTest, DoesContainWorks) { testDoesContainWithUnsignedIntAndChar<SetForTest>(); }

TEST(AvlBinarySearchTreeSetTest, GetSizeWorksWhenEmpty) { testGetSizeWhenEmptyWithUnsignedIntAndChar<SetForTest>(); }

TEST(AvlBinarySearchTreeSetTest, GetSizeWorksWhenNotEmpty) {
    testGetSizeWhenNotEmptyWithUnsignedIntAndChar<SetForTest>();
}

TEST(AvlBinarySearchTreeSetTest, GetWorks) { testGetWithUnsignedIntAndChar<SetForTest>(); }

TEST(AvlBinarySearchTreeSetTest, GetRankWorks) { testGetRankWithUnsignedIntAndChar<SetForTest>(); }

TEST(AvlBinarySearchTreeSetTest, GetMinimumWorks) { testGetMinimumWithUnsignedIntAndChar<SetForTest>(); }

TEST(AvlBinarySearchTreeSetTest, GetMaximumWorks) { testGetMaximumWithUnsignedIntAndChar<SetForTest>(); }

TEST(AvlBinarySearchTreeSetTest, SelectAtWorks) { testSelectAtWithUnsignedIntAndChar<SetForTest>(); }

TEST(AvlBinarySearchTreeSetTest, GetFloorWorks) { testGetFloorWithUnsignedIntAndChar<SetForTest>(); }

TEST(AvlBinarySearchTreeSetTest, GetCeilingWorks) { testGetCeilingWithUnsignedIntAndChar<SetForTest>(); }

TEST(AvlBinarySearchTreeSetTest, PutWorks) { testPutWithUnsignedIntAndChar<SetForTest>(); }

TEST(AvlBinarySearchTreeSetTest, DeleteBasedOnKeyWorks) { testDeleteBasedOnKeyWithUnsignedIntAndChar<SetForTest>(); }

TEST(AvlBinarySearchTreeSetTest, DeleteMinimumWorks) { testDeleteMinimumWithUnsignedIntAndChar<SetForTest>(); }

TEST(AvlBinarySearchTreeSetTest, DeleteMaximumWorks) { testDeleteMaximumWithUnsignedIntAndChar<SetForTest>(); }

TEST(AvlBinarySearchTreeSetTest, GetKeys) { testGetKeysWithUnsignedIntAndChar<SetForTest>(); }

TEST(AvlBinarySearchTreeSetTest, GetKeysInRangeWorks) {
    testGetKeysInRangeInclusiveWithUnsignedIntAndChar<SetForTest>();
}

TEST(AvlBinarySearchTreeSetTest, TraverseByPreOrderWorks) {
    SetForTest setObject;
    setObject.put(3);
    setObject.put(4);
    setObject.put(5);
    setObject.put(9);
    setObject.put(8);
    setObject.put(7);

    KeysForTest keysToVerify;
    setObject.traverseByPreOrder([&keysToVerify](NodeForTest const& node) { keysToVerify.emplace_back(node.key); });

    KeysForTest expectedKeys{5, 4, 3, 8, 7, 9};  // balanced
    EXPECT_EQ(expectedKeys, keysToVerify);
}

TEST(AvlBinarySearchTreeSetTest, TraverseByInOrderWorks) {
    SetForTest setObject;
    setObject.put(3);
    setObject.put(4);
    setObject.put(5);
    setObject.put(9);
    setObject.put(8);
    setObject.put(7);

    KeysForTest keysToVerify;
    setObject.traverseByInOrder([&keysToVerify](NodeForTest const& node) { keysToVerify.emplace_back(node.key); });

    KeysForTest expectedKeys{3, 4, 5, 7, 8, 9};  // balanced
    EXPECT_EQ(expectedKeys, keysToVerify);
}

TEST(AvlBinarySearchTreeSetTest, TraverseByPostOrderWorks) {
    SetForTest setObject;
    setObject.put(3);
    setObject.put(4);
    setObject.put(5);
    setObject.put(9);
    setObject.put(8);
    setObject.put(7);

    KeysForTest keysToVerify;
    setObject.traverseByPostOrder([&keysToVerify](NodeForTest const& node) { keysToVerify.emplace_back(node.key); });

    KeysForTest expectedKeys{3, 4, 7, 9, 8, 5};  // balanced
    EXPECT_EQ(expectedKeys, keysToVerify);
}

TEST(AvlBinarySearchTreeSetTest, AfterDeletionTheTreeIsStillBalanced) {
    SetForTest setObject;
    setObject.put(3);
    setObject.put(4);
    setObject.put(5);
    setObject.put(9);
    setObject.put(8);
    setObject.put(7);

    KeysForTest actualBeforeDelete;
    KeysForTest actualAfterDelete;
    setObject.traverseByPreOrder(
        [&actualBeforeDelete](NodeForTest const& node) { actualBeforeDelete.emplace_back(node.key); });
    setObject.deleteBasedOnKey(5);
    setObject.deleteBasedOnKey(7);
    setObject.deleteBasedOnKey(8);
    setObject.traverseByPreOrder(
        [&actualAfterDelete](NodeForTest const& node) { actualAfterDelete.emplace_back(node.key); });

    KeysForTest expectedBeforeDelete{5, 4, 3, 8, 7, 9};  // balanced
    KeysForTest expectedAfterDelete{4, 3, 9};            // still balanced
    EXPECT_EQ(expectedBeforeDelete, actualBeforeDelete);
    EXPECT_EQ(expectedAfterDelete, actualAfterDelete);
}

TEST(AvlBinarySearchTreeSetTest, AfterDeletionOfMinimumTheTreeIsStillBalanced) {
    SetForTest setObject;
    setObject.put(3);
    setObject.put(4);
    setObject.put(5);
    setObject.put(9);
    setObject.put(8);
    setObject.put(7);

    KeysForTest actualBeforeDelete;
    KeysForTest actualAfterDelete;
    setObject.traverseByPreOrder(
        [&actualBeforeDelete](NodeForTest const& node) { actualBeforeDelete.emplace_back(node.key); });
    setObject.deleteMinimum();
    setObject.deleteMinimum();
    setObject.deleteMinimum();
    setObject.traverseByPreOrder(
        [&actualAfterDelete](NodeForTest const& node) { actualAfterDelete.emplace_back(node.key); });

    KeysForTest expectedBeforeDelete{5, 4, 3, 8, 7, 9};  // balanced
    KeysForTest expectedAfterDelete{8, 7, 9};            // still balanced
    EXPECT_EQ(expectedBeforeDelete, actualBeforeDelete);
    EXPECT_EQ(expectedAfterDelete, actualAfterDelete);
}

TEST(AvlBinarySearchTreeSetTest, AfterDeletionOfMaximumTheTreeIsStillBalanced) {
    SetForTest setObject;
    setObject.put(3);
    setObject.put(4);
    setObject.put(5);
    setObject.put(9);
    setObject.put(8);
    setObject.put(7);

    KeysForTest actualBeforeDelete;
    KeysForTest actualAfterDelete;
    setObject.traverseByPreOrder(
        [&actualBeforeDelete](NodeForTest const& node) { actualBeforeDelete.emplace_back(node.key); });
    setObject.deleteMaximum();
    setObject.deleteMaximum();
    setObject.deleteMaximum();
    setObject.traverseByPreOrder(
        [&actualAfterDelete](NodeForTest const& node) { actualAfterDelete.emplace_back(node.key); });

    KeysForTest expectedBeforeDelete{5, 4, 3, 8, 7, 9};  // balanced
    KeysForTest expectedAfterDelete{4, 3, 5};            // still balanced
    EXPECT_EQ(expectedBeforeDelete, actualBeforeDelete);
    EXPECT_EQ(expectedAfterDelete, actualAfterDelete);
}

}  // namespace algorithm

}  // namespace alba
