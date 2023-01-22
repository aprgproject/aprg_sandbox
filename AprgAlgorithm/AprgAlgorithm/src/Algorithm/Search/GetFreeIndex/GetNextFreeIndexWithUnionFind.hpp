#pragma once

#include <Algorithm/UnionFind/UnionFindForFreeIndex.hpp>

namespace alba
{

namespace algorithm
{

template <typename Index>
class GetNextFreeIndexWithUnionFind
{
public:
    using UnionFind = UnionFindForFreeIndex<Index>;

    GetNextFreeIndexWithUnionFind(Index const numberOfIndexes)
        : m_numberOfIndexes(numberOfIndexes)
        , m_unionFind(numberOfIndexes)
    {}

    Index getNextFreeIndexAt(Index const index)
    {
        Index result{};
        if(index<m_numberOfIndexes)
        {
            result = m_unionFind.getRootWithPathCompression(index);
        }
        return result;
    }

    void setAsNotFree(Index const index)
    {
        if(index+1 < m_numberOfIndexes)
        {
            m_unionFind.connect(index, index+1);
        }
    }

    void setAsFree(Index const index)
    {
        // NOTE: This is linear

        Index rootOfIndex(m_unionFind.getRoot(index));
        if(index<m_numberOfIndexes && rootOfIndex != index)
        {
            auto & relativeRoots(m_unionFind.getRelativeRootVectorReference());

            relativeRoots[index] = index;
            for(Index i=0; i<index; i++)
            {
                if(relativeRoots.at(i) == rootOfIndex)
                {
                    relativeRoots[i] = index;
                }
            }
        }
    }

private:
    Index m_numberOfIndexes;
    UnionFind m_unionFind;
};

}

}
