#pragma once

#include <Algorithm/Sort/BaseSorter.hpp>
#include <Algorithm/Sort/QuickSorter/QuickSorterUtilities.hpp>

namespace alba {

namespace algorithm {

template <typename Values>
class QuickSorter : public BaseSorter<Values> {
public:
    QuickSorter(PivotType const pivotType) : m_pivotType(pivotType) {}

    void sort(Values& valuesToSort) const override {
        if (!valuesToSort.empty()) {
            // You can randomize inputs here to remove dependence on input
            // (quick sort works best if input is not sorted) std::shuffle should help
            sort(valuesToSort, 0, valuesToSort.size() - 1);
        }
    }

private:
    void sort(Values& valuesToSort, int const lowIndex, int const highIndex) const {
        if (lowIndex < highIndex) {
            int partitionIndex = partitionAndGetPartitionIndex(valuesToSort, lowIndex, highIndex, m_pivotType);
            if (lowIndex < partitionIndex) {
                // recursively sort/partition the low part without the partition index
                sort(valuesToSort, lowIndex, partitionIndex - 1);
            }
            if (partitionIndex < highIndex) {
                // recursively sort/partition the high part without the partition index
                sort(valuesToSort, partitionIndex + 1, highIndex);
            }
        }
    }

private:
    PivotType m_pivotType;
};

}  // namespace algorithm

}  // namespace alba

// Quicksort is an in-place sorting algorithm
// Quicksort does partitioning in place so there is no extra cost of memory for sorting
// Having some extra memory can make quick sort stable (but its not worth the cost)

// Quicksort is faster than merge sort -> Lesson 2 : Great algorithms are better than good ones.

// Proposition: The average number of compares CN to quicksort an array of N distinct keys is 2N*ln(N) and the number of
// exchanges is (1/3)N*ln(N). Proof: Check for recurrence

// Best case: Partitions split at the middle and continuously divide the problem by half. The running time its
// ~N*log2(N) Worst case: Partitions are in the edge so it continuous divide the problem one element at a time. The
// running time is about (1/2)N^2 At worst case, quick sort is quadratic. But having an initial random shuffle makes
// this really unlikely (lightning bolt odds). At average case, quicksort has 39% more compares (1.39 N*log2(N)), but
// still faster because of less data movement.

// The initial random shuffle provides probabilistic guarantee against the worst case.
// It also provides the basis for a math model that can be validated with experiments (because probability of the
// partition can be computed).

// Not stable -> Proof by counter example: Long distance swap might move an item past some equal item

// Practical improvements:
// -> Cut off to insertion sort when the subarrays becomes too small (~10 items). It can improve the running time ~20%.
// Not implemented above.
// -> Stop at small arrays and do one insertion sort at the end. Not implemented above.
// -> Use the median as the partition value. Not worth it for large sample but median of 3 is worth it.
// ---> Median of 3 means gets the median at lowest, middle and highest index. Sorting these 3 indexes also help next
// partitions.
// ---> It can improve the running time ~10%. Not implemented above.

// Duplicate keys:
// -> Runs in quadratic time if all equal elements are put on one side (not splitted properly).
// ---> Consequence is that partitions with equal items are reduced one by one (instead of halving the partition on
// average)
// ---> In the implementation above, divides the items on the middle as much as possible even if there are equal keys.
// ---> In 1990s, a C user found this defect on quick sort implementation in C (quadratic time for large files with
// equal keys)
// -----> This problematic algorithm is the standard found in a lot of text books.
// ---> Why dont we put all the equal items in place in the middle and process other items -> This is quick sort with 3
// way partitioning.

// Other discussions
// Like Merge Sort, QuickSort is a Divide and Conquer algorithm.

// It picks an element as pivot and partitions the given array around the picked pivot.
// There are many different versions of quickSort that pick pivot in different ways.
// -> Always pick first element as pivot.
// -> Always pick last element as pivot
// -> Pick a random element as pivot.
// -> Pick median as pivot.

// The key process in quickSort is partition().
// Target of partitions is, given an array and an element x of array as pivot,
// put x at its correct position in sorted array and put all smaller elements (smaller than x) before x,
// and put all greater elements (greater than x) after x.
// All this should be done in linear time.

// Analysis of QuickSort
// Time taken by QuickSort, in general, can be written as following.
// -> T(n) = T(k) + T(n-k-1) + \theta(n)

// The first two terms are for two recursive calls, the last term is for the partition process.
// "k" is the number of elements which are smaller than pivot.
// The time taken by QuickSort depends upon the input array and partition strategy.

// Following are three cases:

// Worst Case:
// The worst case occurs when the partition process always picks greatest or smallest element as pivot.
// If we consider above partition strategy where last element is always picked as pivot,
// the worst case would occur when the array is already sorted in increasing or decreasing order.
// Following is recurrence for worst case.
// -> T(n) = T(0) + T(n-1) + \theta(n)
// -> which is equivalent to
// -> T(n) = T(n-1) + \theta(n)
// The solution of above recurrence is  \theta (n2).

// Best Case:
// The best case occurs when the partition process always picks the middle element as pivot.
// Following is recurrence for best case.
// -> T(n) = 2T(n/2) + \theta(n)
// The solution of above recurrence is \theta (nLogn).
// It can be solved using case 2 of Master Theorem.

// Average Case:
// To do average case analysis, we need to consider all possible permutation of array
// and calculate time taken by every permutation which doesn’t look easy.
// We can get an idea of average case by considering the case when partition puts O(n/9) elements in one set and
// O(9n/10) elements in other set. Following is recurrence for this case.
// -> T(n) = T(n/9) + T(9n/10) + \theta(n)
// The solution of above recurrence is also O(nLogn)
// Although the worst case time complexity of QuickSort is O(n2) which is more than many other sorting algorithms like
// Merge Sort and Heap Sort, QuickSort is faster in practice, because its inner loop can be efficiently implemented on
// most architectures, and in most real-world data. QuickSort can be implemented in different ways by changing the
// choice of pivot, so that the worst case rarely occurs for a given type of data. However, merge sort is generally
// considered better when data is huge and stored in external storage.

// Is QuickSort stable?
// The default implementation is not stable.
// However any sorting algorithm can be made stable by considering indexes as comparison parameter.

// Is QuickSort In-place?
// As per the broad definition of in-place algorithm it qualifies as an in-place sorting algorithm
// as it uses extra space only for storing recursive function calls but not for manipulating the input.

// What is 3-Way QuickSort?
// In simple QuickSort algorithm, we select an element as pivot, partition the array around pivot and recur for
// subarrays on left and right of pivot. Consider an array which has many redundant elements. For example, {1, 4, 2, 4,
// 2, 4, 1, 2, 4, 1, 2, 2, 2, 2, 4, 1, 4, 4, 4}. If 4 is picked as pivot in Simple QuickSort, we fix only one 4 and
// recursively process remaining occurrences. In 3 Way QuickSort, an array arr[l..r] is divided in 3 parts: a) arr[l..i]
// elements less than pivot. b) arr[i+1..j-1] elements equal to pivot. c) arr[j..r] elements greater than pivot.

// Why Quick Sort is preferred over MergeSort for sorting Arrays?
// Quick Sort in its general form is an in-place sort (i.e. it doesn’t require any extra storage) whereas merge sort
// requires O(N) extra storage, N denoting the array size which may be quite expensive. Allocating and de-allocating the
// extra space used for merge sort increases the running time of the algorithm. Comparing average complexity we find
// that both type of sorts have O(NlogN) average complexity but the constants differ. For arrays, merge sort loses due
// to the use of extra O(N) storage space. Most practical implementations of Quick Sort use randomized version. The
// randomized version has expected time complexity of O(nLogn). The worst case is possible in randomized version also,
// but worst case doesn’t occur for a particular pattern (like sorted array) and randomized Quick Sort works well in
// practice. Quick Sort is also a cache friendly sorting algorithm as it has good locality of reference when used for
// arrays. Quick Sort is also tail recursive, therefore tail call optimizations is done.

// Why MergeSort is preferred over QuickSort for Linked Lists?
// In case of linked lists the case is different mainly due to difference in memory allocation of arrays and linked
// lists. Unlike arrays, linked list nodes may not be adjacent in memory. Unlike array, in linked list, we can insert
// items in the middle in O(1) extra space and O(1) time. Therefore merge operation of merge sort can be implemented
// without extra space for linked lists. In arrays, we can do random access as elements are continuous in memory. Let us
// say we have an integer (4-byte) array A and let the address of A[0] be x then to access A[i], we can directly access
// the memory at (x + i*4). Unlike arrays, we can not do random access in linked list. Quick Sort requires a lot of this
// kind of access. In linked list to access i’th index, we have to travel each and every node from the head to i’th node
// as we don’t have continuous block of memory. Therefore, the overhead increases for quick sort. Merge sort accesses
// data sequentially and the need of random access is low.

// When does the worst case of Quicksort occur?
// The answer depends on strategy for choosing pivot.
// In early versions of Quick Sort where leftmost (or rightmost) element is chosen as pivot, the worst occurs in
// following cases. 1) Array is already sorted in same order. 2) Array is already sorted in reverse order. 3) All
// elements are same (special case of case 1 and 2) Since these cases are very common use cases, the problem was easily
// solved by choosing either a random index for the pivot, choosing the middle index of the partition or (especially for
// longer partitions) choosing the median of the first, middle and last element of the partition for the pivot. With
// these modifications, the worst case of Quick sort has less chances to occur, but worst case can still occur if the
// input array is such that the maximum (or minimum) element is always chosen as pivot.
