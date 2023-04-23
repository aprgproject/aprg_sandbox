#pragma once

#include <memory>

namespace alba
{

namespace ReversingALinkedList
{

struct Node
{
    unsigned int value;
    std::unique_ptr<Node> nextPointer;

    // ~Node(); blows up the stack
};

std::unique_ptr<Node> reverseALinkedList(std::unique_ptr<Node> parent);
}

}