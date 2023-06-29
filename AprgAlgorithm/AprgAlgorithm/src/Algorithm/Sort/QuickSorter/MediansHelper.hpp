#pragma once

#include <Algorithm/Utilities/IndexHelper.hpp>

#include <algorithm>
#include <numeric>#include <vector>

namespace alba {

namespace algorithm {

using Indexes = std::vector<int>;
using IndexesIterator = Indexes::iterator;

template <typename Values>
int getIndexOfMedianOfThree(Values const& values, int const index1, int const index2, int const index3) {
    // Based from: https://en.wikipedia.org/wiki/Quicksort#Choice_of_pivot
    auto low = std::make_pair(values[index1], index1);
    auto mid = std::make_pair(values[index2], index2);
    auto high = std::make_pair(values[index3], index3);
    if (low.first > high.first) {
        std::swap(high, low);
    }
    if (low.first > mid.first) {
        std::swap(mid, low);
    }
    if (mid.first > high.first) {
        std::swap(high, mid);
    }
    return mid.second;
}

template <typename Values>
int getIndexOfMedianOfLowMidHighIndexes(Values const& values, int const lowIndex, int const highIndex) {
    // Recommended by Sedgewick:
    // Choose the median of the first, middle and last element of the partition for the pivot
    return getIndexOfMedianOfThree(values, lowIndex, getMidpointOfIndexes(lowIndex, highIndex), highIndex);
}

template <typename Values>
int getIndexOfMedianNinther(Values const& values, int const lowIndex, int const highIndex) {
    // Based from Tukey's ninther
    // https://en.wikipedia.org/wiki/Median#The_sample_median
    Indexes indexes;
    indexes.reserve(9);
    int deltaSize = highIndex - lowIndex;
    for (int i = 0; i <= 8; i++) {
        indexes.emplace_back(lowIndex + i * deltaSize / 8);
    }

    return getIndexOfMedianOfThree(
        values, getIndexOfMedianOfThree(values, indexes[0], indexes[1], indexes[2]),
        getIndexOfMedianOfThree(values, indexes[3], indexes[4], indexes[5]),
        getIndexOfMedianOfThree(values, indexes[6], indexes[7], indexes[8]));
}

template <typename Values>
int getMedianIndexOfLessThanFive(
    Values const& values, Indexes& medianIndexes, int const lowIndex, int const highIndex) {
    // Perform insertion sort
    for (int insertIndex = lowIndex + 1; insertIndex <= highIndex; insertIndex++) {
        for (int iLow = insertIndex - 1, iHigh = insertIndex;
             lowIndex <= iLow && values[medianIndexes[iLow]] > values[medianIndexes[iHigh]]; iLow--, iHigh--) {
            std::swap(medianIndexes[iLow], medianIndexes[iHigh]);
        }
    }    return getMidpointOfIndexes(lowIndex, highIndex);
}

template <typename Values>
int getIndexOfMedianOfMedians(Values const& values, int const lowIndex, int const highIndex) {
    // Based from https://en.wikipedia.org/wiki/Median_of_medians

    int result{};
    if (lowIndex <= highIndex) {
        Indexes medianIndexes(highIndex - lowIndex);
        std::iota(medianIndexes.begin(), medianIndexes.end(), lowIndex);

        int medianIndexesSize = medianIndexes.size();
        while (medianIndexesSize > 1) {
            int medianIndex = 0;
            for (int lowOfFive = 0; lowOfFive < medianIndexesSize; lowOfFive += 5) {
                int highOfFive = std::min(lowOfFive + 4, medianIndexesSize - 1);
                int medianIndexOfFive = getMedianIndexOfLessThanFive(values, medianIndexes, lowOfFive, highOfFive);
                std::swap(medianIndexes[medianIndex++], medianIndexes[medianIndexOfFive]);
            }
            medianIndexesSize = medianIndex;
        }
        result = medianIndexes.front();
    }    return result;
}

}  // namespace algorithm

}  // namespace alba

// Quick selection in worst-case linear time
// Source: http://staff.ustc.edu.cn/~csli/graduate/algorithms/book6/chap10.htm

// We now examine a selection algorithm whose running time is O(n) in the worst case.
// Like RANDOMIZED-SELECT, the algorithm SELECT finds the desired element by recursively partitioning the input array.
// The idea behind the algorithm, however, is to guarantee a good split when the array is partitioned.
// SELECT uses the deterministic partitioning algorithm PARTITION from quicksort, modified to take the element to
// partition around as an input parameter.

// The SELECT algorithm determines the ith smallest of an input array of n elements by executing the following steps:
// 1. Divide the n elements of the input array into n/5 groups of 5 elements each and at most one group made up of the
// remaining n mod 5 elements.
// 2. Find the median of each of the n/5 groups by insertion sorting the elements of each group (of which there are 5 at
// most) and taking its middle element.
// -> (If the group has an even number of elements, take the larger of the two medians.)
// 3. Use SELECT recursively to find the median x of the n/5 medians found in step 2.
// 4. Partition the input array around the median-of-medians x using a modified version of PARTITION.
// -> Let k be the number of elements on the low side of the partition, so that n - k is the number of elements on the
// high side.
// 5. Use SELECT recursively to find the ith smallest element on the low side if i k, or the (i - k)th smallest element
// on the high side if i > k.

// To analyze the running time of SELECT, we first determine a lower bound on the number of elements that are greater
// than the partitioning element x. At least half of the medians found in step 2 are greater than or equal to the
// median-of-medians x. Thus, at least half of the n/5 groups contribute 3 elements that are greater than x, except for
// the one group that has fewer than 5 elements if 5 does not divide n exactly, and the one group containing x itself.
// Discounting these two groups, it follows that the number of elements greater than x is at least 3n/10 - 6.
// -> 3(ceil(1/2*n/5)-2) >= 3n/10 - 6

// Similarly, the number of elements that are less than x is at least 3n/10 - 6.
// Thus, in the worst case, SELECT is called recursively on at most 7n/10 + 6 elements in step 5.

// We can now develop a recurrence for the worst-case running time T(n) of the algorithm SELECT.
// Steps 1, 2, and 4 take O(n) time.
// Step 2 consists of O(n) calls of insertion sort on sets of size O(1).
// Step 3 takes time T(n/5), and step 5 takes time at most T(7n / 10 + 6), assuming that T is monotonically increasing.
// Note that 7n / 10 + 6 < n for n > 20 and that any input of 80 or fewer elements requires O(1) time.
// We can therefore obtain the recurrence:
// T(n) <= sigma(1)                        if n<=80
//      <= T(n/5) + T(7*n/10 + 6) + O(n)   if n>80

//  We show that the running time is linear by substitution.
// Assume that T(n) cn for some constant c and all n<=80.
// Substituting this inductive hypothesis into the right-hand side of the recurrence yields:
// T(n) <= c(n/5) + c(7n/10 + 6) + O(n)
//      <= cn/5 + c + 7cn/10 + 6c + O(n)
//      <= 9cn/10 + 7c + O(n)
//      <= cn
// since we can pick c large enough so that c(n / 10 - 7) is larger than the function described by the O(n) term for all
// n > 80. The worst-case running time of SELECT is therefore linear.

// As in a comparison sort, SELECT and RANDOMIZED-SELECT determine information about the relative order of elements only
// by comparing elements. Thus, the linear-time behavior is not a result of assumptions about the input, as was the case
// for the sorting algorithms. Sorting requires (n 1g n) time in the comparison model, even on average (see Problem
// 9-1), and thus the method of sorting and indexing presented in the introduction to this chapter is asymptotically
// inefficient.

// Note that the above algorithm is linear in worst case, but the constants are very high for this algorithm.
// Therefore, this algorithm doesn’t work well in practical situations, randomized quickSelect works much better and
// preferred.
