#include "InvertingABinaryTree.hpp"

using namespace std;

namespace alba
{

namespace InvertingABinaryTree
{

unique_ptr<Node> invertABinaryTree(unique_ptr<Node> parent)
{
    if(parent)
    {
        unique_ptr<Node> newRightChild = move(parent->leftPointer);
        unique_ptr<Node> newLeftChild = move(parent->rightPointer);
        parent->leftPointer = invertABinaryTree(move(newLeftChild));
        parent->rightPointer = invertABinaryTree(move(newRightChild));
    }
    return parent;
}

}

}
