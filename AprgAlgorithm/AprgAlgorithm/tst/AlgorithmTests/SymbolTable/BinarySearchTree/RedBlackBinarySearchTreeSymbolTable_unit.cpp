#include <Algorithm/SymbolTable/BinarySearchTree/RedBlackBinarySearchTreeSymbolTable.hpp>
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
using SymbolTableForTest = RedBlackBinarySearchTreeSymbolTable<unsigned int, char>;
using NodeForTest = BinarySearchTreeNode::RedBlackTreeNode<unsigned int, char>;
using KeysForTest = typename SymbolTableForTest::Keys;
}

TEST(RedBlackBinarySearchTreeSymbolTableTest, IsEmptyWorksWhenEmpty){
    testIsEmptyWhenEmptyWithUnsignedIntAndChar<SymbolTableForTest>();
}
TEST(RedBlackBinarySearchTreeSymbolTableTest, IsEmptyWorksWhenNotEmpty)
{
    testIsEmptyWhenNotEmptyWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(RedBlackBinarySearchTreeSymbolTableTest, DoesContainWorks)
{
    testDoesContainWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(RedBlackBinarySearchTreeSymbolTableTest, GetSizeWorksWhenEmpty)
{
    testGetSizeWhenEmptyWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(RedBlackBinarySearchTreeSymbolTableTest, GetSizeWorksWhenNotEmpty)
{
    testGetSizeWhenNotEmptyWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(RedBlackBinarySearchTreeSymbolTableTest, GetWorks)
{
    testGetWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(RedBlackBinarySearchTreeSymbolTableTest, GetRankWorks)
{
    testGetRankWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(RedBlackBinarySearchTreeSymbolTableTest, GetMinimumWorks)
{
    testGetMinimumWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(RedBlackBinarySearchTreeSymbolTableTest, GetMaximumWorks)
{
    testGetMaximumWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(RedBlackBinarySearchTreeSymbolTableTest, SelectAtWorks)
{
    testSelectAtWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(RedBlackBinarySearchTreeSymbolTableTest, GetFloorWorks)
{
    testGetFloorWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(RedBlackBinarySearchTreeSymbolTableTest, GetCeilingWorks)
{
    testGetCeilingWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(RedBlackBinarySearchTreeSymbolTableTest, PutWorks)
{
    testPutWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(RedBlackBinarySearchTreeSymbolTableTest, DeleteBasedOnKeyWorks)
{
    testDeleteBasedOnKeyWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(RedBlackBinarySearchTreeSymbolTableTest, DeleteMinimumWorks)
{
    testDeleteMinimumWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(RedBlackBinarySearchTreeSymbolTableTest, DeleteMaximumWorks)
{
    testDeleteMaximumWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(RedBlackBinarySearchTreeSymbolTableTest, GetKeys)
{
    testGetKeysWithUnsignedIntAndChar<SymbolTableForTest>();;
}

TEST(RedBlackBinarySearchTreeSymbolTableTest, GetKeysInRangeWorks)
{
    testGetKeysInRangeInclusiveWithUnsignedIntAndChar<SymbolTableForTest>();
}

TEST(RedBlackBinarySearchTreeSymbolTableTest, TraverseByPreOrderWorks)
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

    KeysForTest expectedKeys{8U, 4U, 3U, 7U, 5U, 9U}; // balanced search tree
    EXPECT_EQ(expectedKeys, keysToVerify);
}

TEST(RedBlackBinarySearchTreeSymbolTableTest, TraverseByInOrderWorks)
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

TEST(RedBlackBinarySearchTreeSymbolTableTest, TraverseByPostOrderWorks)
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

    KeysForTest expectedKeys{3U, 5U, 7U, 4U, 9U, 8U}; // balanced
    EXPECT_EQ(expectedKeys, keysToVerify);
}

}

}