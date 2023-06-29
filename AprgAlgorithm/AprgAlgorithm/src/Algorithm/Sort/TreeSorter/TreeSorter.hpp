#pragma once

#include <Algorithm/Sort/BaseSorter.hpp>

#include <set>

namespace alba {

namespace algorithm {

template <typename Values>
class TreeSorter : public BaseSorter<Values> {
public:
    using Value = typename Values::value_type;
    TreeSorter() = default;

    void sort(Values& valuesToSort) const override {
        std::multiset<Value> tree(valuesToSort.cbegin(), valuesToSort.cend());

        std::copy(tree.cbegin(), tree.cend(), valuesToSort.begin());
    }
};

}  // namespace algorithm

}  // namespace alba

// -> Tree sort (binary tree sort):
// ---> This build binary tree, then traverse it to create sorted list
// ---> A tree sort is a sort algorithm that builds a binary search tree from the elements to be sorted,
// -----> and then traverses the tree (in-order) so that the elements come out in sorted order.
// -----> Its typical use is sorting elements online: after each insertion, the set of elements seen so far is available
// in sorted order.
// ---> Tree sort can be used as a one-time sort, but it is equivalent to quicksort as both recursively partition the
// elements based on a pivot,
// -----> and since quicksort is in-place and has lower overhead, tree sort has few advantages over quicksort.
// -----> It has better worst case complexity when a self-balancing tree is used, but even more overhead.
