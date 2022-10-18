#pragma once

#include <memory>

namespace alba
{

namespace algorithm
{

template <typename Index, typename Value>
struct DynamicSegmentTreeNode
{
    Value value;
    std::unique_ptr<DynamicSegmentTreeNode> leftChildPointer;
    std::unique_ptr<DynamicSegmentTreeNode> rightChildPointer;
};

}

}
