#pragma once

#include <Algorithm/Sort/BaseSorter.hpp>

#include <iterator>
#include <utility>

namespace alba {

namespace algorithm {

template <typename Values>
class OddEvenSorter : public BaseSorter<Values> {
public:
    OddEvenSorter() = default;

    void sort(Values& valuesToSort) const override {
        // Based from https://en.wikipedia.org/wiki/Cocktail_shaker_sort#Pseudocode

        bool didSwapHappened(true);
        while (didSwapHappened) {
            didSwapHappened = false;
            int lastIndex(valuesToSort.size() - 1);
            for (int i = 1; i < lastIndex; i += 2) {
                if (valuesToSort[i] > valuesToSort[i + 1]) {
                    std::swap(valuesToSort[i], valuesToSort[i + 1]);
                    didSwapHappened = true;
                }
            }
            for (int i = 0; i < lastIndex; i += 2) {
                if (valuesToSort[i] > valuesToSort[i + 1]) {
                    std::swap(valuesToSort[i], valuesToSort[i + 1]);
                    didSwapHappened = true;
                }
            }
        }
    }
};

}  // namespace algorithm

}  // namespace alba

// -> Odd–even sort
// ---> In computing, an odd–even sort or odd–even transposition sort (also known as brick sort[1][self-published
// source] or parity sort)
// -----> is a relatively simple sorting algorithm, developed originally for use on parallel processors with local
// interconnections.
// -----> It is a comparison sort related to bubble sort, with which it shares many characteristics.
// -----> It functions by comparing all odd/even indexed pairs of adjacent elements in the list and,
// -----> if a pair is in the wrong order (the first is larger than the second) the elements are switched.
// -----> The next step repeats this for even/odd indexed pairs (of adjacent elements).
// -----> Then it alternates between odd/even and even/odd steps until the list is sorted.
// ---> Sorting on processor arrays
// -----> On parallel processors, with one value per processor and only local left–right neighbor connections,
// -------> the processors all concurrently do a compare–exchange operation with their neighbors, alternating between
// odd–even and even–odd pairings.
// -------> This algorithm was originally presented, and shown to be efficient on such processors, by Habermann in 1972.
// -----> The algorithm extends efficiently to the case of multiple items per processor.
// -------> In the Baudet–Stevenson odd–even merge-splitting algorithm, each processor sorts its own sublist at each
// step,
// -------> using any efficient sort algorithm, and then performs a merge splitting, or transposition–merge,
// -------> operation with its neighbor, with neighbor pairing alternating between odd–even and even–odd on each
// step.[3]
// ---> Algorithm
// -----> The single-processor algorithm, like bubblesort, is simple but not very efficient. Here a zero-based index is
// assumed:
// -------> function oddEvenSort(list) {
// ------->   function swap(list, i, j) {
// ------->     var temp = list[i];
// ------->     list[i] = list[j];
// ------->     list[j] = temp;
// ------->   }
// ------->   var sorted = false;
// ------->   while (!sorted) {
// ------->     sorted = true;
// ------->     for (var i = 1; i < list.length - 1; i += 2) {
// ------->       if (list[i] > list[i + 1]) {
// ------->         swap(list, i, i + 1);
// ------->         sorted = false;
// ------->       }
// ------->     }
// ------->     for (var i = 0; i < list.length - 1; i += 2) {
// ------->       if (list[i] > list[i + 1]) {
// ------->         swap(list, i, i + 1);
// ------->         sorted = false;
// ------->       }
// ------->     }
// ------->   }
// -------> }
// ---> Batcher's odd–even mergesort
// -----> A related but more efficient sort algorithm is the Batcher odd–even mergesort, using compare–exchange
// operations and perfect-shuffle operations.
// -----> Batcher's method is efficient on parallel processors with long-range connections.
