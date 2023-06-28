#pragma once

#include <Algorithm/Search/RangeQuery/SegmentTree/RangeQueryWithStaticSegmentTree.hpp>
#include <Algorithm/Utilities/IndexHelper.hpp>

namespace alba {
namespace algorithm {

template <typename Indexes>class GetAccumulatedNextFreeIndexWithSegmentTree {
public:
    using Index = typename Indexes::value_type;
    using Utilities = SegmentTreeUtilities<Index>;
    using SegmentTree = RangeQueryWithStaticSegmentTree<Indexes>;

    GetAccumulatedNextFreeIndexWithSegmentTree(Index const numberOfIndexes)
        : m_segmentTree(Indexes(numberOfIndexes, 1), std::plus<Index>()),
          m_startOfChildren(m_segmentTree.getStartOfChildren()),
          m_treeSums(m_segmentTree.getTreeValues()) {}

    Index getNextFreeIndexAt(Index const index) const {
        // This has log(N) running time

        Index result{};
        if (m_startOfChildren + index < static_cast<Index>(m_treeSums.size())) {
            result = getNextFreeIndexAt(
                index, Utilities::ROOT_PARENT_INDEX, 0, m_startOfChildren);  // startOfChildren is size of base too
        }
        return result;
    }

    void setAsNotFree(Index const index) { m_segmentTree.changeValueAtIndex(index, 0); }

    void setAsFree(Index const index) { m_segmentTree.changeValueAtIndex(index, 1); }

private:
    Index getNextFreeIndexAt(
        Index const index, Index const currentChild, Index const baseLeft, Index const baseRight) const {
        // This has log(N) running time

        Index result{};
        if (index + 1 == m_treeSums[currentChild] &&
            m_startOfChildren + baseRight < static_cast<Index>(m_treeSums.size()) &&
            m_treeSums[m_startOfChildren + baseRight] != 0) {
            result = baseRight;
        } else if (
            index == 0 && m_startOfChildren + baseLeft < static_cast<Index>(m_treeSums.size()) &&
            m_treeSums[m_startOfChildren + baseLeft] != 0) {
            result = baseLeft;
        } else {
            Index leftChild = Utilities::getLeftChild(currentChild);
            if (leftChild < static_cast<Index>(m_treeSums.size())) {
                Index leftChildSum = m_treeSums[leftChild];
                Index baseMidPoint = getMidpointOfIndexes(baseLeft, baseRight);
                if (index + 1 <= leftChildSum) {
                    result = getNextFreeIndexAt(index, leftChild, baseLeft, baseMidPoint);
                } else {
                    result = getNextFreeIndexAt(
                        index - leftChildSum, Utilities::getRightChild(currentChild), baseMidPoint + 1, baseRight);
                }
            }
        }
        return result;
    }

    SegmentTree m_segmentTree;
    Index const m_startOfChildren;
    Indexes const& m_treeSums;
};

}  // namespace algorithm

}  // namespace alba
