#pragma once

#include <Algorithm/UnionFind/WeightedQuickUnionWithVector.hpp>

namespace alba
{

namespace algorithm
{

template <typename Index>
class GetFreeIndexWithUnionFind
{
public:
    using UnionFind = WeightedQuickUnionWithVector<Index>;

    GetFreeIndexWithUnionFind(Index const numberOfIndexes)
        : m_numberOfIndexes(numberOfIndexes)
        , m_unionFind(numberOfIndexes)
    {}

    void setAsFree(Index const index)
    {
        if(index<m_numberOfIndexes && m_unionFind.getRoot(index) != index)
        {
            auto & relativeRoots(m_unionFind.getRelativeRootVectorReference());
            auto & sizesOfRoots(m_unionFind.getSizesOfRootsVectorReference());
            Index relativeRoot(relativeRoots.at(index));

            relativeRoots[index] = index;
            sizesOfRoots[relativeRoot]-=sizesOfRoots[index];
            sizesOfRoots[index]=1U;
        }
    }

protected:

    Index getFreeIndexAt(Index const index)
    {
        // This has log(N) running time
        Index result{};
        if(index<m_numberOfIndexes)
        {
            result = m_unionFind.getRootWithPathCompressionTwoPass(index);
        }
        return result;
    }
    Index m_numberOfIndexes;
    UnionFind m_unionFind;
};
}

}
