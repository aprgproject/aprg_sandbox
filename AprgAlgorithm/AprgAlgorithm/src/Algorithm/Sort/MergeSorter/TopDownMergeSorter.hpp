#pragma once

#include <Algorithm/Sort/BaseSorter.hpp>
#include <Algorithm/Sort/MergeSorter/MergeSorterUtilities.hpp>

namespace alba
{

namespace algorithm
{

template <typename Values>
class TopDownMergeSorter : public BaseSorter<Values>
{
public:
    void sort(Values & valuesToSort) const override
    {
        if(!valuesToSort.empty())
        {
            Values auxiliary(valuesToSort);
            sort(valuesToSort, auxiliary, 0U, valuesToSort.size()-1);
        }
    }

private:
    void sort(
            Values & valuesToSort,
            Values & auxiliary,
            unsigned int const lowest,
            unsigned int const highest) const
    {
        // recursive approach
        if(lowest < highest)
        {
            unsigned int const middle = (lowest + highest)/2;
            sort(valuesToSort, auxiliary, lowest, middle); // sort the first half (recursive call)
            sort(valuesToSort, auxiliary, middle+1, highest); // sort the second half (recursive call)
            bool isAlreadySorted(valuesToSort.at(middle) < valuesToSort.at(middle+1));
            if(!isAlreadySorted)
            {
                mergeTheTwoSortedParts(valuesToSort, auxiliary, lowest, middle, highest); // merge the two sorted parts
            }
        }
    }
};

// Merge sort has a divide and conquer approach
// When billions items to sort, merge sort is faster than insertion sort even if insertion sort is running on super computer
// Lesson 1: Good algorithms are better than super computers.

// Proposition: Mergesort uses at most N*log2(N) compares and 6N*log2(N) array accesses to sort any array of size N.
// Proof: Let the number of compares C(N) and array accesses A(N) to mergesort an array of size N satisfy the recurrences.
// C(N) <= C(N/2) [first half] + C(N/2) [second half] + N [merge] for N>1 with C(1) = 0
// A(N) <= A(N/2) [first half] + A(N/2) [second half] + N [merge] for N>1 with A(1) = 0
// Discrete math: If D(N) = 2D(N/2)+N  for N>1 and D(1) = 0 then D(N) = N*log2(N)

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

}

}
