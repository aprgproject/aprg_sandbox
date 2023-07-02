#pragma once

#include <Algorithm/Sort/BaseSorter.hpp>

#include <iterator>
#include <utility>

namespace alba {

namespace algorithm {

template <typename Values>
class CocktailShakerSorter : public BaseSorter<Values> {
public:
    CocktailShakerSorter() = default;

    void sort(Values& valuesToSort) const override {
        // Based from https://en.wikipedia.org/wiki/Cocktail_shaker_sort#Pseudocode
        // This can be reimplemented with iterators (for list)
        int lowIndex = 0, highIndex = valuesToSort.size() - 1;
        while (lowIndex <= highIndex) {
            int lowBoundary = highIndex, highBoundary = lowIndex;
            for (int i = lowIndex; i < highIndex; i++) {
                if (valuesToSort[i] > valuesToSort[i + 1]) {
                    std::swap(valuesToSort[i], valuesToSort[i + 1]);
                    highBoundary = i + 1;
                }
            }
            highIndex = highBoundary - 1;
            for (int i = highIndex; i >= lowIndex; i--) {
                if (valuesToSort[i] > valuesToSort[i + 1]) {
                    std::swap(valuesToSort[i], valuesToSort[i + 1]);
                    lowBoundary = i;
                }
            }
            lowIndex = lowBoundary + 1;
        }
    }
};

}  // namespace algorithm

}  // namespace alba

// -> Cocktail shaker sort or bidirectional bubble sort,
// ---> A bubble sort traversing the list alternately from front to back and back to front
// -----> Cocktail shaker sort, also known as bidirectional bubble sort, cocktail sort, shaker sort
// -----> (which can also refer to a variant of selection sort), ripple sort, shuffle sort, or shuttle sort, is an
// extension of bubble sort.
// -----> The algorithm extends bubble sort by operating in two directions.
// -----> While it improves on bubble sort by more quickly moving items to the beginning of the list, it provides only
// marginal performance improvements.
// ---> Like most variants of bubble sort, cocktail shaker sort is used primarily as an educational tool.
// -----> More performant algorithms such as timsort, or merge sort are used by the sorting libraries built into popular
// programming languages such as Python and Java.
// ---> Pseudocode
// -----> The simplest form goes through the whole list each time:
// -------> procedure cocktailShakerSort(A : list of sortable items) is
// ------->     do
// ------->         swapped := false
// ------->         for each i in 0 to length(A) − 2 do:
// ------->             if A[i] > A[i + 1] then // test whether the two elements are in the wrong order
// ------->                 swap(A[i], A[i + 1]) // let the two elements change places
// ------->                 swapped := true
// ------->             end if
// ------->         end for
// ------->         if not swapped then
// ------->             // we can exit the outer loop here if no swaps occurred.
// ------->             break do-while loop
// ------->         end if
// ------->         swapped := false
// ------->         for each i in length(A) − 2 to 0 do:
// ------->             if A[i] > A[i + 1] then
// ------->                 swap(A[i], A[i + 1])
// ------->                 swapped := true
// ------->             end if
// ------->         end for
// ------->     while swapped // if no elements have been swapped, then the list is sorted
// -------> end procedure
// ----> The first rightward pass will shift the largest element to its correct place at the end,
// ------> and the following leftward pass will shift the smallest element to its correct place at the beginning.
// ------> The second complete pass will shift the second largest and second smallest elements to their correct places,
// and so on.
// ------> After i passes, the first i and the last i elements in the list are in their correct positions, and do not
// need to be checked.
// ------> By shortening the part of the list that is sorted each time, the number of operations can be halved (see
// bubble sort).
// ----> This is an example of the algorithm in MATLAB/OCTAVE with the optimization of remembering the last swap index
// and updating the bounds.
// ------> function A = cocktailShakerSort(A)
// ------> % `beginIdx` and `endIdx` marks the first and last index to check
// ------> beginIdx = 1;
// ------> endIdx = length(A) - 1;
// ------> while beginIdx <= endIdx
// ------>     newBeginIdx = endIdx;
// ------>     newEndIdx = beginIdx;
// ------>     for ii = beginIdx:endIdx
// ------>         if A(ii) > A(ii + 1)
// ------>             [A(ii+1), A(ii)] = deal(A(ii), A(ii+1));
// ------>             newEndIdx = ii;
// ------>         end
// ------>     end
// ------>     % decreases `endIdx` because the elements after `newEndIdx` are in correct order
// ------>     endIdx = newEndIdx - 1;
// ------>
// ------>     for ii = endIdx:-1:beginIdx
// ------>         if A(ii) > A(ii + 1)
// ------>             [A(ii+1), A(ii)] = deal(A(ii), A(ii+1));
// ------>             newBeginIdx = ii;
// ------>         end
// ------>     end
// ------>     % increases `beginIdx` because the elements before `newBeginIdx` are in correct order
// ------>     beginIdx = newBeginIdx + 1;
// ------> end
// ------> end
