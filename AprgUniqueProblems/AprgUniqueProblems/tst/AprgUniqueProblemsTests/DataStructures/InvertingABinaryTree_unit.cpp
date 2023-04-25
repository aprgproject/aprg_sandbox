#include <AprgUniqueProblems/DataStructures/InvertingABinaryTree.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace InvertingABinaryTree {

TEST(InvertingABinaryTreeTest, ThreeNodes) {
    std::unique_ptr<Node> node1(new Node{1, nullptr, nullptr});
    std::unique_ptr<Node> node2(new Node{2, nullptr, nullptr});
    std::unique_ptr<Node> node3(new Node{3, nullptr, nullptr});
    node2->leftPointer = move(node1);
    node2->rightPointer = move(node3);

    std::unique_ptr<Node> result = invertABinaryTree(move(node2));

    EXPECT_EQ(2U, result->value);
    EXPECT_EQ(3U, result->leftPointer->value);
    EXPECT_EQ(1U, result->rightPointer->value);
    EXPECT_FALSE(result->leftPointer->leftPointer);
    EXPECT_FALSE(result->leftPointer->rightPointer);
    EXPECT_FALSE(result->rightPointer->leftPointer);
    EXPECT_FALSE(result->rightPointer->rightPointer);
}

TEST(InvertingABinaryTreeTest, SevenNodes) {
    std::unique_ptr<Node> node1(new Node{1, nullptr, nullptr});
    std::unique_ptr<Node> node2(new Node{2, nullptr, nullptr});
    std::unique_ptr<Node> node3(new Node{3, nullptr, nullptr});
    std::unique_ptr<Node> node4(new Node{4, nullptr, nullptr});
    std::unique_ptr<Node> node5(new Node{5, nullptr, nullptr});
    std::unique_ptr<Node> node6(new Node{6, nullptr, nullptr});
    std::unique_ptr<Node> node7(new Node{7, nullptr, nullptr});
    node2->leftPointer = move(node1);
    node2->rightPointer = move(node3);
    node6->leftPointer = move(node5);
    node6->rightPointer = move(node7);
    node4->leftPointer = move(node2);
    node4->rightPointer = move(node6);

    std::unique_ptr<Node> result = invertABinaryTree(move(node4));

    EXPECT_EQ(4U, result->value);
    EXPECT_EQ(6U, result->leftPointer->value);
    EXPECT_EQ(2U, result->rightPointer->value);
    EXPECT_EQ(7U, result->leftPointer->leftPointer->value);
    EXPECT_EQ(5U, result->leftPointer->rightPointer->value);
    EXPECT_EQ(3U, result->rightPointer->leftPointer->value);
    EXPECT_EQ(1U, result->rightPointer->rightPointer->value);
}

}  // namespace InvertingABinaryTree

}  // namespace alba
