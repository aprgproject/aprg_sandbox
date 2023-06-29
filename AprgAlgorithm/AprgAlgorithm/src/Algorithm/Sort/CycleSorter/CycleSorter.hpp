#pragma once

#include <Algorithm/Sort/BaseSorter.hpp>

#include <algorithm>
#include <utility>

namespace alba {

namespace algorithm {

template <typename Values>
class CycleSorter : public BaseSorter<Values> {
public:
    using Value = typename Values::value_type;

    CycleSorter() = default;

    void sort(Values& valuesToSort) const override {
        int numberOfWrites(0);
        for (int incorrectIndex = 0; incorrectIndex + 2 <= static_cast<int>(valuesToSort.size()); incorrectIndex++) {
            Value cycleValue = valuesToSort[incorrectIndex];  // get cycle value from incorrect index
            int correctIndex = getCorrectIndexForValue(valuesToSort, cycleValue, incorrectIndex);
            if (correctIndex != incorrectIndex) {  // check first unsorted
                moveForwardUntilValueIsDifferent(valuesToSort, cycleValue, correctIndex);
                std::swap(cycleValue, valuesToSort[correctIndex]);
                numberOfWrites++;
                while (correctIndex != incorrectIndex) {
                    // continue to fix cycles until cycle ends (cycle ends if it returned to original index)
                    correctIndex = getCorrectIndexForValue(valuesToSort, cycleValue, incorrectIndex);
                    moveForwardUntilValueIsDifferent(valuesToSort, cycleValue, correctIndex);
                    if (cycleValue != valuesToSort[correctIndex]) {
                        std::swap(cycleValue, valuesToSort[correctIndex]);
                        numberOfWrites++;
                    }
                }            }
        }
    }

private:
    int getCorrectIndexForValue(
        Values const& valuesToSort, Value const& currentCycleValue, int const incorrectIndex) const {
        int numberOfLessValues = std::count_if(
            valuesToSort.cbegin() + incorrectIndex + 1, valuesToSort.cend(),
            [&](Value const& valueToSort) { return valueToSort < currentCycleValue; });
        return incorrectIndex + numberOfLessValues;
    }

    void moveForwardUntilValueIsDifferent(Values const& valuesToSort, Value const& matchingValue, int& index) const {
        // The purpose of the move is to ensure that we are getting a correctIndex with a different value from
        // currentCycleValue.
        // This is to avoid redundant cycles and even infinite cycles.
        // -> Remember after we swap values, we have to look for a new cycle value.
        // ---> Its redundant to look for the value again.

        while (matchingValue == valuesToSort[index]) {
            index++;
        }
    }
};
}  // namespace algorithm

}  // namespace alba
// Cycle sort is an in-place sorting Algorithm, unstable sorting algorithm,
// a comparison sort that is theoretically optimal in terms of the total number of writes to the original array.

// It is optimal in terms of number of memory writes.
// It minimizes the number of memory writes to sort (Each value is either written zero times,
// if it’s already in its correct index, or written one time to its correct index.)
// It is based on the idea that array to be sorted can be divided into cycles.
// We have n nodes and an edge directed from node i to node j if the element at i-th index must be present at j-th index
// in the sorted array.

// We one by one consider all cycles.
// We first consider the cycle that includes first element.
// We find correct index of first element, place it at its correct index, say j.
// We consider old value of arr[j] and find its correct index,
// we keep doing this till all elements of current cycle are placed at correct index, i.e., we don’t come back to
// cycle starting point.

// Explanation :// arr[] = {10, 5, 2, 3}
// index =  0   1   2   3
// cycle_start = 0
// item = 10 = arr[0]

// Find index where we put the item
// pos = cycle_start
// i=pos+1
// while(i<n)// if (arr[i] < item)
//    pos++;

// We put 10 at arr[3] and change item to old value of arr[3].// arr[] = {10, 5, 2, 10}
// item = 3

// Again rotate rest cycle that start with index '0'
// Find index where we put the item = 3
// we swap item with element at arr[1] now
// arr[] = {10, 3, 2, 10}
// item = 5
// Again rotate rest cycle that start with index '0' and item = 5
// we swap item with element at arr[2].
// arr[] = {10, 3, 5, 10 }// item = 2

// Again rotate rest cycle that start with index '0' and item = 2
// arr[] = {2, 3,  5, 10}

// Above is one iteration for cycle_stat = 0.
// Repeat above steps for cycle_start = 1, 2, ..n-2

// Time Complexity : O(n2)
// Worst Case : O(n2)
// Average Case: O(n2)
// Best Case : O(n2)
// This sorting algorithm is best suited for situations where memory write or swap operations are costly.

// Which sorting algorithm makes minimum number of memory writes?

// Minimizing the number of writes is useful when making writes to some huge data set is very expensive,
// such as with EEPROMs or Flash memory, where each write reduces the lifespan of the memory.
// Among the sorting algorithms that we generally study in our data structure and algorithm courses,
// Selection Sort makes least number of writes (it makes O(n) swaps).
// But, Cycle Sort almost always makes less number of writes compared to Selection Sort.
// In Cycle Sort, each value is either written zero times, if it’s already in its correct index, or written one time
// to its correct index. This matches the minimal number of overwrites required for a completed in-place sort.

// Selection sort vs Cycle sort
// Cycle sort has less writes compared to selection sort because it only writes one value in the container
// (the previous value is saved on separate variable) per iteration.
// -> This is less compared to selection sort which swaps the two values per iteration (which have two writes in the// container).
