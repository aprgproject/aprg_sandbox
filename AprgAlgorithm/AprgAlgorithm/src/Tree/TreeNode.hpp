#pragma once

#include <Tree/Tree.hpp>

namespace alba
{

class TreeNode;
using TreeNodeIndexes = std::vector<unsigned int>;

template <typename ObjectType>
class TreeNode
{
    using ObjectInNode = std::unique_ptr<ObjectType>;
public:
    TreeNode(Tree & tree)
        : m_tree(tree)
    {
        m_nodeIndex = m_tree.createNewObjectAndReturnObjectIndex();
    }

    void addChildNode(TreeNodePtr const& childNodePtr)
    {
        m_childNodeIndexes.emplace_back(childIndex);
    }

private:
    unsigned int m_nodeIndex;
    TreeNodeIndexes m_childNodeIndexes;
};


}
