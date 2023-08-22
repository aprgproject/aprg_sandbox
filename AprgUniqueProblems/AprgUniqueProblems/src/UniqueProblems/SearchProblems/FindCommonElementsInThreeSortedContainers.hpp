#pragma once

namespace alba {

namespace algorithm {

template <typename Values>
class FindCommonElementsInThreeSortedContainers {
public:
    using Value = typename Values::value_type;

    FindCommonElementsInThreeSortedContainers()  // values can be unsorted
    {}

    Values getCommonElements(Values const& values1, Values const& values2, Values const& values3) {
        Values result;
        // reserve? not needed for now
        if (!values1.empty() && !values2.empty() && !values3.empty()) {
            for (auto it1 = values1.cbegin(), it2 = values2.cbegin(), it3 = values3.cbegin();
                 it1 != values1.cend() && it2 != values2.cend() && it3 != values3.cend();) {
                if (*it1 == *it2 && *it2 == *it3) {
                    result.emplace_back(*it1);
                    it1++, it2++, it3++;
                } else if (*it1 < *it2) {
                    it1++;
                } else if (*it2 < *it3) {
                    it2++;
                } else {
                    it3++;
                }
            }
        }
        return result;
    }
};

}  // namespace algorithm

}  // namespace alba

// Given three arrays sorted in non-decreasing order, print all common elements in these arrays.
// We are given two arrays ar1[0…m-1] and ar2[0..n-1] and a number x,
// we need to find the pair ar1[i] + ar2[j] such that absolute value of (ar1[i] + ar2[j] – x) is minimum.

// A simple solution is to first find intersection of two arrays and store the intersection in a temporary array,
// then find the intersection of third array and temporary array.
// Time complexity of this solution is O(n1 + n2 + n3) where n1, n2 and n3 are sizes of ar1[], ar2[] and ar3[]
// respectively. The above solution requires extra space and two loops, we can find the common elements using a single
// loop and without extra space. The idea is similar to intersection of two arrays. Like two arrays loop, we run a loop
// and traverse three arrays. Let the current element traversed in ar1[] be x, in ar2[] be y and in ar3[] be z. We can
// have following cases inside the loop:
// -> If x, y and z are same, we can simply print any of them as common element and move ahead in all three arrays.
// -> Else If x < y, we can move ahead in ar1[] as x cannot be a common element.
// -> Else If x > z and y > z), we can simply move ahead in ar3[] as z cannot be a common element.-
