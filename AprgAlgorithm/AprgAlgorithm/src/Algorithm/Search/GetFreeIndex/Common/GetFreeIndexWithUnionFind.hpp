#pragma once

#include <Algorithm/UnionFind/QuickUnionWithPathCompressionWithVector.hpp>

namespace alba
{
namespace algorithm
{

template <typename Index>
class GetFreeIndexWithUnionFind
{
public:
    using UnionFind = QuickUnionWithPathCompressionWithVector<Index>;

    GetFreeIndexWithUnionFind(Index const numberOfIndexes)
        : m_numberOfIndexes(numberOfIndexes)        , m_unionFind(numberOfIndexes)
    {}

protected:

    Index getFreeIndexAt(Index const index)
    {
        Index result{};
        if(index<m_numberOfIndexes)
        {            result = m_unionFind.getRootWithPathCompressionTwoPass(index);
        }
        return result;
    }

    Index m_numberOfIndexes;
    UnionFind m_unionFind;
};

}

}
