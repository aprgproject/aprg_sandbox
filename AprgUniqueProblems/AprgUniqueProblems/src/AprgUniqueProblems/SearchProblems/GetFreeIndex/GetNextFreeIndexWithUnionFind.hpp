#pragma once

#include <AprgUniqueProblems/SearchProblems/GetFreeIndex/GetFreeIndexWithUnionFind.hpp>

namespace alba
{

namespace algorithm
{

template <typename Index>
class GetNextFreeIndexWithUnionFind : public GetFreeIndexWithUnionFind<Index>
{
public:
    using BaseClass = GetFreeIndexWithUnionFind<Index>;
    using UnionFind = typename BaseClass::UnionFind;

    GetNextFreeIndexWithUnionFind(Index const numberOfIndexes)
        : BaseClass(numberOfIndexes)
        , b_numberOfIndexes(BaseClass::m_numberOfIndexes)
        , b_unionFind(BaseClass::m_unionFind)
    {}

    Index getNextFreeIndexAt(Index const index) const
    {
        // This has log(N) running time

        return BaseClass::getFreeIndexAt(index);
    }

    void setAsNotFree(Index const index)
    {
        if(index+1 < b_numberOfIndexes)
        {
            b_unionFind.connect(b_unionFind.getRoot(index+1), index);
        }
    }

private:
    Index & b_numberOfIndexes;
    UnionFind & b_unionFind;
};

}

}
