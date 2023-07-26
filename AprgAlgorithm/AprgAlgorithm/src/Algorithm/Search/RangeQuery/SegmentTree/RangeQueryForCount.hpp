#pragma once

#include <Algorithm/Search/RangeQuery/SegmentTree/RangeQueryWithDynamicSegmentTree.hpp>

#include <map>

namespace alba {

namespace algorithm {

template <typename Values>
class RangeQueryForCount {
public:
    // Instead of single values, nodes in a segment tree can also contain data structures that maintain information
    // about the corresponding ranges. In such a tree, the operations take O(f(n)*logn) time, where f (n) is the time
    // needed for processing a single node during an operation.

    // As an example, consider a segment tree that supports queries of the form "how many times does an element x appear
    // in the range [a,b]?"

    // To support such queries, we build a segment tree where each node is assigned a data structure
    // that can be asked how many times any element x appears in the corresponding range.
    // Using this tree, the answer to a query can be calculated by combining the results from the nodes that belong to
    // the range.

    // We can build the tree so that each node contains a map structure.
    // In this case, the time needed for processing each node is O(logn),
    // so the total time complexity of a query is O(log2 n).
    // The tree uses O(nlogn) memory, because there are O(logn) levels and each level contains O(n) elements.

    using Index = int;
    using Count = int;
    using Value = typename Values::value_type;
    using ValueToCountMap = std::map<Value, Count>;
    using ValueToCountMaps = std::vector<ValueToCountMap>;
    using SegmentTree = RangeQueryWithDynamicSegmentTree<ValueToCountMaps>;
    using Function = typename SegmentTree::Function;

    RangeQueryForCount(Values const& valuesToCheck)
        : m_valueToCountMapSegmentTree(getValueToCountMaps(valuesToCheck), getFunctionForSegmentTree()) {}

    Count getCountOfThisValueOnInterval(Index const start, Index const end, Value const& value) const {
        Count result(0);
        ValueToCountMap valueToCountMap(m_valueToCountMapSegmentTree.getValueOnInterval(start, end));
        auto it = valueToCountMap.find(value);
        if (it != valueToCountMap.cend()) {
            result = it->second;
        }
        return result;
    }

    void changeValueAtIndex(Index const index, Value const& newValue) {
        m_valueToCountMapSegmentTree.changeValueAtIndex(index, ValueToCountMap{{newValue, 1}});
    }

private:
    ValueToCountMaps getValueToCountMaps(Values const& valuesToCheck) const {
        ValueToCountMaps result;
        result.reserve(valuesToCheck.size());
        std::transform(
            valuesToCheck.cbegin(), valuesToCheck.cend(), std::back_inserter(result), [](Value const& value) {
                return ValueToCountMap{{value, 1}};
            });
        return result;
    }

    Function getFunctionForSegmentTree() const {
        return [](ValueToCountMap const& map1, ValueToCountMap const& map2) {
            ValueToCountMap result(map1);
            for (auto const& [value, count] : map2) {
                auto valueIt = result.find(value);
                if (valueIt != result.end()) {
                    valueIt->second += count;
                } else {
                    result.emplace(value, count);
                }
            }
            return result;
        };
    }

    SegmentTree m_valueToCountMapSegmentTree;
};

}  // namespace algorithm

}  // namespace alba
