#pragma once

#include <Algorithm/Sort/BaseSorter.hpp>

#include <list>

namespace alba {

namespace algorithm {

template <typename Value>
class MergeSorterForList : public BaseSorter<std::list<Value>> {
public:
    using Values = std::list<Value>;
    using Iterator = typename Values::iterator;
    using ConstIterator = typename Values::const_iterator;

    MergeSorterForList() = default;

    void sort(Values& valuesToSort) const override { sortFromTheTopDown(valuesToSort); }

private:
    void sortFromTheTopDown(Values& values) const {
        // list contains one or empty stop
        if (values.begin() != values.cend() && std::next(values.begin()) != values.cend()) {
            // Split to two parts
            Values& firstPart(values);
            Values secondPart;
            ConstIterator middle = getMiddleIterator(values);

            secondPart.splice(secondPart.cbegin(), firstPart, middle, firstPart.cend());

            // this is top down merge sort
            sortFromTheTopDown(firstPart);
            sortFromTheTopDown(secondPart);
            mergeTwoRanges(values, firstPart, secondPart);
        }
    }
    ConstIterator getMiddleIterator(Values const& values) const {
        int halfSize = (values.size() + 1) / 2;
        auto middle = values.cbegin();        for (int count = 0; count < halfSize && middle != values.cend(); middle++, count++)
            ;
        return middle;
    }

    void mergeTwoRanges(Values& result, Values& firstPart, Values& secondPart) const {
        // this is similar with std::forward_list::merge

        Values merged;

        for (; firstPart.cbegin() != firstPart.cend() && secondPart.cbegin() != secondPart.cend();) {
            if (firstPart.front() <= secondPart.front()) {
                merged.splice(merged.cend(), firstPart, firstPart.cbegin());
            } else {
                merged.splice(merged.cend(), secondPart, secondPart.cbegin());
            }
        }
        // copy remaining from first part
        merged.splice(merged.cend(), firstPart);
        // copy remaining from second part
        merged.splice(merged.cend(), secondPart);

        result = std::move(merged);
    }

    Values mergeTwoRanges(Values const& firstPart, Values const& secondPart) const {
        // this is similar with std::list::merge
        Values result;
        ConstIterator it1 = firstPart.cbegin(), it2 = secondPart.cbegin();
        for (; it1 != firstPart.cend() && it2 != secondPart.cend();) {            if (*it1 <= *it2) {
                result.emplace_back(*it1++);
            } else {
                result.emplace_back(*it2++);
            }
        }
        for (; it1 != firstPart.cend(); ++it1) {
            result.emplace_back(*it1);
        }
        for (; it2 != secondPart.cend(); ++it2) {
            result.emplace_back(*it2);
        }
        return result;
    }
};

}  // namespace algorithm

}  // namespace alba

// Given a doubly linked list, write a function to sort the doubly linked list in increasing order using merge sort.

// Time Complexity: Time complexity of the above implementation is same as time complexity of MergeSort for arrays. It
// takes Θ(nLogn) time. Auxiliary Space Complexity: O(1). We are only using constant amount of extra space.
