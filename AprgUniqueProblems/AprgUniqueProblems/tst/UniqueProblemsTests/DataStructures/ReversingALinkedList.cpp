#include <UniqueProblems/DataStructures/ReversingALinkedList.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace ReversingALinkedList {

TEST(ReversingALinkedListTest, ThreeNodes) {
    std::unique_ptr<Node> node1(new Node{1, nullptr});
    std::unique_ptr<Node> node2(new Node{2, nullptr});
    std::unique_ptr<Node> node3(new Node{3, nullptr});
    node2->nextPointer = move(node3);
    node1->nextPointer = move(node2);

    std::unique_ptr<Node> result = reverseALinkedList(move(node1));

    EXPECT_EQ(3, result->value);
    result = move(result->nextPointer);
    EXPECT_EQ(2, result->value);
    result = move(result->nextPointer);
    EXPECT_EQ(1, result->value);
    result = move(result->nextPointer);
    EXPECT_FALSE(result);
}

TEST(ReversingALinkedListTest, SevenNodes) {
    std::unique_ptr<Node> node1(new Node{1, nullptr});
    std::unique_ptr<Node> node2(new Node{2, nullptr});
    std::unique_ptr<Node> node3(new Node{3, nullptr});
    std::unique_ptr<Node> node4(new Node{4, nullptr});
    std::unique_ptr<Node> node5(new Node{5, nullptr});
    std::unique_ptr<Node> node6(new Node{6, nullptr});
    std::unique_ptr<Node> node7(new Node{7, nullptr});
    node6->nextPointer = move(node7);
    node5->nextPointer = move(node6);
    node4->nextPointer = move(node5);
    node3->nextPointer = move(node4);
    node2->nextPointer = move(node3);
    node1->nextPointer = move(node2);

    std::unique_ptr<Node> result = reverseALinkedList(move(node1));

    EXPECT_EQ(7, result->value);
    result = move(result->nextPointer);
    EXPECT_EQ(6, result->value);
    result = move(result->nextPointer);
    EXPECT_EQ(5, result->value);
    result = move(result->nextPointer);
    EXPECT_EQ(4, result->value);
    result = move(result->nextPointer);
    EXPECT_EQ(3, result->value);
    result = move(result->nextPointer);
    EXPECT_EQ(2, result->value);
    result = move(result->nextPointer);
    EXPECT_EQ(1, result->value);
    result = move(result->nextPointer);
    EXPECT_FALSE(result);
}

}  // namespace ReversingALinkedList

}  // namespace alba
