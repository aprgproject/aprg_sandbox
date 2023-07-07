#include <Algorithm/SetAndSymbolTable/SymbolTable/BinarySearchTree/RedBlackBinarySearchTreeSymbolTable.hpp>
#include <AlgorithmTests/SetAndSymbolTable/SymbolTable/Utilities/CommonTestsWithSymbolTable.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSymbolTable;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using SymbolTableForTest = RedBlackBinarySearchTreeSymbolTable<int, char>;
using NodeForTest = typename SymbolTableForTest::Node;
using KeysForTest = typename SymbolTableForTest::Keys;
}  // namespace

TEST(RedBlackBinarySearchTreeSymbolTableTest, IsEmptyWorksWhenEmpty) {
    testIsEmptyWhenEmptyWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(RedBlackBinarySearchTreeSymbolTableTest, IsEmptyWorksWhenNotEmpty) {
    testIsEmptyWhenNotEmptyWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(RedBlackBinarySearchTreeSymbolTableTest, DoesContainWorks) {
    testDoesContainWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(RedBlackBinarySearchTreeSymbolTableTest, GetSizeWorksWhenEmpty) {
    testGetSizeWhenEmptyWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(RedBlackBinarySearchTreeSymbolTableTest, GetSizeWorksWhenNotEmpty) {
    testGetSizeWhenNotEmptyWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(RedBlackBinarySearchTreeSymbolTableTest, GetWorks) { testGetWithUnsignedIntAndChar<SymbolTableForTest>(); }

TEST(RedBlackBinarySearchTreeSymbolTableTest, GetRankWorks) { testGetRankWithUnsignedIntAndChar<SymbolTableForTest>(); }

TEST(RedBlackBinarySearchTreeSymbolTableTest, GetMinimumWorks) {
    testGetMinimumWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(RedBlackBinarySearchTreeSymbolTableTest, GetMaximumWorks) {
    testGetMaximumWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(RedBlackBinarySearchTreeSymbolTableTest, SelectAtWorks) {
    testSelectAtWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(RedBlackBinarySearchTreeSymbolTableTest, GetFloorWorks) {
    testGetFloorWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(RedBlackBinarySearchTreeSymbolTableTest, GetCeilingWorks) {
    testGetCeilingWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(RedBlackBinarySearchTreeSymbolTableTest, PutWorks) { testPutWithUnsignedIntAndChar<SymbolTableForTest>(); }

TEST(RedBlackBinarySearchTreeSymbolTableTest, DeleteBasedOnKeyWorks) {
    testDeleteBasedOnKeyWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(RedBlackBinarySearchTreeSymbolTableTest, DeleteMinimumWorks) {
    testDeleteMinimumWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(RedBlackBinarySearchTreeSymbolTableTest, DeleteMaximumWorks) {
    testDeleteMaximumWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(RedBlackBinarySearchTreeSymbolTableTest, GetKeys) { testGetKeysWithUnsignedIntAndChar<SymbolTableForTest>(); }

TEST(RedBlackBinarySearchTreeSymbolTableTest, GetKeysInRangeWorks) {
    testGetKeysInRangeInclusiveWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(RedBlackBinarySearchTreeSymbolTableTest, TraverseByPreOrderWorks) {
    SymbolTableForTest symbolTable;
    symbolTable.put(3, 'C');
    symbolTable.put(4, 'D');
    symbolTable.put(5, 'E');
    symbolTable.put(9, 'I');
    symbolTable.put(8, 'H');
    symbolTable.put(7, 'G');

    KeysForTest keysToVerify;
    symbolTable.traverseByPreOrder([&keysToVerify](NodeForTest const& node) { keysToVerify.emplace_back(node.key); });

    KeysForTest expectedKeys{8, 4, 3, 7, 5, 9};  // balanced
    EXPECT_EQ(expectedKeys, keysToVerify);
}

TEST(RedBlackBinarySearchTreeSymbolTableTest, TraverseByInOrderWorks) {
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

TEST(RedBlackBinarySearchTreeSymbolTableTest, TraverseByPostOrderWorks) {
    SymbolTableForTest symbolTable;
    symbolTable.put(3, 'C');
    symbolTable.put(4, 'D');
    symbolTable.put(5, 'E');
    symbolTable.put(9, 'I');
    symbolTable.put(8, 'H');
    symbolTable.put(7, 'G');

    KeysForTest keysToVerify;
    symbolTable.traverseByPostOrder([&keysToVerify](NodeForTest const& node) { keysToVerify.emplace_back(node.key); });

    KeysForTest expectedKeys{3, 5, 7, 4, 9, 8};  // balanced
    EXPECT_EQ(expectedKeys, keysToVerify);
}

}  // namespace algorithm

}  // namespace alba
