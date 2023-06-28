#pragma once

#include <Algorithm/Sort/BaseSorter.hpp>
#include <Algorithm/Sort/MergeSorter/MergeSorterUtilities.hpp>
#include <Algorithm/Utilities/IndexHelper.hpp>

namespace alba {
namespace algorithm {

template <typename Values>class TopDownMergeSorter : public BaseSorter<Values> {
public:
    TopDownMergeSorter() = default;

    void sort(Values& valuesToSort) const override {
        if (!valuesToSort.empty()) {
            Values auxiliary(valuesToSort);
            sort(valuesToSort, auxiliary, 0, valuesToSort.size() - 1);
        }
    }

private:
    void sort(Values& valuesToSort, Values& auxiliary, int const lowest, int const highest) const {
        // recursive approach
        if (lowest < highest) {
            int const middle = getMidpointOfIndexes(lowest, highest);
            sort(valuesToSort, auxiliary, lowest, middle);       // sort the first half (recursive call)
            sort(valuesToSort, auxiliary, middle + 1, highest);  // sort the second half (recursive call)
            bool isAlreadySorted(valuesToSort[middle] < valuesToSort[middle + 1]);
            if (!isAlreadySorted) {
                mergeTheTwoSortedParts(valuesToSort, auxiliary, lowest, middle, highest);  // merge the two sorted parts
            }
        }
    }
};

}  // namespace algorithm

}  // namespace alba

// Merge sort was invented by J. von Neumann in 1945.
// Merge sort has a divide and conquer approach
// When billions items to sort, merge sort is faster than insertion sort even if insertion sort is running on super
// computer Lesson 1: Good algorithms are better than super computers.

// Proposition: Mergesort uses at most N*log2(N) compares and 6N*log2(N) array accesses to sort any array of size N.
// Proof: Let the number of compares C(N) and array accesses A(N) to mergesort an array of size N satisfy the
// recurrences. C(N) <= C(N/2) [first half] + C(N/2) [second half] + N [merge] for N>1 with C(1) = 0 A(N) <= A(N/2)
// [first half] + A(N/2) [second half] + N [merge] for N>1 with A(1) = 0 Discrete math: If D(N) = 2D(N/2)+N  for N>1 and
// D(1) = 0 then D(N) = N*log2(N)

// Downside in memory: Merge sort uses extra space proportional to N
// Actually doing an in place merge is possible. Kronrod 1969. Too complex to be used in practice.

// Practical improvements:
// -> Cut off to insertion sort when the subarrays becomes too small (~7 items). Not implemented above
// -> Stop if its already sorted (after sorting 2 parts, check if middle edges are sorted). Implemented above
// -> Eliminate the copy of the auxiliary array, by switching auxiliary and the main. Not implemented above

// Merge sort is an optimal algorithm for the sorting problem
// -> Sorting has a lower bound of N*log2(N) -> Proof: Decision tree and log2(N!) ~ N*log2(N) (Stirling formula)
// -> Merge sort is an optimal algorithm with respect to number of compares
// -> However, merge sort is not optimal on space usage

// Stable -> Proof: Merge sort is stable if the merge operation is stable.
// Since the merge operation is stable (equal items never move past each other), then merge sort is stable.

// Duplicate keys -> If no effect on merge operation, no effect on overall algorithm.

// Other discussions:
// It is possible to sort an array efficiently in O(nlogn) time using algorithms that are not limited to swapping
// consecutive elements. One such algorithm is merge sort, which is based on recursion. Merge sort sorts a subarray
// array[a...b] as follows:
// 1. If a = b, do not do anything, because the subarray is already sorted.
// 2. Calculate the position of the middle element: k = b(a+b)/2.
// 3. Recursively sort the subarray array[a...k].
// 4. Recursively sort the subarray array[k+1...b].
// 5. Merge the sorted subarrays array[a...k] and array[k+1...b] into a sorted subarray array[a...b].
// Merge sort is an efficient algorithm, because it halves the size of the subarray at each step.
// The recursion consists of O(logn) levels, and processing each level takes O(n) time.
// Merging the subarrays array[a...k] and array[k +1...b] is possible in linear time, because they are already sorted.

// Like QuickSort, Merge Sort is a Divide and Conquer algorithm.
// It divides the input array into two halves, calls itself for the two halves, and then merges the two sorted halves.
// The merge() function is used for merging two halves.
// The merge(arr, l, m, r) is a key process that assumes that arr[l..m] and arr[m+1..r] are sorted and merges the two
// sorted sub-arrays into one.

// MergeSort(arr[], l,  r)
// If l < r
// -> Step 1: Find the middle point to divide the array into two halves:
// ---> middle m = l+ (r-l)/2
// -> Step 2: Call mergeSort for first half:
// ---> Call mergeSort(arr, l, m)
// -> Step 3: Call mergeSort for second half:
// ---> Call mergeSort(arr, m+1, r)
// -> Step 4: Merge the two halves sorted in step 2 and 3:
// ---> Call merge(arr, l, m, r)

// Time Complexity: Sorting arrays on different machines.
// Merge Sort is a recursive algorithm and time complexity can be expressed as following recurrence relation.
// -> T(n) = 2T(n/2) + θ(n)
// The above recurrence can be solved either using the Recurrence Tree method or the Master method.
// It falls in case II of Master Method and the solution of the recurrence is θ(nLogn).
// Time complexity of Merge Sort is  θ(nLogn) in all 3 cases (worst, average and best)
// as merge sort always divides the array into two halves and takes linear time to merge two halves.
// Auxiliary Space: O(n)
// Algorithmic Paradigm: Divide and Conquer
// Sorting In Place: No in a typical implementation
// Stable: Yes

// Applications of Merge Sort
// 1) Merge Sort is useful for sorting linked lists in O(nLogn) time.
// -> In the case of linked lists, the case is different mainly due to the difference in memory allocation of arrays and
// linked lists.
// -> Unlike arrays, linked list nodes may not be adjacent in memory.
// -> Unlike an array, in the linked list, we can insert items in the middle in O(1) extra space and O(1) time.
// -> Therefore, the merge operation of merge sort can be implemented without extra space for linked lists.
// -> In arrays, we can do random access as elements are contiguous in memory.
// -> Let us say we have an integer (4-byte) array A and let the address of A[0] be x then to access A[i], we can
// directly access the memory at (x + i*4).
// -> Unlike arrays, we can not do random access in the linked list.
// -> Quick Sort requires a lot of this kind of access.
// -> In a linked list to access i’th index, we have to travel each and every node from the head to i’th node as we
// don’t have a continuous block of memory.
// -> Therefore, the overhead increases for quicksort. Merge sort accesses data sequentially and the need of random
// access is low. 2) Inversion Count Problem 3) Used in External Sorting

// Drawbacks of Merge Sort
// 1) Slower comparative to the other sort algorithms for smaller tasks.
// 2) Merge sort algorithm requires an additional memory space of 0(n) for the temporary array.
// 3) It goes through the whole process even if the array is sorted.
