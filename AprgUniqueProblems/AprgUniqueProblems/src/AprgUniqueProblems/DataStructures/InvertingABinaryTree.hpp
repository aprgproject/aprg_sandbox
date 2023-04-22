#pragma once

#include <memory>

namespace alba
{

namespace InvertingABinaryTree
{

struct Node
{
    unsigned int value;
    std::unique_ptr<Node> leftPointer;
    std::unique_ptr<Node> rightPointer;
};

std::unique_ptr<Node> invertABinaryTree(std::unique_ptr<Node> parent);

}


}
