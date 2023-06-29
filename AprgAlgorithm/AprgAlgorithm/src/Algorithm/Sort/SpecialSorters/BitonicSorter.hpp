#pragma once

#include <Algorithm/Sort/BaseSorter.hpp>

#include <utility>

namespace alba {

namespace algorithm {

template <typename Values>
class BitonicSorter : public BaseSorter<Values> {
public:
    BitonicSorter() = default;

    void sort(Values& valuesToSort) const override {
        for (unsigned int k = 2; k <= valuesToSort.size(); k *= 2) {
            for (unsigned int j = k / 2; j > 0; j /= 2) {
                for (unsigned int i = 0; i < valuesToSort.size(); i++) {
                    unsigned int l = i ^ j;
                    if (l > i && l < valuesToSort.size()) {
                        if (((i & k) == 0 && valuesToSort[i] > valuesToSort[l]) ||
                            ((i & k) != 0 && valuesToSort[i] < valuesToSort[l])) {
                            std::swap(valuesToSort[i], valuesToSort[l]);
                        }
                    }
                }
            }
        }
    }
};

}  // namespace algorithm

}  // namespace alba

// -> Bitonic sorter
// ---> Bitonic mergesort is a parallel algorithm for sorting. It is also used as a construction method for building a
// sorting network.
// -----> The algorithm was devised by Ken Batcher. The resulting sorting networks consist of O(n log(n)^2) comparators
// and have a delay of O(n log(n)^2), where n is the number of items to be sorted.[1]
// ---> A sorted sequence is a monotonically non-decreasing (or non-increasing) sequence.
// -----> A bitonic sequence is a sequence with x0 ≤ ⋯ ≤ xk ≥ ⋯ ≥ xn−  for some k, 0 ≤ k < n, or a circular shift of
// such a sequence.
// ---> Implementation
// -----> The following is a recursion-free implementation of the bitonic mergesort in C-like pseudocode:[2]
// -------> // given an array arr of length n, this code sorts it in place
// -------> // all indices run from 0 to n-1
// -------> for (k = 2; k <= n; k *= 2) // k is doubled every iteration
// ------->     for (j = k/2; j > 0; j /= 2) // j is halved at every iteration, with truncation of fractional parts
// ------->         for (i = 0; i < n; i++)
// ------->             l = bitwiseXOR (i, j); // in C-like languages this is "i ^ j"
// ------->             if (l > i)
// ------->                 if (  (bitwiseAND (i, k) == 0) AND (arr[i] > arr[l])
// ------->                    OR (bitwiseAND (i, k) != 0) AND (arr[i] < arr[l]) )
// ------->                       swap the elements arr[i] and arr[l]
//
