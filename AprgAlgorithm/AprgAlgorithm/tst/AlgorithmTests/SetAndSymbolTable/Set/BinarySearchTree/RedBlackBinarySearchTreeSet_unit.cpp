#include <Algorithm/SetAndSymbolTable/Set/BinarySearchTree/RedBlackBinarySearchTreeSet.hpp>
#include <AlgorithmTests/SetAndSymbolTable/Set/Utilities/CommonTestsWithSet.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSet;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using SetForTest = RedBlackBinarySearchTreeSet<int>;
using NodeForTest = typename SetForTest::Node;
using KeysForTest = typename SetForTest::Keys;
}  // namespace

TEST(RedBlackBinarySearchTreeSetTest, IsEmptyWorksWhenEmpty) {
    testIsEmptyWhenEmptyWithUnsignedIntAndChar<SetForTest>();
}

TEST(RedBlackBinarySearchTreeSetTest, IsEmptyWorksWhenNotEmpty) {
    testIsEmptyWhenNotEmptyWithUnsignedIntAndChar<SetForTest>();
}

TEST(RedBlackBinarySearchTreeSetTest, DoesContainWorks) { testDoesContainWithUnsignedIntAndChar<SetForTest>(); }

TEST(RedBlackBinarySearchTreeSetTest, GetSizeWorksWhenEmpty) {
    testGetSizeWhenEmptyWithUnsignedIntAndChar<SetForTest>();
}

TEST(RedBlackBinarySearchTreeSetTest, GetSizeWorksWhenNotEmpty) {
    testGetSizeWhenNotEmptyWithUnsignedIntAndChar<SetForTest>();
}

TEST(RedBlackBinarySearchTreeSetTest, GetWorks) { testGetWithUnsignedIntAndChar<SetForTest>(); }

TEST(RedBlackBinarySearchTreeSetTest, GetRankWorks) { testGetRankWithUnsignedIntAndChar<SetForTest>(); }

TEST(RedBlackBinarySearchTreeSetTest, GetMinimumWorks) { testGetMinimumWithUnsignedIntAndChar<SetForTest>(); }

TEST(RedBlackBinarySearchTreeSetTest, GetMaximumWorks) { testGetMaximumWithUnsignedIntAndChar<SetForTest>(); }

TEST(RedBlackBinarySearchTreeSetTest, SelectAtWorks) { testSelectAtWithUnsignedIntAndChar<SetForTest>(); }

TEST(RedBlackBinarySearchTreeSetTest, GetFloorWorks) { testGetFloorWithUnsignedIntAndChar<SetForTest>(); }

TEST(RedBlackBinarySearchTreeSetTest, GetCeilingWorks) { testGetCeilingWithUnsignedIntAndChar<SetForTest>(); }

TEST(RedBlackBinarySearchTreeSetTest, PutWorks) { testPutWithUnsignedIntAndChar<SetForTest>(); }

TEST(RedBlackBinarySearchTreeSetTest, DeleteBasedOnKeyWorks) {
    testDeleteBasedOnKeyWithUnsignedIntAndChar<SetForTest>();
}

TEST(RedBlackBinarySearchTreeSetTest, DeleteMinimumWorks) { testDeleteMinimumWithUnsignedIntAndChar<SetForTest>(); }

TEST(RedBlackBinarySearchTreeSetTest, DeleteMaximumWorks) { testDeleteMaximumWithUnsignedIntAndChar<SetForTest>(); }

TEST(RedBlackBinarySearchTreeSetTest, GetKeys) { testGetKeysWithUnsignedIntAndChar<SetForTest>(); }

TEST(RedBlackBinarySearchTreeSetTest, GetKeysInRangeWorks) {
    testGetKeysInRangeInclusiveWithUnsignedIntAndChar<SetForTest>();
}

TEST(RedBlackBinarySearchTreeSetTest, TraverseByPreOrderWorks) {
    SetForTest setObject;
    setObject.put(3);
    setObject.put(4);
    setObject.put(5);
    setObject.put(9);
    setObject.put(8);
    setObject.put(7);

    KeysForTest keysToVerify;
    setObject.traverseByPreOrder([&keysToVerify](NodeForTest const& node) { keysToVerify.emplace_back(node.key); });

    KeysForTest expectedKeys{8, 4, 3, 7, 5, 9};  // balanced search tree
    EXPECT_EQ(expectedKeys, keysToVerify);
}

TEST(RedBlackBinarySearchTreeSetTest, TraverseByInOrderWorks) {
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

TEST(RedBlackBinarySearchTreeSetTest, TraverseByPostOrderWorks) {
    SetForTest setObject;
    setObject.put(3);
    setObject.put(4);
    setObject.put(5);
    setObject.put(9);
    setObject.put(8);
    setObject.put(7);

    KeysForTest keysToVerify;
    setObject.traverseByPostOrder([&keysToVerify](NodeForTest const& node) { keysToVerify.emplace_back(node.key); });

    KeysForTest expectedKeys{3, 5, 7, 4, 9, 8};  // balanced
    EXPECT_EQ(expectedKeys, keysToVerify);
}

}  // namespace algorithm

}  // namespace alba
