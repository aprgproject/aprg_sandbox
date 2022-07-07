#include <Algorithm/SymbolTable/BinarySearchTree/BinarySearchTreeSymbolTable.hpp>
#include <AlgorithmTests/SymbolTable/Utilities/CommonTestsWithSymbolTable.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithSymbolTable;
using namespace std;


namespace alba
{

namespace algorithm
{

namespace
{
using SymbolTableForTest = BinarySearchTreeSymbolTable<unsigned int, char>;
using NodeForTest = BinarySearchTreeNode::BasicTreeNode<unsigned int, char>;
using KeysForTest = typename SymbolTableForTest::Keys;
}

TEST(BinarySearchTreeSymbolTableTest, IsEmptyWorksWhenEmpty)
{
    testIsEmptyWhenEmptyWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(BinarySearchTreeSymbolTableTest, IsEmptyWorksWhenNotEmpty)
{
    testIsEmptyWhenNotEmptyWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(BinarySearchTreeSymbolTableTest, DoesContainWorks)
{
    testDoesContainWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(BinarySearchTreeSymbolTableTest, GetSizeWorksWhenEmpty)
{
    testGetSizeWhenEmptyWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(BinarySearchTreeSymbolTableTest, GetSizeWorksWhenNotEmpty)
{
    testGetSizeWhenNotEmptyWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(BinarySearchTreeSymbolTableTest, GetWorks)
{
    testGetWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(BinarySearchTreeSymbolTableTest, GetRankWorks)
{
    testGetRankWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(BinarySearchTreeSymbolTableTest, GetMinimumWorks)
{
    testGetMinimumWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(BinarySearchTreeSymbolTableTest, GetMaximumWorks)
{
    testGetMaximumWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(BinarySearchTreeSymbolTableTest, SelectAtWorks)
{
    testSelectAtWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(BinarySearchTreeSymbolTableTest, GetFloorWorks)
{
    testGetFloorWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(BinarySearchTreeSymbolTableTest, GetCeilingWorks)
{
    testGetCeilingWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(BinarySearchTreeSymbolTableTest, PutWorks)
{
    testPutWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(BinarySearchTreeSymbolTableTest, DeleteBasedOnKeyWorks)
{
    testDeleteBasedOnKeyWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(BinarySearchTreeSymbolTableTest, DeleteMinimumWorks)
{
    testDeleteMinimumWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(BinarySearchTreeSymbolTableTest, DeleteMaximumWorks)
{
    testDeleteMaximumWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(BinarySearchTreeSymbolTableTest, GetKeys)
{
    testGetKeysWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(BinarySearchTreeSymbolTableTest, GetKeysInRangeWorks)
{
    testGetKeysInRangeInclusiveWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(BinarySearchTreeSymbolTableTest, GetRootWorks)
{
    SymbolTableForTest symbolTable;
    symbolTable.put(8U, 'H');

    auto const& expectedRoot(symbolTable.getRoot());

    NodeForTest node{8U, 'H', nullptr, nullptr, 1U};
    ASSERT_TRUE(expectedRoot);
    EXPECT_EQ(node.key, expectedRoot->key);
    EXPECT_EQ(node.value, expectedRoot->value);
    EXPECT_EQ(node.left, expectedRoot->left);
    EXPECT_EQ(node.right, expectedRoot->right);
    EXPECT_EQ(node.numberOfNodesOnThisSubTree, expectedRoot->numberOfNodesOnThisSubTree);
}

TEST(BinarySearchTreeSymbolTableTest, TraverseByPreOrderWorks)
{
    SymbolTableForTest symbolTable;
    symbolTable.put(3U, 'C');
    symbolTable.put(4U, 'D');
    symbolTable.put(5U, 'E');
    symbolTable.put(9U, 'I');
    symbolTable.put(8U, 'H');
    symbolTable.put(7U, 'G');

    KeysForTest keysToVerify;
    symbolTable.traverseByPreOrder([&keysToVerify](NodeForTest const& node)
    {
        keysToVerify.emplace_back(node.key);
    });

    KeysForTest expectedKeys{3U, 4U, 5U, 9U, 8U, 7U}; // not balanced
    EXPECT_EQ(expectedKeys, keysToVerify);
}

TEST(BinarySearchTreeSymbolTableTest, TraverseByInOrderWorks)
{
    SymbolTableForTest symbolTable;
    symbolTable.put(3U, 'C');
    symbolTable.put(4U, 'D');
    symbolTable.put(5U, 'E');
    symbolTable.put(9U, 'I');
    symbolTable.put(8U, 'H');
    symbolTable.put(7U, 'G');

    KeysForTest keysToVerify;
    symbolTable.traverseByInOrder([&keysToVerify](NodeForTest const& node)
    {
        keysToVerify.emplace_back(node.key);
    });

    KeysForTest expectedKeys{3U, 4U, 5U, 7U, 8U, 9U};
    EXPECT_EQ(expectedKeys, keysToVerify);
}

TEST(BinarySearchTreeSymbolTableTest, TraverseByPostOrderWorks)
{
    SymbolTableForTest symbolTable;
    symbolTable.put(3U, 'C');
    symbolTable.put(4U, 'D');
    symbolTable.put(5U, 'E');
    symbolTable.put(9U, 'I');
    symbolTable.put(8U, 'H');
    symbolTable.put(7U, 'G');

    KeysForTest keysToVerify;
    symbolTable.traverseByPostOrder([&keysToVerify](NodeForTest const& node)
    {
        keysToVerify.emplace_back(node.key);
    });

    KeysForTest expectedKeys{7U, 8U, 9U, 5U, 4U, 3U}; // not balanced
    EXPECT_EQ(expectedKeys, keysToVerify);
}

}

}
