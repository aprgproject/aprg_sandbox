#pragma once

#include <Algorithm/Search/Common/SegmentTreeUtilities.hpp>
#include <Algorithm/Utilities/IndexHelper.hpp>

#include <functional>
namespace alba {

namespace algorithm {

template <typename Values>
class RangeQueryWithStaticSegmentTree {
public:
    // This supports "selector" and "accumulator" type queries.

    // An ordinary segment tree is static, which means that each node has a fixed position in the array and the tree
    // requires a fixed amount of memory.

    // A segment tree is a data structure that supports two operations: processing a range query and updating an array
    // value. Segment trees can support sum queries, minimum and maximum queries and many other queries so that both
    // operations work in O(logn) time. Compared to a binary indexed tree, the advantage of a segment tree is that it is
    // a more general data structure. While binary indexed trees only support sum queries, segment trees also support
    // other queries. On the other hand, a segment tree requires more memory and is a bit more difficult to implement.

    // Segment trees can support all range queries where it is possible to divide a range into two parts,
    // Calculate the answer separately for both parts and then efficiently combine the answers.

    // Examples of such queries are minimum and maximum, greatest common divisor, and bit operations and, or and xor.

    using Index = int;
    using Value = typename Values::value_type;
    using Function = std::function<Value(Value const&, Value const&)>;
    using Utilities = SegmentTreeUtilities<Index>;

    RangeQueryWithStaticSegmentTree() = default;

    RangeQueryWithStaticSegmentTree(Values const& valuesToCheck, Function const& functionObject)
        : m_startOfChildren(0), m_treeValues(), m_function(functionObject) {
        initialize(valuesToCheck);
    }

    Index getStartOfChildren() const { return m_startOfChildren; }

    Values const& getTreeValues() const { return m_treeValues; }

    Value getValueOnInterval(Index const start, Index const end) const  // bottom to top approach
    {
        // This has log(N) running time
        return getValueOnIntervalFromBottomToTop(start, end);
    }

    Value getValueOnIntervalFromTopToBottom(Index const start, Index const end) const  // top to bottom approach
    {
        // This has log(N) running time
        Value result{};
        if (start <= end && (m_startOfChildren + start) < static_cast<Index>(m_treeValues.size()) &&
            (m_startOfChildren + end) < static_cast<Index>(m_treeValues.size())) {
            result = getValueOnIntervalFromTopToBottom(
                start, end, Utilities::ROOT_PARENT_INDEX, 0, m_startOfChildren);  // startOfChildren is size of base too
        }
        return result;
    }

    void changeValueAtIndex(Index const index, Value const& newValue) {
        // This has log(N) running time
        changeValueAtIndexFromBottomToTop(index, newValue);
    }

protected:
    void initialize(Values const& valuesToCheck) {
        if (!valuesToCheck.empty()) {
            m_startOfChildren = Utilities::getMinimumNumberOfParents(valuesToCheck.size());
            Index totalSize = m_startOfChildren + valuesToCheck.size();

            m_treeValues.resize(totalSize);
            m_treeValues.shrink_to_fit();
            std::copy(
                valuesToCheck.cbegin(), valuesToCheck.cend(),
                m_treeValues.begin() + m_startOfChildren);  // copy children

            Index treeBaseLeft(m_startOfChildren);
            Index treeBaseRight(totalSize - 1);
            while (treeBaseLeft < treeBaseRight)  // fill up parent values
            {
                Index treeBaseRightComplete = treeBaseRight;
                if (Utilities::isALeftChild(treeBaseRight))  // incomplete pair
                {
                    m_treeValues[Utilities::getParent(treeBaseRight)] = m_treeValues[treeBaseRight];
                    treeBaseRightComplete--;
                }
                for (Index treeIndex = treeBaseLeft; treeIndex < treeBaseRightComplete;
                     treeIndex += Utilities::NUMBER_OF_CHILDREN)  // complete pairs
                {
                    m_treeValues[Utilities::getParent(treeIndex)] =
                        m_function(m_treeValues[treeIndex], m_treeValues[treeIndex + 1]);
                }
                treeBaseLeft = Utilities::getParent(treeBaseLeft);
                treeBaseRight = Utilities::getParent(treeBaseRight);
            }
        }
    }

    Value getValueOnIntervalFromBottomToTop(Index const start, Index const end) const {
        // This has log(N) running time
        Value result{};
        Index first(m_startOfChildren + start);
        Index last(m_startOfChildren + end);
        if (first <= last && first < static_cast<Index>(m_treeValues.size()) &&
            last < static_cast<Index>(m_treeValues.size())) {
            result = m_treeValues[first++];
            while (first < last) {
                if (Utilities::isARightChild(first)) {
                    result = m_function(
                        result, m_treeValues[first++]);  // move to next value (right) because current value is added
                }
                if (Utilities::isALeftChild(last)) {
                    result = m_function(
                        result, m_treeValues[last--]);  // move to next value (left) because current value is added
                }
                first = Utilities::getParent(first);
                last = Utilities::getParent(last);
            }
            if (first == last)  // add value if it ends on the same place
            {
                result = m_function(result, m_treeValues[first]);
            }
        }
        return result;
    }

    Value getValueOnIntervalFromTopToBottom(
        Index const startInterval, Index const endInterval, Index const currentChild, Index const baseLeft,
        Index const baseRight) const {
        // This has log(N) running time

        // The parameter k indicates the current position in tree.
        // Initially k equals 1, because we begin at the root of the tree.
        // The range [x, y] corresponds to k and is initially [0,n-1].
        // When calculating the sum, if [x, y] is outside [a,b], the sum is 0, and if [x, y] is completely inside [a,b],
        // the sum can be found in tree. If [x, y] is partially inside [a,b], the search continues recursively to the
        // left and right half of [x, y]. The left half is [x,d] and the right half is [d+1, y] where d =
        // floor((x+y)/2).

        Value result{};
        if (startInterval <= baseLeft && baseRight <= endInterval) {
            result = m_treeValues[currentChild];
        } else {
            Index baseMidPoint = getMidpointOfIndexes(baseLeft, baseRight);
            bool doesLeftPartIntersect = !(endInterval < baseLeft || baseMidPoint < startInterval);
            bool doesRightPartIntersect = !(endInterval < baseMidPoint + 1 || baseRight < startInterval);
            if (doesLeftPartIntersect && doesRightPartIntersect) {
                result = m_function(
                    getValueOnIntervalFromTopToBottom(
                        startInterval, endInterval, Utilities::getLeftChild(currentChild), baseLeft, baseMidPoint),
                    getValueOnIntervalFromTopToBottom(
                        startInterval, endInterval, Utilities::getRightChild(currentChild), baseMidPoint + 1,
                        baseRight));
            } else if (doesLeftPartIntersect) {
                result = getValueOnIntervalFromTopToBottom(
                    startInterval, endInterval, Utilities::getLeftChild(currentChild), baseLeft, baseMidPoint);
            } else if (doesRightPartIntersect) {
                result = getValueOnIntervalFromTopToBottom(
                    startInterval, endInterval, Utilities::getRightChild(currentChild), baseMidPoint + 1, baseRight);
            }
        }
        return result;
    }

    void changeValueAtIndexFromBottomToTop(Index const index, Value const& newValue) {
        // This has log(N) running time
        Index treeIndex(m_startOfChildren + index);
        if (treeIndex < static_cast<Index>(m_treeValues.size())) {
            m_treeValues[treeIndex] = newValue;
            if (m_treeValues.size() > 2) {
                while (treeIndex > 0) {
                    Index parentIndex(Utilities::getParent(treeIndex));
                    if (Utilities::isALeftChild(treeIndex)) {
                        m_treeValues[parentIndex] =
                            m_function(m_treeValues[treeIndex], m_treeValues[treeIndex + 1]);
                    } else {
                        m_treeValues[parentIndex] =
                            m_function(m_treeValues[treeIndex - 1], m_treeValues[treeIndex]);
                    }
                    treeIndex = parentIndex;
                }
                m_treeValues[0] = m_function(m_treeValues[1], m_treeValues[2]);
            } else if (m_treeValues.size() > 1) {
                m_treeValues[0] = m_treeValues[1];
            }
        }
    }

    Index m_startOfChildren;
    Values m_treeValues;
    Function m_function;
};

}  // namespace algorithm

}  // namespace alba
