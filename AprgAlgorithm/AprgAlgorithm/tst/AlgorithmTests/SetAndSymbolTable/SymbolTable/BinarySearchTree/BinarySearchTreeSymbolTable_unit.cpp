#include <Algorithm/SetAndSymbolTable/SymbolTable/BinarySearchTree/BinarySearchTreeSymbolTable.hpp>
#include <AlgorithmTests/SetAndSymbolTable/SymbolTable/Utilities/CommonTestsWithSymbolTable.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSymbolTable;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using SymbolTableForTest = BinarySearchTreeSymbolTable<int, char>;
using NodeForTest = typename SymbolTableForTest::Node;
using KeysForTest = typename SymbolTableForTest::Keys;
}  // namespace

TEST(BinarySearchTreeSymbolTableTest, IsEmptyWorksWhenEmpty) {
    testIsEmptyWhenEmptyWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(BinarySearchTreeSymbolTableTest, IsEmptyWorksWhenNotEmpty) {
    testIsEmptyWhenNotEmptyWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(BinarySearchTreeSymbolTableTest, DoesContainWorks) { testDoesContainWithUnsignedIntAndChar<SymbolTableForTest>(); }

TEST(BinarySearchTreeSymbolTableTest, GetSizeWorksWhenEmpty) {
    testGetSizeWhenEmptyWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(BinarySearchTreeSymbolTableTest, GetSizeWorksWhenNotEmpty) {
    testGetSizeWhenNotEmptyWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(BinarySearchTreeSymbolTableTest, GetWorks) { testGetWithUnsignedIntAndChar<SymbolTableForTest>(); }

TEST(BinarySearchTreeSymbolTableTest, GetRankWorks) { testGetRankWithUnsignedIntAndChar<SymbolTableForTest>(); }

TEST(BinarySearchTreeSymbolTableTest, GetMinimumWorks) { testGetMinimumWithUnsignedIntAndChar<SymbolTableForTest>(); }

TEST(BinarySearchTreeSymbolTableTest, GetMaximumWorks) { testGetMaximumWithUnsignedIntAndChar<SymbolTableForTest>(); }

TEST(BinarySearchTreeSymbolTableTest, SelectAtWorks) { testSelectAtWithUnsignedIntAndChar<SymbolTableForTest>(); }

TEST(BinarySearchTreeSymbolTableTest, GetFloorWorks) { testGetFloorWithUnsignedIntAndChar<SymbolTableForTest>(); }

TEST(BinarySearchTreeSymbolTableTest, GetCeilingWorks) { testGetCeilingWithUnsignedIntAndChar<SymbolTableForTest>(); }

TEST(BinarySearchTreeSymbolTableTest, PutWorks) { testPutWithUnsignedIntAndChar<SymbolTableForTest>(); }

TEST(BinarySearchTreeSymbolTableTest, DeleteBasedOnKeyWorks) {
    testDeleteBasedOnKeyWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(BinarySearchTreeSymbolTableTest, DeleteMinimumWorks) {
    testDeleteMinimumWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(BinarySearchTreeSymbolTableTest, DeleteMaximumWorks) {
    testDeleteMaximumWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(BinarySearchTreeSymbolTableTest, GetKeys) { testGetKeysWithUnsignedIntAndChar<SymbolTableForTest>(); }

TEST(BinarySearchTreeSymbolTableTest, GetKeysInRangeWorks) {
    testGetKeysInRangeInclusiveWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(BinarySearchTreeSymbolTableTest, GetRootWorks) {
    SymbolTableForTest symbolTable;
    symbolTable.put(8, 'H');

    auto const& expectedRoot(symbolTable.getRoot());

    NodeForTest node{8, 'H', nullptr, nullptr, 1};
    ASSERT_TRUE(expectedRoot);
    EXPECT_EQ(node.key, expectedRoot->key);
    EXPECT_EQ(node.value, expectedRoot->value);
    EXPECT_EQ(node.left, expectedRoot->left);
    EXPECT_EQ(node.right, expectedRoot->right);
    EXPECT_EQ(node.sizeOfThisSubTree, expectedRoot->sizeOfThisSubTree);
}

TEST(BinarySearchTreeSymbolTableTest, TraverseByPreOrderWorks) {
    SymbolTableForTest symbolTable;
    symbolTable.put(3, 'C');
    symbolTable.put(4, 'D');
    symbolTable.put(5, 'E');
    symbolTable.put(9, 'I');
    symbolTable.put(8, 'H');
    symbolTable.put(7, 'G');

    KeysForTest keysToVerify;
    symbolTable.traverseByPreOrder([&keysToVerify](NodeForTest const& node) { keysToVerify.emplace_back(node.key); });

    KeysForTest expectedKeys{3, 4, 5, 9, 8, 7};  // not balanced
    EXPECT_EQ(expectedKeys, keysToVerify);
}

TEST(BinarySearchTreeSymbolTableTest, TraverseByInOrderWorks) {
    SymbolTableForTest symbolTable;
    symbolTable.put(3, 'C');
    symbolTable.put(4, 'D');
    symbolTable.put(5, 'E');
    symbolTable.put(9, 'I');
    symbolTable.put(8, 'H');
    symbolTable.put(7, 'G');

    KeysForTest keysToVerify;
    symbolTable.traverseByInOrder([&keysToVerify](NodeForTest const& node) { keysToVerify.emplace_back(node.key); });

    KeysForTest expectedKeys{3, 4, 5, 7, 8, 9};  // not balanced
    EXPECT_EQ(expectedKeys, keysToVerify);
}

TEST(BinarySearchTreeSymbolTableTest, TraverseByPostOrderWorks) {
    SymbolTableForTest symbolTable;
    symbolTable.put(3, 'C');
    symbolTable.put(4, 'D');
    symbolTable.put(5, 'E');
    symbolTable.put(9, 'I');
    symbolTable.put(8, 'H');
    symbolTable.put(7, 'G');

    KeysForTest keysToVerify;
    symbolTable.traverseByPostOrder([&keysToVerify](NodeForTest const& node) { keysToVerify.emplace_back(node.key); });

    KeysForTest expectedKeys{7, 8, 9, 5, 4, 3};  // not balanced
    EXPECT_EQ(expectedKeys, keysToVerify);
}

TEST(BinarySearchTreeSymbolTableTest, HibbardDeletionWorks) {
    SymbolTableForTest symbolTable;
    symbolTable.put(8, 'H');
    symbolTable.put(4, 'D');
    symbolTable.put(9, 'I');
    symbolTable.put(3, 'C');
    symbolTable.put(7, 'G');
    symbolTable.put(5, 'E');

    KeysForTest actualBeforeDelete;
    KeysForTest actualAfterDelete;
    symbolTable.traverseByPreOrder(
        [&actualBeforeDelete](NodeForTest const& node) { actualBeforeDelete.emplace_back(node.key); });
    symbolTable.deleteBasedOnKey(7);
    symbolTable.deleteBasedOnKey(4);
    symbolTable.deleteBasedOnKey(3);
    symbolTable.traverseByPreOrder(
        [&actualAfterDelete](NodeForTest const& node) { actualAfterDelete.emplace_back(node.key); });

    KeysForTest expectedBeforeDelete{8, 4, 3, 7, 5, 9};
    KeysForTest expectedAfterDelete{8, 5, 9};
    EXPECT_EQ(expectedBeforeDelete, actualBeforeDelete);
    EXPECT_EQ(expectedAfterDelete, actualAfterDelete);
}

}  // namespace algorithm

}  // namespace alba