#pragma once

#include <Algorithm/Sort/BaseSorter.hpp>
#include <Algorithm/Sort/QuickSorter/QuickSorterUtilities.hpp>

#include <utility>

namespace alba {

namespace algorithm {

template <typename Values>
class QuickSorterWith3WayPartitioning : public BaseSorter<Values> {
public:
    QuickSorterWith3WayPartitioning(PivotType const pivotType) : m_pivotType(pivotType) {}

    void sort(Values& valuesToSort) const override {
        if (!valuesToSort.empty()) {
            // You can randomize inputs here to remove dependence on input (quick sort works best if input is not
            // sorted)
            sort(valuesToSort, 0, valuesToSort.size() - 1);
        }
    }

private:
    void sort(Values& valuesToSort, int const lowestIndex, int const highestIndex) const {
        if (lowestIndex < highestIndex) {
            auto pivotValue = getPivotValue(valuesToSort, lowestIndex, highestIndex, m_pivotType);
            // Getting the index of the pivot value is an UGLY WORKAROUND, but we want to have multiple
            // purposes
            int indexWithPivotValue = getIndexOfValue(valuesToSort, lowestIndex, highestIndex, pivotValue);
            if (indexWithPivotValue != lowestIndex) {
                // put it as lowest index so it would not be affected
                std::swap(valuesToSort[indexWithPivotValue], valuesToSort[lowestIndex]);
            }

            int boundaryIndexForLessThan = lowestIndex, boundaryIndexForGreaterThan = highestIndex;
            int i = lowestIndex + 1;

            while (i <= boundaryIndexForGreaterThan)  // i moves within the boundaries
            {
                if (valuesToSort.at(i) < pivotValue) {
                    // swap so that elements that are less than are kept to the left of boundaryIndexForLessThan
                    // i is moved here as well (to keep i within the boundary)
                    std::swap(valuesToSort[boundaryIndexForLessThan++], valuesToSort[i++]);
                } else if (pivotValue < valuesToSort.at(i)) {
                    // swap so that elements that are greater than are kept to the right of boundaryIndexForGreaterThan
                    std::swap(valuesToSort[i], valuesToSort[boundaryIndexForGreaterThan--]);
                } else {
                    i++;  // equal to partition value so just move to the next item
                }
            }
            // sort items that are less than the pivotValue
            sort(valuesToSort, lowestIndex, boundaryIndexForLessThan - 1);
            // sort items that are greater than the pivotValue
            sort(valuesToSort, boundaryIndexForGreaterThan + 1, highestIndex);
            // do nothing for items that are equal to the pivotValue
        }
    }

private:
    PivotType m_pivotType;
};

}  // namespace algorithm

}  // namespace alba

// The motivation of this algorithm is to handle items with duplicate keys more efficiently. (compared to original quick
// sort algorithm) Put the equal items in place and focus(sort/partition) on items that are not equal. This version of
// quicksort is still NOT STABLE.

// This algorithm runs by dividing the partition into 3 parts:
// 1) Values less than the partition value is on the left
// 2) Values greater than the partition value is on the right
// 3) Values equal to the partition value is between (1) and (2)

// This is proposed by Djisktra and he was interested in the correctness of programs.

// Worst case (Lower bound): When the keys are distinct so no need to divide the partition into 3 parts.
// What is interesting about this algorithm is that the number compares its using is equal to the lower bound within a
// constant factor. Proof: provided by Sedgewick-Bentley in 1997

// Bottom line is that randomized quicksort with 3-way partitioning reduces running time from linearithmic to linear in
// broad class of applications.

// Engineering a sort function -> paper by Jon L Bentley and M Douglass Mcllroy
// -> Cut off to insertion sort for small subarrays
// -> Partitioning scheme: 3-way partitioning (like Dijkstra)
// -> Partitioning item:
// ---> small arrays: middle entry
// ---> medium arrays: median of 3
// ---> large arrays: Tukey's ninther
// ------> Pick 9 items in the array (evenly spaced), get median of each 3 samples, get the median of that -> that is
// Tukey's ninther
// ---> Why Tukey's ninther? Inexpensive and gets close to the middle
// -> No random shuffle, so there is no change is the state of the system and less costly
// -> Now widely used: C C++ Java
// -> Solid right? NO! A killer input exists that causes a stack overflow and crashes the program and would take
// quadratic if if didnt crash.
// ---> This is because there is no shuffling done.
