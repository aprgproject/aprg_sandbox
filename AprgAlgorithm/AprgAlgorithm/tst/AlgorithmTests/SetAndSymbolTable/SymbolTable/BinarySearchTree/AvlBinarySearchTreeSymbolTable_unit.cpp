#include <Algorithm/SetAndSymbolTable/SymbolTable/BinarySearchTree/AvlBinarySearchTreeSymbolTable.hpp>
#include <AlgorithmTests/SetAndSymbolTable/SymbolTable/Utilities/CommonTestsWithSymbolTable.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSymbolTable;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using SymbolTableForTest = AvlBinarySearchTreeSymbolTable<int, char>;
using NodeForTest = typename SymbolTableForTest::Node;
using KeysForTest = typename SymbolTableForTest::Keys;
}  // namespace

TEST(AvlBinarySearchTreeSymbolTableTest, IsEmptyWorksWhenEmpty) {
    testIsEmptyWhenEmptyWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(AvlBinarySearchTreeSymbolTableTest, IsEmptyWorksWhenNotEmpty) {
    testIsEmptyWhenNotEmptyWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(AvlBinarySearchTreeSymbolTableTest, DoesContainWorks) {
    testDoesContainWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(AvlBinarySearchTreeSymbolTableTest, GetSizeWorksWhenEmpty) {
    testGetSizeWhenEmptyWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(AvlBinarySearchTreeSymbolTableTest, GetSizeWorksWhenNotEmpty) {
    testGetSizeWhenNotEmptyWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(AvlBinarySearchTreeSymbolTableTest, GetWorks) { testGetWithUnsignedIntAndChar<SymbolTableForTest>(); }

TEST(AvlBinarySearchTreeSymbolTableTest, GetRankWorks) { testGetRankWithUnsignedIntAndChar<SymbolTableForTest>(); }

TEST(AvlBinarySearchTreeSymbolTableTest, GetMinimumWorks) {
    testGetMinimumWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(AvlBinarySearchTreeSymbolTableTest, GetMaximumWorks) {
    testGetMaximumWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(AvlBinarySearchTreeSymbolTableTest, SelectAtWorks) { testSelectAtWithUnsignedIntAndChar<SymbolTableForTest>(); }

TEST(AvlBinarySearchTreeSymbolTableTest, GetFloorWorks) { testGetFloorWithUnsignedIntAndChar<SymbolTableForTest>(); }

TEST(AvlBinarySearchTreeSymbolTableTest, GetCeilingWorks) {
    testGetCeilingWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(AvlBinarySearchTreeSymbolTableTest, PutWorks) { testPutWithUnsignedIntAndChar<SymbolTableForTest>(); }

TEST(AvlBinarySearchTreeSymbolTableTest, DeleteBasedOnKeyWorks) {
    testDeleteBasedOnKeyWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(AvlBinarySearchTreeSymbolTableTest, DeleteMinimumWorks) {
    testDeleteMinimumWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(AvlBinarySearchTreeSymbolTableTest, DeleteMaximumWorks) {
    testDeleteMaximumWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(AvlBinarySearchTreeSymbolTableTest, GetKeys) { testGetKeysWithUnsignedIntAndChar<SymbolTableForTest>(); }

TEST(AvlBinarySearchTreeSymbolTableTest, GetKeysInRangeWorks) {
    testGetKeysInRangeInclusiveWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(AvlBinarySearchTreeSymbolTableTest, TraverseByPreOrderWorks) {
    SymbolTableForTest symbolTable;
    symbolTable.put(3, 'C');
    symbolTable.put(4, 'D');
    symbolTable.put(5, 'E');
    symbolTable.put(9, 'I');
    symbolTable.put(8, 'H');
    symbolTable.put(7, 'G');

    KeysForTest keysToVerify;
    symbolTable.traverseByPreOrder([&keysToVerify](NodeForTest const& node) { keysToVerify.emplace_back(node.key); });

    KeysForTest expectedKeys{5, 4, 3, 8, 7, 9};  // balanced
    EXPECT_EQ(expectedKeys, keysToVerify);
}

TEST(AvlBinarySearchTreeSymbolTableTest, TraverseByInOrderWorks) {
    SymbolTableForTest symbolTable;
    symbolTable.put(3, 'C');
    symbolTable.put(4, 'D');
    symbolTable.put(5, 'E');
    symbolTable.put(9, 'I');
    symbolTable.put(8, 'H');
    symbolTable.put(7, 'G');

    KeysForTest keysToVerify;
    symbolTable.traverseByInOrder([&keysToVerify](NodeForTest const& node) { keysToVerify.emplace_back(node.key); });

    KeysForTest expectedKeys{3, 4, 5, 7, 8, 9};  // balanced
    EXPECT_EQ(expectedKeys, keysToVerify);
}

TEST(AvlBinarySearchTreeSymbolTableTest, TraverseByPostOrderWorks) {
    SymbolTableForTest symbolTable;
    symbolTable.put(3, 'C');
    symbolTable.put(4, 'D');
    symbolTable.put(5, 'E');
    symbolTable.put(9, 'I');
    symbolTable.put(8, 'H');
    symbolTable.put(7, 'G');

    KeysForTest keysToVerify;
    symbolTable.traverseByPostOrder([&keysToVerify](NodeForTest const& node) { keysToVerify.emplace_back(node.key); });

    KeysForTest expectedKeys{3, 4, 7, 9, 8, 5};  // balanced
    EXPECT_EQ(expectedKeys, keysToVerify);
}

TEST(AvlBinarySearchTreeSymbolTableTest, AfterDeletionTheTreeIsStillBalanced) {
    SymbolTableForTest symbolTable;
    symbolTable.put(3, 'C');
    symbolTable.put(4, 'D');
    symbolTable.put(5, 'E');
    symbolTable.put(9, 'I');
    symbolTable.put(8, 'H');
    symbolTable.put(7, 'G');

    KeysForTest actualBeforeDelete;
    KeysForTest actualAfterDelete;
    symbolTable.traverseByPreOrder(
        [&actualBeforeDelete](NodeForTest const& node) { actualBeforeDelete.emplace_back(node.key); });
    symbolTable.deleteBasedOnKey(5);
    symbolTable.deleteBasedOnKey(7);
    symbolTable.deleteBasedOnKey(8);
    symbolTable.traverseByPreOrder(
        [&actualAfterDelete](NodeForTest const& node) { actualAfterDelete.emplace_back(node.key); });

    KeysForTest expectedBeforeDelete{5, 4, 3, 8, 7, 9};  // balanced
    KeysForTest expectedAfterDelete{4, 3, 9};            // still balanced
    EXPECT_EQ(expectedBeforeDelete, actualBeforeDelete);
    EXPECT_EQ(expectedAfterDelete, actualAfterDelete);
}

TEST(AvlBinarySearchTreeSymbolTableTest, AfterDeletionOfMinimumTheTreeIsStillBalanced) {
    SymbolTableForTest symbolTable;
    symbolTable.put(3, 'C');
    symbolTable.put(4, 'D');
    symbolTable.put(5, 'E');
    symbolTable.put(9, 'I');
    symbolTable.put(8, 'H');
    symbolTable.put(7, 'G');

    KeysForTest actualBeforeDelete;
    KeysForTest actualAfterDelete;
    symbolTable.traverseByPreOrder(
        [&actualBeforeDelete](NodeForTest const& node) { actualBeforeDelete.emplace_back(node.key); });
    symbolTable.deleteMinimum();
    symbolTable.deleteMinimum();
    symbolTable.deleteMinimum();
    symbolTable.traverseByPreOrder(
        [&actualAfterDelete](NodeForTest const& node) { actualAfterDelete.emplace_back(node.key); });

    KeysForTest expectedBeforeDelete{5, 4, 3, 8, 7, 9};  // balanced
    KeysForTest expectedAfterDelete{8, 7, 9};            // still balanced
    EXPECT_EQ(expectedBeforeDelete, actualBeforeDelete);
    EXPECT_EQ(expectedAfterDelete, actualAfterDelete);
}

TEST(AvlBinarySearchTreeSymbolTableTest, AfterDeletionOfMaximumTheTreeIsStillBalanced) {
    SymbolTableForTest symbolTable;
    symbolTable.put(3, 'C');
    symbolTable.put(4, 'D');
    symbolTable.put(5, 'E');
    symbolTable.put(9, 'I');
    symbolTable.put(8, 'H');
    symbolTable.put(7, 'G');

    KeysForTest actualBeforeDelete;
    KeysForTest actualAfterDelete;
    symbolTable.traverseByPreOrder(
        [&actualBeforeDelete](NodeForTest const& node) { actualBeforeDelete.emplace_back(node.key); });
    symbolTable.deleteMaximum();
    symbolTable.deleteMaximum();
    symbolTable.deleteMaximum();
    symbolTable.traverseByPreOrder(
        [&actualAfterDelete](NodeForTest const& node) { actualAfterDelete.emplace_back(node.key); });

    KeysForTest expectedBeforeDelete{5, 4, 3, 8, 7, 9};  // balanced
    KeysForTest expectedAfterDelete{4, 3, 5};            // still balanced
    EXPECT_EQ(expectedBeforeDelete, actualBeforeDelete);
    EXPECT_EQ(expectedAfterDelete, actualAfterDelete);
}

}  // namespace algorithm

}  // namespace alba
